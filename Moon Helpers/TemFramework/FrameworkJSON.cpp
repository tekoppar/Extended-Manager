#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include "Tem.h"
#include "json.hpp"
#include "FrameworkJSON.h"

namespace tem {
	void to_json(nlohmann::json& j, const tem::ClassField& p)
	{
		j = nlohmann::json{ {"Name", p.Name}, {"TypeDefIndex", p.TypeDefIndex}, {"HasChanged", p.HasChanged}, {"Type", p.Type}, {"FieldValue", p.FieldValue}, {"Namespace", p.Namespace}, {"ClassName", p.ClassName} };
	}

	void from_json(const nlohmann::json& j, tem::ClassField& p)
	{
		j.at("Name").get_to(p.Name);
		j.at("TypeDefIndex").get_to(p.TypeDefIndex);
		j.at("HasChanged").get_to(p.HasChanged);
		j.at("Type").get_to(p.Type);
		j.at("FieldValue").get_to(p.FieldValue);
		j.at("Namespace").get_to(p.Namespace);
		j.at("ClassName").get_to(p.ClassName);
	}

	void to_json(nlohmann::json& j, const tem::ClassProperty& p)
	{
		j = nlohmann::json{ {"HasChanged", p.HasChanged}, {"Name", p.Name},  {"Namespace", p.Namespace}, {"ClassName", p.ClassName}, {"ReturnType", p.ReturnType}, {"PropertyValue", p.PropertyValue} };
	}

	void from_json(const nlohmann::json& j, tem::ClassProperty& p)
	{
		j.at("HasChanged").get_to(p.HasChanged);
		j.at("Name").get_to(p.Name);
		j.at("ReturnType").get_to(p.ReturnType);
		j.at("PropertyValue").get_to(p.PropertyValue);
		j.at("Namespace").get_to(p.Namespace);
		j.at("ClassName").get_to(p.ClassName);
	}

	void to_json(nlohmann::json& j, const tem::ObjectData& p)
	{
		j = nlohmann::json{ {"HasChanged", p.HasChanged}, {"Namespace", p.Namespace}, {"ClassName", p.ClassName}, {"Name", p.Name}, {"Fields", nlohmann::json::array()}, {"Properties", nlohmann::json::array()}, {"NestedObjects", nlohmann::json::array()} };

		for (auto& el : p.Fields)
		{
			if (el.HasChanged == true || el.Name == "position" || el.Name == "eulerAngles" || el.Name == "localScale")
				j["Fields"].push_back(el);
		}
		for (auto& el : p.Properties)
		{
			if (el.HasChanged == true || el.Name == "position" || el.Name == "eulerAngles" || el.Name == "localScale")
				j["Properties"].push_back(el);
		}

		for (auto& el : p.NestedObjects)
		{
			if (el.ShouldSave() == true)
				j["NestedObjects"].push_back(el);
		}
	}

	void from_json(const nlohmann::json& j, tem::ObjectData& p)
	{
		j.at("HasChanged").get_to(p.HasChanged);
		j.at("Namespace").get_to(p.Namespace);
		j.at("ClassName").get_to(p.ClassName);
		j.at("Name").get_to(p.Name);
		j.at("Fields").get_to(p.Fields);
		j.at("Properties").get_to(p.Properties);
		j.at("NestedObjects").get_to(p.NestedObjects);

		for (int i = 0; i < p.Fields.size(); i++)
		{
			p.Fields[i].Parent = &p;
		}

		for (int i = 0; i < p.Properties.size(); i++)
		{
			p.Properties[i].Parent = &p;
		}

		for (int i = 0; i < p.NestedObjects.size(); i++)
		{
			p.NestedObjects[i].Parent = &p;
		}
	}
}