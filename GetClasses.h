#pragma once

#include "Adresses.h"
#include "GhostManager.h"
#include "RaceSystem.h"
#include "MoonDriverSystem.h"
#include "MessageControllerB.h"
#include "QuestsController.h"
#include "InvisibleCheckpoint.h"
#include "SeinCharacter.h"
#include "GameWorld.h"
#include "GameController.h"
#include "GameUI.h"
#include "Object.h"
#include "GameObject.h"

GameUI* BaseGameUI;
InvisibleCheckpoint* BaseInvisibleCheckpoint;
GhostManager* BaseGhostManager;
RaceSystem* BaseRaceSystem;
QuestsController* BaseQuestsController;

SeinCharacter* GetSeinCharacter(HANDLE hProcess) {
	if (hProcess != NULL) {
		uintptr_t dynamicPtrBaseAddr = Assembly_BaseAddr + 0x0449A608;

		if (!dynamicPtrBaseAddr || !&dynamicPtrBaseAddr)
			return NULL;

		GetAddressOffset(hProcess, dynamicPtrBaseAddr, { 0xAD0, 0x48, 0xB8, 0x60, 0x18, 0xF0, 0x0 });

		if (!dynamicPtrBaseAddr || !&dynamicPtrBaseAddr)
			return NULL;

		return (SeinCharacter*)(dynamicPtrBaseAddr);
	}
	else {
		return NULL;
	}
};

MoonDriverSystem* GetMoonDriverSystem(HANDLE hProcess) {
	if (hProcess != NULL) {
		uintptr_t dynamicPtrBaseAddr = Assembly_BaseAddr + 0x446F628;

		if (!dynamicPtrBaseAddr || !&dynamicPtrBaseAddr)
			return NULL;

		//GetAddressOffset(hProcess, dynamicPtrBaseAddr, { 0xAD0, 0x48, 0xB8, 0x60, 0x18, 0xF0, 0x0 });

		if (!dynamicPtrBaseAddr || !&dynamicPtrBaseAddr)
			return NULL;

		return (MoonDriverSystem*)(dynamicPtrBaseAddr);
	}
	else {
		return NULL;
	}
};

GameWorld* GetGameWorld(HANDLE hProcess) {
	if (hProcess != NULL) {
		uintptr_t dynamicPtrBaseAddr = Assembly_BaseAddr + 0x0442B648;
		std::vector<unsigned int> offsets = { 0x68, 0x98, 0x88, 0xB8, 0xB8, 0x0, 0x0 };

		uintptr_t addr = dynamicPtrBaseAddr;
		for (unsigned int i = 0; i < offsets.size(); ++i)
		{
			ReadProcessMemory(hProcess, (BYTE*)addr, &addr, sizeof(addr), 0);
			addr += offsets[i];
		}
		return (GameWorld*)(addr);
	}
	else {
		return NULL;
	}
};

GameController* GetGameController(HANDLE hProcess) {
	if (hProcess != NULL) {
		uintptr_t dynamicPtrBaseAddr = Assembly_BaseAddr + 0x04456A90;
		std::vector<unsigned int> offsets = { 0x68, 0xB8, 0x10, 0x68, 0xF8, 0x70, 0x640 };

		uintptr_t addr = dynamicPtrBaseAddr;
		for (unsigned int i = 0; i < offsets.size(); ++i)
		{
			ReadProcessMemory(hProcess, (BYTE*)addr, &addr, sizeof(addr), 0);
			addr += offsets[i];
		}
		return (GameController*)(addr);
	}
	else {
		return NULL;
	}
}

RaceSystem* GetRaceSystem(HANDLE hProcess)
{
	if (hProcess != NULL) {
		uintptr_t* RaceSystemBaseAdress = (uintptr_t*)(Assembly_BaseAddr + 0x441EF00);
		uintptr_t RacePtr = *RaceSystemBaseAdress;
		return (RaceSystem*)(RacePtr);
	}
	else {
		return NULL;
	}
}

QuestsController* GetQuestsController(HANDLE hProcess)
{
	if (hProcess != NULL) {
		uintptr_t dynamicPtrBaseAddr = Assembly_BaseAddr + 0x440CBA0;

		if (!dynamicPtrBaseAddr || !&dynamicPtrBaseAddr)
			return NULL;

		GetAddressOffset(hProcess, dynamicPtrBaseAddr, { 0x98, 0x8, 0x68, 0x40, 0xB8, 0x0, 0x0 });

		if (!dynamicPtrBaseAddr || !&dynamicPtrBaseAddr)
			return NULL;

		return (QuestsController*)(dynamicPtrBaseAddr);
	}
	else {
		return NULL;
	}
}

MessageControllerB* GetMessageController(HANDLE hProcess) {

	uintptr_t* GameUIBaseAdress = (uintptr_t*)(Assembly_BaseAddr + 0x4464828);
	uintptr_t GameUIT = *GameUIBaseAdress;
	if (GameUIBaseAdress != NULL)
		BaseGameUI = (GameUI*)(GameUIT);

	if (BaseGameUI != nullptr) {
		return (MessageControllerB*)(BaseGameUI->m_messageController);
	}

	return NULL;
}