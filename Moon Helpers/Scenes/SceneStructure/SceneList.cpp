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
#include "SceneHierarchy.h"
#include "UIEvents.h"

#include "SceneList.h"

namespace tem {
	app::Type* tem::SceneList::ComponentType = nullptr;
	tem::SceneHierarchy* tem::SceneList::ActiveHiearchy = nullptr;
	tem::SceneHierarchy tem::SceneList::RootHierarchy = tem::SceneHierarchy(tem::SceneObject(false, false, "Scene Roots", "", 0x0, "", std::vector<tem::Component>(), std::vector<int>{999}, 999), std::unordered_map<int, tem::SceneHierarchy>());
	tem::SceneData tem::SceneList::RootSceneData = tem::SceneData();
	std::unordered_map<std::string, std::uintptr_t> tem::SceneList::SpecialSceneHierarchyMap;
	std::unordered_map<int, std::uintptr_t> tem::SceneList::SpecialSceneHierarchyIndexMap;

	std::string tem::MethodParameter::ToJsonString()
	{
		return "{\"MethodParameter\":{\"Name\":\"" + this->Name + "\",\"Position\":" + std::to_string(this->Position) + ",\"Type\":" + std::to_string(this->Type) + "}}";
	}

	void tem::SceneList::Initialize()
	{
		for (int i = 0; i < TemSceneHelper::SceneManager->fields.ActiveScenes->fields._size; i++)
		{
			if (TemSceneHelper::SceneManager->fields.ActiveScenes->fields._items->vector[i]->fields.SceneRoot != nullptr)
			{
				tem::SceneList::ConstructSceneHierarchy({ 999, TemSceneHelper::SceneManager->fields.ActiveScenes->fields._items->vector[i]->fields.MetaData->fields.LinearId }, 1);
			}
		}

		//tem::SceneList::ConstructSceneHierarchy(app::Component_1_get_gameObject((app::Component_1*)MDV::MoonSein, NULL), 4, 500);
		//tem::SceneList::ConstructSceneHierarchy(app::Component_1_get_gameObject((app::Component_1*)MDV::MoonGameController, NULL), 4, 600);
		tem::SceneList::SpecialSceneHierarchyMap["Editor Canvas"] = (std::uintptr_t)tem::UIEvents::Instance->CanvasObject;
		tem::SceneList::SpecialSceneHierarchyIndexMap[700] = (std::uintptr_t)tem::UIEvents::Instance->CanvasObject;
		tem::SceneList::ConstructSceneHierarchy({999, 700}, 1);
	}

	bool tem::SceneList::LoadHierarchy()
	{
		LoadHierarchyP(&tem::SceneList::RootHierarchy);
		return true;
	}

