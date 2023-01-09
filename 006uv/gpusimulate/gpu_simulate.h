#pragma once
#include "../global/base.h"
#include "frame_buffer.h"
#include "../application/application.h"
#include "../application/image.h"
#include "../math/math.h"

#define GPUSim GPUSimulate::getInstance()

class GPUSimulate
{
public:
	static GPUSimulate* getInstance();

	void initSurface(const uint32_t& width,const uint32_t& height,void* buffer = nullptr);
	void clear();
	void drawPoint(const uint32_t& x, const uint32_t& y, const RGBA& color);
	void drawLine(const Point& p1, const Point& p2);
	void drawTriangle(const Point& p1, const Point& p2, const Point& p3);
	void drawImage(const Image* image);
	void drawImageWithAlpha(const Image* image, const uint32_t& alpha);

	void setBlending(bool enable);
	void setTexture(Image* image);

private:
	GPUSimulate();
	~GPUSimulate();

	RGBA sampleNearest(const math::vec2f& uv);
private:
	static GPUSimulate* m_Instance;

	FrameBuffer* m_FrameBuffer{ nullptr };

	bool is_blending_ = false;

	Image* m_image_ = nullptr;
};