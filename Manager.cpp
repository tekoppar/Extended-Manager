#include "pch-il2cpp.h"

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
#include <typeinfo>
#include <cmath>
#include <random>
#include <functional>

#define IL2CPP true

//il2cpp generated
#include "il2cpp-appdata.h"
#include "helpers.h"

extern const LPCWSTR LOG_FILE = L"il2cpp-log.txt";

#include "CPPBeDumb.h"
#include "Manager.h"
#include "ManagerDef.h"
#include "RaceManager.h"
#include "AreaMapManager.h"
#include "GraphDrawer.h"
#include "DebugDrawer.h"

MessageManager MessagesManager;
AreaMapManager areaMapManager;
Graph graphDrawerDebug;
DebugDrawer debugDrawer;
RaceManager raceManager = RaceManager();

std::vector<Moon::InvisibleCheckpoint> InvisibleCheckpoints;
std::vector<app::GhostPlayer*> ActiveGhostPlayers;
std::vector<app::MoonAnimation*> allAnimations;

app::SeinPlayAnimationController* seinPlayAnimationController = nullptr;

app::GameObject* randotest = nullptr;
bool stopLoop1 = false;

int animationIndex = 874;
int seinRaceBowDown = 630;
int seinRaceBowDown1 = 686;
int seinRaceBowDown2 = 1033;
int seinRaceBowDown3 = 1553;
int seinSlopedWallDownTouch = 471;
int seinVerticalWallTouch = 693;
int seinRunLookingReady = 1280;
int seinBreakdanceVictory = 1609;
int framesPlayed = 0;

unsigned long long totalFrames = 0;

app::GhostCharacterAbilitiesPlugin* ghostAP;
app::GhostCharacterPlugin* ghostCP;
app::GhostStateMachinePlugin* ghostSMP;
app::GhostGenericEventsPlugin* ghostGEP;
app::GhostRecordingMetaDataPlugin* ghostMDP;
app::GhostRecorder* ghostC;
app::RaceSystem* raceSC;
app::UnityRaceTimerDisplay* raceTimerText;
app::RaceTimer* ghostRaceTimer;
app::PetrifiedOwlBossEntity* petrifiedOwlBossEntity = nullptr;
app::SeinUI* seinUI = nullptr;

app::MoonGuid* willowPowlBackgroundGUID = nullptr;
std::string ShriekData = "";

FrameStep frameStep;
bool loopBool = true;
bool IsUsingMessages = false;
bool copySein = false;

std::thread pipeThread;
HANDLE fileHandle;
DWORD pid;
HANDLE hProcess;

Moon::Object objectM = Moon::Object();

app::String* string_new(const char* str)
{
	return RealIl2cpp_string_new_wrapper(str);
}

