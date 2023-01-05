#pragma once
#include "../global/base.h"
#include<Windows.h>

#define app Application::getInstance()

class Application
{
public:
	static Application* getInstance();

	bool initApplication(HINSTANCE hInstance, const uint32_t& width = 800, const uint32_t& height = 600);

	void handleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	bool peekMessage();

	void show();
	uint32_t getWidth() const { return m_Width; }
	uint32_t getHeight() const { return m_Height; }
	void* getCanvas() const { return m_CanvasBuffer; }


private:
	Application();
	~Application();

	BOOL createWindow(HINSTANCE hInstance);
	ATOM registerWindowClass(HINSTANCE hInstance);

private:
	static Application* m_Instance;

	bool		m_Alive = true;

	HINSTANCE	m_WindowInst;
	WCHAR		m_WindowClassName[100] = L"AppWindow";
	HWND		m_Hwnd;

	int			m_Width = 800;
	int			m_Height = 600;

	HDC			m_hDC;							//当前窗口主dc
	HDC			m_CanvasDC;						//创建的于mhDC相兼容的绘图用的dc
	HBITMAP		m_hBmp;							//mCanvasDC内部生成的bitmap
	void*		m_CanvasBuffer{ nullptr };		//mhBmp对应的内存起始位置指针
};