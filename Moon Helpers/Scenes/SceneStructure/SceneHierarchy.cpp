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
		std::string hierarchyString = "{\"Object\":{\"Name\":\"" + Object.Name + "\",\"ClassName\":\"" + Object.ClassName + "\",\"ParentName\":\"" + Object.ParentName + "\",\"Fields\":[";

		for (int i = 0; i < Object.Fields.size(); i++)
		{
			tem::ClassField field = Object.Fields[i];
			hierarchyString += field.ToJsonString();
			if (Object.Fields.size() - 1 > i)
				hierarchyString += ",";
		}

		hierarchyString += "],\"Properties\":[";
		for (int i = 0; i < Object.Properties.size(); i++)
		{
			tem::ClassProperty prop = Object.Properties[i];
			hierarchyString += prop.ToJsonString();
			if (Object.Properties.size() - 1 > i)
				hierarchyString += ",";
		}

		hierarchyString += "],\"SceneComponents\":[";
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

		std::string hierarchyString = "{\"Object\":{\"HierarchyIndex\":" + std::to_string(Object.HierarchyIndex) + ",\"SceneIndexHierarchy\":[" + tem::IntVectorToString(Object.SceneIndexHierarchy, ",") + "],\"ClonedSceneNameHierarchy\":[" + sceneNamedMap + "],\"Name\":\"" + Object.Name + "\",\"ClassName\":\"" + Object.ClassName + "\",\"ParentName\":\"" + Object.ParentName + "\",\"Fields\":[";

		for (int i = 0; i < Object.Fields.size(); i++)
		{
			tem::ClassField field = Object.Fields[i];
			hierarchyString += field.ToJsonString();
			if (Object.Fields.size() - 1 > i)
				hierarchyString += ",";
		}

		hierarchyString += "],\"Properties\":[";
		for (int i = 0; i < Object.Properties.size(); i++)
		{
			tem::ClassProperty prop = Object.Properties[i];
			hierarchyString += prop.ToJsonString();
			if (Object.Properties.size() - 1 > i)
				hierarchyString += ",";
		}

		hierarchyString += "],\"SceneComponents\":[";
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
}