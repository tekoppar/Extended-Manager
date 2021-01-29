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
#include "SceneList.h"
#include "TreeItem.h"

#include "SceneObject.h"

namespace tem {
	SceneObject::SceneObject()
	{
		this->IsCustomObject = false;
		this->HasChanged = false;
		this->Name = "";
		this->ParentName = "";
		this->Parent = 0x0;
		this->ClassName = "";
		this->SceneComponents = std::vector<tem::Component>();
		this->SceneIndexHierarchy = std::vector<int>();
		this->HierarchyIndex = -1;
		this->ClonedPosition = tem::Vector3(0.0f);
	}

	SceneObject::SceneObject(bool isCustomObject, bool hasChanged, std::string name, std::string parentName, std::uintptr_t parent,
		std::string className, std::vector<tem::Component> sceneComponents, std::vector<int> sceneIndexHierarchy, int hierarchyIndex)
	{
		this->IsCustomObject = isCustomObject;
		this->HasChanged = hasChanged;
		this->Name = name;
		this->ParentName = parentName;
		this->Parent = parent;
		this->ClassName = className;
		this->SceneComponents = sceneComponents;
		this->SceneIndexHierarchy = sceneIndexHierarchy;
		this->HierarchyIndex = hierarchyIndex;
		this->ClonedSceneNameHierarchy = std::vector<std::string>();
		this->ClonedPosition = tem::Vector3(0.0f);
	}

	void tem::SceneObject::GetObjectData()
	{
		std::vector<int> hierarchyIndex = this->SceneIndexHierarchy;
		hierarchyIndex.erase(hierarchyIndex.begin());
		app::GameObject* object = tem::SceneList::GetGameObjectFromHierarchyIndex(hierarchyIndex);

		if (object == nullptr)
			return;

		app::Transform* transform = app::GameObject_get_transform(object, NULL);
		app::Component_1__Array* components = app::GameObject_GetComponents(object, tem::SceneList::ComponentType, NULL);
		int count = app::Array_System_Collections_ICollection_get_Count((app::Array*)components, NULL);

		for (int i = 0; i < count; i++)
		{
			if (components->vector[i] != nullptr && i < this->SceneComponents.size())
			{
				std::string comonentClassName = components->vector[i]->klass->_0.name;
				if (this->SceneComponents[i].ClassName == comonentClassName)
				{
					this->SceneComponents[i].ObjectData.Namespace = components->vector[i]->klass->_0.namespaze;
					this->SceneComponents[i].ObjectData.Name = components->vector[i]->klass->_0.name;
					this->SceneComponents[i].ObjectData.FillObjectData((std::uintptr_t)components->vector[i]);
					tem::ObjectData::NestedPointers.clear();
				}
			}
		}
	}

	void tem::SceneObject::GetObjectData(app::GameObject* object)
	{
		if (this->SceneIndexHierarchy.size() == 0)
			return;

		std::vector<int> hierarchyIndex = this->SceneIndexHierarchy;
		hierarchyIndex.erase(hierarchyIndex.begin());

		if (object == nullptr)
			return;

		app::Transform* transform = app::GameObject_get_transform(object, NULL);
		app::Component_1__Array* components = app::GameObject_GetComponents(object, tem::SceneList::ComponentType, NULL);
		int count = app::Array_System_Collections_ICollection_get_Count((app::Array*)components, NULL);

		for (int i = 0; i < count; i++)
		{
			if (components->vector[i] != nullptr && i < this->SceneComponents.size())
			{
				std::string comonentClassName = components->vector[i]->klass->_0.name;
				if (this->SceneComponents[i].ClassName == comonentClassName)
				{
					if (this->SceneComponents[i].ObjectData.Namespace != components->vector[i]->klass->_0.namespaze)
						this->SceneComponents[i].ObjectData.Namespace = components->vector[i]->klass->_0.namespaze;

					if (this->SceneComponents[i].ObjectData.Name != components->vector[i]->klass->_0.name || this->SceneComponents[i].ObjectData.ClassName != components->vector[i]->klass->_0.name)
						this->SceneComponents[i].ObjectData.Name = this->SceneComponents[i].ObjectData.ClassName = components->vector[i]->klass->_0.name;

					this->SceneComponents[i].ObjectData.FillObjectData((std::uintptr_t)components->vector[i]);
					tem::ObjectData::NestedPointers.clear();
				}
			}
		}
	}

