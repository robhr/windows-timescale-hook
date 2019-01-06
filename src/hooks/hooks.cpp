#include "pch.hpp"
#include ".\hooks\hooks.hpp"
#include ".\hooks\imports.hpp"

namespace Hook
{
	namespace Winmm
	{
		DWORD _timeGetTime_val;
		DWORD WINAPI timeGetTime(VOID)
		{
			return (DWORD)(fRateModifier * (IAT::Winmm::timeGetTime() - _timeGetTime_val)) + _timeGetTime_val;
		}
	}

	namespace Kernel32
	{
		DWORD WINAPI SleepEx(DWORD dwMilliseconds, BOOL bAlertable)
		{
			return IAT::Kernel32::SleepEx((DWORD)(dwMilliseconds / fRateModifier), bAlertable);
		}

		DWORD _GetTickCount_val;
		DWORD WINAPI GetTickCount(VOID)
		{
			return (DWORD)(fRateModifier * (IAT::Kernel32::GetTickCount() - _GetTickCount_val)) + _GetTickCount_val;
		}

		ULONGLONG _GetTickCount64_val;
		ULONGLONG WINAPI GetTickCount64(VOID)
		{
			return (ULONGLONG)(fRateModifier * (IAT::Kernel32::GetTickCount() - _GetTickCount64_val)) + _GetTickCount64_val;
		}

		LARGE_INTEGER _QueryPerformanceCounter_val, _QueryPerformanceCounter_temp;
		BOOL WINAPI QueryPerformanceCounter(PLARGE_INTEGER lpPerformanceCount)
		{
			IAT::Kernel32::QueryPerformanceCounter(&_QueryPerformanceCounter_temp);
			lpPerformanceCount->QuadPart = (LONGLONG)(fRateModifier * (_QueryPerformanceCounter_temp.QuadPart - _QueryPerformanceCounter_val.QuadPart)) + _QueryPerformanceCounter_val.QuadPart;
			return TRUE;
		}
	}
}