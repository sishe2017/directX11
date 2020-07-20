#include "Window.h"

//���ڻص�����ָ��
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
	//�ص�ָ��ָ������
	cbPtr = this;
}

Window::~Window()
{
}

//���ô��ڳߴ�
void Window::SetSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void Window::ShowWindow()
{
	WNDCLASS mainWindow;
	//��ˮƽ���ߴ�ֱ�������仯��ʱ�����»�����������
	mainWindow.style = CS_HREDRAW | CS_VREDRAW;
	//���ô��ڻص�����
	mainWindow.lpfnWndProc = WindowCallBack;
	//���ø���ĸ��ӿռ�
	mainWindow.cbClsExtra = 0;
	//���ô����Ĵ��ڵĸ��ӿռ�
	mainWindow.cbWndExtra = 0;
	//������ģ��ʵ�����
	mainWindow.hInstance = hGame;
	//���ô��ڵ�ͼ��ΪϵͳĬ��Ӧ��ͼ��
	mainWindow.hIcon = LoadIcon(0, IDI_APPLICATION);
	//���ô��ڵĹ��
	mainWindow.hCursor = LoadCursor(0, IDC_ARROW);
	//���ñ�����ˢ
	mainWindow.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	//���ò˵����֣�������ɶ�ã�
	mainWindow.lpszMenuName = 0;
	//���ô�������
	mainWindow.lpszClassName = L"MainWindow";

	//ע�ᴰ��
	if (!RegisterClass(&mainWindow))
	{
		MessageBox(0, L"RegisterClass Failed.", 0, 0);
		return;
	}
	//��������
	hWindow = CreateWindow(L"MainWindow", name.c_str(),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, hGame, 0);
	if (!hWindow)
	{
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		return;
	}

	//��ʾ����
	::ShowWindow(hWindow, SW_SHOW);
	//���´���
	UpdateWindow(hWindow);
}

//���ڵ���Ϣ����ص�����
LRESULT Window::MessageProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//�豸���ݾ��
	

	PAINTSTRUCT ps;

	//�����յ��Ĳ�ͬ��Ϣ���д���
	switch (msg)
	{
		//���ڴ�����ʱ��
	case WM_PAINT:
		HDC hdc;
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 300, 400, L"Hello World", 11);
		EndPaint(hwnd, &ps);
		return 0;

	//�յ����ٴ��ڵ���Ϣ�����˳�����
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	//�رմ��ڵ�ʱ�򣬴���һ����Ϣ���� 
	case WM_CLOSE:
		DestroyWindow(hwnd);

	default:
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}