	void tem::SceneObject::FieldPropertyHasChanged(app::GameObject* object, std::string componentName, std::string fieldPropertyName, std::string value)
	{
		if (object == nullptr)
			return;

		for (int i = 0; i < SceneComponents.size(); i++)
		{
			if (SceneComponents[i].ClassName == componentName)
			{
				bool wasSet = SceneComponents[i].ObjectData.SetObjectData(componentName, fieldPropertyName, value);

				if (wasSet == false)
					TemLogger::Add("Failed to set " + fieldPropertyName + " to " + value + " in " + componentName);
			}
		}
 		/*app::Transform* transform = app::GameObject_get_transform(object, NULL);
		app::Component_1__Array* components = app::GameObject_GetComponents(object, tem::SceneList::ComponentType, NULL);
		int count = app::Array_System_Collections_ICollection_get_Count((app::Array*)components, NULL);

		for (int i = 0; i < count; i++)
		{
			if (components->vector[i] != nullptr && i < this->SceneComponents.size())
			{
				std::string comonentClassName = components->vector[i]->klass->_0.name;
				if (this->SceneComponents[i].ClassName == comonentClassName)
				{
					for (int i2 = 0; i2 < this->SceneComponents[i].Fields.size(); i2++)
					{
						tem::ClassField* ptrField = this->SceneComponents[i].Fields[i2].GetFieldByName(fieldPropertyName);

						if (ptrField != nullptr)
						{
							ptrField->FieldValue = value;
							ptrField->HasChanged = true;
						}
					}
					for (int i2 = 0; i2 < this->SceneComponents[i].Properties.size(); i2++)
					{
						if (this->SceneComponents[i].Properties[i2].Name == fieldPropertyName)
						{
							this->SceneComponents[i].Properties[i2].PropertyValue = value;
							this->SceneComponents[i].Properties[i2].HasChanged = true;
						}
					}
				}
			}
		}*/
	}

	void tem::SceneObject::SetComponentData(std::string componentName, std::string fieldPropName, std::string value, bool isField)
	{
		std::vector<int> hierarchyIndex = this->SceneIndexHierarchy;
		hierarchyIndex.erase(hierarchyIndex.begin());
		app::GameObject* object = tem::SceneList::GetGameObjectFromHierarchyIndex(hierarchyIndex);

		if (object == nullptr)
			return;

		app::Transform* transform = app::GameObject_get_transform(object, NULL);
		app::Component_1__Array* components = app::GameObject_GetComponents(object, tem::SceneList::ComponentType, NULL);
		int count = app::Array_System_Collections_ICollection_get_Count((app::Array*)components, NULL);

		if (components->vector[0] == nullptr)
			return;

		app::String* tempString = string_new(componentName.data());
		for (tem::Component &component : SceneComponents)
		{
			if (component.ClassName == componentName)
			{
				for (int i = 0; i < count; i++)
				{
					if (components->vector[i] != nullptr && tem::PtrInRange(components->vector[i]->klass) == true && components->vector[i]->klass->_0.name != NULL && componentName == components->vector[i]->klass->_0.name)
					{
						component.ObjectData.ClassName = components->vector[i]->klass->_0.name;
						component.ObjectData.Namespace = components->vector[i]->klass->_0.namespaze;
						std::vector<std::string> namePath = { };
						component.ObjectData.SetObjectData((std::uintptr_t)components->vector[i], namePath, component.ObjectData.Namespace, component.ObjectData.ClassName);
						component.ObjectData.HasChanged = true;
						this->HasChanged = true;
						return;
					}
				}
			}
		}
	}

	void tem::SceneObject::SetComponentData(app::GameObject* object, std::string componentName, std::string fieldPropPath, std::string fieldPropName, std::string value, bool isField)
	{
		std::vector<int> hierarchyIndex = this->SceneIndexHierarchy;
		hierarchyIndex.erase(hierarchyIndex.begin());

		if (object == nullptr)
			return;

		app::Transform* transform = app::GameObject_get_transform(object, NULL);
		app::Component_1__Array* components = app::GameObject_GetComponents(object, tem::SceneList::ComponentType, NULL);
		int count = app::Array_System_Collections_ICollection_get_Count((app::Array*)components, NULL);

		if (components->vector[0] == nullptr)
			return;

		app::String* tempString = string_new(componentName.data());
		std::vector<std::string> fieldHierarchy;
		bool isNestedField = false;
		if (fieldPropPath != "" && fieldPropPath != " ")
		{
			fieldHierarchy = sutil::SplitTem(fieldPropPath, ".");

			if (fieldHierarchy.size() > 1)
				isNestedField = true;
		}

		for (int i = 0; i < SceneComponents.size(); i++)
		{
			if (SceneComponents[i].ClassName == componentName)
			{
				for (int i = 0; i < count; i++)
				{
					if (tem::PtrInRange(components->vector[i]) == true && tem::PtrInRange(components->vector[i]->klass) == true && tem::PtrInRange(&components->vector[i]->klass->_0) == true && componentName == components->vector[i]->klass->_0.name)
					{
						if (fieldHierarchy[0] == componentName)
							fieldHierarchy.erase(fieldHierarchy.begin());

						tem::ObjectData::SetObjectData(fieldHierarchy, (std::uintptr_t)components->vector[i], components->vector[i]->klass->_0.namespaze, components->vector[i]->klass->_0.name, fieldPropName, value);
						SceneComponents[i].ObjectData.UpdateObjectData(fieldHierarchy, fieldPropName, value);
						SceneComponents[i].ObjectData.HasChanged = true;
					}
				}
			}
		}
	}

	bool tem::SceneObject::HasComponent(std::string className)
	{
		for (tem::Component &component : this->SceneComponents)
		{
			if (component.ClassName == className)
				return true;
		}

		return false;
	}
}