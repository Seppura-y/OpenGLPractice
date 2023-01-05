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
	HINSTANCE	hInstance,		//本应用程序实例句柄，唯一指代当前程序
	HINSTANCE	hPrevInstance,	//本程序前一个实例，一般是null
	LPSTR		lpCmdLine,		//命令行参数
	int			nCmdShow)		//指定应用程序改如何显示(最大、最小化等)
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