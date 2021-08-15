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
#include <filesystem>

#define IL2CPP true
#define WOTWMODDING false

//app::Array_Resize_35();

//il2cpp generated
#include "il2cpp-appdata.h"
#include "helpers.h"

extern const LPCWSTR LOG_FILE = L"il2cpp-log.txt";

#include "Tem.h"
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
#include "SeinVisualEditor.h"
#include "SimpleJson.h"
#include "Component.h"
#include "SceneObject.h"
#include "SceneHierarchy.h"
#include "SceneList.h"
#include "ObjectCreator.h"
#include "ScenesJSON.h"
#include "FrameworkJSON.h"
#include "CollisionCreator.h"
#include "Gizmo.h"
#include "UIEvents.h"

static int MANAGER_INITIALIZED = -1;
static bool WRITE_THREAD_EXITED = false;
static bool EXITING_THREAD = false;
static bool READ_THREAD_DONE = false;
static bool HAS_LOADED_WORLD = false;

bool flipFlopTest = false;

MessageManager MessagesManager;
AreaMapManager areaMapManager;
Graph graphDrawerDebug;
RaceManager raceManager = RaceManager();

unsigned long long totalFrames = 0;

std::chrono::high_resolution_clock::time_point ProgramStart = std::chrono::high_resolution_clock::now();
std::chrono::high_resolution_clock::time_point LastTime;

app::Ku* kuRide = nullptr;
app::MoonGuid* willowPowlBackgroundGUID = nullptr;
app::GameObject* HitboxDebug = nullptr;

FrameStep frameStep;
bool loopBool = true;
bool IsWritingToMessageString = false;

HANDLE fileHandle;
HANDLE fileHandleWrite;
DWORD pid;
HANDLE hProcess;
std::string managerPath = "";

std::future<bool> HasLoadedScenes;
std::future<bool> HasLoadedWorldData;
bool SetupsAreDone = false;
std::chrono::milliseconds span(1);

app::String* string_new(const char* str)
{
	return RealIl2cpp_string_new_wrapper(str);
}

