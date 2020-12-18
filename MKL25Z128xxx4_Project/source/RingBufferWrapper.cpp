/*
 * RingBufferWrapper.cpp
 *
 *  Created on: Oct 30, 2019
 *      Author: hudik3
 */

#include <RingBufferWrapper.h>

RingBufferWrapper::RingBufferWrapper(uint8_t *buf, size_t count) :
		dynamicBuffer(false) {
	RbufferInit(&handler, buf, count);
}

RingBufferWrapper::~RingBufferWrapper() {
	if (bufferData != nullptr && dynamicBuffer)
		delete bufferData;
}
/**
 * @param out Output buffer
 * @param count size of output buffer
 * @return Number of read bytes
 */
size_t RingBufferWrapper::read(uint8_t *out, size_t count) {
	return RbufferRead(&handler, out, count);
}

/**
 * @param src Source buffer
 * @param count size of source buffer
 * @return Number of written bytes
 */
size_t RingBufferWrapper::write(const uint8_t *src, size_t count) {
	return RbufferWrite(&handler, src, count);
}

/**
 *
 * @return Number of elements in Ring Buffer
 */
size_t RingBufferWrapper::numOfElements() {
	return RbufferNumOfElements(&handler);
}

RingBufferWrapper::RingBufferWrapper(size_t count) :
		dynamicBuffer(true) {
	bufferData = new uint8_t[count];
	RbufferInit(&handler, bufferData, count);
}

/**
 *
 * @return True if buffer is full or it overflows
 */
bool RingBufferWrapper::IsFull() {
	return RbufferIsFull(&handler);
}
