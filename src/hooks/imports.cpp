#include "pch.hpp"
#include ".\hooks\imports.hpp"

namespace IAT
{
	namespace Winmm
	{
		DWORD(WINAPI *timeGetTime)(VOID);
	}

	namespace Kernel32
	{
		DWORD(WINAPI *SleepEx)(DWORD dwMilliseconds, BOOL bAlertable);
		DWORD(WINAPI *GetTickCount)(VOID);
		ULONGLONG(WINAPI *GetTickCount64)(VOID);
		BOOL(WINAPI *QueryPerformanceCounter)(PLARGE_INTEGER lpPerformanceCount);
	}
}