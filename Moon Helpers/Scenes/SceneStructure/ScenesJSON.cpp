#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include "FieldHelper.h"
#include "PropertyHelper.h"
#include "TemFramework.h"
#include "Tem.h"
#include "json.hpp"
#include "ScenesJSON.h"
#include "FrameworkJSON.h"

namespace tem {
	void to_json(nlohmann::json& j, const tem::Component& p)
	{
		j = nlohmann::json{ {"ClassName", p.ClassName}, {"Fields", nlohmann::json::array()}, {"Properties", nlohmann::json::array()} };

		for (auto& el : p.Fields) {
			if (el.HasChanged == true)
				j["Fields"].push_back(el);
		}
		for (auto& el : p.Properties) {
			if (el.HasChanged == true)
				j["Properties"].push_back(el);
		}
	}

	void from_json(const nlohmann::json& j, tem::Component& p)
	{
		j.at("ClassName").get_to(p.ClassName);
		j.at("Fields").get_to(p.Fields);
		j.at("Properties").get_to(p.Properties);
	}

	void to_json(nlohmann::json& j, const tem::SceneObject& p)
	{
		j = nlohmann::json{ {"IsCustomObject", p.IsCustomObject}, {"HasChanged", p.HasChanged}, {"Name", p.Name}, {"ParentName", p.ParentName}, {"ClassName", p.ClassName}, {"SceneComponents", p.SceneComponents}, {"HierarchyIndex", p.HierarchyIndex}, {"SceneIndexHierarchy", p.SceneIndexHierarchy}, {"Fields", nlohmann::json::array()}, {"Properties", nlohmann::json::array()}, {"ClonedSceneNameHierarchy", p.ClonedSceneNameHierarchy} };
	
		for (auto& el : p.Fields) {
			if (el.HasChanged == true)
				j["Fields"].push_back(el);
		}
		for (auto& el : p.Properties) {
			if (el.HasChanged == true)
				j["Properties"].push_back(el);
		}
	}

	void from_json(const nlohmann::json& j, tem::SceneObject& p)
	{
		j.at("IsCustomObject").get_to(p.IsCustomObject);
		j.at("HasChanged").get_to(p.HasChanged);
		j.at("Name").get_to(p.Name);
		j.at("ParentName").get_to(p.ParentName);
		j.at("ClassName").get_to(p.ClassName);
		j.at("SceneComponents").get_to(p.SceneComponents);
		j.at("HierarchyIndex").get_to(p.HierarchyIndex);
		j.at("SceneIndexHierarchy").get_to(p.SceneIndexHierarchy);
		j.at("Fields").get_to(p.Fields);
		j.at("Properties").get_to(p.Properties);
		j.at("ClonedSceneNameHierarchy").get_to(p.ClonedSceneNameHierarchy);
	}

	void to_json(nlohmann::json& j, const tem::SceneHierarchy& p)
	{
		j = nlohmann::json{ {"Object", p.Object} };
		for (auto& [key, value] : p.SceneChildren) {
			j["SceneChildren"][std::to_string(key)] = value;
		}
	}

	void from_json(const nlohmann::json& j, tem::SceneHierarchy& p)
	{
		j.at("Object").get_to(p.Object);
		if (j.contains("SceneChildren") == true)
		{
			for (auto& el : j.at("SceneChildren").items()) {
				p.SceneChildren[std::stoi(el.key())] = el.value();
			}
		}
	}
}