	bool tem::SceneList::LoadHierarchyP(tem::SceneHierarchy* hierarchy)
	{
		if (hierarchy->Object.IsCustomObject == true && hierarchy->Object.ClonedSceneNameHierarchy.size() > 0)
		{
			TemLogger::Add(hierarchy->Object.Name + " is custom object, starting to cloning: " + tem::StringVectorToString(hierarchy->Object.ClonedSceneNameHierarchy, ","), LogType::Normal);
			app::GameObject* cloneGameObject = tem::SceneList::GetGameObjectFromHierarchyName(hierarchy->Object.ClonedSceneNameHierarchy);
			//app::GameObject* doesCloneExist = tem::SceneList::GetGameObjectFromHierarchyIndex(hierarchy->Object.SceneIndexHierarchy); //need to change since I can't check if an object already exists or not using indexes when they're not loaded in the same order as they're saved

			if (cloneGameObject != nullptr)
			{
				std::vector<app::GameObject*> foundChildren = GetChildrenByName(TransformGetParent(cloneGameObject), hierarchy->Object.ClonedSceneNameHierarchy[hierarchy->Object.ClonedSceneNameHierarchy.size() - 1]);

				if (foundChildren.size() > 1 && hierarchy->Object.ClonedPosition.Equals(tem::Vector3(0.0f)) == false)
				{
					for (int i = 0; i < foundChildren.size(); i++)
					{
						if (hierarchy->Object.ClonedPosition.NearlyEqual(TransformGetPosition(foundChildren[i])) == true)
							cloneGameObject = foundChildren[i];
					}
				}

				app::Type* entityPlaceholderType = GetType("", "EntityPlaceholder");
				if (app::GameObject_HasComponent(cloneGameObject, entityPlaceholderType, NULL))
				{
					app::EntityPlaceholder* placeHolder = (app::EntityPlaceholder*)GetComponentByType(cloneGameObject, "", "EntityPlaceholder");
					app::SceneManagerScene* sceneManagerTemp = tem::SceneList::GetSceneManagerSceneFromHierarchy(hierarchy->Object.SceneIndexHierarchy);

					if (tem::PtrInRange(sceneManagerTemp) == true && sceneManagerTemp->klass->_0.name == "SceneManagerScene")
						app::EntityPlaceholder_RegisterSceneRoot(placeHolder, sceneManagerTemp->fields.SceneRoot, NULL);

					if (app::GameObject_get_moonReady(cloneGameObject, NULL) == true)
						app::GameObject_set_moonReady(cloneGameObject, false, NULL);

					if (app::GameObject_get_active(cloneGameObject, NULL) == true)
						app::GameObject_set_active(cloneGameObject, false, NULL);
				}
				else
				{
					if (app::GameObject_get_moonReady(cloneGameObject, NULL) == false)
						app::GameObject_set_moonReady(cloneGameObject, true, NULL);

					if (app::GameObject_get_active(cloneGameObject, NULL) == false)
						app::GameObject_set_active(cloneGameObject, true, NULL);
				}

				app::GameObject* clone = (app::GameObject*)app::Object_1_Instantiate_2((app::Object_1*)cloneGameObject, NULL);
				app::String* oName = app::Object_1_get_name((app::Object_1*)clone, NULL);
				std::string newName = il2cppi_to_string(oName) + "clone";
				app::Object_1_set_name((app::Object_1*)clone, string_new(newName.data()), NULL);
				std::vector<int> parentHierarchy = hierarchy->Object.SceneIndexHierarchy;

				if (parentHierarchy.size() > 1)
					parentHierarchy.erase(parentHierarchy.end() - 1);

				app::GameObject* newParent = tem::SceneList::GetGameObjectFromHierarchyIndex(parentHierarchy);

				if (newParent != nullptr)
					TransformSetParent(clone, newParent);
				else
					TransformSetParent(clone, TransformGetParent(cloneGameObject));

				TransformSetLocalPosition(clone, tem::Vector3(0.0f));
				TransformSetPosition(clone, TransformGetPosition(cloneGameObject));
				hierarchy->Object.ClonedPosition = TransformGetPosition(cloneGameObject);
				
				if (app::GameObject_get_moonReady(clone, NULL) == false)
					app::GameObject_set_moonReady(clone, true, NULL);

				if (app::GameObject_get_active(clone, NULL) == false)
					app::GameObject_set_active(clone, true, NULL);

				//tem::SceneHierarchy* parent = tem::SceneList::GetSceneHierarchyPtrFromIndex(parentHierarchy);
				//parent->SceneChildren[parent->SceneChildrenNameMap[hierarchy->Object.Name]].Object.Parent = (std::uintptr_t)parent;
				//parent->SceneChildren[parent->SceneChildrenNameMap[hierarchy->Object.Name]].Object.IsCustomObject = true;
				//parent->SceneChildren[parent->SceneChildrenNameMap[hierarchy->Object.Name]].Object.ClonedSceneNameHierarchy = hierarchy->Object.ClonedSceneNameHierarchy;
			}
			else
			{
				//if (doesCloneExist == nullptr)
				TemLogger::Add("Failed to clone object: " + tem::StringVectorToString(hierarchy->Object.ClonedSceneNameHierarchy, ","), LogType::Error);
				/*else
				TemLogger::Add("Clone already exists: " + tem::StringVectorToString(hierarchy->Object.ClonedSceneNameHierarchy, ","), LogType::Error);*/
			}
		}

		for (int i = 0; i < hierarchy->SceneChildren.size(); i++)
		{
			hierarchy->SceneChildren[i].Object.Parent = (std::uintptr_t)hierarchy;
			LoadHierarchyP(&hierarchy->SceneChildren[i]);
		}
		return true;
	}

	bool tem::SceneList::SetLoadedHierarchyData()
	{
		SetLoadedHierarchyDataP(&tem::SceneList::RootHierarchy);
		return true;
	}

	bool tem::SceneList::SetLoadedHierarchyDataP(tem::SceneHierarchy* hierarchy)
	{
		TemLogger::Add("Checking if " + hierarchy->Object.Name + " is a custom object");
		if (hierarchy->Object.IsCustomObject == true || hierarchy->Object.HasChanged == true)
		{
			TemLogger::Add(hierarchy->Object.Name + " is a custom object, starting to set saved data");
			for (tem::Component& component : hierarchy->Object.SceneComponents)
			{
				hierarchy->Object.SetComponentData(component.ClassName, component.ClassName, component.ClassName, false);
				component.ObjectData.HasChanged = true;
			}
		}

		for (int i = 0; i < hierarchy->SceneChildren.size(); i++)
		{
			SetLoadedHierarchyDataP(&hierarchy->SceneChildren[i]);
		}

		return true;
	}

