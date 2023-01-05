#include "gpu_simulate.h"

GPUSimulate* GPUSimulate::m_Instance = nullptr;
GPUSimulate* GPUSimulate::getInstance() 
{
	if (!m_Instance) 
	{
		m_Instance = new GPUSimulate();
	}

	return m_Instance;
}

GPUSimulate::GPUSimulate() {}

GPUSimulate::~GPUSimulate() 
{
	if (m_FrameBuffer) 
	{
		delete m_FrameBuffer;
	}
}

void GPUSimulate::initSurface(const uint32_t& width, const uint32_t& height, void* buffer) 
{
	m_FrameBuffer = new FrameBuffer(width, height, buffer);
}

void GPUSimulate::clear() 
{
	size_t pixelSize = m_FrameBuffer->m_Width * m_FrameBuffer->m_Height;
	std::fill_n(m_FrameBuffer->m_ColorBuffer, pixelSize, RGBA(0, 0, 0, 0));
}

void GPUSimulate::drawPoint(const uint32_t& x, const uint32_t& y, const RGBA& color) 
{
	//从窗口左下角开始算起
	uint32_t pixelPos = y * m_FrameBuffer->m_Width + x;
	m_FrameBuffer->m_ColorBuffer[pixelPos] = color;
}
