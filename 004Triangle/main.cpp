#include <Windows.h>

#include <iostream>
#include "application/application.h"
#include "gpusimulate/gpu_simulate.h"

void render()
{
	GPUSim->clear();

	//int r = 150;
	//Point c{ 400, 300, RGBA(255, 0, 0, 255) };

	//for (float i = 0; i < 360; i += 10)
	//{
	//	float radian = DEG2RAD(i);
	//	int x = r * sin(radian) + c.x;
	//	int y = r * cos(radian) + c.y;

	//	Point  pt{ x, y, RGBA(rand() % 255, rand() % 255, rand() % 255, 255) };

	//	GPUSim->drawLine(c, pt);
	//}


	Point p1{ 0, 100, RGBA(255, 0, 0, 255) };
	Point p2{ 500, 100, RGBA(0, 255, 0, 255) };
	Point p3{ 250, 500, RGBA(0, 0, 255, 255) };

	GPUSim->drawTriangle(p1, p2, p3);
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