void InitializeDLL()
{
	if (app::Graphic_CrossFadeColor == nullptr && app::Graphic_CrossFadeColor_1 == nullptr && (*app::List_1_UnityEngine_Collider__Add__MethodInfo) == nullptr ||
		(*app::AreaMapUI__TypeInfo) == nullptr || (*app::GameWorld__TypeInfo) == nullptr || (*app::GameWorld__TypeInfo)->static_fields->Instance == nullptr)
		return;

	MANAGER_INITIALIZED = 0;
	Il2CppClass* assemblyClass = GetClass("System.Reflection", "Assembly");
	tem::LOWPTRVALUE = ((std::uintptr_t)assemblyClass->image) - 2199999999;
	tem::HIGHPTRVALUE = ((std::uintptr_t)assemblyClass->image) + 2791794593265;

	MDV::MoonGameWorld = (*app::GameWorld__TypeInfo)->static_fields->Instance;// GetGameWorld(hProcess);
	MDV::MoonGameController = (*app::GameController__TypeInfo)->static_fields->Instance; // GetGameController(hProcess);
	MDV::MoonCamera = (app::Camera*)GetComponentByTypeInChildren(MDV::MoonGameController->fields.m_systemsGameObject, "UnityEngine", "Camera");
	MDV::SeinGameplayCamera = (app::GameplayCamera*)GetComponentByTypeInChildren(MDV::MoonGameController->fields.m_systemsGameObject, "", "GameplayCamera");
	MDV::MoonSein = app::Characters_get_Sein(NULL);// GetSeinCharacter(hProcess);
	MDV::SeinPlayAnimationController = MDV::MoonSein->fields.Controller->fields.m_playAnimationController;
	MDV::AreaMapUI = (*app::AreaMapUI__TypeInfo)->static_fields->Instance;

	auto rectClass = GetClass<>("UnityEngine", "Rect");
	il2cpp_runtime_class_init((Il2CppClass*)rectClass);

	sceneManager = (*app::Scenes__TypeInfo)->static_fields->Manager;
	TemSceneHelper::SceneManager = sceneManager;

	(*app::SavePedestal__TypeInfo)->static_fields->All->fields._items->vector[0];

#if WOTWMODDING == true
	tem::UIEvents::Instance = new tem::UIEvents();
	tem::Gizmo::Instance.SetupGizmo();
	MDV::AllObjectsToCallUpdate.push_back(&tem::Gizmo::Instance);
	tem::CollisionCreator::Instance = tem::CollisionCreator();
	tem::CollisionCreator::Instance.AddCollisionToolbar();
	MDV::AllObjectsToCallUpdate.push_back(&tem::CollisionCreator::Instance);
#endif

	for (int i = 0; i < 6; i++)
	{
		switch (TemSceneHelper::SceneManager->fields.m_behaviours->vector[i]->klass->_0.byval_arg.data.klassIndex)
		{
			case 14927:TemSceneHelper::BehaviourCinematic = reinterpret_cast<app::ScenesManagerBehaviourCinematic*>(TemSceneHelper::SceneManager->fields.m_behaviours->vector[i]); break;
			case 14928:TemSceneHelper::BehaviourExplicit = reinterpret_cast<app::ScenesManagerBehaviourExplicit*>(TemSceneHelper::SceneManager->fields.m_behaviours->vector[i]); break;
			case 14929:TemSceneHelper::BehaviourGameplay = reinterpret_cast<app::ScenesManagerBehaviourGameplay*>(TemSceneHelper::SceneManager->fields.m_behaviours->vector[i]); break;
			case 14930:TemSceneHelper::BehaviourLegacy = reinterpret_cast<app::ScenesManagerBehaviourLegacy*>(TemSceneHelper::SceneManager->fields.m_behaviours->vector[i]); break;
			case 14931:TemSceneHelper::BehaviourStatic = reinterpret_cast<app::ScenesManagerBehaviourStatic*>(TemSceneHelper::SceneManager->fields.m_behaviours->vector[i]); break;
			case 14932:TemSceneHelper::BehaviourUtility = reinterpret_cast<app::ScenesManagerBehaviourUtility*>(TemSceneHelper::SceneManager->fields.m_behaviours->vector[i]); break;
		}
	}

	GraphColors::Initialize();

	for (int i = 0; i < sceneManager->fields.AllScenes->fields._size; i++)
	{
		std::string sceneName = il2cppi_to_string(sceneManager->fields.AllScenes->fields._items->vector[i]->fields.Scene);
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

	DebugDrawer::Instance.Initialize();
	MDV::AllObjectsToCallUpdate.push_back(&DebugDrawer::Instance);

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
				std::string nameS = il2cppi_to_string(name);

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

	app::Vector3__Boxed* myVector3 = (app::Vector3__Boxed*)il2cpp_object_new((Il2CppClass*)(*app::Vector3__TypeInfo));
	app::Vector3__ctor(myVector3, -612.0f, -4318.0f, 0.0f, NULL);

	auto scenes = TemSceneHelper::GetScenesAtPosition(myVector3->fields);
	app::RuntimeSceneMetaData* raceScene = TemSceneHelper::GetSceneByName("inkwaterMarshRaceSetups");

	scenes.push_back(raceScene);
	TemSceneHelper::LoadScenes(scenes);
	HasLoadedScenes = std::async(TemSceneHelper::IsScenesLoaded, scenes, false);
	//MDV::User.Initialize();

	app::SimpleFPS* simpleFPS = (*app::SimpleFPS__TypeInfo)->static_fields->Instance;
	app::Behaviour_set_enabled((app::Behaviour*)simpleFPS, false, NULL);

	app::PlayerInput* playerInput = (*app::PlayerInput__TypeInfo)->static_fields->Instance;

	/*app::List_1_Moon_Timeline_MoonTimeline_* allTimelines = (*app::MoonTimeline__TypeInfo)->static_fields->All;
	
	for (int i = 0; i < allTimelines->fields._size; i++)
	{
		app::TimelineEntity_StartPlayback((app::TimelineEntity*)allTimelines->fields._items->vector[i], NULL);
	}*/

	//UberStateManager::AddUberStates(192, 123456, true);

	MANAGER_INITIALIZED = 1;
}

void __fastcall Mine_CClassFunction(void* __this, int edx)
{
	if (MANAGER_INITIALIZED == -1)
	{
		if (READ_THREAD_DONE == true)
			InitializeDLL();
	}
	else
	{
		MDV::CanCallMethods = true;
		TemSceneHelper::CanCallMethods = true;
		MDV::ValidatePointers();

		totalFrames++;
		raceManager.totalFrames = totalFrames;

		if (MANAGER_INITIALIZED == 1 && SetupsAreDone == false && HasLoadedScenes.valid() && HasLoadedScenes.wait_for(span) == std::future_status::ready)
		{
			//app::SceneRoot* sceneRoot = app::ScenesManager_RegisterSceneByName(sceneManager, string_new("Test1234"), false, true, NULL);
			app::RuntimeSceneMetaData* raceScene = TemSceneHelper::GetSceneByName("inkwaterMarshRaceSetups");

			for (int i = 0; i < sceneManager->fields.ActiveScenes->fields._size; i++)
			{
				if (sceneManager->fields.ActiveScenes->fields._items->vector[i]->fields.SceneRoot->fields.m_sceneSettings != nullptr)
				{
					tem::ObjectCreator::SceneCopySettings = sceneManager->fields.ActiveScenes->fields._items->vector[i]->fields.SceneRoot->fields.m_sceneSettings;
					break;
				}
			}

			MDV::MessageToWrite.push_back(std::to_string(static_cast<int>(MessageType::ManagerInitialized)));
			AnimationHelper::GetAnimations();
			raceManager.racePath = managerPath + "\\RaceSettings\\";
			raceManager.SetupManager();
			SetupsAreDone = true;

			//app::ScenesManager* scenesManager = (*app::Scenes__TypeInfo)->static_fields->Manager;
			//app::ScenesManager_PreloadScene(scenesManager, MyTestScene->fields.MetaData, NULL);

			/*std::vector<std::string> scenePath = { "interactibles", "savePedestal" };
			app::GameObject* foundObject = GetComponentByScenePath("kwoloksCavernSaveRoomA", scenePath);
			app::SavePedestal* savePedestalObject = (app::SavePedestal*)app::Object_1_Instantiate_2((app::Object_1*)foundObject, NULL);
			//app::GameObject__ctor(savePedestalObject, string_new("TestPort"), NULL);

			//app::SavePedestal* savePedestal = (app::SavePedestal*)GetComponentByType(savePedestalObject, "", "SavePedestal");
			app::SavePedestal__ctor(savePedestalObject, NULL);
			TransformSetPosition((app::GameObject*)savePedestalObject, MDV::MoonSein->fields.PlatformBehaviour->fields.PlatformMovement->fields.m_oldPosition);*/
		}

#if WOTWMODDING == true
		if (HAS_LOADED_WORLD == false && HasLoadedWorldData.valid() && HasLoadedWorldData.wait_for(span) == std::future_status::ready)
		{
			HAS_LOADED_WORLD = true;
			tem::SceneList::SetLoadedHierarchyData();
		}
#endif

		if (SetupsAreDone == true)
		{
			for (int i = 0; i < MDV::AllObjectsToCallUpdate.size(); i++)
			{
				if (MDV::AllObjectsToCallUpdate[i] != nullptr)
				{
					Global* object = MDV::AllObjectsToCallUpdate[i];
					if (object != nullptr)
						object->Update(); //something weird is occuring that breaks pausing
				}
			}
		}

		LastTime = std::chrono::high_resolution_clock::now();
		std::chrono::milliseconds timeSpan = std::chrono::duration_cast<std::chrono::milliseconds>(LastTime - ProgramStart);
		ProgramStart = LastTime;

		app::Dictionary_2_SmartInput_IButtonInput_Core_Input_InputButtonProcessor_* inputs = (*app::PlayerInput__TypeInfo)->static_fields->Instance->fields.m_InputProcessorPairs;

		for (int i = 0; i < inputs->fields.count; i++)
		{
			//inputs->fields.entries->vector[i].value->fields.IsPressed = flipFlopTest;
			//inputs->fields.entries->vector[i].value->fields.WasPressed = !flipFlopTest;
			//app::Input_InputButtonProcessor_Update(inputs->fields.entries->vector[i].value, flipFlopTest, NULL);
		}

		flipFlopTest = !flipFlopTest;

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

				case MessageType::CreateCheckpoint:
				{
					tCreateCheckpoint oCreateCheckpoint = tCreateCheckpoint(Assembly_BaseAddr + 0x997230);
					if (oCreateCheckpoint != nullptr) {

						if (MDV::MoonGameController != nullptr)
							app::GameController_CreateCheckpointWithSave(MDV::MoonGameController, NULL); // oCreateCheckpoint(pGameController);
					}
				}
				break;

				case MessageType::CreateObject: raceManager.TemGhostRecorder.CreateRecorder(); raceManager.TemGhostRecorder.StartRecorder(); break;
				case MessageType::StopRecorder: raceManager.TemGhostRecorder.StopRecorder(); break;
				case MessageType::WriteRecorder: raceManager.TemGhostRecorder.WriteRecorder(sutil::ReplaceSR(sutil::getexepath(), "oriwotw.exe", "oriwotw_Data\\output\\ghosts\\test.ghost"));  break;
				case MessageType::GhostPlayerRun: GhostHandler::CreateGhostPublic(sutil::ReplaceSR(sutil::getexepath(), "oriwotw.exe", "oriwotw_Data\\output\\ghosts\\test.ghost")); raceManager.startedWeRacing = totalFrames; break;

				case MessageType::EndThread:
				{
#ifdef TEMSOCKET
					TemSocket::IsConnected = false;
#endif
					SeinCharacterHelper::RestoreSeinAbilities();
					GhostHandler::Instance.Cleanup();
					loopBool = false;
				}
				break;

				case MessageType::FrameStep: frameStep.State = FrameStepping::FrameSteppingEnabled; break;
				case MessageType::CreateRaceCheckpoint:
				{
					tem::Vector3 position;
					auto sPosition = sutil::SplitTem(message.second.Content, ";");
					position.X = std::stof(sPosition[0]);
					position.Y = std::stof(sPosition[1]);
					position.Z = 0;
					DebugDrawer::Instance.SetupTexture(GraphColors::Orange, position);
				}
				break;

				case MessageType::CreateScene: 
				{
					if (tem::ObjectCreator::temScene1RuntimeMetaData == nullptr)
					{
						auto values = sutil::SplitTem(message.second.Content, "|");
						tem::SceneList::RootSceneData = tem::SceneData(values[0], tem::Vector3(values[1]), tem::Vector2(values[2]), tem::Rect(values[3]));
						tem::SceneList::RootSceneData.LoadScene();
					}
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
#ifdef TEMSOCKET
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

				case MessageType::RemoveCheckpoint: raceManager.RemoveCheckpoint(std::stoi(message.second.Content)); break;
				case MessageType::LoadRace:
				{
					if (futureIsReady == false)
					{
						auto splitContent = sutil::SplitTem(message.second.Content, "|");
						DebugDrawer::Instance.toggleDebugObjects = splitContent[1] == "False" ? false : true;
						raceManager.LoadRaceData(splitContent[0]);
#ifdef TEMSOCKET
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

				case MessageType::KuDash: if (kuRide != nullptr && kuRide->fields.Abilities->fields.Dash != nullptr) { app::KuDash_TryPerformDash(kuRide->fields.Abilities->fields.Dash, NULL); } break;

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

				case MessageType::SetManagerPath: ManagerPath = managerPath = message.second.Content; raceManager.racePath = managerPath + "\\RaceSettings\\"; break;

				case MessageType::ToggleDebugObjects: DebugDrawer::Instance.toggleDebugObjects = !DebugDrawer::Instance.toggleDebugObjects; DebugDrawer::Instance.ToggleDebugObjects(); break;

				case MessageType::UpdateHitbox:
				{
					auto splitContent = sutil::SplitTem(message.second.Content, "|");
					tem::Vector4 values = splitContent[0];
					tem::Vector2 scale = tem::Vector2(values.Z, values.A);
					values.X = values.X - (scale.x * -1);
					values.Y = values.Y - scale.y;

					if (HitboxDebug == nullptr)
					{
						HitboxDebug = DebugDrawer::Instance.CreateDebugObjectDetached(GraphColors::Blue, tem::Vector2(values.X, values.Y), tem::Vector2(values.Z, values.A));

						if (tem::PtrInRange(HitboxDebug) == true)
						{
							TransformSetScale(HitboxDebug, tem::Vector3(scale.x, scale.y, 1.0f));
							TransformSetLocalPosition(HitboxDebug, tem::Vector3(scale.x / 2.0f * -1.0f, scale.y / 2.0f, 0.0f));
							TransformSetPosition(HitboxDebug, values);
						}
					}
					else
					{
						TransformSetScale(HitboxDebug, tem::Vector3(scale.x, scale.x, 1.0f));
						TransformSetPosition(HitboxDebug, values);
					}
				}
				break;

				case MessageType::RemoveHitbox: if (HitboxDebug != nullptr) { app::Object_1_Destroy_1((app::Object_1*)HitboxDebug, NULL); HitboxDebug = nullptr; } break;

				case MessageType::RestartRace: raceManager.RestartRace(); break;

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
							MDV::MessageToWrite.push_back(std::to_string(static_cast<int>(MessageType::StoppedRace)));
							MessagesManager.RemoveMessage(message.second.Type);
							MessagesManager.MessagesFutures.erase(message.second.Type);
							//MessagesManager.MessagesFutures.erase(i);
							futureExists = false;
							raceManager.IsRaceLoaded = true;
						}
					}
				}
				break;

				case MessageType::SaveUberStates: UberStateManager::SaveUberStates(raceManager.racePath + raceManager.raceName + ".uberstates"); break;

				case MessageType::LoadUberStates: UberStateManager::LoadUberStates(raceManager.racePath + raceManager.raceName + ".uberstates"); break;

				case MessageType::SetSeinPosition:
				{
					tem::Vector3 position = message.second.Content;
					app::CharacterPlatformMovement_TeleportAndPlaceOnGround(MDV::MoonSein->fields.PlatformBehaviour->fields.PlatformMovement, position.ToMoon(), 0.01f, 0.01f, NULL);
					app::GameplayCamera_MoveCameraToTargetInstantly(MDV::SeinGameplayCamera, true, NULL);
				}
				break;

				case MessageType::RefreshBackups:
				{
					app::SaveFileInfo* saveInfo = app::SaveGameController_get_CurrentSaveFileInfo(MDV::MoonGameController->fields.SaveGameController, NULL);
					int saveIndex = std::max<int>(0, std::min<int>(9, std::stoi(message.second.Content)));
					app::SaveSlotBackupsManager_RequestReadBackups(saveInfo->fields.m_slotIndex, NULL);
					app::SaveGameController_Refresh(MDV::MoonGameController->fields.SaveGameController, NULL);
				}
				break;

				case MessageType::CreateBackupSave:
				{
					app::SaveFileInfo* saveInfo = app::SaveGameController_get_CurrentSaveFileInfo(MDV::MoonGameController->fields.SaveGameController, NULL);
					int saveIndex = std::max<int>(0, std::min<int>(9, std::stoi(message.second.Content)));
					app::SaveGameController_SaveToFile(MDV::MoonGameController->fields.SaveGameController, saveInfo->fields.m_slotIndex, saveIndex, app::UberStateController_get_CurrentStateValueStore(NULL), false, false, NULL);
					Message refreshBackupsMessage;
					refreshBackupsMessage.Content = message.second.Content;
					refreshBackupsMessage.Type = MessageType::RefreshBackups;
					refreshBackupsMessage.TypeInt = (int)MessageType::RefreshBackups;
					MessagesManager.AddMessage(refreshBackupsMessage);
				}
				break;

				case MessageType::GetSaveInfo:
				{
					if (futureIsReady == false)
					{
						app::SaveFileInfo* saveInfo = app::SaveGameController_get_CurrentSaveFileInfo(MDV::MoonGameController->fields.SaveGameController, NULL);
						app::SaveSlotBackup* backupSaves = app::SaveSlotBackupsManager_SaveSlotBackupAtIndex(saveInfo->fields.m_slotIndex, NULL);

						int count = backupSaves->fields.Count;
						app::SaveSlotBackupsManager_ClearCache((*app::SaveSlotBackupsManager__TypeInfo)->static_fields->m_instance, NULL);
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
							std::string backupsaveInfo = "";

							for (int i = 0; i < backupSaves->fields.Count; i++)
							{
								app::SaveSlotBackupInfo* backupsave = backupSaves->fields.SaveSlotInfos->vector[i];
								app::SaveFileInfo* backupSaveInfo = app::SaveGameController_GetSaveFileInfo(MDV::MoonGameController->fields.SaveGameController, saveInfo->fields.m_slotIndex, backupsave->fields.Index, NULL);
								backupsaveInfo += sutil::convert_csstring(backupsave->fields.SaveSlotInfo->fields.AreaName) + ";" + std::to_string(backupsave->fields.SaveSlotInfo->fields.Completion) + ";";
								backupsaveInfo += std::to_string(backupsave->fields.SaveSlotInfo->fields.Health) + "/" + std::to_string(backupsave->fields.SaveSlotInfo->fields.MaxHealth) + ";";
								backupsaveInfo += std::to_string(backupsave->fields.SaveSlotInfo->fields.Energy) + "/" + std::to_string(backupsave->fields.SaveSlotInfo->fields.MaxEnergy) + ";";
								backupsaveInfo += std::to_string(backupsave->fields.SaveSlotInfo->fields.Order) + ";" + std::to_string(backupsave->fields.SaveSlotInfo->fields.Difficulty) + ";";
								backupsaveInfo += std::to_string(backupsave->fields.SaveSlotInfo->fields.Hours) + ":" + std::to_string(backupsave->fields.SaveSlotInfo->fields.Minutes) + ":" + std::to_string(backupsave->fields.SaveSlotInfo->fields.Seconds) + ";";
								backupsaveInfo += std::to_string(backupsave->fields.SaveSlotInfo->fields.DebugOn) + ";" + std::to_string(backupsave->fields.SaveSlotInfo->fields.WasKilled) + ";" + std::to_string(backupSaveInfo->fields.m_backupSlotIndex) + ";";

								backupsaves.push_back(backupsave);
							}

							MDV::MessageToWrite.push_back(std::to_string(static_cast<int>(MessageType::GetSaveInfo)) + "|" + backupsaveInfo);
						}
					}
				}
				break;

				case MessageType::SetOriVisuals: SeinVisualEditor::ManagerLoaded = true; SeinVisualEditor::VisualSettingsUpdated.ResetBooleans(); SeinVisualEditor::LoadJsonFile(message.second.Content); SeinVisualEditor::SetAllVisuals(); break;
				case MessageType::ResetOriVisuals: SeinVisualEditor::VisualSettingsUpdated.ResetBooleans(); SeinVisualEditor::ResetAllVisuals(); break;
				
#if WOTWMODDING == true
				case MessageType::GetSceneHierarchy: tem::SceneList::Initialize(); MDV::MessageToWrite.push_back(std::to_string(static_cast<int>(MessageType::GetSceneHierarchy)) + "|" + tem::SceneList::RootHierarchy.ToString()); break;

				case MessageType::SetSelectedGameObject:
				{
					std::vector<int> sceneHierarchy = tem::StringToIntVector(message.second.Content, ",");
					MDV::SelectedObject = tem::SceneList::GetGameObjectFromHierarchyIndex(sceneHierarchy);

					if (MDV::SelectedObject != nullptr)
					{
						app::GameObject_set_moonReady(MDV::SelectedObject, true, NULL);
						app::GameObject_set_active(MDV::SelectedObject, true, NULL);

						tem::SceneList::ActiveHiearchy = tem::SceneList::GetSceneHierarchyPtrFromIndex(sceneHierarchy);
						tem::Gizmo::Instance.SetGizmoPosition(TransformGetPosition(MDV::SelectedObject));

						if (tem::PtrInRange(MDV::PreviewObject) == true && MDV::PreviewObject != MDV::SelectedObject)
						{
							app::Object_1_Destroy_1((app::Object_1*)MDV::PreviewObject, NULL);
							MDV::PreviewObject = nullptr;
						}

						if (app::GameObject_HasComponent(MDV::SelectedObject, GetType("UnityEngine", "MeshRenderer"), NULL) == true && tem::SceneList::SpecialSceneHierarchyIndexMap.find(sceneHierarchy[1]) == tem::SceneList::SpecialSceneHierarchyIndexMap.end())
						{
							MDV::PreviewObject = tem::ObjectCreator::CreateClone(MDV::SelectedObject);
							tem::Vector3 seinPos = app::SeinCharacter_get_Position(MDV::MoonSein, NULL);
							seinPos.Z = TransformGetPosition(MDV::PreviewObject).z;
							TransformSetPosition(MDV::PreviewObject, seinPos);
						}

						MDV::MessageToWrite.push_back(std::to_string(static_cast<int>(MessageType::SetSelectedGameObject)) + "|" + il2cppi_to_string(app::Object_1_get_name((app::Object_1*)MDV::SelectedObject, NULL)));
					}
					else
					{
						tem::SceneList::ActiveHiearchy = nullptr;
						MDV::MessageToWrite.push_back(std::to_string(static_cast<int>(MessageType::SetSelectedGameObject)));
					}
				}
				break;

				case MessageType::MoveGameObjectHierarchy:
				{
					auto messageContent = sutil::SplitTem(message.second.Content, "|");
					std::vector<int> sceneHierarchy1 = tem::StringToIntVector(messageContent[0], ",");
					std::vector<int> sceneHierarchy2 = tem::StringToIntVector(messageContent[1], ",");
					app::GameObject* moving = tem::SceneList::GetGameObjectFromHierarchyIndex(sceneHierarchy1);
					app::GameObject* newParent = tem::SceneList::GetGameObjectFromHierarchyIndex(sceneHierarchy2);

					if (moving != nullptr && newParent != nullptr)
					{
						tem::Vector3 oldPosition = TransformGetPosition(moving);
						TransformSetParent(moving, newParent);
						tem::Vector3 newPosition = tem::Vector3(TransformGetPosition(newParent));
						newPosition.Z = oldPosition.Z;
						TransformSetPosition(moving, newPosition);
						tem::SceneList::MoveHierarchy(tem::SceneList::GetSceneHierarchyPtrFromIndex(sceneHierarchy1), tem::SceneList::GetSceneHierarchyPtrFromIndex(sceneHierarchy2));
					}
				}
				break;

				case MessageType::CloneGameObject:
				{
					std::vector<int> sceneHierarchyIndex = tem::StringToIntVector(message.second.Content, ",");
					tem::SceneHierarchy* clonedParentHierarchy = tem::SceneList::CloneGameObject(sceneHierarchyIndex);

					if (clonedParentHierarchy != nullptr)
						MDV::MessageToWrite.push_back(std::to_string(static_cast<int>(MessageType::CloneGameObject)) + "|" + tem::IntVectorToString(clonedParentHierarchy->Object.SceneIndexHierarchy, ",") + "|" + clonedParentHierarchy->ToString());
				}
				break;

				case MessageType::ExpandSceneHierarchy:
				{
					std::vector<int> sceneHierarchy = tem::StringToIntVector(message.second.Content, ",");
					app::GameObject* foundObject = tem::SceneList::GetGameObjectFromHierarchyIndex(sceneHierarchy);
					if (foundObject != nullptr)
					{
						tem::SceneList::ConstructSceneHierarchy(sceneHierarchy, 2);
						tem::SceneHierarchy* hierarchy = tem::SceneList::GetSceneHierarchyPtrFromIndex(sceneHierarchy);
						MDV::MessageToWrite.push_back(std::to_string(static_cast<int>(MessageType::ExpandSceneHierarchy)) + "|" + message.second.Content + "|" + hierarchy->ToString());
					}
					else if (sceneHierarchy.size() == 1 && sceneHierarchy[0] == 999)
					{
						for (int i = 0; i < TemSceneHelper::SceneManager->fields.ActiveScenes->fields._size; i++)
						{
							if (TemSceneHelper::SceneManager->fields.ActiveScenes->fields._items->vector[i]->fields.SceneRoot != nullptr)
							{
								tem::SceneList::ConstructSceneHierarchy({ 999, TemSceneHelper::SceneManager->fields.ActiveScenes->fields._items->vector[i]->fields.MetaData->fields.LinearId }, 1);
							}
						}
						tem::SceneList::ConstructSceneHierarchy({ 999, 750 }, 1);

						MDV::MessageToWrite.push_back(std::to_string(static_cast<int>(MessageType::ExpandSceneHierarchy)) + "|" + message.second.Content + "|" + tem::SceneList::RootHierarchy.ToString());
					}
				}
				break;

				case MessageType::GetFieldsProperties:
				{
					std::vector<int> sceneHierarchy = tem::StringToIntVector(message.second.Content, ",");
					MDV::SelectedObject = tem::SceneList::GetGameObjectFromHierarchyIndex(sceneHierarchy);
					tem::SceneHierarchy* hierarchy = tem::SceneList::GetSceneHierarchyPtrFromIndex(sceneHierarchy);				

					if (MDV::SelectedObject != nullptr)
					{
						hierarchy->Object.GetObjectData(MDV::SelectedObject);
						MDV::MessageToWrite.push_back(std::to_string(static_cast<int>(MessageType::GetFieldsProperties)) + "|" + hierarchy->ToString());
					}
				}
				break;

				case MessageType::GetFieldsPropertiesGameObject:
				{
					/*std::vector<int> sceneHierarchy = tem::StringToIntVector(message.second.Content, ",");
					MDV::SelectedObject = tem::SceneList::GetGameObjectFromHierarchyIndex(sceneHierarchy);
					tem::SceneHierarchy* hierarchy = tem::SceneList::GetSceneHierarchyPtrFromIndex(sceneHierarchy);

					if (MDV::SelectedObject != nullptr)
					{
						//hierarchy->Object.GetObjectDataGameObject(MDV::SelectedObject);
						MDV::MessageToWrite.push_back(std::to_string(static_cast<int>(MessageType::GetFieldsPropertiesGameObject)) + "|" + hierarchy->ToString() + "|" + message.second.Content);
					}*/
				}
				break;

				case MessageType::SetFieldsProperties:
				{
					auto messageContent = sutil::SplitTem(message.second.Content, "|");
					if (messageContent.size() >= 4)
					{
						std::vector<int> sceneHierarchy = tem::StringToIntVector(messageContent[0], ",");
						MDV::SelectedObject = tem::SceneList::GetGameObjectFromHierarchyIndex(sceneHierarchy);

						if (MDV::SelectedObject != nullptr)
							tem::SceneList::GetSceneHierarchyPtrFromIndex(sceneHierarchy)->Object.SetComponentData(MDV::SelectedObject, messageContent[1], messageContent[2], messageContent[3], messageContent[4], messageContent[5] == "True" ? true : false);
					}
				}
				break;

				case MessageType::SaveEditorWorld:
				{
					nlohmann::json j_scenedata(tem::SceneList::RootSceneData);
					sutil::Write(ManagerPath + "WorldEditor\\EditorWorldScene.json", j_scenedata.dump());
					nlohmann::json j_umap(tem::SceneList::RootHierarchy);
					sutil::Write(ManagerPath + "WorldEditor\\EditorWorld.json", j_umap.dump());
					nlohmann::json j_collision(tem::CollisionCreator::Instance);
					sutil::Write(ManagerPath + "WorldEditor\\EditorCollision.json", j_collision.dump());
				}
				break;

				case MessageType::LoadEditorWorld:
				{
					if (futureIsReady == false)
					{
						if (std::filesystem::exists(ManagerPath + "WorldEditor\\EditorWorldScene.json") == true)
						{
							nlohmann::json jSceneData = nlohmann::json::parse(sutil::ReadFile(ManagerPath + "WorldEditor\\EditorWorldScene.json"));
							tem::SceneList::RootSceneData = jSceneData.get<tem::SceneData>();
							tem::SceneList::RootSceneData.LoadScene();
						}

						nlohmann::json j = nlohmann::json::parse(sutil::ReadFile(ManagerPath + "WorldEditor\\EditorWorld.json"));
						tem::SceneList::RootHierarchy = j.get<tem::SceneHierarchy>();
						std::vector<app::RuntimeSceneMetaData*> scenesToLoad = tem::SceneList::GetScenesToLoad();
						TemSceneHelper::SceneManager->fields.Settings->fields.MinUtilityToDisableScene = 2500;
						TemSceneHelper::SceneManager->fields.Settings->fields.MinUtilityToPreventUnloading = 2500;
						TemSceneHelper::SceneManager->fields.Settings->fields.AllowInstantSceneUnloads = false;
						TemSceneHelper::SceneManager->fields.Settings->fields.DistanceMovedAwayFromSceneBeforeDisabling = 2500;
						TemSceneHelper::SceneManager->fields.Settings->fields.MaxUtilityBeforeConsideredUneeded = 2500;
						TemSceneHelper::SceneManager->fields.Settings->fields.MaxUtilityToEnableScene = 1800;
						TemSceneHelper::SceneManager->fields.Settings->fields.MaxUtilityToLoad = 2000;

						TemSceneHelper::LoadScenes(scenesToLoad);
						MessagesManager.MessagesFutures[message.second.Type] = std::async(TemSceneHelper::IsScenesLoaded, scenesToLoad, true);
						MessagesManager.SetTimeout(45 * 1000, message.second.Type);
						message.second.Timeout = 45 * 1000;
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

							std::vector<app::RuntimeSceneMetaData*> scenesToLoad = tem::SceneList::GetScenesToLoad();
							TemLogger::Add("Scenes needs to be activated and enabled: " + std::to_string(scenesToLoad.size()), LogType::Normal);
							for (auto& sceneLoad : scenesToLoad)
							{
								app::SceneManagerScene* managerScene = app::ScenesManager_GetSceneManagerScene(TemSceneHelper::SceneManager, sceneLoad->fields.Scene, NULL);

								if (managerScene != nullptr && managerScene->fields.SceneRoot != nullptr)
								{
									app::GameObject* object = app::Component_1_get_gameObject((app::Component_1*)managerScene->fields.SceneRoot, NULL);

									if (object != nullptr)
									{
										TemLogger::Add("Activating and enabling scene: " + il2cppi_to_string(managerScene->fields.MetaData->fields.Scene), LogType::Normal);
										
										if (app::GameObject_get_moonReady(object, NULL) == false)
											app::GameObject_set_moonReady(object, true, NULL);

										if (app::GameObject_get_active(object, NULL) == false)
											app::GameObject_set_active(object, true, NULL);
									}
									else
										TemLogger::Add("Loaded scene object was nullptr failed to activate it.", LogType::Error);
								}
								else
									TemLogger::Add("Loaded scene object was nullptr failed to activate it.", LogType::Error);
							}

							HasLoadedWorldData = std::async(tem::SceneList::LoadHierarchy);

							nlohmann::json jCollision = nlohmann::json::parse(sutil::ReadFile(ManagerPath + "WorldEditor\\EditorCollision.json"));
							tem::CollisionCreator newCollisionCreator = jCollision.get<tem::CollisionCreator>();
							tem::CollisionCreator::Instance.LoadCollision(newCollisionCreator);
						}
					}
				}
				break;
#endif
			}

			if (futureExists == false)
			{
				MessagesManager.RemoveMessage(message.second.Type);
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

	if (frameStep.State == FrameStepping::IsAutoFrameStepping) {
		Real_GameControllerUpdate(__this);
	}

	if (frameStep.State == FrameStepping::FrameSteppingDisabled) {
		Real_GameControllerUpdate(__this);
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
	} while (read > 0 && *(output + index - 1) != 0 && fileHandle && loopBool);
}

