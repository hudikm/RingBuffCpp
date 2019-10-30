/*
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <fsl_clock.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_LPSCI UART0
#define DEMO_LPSCI_CLKSRC kCLOCK_CoreSysClk
#define DEMO_LPSCI_CLK_FREQ CLOCK_GetFreq(kCLOCK_CoreSysClk)
#define DEMO_LPSCI_IRQn UART0_IRQn
#define DEMO_LPSCI_IRQHandler UART0_IRQHandler

/**
 * @file    MKL25Z128xxx4_Project.cpp
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "fsl_lpsci.h"
//#include "RingBuffer.h"
#include "RingBufferWrapper.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

uint8_t g_tipString[] =
		"LPSCI functional API interrupt example\r\nBoard receives characters then sends them out\r\nNow please input:\r\n";

volatile bool new_line_flag = false;

//buffer_t rxBuffer_handler;
//buffer_t txBuffer_handler;
uint8_t rxBufferData[100];
uint8_t txBufferData[100];

/* Setup RingBuffers */
RingBufferWrapper<100> ringBuffRx();
RingBufferWrapper<100> ringBuffTx();

/*******************************************************************************
 * Code
 ******************************************************************************/

extern "C" void DEMO_LPSCI_IRQHandler(void) {

	uint8_t data;

	/* If new data arrived. */
	if ((kLPSCI_RxDataRegFullFlag) & LPSCI_GetStatusFlags(DEMO_LPSCI)) {
		data = LPSCI_ReadByte(DEMO_LPSCI);
		if (data == '\r' || data == '\n')
			new_line_flag = true;
		ringBuffRx.Write(&data, 1);
//		RbufferWrite(&rxBuffer_handler, &data, 1);
	}
	/*If there are data to send*/
	if ((kLPSCI_TxDataRegEmptyFlag & LPSCI_GetStatusFlags(DEMO_LPSCI))) {
		ringBuffTx.Read(&data, 1);
//		RbufferRead(&txBuffer_handler, &data, 1);
		LPSCI_WriteByte(DEMO_LPSCI, data);

		/* Disable TX interrupt If there are NO data to send */
		if (ringBuffTx.NumOfElements() == 0)
			LPSCI_DisableInterrupts(DEMO_LPSCI,
					kLPSCI_TxDataRegEmptyInterruptEnable);
	}

}

/*
 * @brief   Application entry point.
 */
int main(void) {
	lpsci_config_t config;

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();

	CLOCK_SetLpsci0Clock(0x1U);

	/*
	 * config.parityMode = kLPSCI_ParityDisabled;
	 * config.stopBitCount = kLPSCI_OneStopBit;
	 * config.enableTx = false;
	 * config.enableRx = false;
	 */
	LPSCI_GetDefaultConfig(&config);
	config.baudRate_Bps = BOARD_DEBUG_UART_BAUDRATE;
	config.enableTx = true;
	config.enableRx = true;

	LPSCI_Init(DEMO_LPSCI, &config, DEMO_LPSCI_CLK_FREQ);

	/* Send g_tipString out. */
	LPSCI_WriteBlocking(DEMO_LPSCI, g_tipString,
			sizeof(g_tipString) / sizeof(g_tipString[0]));



	/* Enable RX interrupt. */
	LPSCI_EnableInterrupts(DEMO_LPSCI, kLPSCI_RxDataRegFullInterruptEnable);
	EnableIRQ(DEMO_LPSCI_IRQn);

	while (1) {

		// Wait for new line
		while (!new_line_flag) {
		};

		new_line_flag = false; /* Clear new line flag */

		/* Copy data  from rxBuffer to txbuffer*/
//		uint16_t count = RbufferNumOfElements(&rxBuffer_handler);
		uint16_t count = ringBuffRx.NumOfElements();

		uint8_t buffer[count];
		ringBuffRx.Read( buffer, count);
//		RbufferRead(&rxBuffer_handler, buffer, count);

		/* Write new line to txHandler and enable Tx interrupt*/
		ringBuffTx.Write(buffer, count);
//		RbufferWrite(&txBuffer_handler, buffer, count);
		LPSCI_EnableInterrupts(DEMO_LPSCI,
				kLPSCI_TxDataRegEmptyInterruptEnable);
	}
}
