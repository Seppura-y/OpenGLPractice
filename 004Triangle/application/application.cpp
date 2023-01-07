#include"application.h"

Application* Application::m_Instance = nullptr;
Application* Application::getInstance() 
{
	if (m_Instance == nullptr) {
		m_Instance = new Application();
	}

	return m_Instance;
}

Application::Application() {}
Application::~Application() {}

LRESULT CALLBACK Wndproc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	Application::getInstance()->handleMessage(hWnd, message, wParam, lParam);
	return(DefWindowProc(hWnd, message, wParam, lParam));
}

bool Application::initApplication(HINSTANCE hInstance, const uint32_t& width, const uint32_t& height) 
{
	m_Width = width;
	m_Height = height;

	//初始化窗体类型，并且注册
	registerWindowClass(hInstance);

	//生成一个窗体，并且显示
	if (!createWindow(hInstance)) 
	{
		return false;
	}

	//初始化画布
	/*
	* DC：Device Context 设备上下文描述对象
	* 每个窗口都有自己对应的设备区域映射，即m_MainDC
	* 这里创建一个与本窗口兼容的DC，m_CanvasDC
	* 可以从m_CanvasDC向m_MainDC拷贝绘图数据内容
	*/
	m_MainDC = GetDC(m_Hwnd);
	m_CanvasDC = CreateCompatibleDC(m_MainDC);

	BITMAPINFO  bmpInfo{};
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth = m_Width;
	bmpInfo.bmiHeader.biHeight = m_Height;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 32;
	bmpInfo.bmiHeader.biCompression = BI_RGB; //实际上存储方式为bgra

	//创建与m_hMem兼容的位图,其实实在m_hMem指代的设备上划拨了一块内存，让m_CanvasBuffer指向它
	m_hBmp = CreateDIBSection(m_CanvasDC, &bmpInfo, DIB_RGB_COLORS, (void**)&m_CanvasBuffer, 0, 0);//在这里创建buffer的内存

	//一个设备可以创建多个位图，本设备使用m_hBmp作为激活位图，对m_CanvasDC的内存拷出，其实就是拷出了m_hBmp的数据
	SelectObject(m_CanvasDC, m_hBmp);

	memset(m_CanvasBuffer, 0, m_Width * m_Height * 4); //清空buffer为0

	return true;
}

ATOM Application::registerWindowClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wndClass;

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//水平/垂直大小发生变化重绘窗口
	wndClass.lpfnWndProc = Wndproc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;									//应用程序句柄
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//应用程序图标,即任务栏的大图标
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//鼠标图标
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);	//窗口背景色
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = m_WindowClassName;						//窗口类名
	wndClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);					//窗口标题图标

	return RegisterClassExW(&wndClass);
}

BOOL Application::createWindow(HINSTANCE hInstance)
{
	m_WindowInst = hInstance;

	/*
	* WS_POPUP:不需要标题栏，则不需要边框
	* WS_OVERLAPPEDWINDOW：拥有普通程序主窗口的所有特点，必须有标题且有边框
	*
	* WS_CLIPSIBLINGS:被兄弟窗口挡住区域不绘制
	* WS_CLIPCHILDREN:被子窗口遮挡住的区域不绘制
	*/

	auto dwExStyle = WS_EX_APPWINDOW;
	auto dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	//由于存在标题栏等，所以需要计算中间显示区域的大小,比如PopUp的窗体，就没有标题栏，则不会改变
	RECT windowRect;
	windowRect.left = 0L;
	windowRect.top = 0L;
	windowRect.right = (long)m_Width;
	windowRect.bottom = (long)m_Height;
	AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

	m_Hwnd = CreateWindowW(
		m_WindowClassName,
		(LPCWSTR)"GraphicLearning",			//窗体标题
		dwStyle,
		500,								//x位置，相对左上角
		500,								//y位置，相对左上角
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		nullptr,							//父窗体
		nullptr,							//菜单栏
		hInstance,							//程序实例
		nullptr);							//额外参数


	if (!m_Hwnd)
	{
		return FALSE;
	}

	ShowWindow(m_Hwnd, true);
	UpdateWindow(m_Hwnd);

	return TRUE;
}

bool Application::peekMessage() 
{
	MSG msg;
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return m_Alive;
}

void Application::handleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch (message)
	{
		case WM_CLOSE: 
		{
			DestroyWindow(hWnd);//此处销毁窗体,会自动发出WM_DESTROY
			break;
		}
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
		}
		break;
		case WM_DESTROY: 
		{
			PostQuitMessage(0);//发出线程终止请求
			m_Alive = false;
			break;
		}
	}
}

void Application::show() 
{
	BitBlt(m_MainDC, 0, 0, m_Width, m_Height, m_CanvasDC, 0, 0, SRCCOPY);
}