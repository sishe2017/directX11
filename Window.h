#pragma once
#include <string>
#include <Windows.h>
#include "Keyboard.h"
#include "Mouse.h"


//游戏窗口
class Window
{
public:
	Window(int width, int height, std::wstring caption);
	~Window();
	//禁止拷贝和赋值
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	//窗口句柄
	HWND hwnd;

private:
	//窗口宽度
	int width;
	//窗口高度
	int height;
	//窗口句柄
	HINSTANCE hInstance;

	//最初的窗口的回调事件：在窗口创建完成之前都使用默认处理
	static LRESULT CALLBACK FirstWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	//后续的窗口的回调事件
	static LRESULT CALLBACK FollowWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	//窗口回调事件处理
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