	void tem::SceneList::MoveHierarchy(tem::SceneHierarchy* moving, tem::SceneHierarchy* newParent)
	{
		tem::SceneHierarchy* oldParent = reinterpret_cast<tem::SceneHierarchy*>(moving->Object.Parent);

		int oldIndex = moving->Object.HierarchyIndex;
		moving->Object.HierarchyIndex = newParent->SceneChildren.size();
		moving->Object.ParentName = newParent->Object.Name;
		moving->Object.Parent = (std::uintptr_t)newParent;
		moving->Object.SceneIndexHierarchy = newParent->Object.SceneIndexHierarchy;
		moving->Object.SceneIndexHierarchy.push_back(moving->Object.HierarchyIndex);
		newParent->SceneChildren[moving->Object.HierarchyIndex] = *moving;

		if (oldParent->SceneChildren.find(oldIndex) != oldParent->SceneChildren.end())
			oldParent->SceneChildren.erase(oldIndex);

		tem::SceneList::UpdateHierarchyIndex(oldParent);
		tem::SceneList::UpdateHierarchyIndex(newParent);
	}

	tem::SceneHierarchy* tem::SceneList::CloneGameObject(std::vector<std::string> indexes)
	{
		app::GameObject* cloneGameObject = tem::SceneList::GetGameObjectFromHierarchyName(indexes);
		tem::SceneHierarchy* sceneHierarchy = tem::SceneList::GetSceneHierarchyPtrFromIndex(indexes);
		tem::SceneHierarchy* parent = reinterpret_cast<tem::SceneHierarchy*>(sceneHierarchy->Object.Parent);

		if (cloneGameObject != nullptr && parent != nullptr)
		{
			app::GameObject_SetActive(cloneGameObject, true, NULL);
			app::GameObject_SetMoonHidden2ToHierarchy(cloneGameObject, false, NULL);
			app::GameObject* clone = (app::GameObject*)app::Object_1_Instantiate_2((app::Object_1*)cloneGameObject, NULL);

			std::string name = il2cppi_to_string(app::Object_1_get_name((app::Object_1*)clone, NULL));
			app::Object_1_set_name((app::Object_1*)clone, string_new((name + "clone").data()), NULL);
			TransformSetParent(clone, TransformGetParent(cloneGameObject));
			TransformSetLocalPosition(clone, tem::Vector3(0.0f));
			app::GameObject_SetActive(clone, true, NULL);
			app::GameObject_SetMoonHidden2ToHierarchy(clone, false, NULL);

			std::vector<std::string> newHierarchyIndex = indexes;
			newHierarchyIndex.erase(newHierarchyIndex.end() - 1);
			newHierarchyIndex.push_back(name);
			tem::SceneList::ConstructSceneHierarchy(newHierarchyIndex, 2);

			parent->SceneChildren[parent->SceneChildrenNameMap[name]].Object.IsCustomObject = true;
			parent->SceneChildren[parent->SceneChildrenNameMap[name]].Object.ClonedSceneNameHierarchy = indexes;
			return parent;
		}

		return nullptr;
	}

	tem::SceneHierarchy* tem::SceneList::CloneGameObject(std::vector<int> indexes)
	{
		app::GameObject* cloneGameObject = tem::SceneList::GetGameObjectFromHierarchyIndex(indexes);
		tem::SceneHierarchy* sceneHierarchy = tem::SceneList::GetSceneHierarchyPtrFromIndex(indexes);
		tem::SceneHierarchy* parent = reinterpret_cast<tem::SceneHierarchy*>(sceneHierarchy->Object.Parent);

		if (cloneGameObject != nullptr && parent != nullptr)
		{
			if (app::GameObject_get_active(cloneGameObject, NULL) == false)
				app::GameObject_set_active(cloneGameObject, true, NULL);

			//app::GameObject_SetMoonHidden2ToHierarchy(cloneGameObject, false, NULL);
			app::GameObject* clone = (app::GameObject*)app::Object_1_Instantiate_2((app::Object_1*)cloneGameObject, NULL);

			std::string name = il2cppi_to_string(app::Object_1_get_name((app::Object_1*)clone, NULL));
			app::Object_1_set_name((app::Object_1*)clone, string_new((name + "clone").data()), NULL);
			
			if (name.find("Placeholder") != std::string::npos)
			{
				parent->VerifyHierarchy();
				ConstructSceneHierarchy(parent->Object.SceneIndexHierarchy, 2);
			}

			TransformSetParent(clone, TransformGetParent(cloneGameObject), true);
			TransformSetLocalPosition(clone, tem::Vector3(0.0f));
			TransformSetPosition(clone, TransformGetPosition(cloneGameObject));

			if (app::GameObject_get_active(clone, NULL) == false)
				app::GameObject_set_active(clone, true, NULL);

			//app::GameObject_SetMoonHidden2ToHierarchy(clone, false, NULL);
			int newIndex = parent->SceneChildren.size(); //TransformGetObjectIndex(clone);//
			std::vector<int> newHierarchyIndex = indexes;
			newHierarchyIndex.erase(newHierarchyIndex.end() - 1);
			newHierarchyIndex.push_back(newIndex);
			tem::SceneList::ConstructSceneHierarchy(newHierarchyIndex, 2);

			parent->SceneChildren[newIndex].Object.IsCustomObject = true;
			parent->SceneChildren[newIndex].Object.ClonedPosition = TransformGetPosition(cloneGameObject);
			parent->SceneChildren[newIndex].Object.ClonedSceneNameHierarchy = GetSceneHierarchyIndexFromGameObject(cloneGameObject);
			return parent;
		}

		return nullptr;
	}

