#pragma once

#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "FieldHelper.h"
#include "PropertyHelper.h"
#include "Adresses.h"

namespace tem {
	class Component
	{
	public:
		std::string ClassName;
		std::vector<tem::ClassField> Fields;
		std::vector<tem::ClassProperty> Properties;

		Component();
		Component(std::string className, std::vector<tem::ClassField> fields, std::vector<tem::ClassProperty> properties);

		void FillFields(app::Component_1* component, std::vector<FieldInfo*> fields);
		void FillProperties(app::Component_1* component, std::vector<PropertyInfo*> properties);
		std::string ToJsonString();
		std::string SaveJsonComponent();
		int HasField(std::string name);
		int HasProperty(std::string name);

		static app::Component_1* GetComponentByNameFromObject(app::GameObject* object, std::string name);
	};
}

#endif