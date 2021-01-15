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
		this->Fields = std::vector<tem::ClassField>();
		this->Properties = std::vector<tem::ClassProperty>();
	}

	Component::Component(std::string className, std::vector<tem::ClassField> fields, std::vector<tem::ClassProperty> properties)
	{
		this->ClassName = className;
		this->Fields = fields;
		this->Properties = properties;
	}

	int Component::HasField(std::string name)
	{
		for (int i = 0; i < Fields.size(); i++)
		{
			if (Fields[i].Name == name)
				return i;
		}

		return -1;
	}

	void Component::FillFields(app::Component_1* component, std::vector<FieldInfo*> fields)
	{
		for (FieldInfo* field : fields)
		{
			int index = HasField(field->name);

			if (index == -1)
			{
				tem::ClassField classField = tem::ClassField(field);

				app::Type* fieldClassType = GetType(component->klass->_0.namespaze, component->klass->_0.name);
				app::FieldInfo_1* field1 = app::TypeExtensions_2_GetField(fieldClassType, string_new(field->name), NULL);
				if (field1 != nullptr)
					classField.IsStatic = app::FieldInfo_1_get_IsStatic(field1, NULL);

				classField.GetFieldValue((std::uintptr_t)component, field);
				this->Fields.push_back(classField);
			}
			else
				Fields[index].GetFieldValue((std::uintptr_t)component, field);
		}
	}

	int Component::HasProperty(std::string name)
	{
		for (int i = 0; i < Properties.size(); i++)
		{
			if (Properties[i].Name == name)
				return i;
		}

		return -1;
	}

	void Component::FillProperties(app::Component_1* component, std::vector<PropertyInfo*> properties)
	{
		for (PropertyInfo* Property : properties)
		{
			int index = HasProperty(Property->name);
			
			if (index == -1)
			{
				tem::ClassProperty CProperty = tem::ClassProperty(Property);
				CProperty.GetPropertyValue(component, Property);
				this->Properties.push_back(CProperty);
			}
			else
				Properties[index].GetPropertyValue(component, Property);
		}
	}

	std::string Component::ToJsonString()
	{
		std::string json = "{\"ClassName\":\"" + this->ClassName + "\",\"Fields\":[";
		for (int i = 0; i < this->Fields.size(); i++)
		{
			tem::ClassField field = this->Fields[i];
			json += field.ToJsonString();
			if (this->Fields.size() - 1 > i)
				json += ",";
		}

		json += "],\"Properties\":[";

		for (int i = 0; i < this->Properties.size(); i++)
		{
			tem::ClassProperty Property = this->Properties[i];
			json += Property.ToJsonString();
			if (this->Properties.size() - 1 > i)
				json += ",";
		}

		return json + "]}";
	}

	std::string Component::SaveJsonComponent()
	{
		std::string json = "{\"" + this->ClassName + "\":[[";
		for (int i = 0; i < this->Fields.size(); i++)
		{
			tem::ClassField field = this->Fields[i];
			json += field.SaveJsonField();
			if (this->Fields.size() - 1 > i)
				json += ",";
		}

		json += "],[";

		for (int i = 0; i < this->Properties.size(); i++)
		{
			tem::ClassProperty Property = this->Properties[i];
			json += Property.SaveJsonProperty();
			if (this->Properties.size() - 1 > i)
				json += ",";
		}

		return json + "]]}";
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