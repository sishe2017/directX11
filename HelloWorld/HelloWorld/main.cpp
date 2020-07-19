#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, PSTR szCmdLine, int iCmdShow)
{
	MessageBox(NULL, TEXT("Hello World"), TEXT("My first prgram"), MB_OK);
	return 0;
}