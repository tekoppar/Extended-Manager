#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <future>
#include <unordered_map>
#include <chrono>

#include "StringUtils.h"
#include "ManagerDef.h"
#include "GameWorldHelper.h"

#include "TemSceneHelper.h"

std::unordered_map<std::string, app::UberPoolGroup*> TemSceneHelper::UberPoolGroups = std::unordered_map<std::string, app::UberPoolGroup*>();
std::unordered_map<std::string, TemSceneNode> TemSceneHelper::SceneData = std::unordered_map<std::string, TemSceneNode>();
app::ScenesManager* TemSceneHelper::SceneManager = nullptr;
bool TemSceneHelper::CanCallMethods = false;
app::ScenesManagerBehaviourCinematic* TemSceneHelper::BehaviourCinematic = nullptr;
app::ScenesManagerBehaviourExplicit* TemSceneHelper::BehaviourExplicit = nullptr;
app::ScenesManagerBehaviourGameplay* TemSceneHelper::BehaviourGameplay = nullptr;
app::ScenesManagerBehaviourLegacy* TemSceneHelper::BehaviourLegacy = nullptr;
app::ScenesManagerBehaviourStatic* TemSceneHelper::BehaviourStatic = nullptr;
app::ScenesManagerBehaviourUtility* TemSceneHelper::BehaviourUtility = nullptr;

std::vector< app::RuntimeSceneMetaData*> TemSceneHelper::GetScenesAtPosition(tem::Vector3 position)
{
	app::List_1_RuntimeSceneMetaData_* scenes = app::ScenesManager_ListAllScenesAtPosition(TemSceneHelper::SceneManager, position.ToMoon(), NULL);
	std::vector< app::RuntimeSceneMetaData*> returnScenes;

	for (int i = 0; i < scenes->fields._size; i++)
	{
		app::RuntimeSceneMetaData* scene = scenes->fields._items->vector[i];

		if (scene != nullptr)
		{
			returnScenes.push_back(scene);
		}
	}

	return returnScenes;
}

app::RuntimeSceneMetaData* TemSceneHelper::GetSceneByName(std::string name)
{
	app::RuntimeSceneMetaData* metaDataTop = nullptr;

	for (int i = 0; i < TemSceneHelper::SceneManager->fields.AllScenes->fields._size; i++)
	{
		metaDataTop = TemSceneHelper::SceneManager->fields.AllScenes->fields._items->vector[i];
		std::string sceneNameTop = sutil::convert_csstring(metaDataTop->fields.Scene);
		app::SceneManagerScene* managerScene = app::ScenesManager_GetFromCurrentScenes(TemSceneHelper::SceneManager, metaDataTop, NULL);

		if (managerScene == nullptr && sceneNameTop == name)
		{
			return metaDataTop;
		}
	}

	return metaDataTop;
}

void TemSceneHelper::LoadScenes(std::vector<app::RuntimeSceneMetaData*> scenes)
{
	for (auto& scene : scenes)
	{
		app::ScenesManager_RequestAdditivelyLoadScene(TemSceneHelper::SceneManager, scene, true, true, true, false, true, NULL);
		//app::ScenesManager_PreloadScene(TemSceneHelper::SceneManager, scene, NULL);
	}
}