DWORD WINAPI ThreadMain(HMODULE hIns)
{
	//is this a valid path?
	//assets/scenes/gameScenes/scenes/swampGetSpiritBlade.unity

	if (std::filesystem::exists(std::filesystem::temp_directory_path()))
		managerPath = ManagerPath = sutil::ReadFile(std::filesystem::temp_directory_path().string() + "\\extendedmanager.tmp");

	pid = GetCurrentProcessId();
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, 1, pid);

	sutil::Append("C:\\moon\\manager_error.log", "Pid: " + std::to_string(pid) + ".\r\n");
	sutil::Append("C:\\moon\\manager_error.log", "Starting read thread.\r\n");

	//get dll base adress
	Assembly_BaseAddr = (unsigned long long)GetModuleHandleA("GameAssembly.dll");
	UnityPlayer_BaseAddress = (unsigned long long)GetModuleHandleA("UnityPlayer.dll");

	//initalize detours
	/* For finding CClassFunction
	mov qword ptr [r11-38],FFFFFFFFFFFFFFFE
	mov [r11+08],rbx
	mov [r11+10],rsi
	movaps [rsp+40],xmm6
	mov rbx,rcx
	xor esi,esi
	*/
	Real_CClassFunction = CClassFunction_t(Assembly_BaseAddr + 0x692380);// patch 1.3 0x6920c0);// patch 1.2 +0x994520);
	Real_MoonDriverSystem = tMoonDriverSystem(Assembly_BaseAddr + 0xE463C0);
	/* For finding GameAssembly.il2cpp_string_new <- goto adress subtract gameassembly.dll location
	mov rdx,FFFFFFFFFFFFFFFF
	inc rdx
	cmp byte ptr [rcx+rdx],00
	jne 7FFD7B303B57
	*/
	RealIl2cpp_string_new_wrapper = tIl2CppString(Assembly_BaseAddr + 0x279550); // patch 1.3 +0x279570); patch 1.2 0x263B50);
	Real_SeinOnKill = tSeinOnKill(Assembly_BaseAddr + 0x6EAAE0); // patch 1.3 0x01F2B430);
	Real_GameControllerUpdate = tGameControllerUpdate(UnityPlayer_BaseAddress + 0x692380);// patch 1.3 0x5f0350); //0x994040 gc -  0xA77FA0 sein

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)Real_CClassFunction, Mine_CClassFunction);

