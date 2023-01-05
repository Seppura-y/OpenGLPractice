#pragma once
#include "../global/base.h"

/*
* class FrameBuffer：
* 存储当前画布对应的bmp的内存指针，作为当前绘图画板
*/
class FrameBuffer {
public:
	FrameBuffer(uint32_t width, uint32_t height, void* buffer = nullptr);
	~FrameBuffer();
	FrameBuffer(const FrameBuffer&) = delete;

	uint32_t	m_Width{ 0 };
	uint32_t	m_Height{ 0 };
	RGBA*		m_ColorBuffer{ nullptr };
	bool		m_ExternBuffer{ false };
};