void __fastcall Mine_CClassFunction(void* __this, int edx)
{
	totalFrames++;
	raceManager.totalFrames = totalFrames;

	if (totalFrames >= 100 && raceManager.RaceLoopAnimation == nullptr)
	{
		raceManager.SetupManager();

		if (raceManager.BaseGhostManager == nullptr)
		{
			uintptr_t GhostManagerBaseAdress = Assembly_BaseAddr + 0x0445EB38;
			GetAddressOffset(hProcess, GhostManagerBaseAdress, { 0xB8, 0x0, 0x10, 0x28, 0x0 });
			if (GhostManagerBaseAdress != NULL)
				raceManager.BaseGhostManager = (app::GhostManager*)(GhostManagerBaseAdress);

			raceManager.Sein = GetSeinCharacter(hProcess);
			raceManager.seinPlayAnimationController = seinPlayAnimationController;
		}

		app::Type* type3 = GetType("Moon", "MoonAnimation");
		app::Object_1__Array* arrA = app::Object_1_FindObjectsOfTypeAll(type3, NULL);

		for (int i = 0; i < arrA->max_length; i++)
		{
			if (arrA->vector[i] != NULL && arrA->vector[i] != nullptr)
			{
				app::MoonAnimation* tempANI = (app::MoonAnimation*)arrA->vector[i];
				if (tempANI != nullptr) {
					app::String* aniName = app::MoonAnimation_get_Name(tempANI, NULL);
					std::string aniNameS = sutil::convert_csstring(aniName);

					if (aniNameS == "oriStartRaceLoop")
					{
						raceManager.RaceLoopAnimation = tempANI;
					}
					else if (aniNameS == "oriFinishRace")
					{
						raceManager.RaceFinishAnimation = tempANI;
					}
					else if (aniNameS == "oriNewPBRace")
					{
						raceManager.RaceNewPBAnimation = tempANI;
					}
					else if (aniNameS == "oriTopScore")
					{
						raceManager.RaceTopScoreAnimation = tempANI;
					}
				}
			}
		}

		/*graphDrawerDebug.Initialize();
		Graph::Instance = &graphDrawerDebug;

		std::vector<float> debugFloatData(100);
		std::uniform_real_distribution<float> distribution(0.0f, 32.0f); //Values between 0 and 2
		std::mt19937 engine; // Mersenne twister MT19937
		engine.seed(1);
		auto generator = std::bind(distribution, engine);
		std::generate_n(debugFloatData.begin(), 100, generator);

		std::vector<float> debugFloatData1(100);
		std::uniform_real_distribution<float> distribution1(0.0f, 32.0f); //Values between 0 and 2
		std::mt19937 engine1; // Mersenne twister MT19937
		engine1.seed(2);
		auto generator1 = std::bind(distribution1, engine1);
		std::generate_n(debugFloatData1.begin(), 100, generator1);

		graphDrawerDebug.StartDrawing();

		graphDrawerDebug.AddFloatData(debugFloatData, graphColors.Green, 2, 6);
		graphDrawerDebug.AddGraphLabel("Debug Float", 16, graphColors.Green, 0);
		graphDrawerDebug.AddFloatData(debugFloatData1, graphColors.Orange, 2, 6);
		graphDrawerDebug.AddGraphLabel("Debug Int", 16, graphColors.Orange, 1);*/
	}

	if (sceneManager != nullptr && willowPowlBackgroundGUID != nullptr && petrifiedOwlBossEntity == nullptr)
	{
		bool willowPowlBackgroundIsLoaded = app::ScenesManager_SceneIsEnabled_1(sceneManager, willowPowlBackgroundGUID, NULL);
		if (willowPowlBackgroundIsLoaded == true && petrifiedOwlBossEntity == nullptr)
		{
			app::Type* type45 = GetType("", "PetrifiedOwlBossEntity");
			app::Object_1__Array* arr22 = app::Object_1_FindObjectsOfType(type45, NULL);

			if (arr22 != nullptr && arr22->vector[0] != nullptr)
				petrifiedOwlBossEntity = (app::PetrifiedOwlBossEntity*)arr22->vector[0];
		}
	}

	IsUsingMessages = true;

	raceManager.CheckTimer();

	for (auto& message : MessagesManager.Messages) 
	{
		switch (message.Type) {

		case MessageType::GameCompletion:
		{
			tGetGameCompletion oGetGameCompletion = tGetGameCompletion(Assembly_BaseAddr + 0x3e45d0);
			Moon::GameWorld* pGameWorld = GetGameWorld(hProcess);
			if (pGameWorld != nullptr && oGetGameCompletion != nullptr)
				Moon::gameCompletionHooked = oGetGameCompletion(pGameWorld);
		}
		break;

		case MessageType::CreateCheckpoint:
		{
			tCreateCheckpoint oCreateCheckpoint = tCreateCheckpoint(Assembly_BaseAddr + 0x997230);
			if (oCreateCheckpoint != nullptr) {
				Moon::GameController* pGameController = GetGameController(hProcess);

				if (pGameController != nullptr)
					oCreateCheckpoint(pGameController);
			}
		}
		break;

		case MessageType::CreateObject:
		{
			raceManager.CreateRecorder();
			raceManager.StartRecorder();

			copySein = true;
		}
		break;

		case MessageType::StopRecorder:
		{
			raceManager.StopRecorder();
		}
		break;

		case MessageType::WriteRecorder:
		{
			raceManager.WriteRecorder();
		}
		break;

		case MessageType::GhostPlayerRun:
		{
			std::string ghostPath = sutil::getexepath();
			sutil::ReplaceS(ghostPath, "oriwotw.exe", "oriwotw_Data\\output\\ghosts\\test.ghost");
			bool wasSuccess = raceManager.CreateGhost(ghostPath);

			if (wasSuccess)
			{
				raceManager.startedWeRacing = totalFrames;
			}
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
				app::String* qName = string_new(qN);
				Moon::HString* qName1 = new Moon::HString(L"Fallen Friend", 1);
				Moon::Quest quest1 = BaseQuestsController->GetQuestByName(qName);
				bool works = true;
			}
		}
		break;

		case MessageType::FrameStep:
		{
			frameStep.State = FrameStepping::FrameSteppingEnabled;
		}
		break;

		case MessageType::CreateRaceCheckpoint:
		{
			tem::Vector3 position;
			auto sPosition = sutil::SplitTem(message.Content, ";");
			position.X = std::stof(sPosition[0]);
			position.Y = std::stof(sPosition[1]);
			position.Z = 0;
			debugDrawer.SetupTexture(graphColors.Orange, position);
		}
		break;

		case MessageType::RunRace:
		{
			raceManager.LoadRaceData(message.Content);
			raceManager.SetupRace();
		}
		break;
		}
	}
	MessagesManager.Messages = std::vector<Message>();
	MessagesManager.CurrentMessagesType = std::vector<int>();
	IsUsingMessages = false;

	Real_CClassFunction(__this);
}

