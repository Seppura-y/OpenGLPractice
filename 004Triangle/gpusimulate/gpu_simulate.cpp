#include "gpu_simulate.h"
#include "raster.h"

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
	//�Ӵ������½ǿ�ʼ����
	uint32_t pixelPos = y * m_FrameBuffer->m_Width + x;
	m_FrameBuffer->m_ColorBuffer[pixelPos] = color;
}

void GPUSimulate::drawLine(const Point& p1, const Point& p2)
{
	std::vector<Point> pixels;
	Raster::rasterizeLine(pixels, p1, p2);

	for (auto p : pixels) 
	{
		drawPoint(p.x, p.y, p.color);
	}
}

void GPUSimulate::drawTriangle(const Point& p1, const Point& p2, const Point& p3) {
	std::vector<Point> pixels;
	Raster::rasterizeTriangle(pixels, p1, p2, p3);

	for (auto p : pixels) {
		drawPoint(p.x, p.y, p.color);
	}
}