	void tem::SceneList::UpdateHierarchyIndex(tem::SceneHierarchy* update)
	{
		for (auto& child : update->SceneChildren)
		{
			update->SceneChildren[child.second.Object.HierarchyIndex].Object.HierarchyIndex = child.second.Object.HierarchyIndex;
			std::vector<int> childIndexes = update->Object.SceneIndexHierarchy;
			childIndexes.push_back(child.second.Object.HierarchyIndex);
			update->SceneChildren[child.second.Object.HierarchyIndex].Object.SceneIndexHierarchy = childIndexes;
			UpdateHierarchyIndex(&update->SceneChildren[child.second.Object.HierarchyIndex], update->SceneChildren[child.second.Object.HierarchyIndex].Object.SceneIndexHierarchy);
		}
	}

	void tem::SceneList::UpdateHierarchyIndex(tem::SceneHierarchy* update, std::vector<int> hierarchyIndex)
	{
		for (auto& child : update->SceneChildren)
		{
			update->SceneChildren[child.second.Object.HierarchyIndex].Object.HierarchyIndex = child.second.Object.HierarchyIndex;
			std::vector<int> childIndexes = update->Object.SceneIndexHierarchy;
			childIndexes.push_back(child.second.Object.HierarchyIndex);
			update->SceneChildren[child.second.Object.HierarchyIndex].Object.SceneIndexHierarchy = childIndexes;
			UpdateHierarchyIndex(&update->SceneChildren[child.second.Object.HierarchyIndex], update->SceneChildren[child.second.Object.HierarchyIndex].Object.SceneIndexHierarchy);
		}
	}

	std::vector<int> tem::SceneList::DoesHierarchyExists(std::vector<int> indexes)
	{
		tem::SceneHierarchy* ptr = &tem::SceneList::RootHierarchy;
		int i = indexes[0] == 999 ? 1 : 0;

		for (;i < indexes.size(); i++)
		{
			int index = indexes[i];
			if (ptr->SceneChildren.find(index) != ptr->SceneChildren.end())
				ptr = &ptr->SceneChildren[index];
			else
				return std::vector<int>();
		}
		std::vector<int> returnVal = ptr->Object.SceneIndexHierarchy;

		if (returnVal.size() > 1 && returnVal[0] == 999)
			return returnVal;
		else if (returnVal.size() == 1 && returnVal[0] == 999)
			return std::vector<int>();

		return returnVal;
	}

	std::vector<std::string> tem::SceneList::DoesHierarchyExists(std::vector<std::string> indexes)
	{
		tem::SceneHierarchy* ptr = &tem::SceneList::RootHierarchy;
		std::string name = indexes[0];

		for (int i = 0; i < indexes.size(); i++)
		{
			name = indexes[i];
			if (ptr->SceneChildrenNameMap.find(name) != ptr->SceneChildrenNameMap.end())
				ptr = &ptr->SceneChildren[ptr->SceneChildrenNameMap[name]];
			else
				return std::vector<std::string>();
		}

		if (indexes.size() > 1 && indexes[0] == "Scene Roots")
			return indexes;
		else if (indexes.size() == 1 && indexes[0] == "Scene Roots")
			return std::vector<std::string>();

		return indexes;
	}

	tem::SceneHierarchy* tem::SceneList::GetSceneHierarchyPtrFromIndex(std::vector<int> indexes)
	{
		tem::SceneHierarchy* foundHierarchy = &tem::SceneList::RootHierarchy;
		int index = indexes[0];
		for (int i = 0; i < indexes.size(); i++)
		{
			index = indexes[i];
			if (foundHierarchy->SceneChildren.find(index) != foundHierarchy->SceneChildren.end())
				foundHierarchy = &foundHierarchy->SceneChildren[index];
		}

		return foundHierarchy;
	}

	tem::SceneHierarchy* tem::SceneList::GetSceneHierarchyPtrFromIndex(std::vector<std::string> indexes)
	{
		tem::SceneHierarchy* foundHierarchy = &tem::SceneList::RootHierarchy;
		std::string name = indexes[0];
		for (int i = 0; i < indexes.size(); i++)
		{
			std::string index = indexes[i];
			if (foundHierarchy->SceneChildrenNameMap.find(index) != foundHierarchy->SceneChildrenNameMap.end())
				foundHierarchy = &foundHierarchy->SceneChildren[foundHierarchy->SceneChildrenNameMap[index]];
		}

		return foundHierarchy;
	}