typedef void(__thiscall* tMoonDriverSystem)(void* __this);
tMoonDriverSystem Real_MoonDriverSystem;

void __fastcall Mine_MoonDriverSystem(void* __this, int edx)
{
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
	else {
		Real_GameControllerUpdate(__this);
	}

	/*if (frameStep.State == FrameStepping::IsAutoFrameStepping) {
		Real_GameControllerUpdate(__this);
	}

	if (frameStep.State == FrameStepping::FrameSteppingDisabled) {
		Real_GameControllerUpdate(__this);
	}*/
}

void __fastcall My_OnPointerClick(void* __this, int edx)
{
	Real_OnPointerClick(__this);

	if (graphDrawer.AllFloatData.size() > 0)
	{
		graphDrawer.ClickEvent(__this);
	}

	if (graphDrawerDebug.AllFloatData.size() > 0)
	{
		graphDrawerDebug.ClickEvent(__this);
	}
}

std::string GetShriekData()
{
	std::string shriekData = "";
	if (petrifiedOwlBossEntity != nullptr && petrifiedOwlBossEntity->fields._._.m_vitals != nullptr && petrifiedOwlBossEntity->fields._._.m_sensor != nullptr)
	{
		shriekData = "HP: " + std::to_string(petrifiedOwlBossEntity->fields._._.m_vitals->fields.m_health) + "/" + std::to_string(petrifiedOwlBossEntity->fields._._.m_vitals->fields.m_maxHealth);
		shriekData += "POSITION: " + std::to_string(petrifiedOwlBossEntity->fields._._.m_sensor->fields.m_platformMovement->fields.m_prevPosition.x);
		shriekData += ", " + std::to_string(petrifiedOwlBossEntity->fields._._.m_sensor->fields.m_platformMovement->fields.m_prevPosition.y);
	}

	return shriekData;
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

	Moon::GameWorld* pGameWorld = GetGameWorld(hProcess);
	Moon::GameController* pGameController = GetGameController(hProcess);

	std::string returnMessage = "";
	std::vector<std::string> messages;

	//initalize detours
	Real_CClassFunction = CClassFunction_t(Assembly_BaseAddr + 0x994520);
	Real_MoonDriverSystem = tMoonDriverSystem(Assembly_BaseAddr + 0xE463C0);
	RealIl2cpp_string_new_wrapper = tIl2CppString(Assembly_BaseAddr + 0x263B50);
	//oSystem_String__ToCharArray = tSystem_String__ToCharArray(Assembly_BaseAddr + 0x1CD17A0);
	Real_GameControllerUpdate = tGameControllerUpdate(UnityPlayer_BaseAddress + 0x5f0350); //0x994040 gc -  0xA77FA0 sein
	Real_OnPointerClick = tOnPointerClick(Assembly_BaseAddr + 0x1E1A5C0);

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)Real_CClassFunction, Mine_CClassFunction);

