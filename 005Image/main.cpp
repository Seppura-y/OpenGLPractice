#include <Windows.h>

#include <iostream>

#include "application/application.h"
#include "gpusimulate/gpu_simulate.h"

Image* image01 = Image::createImage("assets/textures/cat.jpg");
Image* image02 = Image::createImage("assets/textures/cat2.jpg");
void render()
{
	GPUSim->clear();

	GPUSim->setBlending(true);
	//GPUSim->drawImage(image01);
	GPUSim->drawImageWithAlpha(image01, 80);
	GPUSim->drawImageWithAlpha(image02, 100);
}

int CALLBACK WinMain(
	HINSTANCE	hInstance,		//本应用程序实例句柄，唯一指代当前程序
	HINSTANCE	hPrevInstance,	//本程序前一个实例，一般是null
	LPSTR		lpCmdLine,		//命令行参数
	int			nCmdShow)		//指定应用程序改如何显示(最大、最小化等)
{
	if (!app->initApplication(hInstance, 1920, 1080))
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