#pragma once
#include "../global/base.h"

/*
* class FrameBuffer��
* �洢��ǰ������Ӧ��bmp���ڴ�ָ�룬��Ϊ��ǰ��ͼ����
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