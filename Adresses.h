#pragma once

#include <Windows.h>
#include <vector>

extern unsigned long long Assembly_BaseAddr;
extern unsigned long long UnityPlayer_BaseAddress;
extern bool GetAddressOffset(HANDLE hProcess, uintptr_t& dynamicPtrBaseAddr, std::vector<unsigned int> offsets);