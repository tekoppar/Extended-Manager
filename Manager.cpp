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

#define IL2CPP true

//il2cpp generated
#include "il2cpp-appdata.h"
#include "helpers.h"
using namespace app;

extern const LPCWSTR LOG_FILE = L"il2cpp-log.txt";

#include "CPPBeDumb.h"
#include "ManagerDef.h"
#include "Manager.h"
#include "RaceManager.h"

MessageManager MessagesManager;
std::vector<Moon::InvisibleCheckpoint> InvisibleCheckpoints;
std::vector<GhostPlayer*> ActiveGhostPlayers;
std::vector<MoonAnimation*> allAnimations;

SeinPlayAnimationController* seinPlayAnimationController = nullptr;
MoonAnimation* WERACING = nullptr;
unsigned long long startedWeRacing = 0;
bool playingAnimation = false;

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

GhostCharacterAbilitiesPlugin* ghostAP;
GhostCharacterPlugin* ghostCP;
GhostStateMachinePlugin* ghostSMP;
GhostGenericEventsPlugin* ghostGEP;
GhostRecordingMetaDataPlugin* ghostMDP;
GhostRecorder* ghostC;
RaceSystem* raceSC;
UnityRaceTimerDisplay* raceTimerText;
RaceTimer* ghostRaceTimer;

FrameStep frameStep;
bool loopBool = true;
bool IsUsingMessages = false;
bool copySein = false;

std::thread pipeThread;
HANDLE fileHandle;
DWORD pid;
HANDLE hProcess;

Moon::Object objectM = Moon::Object();

RaceManager raceManager = RaceManager();

String* string_new(const char* str)
{
	return RealIl2cpp_string_new_wrapper(str);
}

