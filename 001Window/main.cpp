#include <Windows.h>

#include <iostream>
#include "application/application.h"

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

	bool alive = true;
	while (alive)
	{
		alive = app->peekMessage();
	}

	return 0;
}