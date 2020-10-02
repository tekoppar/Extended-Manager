#pragma once

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
#include "ScenariosRecorder.h"
#include "FindObjectsWrapper.h"

Moon::GameUI* BaseGameUI;
Moon::InvisibleCheckpoint* BaseInvisibleCheckpoint;
Moon::RaceSystem* BaseRaceSystem;
Moon::QuestsController* BaseQuestsController;
Moon::ScenariosRecorder* BaseScenarioRecorder;
Moon::GhostRecorder* BaseGhostRecorder;

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

Moon::MoonDriverSystem* GetMoonDriverSystem(HANDLE hProcess) {
	if (hProcess != NULL) {
		uintptr_t dynamicPtrBaseAddr = Assembly_BaseAddr + 0x446F628;

		if (!dynamicPtrBaseAddr || !&dynamicPtrBaseAddr)
			return NULL;

		//GetAddressOffset(hProcess, dynamicPtrBaseAddr, { 0xAD0, 0x48, 0xB8, 0x60, 0x18, 0xF0, 0x0 });

		if (!dynamicPtrBaseAddr || !&dynamicPtrBaseAddr)
			return NULL;

		return (Moon::MoonDriverSystem*)(dynamicPtrBaseAddr);
	}
	else {
		return NULL;
	}
};

Moon::GameWorld* GetGameWorld(HANDLE hProcess) {
	if (hProcess != NULL) {
		uintptr_t dynamicPtrBaseAddr = Assembly_BaseAddr + 0x0442B648;
		std::vector<unsigned int> offsets = { 0x68, 0x98, 0x88, 0xB8, 0xB8, 0x0, 0x0 };

		uintptr_t addr = dynamicPtrBaseAddr;
		for (unsigned int i = 0; i < offsets.size(); ++i)
		{
			ReadProcessMemory(hProcess, (BYTE*)addr, &addr, sizeof(addr), 0);
			addr += offsets[i];
		}
		return (Moon::GameWorld*)(addr);
	}
	else {
		return NULL;
	}
};

Moon::GameController* GetGameController(HANDLE hProcess) {
	if (hProcess != NULL) {
		uintptr_t dynamicPtrBaseAddr = Assembly_BaseAddr + 0x04456A90;
		std::vector<unsigned int> offsets = { 0x68, 0xB8, 0x10, 0x68, 0xF8, 0x70, 0x640 };

		uintptr_t addr = dynamicPtrBaseAddr;
		for (unsigned int i = 0; i < offsets.size(); ++i)
		{
			ReadProcessMemory(hProcess, (BYTE*)addr, &addr, sizeof(addr), 0);
			addr += offsets[i];
		}
		return (Moon::GameController*)(addr);
	}
	else {
		return NULL;
	}
}

Moon::RaceSystem* GetRaceSystem(HANDLE hProcess)
{
	if (hProcess != NULL) {
		uintptr_t* RaceSystemBaseAdress = (uintptr_t*)(Assembly_BaseAddr + 0x441EF00);
		uintptr_t RacePtr = *RaceSystemBaseAdress;
		return (Moon::RaceSystem*)(RacePtr);
	}
	else {
		return NULL;
	}
}

Moon::QuestsController* GetQuestsController(HANDLE hProcess)
{
	if (hProcess != NULL) {
		uintptr_t dynamicPtrBaseAddr = Assembly_BaseAddr + 0x440CBA0;

		if (!dynamicPtrBaseAddr || !&dynamicPtrBaseAddr)
			return NULL;

		GetAddressOffset(hProcess, dynamicPtrBaseAddr, { 0x98, 0x8, 0x68, 0x40, 0xB8, 0x0, 0x0 });

		if (!dynamicPtrBaseAddr || !&dynamicPtrBaseAddr)
			return NULL;

		return (Moon::QuestsController*)(dynamicPtrBaseAddr);
	}
	else {
		return NULL;
	}
}

Moon::MessageControllerB* GetMessageController(HANDLE hProcess) {

	uintptr_t* GameUIBaseAdress = (uintptr_t*)(Assembly_BaseAddr + 0x4464828);
	uintptr_t GameUIT = *GameUIBaseAdress;
	if (GameUIBaseAdress != NULL)
		BaseGameUI = (Moon::GameUI*)(GameUIT);

	if (BaseGameUI != nullptr) {
		return (Moon::MessageControllerB*)(BaseGameUI->m_messageController);
	}

	return NULL;
}