#if defined(IL2CPP)
	DetourAttach(&(PVOID&)Real_MoonDriverSystem, Mine_MoonDriverSystem);
	DetourAttach(&(PVOID&)RealIl2cpp_string_new_wrapper, string_new);
	DetourAttach(&(PVOID&)Real_OnPointerClick, My_OnPointerClick);
#endif

	DetourAttach(&(PVOID&)Real_GameControllerUpdate, My_GameControllerUpdate);
	LONG lError = DetourTransactionCommit();

	//find base invis to use for cloning
	uintptr_t InvisibleCheckpointBaseAdress = UnityPlayer_BaseAddress + 0x0148FDA0;
	GetAddressOffset(hProcess, InvisibleCheckpointBaseAdress, { 0x60, 0x30, 0xE8, 0xE0, 0x60, 0x0 });
	if (InvisibleCheckpointBaseAdress != NULL)
		BaseInvisibleCheckpoint = (Moon::InvisibleCheckpoint*)(InvisibleCheckpointBaseAdress);

#if defined(IL2CPP)
	// Setup for the race animation.
	app::Vector3__Boxed* myVector3 = (app::Vector3__Boxed*)il2cpp_object_new((Il2CppClass*)app::Vector3__TypeInfo);
	app::Vector3__ctor(myVector3, -612.0f, -4318.0f, 0.0f, NULL);

	app::Type* scenesManagerType = GetType("", "ScenesManager");
	app::Object_1__Array* arr22 = app::Object_1_FindObjectsOfType(scenesManagerType, NULL);

	sceneManager = (app::ScenesManager*)arr22->vector[0];
	app::String* sceneToLoad = string_new("inkwaterMarshRaceSetups");
	app::List_1_RuntimeSceneMetaData_* allScenes = app::ScenesManager_ListAllScenesAtPosition(sceneManager, myVector3->fields, NULL);

	if (allScenes->fields._size > 0) {
		for (int i = 0; i < allScenes->fields._items->max_length; i++) {
			app::RuntimeSceneMetaData* inkMeta = allScenes->fields._items->vector[i];
			if (inkMeta != nullptr) {
				std::string aniNameS = sutil::convert_csstring(inkMeta->fields.Scene);
				if (aniNameS == "swampSpringIntroductionB")
					app::ScenesManager_PreloadScene(sceneManager, inkMeta, NULL);
			}
		}
	}

	for (int i = 0; i < sceneManager->fields.AllScenes->fields._size; i++)
	{
		std::string sceneName = sutil::convert_csstring(sceneManager->fields.AllScenes->fields._items->vector[i]->fields.Scene);
		if (sceneName == "willowPowlBackground")
		{
			willowPowlBackgroundGUID = sceneManager->fields.AllScenes->fields._items->vector[i]->fields.SceneMoonGuid;
		}
	}

	app::SeinCharacter* seinC = GetSeinCharacter(hProcess);
	app::SeinController* seinCC = seinC->fields.Controller;
	seinPlayAnimationController = seinCC->fields.m_playAnimationController;

	app::Type* type5111 = GetType("", "AreaMapIcon");
	app::Object_1__Array* arrAIcons = app::Object_1_FindObjectsOfTypeAll(type5111, NULL);

	std::vector<app::AreaMapIcon*> allAreaMapIcons;
	for (int i = 0; i < arrAIcons->max_length; i++)
	{
		if (arrAIcons->vector[i] != nullptr)
		{
			app::AreaMapIcon* icon = (app::AreaMapIcon*)arrAIcons->vector[i];

			if (icon != nullptr)
			{
				allAreaMapIcons.push_back(icon);
			}
		}
	}

	//RuntimeWorldMapIcon
	app::Type* tGameMapObjectiveIcons = GetType("", "GameMapObjectiveIcons");
	app::Object_1__Array* arrAGameMapObjectiveIcons = app::Object_1_FindObjectsOfTypeAll(tGameMapObjectiveIcons, NULL);

	app::GameMapObjectiveIcons* gameMapObjectives = (app::GameMapObjectiveIcons*)arrAGameMapObjectiveIcons->vector[0];

	areaMapManager.Initialize();

	//to create icons
	/*app::Type* type51 = GetType("", "GameWorldArea");
	app::Object_1__Array* arrA61 = app::Object_1_FindObjectsOfTypeAll(type51, NULL);

	app::GameWorldArea* gameWorldArea = nullptr;
	if (arrA61 != nullptr && arrA61->max_length > 0)
		gameWorldArea = (app::GameWorldArea*)arrA61->vector[0];
	
	app::GameWorldArea_WorldMapIcon* newWorldMapIcon2 = (app::GameWorldArea_WorldMapIcon*)il2cpp_object_new((Il2CppClass*)gameWorldArea->fields.Icons->fields._items->vector[0]->klass);
	newWorldMapIcon2->fields.Position.x = -730.0f;
	newWorldMapIcon2->fields.Position.y = -4300.0f;
	newWorldMapIcon2->fields.Icon = app::WorldMapIconType__Enum::WorldMapIconType__Enum_CreepHeart;
	app::CollectionBase_System_Collections_IList_Add((app::CollectionBase*)gameWorldArea->fields.Icons->fields._items, (app::Object*)newWorldMapIcon2, NULL);*/

