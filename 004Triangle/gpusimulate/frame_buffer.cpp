#include "frame_buffer.h"

FrameBuffer::FrameBuffer(uint32_t width, uint32_t height, void* buffer) {
	m_Width = width;
	m_Height = height;

	if (!buffer) {
		buffer = new RGBA[width * height];
		m_ExternBuffer = false;
	}
	else {
		m_ExternBuffer = true;
	}

	m_ColorBuffer = (RGBA*)buffer;

}

FrameBuffer::~FrameBuffer() {
	if (!m_ExternBuffer && m_ColorBuffer) 
	{
		delete[] m_ColorBuffer;
	}
}