#if defined(IL2CPP)
	DetourAttach(&(PVOID&)Real_MoonDriverSystem, Mine_MoonDriverSystem);
	DetourAttach(&(PVOID&)RealIl2cpp_string_new_wrapper, string_new);
	DetourAttach(&(PVOID&)Real_SeinOnKill, My_SeinOnKill);
#endif

	DetourAttach(&(PVOID&)Real_GameControllerUpdate, My_GameControllerUpdate);
	LONG lError = DetourTransactionCommit();

	if (lError == NO_ERROR)
		sutil::Append("C:\\moon\\manager_error.log", "Read thread detours hooked.\r\n");
	else if (lError == ERROR_INVALID_DATA)
		sutil::Append("C:\\moon\\manager_error.log", "Target function was changed by third party between steps of the transaction.\r\n");
	else if (lError == ERROR_INVALID_OPERATION)
		sutil::Append("C:\\moon\\manager_error.log", "No pending transaction exists.\r\n");
	else
		sutil::Append("C:\\moon\\manager_error.log", "Unkown error:" + std::to_string(lError) + ".\r\n");

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

	std::string managerExeName = "ExtendedManager.exe";
	DWORD proccessID = FindProcessId(managerExeName);
	char* buffer = new char[512];
	READ_THREAD_DONE = true;

