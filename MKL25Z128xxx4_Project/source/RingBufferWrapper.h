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
	size_t read(uint8_t *out, size_t count);
	template<typename T>
	size_t write(T src, size_t count) {
		return write((const uint8_t*)(src), count);
	}
	size_t write(const uint8_t *src, size_t coun);
	size_t numOfElements();
	bool IsFull();

private:
	const bool dynamicBuffer;
	buffer_t handler;
	uint8_t *bufferData = nullptr;
};

#endif /* RINGBUFFERWRAPPER_H_ */
