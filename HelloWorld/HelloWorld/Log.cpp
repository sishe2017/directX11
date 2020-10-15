#include "Log.h"

//´òÓ¡(µ÷ÊÔÓÃ)
void DebugLog(std::wstring str)
{
	OutputDebugString((str + L"\n").c_str());
}