#ifdef TEMSOCKET
	TemSocket::ConnectToServer("HELLO SERVER");
	TemSocket::SendSocketMessage("HELLO AGAIN");
#endif
	sutil::Append("C:\\moon\\manager_error.log", "Injection was succesful\r\nPipe is being read from.\r\n");

	std::vector<std::string> messages;
	while (IsProcessRunning(proccessID) && loopBool)
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

						sutil::Append("C:\\moon\\manager_error.log", "Message received: " + message + ".\r\n");

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
							if (MANAGER_INITIALIZED == 1)
								app::SeinPlayAnimationController_StopAnimation(MDV::SeinPlayAnimationController, NULL);
						}
						if (newMessage.Type == MessageType::GetSeinFaces)
						{
							if (MANAGER_INITIALIZED == 1)
							{
								int faces = app::SeinCharacter_get_FacingDirection(MDV::MoonSein, NULL);
								MDV::MessageToWrite.push_back(std::to_string(static_cast<int>(MessageType::GetSeinFaces)) + "|" + std::to_string(faces));
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
#ifdef TEMSOCKET
	TemSocket::Exit();
#endif

	for (int i = 0; i < MDV::AllObjectsToCallUpdate.size(); i++)
	{
		if (MDV::AllObjectsToCallUpdate[i] != nullptr)
		{
			Global* object = MDV::AllObjectsToCallUpdate[i];
			if (object != nullptr)
				object->Cleanup();
		}
	}
	TemLogger::Logger.Cleanup();
	MDV::AllObjectsToCallUpdate.clear();

	graphDrawer.Destroy();
	SeinVisualEditor::Cleanup();

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&(PVOID&)Real_CClassFunction, Mine_CClassFunction);

#if defined(IL2CPP)
	DetourDetach(&(PVOID&)Real_MoonDriverSystem, Mine_MoonDriverSystem);
	DetourDetach(&(PVOID&)RealIl2cpp_string_new_wrapper, string_new);
	DetourDetach(&(PVOID&)Real_SeinOnKill, My_SeinOnKill);
#endif

	DetourDetach(&(PVOID&)Real_GameControllerUpdate, My_GameControllerUpdate);
	DetourTransactionCommit();

	CloseHandle(fileHandle);
	CloseHandle(fileHandleWrite);

	//sleep again to let the game cleanly return to it's own loops
	EXITING_THREAD = true;
	while (WRITE_THREAD_EXITED == false)
	{
		Sleep(25);
	}
	FreeLibraryAndExitThread(hIns, 0);
}

