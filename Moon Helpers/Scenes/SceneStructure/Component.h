#pragma once

#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "FieldHelper.h"
#include "PropertyHelper.h"
#include "TemFramework.h"
#include "Adresses.h"

namespace tem {
	class Component
	{
	public:
		std::string ClassName = "";
		tem::ObjectData ObjectData = tem::ObjectData();

		Component();
		Component(std::string className, tem::ObjectData objectData);

		void FillFields(app::Component_1* component, std::vector<FieldInfo*> fields);
		void FillProperties(app::Component_1* component, std::vector<PropertyInfo*> properties);
		std::string ToJsonString();
		std::string SaveJsonComponent();
		//int HasField(std::string name);
		//int HasProperty(std::string name);

		static app::Component_1* GetComponentByNameFromObject(app::GameObject* object, std::string name);
	};
}

#endif