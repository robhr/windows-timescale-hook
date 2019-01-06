#pragma once

namespace IAT
{
	namespace Winmm
	{
		extern DWORD(WINAPI *timeGetTime)(VOID);
	}

	namespace Kernel32
	{
		extern DWORD(WINAPI *SleepEx)(DWORD dwMilliseconds, BOOL bAlertable);
		extern DWORD(WINAPI *GetTickCount)(VOID);
		extern ULONGLONG(WINAPI *GetTickCount64)(VOID);
		extern BOOL(WINAPI *QueryPerformanceCounter)(PLARGE_INTEGER lpPerformanceCount);
	}
}