/*
 * RingBufferWrapper.cpp
 *
 *  Created on: Oct 30, 2019
 *      Author: hudik3
 */

#include <RingBufferWrapper.h>

RingBufferWrapper::RingBufferWrapper(uint8_t *buf, size_t count) {
	RbufferInit(&handler, buf, count);
}

RingBufferWrapper::~RingBufferWrapper() {
	delete bufferData;
}

size_t RingBufferWrapper::Read(uint8_t* out, size_t count) {
	return RbufferRead(&handler, out, count);
}

size_t RingBufferWrapper::Write(const uint8_t* src, size_t count) {
	return RbufferWrite(&handler, src, count);
}

size_t RingBufferWrapper::NumOfElements() {
	return RbufferNumOfElements(&handler);
}

RingBufferWrapper::RingBufferWrapper(size_t count) {
	bufferData = new uint8_t[count];
	RbufferInit(&handler, bufferData, count);
}

bool RingBufferWrapper::IsFull() {
	return RbufferIsFull(&handler);
}
