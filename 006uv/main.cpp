#include <Windows.h>

#include <iostream>

#include "application/application.h"
#include "gpusimulate/gpu_simulate.h"

Image* texture;
Point p1;
Point p2;
Point p3;

void render() 
{
	GPUSim->clear();
	GPUSim->setTexture(texture);
	GPUSim->drawTriangle(p1, p2, p3);
}

void prepare() {
	texture = Image::createImage("assets/textures/cat.jpg");

	p1.x = 0;
	p1.y = 0;
	p1.color = RGBA(255, 0, 0, 255);
	p1.uv = math::vec2f(0.0f, 0.0f);

	p2.x = texture->width_ / 2;
	p2.y = texture->height_;
	p2.color = RGBA(0, 255, 0, 255);
	p2.uv = math::vec2f(0.5f, 1.0f);

	p3.x = texture->width_;
	p3.y = 0;
	p3.color = RGBA(0, 0, 255, 255);
	p3.uv = math::vec2f(1.0f, 0.0f);
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

	prepare();

	bool alive = true;
	while (alive)
	{
		alive = app->peekMessage();
		render();
		app->show();
	}

	Image::destroyImage(texture);
	return 0;
}