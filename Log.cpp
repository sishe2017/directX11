#include "Log.h"

//��ӡ(������)
void DebugLog(std::wstring str)
{
	OutputDebugString((str + L"\n").c_str());
}