#include <Windows.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <string_view>
#include <thread>
#include <sstream>
#include <xstring>
#include <set>
#include <locale>
#include <codecvt>

#include "Adresses.h"
#include "detours.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Transform.h"
#include "SystemString.h"
#include "HString.h"
#include "MessageClass.h"
#include "AkLogger.h"
#include "GameObject.h"
#include "Object.h"
#include "Component.h"
#include "GetClasses.h"
#include "StringUtils.h"
#include "inject.h" 

namespace Moon3 {
#include "SystemString3.h"
}

/*namespace Moon {
#include "SystemString2.h"
}*/

std::vector<Message> ManagerMessages;
std::vector<InvisibleCheckpoint> InvisibleCheckpoints;

FrameStep frameStep;
bool loopBool = true;
bool IsUsingMessages = false;
bool copySein = false;

std::thread pipeThread;
HANDLE fileHandle;
DWORD pid;
HANDLE hProcess;

typedef void(__thiscall* CClassFunction_t)(void* __this);
CClassFunction_t Real_CClassFunction;

typedef Moon3::Moon_MoonString_o*(__thiscall* tIl2CppString)(const char* str);
tIl2CppString RealIl2cpp_string_new_wrapper;

typedef void(__thiscall* tGameControllerUpdate)(void* __this);
tGameControllerUpdate Real_GameControllerUpdate;

//MoonString* stringCreator;

GameObject* GameObject::gameObject = new GameObject(); // 0x0
Object objectM = Object();

Moon3::Moon_MoonString_o* string_new(const char* str)
{
	return RealIl2cpp_string_new_wrapper(str);
}

void __fastcall Mine_CClassFunction(void* __this, int edx)
{
	IsUsingMessages = true;
	for (auto& message : ManagerMessages) {
		switch (message.Type) {

		case MessageType::GameCompletion:
		{
			tGetGameCompletion oGetGameCompletion = tGetGameCompletion(Assembly_BaseAddr + 0x3e45d0);
			GameWorld* pGameWorld = GetGameWorld(hProcess);
			if (pGameWorld != nullptr && oGetGameCompletion != nullptr)
				gameCompletionHooked = oGetGameCompletion(pGameWorld);
		}
		break;

		case MessageType::CreateCheckpoint:
		{
			tCreateCheckpoint oCreateCheckpoint = tCreateCheckpoint(Assembly_BaseAddr + 0x997230);
			if (oCreateCheckpoint != nullptr) {
				GameController* pGameController = GetGameController(hProcess);

				if (pGameController != nullptr)
					oCreateCheckpoint(pGameController);
			}
		}
		break;

		case MessageType::CreateObject:
		{
			copySein = true;
		}
		break;

		case MessageType::StopRecorder:
		{
			uintptr_t GhostManagerBaseAdress = UnityPlayer_BaseAddress + 0x445EB38;
			//GetAddressOffset(hProcess, InvisibleCheckpointBaseAdress, { 0x60, 0x30, 0xE8, 0xE0, 0x60, 0x0 });
			GhostRecorder* GhostRecorder;
			if (GhostManagerBaseAdress != NULL)
				BaseGhostManager = (GhostManager*)(GhostManagerBaseAdress);

			GhostRecorder = GhostManager::GetRecorder();
			if (GhostRecorder != nullptr) {
				GhostRecorder->StopRecorder();
			}

		}
		break;

		case MessageType::WriteRecorder:
		{
			uintptr_t GhostManagerBaseAdress = UnityPlayer_BaseAddress + 0x445EB38;
			//GetAddressOffset(hProcess, InvisibleCheckpointBaseAdress, { 0x60, 0x30, 0xE8, 0xE0, 0x60, 0x0 });
			GhostRecorder* GhostRecorder;
			if (GhostManagerBaseAdress != NULL)
				BaseGhostManager = (GhostManager*)(GhostManagerBaseAdress);

			GhostRecorder = GhostManager::GetRecorder();
			if (GhostRecorder != nullptr) {
				GhostRecorder->WriteToFile();
			}

		}
		break;

		case MessageType::GhostPlayerRun:
		{
			const char* qD = "swamp1";
			Moon3::Moon_MoonString_o* qDir = string_new(qD);
			HString* ghostPathGet = GhostManager::GetRaceDirectory(qDir);
			bool itworked = false;
			//std::string ghostPath = getexepath();
			//ReplaceS(ghostPath, "oriwotw.exe", "oriwotw_Data\\output\\ghosts\\local.ghost");
			//std::string ghostContent = readFile(ghostPath);

			/*uintptr_t GhostManagerBaseAdress = UnityPlayer_BaseAddress + 0x445EB38;
			if (GhostManagerBaseAdress != NULL)
				BaseGhostManager = (GhostManager*)(GhostManagerBaseAdress);*/
			/*const char* gP = ghostContent.data();
			Moon3::Moon_MoonString_o gPath = string_new(gP);
			const char* gPN = "tekoppar";
			Moon3::Moon_MoonString_o gName = string_new(gPN);
			//GhostPlayer* ghostPlayer = BaseGhostManager->createGhost(gPath);
			GhostPlayer* ghostPlayer = BaseGhostManager->createGhost(gName, gPath);

			if (ghostPlayer != nullptr)
				ghostPlayer->Run();*/
		}
			break;

		case MessageType::EndThread:
		{
			loopBool = false;
		}
		break;

		case MessageType::GetQuestByName:
		{
			BaseQuestsController = GetQuestsController(hProcess);

			if (BaseQuestsController != nullptr) {
				const char* qN = "Fallen Friend";
				Moon3::Moon_MoonString_o* qName = string_new(qN);
				HString* qName1 = new HString(L"Fallen Friend", 1);
				Quest quest1 = BaseQuestsController->GetQuestByName(qName);
				bool works = true;
			}
		}
		break;

		case MessageType::FrameStep:
		{
			frameStep.State = FrameStepping::FrameSteppingEnabled;
		}
		break;
		}
	}
	ManagerMessages.clear();
	IsUsingMessages = false;

	Real_CClassFunction(__this);
}

