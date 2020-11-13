#pragma once

#include "Tem.h"

struct TemSceneNodeData {
	std::string SceneName;
	app::MoonGuid* SceneGuid;
	tem::Vector3 ScenePosition;
	app::Rect SceneBounds;
	float Distance;
	int Hops;
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
};