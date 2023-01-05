#include <Windows.h>

#include <iostream>
#include "application/application.h"

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

	bool alive = true;
	while (alive)
	{
		alive = app->peekMessage();
	}

	return 0;
}