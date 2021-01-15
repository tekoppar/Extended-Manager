#pragma once

#ifndef _SCENEHIERARCHY_H
#define _SCENEHIERARCHY_H

#include "Adresses.h"
#include "Component.h"
#include "SceneObject.h"

namespace tem {
	class SceneHierarchy
	{
	public:
		tem::SceneObject Object;
		std::unordered_map<int, SceneHierarchy> SceneChildren;
		std::unordered_map<std::string, int> SceneChildrenNameMap;

		std::string ToString();
		std::string ToJsonString();
		std::string SaveJsonHierarchy();
		//void Append(app::GameObject* object, std::string hierarchy);
		void SaveHierarchy(std::string& jsonHierarchy);
		bool HasChild(std::string name);
		bool HasChild(int index);
		int GetChildIndex(std::string name, int index);
		SceneHierarchy* GetChildByName(std::string name);

		SceneHierarchy();
		SceneHierarchy(tem::SceneObject object, std::unordered_map<int, SceneHierarchy> children);
	};
}

#endif