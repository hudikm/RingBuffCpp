/*
 * RingBufferWrapper.h
 *
 *  Created on: Oct 30, 2019
 *      Author: hudik3
 */

#ifndef RINGBUFFERWRAPPER_H_
#define RINGBUFFERWRAPPER_H_
#include <RingBuffer.h>

template <int COUNT>
class RingBufferWrapper {
public:
//	RingBufferWrapper(uint8_t *buf, size_t count);
//	RingBufferWrapper(size_t count);
//	RingBufferWrapper();
//	virtual ~RingBufferWrapper();
	size_t Read(uint8_t *out, size_t count);
	size_t Write(const uint8_t *src, size_t coun);
	size_t NumOfElements();
	bool IsFull();

private:
	buffer_t handler;
	uint8_t bufferData[100];
};

template<size_t COUNT>
 RingBufferWrapper<>::RingBufferWrapper(uint8_t* buf, size_t count) {
	RbufferInit(&handler, buf, count);
}

template<size_t COUNT>
 RingBufferWrapper<>::RingBufferWrapper() {
}

template<size_t COUNT>
 RingBufferWrapper<>::~RingBufferWrapper() {
	delete bufferData;
}

template<size_t COUNT>
 size_t RingBufferWrapper<>::Read(uint8_t* out, size_t count) {
	return RbufferRead(&handler, out, count);
}

template<size_t COUNT>
 size_t RingBufferWrapper<>::Write(const uint8_t* src, size_t count) {
	return RbufferWrite(&handler, src, count);
}

template<size_t COUNT>
 size_t RingBufferWrapper<>::NumOfElements() {
	return RbufferNumOfElements(&handler);
}

template<size_t COUNT>
 bool RingBufferWrapper<>::IsFull() {
	return RbufferIsFull(&handler);
}

#endif /* RINGBUFFERWRAPPER_H_ */