typedef void(__thiscall* tMoonDriverSystem)(void* __this);
tMoonDriverSystem Real_MoonDriverSystem;

void __fastcall Mine_MoonDriverSystem(void* __this, int edx)
{
	if (copySein) {
		copySein = false;
		SeinCharacter* sein = GetSeinCharacter(hProcess);
		//auto test = Object::FindObjectOfType(*sein);
		/*if (BaseInvisibleCheckpoint != NULL) {
			Vector3 position = Vector3(-578.4630737f, -4312.749023f);
			Quaternion quat = Quaternion(0.0f, 0.0f, 0.0f, 0.0f);
			auto newSein = Object::Instantiate(reinterpret_cast<Object*>(BaseInvisibleCheckpoint), position, quat);
			if (newSein) {
				InvisibleCheckpoint* newC = reinterpret_cast<InvisibleCheckpoint*>(newSein);
				//String* gTag = new String(L"hej", 0);
				if (newC) {
					//String* tag = newC->get_tag();
					UnityEngineRect newBounds = newC->CalculateBounds();
					std::string testff = "hej";
					newC->set_tag(testff);
					bool f111 = true;
					String* tagC = newC->get_tag();
				}
			}
		}*/
	}

	Real_MoonDriverSystem(__this);
}

void __fastcall My_GameControllerUpdate(void* __this, int edx)
{
	if (frameStep.State == FrameStepping::FrameSteppingEnabled)
	{
		if (frameStep.ShouldFrameStep == true) {
			Real_GameControllerUpdate(__this);
			frameStep.ShouldFrameStep = false;
		}
	}
	if (frameStep.State == FrameStepping::IsAutoFrameStepping) {
		Real_GameControllerUpdate(__this);
	}
	if (frameStep.State == FrameStepping::FrameSteppingDisabled) {
		Real_GameControllerUpdate(__this);
	}
}

void ReadString(char* output) {
	ULONG read = 0;
	int index = 0;
	do {
		ReadFile(fileHandle, output + index++, 1, &read, NULL);
	} while (read > 0 && *(output + index - 1) != 0 && fileHandle);
}

