#include <Windows.h>
#include <windowsx.h>
#include <string>
#include <iostream>

using namespace std;

LRESULT CALLBACK WindowsCallback(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, PSTR szCmdLine, int iCmdShow)
{
	WNDCLASS wndclass;
	//��ˮƽ���ߴ�ֱ�������仯��ʱ�����»�����������
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	//���ô��ڻص�����
	wndclass.lpfnWndProc = WindowsCallback;
	//���øô�����ĸ��ӿռ�
	wndclass.cbClsExtra = 0;
	//���ô����Ĵ��ڵĸ��ӿռ�
	wndclass.cbWndExtra = 0;
	//���ô��ڵĽ��̾��
	wndclass.hInstance = hInstance;
	//���ô��ڵ�ͼ��
	wndclass.hIcon = LoadIcon(0, IDI_APPLICATION);
	//���ô��ڵĹ��
	wndclass.hCursor = LoadCursor(0, IDC_ARROW);
	//���ô��ڱ�����ɫ
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	//���ò˵�����
	wndclass.lpszMenuName = 0;
	//���ô�������
	wndclass.lpszClassName = L"MainWindow";

	//ע�ᴰ��
	if (!RegisterClass(&wndclass))
	{
		MessageBox(0, L"RegisterClass Failed.", 0, 0);
		return 0;
	}
	//��������
	auto hWindow = CreateWindow(L"MainWindow", L"Hello World",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, 0, 0, hInstance, 0);
	if (!hWindow)
	{
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		return 0;
	}

	//��ʾ����
	::ShowWindow(hWindow, SW_SHOW);
	//���´���
	UpdateWindow(hWindow);

	//��Ϣѭ��
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		//����Ϣ������ַ�
		TranslateMessage(&msg);
		//����Ϣ���͵����ڣ�����WndProc�ص�
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
	//����ƶ�����Ϣ
	case WM_MOUSEMOVE:
		//��ȡ����x�����y����
		pos = to_wstring(x) + L" " + to_wstring(y);
		hdc = GetDC(hwnd);
		TextOut(hdc, 400, 300, pos.c_str(), pos.size());
		ReleaseDC(hwnd, hdc);
		return 0;

	//esc���˳�����
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