void __fastcall Mine_CClassFunction(void* __this, int edx)
{
	totalFrames++;

	/*if (totalFrames >= 100 && WERACING == nullptr)
	{
		raceManager.SetupManager();

		if (raceManager.BaseGhostManager == nullptr)
		{
			uintptr_t GhostManagerBaseAdress = Assembly_BaseAddr + 0x0445EB38;
			GetAddressOffset(hProcess, GhostManagerBaseAdress, { 0xB8, 0x0, 0x10, 0x28, 0x0 });
			if (GhostManagerBaseAdress != NULL)
				raceManager.BaseGhostManager = (GhostManager*)(GhostManagerBaseAdress);
		}

		Type* type3 = GetType("Moon", "MoonAnimation");
		Object_1__Array* arrA = Object_1_FindObjectsOfTypeAll(type3, NULL);

		for (int i = 0; i < arrA->max_length; i++)
		{
			if (arrA->vector[i] != NULL && arrA->vector[i] != nullptr)
			{
				MoonAnimation* tempANI = (MoonAnimation*)arrA->vector[i];
				if (tempANI != nullptr) {
					String* aniName = MoonAnimation_get_Name(tempANI, NULL);
					std::string aniNameS = convert_csstring(aniName);

					if (aniNameS == "oriStartRaceLoop")
					{
						WERACING = tempANI;
					}
				}
			}
		}
	}*/

	if (playingAnimation == true && totalFrames >= startedWeRacing + (1000 / 16.6666f * 3))
	{
		SeinPlayAnimationController_StopAnimation(seinPlayAnimationController, NULL);
		playingAnimation = false;

		bool wasSuccess = raceManager.RunGhost();
		/*for (GhostPlayer*& ghostPlayer : ActiveGhostPlayers) 
		{
			GhostPlayer_Run(ghostPlayer, NULL);
		}

		if (ghostRaceTimer != nullptr)
		{
			ghostRaceTimer->fields._TimeLimit_k__BackingField = 60.0f;
			ghostRaceTimer->fields._BestTime_k__BackingField = 35.6f;
			ghostRaceTimer->fields._TimeToBeat_k__BackingField = 35.6f;
			ghostRaceTimer->fields._IsSuspended_k__BackingField = false;
			RaceTimer_SetTimeLimit(ghostRaceTimer, 60.0f, NULL);
			RaceTimer_StartTimer(ghostRaceTimer, NULL);
		}*/
	}


	IsUsingMessages = true;

	//check if ghost has finished, if so remove them
	/*std::vector<GhostPlayer*> ghostsStillRunning;
	for (auto& ghost : ActiveGhostPlayers)
	{
		if (ghost->fields._IsFinished_k__BackingField)
		{
			GhostPlayer_Stop(ghost, NULL);
		}
		else
		{
			ghostsStillRunning.push_back(ghost);
		}
	}
	ActiveGhostPlayers = ghostsStillRunning;*/

	raceManager.CheckTimer();
	/*if (ghostRaceTimer != nullptr && ghostRaceTimer->fields.m_startedRace == true)
	{
		float raceFloat = ghostRaceTimer->fields._ElapsedTime_k__BackingField;

		if (raceFloat >= 60.0f)
		{
			RaceTimer_Stop(ghostRaceTimer, NULL);
		}

		double minutes = std::floor(std::fmod(raceFloat * 1000.0f / (1000.0f * 60.0f), 60));// std::floor(raceFloat / (1000.0f * 60.0f) % 60);
		double seconds = std::floor(std::fmod(raceFloat * 1000.0f / 1000.0f, 60));// std::floor(raceFloat / 1000.0f % 60);
		double milliseconds = std::floor(std::fmod(raceFloat * 1000.0f, 1000));

		String* raceTimerDivisorMinute = string_new(":");
		String* raceTimerDivisorSecond = string_new(".");

		std::string raceTimerMinute = DoubleToStr(minutes);
		String* raceTimerMinuteS = string_new(raceTimerMinute.data());

		std::string raceTimerSeconds = DoubleToStr(seconds);
		raceTimerSeconds = raceTimerSeconds.length() == 2 ? raceTimerSeconds : "0" + raceTimerSeconds;
		std::string raceTimerSecondsOne = raceTimerSeconds.substr(1, 1);
		std::string raceTimerSecondsTen = raceTimerSeconds.substr(0, 1);
		String* raceTimerSecondsTenS = string_new(raceTimerSecondsTen.data());
		String* raceTimerSecondsOneS = string_new(raceTimerSecondsOne.data());

		std::string raceTimerMilliseconds = DoubleToStr(milliseconds);
		raceTimerMilliseconds = raceTimerMilliseconds.length() == 3 ? raceTimerMilliseconds : (raceTimerMilliseconds.length() == 2  ? "0" + raceTimerMilliseconds : "00" + raceTimerMilliseconds);
		std::string raceTimerMillisecondsOne = raceTimerMilliseconds.substr(2, 1);
		std::string raceTimerMillisecondsTen = raceTimerMilliseconds.substr(1, 1);
		std::string raceTimerMillisecondsHundred = raceTimerMilliseconds.substr(0, 1);
		String* raceTimerMillisecondsOneS = string_new(raceTimerMillisecondsOne.data());
		String* raceTimerMillisecondsTenS = string_new(raceTimerMillisecondsTen.data());
		String* raceTimerMillisecondsHundredS = string_new(raceTimerMillisecondsHundred.data());

		if (raceTimerText != nullptr)
		{
			TextBox_SetText_1(raceTimerText->fields.Minute, raceTimerMinuteS, NULL);
			TextBox_SetText_1(raceTimerText->fields.ColonMin, raceTimerDivisorMinute, NULL);
			TextBox_SetText_1(raceTimerText->fields.SecondTen, raceTimerSecondsTenS, NULL);
			TextBox_SetText_1(raceTimerText->fields.SecondOne, raceTimerSecondsOneS, NULL);
			TextBox_SetText_1(raceTimerText->fields.ColonSec, raceTimerDivisorSecond, NULL);
			TextBox_SetText_1(raceTimerText->fields.MiliHund, raceTimerMillisecondsHundredS, NULL);
			TextBox_SetText_1(raceTimerText->fields.MiliTen, raceTimerMillisecondsTenS, NULL);
			TextBox_SetText_1(raceTimerText->fields.MiliOne, raceTimerMillisecondsOneS, NULL);

			if (ghostRaceTimer->fields._ElapsedTime_k__BackingField >= ghostRaceTimer->fields._BestTime_k__BackingField)
			{
				Color redColor = Color();
				redColor.a = 1.0f;
				redColor.b = 0.0f;
				redColor.g = 0.0f;
				redColor.r = 1.0f;

				raceTimerText->fields.Minute->fields.color = redColor;
				raceTimerText->fields.ColonMin->fields.color = redColor;
				raceTimerText->fields.SecondTen->fields.color = redColor;
				raceTimerText->fields.SecondOne->fields.color = redColor;
				raceTimerText->fields.ColonSec->fields.color = redColor;
				raceTimerText->fields.MiliHund->fields.color = redColor;
				raceTimerText->fields.MiliTen->fields.color = redColor;
				raceTimerText->fields.MiliOne->fields.color = redColor;
			}

			TextBox_RefreshText(raceTimerText->fields.Minute, NULL);
			TextBox_RefreshText(raceTimerText->fields.ColonMin, NULL);
			TextBox_RefreshText(raceTimerText->fields.SecondTen, NULL);
			TextBox_RefreshText(raceTimerText->fields.SecondOne, NULL);
			TextBox_RefreshText(raceTimerText->fields.ColonSec, NULL);
			TextBox_RefreshText(raceTimerText->fields.MiliHund, NULL);
			TextBox_RefreshText(raceTimerText->fields.MiliTen, NULL);
			TextBox_RefreshText(raceTimerText->fields.MiliOne, NULL);
		}
	}*/

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
			/*ghostC = Moon::GhostManager::GetOrCreateRecorder();

			auto Class1 = GetClass<>("", "GhostCharacterAbilitiesPlugin");
			ghostAP = (GhostCharacterAbilitiesPlugin*)il2cpp_object_new((Il2CppClass*)Class1);
			auto Class2 = GetClass<>("", "GhostCharacterPlugin");
			ghostCP = (GhostCharacterPlugin*)il2cpp_object_new((Il2CppClass*)Class2);
			auto Class3 = GetClass<>("", "GhostStateMachinePlugin");
			ghostSMP = (GhostStateMachinePlugin*)il2cpp_object_new((Il2CppClass*)Class3);
			auto Class4 = GetClass<>("", "GhostGenericEventsPlugin");
			ghostGEP = (GhostGenericEventsPlugin*)il2cpp_object_new((Il2CppClass*)Class4);
			auto Class5 = GetClass<>("", "GhostRecordingMetaDataPlugin");
			ghostMDP = (GhostRecordingMetaDataPlugin*)il2cpp_object_new((Il2CppClass*)Class5);

			GhostRecorder_RegisterPluginAbilities(ghostC, ghostAP, NULL);
			GhostRecorder_RegisterPlugin(ghostC, (IGhostRecorderPlugin*)ghostCP, NULL);
			GhostRecorder_RegisterPlugin(ghostC, (IGhostRecorderPlugin*)ghostSMP, NULL);
			GhostRecorder_RegisterPlugin(ghostC, (IGhostRecorderPlugin*)ghostGEP, NULL);
			GhostRecorder_RegisterPlugin(ghostC, (IGhostRecorderPlugin*)ghostMDP, NULL);

			std::string ghostPath = getexepath();
			ReplaceS(ghostPath, "oriwotw.exe", "oriwotw_Data\\output\\ghosts\\swamp1\\test.ghost");
			String* MRecorderPath = string_new(ghostPath.c_str());

			GhostRecorder_InitializeRecorder(ghostC, MRecorderPath, NULL);
			GhostRecorder_StartRecorder(ghostC, NULL);*/

			copySein = true;
		}
		break;

		case MessageType::StopRecorder:
		{
			raceManager.StopRecorder();
			/*if (ghostC != nullptr) {
				GhostRecorder_StopRecorder(ghostC, NULL);
			}*/

		}
		break;

		case MessageType::WriteRecorder:
		{
			raceManager.WriteRecorder();
			/*if (ghostC != nullptr) {
				GhostRecorder_FinalizeFrame(ghostC, NULL);
				GhostRecorder_WriteToFile(ghostC, NULL);

				String* raceFile = GhostRecorder_get_FilePath(ghostC, NULL);
				std::string raceFileS = convert_csstring(raceFile);
				ConvertGhostRecordingToBase64(raceFileS);
			}*/
		}
		break;

		case MessageType::GhostPlayerRun:
		{
			std::string ghostPath = getexepath();
			ReplaceS(ghostPath, "oriwotw.exe", "oriwotw_Data\\output\\ghosts\\test.ghost");
			bool wasSuccess = raceManager.CreateGhost(ghostPath);

			if (wasSuccess)
			{
				SeinPlayAnimationController_PlayAnimation_1(seinPlayAnimationController, WERACING, NULL);
				startedWeRacing = totalFrames;
				playingAnimation = true;
			}

			/*//get the ghost race timer
			raceSC = (RaceSystem*)il2cpp_object_new((Il2CppClass*)RaceSystem__TypeInfo);
			ghostRaceTimer = raceSC->klass->static_fields->_Instance_k__BackingField->fields.m_timer;

			//Get race timer
			Type* type = GetType("", "UnityRaceTimerDisplay");
			Object_1__Array* arr2222 = Object_1_FindObjectsOfType(type, NULL);

			if (arr2222->vector[0] != nullptr)
				raceTimerText = (UnityRaceTimerDisplay*)arr2222->vector[0];

			std::string contents = readFile(ghostPath);
			const char* gP = contents.data();// readFile(ghostPath);
			String* gPath = string_new(gP);
			const char* gPN = "SPOOOOOKKKYYY";
			String* gName = string_new(gPN);
			GhostPlayer* ghostPlayer = GhostManager_createGhost_1(BaseGhostManager, gName, gPath, NULL);

			if (ghostPlayer != nullptr) {
				ActiveGhostPlayers.push_back(ghostPlayer);

				if (seinPlayAnimationController != nullptr && WERACING != nullptr)
				{
					SeinPlayAnimationController_PlayAnimation_1(seinPlayAnimationController, WERACING, NULL);
					startedWeRacing = totalFrames;
					playingAnimation = true;
				}
			}*/
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
				String* qName = string_new(qN);
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
		}
	}
	MessagesManager.Messages.clear();
	MessagesManager.CurrentMessagesType.clear();
	IsUsingMessages = false;

	Real_CClassFunction(__this);
}

