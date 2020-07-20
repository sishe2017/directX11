#include "Window.h"

//窗口回调函数指针
Window *cbPtr = nullptr;

LRESULT CALLBACK WindowCallBack(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return cbPtr->MessageProc(hwnd, msg, wParam, lParam);
}

Window::Window(HINSTANCE hGame, std::wstring name):
	hGame(hGame),
	name(name),
	width(800),
	height(600),
	hWindow(0)
{
	//回调指针指向自身
	cbPtr = this;
}

Window::~Window()
{
}

//设置窗口尺寸
void Window::SetSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void Window::ShowWindow()
{
	WNDCLASS mainWindow;
	//当水平或者垂直方向发生变化的时候，重新绘制整个窗口
	mainWindow.style = CS_HREDRAW | CS_VREDRAW;
	//设置窗口回调函数
	mainWindow.lpfnWndProc = WindowCallBack;
	//设置该类的附加空间
	mainWindow.cbClsExtra = 0;
	//设置创建的窗口的附加空间
	mainWindow.cbWndExtra = 0;
	//主窗口模块实例句柄
	mainWindow.hInstance = hGame;
	//设置窗口的图标为系统默认应用图标
	mainWindow.hIcon = LoadIcon(0, IDI_APPLICATION);
	//设置窗口的光标
	mainWindow.hCursor = LoadCursor(0, IDC_ARROW);
	//设置背景画刷
	mainWindow.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	//设置菜单名字（不晓得啥用）
	mainWindow.lpszMenuName = 0;
	//设置窗口类名
	mainWindow.lpszClassName = L"MainWindow";

	//注册窗口
	if (!RegisterClass(&mainWindow))
	{
		MessageBox(0, L"RegisterClass Failed.", 0, 0);
		return;
	}
	//创建窗口
	hWindow = CreateWindow(L"MainWindow", name.c_str(),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, hGame, 0);
	if (!hWindow)
	{
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		return;
	}

	//显示窗口
	::ShowWindow(hWindow, SW_SHOW);
	//更新窗口
	UpdateWindow(hWindow);
}

//窗口的消息处理回调函数
LRESULT Window::MessageProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//设备内容句柄
	

	PAINTSTRUCT ps;

	//根据收到的不同消息进行处理
	switch (msg)
	{
		//窗口创建的时候
	case WM_PAINT:
		HDC hdc;
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 300, 400, L"Hello World", 11);
		EndPaint(hwnd, &ps);
		return 0;

	//收到销毁窗口的消息，则退出程序
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	//关闭窗口的时候，创建一个消息盒子 
	case WM_CLOSE:
		DestroyWindow(hwnd);

	default:
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}