	std::vector<std::string> tem::SceneList::GetSceneHierarchyIndexFromGameObject(app::GameObject* object)
	{
		std::vector<std::string> indexes;
		app::Transform* transform = app::GameObject_get_transform(object, NULL);

		while (transform != nullptr)
		{
			indexes.push_back(il2cppi_to_string(app::Object_1_get_name((app::Object_1*)app::Component_1_get_gameObject((app::Component_1*)transform, NULL), NULL)));
			transform = app::Transform_get_parent(transform, NULL);
		}

		std::reverse(indexes.begin(), indexes.end());
		return indexes;
	}

	void tem::SceneList::ConstructSceneHierarchy(std::vector<int> sceneIndexHierarchy, int maxDepth)
	{
		if (sceneIndexHierarchy.size() > 0)
		{
			std::vector<int> exists = DoesHierarchyExists(sceneIndexHierarchy);
			tem::SceneHierarchy* hierarchy = nullptr;

			if (exists.size() > 0 && exists == sceneIndexHierarchy)
			{
				hierarchy = tem::SceneList::GetSceneHierarchyPtrFromIndex(exists);
				hierarchy->VerifyHierarchy();
			}
			else
			{
				tem::SceneHierarchy child = tem::SceneHierarchy();
				child.Object.HierarchyIndex = sceneIndexHierarchy[sceneIndexHierarchy.size() - 1];
				child.Object.SceneIndexHierarchy = sceneIndexHierarchy;

				std::vector<int> parentHierarchyIndex = sceneIndexHierarchy;

				if (parentHierarchyIndex.size() > 1)
					parentHierarchyIndex.erase(parentHierarchyIndex.end() - 1);

				tem::SceneHierarchy* parentHierarchy = tem::SceneList::GetSceneHierarchyPtrFromIndex(parentHierarchyIndex);

				if (parentHierarchy != nullptr)
				{
					child.Object.Parent = reinterpret_cast<std::uintptr_t>(parentHierarchy);
					child.Object.ParentName = parentHierarchy->Object.Name;

					if (parentHierarchy->SceneChildren.find(child.Object.HierarchyIndex) == parentHierarchy->SceneChildren.end() && child.Object.SceneIndexHierarchy.size() > 2)
					{
						child.Object.HierarchyIndex = parentHierarchy->SceneChildren.size();
						child.Object.SceneIndexHierarchy.erase(child.Object.SceneIndexHierarchy.end() - 1);
						child.Object.SceneIndexHierarchy.push_back(child.Object.HierarchyIndex);
					}

					parentHierarchy->SceneChildren[child.Object.HierarchyIndex] = child;

					hierarchy = &parentHierarchy->SceneChildren[child.Object.HierarchyIndex];
				}
			}

			SceneHiearchyGetComponents(hierarchy);
			int sceneIndexDepth = 0;
			SceneHierarchyGetChildren(hierarchy, maxDepth, &sceneIndexDepth);
		}
	}

	void tem::SceneList::ConstructSceneHierarchy(std::vector<std::string> sceneIndexHierarchy, int maxDepth)
	{
		if (sceneIndexHierarchy.size() > 0)
		{
			std::vector<std::string> exists = DoesHierarchyExists(sceneIndexHierarchy);
			tem::SceneHierarchy* hierarchy = nullptr;

			if (exists.size() > 0 && exists == sceneIndexHierarchy)
			{
				hierarchy = tem::SceneList::GetSceneHierarchyPtrFromIndex(exists);
			}
			else
			{
				tem::SceneHierarchy child = tem::SceneHierarchy();
				child.Object.Name = sceneIndexHierarchy[sceneIndexHierarchy.size() - 1];

				std::vector<std::string> parentHierarchyIndex = sceneIndexHierarchy;

				if (parentHierarchyIndex.size() > 1)
					parentHierarchyIndex.erase(parentHierarchyIndex.end() - 1);

				tem::SceneHierarchy* parentHierarchy = tem::SceneList::GetSceneHierarchyPtrFromIndex(parentHierarchyIndex);

				if (parentHierarchy != nullptr)
				{
					child.Object.Parent = reinterpret_cast<std::uintptr_t>(parentHierarchy);
					child.Object.ParentName = parentHierarchy->Object.Name;
					parentHierarchy->SceneChildren[parentHierarchy->SceneChildrenNameMap[child.Object.Name]] = child;

					hierarchy = &parentHierarchy->SceneChildren[parentHierarchy->SceneChildrenNameMap[child.Object.Name]];
				}
			}

			SceneHiearchyGetComponents(hierarchy);
			int sceneIndexDepth = 0;
			SceneHierarchyGetChildren(hierarchy, maxDepth, &sceneIndexDepth);
		}
	}

