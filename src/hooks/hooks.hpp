#pragma once

namespace Hook
{
	namespace Winmm
	{
		extern DWORD _timeGetTime_val;
		DWORD WINAPI timeGetTime(VOID);
	}

	namespace Kernel32
	{
		DWORD WINAPI SleepEx(DWORD dwMilliseconds, BOOL bAlertable);

		extern DWORD _GetTickCount_val;
		DWORD WINAPI GetTickCount(VOID);

		extern ULONGLONG _GetTickCount64_val;
		ULONGLONG WINAPI GetTickCount64(VOID);

		extern LARGE_INTEGER _QueryPerformanceCounter_val, _QueryPerformanceCounter_temp;
		BOOL WINAPI QueryPerformanceCounter(PLARGE_INTEGER lpPerformanceCount);
	}
}