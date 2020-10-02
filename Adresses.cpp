#include "pch-il2cpp.h"

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