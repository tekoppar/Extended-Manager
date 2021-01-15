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
	}

	void tem::SceneObject::GetObjectData()
	{
		std::vector<int> hierarchyIndex = this->SceneIndexHierarchy;
		hierarchyIndex.erase(hierarchyIndex.begin());
		app::GameObject* object = tem::SceneList::GetGameObjectFromHierarchyIndex(hierarchyIndex);

		if (object == nullptr)
			return;

		this->Fields = tem::FieldHelper::FillFields(object, tem::FieldHelper::GetFieldsFromClass(object->klass->_0.namespaze, object->klass->_0.name));
		this->Properties = tem::PropertyHelper::FillProperties(object, tem::PropertyHelper::GetPropertiesFromClass(object->klass->_0.namespaze, object->klass->_0.name));

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
					tem::ClassField::NestedPointers = std::vector<std::uintptr_t>();
					this->SceneComponents[i].FillFields(components->vector[i], tem::FieldHelper::GetFieldsFromClass(components->vector[i]->klass->_0.namespaze, components->vector[i]->klass->_0.name));
					this->SceneComponents[i].FillProperties(components->vector[i], tem::PropertyHelper::GetPropertiesFromClass(components->vector[i]->klass->_0.namespaze, components->vector[i]->klass->_0.name));
				}
			}
		}
	}

	void tem::SceneObject::GetObjectData(app::GameObject* object)
	{
		std::vector<int> hierarchyIndex = this->SceneIndexHierarchy;
		hierarchyIndex.erase(hierarchyIndex.begin());

		if (object == nullptr)
			return;

		//this->Fields = tem::FieldHelper::FillFields(object, tem::FieldHelper::GetFieldsFromClass(object->klass->_0.namespaze, object->klass->_0.name));
		//this->Properties = tem::PropertyHelper::FillProperties(object, tem::PropertyHelper::GetPropertiesFromClass(object->klass->_0.namespaze, object->klass->_0.name));

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
					this->SceneComponents[i].FillFields(components->vector[i], tem::FieldHelper::GetFieldsFromClass(components->vector[i]->klass->_0.namespaze, components->vector[i]->klass->_0.name));
					this->SceneComponents[i].FillProperties(components->vector[i], tem::PropertyHelper::GetPropertiesFromClass(components->vector[i]->klass->_0.namespaze, components->vector[i]->klass->_0.name));
				}
			}
		}
	}

	void tem::SceneObject::FieldPropertyHasChanged(app::GameObject* object, std::string componentName, std::string fieldPropertyName, std::string value)
	{
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
		}

	}

	void tem::SceneObject::GetObjectDataGameObject(app::GameObject* object)
	{
		std::vector<int> hierarchyIndex = this->SceneIndexHierarchy;
		hierarchyIndex.erase(hierarchyIndex.begin());

		if (object == nullptr)
			return;

		this->Fields = tem::FieldHelper::FillFields(object, tem::FieldHelper::GetFieldsFromClass(object->klass->_0.namespaze, object->klass->_0.name));
		this->Properties = tem::PropertyHelper::FillProperties(object, tem::PropertyHelper::GetPropertiesFromClass(object->klass->_0.namespaze, object->klass->_0.name));
	}

	void tem::SceneObject::SetComponentDataField(std::string componentName, tem::ClassField field)
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

		for (int i = 0; i < count; i++)
		{
			if (components->vector[i] != nullptr)
			{
				if (components->vector[i]->klass->_0.name != NULL && std::string(components->vector[i]->klass->_0.name) == componentName)
					field.SetFieldValue((std::uintptr_t)components->vector[i], components->vector[i]->klass->_0.namespaze, components->vector[i]->klass->_0.name, field.Name, field.FieldValue, &field);
			}
			else
				return;
		}
	}

	void tem::SceneObject::SetComponentDataProperty(std::string componentName, tem::ClassProperty prop)
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

		for (int i = 0; i < count; i++)
		{
			if (components->vector[i] != nullptr)
			{
				if (components->vector[i]->klass->_0.name != NULL && std::string(components->vector[i]->klass->_0.name) == componentName)
					prop.SetPropertyValue(components->vector[i], components->vector[i]->klass->_0.namespaze, components->vector[i]->klass->_0.name, prop.Name, prop.PropertyValue, &prop);
			}
			else
				return;
		}
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
				if (isField == true)
				{
					if (component.Fields.size() > 0)
					{
						tem::ClassField field;
						for (int i = 0; i < component.Fields.size(); i++)
						{
							if (component.Fields[i].Name == fieldPropName)
								field = component.Fields[i];
						}

						for (int i = 0; i < count; i++)
						{
							if (components->vector[i] != nullptr && components->vector[i]->klass->_0.name != NULL && componentName == components->vector[i]->klass->_0.name)
							{
								field.SetFieldValue((std::uintptr_t)components->vector[i], components->vector[i]->klass->_0.namespaze, components->vector[i]->klass->_0.name, fieldPropName, value, &field);
								field.FieldValue = value;
								this->HasChanged = true;
								return;
							}
						}
					}
				}
				else
				{
					tem::ClassProperty Property;
					for (int i = 0; i < component.Properties.size(); i++)
					{
						if (component.Properties[i].Name == fieldPropName)
							Property = component.Properties[i];
					}

					for (int i = 0; i < count; i++)
					{
						if (components->vector[i] != nullptr && components->vector[i]->klass->_0.name != NULL && componentName == components->vector[i]->klass->_0.name)
						{
							Property.SetPropertyValue(components->vector[i], components->vector[i]->klass->_0.namespaze, components->vector[i]->klass->_0.name, fieldPropName, value, &Property);
							Property.PropertyValue = value;
							this->HasChanged = true;
							return;
						}
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

		if (componentName == "GameObject")
		{
			if (isField == true)
			{
				tem::ClassField* field = nullptr;

				if (fieldHierarchy.size() > 0)
				{
					for (int i = 0; i < Fields.size(); i++)
					{
						if (fieldHierarchy.size() > 0 && Fields[i].Name == fieldHierarchy[0])
						{
							fieldHierarchy.erase(fieldHierarchy.begin());

							if (fieldHierarchy.size() > 0)
							{
								field = Fields[i].GetNestedField(fieldHierarchy);
								break;
							}
							else
							{
								field = &Fields[i];
								break;
							}
						}
					}
				}
				else
					field = FindField(fieldPropName, Fields);

				if (field == nullptr)
					return;

				if (isNestedField == true)
				{
					field->SetNestedFieldValue((std::uintptr_t)object, object->klass->_0.namespaze, object->klass->_0.name, sutil::SplitTem(fieldPropPath, "."), value);
				}
				else
				{
					field->SetFieldValue((std::uintptr_t)object, object->klass->_0.namespaze, object->klass->_0.name, fieldPropName, value, field);
				}
				field->FieldValue = value;
				this->HasChanged = true;
				return;
			}
			else
			{
				tem::ClassProperty* Property = FindProperty(fieldPropName, Properties);

				if (Property == nullptr)
					return;

				Property->SetPropertyValue((void*)object, object->klass->_0.namespaze, object->klass->_0.name, fieldPropName, value, Property);
				Property->PropertyValue = value;
				this->HasChanged = true;
				return;
			}
		}
		else
		{
			for (tem::Component &component : SceneComponents)
			{
				if (component.ClassName == componentName)
				{
					if (isField == true)
					{
						tem::ClassField* field = nullptr;

						if (fieldHierarchy.size() > 0)
						{
							for (int i = 0; i < component.Fields.size(); i++)
							{
								if (fieldHierarchy.size() > 0 && component.Fields[i].Name == fieldHierarchy[0])
								{
									fieldHierarchy.erase(fieldHierarchy.begin());

									if (fieldHierarchy.size() > 0)
										field = component.Fields[i].GetNestedField(fieldHierarchy);
									else
										field = &component.Fields[i];

									break;
								}
							}
						}
						else
							field = FindField(fieldPropName, component.Fields);

						if (field == nullptr)
							return;

						for (int i = 0; i < count; i++)
						{
							if (components->vector[i] != nullptr && components->vector[i]->klass->_0.name != NULL && componentName == components->vector[i]->klass->_0.name)
							{
								if (isNestedField == true)
									field->SetNestedFieldValue((std::uintptr_t)components->vector[i], components->vector[i]->klass->_0.namespaze, components->vector[i]->klass->_0.name, sutil::SplitTem(fieldPropPath, "."), value);
								else
									field->SetFieldValue((std::uintptr_t)components->vector[i], components->vector[i]->klass->_0.namespaze, components->vector[i]->klass->_0.name, fieldPropName, value, field);

								field->FieldValue = value;
								this->HasChanged = true;
								return;
							}
						}
					}
					else
					{
						tem::ClassProperty* Property = FindProperty(fieldPropName, component.Properties);

						for (int i = 0; i < count; i++)
						{
							if (components->vector[i] != nullptr && components->vector[i]->klass->_0.name != NULL && componentName == components->vector[i]->klass->_0.name)
							{
								Property->SetPropertyValue(components->vector[i], components->vector[i]->klass->_0.namespaze, components->vector[i]->klass->_0.name, fieldPropName, value, Property);
								Property->PropertyValue = value;
								this->HasChanged = true;
								return;
							}
						}
					}
				}
			}
		}
	}

	tem::ClassProperty* tem::SceneObject::FindProperty(std::string name, std::vector<tem::ClassProperty> &properties)
	{
		for (int i = 0; i < properties.size(); i++)
		{
			if (properties[i].Name == name)
				return &properties[i];
		}

		return nullptr;
	}

	tem::ClassField* tem::SceneObject::FindField(std::string name, std::vector<tem::ClassField> &fields)
	{
		for (int i = 0; i < fields.size(); i++)
		{
			if (fields[i].Name == name)
				return &fields[i];
		}

		return nullptr;
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