#pragma once

#include <Windows.h>
#include <vector>

#ifndef _ADRESSES_H
#define _ADRESSES_H

extern unsigned long long Assembly_BaseAddr;
extern unsigned long long UnityPlayer_BaseAddress;
extern bool GetAddressOffset(HANDLE hProcess, uintptr_t& dynamicPtrBaseAddr, std::vector<unsigned int> offsets);
bool IsProcessRunning(DWORD processID);
DWORD FindProcessId(std::string& processName);
HANDLE FindProcessHandle(std::string& processName);

#endif