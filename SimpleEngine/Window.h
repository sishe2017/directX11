#pragma once
#include <string>
#include <Windows.h>
#include <functional>

//Windows������
class Window
{
	friend LRESULT CALLBACK WindowCallBack(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	Window(HINSTANCE hGame, std::wstring name);
	~Window();
	
	//���ô��ڳߴ�
	void SetSize(int width, int height);
	//��ʾ����
	void ShowWindow();

private:
	//����ʵ�����
	HINSTANCE hGame;
	//���ھ��
	HWND hWindow;
	//��������
	std::wstring name;
	//���ڿ��
	int width;
	//���ڸ߶�
	int height;
	

	//���ڵ���Ϣ����ص�����
	LRESULT MessageProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