DWORD WINAPI ThreadMain(HMODULE hIns)
{
	pid = GetCurrentProcessId();
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, 1, pid);
	
	//get dll base adress
	Assembly_BaseAddr = (unsigned long long)GetModuleHandleA("GameAssembly.dll");
	UnityPlayer_BaseAddress = (unsigned long long)GetModuleHandleA("UnityPlayer.dll");

	//initialize functions
	tCreateCheckpoint oCreateCheckpoint = tCreateCheckpoint(Assembly_BaseAddr + 0x7DE210);
	tGetGameCompletion oGetGameCompletion = tGetGameCompletion(Assembly_BaseAddr + 0x3e45d0);


	void* pGameWorld2 = (void**)(Assembly_BaseAddr + 71715792);

	GameWorld* pGameWorld = GetGameWorld(hProcess);
	GameController* pGameController = GetGameController(hProcess);

	std::string returnMessage = "";
	std::vector<std::string> messages;

	//initalize detours
	Real_CClassFunction = CClassFunction_t(Assembly_BaseAddr + 0x994520);
	Real_MoonDriverSystem = tMoonDriverSystem(Assembly_BaseAddr + 0xE463C0);
	RealIl2cpp_string_new_wrapper = tIl2CppString(Assembly_BaseAddr + 0x263B50);
	//oSystem_String__ToCharArray = tSystem_String__ToCharArray(Assembly_BaseAddr + 0x1CD17A0);
	Real_GameControllerUpdate = tGameControllerUpdate(UnityPlayer_BaseAddress + 0x5f0350); //0x994040 gc -  0xA77FA0 sein 

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)Real_CClassFunction, Mine_CClassFunction);
	DetourAttach(&(PVOID&)Real_MoonDriverSystem, Mine_MoonDriverSystem);
	DetourAttach(&(PVOID&)RealIl2cpp_string_new_wrapper, string_new);
	DetourAttach(&(PVOID&)Real_GameControllerUpdate, My_GameControllerUpdate);
	LONG lError = DetourTransactionCommit();


	//find base invis to use for cloning
	uintptr_t InvisibleCheckpointBaseAdress = UnityPlayer_BaseAddress + 0x0148FDA0;
	GetAddressOffset(hProcess, InvisibleCheckpointBaseAdress, { 0x60, 0x30, 0xE8, 0xE0, 0x60, 0x0 });
	if (InvisibleCheckpointBaseAdress != NULL)
		BaseInvisibleCheckpoint = (InvisibleCheckpoint*)(InvisibleCheckpointBaseAdress);

	uintptr_t* GhostManagerBaseAdress = (uintptr_t*)(Assembly_BaseAddr + 0x445EB38);
	uintptr_t test123 = *GhostManagerBaseAdress;
	GhostRecorder* GhostRecorder;
	if (GhostManagerBaseAdress != NULL)
		BaseGhostManager = (GhostManager*)(test123);

	GhostRecorder = GhostManager::GetRecorder();
	
	fileHandle = CreateFileA("\\\\.\\pipe\\wotw-manager-pipe", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

	while (loopBool) {
		char* buffer = new char[100];
		memset(buffer, 0, 100);
		ReadString(buffer);

		if ((buffer != NULL) && (buffer[0] == '\0')) {

		}
		else {
			std::string message(buffer);
			returnMessage = "";

			if (message.find("CALL") != std::string::npos) {
				messages.clear();

				if (message.find("||") != std::string::npos) {
					messages = SplitS(message, '||');
				}
				else {
					messages.push_back(message);
				}

				if (IsUsingMessages == false) {
					for (auto& message : messages) {
						ReplaceS(message, "CALL", "");
						if (message != "") {
							Message newMessage;
							newMessage.Type = MessageType(std::stoi(message));
							
							if (newMessage.Type == MessageType::FrameStep) {
								frameStep.ShouldFrameStep = true;
							}
							if (newMessage.Type == MessageType::FrameStepStop) {
								frameStep.State = FrameStepping::FrameSteppingDisabled;
								frameStep.ShouldFrameStep = false;
							}

							ManagerMessages.push_back(newMessage);
						}
					}
				}

				returnMessage += "GAMECOMPLETION:" + std::to_string(gameCompletionHooked * 100) + "||";
			}

			if (returnMessage.length() > 0) {
				returnMessage += "\r\n";
				WriteFile(fileHandle, returnMessage.c_str(), (DWORD)strlen(returnMessage.c_str()), nullptr, 0);
			}
			else {
				const char* msg = "\r\n";
				WriteFile(fileHandle, msg, (DWORD)strlen(msg), nullptr, 0);
			}
		}
	}
	frameStep.State = FrameStepping::FrameSteppingDisabled;
	frameStep.ShouldFrameStep = false;

	//sleep to let game finish and then dettach all the detours
	Sleep(100);
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&(PVOID&)Real_CClassFunction, Mine_CClassFunction);
	DetourDetach(&(PVOID&)Real_MoonDriverSystem, Mine_MoonDriverSystem);
	DetourDetach(&(PVOID&)RealIl2cpp_string_new_wrapper, string_new);
	DetourDetach(&(PVOID&)Real_GameControllerUpdate, My_GameControllerUpdate);
	DetourTransactionCommit();
	ManagerMessages.clear();

	FreeLibraryAndExitThread(hIns, 0);
	return 0;
}

BOOL __stdcall DllMain(HMODULE hIns, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
	{
		//DisableThreadLibraryCalls(hIns);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ThreadMain, hIns, 0, 0);
	}
	break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;
}