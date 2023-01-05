#include <Windows.h>

#include <iostream>
#include "application/application.h"
#include "gpusimulate/gpu_simulate.h"

void render()
{
	GPUSim->clear();

	//for (uint32_t i = 0; i < app->getWidth(); ++i) {
//	sgl->drawPoint(i, 500, RGBA(255, 255, 255));
//}

	for (uint32_t i = 0; i < app->getWidth(); ++i) 
	{
		for (uint32_t j = 0; j < app->getHeight(); ++j) 
		{
			uint32_t v = std::rand() % 255;
			RGBA color(v, v, v, v);
			GPUSim->drawPoint(i, j, color);
		}
	}
}

int CALLBACK WinMain(
	HINSTANCE	hInstance,		//��Ӧ�ó���ʵ�������Ψһָ����ǰ����
	HINSTANCE	hPrevInstance,	//������ǰһ��ʵ����һ����null
	LPSTR		lpCmdLine,		//�����в���
	int			nCmdShow)		//ָ��Ӧ�ó���������ʾ(�����С����)
{
	if (!app->initApplication(hInstance, 800, 600))
	{
		return -1;
	}

	GPUSim->initSurface(app->getWidth(), app->getHeight(), app->getCanvas());

	bool alive = true;
	while (alive)
	{
		alive = app->peekMessage();
		render();
		app->show();
	}

	return 0;
}