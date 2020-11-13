#include <Windows.h>
#include "il2cpp-init.h"
#include "CPPBeDumb.h"
#include "inject.h"

BOOL __stdcall DllMain(HMODULE hIns, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
	{
		//DisableThreadLibraryCalls(hIns);
		init_il2cpp();
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ThreadMain, hIns, 0, 0);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ThreadWrite, hIns, 0, 0);
	}
	break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;
}