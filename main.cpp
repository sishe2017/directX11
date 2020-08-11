#include <Windows.h>
#include <windowsx.h>
#include <string>
#include <iostream>

using namespace std;

LRESULT CALLBACK WindowsCallback(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, PSTR szCmdLine, int iCmdShow)
{
	WNDCLASS wndclass;
	//当水平或者垂直方向发生变化的时候，重新绘制整个窗口
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	//设置窗口回调函数
	wndclass.lpfnWndProc = WindowsCallback;
	//设置该窗口类的附加空间
	wndclass.cbClsExtra = 0;
	//设置创建的窗口的附加空间
	wndclass.cbWndExtra = 0;
	//设置窗口的进程句柄
	wndclass.hInstance = hInstance;
	//设置窗口的图标
	wndclass.hIcon = LoadIcon(0, IDI_APPLICATION);
	//设置窗口的光标
	wndclass.hCursor = LoadCursor(0, IDC_ARROW);
	//设置窗口背景颜色
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	//设置菜单名字
	wndclass.lpszMenuName = 0;
	//设置窗口类名
	wndclass.lpszClassName = L"MainWindow";

	//注册窗口
	if (!RegisterClass(&wndclass))
	{
		MessageBox(0, L"RegisterClass Failed.", 0, 0);
		return 0;
	}
	//创建窗口
	auto hWindow = CreateWindow(L"MainWindow", L"Hello World",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, 0, 0, hInstance, 0);
	if (!hWindow)
	{
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		return 0;
	}

	//显示窗口
	::ShowWindow(hWindow, SW_SHOW);
	//更新窗口
	UpdateWindow(hWindow);

	//消息循环
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		//将消息翻译成字符
		TranslateMessage(&msg);
		//将消息发送到窗口，触发WndProc回调
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowsCallback(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	static wstring pos;
	HDC hdc;
	int x = GET_X_LPARAM(lParam);
	int y = GET_Y_LPARAM(lParam);

	TCHAR szText[256] = { 0 };

	switch (msg)
	{
	//鼠标移动的消息
	case WM_MOUSEMOVE:
		//获取鼠标的x坐标和y坐标
		pos = to_wstring(x) + L" " + to_wstring(y);
		hdc = GetDC(hwnd);
		TextOut(hdc, 400, 300, pos.c_str(), pos.size());
		ReleaseDC(hwnd, hdc);
		return 0;

	//esc键退出窗口
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
		}
		PostQuitMessage(0);
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}
