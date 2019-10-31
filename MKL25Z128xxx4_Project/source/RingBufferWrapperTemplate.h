/*
 * RingBufferWrapper.h
 *
 *  Created on: Oct 30, 2019
 *      Author: hudik3
 */

#ifndef RINGBUFFERWRAPPERTEMPLATE_H_
#define RINGBUFFERWRAPPERTEMPLATE_H_
#include <RingBuffer.h>


template <int COUNT>
class RingBufferWrapperTemplate: public RingBufferWrapper {
public:
	RingBufferWrapperTemplate():RingBufferWrapper(bufferData, COUNT){
	}

private:
	uint8_t bufferData[COUNT];
};


#endif /* RINGBUFFERWRAPPERTEMPLATE_H_ */