#endif

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
					auto tempMM = sutil::SplitTem(message, "||");
					messages.insert(messages.end(), tempMM.begin(), tempMM.end());
				}
				else {
					messages.push_back(message);
				}

				if (IsUsingMessages == false) {
					for (auto& message : messages) {
						sutil::ReplaceS(message, "CALL", "");
						if (message != "") {
							Message newMessage;

							if (message.find("PAR") != std::string::npos)
							{
								auto paramSplit = sutil::SplitTem(message, "PAR");
								if (paramSplit.size() > 0)
								{
									newMessage.Content = paramSplit[1];
									newMessage.Type = MessageType(std::stoi(paramSplit[0]));
									newMessage.TypeInt = std::stoi(paramSplit[0]);
								}
							}
							else
							{
								newMessage.Type = MessageType(std::stoi(message));
								newMessage.TypeInt = std::stoi(message);
							}

							if (newMessage.Type == MessageType::FrameStep) {
								frameStep.ShouldFrameStep = true;
							}
							if (newMessage.Type == MessageType::FrameStepStop) {
								frameStep.State = FrameStepping::FrameSteppingDisabled;
								frameStep.ShouldFrameStep = false;
							}
							if (newMessage.Type == MessageType::NextAnimation)
							{
								app::SeinCharacter* seinC = GetSeinCharacter(hProcess);
								app::SeinController* seinCC = seinC->fields.Controller;
								app::SeinPlayAnimationController* seinCCA = seinCC->fields.m_playAnimationController;
								app::SeinPlayAnimationController_StopAnimation(seinCCA, NULL);
								animationIndex++;
							}

							MessagesManager.AddMessage(newMessage);
						}
					}
				}

				returnMessage += "GAMECOMPLETION:" + std::to_string(Moon::gameCompletionHooked * 100) + "||" + "SHRIEKDATA:" + GetShriekData() + "||";
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

	MessagesManager.Messages.clear();

	//sleep to let game finish and then dettach all the detours
	Sleep(25);

	graphDrawer.Destroy();
	debugDrawer.CleanUp();

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&(PVOID&)Real_CClassFunction, Mine_CClassFunction);

#if defined(IL2CPP)
	DetourDetach(&(PVOID&)Real_MoonDriverSystem, Mine_MoonDriverSystem);
	DetourDetach(&(PVOID&)RealIl2cpp_string_new_wrapper, string_new);
	DetourDetach(&(PVOID&)Real_OnPointerClick, My_OnPointerClick);
#endif

	DetourDetach(&(PVOID&)Real_GameControllerUpdate, My_GameControllerUpdate);
	DetourTransactionCommit();

	raceManager.CleanupManager();

	//sleep again to let the game cleanly return to it's own loops
	Sleep(25);
	FreeLibraryAndExitThread(hIns, 0);
	return 0;
}