	void tem::SceneList::SceneHierarchyGetChildren(tem::SceneHierarchy* hierarchy, int maxDepth, int* sceneIndexDepth)
	{
		app::GameObject* object = GetGameObjectFromHierarchyIndex(hierarchy->Object.SceneIndexHierarchy);

		if (object == nullptr)
			return;

		hierarchy->Object.Name = il2cppi_to_string(app::Object_1_get_name((app::Object_1*)object, NULL));
		hierarchy->Object.ClassName = object->klass->_0.name;

		if (maxDepth == -1 || maxDepth >= *sceneIndexDepth)
		{
			app::Transform* transform = app::GameObject_get_transform(object, NULL);
			int children = app::Transform_GetChildCount(transform, NULL);

			if (children > 0)
			{
				*sceneIndexDepth = *sceneIndexDepth + 1;
				for (int i = 0; i < children; i++)
				{
					app::Transform* childTransform = app::Transform_GetChild(transform, i, NULL);
					app::GameObject* childObject = app::Component_1_get_gameObject((app::Component_1*)childTransform, NULL);

					if (childObject != nullptr && childObject->fields._.m_CachedPtr != nullptr)
					{
						std::string childName = il2cppi_to_string(app::Object_1_get_name((app::Object_1*)childObject, NULL));
						int childIndex = app::Transform_GetSiblingIndex(childTransform, NULL);

						if (hierarchy->SceneChildren.find(childIndex) == hierarchy->SceneChildren.end())
						{
							tem::SceneHierarchy childHierarchy = tem::SceneHierarchy();
							childHierarchy.Object.ParentName = hierarchy->Object.Name;
							childHierarchy.Object.Parent = (std::uintptr_t)hierarchy;
							childHierarchy.Object.SceneIndexHierarchy = hierarchy->Object.SceneIndexHierarchy;
							childHierarchy.Object.SceneIndexHierarchy.push_back(childIndex);
							childHierarchy.Object.HierarchyIndex = childIndex;
							childHierarchy.Object.Name = childName;
							childHierarchy.Object.ClassName = childObject->klass->_0.name;
							SceneHiearchyGetComponents(&childHierarchy);
							hierarchy->SceneChildren[childIndex] = childHierarchy;
							hierarchy->SceneChildrenNameMap[childName] = childIndex;
						}
						SceneHierarchyGetChildren(&hierarchy->SceneChildren[childIndex], maxDepth, sceneIndexDepth);
					}
				}
				*sceneIndexDepth = *sceneIndexDepth - 1;
			}
		}
	}

	void tem::SceneList::SceneHiearchyGetComponents(tem::SceneHierarchy* hierarchy)
	{
		app::GameObject* object = GetGameObjectFromHierarchyIndex(hierarchy->Object.SceneIndexHierarchy);

		if (object == nullptr)
			return;

		if (ComponentType == nullptr)
		{
			ComponentType = GetType("UnityEngine", "Component");
			if (ComponentType->klass->_0.name != "Component")
			{
				ComponentType = GetTypeFromClass((Il2CppClass*)(*app::Component_1__TypeInfo));
			}
		}

		app::Component_1__Array* components = app::GameObject_GetComponents(object, ComponentType, NULL);
		int count = app::Array_System_Collections_ICollection_get_Count((app::Array*)components, NULL);
		std::string componentName = "";

		for (int i = 0; i < count; i++)
		{
			if (components->vector[i] != nullptr)
			{
				app::Component_1* component = components->vector[i];
				componentName = component->klass->_0.name;

				if (hierarchy->Object.HasComponent(componentName) == false)
				{
					tem::Component newComponent;
					newComponent.ClassName = component->klass->_0.name;
					hierarchy->Object.SceneComponents.push_back(newComponent);
				}
			}
		}
	}

