#include "pch-il2cpp.h"

#include <Windows.h>
#undef MessageBox 
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
#include <psapi.h>
#include <future>
#include <chrono>
#include <unordered_map>

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
#include "CreateUI.h"
#include "SeinCharacterHelper.h"
#include "TemSceneHelper.h"
#include "MessageHelper.h"
#include "MoonAnimationHelper.h"
#include "TemSocket.h"
#include "GhostHandler.h"
#include "TemRecorder.h"
#include "UberStateManager.h"
#include "SavesHelper.h"

static bool MANAGER_INITIALIZED = false;

MessageManager MessagesManager;
AreaMapManager areaMapManager;
Graph graphDrawerDebug;
DebugDrawer debugDrawer;
RaceManager raceManager = RaceManager();

std::vector<app::GhostPlayer*> ActiveGhostPlayers;
std::vector<app::MoonAnimation*> allAnimations;

app::GameObject* randotest = nullptr;
bool stopLoop1 = false;
int framesPlayed = 0;
unsigned long long totalFrames = 0;

std::chrono::high_resolution_clock::time_point ProgramStart = std::chrono::high_resolution_clock::now();
std::chrono::high_resolution_clock::time_point LastTime;

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
app::Ku* kuRide = nullptr;

app::MoonGuid* willowPowlBackgroundGUID = nullptr;
std::string ShriekData = "";

app::GameObject* HitboxDebug = nullptr;

FrameStep frameStep;
bool loopBool = true;
bool copySein = false;
bool IsWritingToMessageString = false;

std::thread pipeThread;
HANDLE fileHandle;
HANDLE fileHandleWrite;
DWORD pid;
HANDLE hProcess;
std::string managerPath = "";
//std::string MessageToWrite = "";

std::future<bool> HasLoadedScenes;
bool SetupsAreDone = false;
std::chrono::milliseconds span(1);

app::Canvas* canvas123 = nullptr;

app::String* string_new(const char* str)
{
	return RealIl2cpp_string_new_wrapper(str);
}

void InitializeDLL()
{
	app::Type* scenesManagerType = GetType("", "ScenesManager");
	app::Object_1__Array* arr22 = app::Object_1_FindObjectsOfType(scenesManagerType, NULL);

	sceneManager = (app::ScenesManager*)arr22->vector[0];
	TemSceneHelper::SceneManager = sceneManager;
	GraphColors::Initialize();

	for (int i = 0; i < sceneManager->fields.AllScenes->fields._size; i++)
	{
		std::string sceneName = sutil::convert_csstring(sceneManager->fields.AllScenes->fields._items->vector[i]->fields.Scene);
		if (sceneName == "willowPowlBackground")
		{
			willowPowlBackgroundGUID = sceneManager->fields.AllScenes->fields._items->vector[i]->fields.SceneMoonGuid;
		}
	}

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

	DebugDrawer::Initialize();
	debugDrawer = DebugDrawer();

	app::Type* Texture2DType = GetType("UnityEngine", "Texture2D");
	app::Object_1__Array* Texture2DArr = app::Object_1_FindObjectsOfTypeAll(Texture2DType, NULL);

	for (int i = 0; i < Texture2DArr->max_length; i++)
	{
		if (Texture2DArr->vector[i] != nullptr)
		{
			app::Texture2D* texture2D = (app::Texture2D*)Texture2DArr->vector[i];

			if (texture2D != nullptr)
			{
				app::String* name = app::Object_1_get_name((app::Object_1*)texture2D, NULL);
				std::string nameS = sutil::convert_csstring(name);

				if (nameS != "" && nameS.find("lightCanvas") == std::string::npos)
				{
					DrawUI::AllTexture2DNames.push_back(nameS);
					DrawUI::AllTexture2D.push_back(texture2D);
				}
			}
		}
	}

	TemSceneHelper::InitializeSceneNodes();
	TemSceneHelper::FillUberPoolGroups();

	app::Vector3__Boxed* myVector3 = (app::Vector3__Boxed*)il2cpp_object_new((Il2CppClass*)app::Vector3__TypeInfo);
	app::Vector3__ctor(myVector3, -612.0f, -4318.0f, 0.0f, NULL);

	auto scenes = TemSceneHelper::GetScenesAtPosition(myVector3->fields);
	app::RuntimeSceneMetaData* raceScene = TemSceneHelper::GetSceneByName("inkwaterMarshRaceSetups");
	scenes.push_back(raceScene);
	TemSceneHelper::LoadScenes(scenes);
	HasLoadedScenes = std::async(TemSceneHelper::IsScenesLoaded, scenes, false);
	MDV::User.Initialize();

	app::SimpleFPS* simpleFPS = app::SimpleFPS__TypeInfo->static_fields->Instance;
	//simpleFPS->fields.ComplicatedMode = false;
	//simpleFPS->fields.ReallySimpleMode = false;
	//simpleFPS->fields.TrailerMode = false;
	//app::Behaviour_set_moonReady((app::Behaviour*)simpleFPS, false, NULL);
	app::Behaviour_set_enabled((app::Behaviour*)simpleFPS, false, NULL);

	MANAGER_INITIALIZED = true;
}