DWORD WINAPI ThreadWrite(HMODULE hIns)
{
	while (READ_THREAD_DONE == false && EXITING_THREAD == false)
	{
		sutil::Append("C:\\moon\\manager_error.log", "Waiting on read thread to start up.\r\n");
		Sleep(500);
	}

	pid = GetCurrentProcessId();
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, 1, pid);

recreateFile:
	fileHandleWrite = CreateFileA("\\\\.\\pipe\\injectdll-manager-pipe", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

	DWORD errorMessageID = ::GetLastError();
	if (errorMessageID != 0 && EXITING_THREAD == false)
	{
		LPSTR messageBuffer = nullptr;
		size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

		std::string message(messageBuffer, size);

		//Free the buffer.
		LocalFree(messageBuffer);
		Sleep(500);
		sutil::Append("C:\\moon\\manager_error.log", "Insufficient privileges, couldn't create pipe. Access denied.\r\n");
		goto recreateFile;
	}

	sutil::Append("C:\\moon\\manager_error.log", "DLL pipe was succesful\r\n");

	std::string managerExeName = "ExtendedManager.exe";
	std::string messageToSend = "";
	DWORD proccessID = FindProcessId(managerExeName);

	while (EXITING_THREAD == false || IsProcessRunning(proccessID) && loopBool)
	{
		if (IsWritingToMessageString == false && MDV::MessageToWrite.size() > 0)
		{
			messageToSend = "";

			if (MDV::MessageToWrite.size() > 100) {
				MDV::MessageToWrite.clear();
			}

			while (MDV::MessageToWrite.size() > 0)
			{
				messageToSend += MDV::MessageToWrite[0] + "||";

				if (MDV::MessageToWrite.size() > 0)
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

	WRITE_THREAD_EXITED = true;
	return 0;
}