#include "Window.h"
#include <string>
#include <windowsx.h>

using namespace std;

Window::Window(int width, int height, std::wstring caption):
	width(width),
	height(height),
	hInstance(GetModuleHandle(nullptr))
{
	//ע�ᴰ����
	//��������
	wstring wndClassName = L"GameWindow";
	//������
	WNDCLASSEX wc;
	//�������С
	wc.cbSize = sizeof(WNDCLASSEX);
	//���
	wc.style = CS_OWNDC;
	//���ڻص�
	wc.lpfnWndProc = FirstWndProc;
	//����Ҫ����ռ䣬����Ϊ0
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	//������������
	wc.hInstance = hInstance;
	//���涼����Ҫ��ֱ����nullptr
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = wndClassName.c_str();
	wc.hIconSm = nullptr;
	//ע�ᴰ����
	RegisterClassEx(&wc);
	//�������ڿͻ����Ĵ�С�ߴ�Ϊ����Ŀ�Ⱥ͸߶�
	RECT rect;
	rect.left = 100;
	rect.right = width + rect.left;
	rect.top = 100;
	rect.bottom = height + rect.top;
	if (AdjustWindowRect(&rect, WS_OVERLAPPED, false) == 0)
		throw exception();
	//��������
	hwnd = CreateWindowEx(0,
		wndClassName.c_str(),
		caption.c_str(),
		WS_OVERLAPPEDWINDOW,
		200, 200, rect.right - rect.left, rect.bottom - rect.top,
		nullptr, nullptr,
		hInstance, this);
	//��ʾ����
	::ShowWindow(hwnd, SW_SHOW);
}

Window::~Window()
{
}

//����Ĵ��ڵĻص��¼����ڴ��ڴ������֮ǰ��ʹ��Ĭ�ϴ���
LRESULT Window::FirstWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//���ڴ�����ɵ���Ϣ������ʱ��
	if (msg == WM_NCCREATE)
	{
		//ȡ��thisָ��
		auto pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		auto pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		//��thisָ�����õ�USERDATA��
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		//�����µĴ��ڻص�����
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(Window::FollowWndProc));
	}

	//���ڴ�����֮ǰ����ʹ��Ĭ�ϴ���
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

//�����Ĵ��ڵĻص��¼�
LRESULT Window::FollowWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//ȡ��thisָ��
	auto pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	//ʹ�ó�Ա�����Ĵ��ڻص�����
	return pWnd->WndProc(hwnd, msg, wParam, lParam);
}

//���ڻص��¼�����
LRESULT Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	//���̰��µ���Ϣ
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN: 
		Keyboard::OnKeyDown(static_cast<unsigned int>(wParam));
		return 0;
	//���̵������Ϣ
	case WM_KEYUP:
	case WM_SYSKEYUP:
		Keyboard::OnKeyUp(static_cast<unsigned int>(wParam));
		return 0;

	//���������µ���Ϣ
	case WM_LBUTTONDOWN:
		Mouse::OnKeyDown(0);
		return 0;
	//����Ҽ����µ���Ϣ
	case WM_RBUTTONDOWN:
		Mouse::OnKeyDown(1);
		return 0;
	//�������������Ϣ
	case WM_LBUTTONUP:
		Mouse::OnKeyUp(0);
		return 0;
	//����Ҽ��������Ϣ
	case WM_RBUTTONUP:
		Mouse::OnKeyUp(1);
		return 0;
	//����ƶ�����Ϣ
	case WM_MOUSEMOVE:
		Mouse::OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;

	//���ڹرյ���Ϣ
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;

	default:
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}