bool TemSceneHelper::IsScenesLoaded(std::vector< app::RuntimeSceneMetaData*> scenes, bool preventUnloading)
{
	std::chrono::high_resolution_clock::time_point ProgramStart = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::time_point LastTime = std::chrono::high_resolution_clock::now();
	std::chrono::milliseconds timeSpan = std::chrono::duration_cast<std::chrono::milliseconds>(LastTime - ProgramStart);

	bool isLoaded = false;
	bool isEnabled = false;
	bool isSceneEnabled = false;
	std::vector<app::SceneManagerScene*> managerScenes;

	TemLogger::Add("Checking if scenes loaded");

	while (managerScenes.size() <= scenes.size())
	{
		if (timeSpan.count() > 5 * 1000)
			break;

		LastTime = std::chrono::high_resolution_clock::now();
		timeSpan = std::chrono::duration_cast<std::chrono::milliseconds>(LastTime - ProgramStart);

		if (CanCallMethods == true)
		{
			for (auto& scene : scenes)
			{
				app::SceneManagerScene* managerScene = app::ScenesManager_GetSceneManagerScene(TemSceneHelper::SceneManager, scene->fields.Scene, NULL);

				if (managerScene != nullptr)
				{
					managerScenes.push_back(managerScene);

					if (preventUnloading == true)
					{
						app::ScenesManager_PreventUnloading_1(TemSceneHelper::SceneManager, scene, true, NULL);
						//app::ScenesManager_PreventUnloading(TemSceneHelper::SceneManager, scene->fields.VisibleOnlyInPaddingDependantScene, true, NULL);
					}
				}
			}
		}
	}

	while (scenes.size() > 0)
	{
		if (timeSpan.count() > 10 * 1000)
			break;

		LastTime = std::chrono::high_resolution_clock::now();
		timeSpan = std::chrono::duration_cast<std::chrono::milliseconds>(LastTime - ProgramStart);

		if (CanCallMethods == true)
		{
			if (scenes[0]->fields.SceneMoonGuid != nullptr)
			{
				isLoaded = app::ScenesManager_SceneIsLoaded(TemSceneHelper::SceneManager, scenes[0]->fields.SceneMoonGuid, NULL);

				if (isLoaded)
				{
#ifdef _WOTW_PATCH_THREE
					if (managerScenes[0]->fields.SceneRoot->fields.m_state != app::SceneState__Enum::SceneState__Enum_Enabling || managerScenes[0]->fields.SceneRoot->fields.m_state != app::SceneState__Enum::SceneState__Enum_Enabled)
					{
#endif
#ifdef _WOTW_PATCH_TWO
						if (managerScenes[0]->fields.SceneRoot->fields.m_state != app::SceneState__Enum::Enabling || managerScenes[0]->fields.SceneRoot->fields.m_state != app::SceneState__Enum::Enabled)
						{
#endif
							app::ScenesManager_EnableDisabledScene(TemSceneHelper::SceneManager, managerScenes[0], true, NULL);
							//app::SceneRoot_set_HighPriorityEnabling(managerScenes[0]->fields.SceneRoot, true, NULL);
							//app::SceneRoot_EnableSceneImmediate(managerScenes[0]->fields.SceneRoot, NULL);
							//managerScenes[0]->fields.KeepLoadedForCheckpoint = true;
							//managerScenes[0]->fields.PreventUnloading = true;
						}

						if (CanCallMethods == true)
						{
							isEnabled = app::ScenesManager_SceneIsEnabled_1(TemSceneHelper::SceneManager, managerScenes[0]->fields.MetaData->fields.SceneMoonGuid, NULL);
							isSceneEnabled = app::SceneManagerScene_get_IsEnabled(managerScenes[0], NULL);

#ifdef _WOTW_PATCH_THREE
							if ((isEnabled == true && isSceneEnabled == true) ||
								(managerScenes[0]->fields.SceneRoot->fields.m_state == app::SceneState__Enum::SceneState__Enum_Enabling || managerScenes[0]->fields.SceneRoot->fields.m_state == app::SceneState__Enum::SceneState__Enum_Enabled))
							{
#endif
#ifdef _WOTW_PATCH_TWO
								if ((isEnabled == true && isSceneEnabled == true) ||
									(managerScenes[0]->fields.SceneRoot->fields.m_state == app::SceneState__Enum::Enabling || managerScenes[0]->fields.SceneRoot->fields.m_state == app::SceneState__Enum::Enabled))
								{
#endif
									scenes.erase(scenes.begin());
									managerScenes.erase(managerScenes.begin());
								}

								isSceneEnabled = isEnabled = false;
						}
							else
								continue;
				}
						else
						{
							if (CanCallMethods == true)
							{
								bool isLoading = app::ScenesManager_SceneIsLoading(TemSceneHelper::SceneManager, scenes[0]->fields.SceneMoonGuid, NULL);

								if (isLoading == false)
									app::ScenesManager_RequestAdditivelyLoadScene(TemSceneHelper::SceneManager, scenes[0], true, true, true, false, true, NULL);
								//app::ScenesManager_PreloadScene(TemSceneHelper::SceneManager, scenes[0], NULL);
							}
							else
								continue;
						}
						isLoaded = false;
			}
					else
					{
						scenes.erase(scenes.begin());
						managerScenes.erase(managerScenes.begin());
					}
		}
				else
				{
					Sleep(4);
				}
	}


			/*while (CanCallMethods == false)
			{
				for (auto& manager : managerScenes)
				{
					app::ScenesManager_EnableDisabledScene(TemSceneHelper::SceneManager, manager, true, NULL);
				}
			}

			while (managerScenes.size() > 0)
			{
				if (CanCallMethods == true) {
					isEnabled = app::ScenesManager_SceneIsEnabled_1(TemSceneHelper::SceneManager, managerScenes[0]->fields.MetaData->fields.SceneMoonGuid, NULL);
					isSceneEnabled = app::SceneManagerScene_get_IsEnabled(managerScenes[0], NULL);

					if (isEnabled == true && isSceneEnabled == true)
						managerScenes.erase(managerScenes.begin());

					isSceneEnabled = isEnabled = false;
				}
			}*/
			if (timeSpan.count() > 14 * 1000)
			{
				TemLogger::Add("Scenes failed to load in time.", LogType::Error);
				return false;
			}
			else
			{
				TemLogger::Add("Scenes loaded in time.", LogType::Normal);
				return true;
			}
}

		bool TemSceneHelper::ResetScenes(std::vector<app::RuntimeSceneMetaData*> scenes)
		{
			std::vector<app::SceneManagerScene*> managerScenes;
			for (auto& scene : scenes)
			{
				app::SceneManagerScene* managerScene = app::ScenesManager_GetSceneManagerScene(TemSceneHelper::SceneManager, scene->fields.Scene, NULL);
				//app::SceneRoot_LoadSavedSceneData(managerScene->fields.SceneRoot, NULL);
				app::SceneRoot_RefreshObjectsToTimeSliceEnableList(managerScene->fields.SceneRoot, NULL);
			}
			/*app::ScenesManager_DisableEnabledScene(TemSceneHelper::SceneManager, managerScene, false, NULL);

			if (managerScene != nullptr)
				managerScenes.push_back(managerScene);
		}

		bool isEnabled = true;
		while (scenes.size() > 0)
		{
			isEnabled = app::ScenesManager_SceneIsEnabled_1(TemSceneHelper::SceneManager, scenes[0]->fields.SceneMoonGuid, NULL);

			if (isEnabled == false)
				scenes.erase(scenes.begin());

		}

		for (auto& manager : managerScenes)
		{
			app::SceneRoot_LoadSavedSceneData(manager->fields.SceneRoot, NULL);
			app::ScenesManager_EnableDisabledScene(TemSceneHelper::SceneManager, manager, false, NULL);
		}

		isEnabled = false;
		while (managerScenes.size() > 0)
		{
			isEnabled = app::ScenesManager_SceneIsEnabled_1(TemSceneHelper::SceneManager, managerScenes[0]->fields.MetaData->fields.SceneMoonGuid, NULL);

			if (isEnabled == true)
				managerScenes.erase(managerScenes.begin());

		}*/

			return true;
		}

		void TemSceneHelper::FillUberPoolGroups()
		{
			app::Type* UberPoolGroupType = GetType("", "UberPoolGroup");
			app::Object_1__Array* UberPoolGroupArr = app::Object_1_FindObjectsOfTypeAll(UberPoolGroupType, NULL);

			for (int i = 0; i < UberPoolGroupArr->max_length; i++)
			{
				app::UberPoolGroup* pool = (app::UberPoolGroup*)UberPoolGroupArr->vector[i];

				if (pool != nullptr)
				{
					app::String* name = app::Object_1_get_name((app::Object_1*)pool, NULL);
					std::string nameS = sutil::convert_csstring(name);

					auto it = UberPoolGroups.find(nameS);
					if (it == UberPoolGroups.end())
						UberPoolGroups[nameS] = pool;
				}
			}
		}

		void TemSceneHelper::PostRestoreCheckpoint()
		{
			std::vector<app::SceneManagerScene*> currentScenes;
			for (int i = 0; i < TemSceneHelper::SceneManager->fields.ActiveScenes->fields._size; i++)
			{
				app::SceneManagerScene* scene = TemSceneHelper::SceneManager->fields.ActiveScenes->fields._items->vector[i];
				currentScenes.push_back(scene);

				app::Dictionary_2_MoonGuid_NearbySceneData_* nearbyScenes = app::RuntimeSceneMetaData_get_NearbyReachableScenes(scene->fields.MetaData, NULL);
				app::Dictionary_2_TKey_TValue_Enumerator_MoonGuid_NearbySceneData_ enumerator = app::Dictionary_2_MoonGuid_NearbySceneData__GetEnumerator(nearbyScenes, NULL);

				for (int i2 = 0; i2 < nearbyScenes->fields.count; i2++)
				{
					app::Dictionary_2_TKey_TValue_Entry_MoonGuid_NearbySceneData_ keyValue2 = nearbyScenes->fields.entries->vector[i2];
					app::NearbySceneData nearbyData = keyValue2.value;
					app::SceneManagerScene* managerScene = app::ScenesManager_GetSceneManagerScene(TemSceneHelper::SceneManager, nearbyData.MetaData->fields.Scene, NULL);
					currentScenes.push_back(managerScene);
				}

				for (auto& currentScene : currentScenes)
				{
					if (currentScene != nullptr)
					{
						app::GameObject* masterObject = app::Component_1_get_gameObject((app::Component_1*)currentScene->fields.SceneRoot, NULL);
						std::vector<app::Component_1*> components = GetComponentsByTypeInChildren(masterObject, "", "ProximityMine");

						for (auto& component : components)
						{
							//app::GameObject* object = app::Component_1_get_gameObject((app::Component_1*)component, NULL);

							//if (object != nullptr)
							//{
								//if (object->klass->_0.name == "ProximityMine")
								//{
							app::ProximityMine_Reset((app::ProximityMine*)component, NULL);
							//}
						//}
						}
					}
				}
			}


		}

		void TemSceneHelper::InitializeSceneNodes()
		{
			std::vector<std::string> sceneResourcesNames;

			for (int i = 0; i < TemSceneHelper::SceneManager->fields.AllScenes->fields._size; i++)
			{
				app::RuntimeSceneMetaData* currentScene = TemSceneHelper::SceneManager->fields.AllScenes->fields._items->vector[i];

				if (currentScene != nullptr)
				{
					TemSceneNode sceneNode = TemSceneNode();
					sceneNode.SceneGuid = currentScene->fields.SceneMoonGuid;
					sceneNode.SceneName = sutil::convert_csstring(currentScene->fields.Scene);
					sceneNode.ScenePosition = tem::Vector3(currentScene->fields.m_totalRect.m_XMin + (currentScene->fields.m_totalRect.m_Width * 0.5f), currentScene->fields.m_totalRect.m_YMin + (currentScene->fields.m_totalRect.m_Height * 0.5f), 0.0f);
					sceneNode.SceneBounds = currentScene->fields.m_totalRect; // app::RuntimeSceneMetaData_get_SceneBounds(currentScene, NULL);

					app::List_1_MoonGuid_* scenesList = app::ScenesManager_GetConnectedScenesCached(TemSceneHelper::SceneManager, currentScene, NULL);

					for (int i2 = 0; i2 < scenesList->fields._size; i2++)
					{
						app::MoonGuid* sceneGuid = scenesList->fields._items->vector[i2];
						app::RuntimeSceneMetaData* tempScene = app::ScenesManager_FindRuntimeSceneMetaData(TemSceneHelper::SceneManager, sceneGuid, NULL);

						if (tempScene != nullptr)
						{
							TemSceneNodeData sceneNodeData = TemSceneNodeData();
							sceneNodeData.SceneGuid = tempScene->fields.SceneMoonGuid;
							sceneNodeData.SceneName = sutil::convert_csstring(tempScene->fields.Scene);
							sceneNodeData.ScenePosition = tem::Vector3(tempScene->fields.m_totalRect.m_XMin + (tempScene->fields.m_totalRect.m_Width * 0.5f), tempScene->fields.m_totalRect.m_YMin + (tempScene->fields.m_totalRect.m_Height * 0.5f), 0.0f);
							sceneNodeData.Distance = tem::Vector3::Distance(sceneNode.ScenePosition, sceneNodeData.ScenePosition);
							sceneNodeData.SceneBounds = tempScene->fields.m_totalRect;// app::RuntimeSceneMetaData_get_SceneBounds(sceneToCheck, NULL);

							sceneNode.NearbyScenes[sceneNodeData.SceneName] = sceneNodeData;
							sceneNode.NearbyScenesVector.push_back(sceneNodeData);
						}
					}

					TemSceneHelper::SceneData[sceneNode.SceneName] = sceneNode;
				}
			}
		}

		std::vector<TemSceneNode> TemSceneHelper::GetScenePathByName(std::string start, std::string end)
		{
			if (TemSceneHelper::SceneData.find(start) != TemSceneHelper::SceneData.end() && TemSceneHelper::SceneData.find(end) != TemSceneHelper::SceneData.end())
			{

				TemSceneNode startScene = TemSceneHelper::SceneData[start];
				TemSceneNode endScene = TemSceneHelper::SceneData[end];

				std::unordered_map<std::string, TemSceneNodeData> scenesVisited;
				TemSceneNodeData startSceneData;
				startSceneData.Distance = 101000.0f;
				startSceneData.SceneGuid = startScene.SceneGuid;
				startSceneData.SceneName = startScene.SceneName;
				startSceneData.ScenePosition = startScene.ScenePosition;

				std::vector<TemSceneNodeData> scenesToVisit = startScene.NearbyScenesVector;
				scenesVisited[startScene.SceneName] = startSceneData;

				TemSceneNode currentScene = startScene;

				float DistanceToEnd = tem::Vector3::Distance(startScene.ScenePosition, endScene.ScenePosition);
				float DistanceToEndCurrent = DistanceToEnd;
				float DistanceToCurrent = 10000.0f;
				float TestDistance = 1000000.0f;
				float TestDistanceCurrent = 0.0f;

				std::vector<TemSceneNode> scenePath;
				scenePath.push_back(startScene);

				while (scenesToVisit.size() > 0)
				{
					if (scenesVisited.find(scenesToVisit[0].SceneName) == scenesVisited.end())
					{
						TestDistance = tem::Vector3::Distance(scenesToVisit[0].ScenePosition, endScene.ScenePosition);
						TestDistanceCurrent = tem::Vector3::Distance(scenesToVisit[0].ScenePosition, currentScene.ScenePosition);

						if (TestDistanceCurrent < DistanceToCurrent && TestDistance < DistanceToEnd && DistanceToEnd + DistanceToCurrent > TestDistance + TestDistanceCurrent)
						{
							DistanceToEnd = TestDistance;
							DistanceToCurrent = 10000.0f;
							currentScene = TemSceneHelper::SceneData[scenesToVisit[0].SceneName];

							scenePath.push_back(currentScene);

							if (currentScene.SceneName == end)
								return scenePath;

							scenesToVisit.insert(scenesToVisit.end(), currentScene.NearbyScenesVector.begin(), currentScene.NearbyScenesVector.end());
						}

						scenesVisited[scenesToVisit[0].SceneName] = scenesToVisit[0];
					}

					scenesToVisit.erase(scenesToVisit.begin());
				}

				return scenePath;
			}

			return std::vector<TemSceneNode>();
		}

		std::vector<app::RuntimeSceneMetaData*> TemSceneHelper::GetScenesByTemSceneNode(std::vector<TemSceneNode> scenes)
		{
			std::vector<app::RuntimeSceneMetaData*> returnScenes;
			for (auto& scene : scenes)
			{
				app::RuntimeSceneMetaData* newScene = app::ScenesManager_FindRuntimeSceneMetaData(TemSceneHelper::SceneManager, scene.SceneGuid, NULL);

				if (newScene != nullptr)
					returnScenes.push_back(newScene);
			}

			return returnScenes;
		}

		void TemSceneHelper::SetScenesCanUnload(std::vector<app::RuntimeSceneMetaData*> scenes)
		{
			for (auto& scene : scenes)
			{
				app::ScenesManager_UnsetPreventUnloading_1(TemSceneHelper::SceneManager, scene, NULL);
			}
		}

		void TemSceneHelper::SetAllScenesCanUnload()
		{
			app::ScenesManager_ClearKeepLoadedForCheckpoint(TemSceneHelper::SceneManager, NULL);
			app::ScenesManager_ClearPreventUnloading(TemSceneHelper::SceneManager, NULL);
			app::ScenesManager_AllowUnloadingOnAllScenes(TemSceneHelper::SceneManager, NULL);
		}

		std::vector<TemSceneNodeData> TemSceneHelper::GetNearbyScenes(tem::Vector3 position)
		{
			TemSceneNode closestNode = GetClosestSceneAtPosition(position);
			std::vector<TemSceneNodeData> nearbyNodes;
			std::unordered_map<std::string, bool> visitedNodes;
			std::vector<TemSceneNodeData> nodesToCheck = closestNode.NearbyScenesVector;
			TemSceneNodeData closeNode = TemSceneNodeData();
			closeNode.Hops = 0;
			closeNode.SceneBounds = closestNode.SceneBounds;
			closeNode.SceneName = closestNode.SceneName;
			closeNode.SceneGuid = closestNode.SceneGuid;
			closeNode.ScenePosition = closestNode.ScenePosition;
			closeNode.Distance = tem::Vector3::Distance(position, closestNode.ScenePosition);
			nearbyNodes.push_back(closeNode);
			visitedNodes[closeNode.SceneName] = true;

			while (nodesToCheck.size() > 0)
			{
				if (visitedNodes.find(nodesToCheck[0].SceneName) == visitedNodes.end() && tem::Vector3::Distance(position, nodesToCheck[0].ScenePosition) < 500.0f)
				{
					TemSceneNodeData clone = nodesToCheck[0].Clone();
					clone.Hops++;
					nearbyNodes.push_back(clone);
					visitedNodes[clone.SceneName] = true;

					if (SceneData.find(nodesToCheck[0].SceneName) != SceneData.end())
					{
						nodesToCheck.insert(std::end(nodesToCheck), std::begin(SceneData[nodesToCheck[0].SceneName].NearbyScenesVector), std::end(SceneData[nodesToCheck[0].SceneName].NearbyScenesVector));
					}
				}

				nodesToCheck.erase(nodesToCheck.begin());
			}

			return nearbyNodes;
		}

		app::Dictionary_2_MoonGuid_NearbySceneData_* TemSceneHelper::TemSceneNodeDataToDictionary(std::vector<TemSceneNodeData> nodes)
		{
			app::Dictionary_2_MoonGuid_NearbySceneData_* nearbyScenes = (app::Dictionary_2_MoonGuid_NearbySceneData_*)il2cpp_object_new((Il2CppClass*)(*app::Dictionary_2_MoonGuid_NearbySceneData___TypeInfo));
			app::Dictionary_2_MoonGuid_NearbySceneData___ctor(nearbyScenes, static_cast<int32_t>(nodes.size()), (*app::Dictionary_2_MoonGuid_NearbySceneData___ctor__MethodInfo));

			for (int i = 0; i < nodes.size(); i++)
			{
				app::NearbySceneData nearbyData = app::NearbySceneData();
				nearbyData.Hops = nodes[i].Hops;
				nearbyData.SceneGuid = nodes[i].SceneGuid;
				nearbyData.MetaData = app::ScenesManager_FindRuntimeSceneMetaData(SceneManager, nearbyData.SceneGuid, NULL);
				app::Dictionary_2_MoonGuid_NearbySceneData__Add(nearbyScenes, nodes[i].SceneGuid, nearbyData, (*app::Dictionary_2_MoonGuid_NearbySceneData__Add__MethodInfo));
			}

			return nearbyScenes;
		}

		TemSceneNode TemSceneHelper::GetClosestSceneAtPosition(tem::Vector3 position)
		{
			float closestDistance = 99999999.0f;
			float currentDistance = 99999999.0f;
			TemSceneNode closestNode = TemSceneNode();

			for (auto& node : SceneData)
			{
				currentDistance = tem::Vector3::Distance(position, node.second.ScenePosition);

				if (currentDistance < closestDistance)
				{
					closestNode = node.second;
					closestDistance = currentDistance;
				}
			}

			return closestNode;
		}