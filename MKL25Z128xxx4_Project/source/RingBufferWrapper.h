/*
 * RingBufferWrapper.h
 *
 *  Created on: Oct 30, 2019
 *      Author: hudik3
 */

#ifndef RINGBUFFERWRAPPER_H_
#define RINGBUFFERWRAPPER_H_
#include <RingBuffer.h>


class RingBufferWrapper {
public:
	RingBufferWrapper(uint8_t *buf, size_t count);
	RingBufferWrapper(size_t count);

	virtual ~RingBufferWrapper();
	size_t Read(uint8_t *out, size_t count);
	size_t Write(const uint8_t *src, size_t coun);
	size_t NumOfElements();
	bool IsFull();

private:
	buffer_t handler;
	uint8_t *bufferData;
};


#endif /* RINGBUFFERWRAPPER_H_ */
