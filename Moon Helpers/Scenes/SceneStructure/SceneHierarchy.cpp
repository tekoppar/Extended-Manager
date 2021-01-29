#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <future>
#include <unordered_map>

#include "StringUtils.h"
#include "ManagerDef.h"
#include "TemSceneHelper.h"
#include "FieldHelper.h"
#include "PropertyHelper.h"
#include "TemFramework.h"
#include "Component.h"
#include "SceneObject.h"
#include "SceneList.h"
#include "TemSceneHelper.h"

#include "SceneHierarchy.h"

namespace tem {

	SceneHierarchy::SceneHierarchy()
	{
		this->Object = tem::SceneObject();
		this->SceneChildren = std::unordered_map<int, SceneHierarchy>();
	}

	SceneHierarchy::SceneHierarchy(tem::SceneObject object, std::unordered_map<int, SceneHierarchy> children)
	{
		this->Object = object;
		this->SceneChildren = children;
	}

	std::string tem::SceneHierarchy::ToJsonString()
	{
		std::string hierarchyString = "{\"Object\":{\"Name\":\"" + Object.Name + "\",\"ClassName\":\"" + Object.ClassName + "\",\"ParentName\":\"" + Object.ParentName + "\",";

		hierarchyString += "\"SceneComponents\":[";
		for (std::size_t i = 0; i < Object.SceneComponents.size(); i++)
		{
			tem::Component component = Object.SceneComponents[i];
			if (i + 1 < Object.SceneComponents.size())
				hierarchyString += component.ToJsonString() + ",";
			else
				hierarchyString += component.ToJsonString();
		}
		hierarchyString += "]},\"SceneChildren\":[";

		std::size_t index = 0;
		for (auto& child : SceneChildren)
		{
			if (index + 1 < SceneChildren.size())
				hierarchyString += child.second.ToJsonString() + ",";
			else
				hierarchyString += child.second.ToJsonString();

			index++;
		}
		hierarchyString += "]}";
		return hierarchyString;
	}

	std::string tem::SceneHierarchy::SaveJsonHierarchy()
	{
		std::string hierarchyString = "{\"Object\":{\"HierarchyIndex\":" + std::to_string(Object.HierarchyIndex) + ",\"Name\":\"" + Object.Name + "\",\"ClassName\":\"" + Object.ClassName + "\",\"ParentName\":\"" + Object.ParentName + "\",\"SceneComponents\":[";

		for (std::size_t i = 0; i < Object.SceneComponents.size(); i++)
		{
			tem::Component component = Object.SceneComponents[i];
			if (i + 1 < Object.SceneComponents.size())
				hierarchyString += component.SaveJsonComponent() + ",";
			else
				hierarchyString += component.SaveJsonComponent();
		}
		hierarchyString += "]},\"SceneChildren\":{";

		std::size_t index = 0;
		for (auto& child : SceneChildren)
		{
			if (index + 1 < SceneChildren.size())
				hierarchyString += "\"" + std::to_string(child.second.Object.HierarchyIndex) + "\":" + child.second.ToString() + ",";
			else
				hierarchyString += "\"" + std::to_string(child.second.Object.HierarchyIndex) + "\":" + child.second.ToString();

			index++;
		}
		hierarchyString += "}}";

		return hierarchyString;
	}

