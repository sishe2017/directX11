#pragma once
#include <string>
#include <Windows.h>
#include <functional>

//Windows窗口类
class Window
{
	friend LRESULT CALLBACK WindowCallBack(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	Window(HINSTANCE hGame, std::wstring name);
	~Window();
	
	//设置窗口尺寸
	void SetSize(int width, int height);
	//显示窗口
	void ShowWindow();

private:
	//程序实例句柄
	HINSTANCE hGame;
	//窗口句柄
	HWND hWindow;
	//窗口名字
	std::wstring name;
	//窗口宽度
	int width;
	//窗口高度
	int height;
	

	//窗口的消息处理回调函数
	LRESULT MessageProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