typedef void(__thiscall* tMoonDriverSystem)(void* __this);
tMoonDriverSystem Real_MoonDriverSystem;

void __fastcall Mine_MoonDriverSystem(void* __this, int edx)
{
	if (copySein) {
		copySein = false;
		//Moon::SeinCharacter* sein = GetSeinCharacter(hProcess);
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

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)Real_CClassFunction, Mine_CClassFunction);

#if defined(IL2CPP)
	DetourAttach(&(PVOID&)Real_MoonDriverSystem, Mine_MoonDriverSystem);
	DetourAttach(&(PVOID&)RealIl2cpp_string_new_wrapper, string_new);
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
	Vector3__Boxed* myVector3 = (Vector3__Boxed*)il2cpp_object_new((Il2CppClass*)Vector3__TypeInfo);
	Vector3__ctor(myVector3, -612.0f, -4318.0f, 0.0f, NULL);

	Type* type45 = GetType("", "ScenesManager");
	Object_1__Array* arr22 = Object_1_FindObjectsOfType(type45, NULL);

	ScenesManager* sceneManager = (ScenesManager*)arr22->vector[0];
	String* sceneToLoad = string_new("inkwaterMarshRaceSetups");
	List_1_RuntimeSceneMetaData_* allScenes = ScenesManager_ListAllScenesAtPosition(sceneManager, myVector3->fields, NULL);

	if (allScenes->fields._size > 0) {
		for (int i = 0; i < allScenes->fields._items->max_length; i++) {
			RuntimeSceneMetaData* inkMeta = allScenes->fields._items->vector[i];
			if (inkMeta != nullptr) {
				std::string aniNameS = convert_csstring(inkMeta->fields.Scene);
				if (aniNameS == "swampSpringIntroductionB")
					ScenesManager_PreloadScene(sceneManager, inkMeta, NULL);
			}
		}
	}
	// Setup for the race animation.


	SeinCharacter* seinC = GetSeinCharacter(hProcess);

	//ATTACK ANIMATIONS????
	/*Type* type4 = GetType("Moon", "AnimationPlayer");
	Object_1__Array* arrA5 = Object_1_FindObjectsOfTypeAll(type4, NULL);

	std::vector<MoonAnimation*> allAnimationPlayer;
	std::vector<std::string> allAnimationPlayerNames;
	for (int i = 0; i < arrA5->max_length; i++)
	{
		if (arrA5->vector[i] != nullptr)
		{
			AnimationPlayer* tempMoon = (AnimationPlayer*)arrA5->vector[i];

			if (tempMoon != nullptr && tempMoon->fields.Animation != nullptr)
			{
				String* aniName = MoonAnimation_get_Name(tempMoon->fields.Animation, NULL);
				std::string aniNameS = convert_csstring(aniName);
				allAnimationPlayerNames.push_back(aniNameS);
				allAnimationPlayer.push_back(tempMoon->fields.Animation);
			}
		}
	}*/
	//ATTACK ANIMATIONS????

	//LOTS OF BLEND ANIMATIONS?????
	/*Type* type5 = GetType("Moon", "BlendAnimation");
	Object_1__Array* arrA6 = Object_1_FindObjectsOfTypeAll(type5, NULL);

	std::vector<MoonAnimation*> allBlendAnimation;
	std::vector<std::string> allBlendAnimationNames;
	if (arrA6 != nullptr) 
	{
		for (int i = 0; i < arrA6->max_length; i++)
		{
			if (arrA6->vector[i] != nullptr)
			{
				BlendAnimation* tempMoon = (BlendAnimation*)arrA6->vector[i];

				if (tempMoon != nullptr && tempMoon->fields.Inputs != nullptr)
				{
					for (int i2 = 0; i2 < tempMoon->fields.Inputs->max_length; i2++) {
						BlendAnimation_Input* tempVar = tempMoon->fields.Inputs->vector[i2];
						if (tempVar != nullptr) {
							MoonAnimation* moonimation = tempVar->fields.Animation;

							if (moonimation != nullptr) {
								String* aniName = MoonAnimation_get_Name(moonimation, NULL);
								std::string aniNameS = convert_csstring(aniName);
								allBlendAnimationNames.push_back(aniNameS);
								allBlendAnimation.push_back(moonimation);
							}
						}
					}
				}
			}
		}
	}*/
	//LOTS OF BLEND ANIMATIONS?????

	//LOTS OF BLEND ClipAnimation?????
	/*Type* type6 = GetType("Moon", "ClipAnimation");
	Object_1__Array* arrA7 = Object_1_FindObjectsOfTypeAll(type6, NULL);

	std::vector<MoonAnimation*> allClipAnimation;
	std::vector<std::string> allClipAnimationNames;
	for (int i = 0; i < arrA7->max_length; i++)
	{
		if (arrA7->vector[i] != nullptr)
		{
			ClipAnimation* tempMoon = (ClipAnimation*)arrA7->vector[i];
			MoonAnimation* moonimation  = new MoonAnimation();
			moonimation->fields = tempMoon->fields._;

			if (tempMoon != nullptr)
			{
				String* aniName = MoonAnimation_get_Name(moonimation, NULL);
				std::string aniNameS = convert_csstring(aniName);
				allClipAnimationNames.push_back(aniNameS);
				allClipAnimation.push_back(moonimation);
			}
		}
	}*/
	//LOTS OF BLEND ClipAnimation?????

	SeinController* seinCC = seinC->fields.Controller;
	seinPlayAnimationController = seinCC->fields.m_playAnimationController;

	/*PlatformBehaviour* seinPlat = seinC->fields.PlatformBehaviour;
	CharacterVisuals* seinVis = seinPlat->fields.Visuals;
	CharacterAnimationSystem* seinAniSys = seinVis->fields.Animation;
	MoonAnimator* moonAnimator = seinAniSys->fields.MoonAnimator;
	MoonAnimator_ActiveAnimation* IactiveAni = (MoonAnimator_ActiveAnimation*)seinAniSys->fields.m_currentState;
	MoonAnimation* activeAni = (MoonAnimation*)MoonAnimator_ActiveAnimation_get_Animation(IactiveAni, NULL);
	String* aniNames = MoonAnimation_get_Name(activeAni, NULL);
	std::string aniNameSs = convert_csstring(aniNames);

	//if (WERACING != nullptr)
		//SeinPlayAnimationController_PlayAnimation_1(seinPlayAnimationController, WERACING, NULL);*/

	//to create icons
	/*Type* type51 = GetType("", "GameWorldArea");
	Object_1__Array* arrA61 = Object_1_FindObjectsOfTypeAll(type51, NULL);

	GameWorldArea* gameWorldArea = nullptr;
	if (arrA61 != nullptr && arrA61->max_length > 0)
		gameWorldArea = (GameWorldArea*)arrA61->vector[0];
	
	GameWorldArea_WorldMapIcon* newWorldMapIcon2 = (GameWorldArea_WorldMapIcon*)il2cpp_object_new((Il2CppClass*)gameWorldArea->fields.Icons->fields._items->vector[0]->klass);
	newWorldMapIcon2->fields.Position.x = -730.0f;
	newWorldMapIcon2->fields.Position.y = -4300.0f;
	newWorldMapIcon2->fields.Icon = WorldMapIconType__Enum::WorldMapIconType__Enum_CreepHeart;
	CollectionBase_System_Collections_IList_Add((CollectionBase*)gameWorldArea->fields.Icons->fields._items, (Object*)newWorldMapIcon2, NULL);*/

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
					auto tempMM = SplitS(message, '||');
					messages.insert(messages.end(), tempMM.begin(), tempMM.end());
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
							newMessage.TypeInt = std::stoi(message);

							if (newMessage.Type == MessageType::FrameStep) {
								frameStep.ShouldFrameStep = true;
							}
							if (newMessage.Type == MessageType::FrameStepStop) {
								frameStep.State = FrameStepping::FrameSteppingDisabled;
								frameStep.ShouldFrameStep = false;
							}
							if (newMessage.Type == MessageType::NextAnimation)
							{
								SeinCharacter* seinC = GetSeinCharacter(hProcess);
								SeinController* seinCC = seinC->fields.Controller;
								SeinPlayAnimationController* seinCCA = seinCC->fields.m_playAnimationController;
								SeinPlayAnimationController_StopAnimation(seinCCA, NULL);
								animationIndex++;
							}

							//MessagesManager.AddMessage(newMessage);
						}
					}
				}

				returnMessage += "GAMECOMPLETION:" + std::to_string(Moon::gameCompletionHooked * 100) + "||";
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
	Sleep(100);
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&(PVOID&)Real_CClassFunction, Mine_CClassFunction);

#if defined(IL2CPP)
	DetourDetach(&(PVOID&)Real_MoonDriverSystem, Mine_MoonDriverSystem);
	DetourDetach(&(PVOID&)RealIl2cpp_string_new_wrapper, string_new);
#endif

	DetourDetach(&(PVOID&)Real_GameControllerUpdate, My_GameControllerUpdate);
	DetourTransactionCommit();

	//sleep again to let the game cleanly return to it's own loops
	Sleep(100);
	FreeLibraryAndExitThread(hIns, 0);
	return 0;
}