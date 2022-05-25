#pragma once

#ifndef _SCENELIST_H
#define _SCENELIST_H

#include "Adresses.h"
#include "SceneHierarchy.h"
#include "SceneData.h"

namespace tem {
	class MethodParameter
	{
	public:
		std::string Name;
		int Position;
		Il2CppTypeEnum Type;

		MethodParameter()
		{
			Name = "";
			Position = -1;
			Type = Il2CppTypeEnum::IL2CPP_TYPE_VOID;
		}

		MethodParameter(ParameterInfo parameterInfo)
		{
			Name = parameterInfo.name;
			Position = -parameterInfo.position;
			Type = parameterInfo.parameter_type->type;
		}

		std::string ToJsonString();
	};

	class SceneList
	{
	public:
		static bool HasBeenInitialized;
		static app::Type* ComponentType;
		static tem::SceneHierarchy RootHierarchy;
		static tem::SceneData RootSceneData;
		static tem::SceneHierarchy* ActiveHiearchy;
		static std::unordered_map<int, std::uintptr_t> SpecialSceneHierarchyIndexMap;
		static std::unordered_map<std::string, std::uintptr_t> SpecialSceneHierarchyMap;

		static tem::SceneHierarchy* GetSceneHierarchyPtrFromIndex(std::vector<int> indexes);
		static tem::SceneHierarchy* GetSceneHierarchyPtrFromIndex(std::vector<std::string> indexes);
		static std::vector<std::string> GetSceneHierarchyIndexFromGameObject(app::GameObject* object);
		static void Initialize();
		static bool LoadHierarchy();
		static bool SetLoadedHierarchyData();
		static void MoveHierarchy(tem::SceneHierarchy* moving, tem::SceneHierarchy* newParent);
		static void UpdateHierarchyIndex(tem::SceneHierarchy* update);
		static tem::SceneHierarchy* CloneGameObject(std::vector<std::string> indexes);
		static tem::SceneHierarchy* CloneGameObject(std::vector<int> indexes);
		static app::GameObject* GetGameObjectFromHierarchyIndex(std::vector<int> hierarchy, app::GameObject* object = nullptr);
		static app::GameObject* GetGameObjectFromHierarchyName(std::vector<std::string> hierarchy, app::GameObject* object = nullptr);
		static void ConstructSceneHierarchy(std::vector<int> sceneIndexHierarchy, int maxDepth);
		static void ConstructSceneHierarchy(std::vector<std::string> sceneIndexHierarchy, int maxDepth);
		static std::vector<app::RuntimeSceneMetaData*> GetScenesToLoad();
		static app::SceneManagerScene* GetSceneManagerSceneFromHierarchy(std::vector<int> hierarchy);
		static app::SceneManagerScene* GetSceneManagerSceneFromHierarchyName(std::vector<std::string> hierarchy);

		static app::GameObject* GetGameObject(int hierarchyIndex, std::vector<std::string> hierarchyPath);

	private:
		static std::vector<int> DoesHierarchyExists(std::vector<int> indexes);
		static std::vector<std::string> DoesHierarchyExists(std::vector<std::string> indexes);
		static bool LoadHierarchyP(tem::SceneHierarchy* hierarchy);
		static bool SetLoadedHierarchyDataP(tem::SceneHierarchy* hierarchy);
		static void UpdateHierarchyIndex(tem::SceneHierarchy* update, std::vector<int> hierarchyIndex);
		static void SceneHiearchyGetComponents(tem::SceneHierarchy* hierarchy);
		static void SceneHierarchyGetChildren(tem::SceneHierarchy* hierarchy, int maxDepth, int* sceneIndexDepth);

		friend class SceneHierarchy;
		friend class SceneObject;
	};
}

#endif