	app::GameObject* tem::SceneList::GetGameObjectFromHierarchyIndex(std::vector<int> hierarchy, app::GameObject* object)
	{
		std::vector<int> tempHierarchy = hierarchy;

		if (tempHierarchy.size() > 1 && tempHierarchy[0] == 999)
			tempHierarchy.erase(tempHierarchy.begin());

		if (tempHierarchy.size() < 1 || (tempHierarchy.size() == 1 && (tempHierarchy[0] == 999 || tempHierarchy[0] == -1)))
			return nullptr;

		app::SceneManagerScene* sceneManagerScene = nullptr;
		if (tempHierarchy[0] <= 300)
		{
			app::RuntimeSceneMetaData* runtime = TemSceneHelper::SceneManager->fields.AllScenes->fields._items->vector[tempHierarchy[0]];
			sceneManagerScene = app::ScenesManager_GetFromCurrentScenes(TemSceneHelper::SceneManager, runtime, NULL);

			if (sceneManagerScene == nullptr && runtime != nullptr)
				sceneManagerScene = app::ScenesManager_GetSceneManagerScene(TemSceneHelper::SceneManager, runtime->fields.Scene, NULL);

			if (sceneManagerScene == nullptr && runtime != nullptr)
			{
				app::ScenesManager_AdditivelyLoadSceneFile(TemSceneHelper::SceneManager, runtime, false, true, false, false, NULL);
				sceneManagerScene = app::ScenesManager_GetSceneManagerScene(TemSceneHelper::SceneManager, runtime->fields.Scene, NULL);
			}
		}

		app::GameObject* tempObject = object;

		if (tempObject == nullptr)
		{
			if (tem::SceneList::SpecialSceneHierarchyIndexMap.find(tempHierarchy[0]) != tem::SceneList::SpecialSceneHierarchyIndexMap.end())
			{
				tempObject = reinterpret_cast<app::GameObject*>(tem::SceneList::SpecialSceneHierarchyIndexMap[tempHierarchy[0]]);
				tempHierarchy.erase(tempHierarchy.begin());
			}
			else if (sceneManagerScene != nullptr && sceneManagerScene->fields.SceneRoot != nullptr)
			{
				tempObject = app::Component_1_get_gameObject((app::Component_1*)sceneManagerScene->fields.SceneRoot, NULL);
				tempHierarchy.erase(tempHierarchy.begin());
			}

			if (tempObject == nullptr)
				return nullptr;
		}

		app::Transform* transform = app::GameObject_get_transform(tempObject, NULL);
		int children = app::Transform_GetChildCount(transform, NULL);
		int currentIndex = -1;

		while (tempHierarchy.size() > 0)
		{
			if (tempHierarchy[0] < children)
			{
				app::Transform* childTransform = app::Transform_GetChild(transform, tempHierarchy[0], NULL);

				if (childTransform != nullptr)
				{
					tempHierarchy.erase(tempHierarchy.begin());
					transform = childTransform;
					children = app::Transform_GetChildCount(transform, NULL);

					if (tempHierarchy.size() == 0)
						return app::Component_1_get_gameObject((app::Component_1*)transform, NULL);
				}
				else
					return nullptr;
			}
			else
				return nullptr;
		}

		if (tempHierarchy.size() == 0)
			return app::Component_1_get_gameObject((app::Component_1*)transform, NULL);
		else
			return nullptr;
	}

	app::SceneManagerScene* tem::SceneList::GetSceneManagerSceneFromHierarchy(std::vector<int> hierarchy)
	{
		if (hierarchy.size() > 1 && hierarchy[0] == 999)
			hierarchy.erase(hierarchy.begin());

		if (hierarchy.size() < 1 || (hierarchy.size() == 1 && (hierarchy[0] == 999 || hierarchy[0] == -1)))
			return nullptr;

		if (hierarchy[0] <= 300)
		{
			app::RuntimeSceneMetaData* runtime = TemSceneHelper::SceneManager->fields.AllScenes->fields._items->vector[hierarchy[0]];
			app::SceneManagerScene* sceneManagerScene = app::ScenesManager_GetFromCurrentScenes(TemSceneHelper::SceneManager, runtime, NULL);

			if (tem::PtrInRange(sceneManagerScene) == false && tem::PtrInRange(runtime) == true)
				sceneManagerScene = app::ScenesManager_GetSceneManagerScene(TemSceneHelper::SceneManager, runtime->fields.Scene, NULL);

			if (tem::PtrInRange(sceneManagerScene) == false && tem::PtrInRange(runtime) == true)
			{
				app::ScenesManager_AdditivelyLoadSceneFile(TemSceneHelper::SceneManager, runtime, false, true, false, false, NULL);
				sceneManagerScene = app::ScenesManager_GetSceneManagerScene(TemSceneHelper::SceneManager, runtime->fields.Scene, NULL);
			}

			return sceneManagerScene;
		}

		return nullptr;
	}

