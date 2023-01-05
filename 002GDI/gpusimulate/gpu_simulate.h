#pragma once
#include "../global/base.h"
#include "frame_buffer.h"
#include "../application/application.h"

#define GPUSim GPUSimulate::getInstance()

class GPUSimulate
{
public:
	static GPUSimulate* getInstance();

	void initSurface(const uint32_t& width,const uint32_t& height,void* buffer = nullptr);
	void clear();
	void drawPoint(const uint32_t& x, const uint32_t& y, const RGBA& color);

private:
	GPUSimulate();
	~GPUSimulate();

	static GPUSimulate* m_Instance;

	FrameBuffer* m_FrameBuffer{ nullptr };
};