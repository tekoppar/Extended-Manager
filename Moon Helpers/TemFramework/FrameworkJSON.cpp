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
		j = nlohmann::json{ {"HasChanged", p.HasChanged}, {"Name", p.Name}, {"ReturnType", p.ReturnType}, {"PropertyValue", p.PropertyValue} };
	}

	void from_json(const nlohmann::json& j, tem::ClassProperty& p)
	{
		j.at("HasChanged").get_to(p.HasChanged);
		j.at("Name").get_to(p.Name);
		j.at("ReturnType").get_to(p.ReturnType);
		j.at("PropertyValue").get_to(p.PropertyValue);
	}
}