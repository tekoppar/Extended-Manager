#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <future>
#include <unordered_map>

#include "StringUtils.h"
#include "ManagerDef.h"
#include "TemSceneHelper.h"
#include "TemFramework.h"
#include "SceneList.h"

#include "Component.h"

namespace tem {

	Component::Component()
	{
		this->ClassName = "";
		this->ObjectData = tem::ObjectData();
	}

	Component::Component(std::string className, tem::ObjectData objectData)
	{
		this->ClassName = className;
		this->ObjectData = objectData;
	}

	/*int Component::HasField(std::string name)
	{
		for (int i = 0; i < Fields.size(); i++)
		{
			if (Fields[i].Name == name)
				return i;
		}

		return -1;
	}*/

	void Component::FillFields(app::Component_1* component, std::vector<FieldInfo*> fields)
	{
		for (FieldInfo* field : fields)
		{
			int index = 0; //HasField(field->name);

			if (index == -1)
			{
				tem::ClassField classField = tem::ClassField(field);

				app::Type* fieldClassType = GetType(component->klass->_0.namespaze, component->klass->_0.name);
				app::FieldInfo_1* field1 = app::TypeExtensions_2_GetField(fieldClassType, string_new(field->name), NULL);
				if (field1 != nullptr)
					classField.IsStatic = app::FieldInfo_1_get_IsStatic(field1, NULL);

				classField.GetFieldValue((std::uintptr_t)component, field);
				//this->Fields.push_back(classField);
			}
			//else
				//Fields[index].GetFieldValue((std::uintptr_t)component, field);
		}
	}

	/*int Component::HasProperty(std::string name)
	{
		for (int i = 0; i < Properties.size(); i++)
		{
			if (Properties[i].Name == name)
				return i;
		}

		return -1;
	}*/

	void Component::FillProperties(app::Component_1* component, std::vector<PropertyInfo*> properties)
	{
		for (PropertyInfo* Property : properties)
		{
			int index = 0;// HasProperty(Property->name);
			
			if (index == -1)
			{
				tem::ClassProperty CProperty = tem::ClassProperty(Property);
				CProperty.GetPropertyValue(component, Property);
				//this->Properties.push_back(CProperty);
			}
			//else
				//Properties[index].GetPropertyValue(component, Property);
		}
	}

	std::string Component::ToJsonString()
	{
		return "{\"ClassName\":\"" + this->ClassName + "\",\"ObjectData\":" + ObjectData.ToJsonString() + "}";
	}

	std::string Component::SaveJsonComponent()
	{
		return "{\"ClassName\":\"" + this->ClassName + "\",\"ObjectData\":" + ObjectData.ToJsonString() + "}";
	}

	app::Component_1* Component::GetComponentByNameFromObject(app::GameObject* object, std::string name)
	{
		app::Component_1__Array* components = app::GameObject_GetComponents(object, tem::SceneList::ComponentType, NULL);
		int count = app::Array_System_Collections_ICollection_get_Count((app::Array*)components, NULL);

		if (components->vector[0] == nullptr)
			return nullptr;

		for (int i = 0; i < count; i++)
		{
			if (components->vector[i] != nullptr && components->vector[i]->klass->_0.name == name)
				return components->vector[i];
		}

		return nullptr;
	}
}