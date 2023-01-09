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
	HINSTANCE	hInstance,		//��Ӧ�ó���ʵ�������Ψһָ����ǰ����
	HINSTANCE	hPrevInstance,	//������ǰһ��ʵ����һ����null
	LPSTR		lpCmdLine,		//�����в���
	int			nCmdShow)		//ָ��Ӧ�ó���������ʾ(�����С����)
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