void __fastcall Mine_CClassFunction(void* __this, int edx)
{
	if (MANAGER_INITIALIZED == false)
	{
		InitializeDLL();

	}
	else
	{
		MDV::CanCallMethods = true;
		TemSceneHelper::CanCallMethods = true;
		MDV::ValidatePointers();

		totalFrames++;
		raceManager.totalFrames = totalFrames;

		if (MANAGER_INITIALIZED == true && SetupsAreDone == false && HasLoadedScenes.valid() && HasLoadedScenes.wait_for(span) == std::future_status::ready)
		{
			AnimationHelper::GetAnimations();
			raceManager.SetupManager();
			SetupsAreDone = true;
		}

		/*if (sceneManager != nullptr && willowPowlBackgroundGUID != nullptr && petrifiedOwlBossEntity == nullptr)
		{
			bool willowPowlBackgroundIsLoaded = app::ScenesManager_SceneIsEnabled_1(sceneManager, willowPowlBackgroundGUID, NULL);
			if (willowPowlBackgroundIsLoaded == true && petrifiedOwlBossEntity == nullptr)
			{
				app::Type* type45 = GetType("", "PetrifiedOwlBossEntity");
				app::Object_1__Array* arr22 = app::Object_1_FindObjectsOfType(type45, NULL);

				if (arr22 != nullptr && arr22->vector[0] != nullptr)
					petrifiedOwlBossEntity = (app::PetrifiedOwlBossEntity*)arr22->vector[0];
			}
		}*/

		if (MDV::MoonGameWorld != nullptr)
		{
			MDV::PreviousGameCompletion = MDV::GameCompletion;
			MDV::GameCompletion = app::GameWorld_get_CompletionAmount(MDV::MoonGameWorld, NULL);

			if (MDV::GameCompletion != MDV::PreviousGameCompletion)
				MDV::MessageToWrite.push_back("GAMECOMPLETION:" + std::to_string(MDV::GameCompletion * 100));
		}
		/*if (petrifiedOwlBossEntity != nullptr && petrifiedOwlBossEntity->fields._._.m_vitals != nullptr && petrifiedOwlBossEntity->fields._._.m_sensor != nullptr)
		{
			std::string shriekData = "HP: " + std::to_string(petrifiedOwlBossEntity->fields._._.m_vitals->fields.m_health) + "/" + std::to_string(petrifiedOwlBossEntity->fields._._.m_vitals->fields.m_maxHealth);
			shriekData += "POSITION: " + std::to_string(petrifiedOwlBossEntity->fields._._.m_sensor->fields.m_platformMovement->fields.m_prevPosition.x);
			shriekData += ", " + std::to_string(petrifiedOwlBossEntity->fields._._.m_sensor->fields.m_platformMovement->fields.m_prevPosition.y);
			MDV::MessageToWrite.push_back("SHRIEKDATA:" + shriekData);
		}*/

		for (auto& object : MDV::AllObjectsToCallUpdate)
		{
			object->Update();
		}

		//send data to the manager
		if (MDV::MoonSein != nullptr && MDV::MoonSein->fields.PlatformBehaviour != nullptr && MDV::MoonSein->fields.PlatformBehaviour->fields.PlatformMovement != nullptr)
		{
			tem::Vector3 oldSeinPosition = tem::Vector3(MDV::MoonSein->fields.PlatformBehaviour->fields.PlatformMovement->fields.m_oldPosition);
			MDV::MessageToWrite.push_back("SEINPOSITION:" + oldSeinPosition.ToString());
			unsigned long long seinPtr = (unsigned long long)(MDV::MoonSein);
			MDV::MessageToWrite.push_back("SEINPTR:" + std::to_string(seinPtr));
		}

		LastTime = std::chrono::high_resolution_clock::now();
		std::chrono::milliseconds timeSpan = std::chrono::duration_cast<std::chrono::milliseconds>(LastTime - ProgramStart);
		ProgramStart = LastTime;

		std::unordered_map<MessageType, Message> messages = MessagesManager.GetMessages();
		for (auto& message : messages)
		{
			bool futureIsReady = false;
			bool futureExists = false;

			MessagesManager.DecrementTimeout(timeSpan.count(), message.second.Type);
			message.second.Timeout -= timeSpan.count();
			if (message.second.Timeout < 0)
			{
				MessagesManager.RemoveMessage(message.second.Type);
				//MessagesManager.Messages.erase(MessagesManager.Messages.begin() + i);
				//MessagesManager.CurrentMessagesType.erase(MessagesManager.CurrentMessagesType.begin() + i);
				//i--;
				continue;
			}

			if (MessagesManager.MessagesFutures.find(message.second.Type) != MessagesManager.MessagesFutures.end())
			{
				futureExists = true;
				if (MessagesManager.MessagesFutures[message.second.Type].wait_for(span) != std::future_status::ready)
				{
					continue;
				}
				else
				{
					futureIsReady = true;
				}
			}

			switch (message.second.Type)
			{

			case MessageType::GameCompletion:
			{
				if (MDV::MoonGameWorld != nullptr)
					MDV::GameCompletion = app::GameWorld_get_CompletionAmount(MDV::MoonGameWorld, NULL);// oGetGameCompletion(pGameWorld);
			}
			break;

			case MessageType::CreateCheckpoint:
			{
				tCreateCheckpoint oCreateCheckpoint = tCreateCheckpoint(Assembly_BaseAddr + 0x997230);
				if (oCreateCheckpoint != nullptr) {

					if (MDV::MoonGameController != nullptr)
						app::GameController_CreateCheckpointWithSave(MDV::MoonGameController, NULL); // oCreateCheckpoint(pGameController);
				}
			}
			break;

			case MessageType::CreateObject:
			{
				raceManager.TemGhostRecorder.CreateRecorder();
				raceManager.TemGhostRecorder.StartRecorder();

				copySein = true;
			}
			break;

			case MessageType::StopRecorder:
			{
				raceManager.TemGhostRecorder.StopRecorder();
			}
			break;

			case MessageType::WriteRecorder:
			{
				std::string ghostPath = sutil::getexepath();
				sutil::ReplaceS(ghostPath, "oriwotw.exe", "oriwotw_Data\\output\\ghosts\\test.ghost");
				raceManager.TemGhostRecorder.WriteRecorder(ghostPath);
			}
			break;

			case MessageType::GhostPlayerRun:
			{
				std::string ghostPath = sutil::getexepath();
				sutil::ReplaceS(ghostPath, "oriwotw.exe", "oriwotw_Data\\output\\ghosts\\test.ghost");
				//app::GameObject* ghost = (app::GameObject*)app::Object_1_Instantiate_2((app::Object_1*)GhostHandler::BaseGhostManager->fields.GhostPrefab, NULL);
				GhostHandler::CreateGhostPublic(ghostPath);
				raceManager.startedWeRacing = totalFrames;
			}
			break;

			case MessageType::EndThread:
			{
#ifdef _DEBUG

				::IsConnected = false;
#endif
				SeinCharacterHelper::RestoreSeinAbilities();
				GhostHandler::Cleanup();
				loopBool = false;
			}
			break;

			case MessageType::GetQuestByName:
			{
				/*BaseQuestsController = GetQuestsController(hProcess);

				if (BaseQuestsController != nullptr) {
					const char* qN = "Fallen Friend";
					app::String* qName = string_new(qN);
					Moon::HString* qName1 = new Moon::HString(L"Fallen Friend", 1);
					Moon::Quest quest1 = BaseQuestsController->GetQuestByName(qName);
					bool works = true;
				}*/
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
				auto sPosition = sutil::SplitTem(message.second.Content, ";");
				position.X = std::stof(sPosition[0]);
				position.Y = std::stof(sPosition[1]);
				position.Z = 0;
				debugDrawer.SetupTexture(GraphColors::Orange, position);
			}
			break;

			case MessageType::RunRace:
			{
				raceManager.CheckHash();
				if (raceManager.IsRaceLoaded == true)
				{
					raceManager.SetupRace(raceManager.RaceDuration);
				}
				else if (futureIsReady == false)
				{
					raceManager.LoadRaceData(message.second.Content);
					message.second.Content = "";

					if (raceManager.StartPosition.IsSet() && raceManager.FinishPosition.IsSet())
					{
#ifdef _DEBUG
						TemSocket::SendSocketMessage("GETGHOSTS" + TemSocket::MD + raceManager.raceName);
#endif

						auto scenes = TemSceneHelper::GetScenesAtPosition(raceManager.StartPosition);
						auto scenes1 = TemSceneHelper::GetScenesAtPosition(raceManager.FinishPosition);

						if (scenes.size() > 0 && scenes1.size() > 0)
						{
							std::vector<TemSceneNode> scenesFound = TemSceneHelper::GetScenePathByName(sutil::convert_csstring(scenes[0]->fields.Scene), sutil::convert_csstring(scenes1[0]->fields.Scene));
							std::vector<app::RuntimeSceneMetaData*> scenesToLoad = TemSceneHelper::GetScenesByTemSceneNode(scenesFound);

							app::RuntimeSceneMetaData* raceScene = TemSceneHelper::GetSceneByName("inkwaterMarshRaceSetups");
							TemSceneHelper::LoadScenes(std::vector<app::RuntimeSceneMetaData*> {raceScene});

							TemSceneHelper::LoadScenes(scenesToLoad);
							MessagesManager.MessagesFutures[message.second.Type] = std::async(TemSceneHelper::IsScenesLoaded, scenesToLoad, true);
							MessagesManager.SetTimeout(15 * 1000, message.second.Type);
							message.second.Timeout = 15 * 1000;
							//MessagesManager.Messages[i].Timeout = 15 * 1000;
							futureExists = true;
						}
					}
					else
					{
						MessagesManager.RemoveMessage(message.second.Type);
						//MessagesManager.Messages.erase(MessagesManager.Messages.begin() + i);
						//MessagesManager.CurrentMessagesType.erase(MessagesManager.CurrentMessagesType.begin() + i);
						//i--;
						continue;
					}
				}
				else
				{
					auto value = MessagesManager.MessagesFutures[message.second.Type].get();

					if (value == true)
					{
						MessagesManager.RemoveMessage(message.second.Type);
						MessagesManager.MessagesFutures.erase(message.second.Type);
						futureExists = false;
						raceManager.SetupRace(raceManager.RaceDuration);
					}
				}
			}
			break;

			case MessageType::RemoveCheckpoint:
			{
				raceManager.RemoveCheckpoint(std::stoi(message.second.Content));
			}
			break;

			case MessageType::LoadRace:
			{
				if (futureIsReady == false)
				{
					auto splitContent = sutil::SplitTem(message.second.Content, "|");
					DebugDrawer::toggleDebugObjects = splitContent[1] == "False" ? false : true;
					raceManager.LoadRaceData(splitContent[0]);
#ifdef _DEBUG
					TemSocket::SendSocketMessage("GETGHOSTS" + TemSocket::MD + raceManager.raceName);
#endif
					if (raceManager.StartPosition.IsSet() && raceManager.FinishPosition.IsSet())
					{
						auto scenes = TemSceneHelper::GetScenesAtPosition(raceManager.StartPosition);
						auto scenes1 = TemSceneHelper::GetScenesAtPosition(raceManager.FinishPosition);

						if (scenes.size() > 0 && scenes1.size() > 0)
						{
							std::vector<TemSceneNode> scenesFound = TemSceneHelper::GetScenePathByName(sutil::convert_csstring(scenes[0]->fields.Scene), sutil::convert_csstring(scenes1[0]->fields.Scene));
							std::vector<app::RuntimeSceneMetaData*> scenesToLoad = TemSceneHelper::GetScenesByTemSceneNode(scenesFound);

							app::RuntimeSceneMetaData* raceScene = TemSceneHelper::GetSceneByName("inkwaterMarshRaceSetups");
							TemSceneHelper::LoadScenes(std::vector<app::RuntimeSceneMetaData*> {raceScene});

							TemSceneHelper::LoadScenes(scenesToLoad);
							MessagesManager.MessagesFutures[message.second.Type] = std::async(TemSceneHelper::IsScenesLoaded, scenesToLoad, true);
							MessagesManager.SetTimeout(15 * 1000, message.second.Type);
							message.second.Timeout = 15 * 1000;
							//MessagesManager.Messages[i].Timeout = 15 * 1000;
							futureExists = true;
						}
					}
					else
					{
						MessagesManager.RemoveMessage(message.second.Type);
						//MessagesManager.Messages.erase(MessagesManager.Messages.begin() + i);
						//MessagesManager.CurrentMessagesType.erase(MessagesManager.CurrentMessagesType.begin() + i);
						//i--;
						continue;
					}
				}
				else
				{
					auto value = MessagesManager.MessagesFutures[message.second.Type].get();

					if (value == true)
					{
						MessagesManager.RemoveMessage(message.second.Type);
						MessagesManager.MessagesFutures.erase(message.second.Type);
						futureExists = false;
						raceManager.IsRaceLoaded = true;
					}
				}
			}
			break;

			case MessageType::KuDash:
			{
				if (kuRide != nullptr && kuRide->fields.Abilities->fields.Dash != nullptr)
					app::KuDash_TryPerformDash(kuRide->fields.Abilities->fields.Dash, NULL);
			}
			break;

			case MessageType::UpdateRaceCheckpoint:
			{
				if (message.second.Content.size() > 3)
				{
					auto splitContent = sutil::SplitTem(message.second.Content, "|");
					tem::Vector3 position = splitContent[0];
					tem::Vector3 scale = splitContent[1];
					scale.Z = 1.0f;
					position.X = position.X - (scale.X * -1);
					position.Y = position.Y;// -scale.Y;
					int index = std::stoi(splitContent[2]);
					raceManager.UpdateCheckpoint(position, scale, index);
				}
			}
			break;

			case MessageType::SetManagerPath:
			{
				managerPath = message.second.Content;
				ManagerPath = managerPath;
				raceManager.racePath = managerPath + "\\RaceSettings\\";
			}
			break;

			case MessageType::ToggleDebugObjects:
			{
				DebugDrawer::toggleDebugObjects = !DebugDrawer::toggleDebugObjects;
				DebugDrawer::ToggleDebugObjects();
			}
			break;

			case MessageType::UpdateHitbox:
			{
				auto splitContent = sutil::SplitTem(message.second.Content, "|");
				tem::Vector3 position = splitContent[0];
				tem::Vector3 scale = splitContent[1];
				position.X = position.X - (scale.X * -1);
				position.Y = position.Y - scale.Y;

				if (HitboxDebug == nullptr)
				{
					HitboxDebug = debugDrawer.CreateDebugObjectDetached(GraphColors::Blue, position, scale);
					TransformSetScale(HitboxDebug, tem::Vector3(scale.X, scale.Y, 1));
					TransformSetLocalPosition(HitboxDebug, tem::Vector3(scale.X / 2 * -1, scale.Y / 2, 0));
					TransformSetPosition(HitboxDebug, position);
				}
				else
				{
					TransformSetScale(HitboxDebug, tem::Vector3(scale.X, scale.Y, 1));
					TransformSetPosition(HitboxDebug, position);
				}
			}
			break;

			case MessageType::RemoveHitbox:
			{
				if (HitboxDebug != nullptr)
				{
					app::Object_1_Destroy_1((app::Object_1*)HitboxDebug, NULL);
					HitboxDebug = nullptr;
				}
			}
			break;

			case MessageType::RestartRace:
			{
				raceManager.RestartRace();
			}
			break;

			case MessageType::StopRace:
			{
				if (futureIsReady == false)
				{
					auto scenes = TemSceneHelper::GetScenesAtPosition(raceManager.StartPosition);
					auto scenes1 = TemSceneHelper::GetScenesAtPosition(raceManager.FinishPosition);

					if (scenes.size() > 0 && scenes1.size() > 0) {
						std::vector<TemSceneNode> scenesFound = TemSceneHelper::GetScenePathByName(sutil::convert_csstring(scenes[0]->fields.Scene), sutil::convert_csstring(scenes1[0]->fields.Scene));
						std::vector<app::RuntimeSceneMetaData*> scenesToLoad = TemSceneHelper::GetScenesByTemSceneNode(scenesFound);
					}

					raceManager.StopRace();

					MessagesManager.MessagesFutures[message.second.Type] = std::async(RaceManager::HasRaceStopped);
					MessagesManager.SetTimeout(15 * 1000, message.second.Type);
					message.second.Timeout = 15 * 1000;
					//MessagesManager.Messages[i].Timeout = 15 * 1000;
					futureExists = true;
				}
				else
				{
					auto value = MessagesManager.MessagesFutures[message.second.Type].get();

					if (value == true)
					{
						MDV::MessageToWrite.push_back("STOPPEDRACE");
						MessagesManager.RemoveMessage(message.second.Type);
						MessagesManager.MessagesFutures.erase(message.second.Type);
						//MessagesManager.MessagesFutures.erase(i);
						futureExists = false;
						raceManager.IsRaceLoaded = true;
					}
				}
			}
			break;

			case MessageType::SaveUberStates:
			{
				UberStateManager::SaveUberStates(raceManager.racePath + raceManager.raceName + ".uberstates");
			}
			break;

			case MessageType::LoadUberStates:
			{
				UberStateManager::LoadUberStates(raceManager.racePath + raceManager.raceName + ".uberstates");
			}
			break;

			case MessageType::SetSeinPosition:
			{
				tem::Vector3 position = message.second.Content;
				app::CharacterPlatformMovement_TeleportAndPlaceOnGround(MDV::MoonSein->fields.PlatformBehaviour->fields.PlatformMovement, position.ToMoon(), 0.01f, 0.01f, NULL);
				app::GameplayCamera_MoveCameraToTargetInstantly(MDV::SeinGameplayCamera, true, NULL);
			}
			break;

			case MessageType::CreateBackupSave:
			{
				app::SaveFileInfo* saveInfo = app::SaveGameController_get_CurrentSaveFileInfo(MDV::MoonGameController->fields.SaveGameController, NULL);
				int saveIndex = std::max<int>(0, std::min<int>(9, std::stoi(message.second.Content)));
				app::SaveGameController_SaveToFile(MDV::MoonGameController->fields.SaveGameController, saveInfo->fields.m_slotIndex, saveIndex, app::UberStateController_get_CurrentStateValueStore(NULL), true, true, NULL);
			}
			break;

			case MessageType::GetSaveInfo:
			{
				if (futureIsReady == false)
				{
					app::SaveFileInfo* saveInfo = app::SaveGameController_get_CurrentSaveFileInfo(MDV::MoonGameController->fields.SaveGameController, NULL);
					app::SaveSlotBackup* backupSaves = app::SaveSlotBackupsManager_SaveSlotBackupAtIndex(saveInfo->fields.m_slotIndex, NULL);

					int count = backupSaves->fields.Count;// app::SaveSlotBackupsManager__TypeInfo->static_fields->m_instance->fields.m_saveSlotBackups->fields._size;
					app::SaveSlotBackupsManager_ClearCache(app::SaveSlotBackupsManager__TypeInfo->static_fields->m_instance, NULL);
					app::SaveSlotBackupsManager_RequestReadBackups(saveInfo->fields.m_slotIndex, NULL);
					MessagesManager.MessagesFutures[message.second.Type] = std::async(SavesHelper::IsBackupsLoaded, count, saveInfo->fields.m_slotIndex);
					MessagesManager.SetTimeout(15 * 1000, message.second.Type);
					message.second.Timeout = 15 * 1000;
					futureExists = true;
				}
				else
				{
					auto value = MessagesManager.MessagesFutures[message.second.Type].get();

					if (value == true)
					{
						MessagesManager.RemoveMessage(message.second.Type);
						MessagesManager.MessagesFutures.erase(message.second.Type);
						futureExists = false;
						raceManager.IsRaceLoaded = true;

						app::SaveFileInfo* saveInfo = app::SaveGameController_get_CurrentSaveFileInfo(MDV::MoonGameController->fields.SaveGameController, NULL);
						app::SaveSlotBackup* backupSaves = app::SaveSlotBackupsManager_SaveSlotBackupAtIndex(saveInfo->fields.m_slotIndex, NULL);
						std::vector<app::SaveSlotBackupInfo*> backupsaves;
						std::string backupsaveInfo = "SAVEINFO";

						for (int i = 0; i < backupSaves->fields.Count; i++)
						{
							app::SaveSlotBackupInfo* backupsave = backupSaves->fields.SaveSlotInfos->vector[i];
							backupsaveInfo += sutil::convert_csstring(backupsave->fields.SaveSlotInfo->fields.AreaName) + ";" + std::to_string(backupsave->fields.SaveSlotInfo->fields.Completion) + ";";
							backupsaveInfo += std::to_string(backupsave->fields.SaveSlotInfo->fields.Health) + "/" + std::to_string(backupsave->fields.SaveSlotInfo->fields.MaxHealth) + ";";
							backupsaveInfo += std::to_string(backupsave->fields.SaveSlotInfo->fields.Energy) + "/" + std::to_string(backupsave->fields.SaveSlotInfo->fields.MaxEnergy) + ";";
							backupsaveInfo += std::to_string(backupsave->fields.SaveSlotInfo->fields.Order) + ";" + std::to_string(backupsave->fields.SaveSlotInfo->fields.Difficulty) + ";";
							backupsaveInfo += std::to_string(backupsave->fields.SaveSlotInfo->fields.Hours) + ":" + std::to_string(backupsave->fields.SaveSlotInfo->fields.Minutes) + ":" + std::to_string(backupsave->fields.SaveSlotInfo->fields.Seconds) + ";";
							backupsaveInfo += std::to_string(backupsave->fields.SaveSlotInfo->fields.DebugOn) + ";" + std::to_string(backupsave->fields.SaveSlotInfo->fields.WasKilled) + ";" + std::to_string(backupsave->fields.Index) + ";";

							backupsaves.push_back(backupsave);
						}

						MDV::MessageToWrite.push_back(backupsaveInfo);
					}
				}
			}
			break;

			}

			if (futureExists == false)
			{
				MessagesManager.RemoveMessage(message.second.Type);
				//MessagesManager.Messages.erase(MessagesManager.Messages.begin() + i);
				//MessagesManager.CurrentMessagesType.erase(MessagesManager.CurrentMessagesType.begin() + i);
				//i--;
			}
		}
		MessagesManager.PullMessages();
	}

	MDV::CanCallMethods = false;
	TemSceneHelper::CanCallMethods = false;
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

void __fastcall My_SeinOnKill(void* __this, int edx)
{
	if (raceManager.IsRacing == false)
	{
		Real_SeinOnKill(__this);
	}
	else
	{
		raceManager.RestartRace();
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

	MDV::MoonGameWorld = app::GameWorld__TypeInfo->static_fields->Instance;// GetGameWorld(hProcess);
	MDV::MoonGameController = app::GameController__TypeInfo->static_fields->Instance; // GetGameController(hProcess);
	MDV::SeinGameplayCamera = (app::GameplayCamera*)GetComponentByTypeInChildren(MDV::MoonGameController->fields.m_systemsGameObject, "", "GameplayCamera");
	MDV::MoonSein = app::Characters_get_Sein(NULL);// GetSeinCharacter(hProcess);
	MDV::SeinPlayAnimationController = MDV::MoonSein->fields.Controller->fields.m_playAnimationController;
	MDV::AreaMapUI = app::AreaMapUI__TypeInfo->static_fields->Instance;
	std::vector<std::string> messages;

	//initalize detours
	/* For finding CClassFunction
	mov qword ptr [r11-38],FFFFFFFFFFFFFFFE
	mov [r11+08],rbx
	mov [r11+10],rsi
	movaps [rsp+40],xmm6
	mov rbx,rcx
	xor esi,esi
	*/
	Real_CClassFunction = CClassFunction_t(Assembly_BaseAddr + 0x6920c0);// +0x994520);
	Real_MoonDriverSystem = tMoonDriverSystem(Assembly_BaseAddr + 0xE463C0);
	/* For finding GameAssembly.il2cpp_string_new <- goto adress subtract gameassembly.dll location
	mov rdx,FFFFFFFFFFFFFFFF
	inc rdx
	cmp byte ptr [rcx+rdx],00
	jne 7FFD7B303B57
	*/
	RealIl2cpp_string_new_wrapper = tIl2CppString(Assembly_BaseAddr + 0x279570);// 0x263B50);
	Real_SeinOnKill = tSeinOnKill(Assembly_BaseAddr + 0x01F2B430);
	Real_GameControllerUpdate = tGameControllerUpdate(UnityPlayer_BaseAddress + 0x5f0350); //0x994040 gc -  0xA77FA0 sein
	Real_OnPointerClick = tOnPointerClick(Assembly_BaseAddr + 0x1F2B430);

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)Real_CClassFunction, Mine_CClassFunction);

#if defined(IL2CPP)
	DetourAttach(&(PVOID&)Real_MoonDriverSystem, Mine_MoonDriverSystem);
	DetourAttach(&(PVOID&)RealIl2cpp_string_new_wrapper, string_new);
	DetourAttach(&(PVOID&)Real_OnPointerClick, My_OnPointerClick);
	DetourAttach(&(PVOID&)Real_SeinOnKill, My_SeinOnKill);
#endif

	//DetourAttach(&(PVOID&)Real_GameControllerUpdate, My_GameControllerUpdate);
	LONG lError = DetourTransactionCommit();

	ProgramStart = std::chrono::high_resolution_clock::now();

#if defined(IL2CPP)

	/*app::Type* kuType = GetType("", "Ku");
	app::Object_1__Array* kuArr = app::Object_1_FindObjectsOfTypeAll(kuType, NULL);

	if (kuArr != nullptr && kuArr->vector[0] != nullptr && kuRide->fields.Abilities != nullptr)
	{
		kuRide = (app::Ku*)kuArr->vector[0];
		kuRide->fields.Abilities->fields.Dash->fields._.m_isActive = true;
		kuRide->fields.Abilities->fields.MeditateSpell->fields._.m_isActive = true;
	}*/

#endif
	fileHandle = CreateFileA("\\\\.\\pipe\\wotw-manager-pipe", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	const char* msg = "\r\n";
	WriteFile(fileHandle, msg, (DWORD)strlen(msg), nullptr, 0);

	std::string managerExeName = "LiveSplit.OriWotW.exe";
	DWORD proccessID = FindProcessId(managerExeName);
	char* buffer = new char[512];

#ifdef _DEBUG
	TemSocket::ConnectToServer("HELLO SERVER");
	TemSocket::SendSocketMessage("HELLO AGAIN");
#endif

	while (loopBool && IsProcessRunning(proccessID))
	{

		buffer[512];
		memset(buffer, 0, 512);
		ReadString(buffer);

		if ((buffer != NULL) && (buffer[0] == '\0'))
		{

		}
		else
		{
			IsWritingToMessageString = true;
			std::string message(buffer);

			if (message.find("CALL") != std::string::npos)
			{
				messages.clear();

				if (message.find("||") != std::string::npos)
				{
					auto tempMM = sutil::SplitTem(message, "||");
					messages.insert(messages.end(), tempMM.begin(), tempMM.end());
				}
				else
				{
					messages.push_back(message);
				}

				for (auto& message : messages)
				{
					sutil::ReplaceS(message, "CALL", "");
					if (message != "")
					{
						Message newMessage;

						if (message.find("PAR") != std::string::npos)
						{
							auto paramSplit = sutil::SplitTem(message, "PAR");
							if (paramSplit.size() > 1)
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

						if (newMessage.Type == MessageType::FrameStep)
						{
							frameStep.ShouldFrameStep = true;
						}
						if (newMessage.Type == MessageType::FrameStepStop)
						{
							frameStep.State = FrameStepping::FrameSteppingDisabled;
							frameStep.ShouldFrameStep = false;
						}
						if (newMessage.Type == MessageType::NextAnimation)
						{
							if (MANAGER_INITIALIZED == true)
								app::SeinPlayAnimationController_StopAnimation(MDV::SeinPlayAnimationController, NULL);
						}
						if (newMessage.Type == MessageType::GetSeinFaces)
						{
							if (MANAGER_INITIALIZED == true)
							{
								int faces = app::SeinCharacter_get_FacingDirection(MDV::MoonSein, NULL);
								MDV::MessageToWrite.push_back("SEINFACES:" + std::to_string(faces));
							}
						}

						MessagesManager.AddMessage(newMessage);
					}
				}
			}
		}
		IsWritingToMessageString = false;
	}
	frameStep.State = FrameStepping::FrameSteppingDisabled;
	frameStep.ShouldFrameStep = false;

	while (MessagesManager.Messages.size() > 0)
	{
		Sleep(16);
	}
	MessagesManager.Messages.clear();

	//sleep to let game finish and then dettach all the detours
	Sleep(25);
#ifdef _DEBUG
	TemSocket::Exit();
#endif
	graphDrawer.Destroy();
	debugDrawer.CleanUp();
	raceManager.CleanupManager();

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&(PVOID&)Real_CClassFunction, Mine_CClassFunction);

#if defined(IL2CPP)
	DetourDetach(&(PVOID&)Real_MoonDriverSystem, Mine_MoonDriverSystem);
	DetourDetach(&(PVOID&)RealIl2cpp_string_new_wrapper, string_new);
	DetourDetach(&(PVOID&)Real_OnPointerClick, My_OnPointerClick);
	DetourDetach(&(PVOID&)Real_SeinOnKill, My_SeinOnKill);
#endif

	//DetourDetach(&(PVOID&)Real_GameControllerUpdate, My_GameControllerUpdate);
	DetourTransactionCommit();

	CloseHandle(fileHandle);
	CloseHandle(fileHandleWrite);

	//sleep again to let the game cleanly return to it's own loops
	Sleep(25);
	FreeLibraryAndExitThread(hIns, 0);
	return 0;
}

DWORD WINAPI ThreadWrite(HMODULE hIns)
{
	pid = GetCurrentProcessId();
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, 1, pid);

	fileHandleWrite = CreateFileA("\\\\.\\pipe\\injectdll-manager-pipe", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

	std::string managerExeName = "LiveSplit.OriWotW.exe";
	std::string messageToSend = "";
	DWORD proccessID = FindProcessId(managerExeName);

	while (loopBool && IsProcessRunning(proccessID))
	{
		if (IsWritingToMessageString == false && MDV::MessageToWrite.size() > 0)
		{
			messageToSend = "";
			while (MDV::MessageToWrite.size() > 0)
			{
				messageToSend += MDV::MessageToWrite[0] + "||";
				MDV::MessageToWrite.erase(MDV::MessageToWrite.begin());
			}
			messageToSend += "\r\n";

			WriteFile(fileHandleWrite, messageToSend.c_str(), (DWORD)strlen(messageToSend.c_str()), nullptr, 0);
		}
		else
		{
			const char* msg = "\r\n";
			WriteFile(fileHandleWrite, msg, (DWORD)strlen(msg), nullptr, 0);
		}
		Sleep(7);
	}

	return 0;
}