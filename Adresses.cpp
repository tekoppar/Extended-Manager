#include "pch-il2cpp.h"

#include <windows.h>
#include <tlhelp32.h>
#include <string>

#include "Adresses.h"

unsigned long long Assembly_BaseAddr = 0x0;
unsigned long long UnityPlayer_BaseAddress = 0x0;

bool GetAddressOffset(HANDLE hProcess, uintptr_t& dynamicPtrBaseAddr, std::vector<unsigned int> offsets) {
	for (unsigned int i = 0; i < offsets.size(); ++i)
	{
		ReadProcessMemory(hProcess, (BYTE*)dynamicPtrBaseAddr, &dynamicPtrBaseAddr, sizeof(dynamicPtrBaseAddr), 0);
		dynamicPtrBaseAddr += offsets[i];
		if (!dynamicPtrBaseAddr || !&dynamicPtrBaseAddr)
			return NULL;
	}
	return true;
}

bool IsProcessRunning(DWORD processID)
{
    if (HANDLE process = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, processID))
    {
        DWORD exitCodeOut;
        // GetExitCodeProcess returns zero on failure
        if (GetExitCodeProcess(process, &exitCodeOut) != 0)
        {
            // Return if the process is still active
            return exitCodeOut == STILL_ACTIVE;
        }
    }
    return false;
}

HANDLE FindProcessHandle(std::string& processName)
{
    PROCESSENTRY32 processInfo;
    processInfo.dwSize = sizeof(processInfo);

    HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (processesSnapshot == INVALID_HANDLE_VALUE)
        return 0;

    Process32First(processesSnapshot, &processInfo);
    if (!strcmp(processName.data(), processInfo.szExeFile))
    {
        CloseHandle(processesSnapshot);
        return processesSnapshot;
    }

    while (Process32Next(processesSnapshot, &processInfo))
    {
        if (!strcmp(processName.data(), processInfo.szExeFile))
        {
            CloseHandle(processesSnapshot);
            return processesSnapshot;
        }
    }

    CloseHandle(processesSnapshot);
    return 0;
}

DWORD FindProcessId(std::string& processName)
{
    PROCESSENTRY32 processInfo;
    processInfo.dwSize = sizeof(processInfo);

    HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (processesSnapshot == INVALID_HANDLE_VALUE)
        return 0;

    Process32First(processesSnapshot, &processInfo);
    if (!strcmp(processName.data(), processInfo.szExeFile))
    {
        CloseHandle(processesSnapshot);
        return processInfo.th32ProcessID;
    }

    while (Process32Next(processesSnapshot, &processInfo))
    {
        if (!strcmp(processName.data(), processInfo.szExeFile))
        {
            CloseHandle(processesSnapshot);
            return processInfo.th32ProcessID;
        }
    }

    CloseHandle(processesSnapshot);
    return 0;
}