#pragma once

#include "Tem.h"

class TemSceneNodeData 
{
public :
	std::string SceneName;
	app::MoonGuid* SceneGuid;
	tem::Vector3 ScenePosition;
	app::Rect SceneBounds;
	float Distance;
	int Hops;

	TemSceneNodeData Clone()
	{
		TemSceneNodeData newNode = TemSceneNodeData();
		newNode.Distance = this->Distance;
		newNode.Hops = this->Hops;
		newNode.SceneBounds = this->SceneBounds;
		newNode.SceneGuid = this->SceneGuid;
		newNode.SceneName = this->SceneName;
		newNode.ScenePosition = this->ScenePosition;

		return newNode;
	}
};

class TemSceneNode
{
public:
	std::string SceneName;
	app::MoonGuid* SceneGuid;
	tem::Vector3 ScenePosition;
	app::Rect SceneBounds;
	std::unordered_map<std::string, TemSceneNodeData> NearbyScenes;
	std::vector<TemSceneNodeData> NearbyScenesVector;
};

class TemSceneHelper
{
public:
	static std::unordered_map<std::string, app::UberPoolGroup*> UberPoolGroups;
	static std::unordered_map<std::string, TemSceneNode> SceneData;
	static app::ScenesManager* SceneManager;
	static app::ScenesManagerBehaviourCinematic* BehaviourCinematic;
	static app::ScenesManagerBehaviourExplicit* BehaviourExplicit;
	static app::ScenesManagerBehaviourGameplay* BehaviourGameplay;
	static app::ScenesManagerBehaviourLegacy* BehaviourLegacy;
	static app::ScenesManagerBehaviourStatic* BehaviourStatic;
	static app::ScenesManagerBehaviourUtility* BehaviourUtility;

	static bool CanCallMethods;

	static void FillUberPoolGroups();
	static std::vector< app::RuntimeSceneMetaData*> GetScenesAtPosition(tem::Vector3 position);
	static app::RuntimeSceneMetaData* GetSceneByName(std::string name);
	static void LoadScenes(std::vector< app::RuntimeSceneMetaData*> scenes);
	static bool IsScenesLoaded(std::vector< app::RuntimeSceneMetaData*> scenes, bool preventUnloading = false);
	static bool ResetScenes(std::vector<app::RuntimeSceneMetaData*> scenes);
	static void PostRestoreCheckpoint();
	static void InitializeSceneNodes();
	static std::vector< TemSceneNode> GetScenePathByName(std::string start, std::string end);
	static std::vector<app::RuntimeSceneMetaData*> GetScenesByTemSceneNode(std::vector<TemSceneNode> scenes);
	static void SetScenesCanUnload(std::vector<app::RuntimeSceneMetaData*> scenes);
	static void SetAllScenesCanUnload();
	static std::vector<TemSceneNodeData> GetNearbyScenes(tem::Vector3 position);
	static app::Dictionary_2_MoonGuid_NearbySceneData_* TemSceneNodeDataToDictionary(std::vector<TemSceneNodeData> nodes);

private:
	static TemSceneNode GetClosestSceneAtPosition(tem::Vector3 position);
};