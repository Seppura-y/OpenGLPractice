#include <Windows.h>

#include <iostream>

#include "application/application.h"
#include "gpusimulate/gpu_simulate.h"

Image* texture;
Point p1;
Point p2;
Point p3;

Point q1;
Point q2;
Point q3;

void render() 
{
	GPUSim->clear();
	GPUSim->setTexture(texture);

	GPUSim->setBilinear(false);
	GPUSim->drawTriangle(p1, p2, p3);

	GPUSim->setBilinear(true);
	GPUSim->drawTriangle(q1, q2, q3);
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

	q1.x = texture->width_ + 0;
	q1.y = 0;
	q1.color = RGBA(255, 0, 0, 255);
	q1.uv = math::vec2f(0.0f, 0.0f);

	q2.x = texture->width_ + texture->width_ / 2;
	q2.y = texture->height_;
	q2.color = RGBA(0, 255, 0, 255);
	q2.uv = math::vec2f(0.5f, 1.0f);

	q3.x = texture->width_ * 2;
	q3.y = 0;
	q3.color = RGBA(0, 0, 255, 255);
	q3.uv = math::vec2f(1.0f, 0.0f);
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