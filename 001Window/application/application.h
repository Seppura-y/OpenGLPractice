#pragma once
#include "../global/base.h"
#include<Windows.h>

#define app Application::getInstance()

class Application
{
public:
	static Application* getInstance();
	Application();
	~Application();

	bool initApplication(HINSTANCE hInstance, const uint32_t& width = 800, const uint32_t& height = 600);

	void handleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	bool peekMessage();

private:
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
};