	std::string tem::SceneHierarchy::ToString()
	{
		std::string sceneNamedMap = "";
		std::size_t index = 0;
		for (auto& s : Object.ClonedSceneNameHierarchy)
		{
			if (index + 1 < Object.ClonedSceneNameHierarchy.size())
				sceneNamedMap += "\"" + s + "\",";
			else
				sceneNamedMap += "\"" + s + "\"";

			index++;
		}

		std::string hierarchyString = "{\"Object\":{\"HierarchyIndex\":" + std::to_string(Object.HierarchyIndex) + ",\"SceneIndexHierarchy\":[" + tem::IntVectorToString(Object.SceneIndexHierarchy, ",") + "],\"ClonedSceneNameHierarchy\":[" + sceneNamedMap + "],\"Name\":\"" + Object.Name + "\",\"ClassName\":\"" + Object.ClassName + "\",\"ParentName\":\"" + Object.ParentName + "\",";

		hierarchyString += "\"SceneComponents\":[";
		for (std::size_t i = 0; i < Object.SceneComponents.size(); i++)
		{
			tem::Component component = Object.SceneComponents[i];
			if (i + 1 < Object.SceneComponents.size())
				hierarchyString += component.ToJsonString() + ",";
			else
				hierarchyString += component.ToJsonString();
		}
		hierarchyString += "]},\"SceneChildren\":{";

		index = 0;
		for (auto& child : SceneChildren)
		{
			if (index + 1 < SceneChildren.size())
				hierarchyString += "\"" + std::to_string(child.second.Object.HierarchyIndex) + "\":" + child.second.ToString() + ",";
			else
				hierarchyString += "\"" + std::to_string(child.second.Object.HierarchyIndex) + "\":" + child.second.ToString();

			index++;
		}
		hierarchyString += "}}";
		return hierarchyString;
	}

	/*void tem::SceneHierarchy::Append(app::GameObject* object, std::string hierarchy)
	{
		std::vector<std::string> objectHierarchy = sutil::SplitTem(hierarchy, ",");
		tem::SceneHierarchy* currentHierarchy = nullptr;

		if (objectHierarchy.size() < 0)
			return;

		for (std::string s : objectHierarchy)
		{
			if (s != "" && s != ",")
			{
				if (currentHierarchy != nullptr)
				{
					currentHierarchy = &currentHierarchy->SceneChildren[s];
				}
			}
		}
		int index = TransformGetObjectIndex(object);
		tem::SceneHierarchy childHierarchy = tem::SceneHierarchy();
		childHierarchy.Object.ParentName = currentHierarchy->Object.Name;
		childHierarchy.Object.Parent = (std::uintptr_t)currentHierarchy;
		childHierarchy.Object.SceneIndexHierarchy = currentHierarchy->Object.SceneIndexHierarchy;
		childHierarchy.Object.SceneIndexHierarchy.push_back(childHierarchy.Object.HierarchyIndex);
		currentHierarchy->SceneChildren[childHierarchy.Object.HierarchyIndex] = childHierarchy;
		int sceneIndexDephth = 0;
		//tem::SceneList::ConstructSceneHierarchy(object, &childHierarchy, childHierarchy.Object.SceneIndexHierarchy, &sceneIndexDephth, 1);
	}*/

	void tem::SceneHierarchy::SaveHierarchy(std::string& jsonHierarchy)
	{
		this->Object.GetObjectData();
		jsonHierarchy += this->SaveJsonHierarchy();

		int index = 0;
		for (auto& child : this->SceneChildren)
		{
			child.second.SaveHierarchy(jsonHierarchy);

			if (index < this->SceneChildren.size() - 1)
				jsonHierarchy += ",";

			index++;
		}
		jsonHierarchy += "]}";
	}

	bool tem::SceneHierarchy::HasChild(std::string name)
	{
		if (SceneChildrenNameMap.find(name) == SceneChildrenNameMap.end())
			return false;
		else
			return true;
	}

	bool tem::SceneHierarchy::HasChild(int index)
	{
		if (SceneChildren.find(index) == SceneChildren.end())
			return false;
		else
			return true;
	}

	int tem::SceneHierarchy::GetChildIndex(std::string name, int index)
	{
		for (int i = 0; i < this->SceneChildren.size(); i++)
		{
			if (this->SceneChildren[i].Object.Name == name && i == index)
				return i;
		}

		return -1;
	}

	tem::SceneHierarchy* tem::SceneHierarchy::GetChildByName(std::string name)
	{
		if (SceneChildrenNameMap.find(name) == SceneChildrenNameMap.end())
			return nullptr;
		else
			return &SceneChildren[SceneChildrenNameMap[name]];
	}