	app::SceneManagerScene* tem::SceneList::GetSceneManagerSceneFromHierarchyName(std::vector<std::string> hierarchy)
	{
		if (hierarchy.size() > 1 && hierarchy[0] == "Scene Roots")
			hierarchy.erase(hierarchy.begin());

		if (hierarchy.size() < 1 || (hierarchy.size() == 1 && (hierarchy[0] == "Scene Roots" || hierarchy[0] == "")))
			return nullptr;

		app::RuntimeSceneMetaData* runtime = app::ScenesManager_GetSceneInformation(TemSceneHelper::SceneManager, string_new(hierarchy[0].data()), NULL);
		app::SceneManagerScene* sceneManagerScene = app::ScenesManager_GetFromCurrentScenes(TemSceneHelper::SceneManager, runtime, NULL);

		if (tem::PtrInRange(sceneManagerScene) == false && tem::PtrInRange(runtime) == true)
			sceneManagerScene = app::ScenesManager_GetSceneManagerScene(TemSceneHelper::SceneManager, runtime->fields.Scene, NULL);

		if (tem::PtrInRange(sceneManagerScene) == false && tem::PtrInRange(runtime) == true)
		{
			app::ScenesManager_AdditivelyLoadSceneFile(TemSceneHelper::SceneManager, runtime, false, true, false, false, NULL);
			sceneManagerScene = app::ScenesManager_GetSceneManagerScene(TemSceneHelper::SceneManager, runtime->fields.Scene, NULL);
		}

		if (tem::PtrInRange(sceneManagerScene) == true && tem::PtrInRange(sceneManagerScene->fields.SceneRoot) == true)
			return sceneManagerScene;

		return nullptr;
	}

	app::GameObject* tem::SceneList::GetGameObjectFromHierarchyName(std::vector<std::string> hierarchy, app::GameObject* object)
	{
		std::vector<std::string> tempHierarchy = hierarchy;

		if (tempHierarchy.size() > 1 && tempHierarchy[0] == "Scene Roots")
			tempHierarchy.erase(tempHierarchy.begin());
		
		if (tempHierarchy.size() < 1 || (tempHierarchy.size() == 1 && (tempHierarchy[0] == "Scene Roots" || tempHierarchy[0] == "")))
			return nullptr;

		app::RuntimeSceneMetaData* runtime = app::ScenesManager_GetSceneInformation(TemSceneHelper::SceneManager, string_new(tempHierarchy[0].data()), NULL);
		app::SceneManagerScene* sceneManagerScene = app::ScenesManager_GetFromCurrentScenes(TemSceneHelper::SceneManager, runtime, NULL);

		if (sceneManagerScene == nullptr && runtime != nullptr)
			sceneManagerScene = app::ScenesManager_GetSceneManagerScene(TemSceneHelper::SceneManager, runtime->fields.Scene, NULL);

		if (sceneManagerScene == nullptr && runtime != nullptr)
		{
			app::ScenesManager_AdditivelyLoadSceneFile(TemSceneHelper::SceneManager, runtime, false, true, false, false, NULL);
			sceneManagerScene = app::ScenesManager_GetSceneManagerScene(TemSceneHelper::SceneManager, runtime->fields.Scene, NULL);
		}

		app::GameObject* tempObject = object;

		if (tempObject == nullptr)
		{
			if (tem::SceneList::SpecialSceneHierarchyMap.find(tempHierarchy[0]) != tem::SceneList::SpecialSceneHierarchyMap.end())
			{
				tempObject = reinterpret_cast<app::GameObject*>(tem::SceneList::SpecialSceneHierarchyMap[tempHierarchy[0]]);
				tempHierarchy.erase(tempHierarchy.begin());
			}
			else if (sceneManagerScene != nullptr && sceneManagerScene->fields.SceneRoot != nullptr)
			{
				tempObject = app::Component_1_get_gameObject((app::Component_1*)sceneManagerScene->fields.SceneRoot, NULL);
				tempHierarchy.erase(tempHierarchy.begin());
			}

			if (tempObject == nullptr)
				return nullptr;
		}

		app::Transform* transform = app::GameObject_get_transform(tempObject, NULL);

		while (tempHierarchy.size() > 0)
		{
			app::Transform* childTransform = app::Transform_FindChild(transform, string_new(tempHierarchy[0].data()), NULL);

			if (childTransform != nullptr)
			{
				tempHierarchy.erase(tempHierarchy.begin());
				transform = childTransform;

				if (tempHierarchy.size() == 0)
					return app::Component_1_get_gameObject((app::Component_1*)transform, NULL);
			}
			else
				return nullptr;
		}

		if (tempHierarchy.size() == 0)
			return app::Component_1_get_gameObject((app::Component_1*)transform, NULL);
		else
			return nullptr;
	}

	std::vector<app::RuntimeSceneMetaData*> tem::SceneList::GetScenesToLoad()
	{
		std::vector<app::RuntimeSceneMetaData*> scenes;
		bool existsAlready = false;

		std::vector<std::string> sceneNames;
		tem::SceneHierarchy::GetScenesToLoad(sceneNames, tem::SceneList::RootHierarchy);

		for (std::string& sceneName : sceneNames)
		{
			app::RuntimeSceneMetaData* runtime = app::ScenesManager_GetSceneInformation(TemSceneHelper::SceneManager, string_new(sceneName.data()), NULL);

			if (runtime != nullptr)
			{
				for (auto& scene : scenes)
				{
					if (runtime == scene)
						existsAlready = true;
				}

				if (existsAlready == false)
					scenes.push_back(runtime);
			}
		}

		return scenes;
	}
}