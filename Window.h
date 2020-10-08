#pragma once
#include <string>
#include <Windows.h>
#include "Keyboard.h"
#include "Mouse.h"


//��Ϸ����
class Window
{
public:
	Window(int width, int height, std::wstring caption);
	~Window();
	//��ֹ�����͸�ֵ
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	//���ھ��
	HWND hwnd;

private:
	//���ڿ��
	int width;
	//���ڸ߶�
	int height;
	//���ھ��
	HINSTANCE hInstance;

	//����Ĵ��ڵĻص��¼����ڴ��ڴ������֮ǰ��ʹ��Ĭ�ϴ���
	static LRESULT CALLBACK FirstWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	//�����Ĵ��ڵĻص��¼�
	static LRESULT CALLBACK FollowWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	//���ڻص��¼�����
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