	void tem::SceneHierarchy::GetScenesToLoad(std::vector<std::string>& scenesToLoad, SceneHierarchy& current)
	{
		for (auto& child : current.SceneChildren)
		{
			if (child.second.Object.IsCustomObject == true)
			{
				if (child.second.Object.ClonedSceneNameHierarchy.size() > 1 && vector::contains(scenesToLoad, child.second.Object.ClonedSceneNameHierarchy[0]) == false)
					scenesToLoad.push_back(child.second.Object.ClonedSceneNameHierarchy[0]);
			}

			tem::SceneHierarchy::GetScenesToLoad(scenesToLoad, child.second);
		}
	}

	bool tem::SceneHierarchy::VerifyHierarchy()
	{
		if (this->Object.SceneIndexHierarchy.size() == 0)
			return false;

		if (this->Object.SceneIndexHierarchy[1] > 299 && this->Object.ClonedSceneNameHierarchy.size() == 0)
		{
			tem::SceneHierarchy* parentPtr = reinterpret_cast<tem::SceneHierarchy*>(this->Object.Parent);
			bool isCustomChild = false;
			while (tem::PtrInRange(parentPtr) == true && tem::PtrInRange(parentPtr->Object.Parent) == true && parentPtr->Object.Parent != (std::uintptr_t)parentPtr)
			{
				if (parentPtr->Object.IsCustomObject)
					isCustomChild = true;

				parentPtr = reinterpret_cast<tem::SceneHierarchy*>(parentPtr->Object.Parent);
			}

			if (isCustomChild == false)
				TemLogger::Add(this->Object.Name + " is a custom object but missing cloned scene hierarchy", LogType::Warning);
		}

		bool sceneIsLoaded = false;
		for (int i = 0; i < TemSceneHelper::SceneManager->fields.ActiveScenes->fields._size; i++)
		{
			if (TemSceneHelper::SceneManager->fields.ActiveScenes->fields._items->vector[i]->fields.MetaData->fields.LinearId == this->Object.SceneIndexHierarchy[1])
				sceneIsLoaded = true;
		}

		if (sceneIsLoaded == false)
			return true;

		app::GameObject* foundObject = tem::SceneList::GetGameObjectFromHierarchyIndex(this->Object.SceneIndexHierarchy);
		if (foundObject != nullptr)
		{
			std::string childName = il2cppi_to_string(app::Object_1_get_name((app::Object_1*)foundObject, NULL));

			if (childName == this->Object.Name)
			{
				std::unordered_map<int, SceneHierarchy> newChildren;
				std::unordered_map<std::string, int> newSceneChildrenNameMap;
				for (auto& child : SceneChildren)
				{
					if (child.second.VerifyHierarchy() == true)
					{
						newChildren[child.first] = child.second;
						newSceneChildrenNameMap[child.second.Object.Name] = child.first;
					}
					else
						TemLogger::Add("Removing child hierarchy: " + child.second.Object.Name + " from parent: " + child.second.Object.ParentName, LogType::Warning);
				}

				SceneChildrenNameMap = newSceneChildrenNameMap;
				SceneChildren = newChildren;
				return true;
			}
		}

		foundObject = tem::SceneList::GetGameObjectFromHierarchyName(this->Object.ClonedSceneNameHierarchy);
		if (foundObject != nullptr)
		{
			std::string childName = il2cppi_to_string(app::Object_1_get_name((app::Object_1*)foundObject, NULL));

			if (this->Object.Name.find(childName) != std::string::npos)
			{
				std::unordered_map<int, SceneHierarchy> newChildren;
				std::unordered_map<std::string, int> newSceneChildrenNameMap;
				for (auto& child : SceneChildren)
				{
					if (child.second.VerifyHierarchy() == true)
					{
						newChildren[child.first] = child.second;
						newSceneChildrenNameMap[child.second.Object.Name] = child.first;
					}
					else
						TemLogger::Add("Removing child hierarchy: " + child.second.Object.Name + " from parent: " + child.second.Object.ParentName, LogType::Warning);
				}

				SceneChildrenNameMap = newSceneChildrenNameMap;
				SceneChildren = newChildren;
				return true;
			}

		}

		return false;
	}
}