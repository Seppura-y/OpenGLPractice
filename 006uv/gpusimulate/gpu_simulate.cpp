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
	if (x >= m_FrameBuffer->m_Width || y >= m_FrameBuffer->m_Height) {
		return;
	}

	//从窗口左下角开始算起
	uint32_t pixelPos = y * m_FrameBuffer->m_Width + x;


	RGBA result = color;

	if (is_blending_) {
		//加入blending
		auto src = color;
		auto dst = m_FrameBuffer->m_ColorBuffer[pixelPos];
		float weight = static_cast<float>(src.mA) / 255.0f;

		result.mR = static_cast<float>(src.mR) * weight + static_cast<float>(dst.mR) * (1.0f - weight);
		result.mG = static_cast<float>(src.mG) * weight + static_cast<float>(dst.mG) * (1.0f - weight);
		result.mB = static_cast<float>(src.mB) * weight + static_cast<float>(dst.mB) * (1.0f - weight);
		result.mA = static_cast<float>(src.mA) * weight + static_cast<float>(dst.mA) * (1.0f - weight);
	}


	m_FrameBuffer->m_ColorBuffer[pixelPos] = result;
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

	RGBA resultColor;
	for (auto p : pixels) 
	{
		if (m_image_)
		{
			resultColor = sampleNearest(p.uv);
		}
		else
		{
			resultColor = p.color;
		}
		drawPoint(p.x, p.y, resultColor);
	}
}

void GPUSimulate::drawImage(const Image* image) 
{
	for (uint32_t i = 0; i < image->width_; ++i) 
	{
		for (uint32_t j = 0; j < image->height_; ++j) 
		{
			drawPoint(i, j, image->data_[j * image->width_ + i]);
		}
	}
}

void GPUSimulate::drawImageWithAlpha(const Image* image, const uint32_t& alpha)
{
	RGBA color;
	for (uint32_t i = 0; i < image->width_; ++i)
	{
		for (uint32_t j = 0; j < image->height_; ++j)
		{
			color = image->data_[j * image->width_ + i];
			color.mA = alpha;
			drawPoint(i, j, color);
		}
	}
}

//设置状态
void GPUSimulate::setBlending(bool enable)
{
	is_blending_ = enable;
}

void GPUSimulate::setTexture(Image* image)
{
	m_image_ = image;
}

RGBA GPUSimulate::sampleNearest(const math::vec2f& uv)
{
	auto myUV = uv;

	//四舍五入到最近整数
	// u = 0 对应 x = 0，u = 1 对应 x = width - 1
	// v = 0 对应 y = 0，v = 1 对应 y = height - 1
	int x = std::round(myUV.x * (m_image_->width_ - 1));
	int y = std::round(myUV.y * (m_image_->height_ - 1));

	int position = y * m_image_->width_ + x;
	return m_image_->data_[position];
}