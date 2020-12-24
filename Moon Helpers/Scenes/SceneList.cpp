#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <future>
#include <unordered_map>

#include "StringUtils.h"
#include "ManagerDef.h"

#include "SceneList.h"

std::string SceneHierarchy::ToString()
{
	std::string hierarchyString = "{\"Object\":{\"Name\":\"" + Object.Name + "\",\"ClassName\":\"" + Object.ClassName + "\",\"ParentName\":\"" + Object.ParentName + "\",\"SceneComponents\":[";
	
	for (int i = 0; i < Object.SceneComponents.size(); i++)
	{
		auto component = Object.SceneComponents[i];
		if (i+ 1 < Object.SceneComponents.size())
			hierarchyString += '"' + component + '"' + ",";
		else
			hierarchyString += '"' + component + '"';
	}
	hierarchyString += "]},\"SceneChildren\":[";

	for (int i = 0; i < SceneChildren.size(); i++)
	{
		auto child = SceneChildren[i];
		if (i + 1 < SceneChildren.size())
			hierarchyString += child.ToString() + ",";
		else
			hierarchyString += child.ToString();
	}
	hierarchyString += "]}";
	return hierarchyString;
}

SceneHierarchy SceneList::GetSceneStructureFromGameObject(app::GameObject* object)
{
	if (ComponentType == nullptr)
	{
		ComponentType = GetType("UnityEngine", "Component");
		if (ComponentType->klass->_0.name != "Component")
		{
			ComponentType = GetTypeFromClass((Il2CppClass*)(*app::Component_1__TypeInfo));
		}
	}
	SceneHierarchy SceneHierarchyList;
	SceneHierarchyList.Object = SceneObject();
	SceneHierarchyList.Object.Name = il2cppi_to_string(app::Object_1_get_name((app::Object_1*)object, NULL));
	SceneHierarchyList.Object.ClassName = object->klass->_0.name;

	app::Component_1__Array* components = app::GameObject_GetComponents(object, ComponentType, NULL);
	for (int i = 0; i < components->max_length; i++)
	{
		if (components->vector[i] != nullptr)
		{
			app::Component_1* component = components->vector[i];
			SceneHierarchyList.Object.SceneComponents.push_back(component->klass->_0.name);
		}
	}

	app::Transform* transform = app::GameObject_get_transform(object, NULL);
	int children = app::Transform_GetChildCount(transform, NULL);

	if (children > 0)
	{
		for (int i = 0; i < children; i++)
		{
			app::Transform* childTransform = app::Transform_GetChild(transform, i, NULL);
			app::GameObject* childObject = app::Component_1_get_gameObject((app::Component_1*)childTransform, NULL);

			if (childObject != nullptr)
			{
				SceneHierarchy sceneChildHierarchy;
				sceneChildHierarchy.Object.ParentName = SceneHierarchyList.Object.Name;
				sceneChildHierarchy.Object.Name = il2cppi_to_string(app::Object_1_get_name((app::Object_1*)childObject, NULL));
				sceneChildHierarchy.Object.ClassName = childObject->klass->_0.name;

				app::Component_1__Array* componentsChild = app::GameObject_GetComponents(childObject, ComponentType, NULL);
				for (int i = 0; i < componentsChild->max_length; i++)
				{
					if (componentsChild->vector[i] != nullptr)
					{
						app::Component_1* componentChild = componentsChild->vector[i];
						sceneChildHierarchy.Object.SceneComponents.push_back(componentChild->klass->_0.name);
					}
				}
				SceneHierarchyList.SceneChildren.push_back(sceneChildHierarchy);
			}
		}
	}

	return SceneHierarchyList;
}

