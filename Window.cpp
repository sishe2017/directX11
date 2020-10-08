#include "Window.h"
#include <string>
#include <windowsx.h>

using namespace std;

Window::Window(int width, int height, std::wstring caption):
	width(width),
	height(height),
	hInstance(GetModuleHandle(nullptr))
{
	//注册窗口类
	//窗口类名
	wstring wndClassName = L"GameWindow";
	//窗口类
	WNDCLASSEX wc;
	//窗口类大小
	wc.cbSize = sizeof(WNDCLASSEX);
	//风格
	wc.style = CS_OWNDC;
	//窗口回调
	wc.lpfnWndProc = FirstWndProc;
	//不需要额外空间，所以为0
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	//句柄主函数句柄
	wc.hInstance = hInstance;
	//后面都不需要，直接填nullptr
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = wndClassName.c_str();
	wc.hIconSm = nullptr;
	//注册窗口类
	RegisterClassEx(&wc);
	//调整窗口客户区的大小尺寸为传入的宽度和高度
	RECT rect;
	rect.left = 100;
	rect.right = width + rect.left;
	rect.top = 100;
	rect.bottom = height + rect.top;
	if (AdjustWindowRect(&rect, WS_OVERLAPPED, false) == 0)
		throw exception();
	//创建窗口
	hwnd = CreateWindowEx(0,
		wndClassName.c_str(),
		caption.c_str(),
		WS_OVERLAPPEDWINDOW,
		200, 200, rect.right - rect.left, rect.bottom - rect.top,
		nullptr, nullptr,
		hInstance, this);
	//显示窗口
	::ShowWindow(hwnd, SW_SHOW);
}

Window::~Window()
{
}

//最初的窗口的回调事件：在窗口创建完成之前都使用默认处理
LRESULT Window::FirstWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//窗口创建完成的消息到来的时候
	if (msg == WM_NCCREATE)
	{
		//取出this指针
		auto pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		auto pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		//将this指针设置到USERDATA中
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		//设置新的窗口回调函数
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(Window::FollowWndProc));
	}

	//窗口创建好之前，都使用默认处理
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

//后续的窗口的回调事件
LRESULT Window::FollowWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//取出this指针
	auto pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	//使用成员函数的窗口回调处理
	return pWnd->WndProc(hwnd, msg, wParam, lParam);
}

//窗口回调事件处理
LRESULT Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	//键盘按下的消息
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN: 
		Keyboard::OnKeyDown(static_cast<unsigned int>(wParam));
		return 0;
	//键盘弹起的消息
	case WM_KEYUP:
	case WM_SYSKEYUP:
		Keyboard::OnKeyUp(static_cast<unsigned int>(wParam));
		return 0;

	//鼠标左键按下的消息
	case WM_LBUTTONDOWN:
		Mouse::OnKeyDown(0);
		return 0;
	//鼠标右键按下的消息
	case WM_RBUTTONDOWN:
		Mouse::OnKeyDown(1);
		return 0;
	//鼠标左键弹起的消息
	case WM_LBUTTONUP:
		Mouse::OnKeyUp(0);
		return 0;
	//鼠标右键弹起的消息
	case WM_RBUTTONUP:
		Mouse::OnKeyUp(1);
		return 0;
	//鼠标移动的消息
	case WM_MOUSEMOVE:
		Mouse::OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;

	//窗口关闭的消息
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;

	default:
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}


