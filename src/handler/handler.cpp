#include "pch.hpp"
#include ".\handler\handler.hpp"
#include ".\hooks\imports.hpp"
#include ".\hooks\hooks.hpp"
#include "..\dependencies\Detours\include\detours.h"

namespace Handler
{
	BOOL Init()
	{
		HMODULE hWinmm = GetModuleHandleA("winmm.dll");
		if (hWinmm != NULL)
		{
			IAT::Winmm::timeGetTime = { reinterpret_cast<decltype(IAT::Winmm::timeGetTime)>(GetProcAddress(hWinmm, "timeGetTime")) };
		}

		HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");
		if (hKernel32 != NULL)
		{
			IAT::Kernel32::SleepEx = { reinterpret_cast<decltype(IAT::Kernel32::SleepEx)>(GetProcAddress(hKernel32, "SleepEx")) };
			IAT::Kernel32::GetTickCount = { reinterpret_cast<decltype(IAT::Kernel32::GetTickCount)>(GetProcAddress(hKernel32, "GetTickCount")) };
			IAT::Kernel32::GetTickCount64 = { reinterpret_cast<decltype(IAT::Kernel32::GetTickCount64)>(GetProcAddress(hKernel32, "GetTickCount64")) };
			IAT::Kernel32::QueryPerformanceCounter = { reinterpret_cast<decltype(IAT::Kernel32::QueryPerformanceCounter)>(GetProcAddress(hKernel32, "QueryPerformanceCounter")) };
		}

		return (hKernel32 != NULL) || (hWinmm != NULL);
	}
	
	VOID Start(float _fRateModifier = 1.0f)
	{
		fRateModifier = _fRateModifier;

		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());

		if (IAT::Winmm::timeGetTime != NULL)
		{
			Hook::Winmm::_timeGetTime_val = IAT::Winmm::timeGetTime();
			DetourAttach(&(LPVOID&)IAT::Winmm::timeGetTime, Hook::Winmm::timeGetTime);
		}

		if (IAT::Kernel32::SleepEx != NULL)
		{
			DetourAttach(&(LPVOID&)IAT::Kernel32::SleepEx, Hook::Kernel32::SleepEx);
		}

		if (IAT::Kernel32::GetTickCount != NULL)
		{
			Hook::Kernel32::_GetTickCount_val = IAT::Kernel32::GetTickCount();
			DetourAttach(&(LPVOID&)IAT::Kernel32::GetTickCount, Hook::Kernel32::GetTickCount);
		}

		if (IAT::Kernel32::GetTickCount64 != NULL)
		{
			Hook::Kernel32::_GetTickCount64_val = IAT::Kernel32::GetTickCount64();
			DetourAttach(&(LPVOID&)IAT::Kernel32::GetTickCount64, Hook::Kernel32::GetTickCount64);
		}

		if (IAT::Kernel32::QueryPerformanceCounter != NULL)
		{
			IAT::Kernel32::QueryPerformanceCounter(&Hook::Kernel32::_QueryPerformanceCounter_val);
			DetourAttach(&(LPVOID&)IAT::Kernel32::QueryPerformanceCounter, Hook::Kernel32::QueryPerformanceCounter);
		}

		DetourTransactionCommit();
	}
}
