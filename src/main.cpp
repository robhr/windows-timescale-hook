#include "pch.hpp"
#include ".\handler\handler.hpp"

VOID WINAPI DllThread()
{
	if (Handler::Init())
	{
		Handler::Start(2.0f);
	}
}

BOOL APIENTRY DllMain(HMODULE, DWORD ul_reason_for_call, LPVOID)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)DllThread, NULL, 0, NULL);
	}

	return TRUE;
}