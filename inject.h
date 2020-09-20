#pragma once

#include <Windows.h>
//#include "MoonString.h"
//#include "SystemString.h"
#include <string>
/*namespace Moon {
	#include "SystemString2.h"
}*/

typedef void (*tCreateCheckpoint)(void* GameController);
tCreateCheckpoint oCreateCheckpoint;

typedef float(* tGetGameCompletion)(void* GameController);
tGetGameCompletion oGetGameCompletion;

typedef Object(*tInstantiate)(Object object);
tInstantiate oInstantiate;

/*typedef Moon_MoonString_o(* tIl2CppString)(const char* str); //Moon_MoonString_o
tIl2CppString oIl2cpp_string_new_wrapper;*/

/**
 * Dll entry point.
 */
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
);