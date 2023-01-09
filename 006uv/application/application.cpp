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

	//��ʼ���������ͣ�����ע��
	registerWindowClass(hInstance);

	//����һ�����壬������ʾ
	if (!createWindow(hInstance)) 
	{
		return false;
	}

	//��ʼ������
	/*
	* DC��Device Context �豸��������������
	* ÿ�����ڶ����Լ���Ӧ���豸����ӳ�䣬��m_MainDC
	* ���ﴴ��һ���뱾���ڼ��ݵ�DC��m_CanvasDC
	* ���Դ�m_CanvasDC��m_MainDC������ͼ��������
	*/
	m_MainDC = GetDC(m_Hwnd);
	m_CanvasDC = CreateCompatibleDC(m_MainDC);

	BITMAPINFO  bmpInfo{};
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth = m_Width;
	bmpInfo.bmiHeader.biHeight = m_Height;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 32;
	bmpInfo.bmiHeader.biCompression = BI_RGB; //ʵ���ϴ洢��ʽΪbgra

	//������m_hMem���ݵ�λͼ,��ʵʵ��m_hMemָ�����豸�ϻ�����һ���ڴ棬��m_CanvasBufferָ����
	m_hBmp = CreateDIBSection(m_CanvasDC, &bmpInfo, DIB_RGB_COLORS, (void**)&m_CanvasBuffer, 0, 0);//�����ﴴ��buffer���ڴ�

	//һ���豸���Դ������λͼ�����豸ʹ��m_hBmp��Ϊ����λͼ����m_CanvasDC���ڴ濽������ʵ���ǿ�����m_hBmp������
	SelectObject(m_CanvasDC, m_hBmp);

	memset(m_CanvasBuffer, 0, m_Width * m_Height * 4); //���bufferΪ0

	return true;
}

ATOM Application::registerWindowClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wndClass;

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//ˮƽ/��ֱ��С�����仯�ػ洰��
	wndClass.lpfnWndProc = Wndproc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;									//Ӧ�ó�����
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//Ӧ�ó���ͼ��,���������Ĵ�ͼ��
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//���ͼ��
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);	//���ڱ���ɫ
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = m_WindowClassName;						//��������
	wndClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);					//���ڱ���ͼ��

	return RegisterClassExW(&wndClass);
}

BOOL Application::createWindow(HINSTANCE hInstance)
{
	m_WindowInst = hInstance;

	/*
	* WS_POPUP:����Ҫ������������Ҫ�߿�
	* WS_OVERLAPPEDWINDOW��ӵ����ͨ���������ڵ������ص㣬�����б������б߿�
	*
	* WS_CLIPSIBLINGS:���ֵܴ��ڵ�ס���򲻻���
	* WS_CLIPCHILDREN:���Ӵ����ڵ�ס�����򲻻���
	*/

	auto dwExStyle = WS_EX_APPWINDOW;
	auto dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	//���ڴ��ڱ������ȣ�������Ҫ�����м���ʾ����Ĵ�С,����PopUp�Ĵ��壬��û�б��������򲻻�ı�
	RECT windowRect;
	windowRect.left = 0L;
	windowRect.top = 0L;
	windowRect.right = (long)m_Width;
	windowRect.bottom = (long)m_Height;
	AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

	m_Hwnd = CreateWindowW(
		m_WindowClassName,
		(LPCWSTR)"GraphicLearning",			//�������
		dwStyle,
		500,								//xλ�ã�������Ͻ�
		500,								//yλ�ã�������Ͻ�
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		nullptr,							//������
		nullptr,							//�˵���
		hInstance,							//����ʵ��
		nullptr);							//�������


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
			DestroyWindow(hWnd);//�˴����ٴ���,���Զ�����WM_DESTROY
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
			PostQuitMessage(0);//�����߳���ֹ����
			m_Alive = false;
			break;
		}
	}
}

void Application::show() 
{
	BitBlt(m_MainDC, 0, 0, m_Width, m_Height, m_CanvasDC, 0, 0, SRCCOPY);
}