SceneHierarchy SceneList::GetSceneStructureFromGameObjectNested(app::GameObject* object)
{
	if (ComponentType == nullptr)
	{
		ComponentType = GetType("UnityEngine", "Component");
		if (ComponentType->klass->_0.name != "Component")
		{
			ComponentType = GetTypeFromClass((Il2CppClass*)(*app::Component_1__TypeInfo));
		}
	}
	SceneHierarchy SceneHierarchyList;
	SceneHierarchyList.Object = SceneObject();
	SceneHierarchyList.Object.Name = il2cppi_to_string(app::Object_1_get_name((app::Object_1*)object, NULL));
	SceneHierarchyList.Object.ClassName = object->klass->_0.name;

	app::Component_1__Array* components = app::GameObject_GetComponents(object, ComponentType, NULL);
	for (int i = 0; i < components->max_length; i++)
	{
		if (components->vector[i] != nullptr)
		{
			app::Component_1* component = components->vector[i];
			SceneHierarchyList.Object.SceneComponents.push_back(component->klass->_0.name);
		}
	}

	app::Transform* transform = app::GameObject_get_transform(object, NULL);
	int children = app::Transform_GetChildCount(transform, NULL);

	if (children > 0)
	{
		for (int i = 0; i < children; i++)
		{
			app::Transform* childTransform = app::Transform_GetChild(transform, i, NULL);
			app::GameObject* childObject = app::Component_1_get_gameObject((app::Component_1*)childTransform, NULL);

			if (childObject != nullptr)
			{
				SceneHierarchy sceneChildHierarchy = GetSceneStructureFromGameObjectNested(childObject);
				sceneChildHierarchy.Object.ParentName = SceneHierarchyList.Object.Name;
				SceneHierarchyList.SceneChildren.push_back(sceneChildHierarchy);
			}
		}
	}

	return SceneHierarchyList;
}

app::GameObject* SceneList::GetGameObjectFromNames(std::string parentName, std::string objectName, app::GameObject* root)
{
	if (ComponentType == nullptr)
	{
		ComponentType = GetType("UnityEngine", "Component");
		if (ComponentType->klass->_0.name != "Component")
		{
			ComponentType = GetTypeFromClass((Il2CppClass*)(*app::Component_1__TypeInfo));
		}
	}
	app::String* objectNameS = string_new(objectName.c_str());
	app::String* parentNameS = string_new(parentName.c_str());
	app::Component_1__Array* components = app::GameObject_GetComponentsInChildren_1(root, ComponentType, true, NULL);

	for (int i = 0; i < components->max_length; i++)
	{
		if (components->vector[i] != nullptr)
		{
			app::Component_1* childTransform = components->vector[i];
			app::GameObject* childObject = app::Component_1_get_gameObject((app::Component_1*)childTransform, NULL);

			if (childObject != nullptr)
			{
				app::String* childObjectName = app::Object_1_get_name((app::Object_1*)childObject, NULL);
				bool same = app::String_Equals_1(childObjectName, objectNameS, NULL);

				if (same == true)
				{
					app::Transform* parentTransform = app::Transform_GetParent((app::Transform*)childTransform, NULL);

					if (parentTransform != nullptr)
					{
						app::GameObject* parentObject = app::Component_1_get_gameObject((app::Component_1*)parentTransform, NULL);

						if (parentObject != nullptr)
						{
							app::String* parentObjectName = app::Object_1_get_name((app::Object_1*)parentObject, NULL);
							bool sameParent = app::String_Equals_1(parentObjectName, parentNameS, NULL);

							if (sameParent == true)
								return childObject;
						}
					}
				}
			}
		}
	}

	return nullptr;
}

app::GameObject* SceneList::GetGameObjectFromHierarchyIndex(app::GameObject* object, std::string hierarchy)
{
	std::vector<std::string> objectHierarchy = sutil::SplitTem(hierarchy, ",");

	if (objectHierarchy.size() < 1)
		return nullptr;

	app::Transform* transform = app::GameObject_get_transform(object, NULL);
	int children = app::Transform_GetChildCount(transform, NULL);
	int currentIndex = -1;

	if (currentIndex <= children)
	{
		for (std::string index : objectHierarchy)
		{
			if (index != "" && index != ",")
			{
				children = app::Transform_GetChildCount(transform, NULL);
				currentIndex = std::stoi(index);

				if (currentIndex > children)
					return nullptr;

				transform = app::Transform_GetChild(transform, currentIndex, NULL);
			}
		}
	}

	return app::Component_1_get_gameObject((app::Component_1*)transform, NULL);
}