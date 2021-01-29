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
		j = nlohmann::json{ {"ClassName", p.ClassName}, {"ObjectData", {}} };

		if (p.ObjectData.ShouldSave() == true)
			j["ObjectData"] = p.ObjectData;
	}

	void from_json(const nlohmann::json& j, tem::Component& p)
	{
		j.at("ClassName").get_to(p.ClassName);

		if (j.at("ObjectData").is_null() == true)
			p.ObjectData = tem::ObjectData();
		else
			j.at("ObjectData").get_to(p.ObjectData);
	}

	void to_json(nlohmann::json& j, const tem::SceneObject& p)
	{
		j = nlohmann::json{ {"IsCustomObject", p.IsCustomObject}, {"HasChanged", p.HasChanged}, {"Name", p.Name}, {"ParentName", p.ParentName}, {"ClassName", p.ClassName}, {"SceneComponents", p.SceneComponents}, {"HierarchyIndex", p.HierarchyIndex}, {"SceneIndexHierarchy", p.SceneIndexHierarchy}, {"ClonedSceneNameHierarchy", p.ClonedSceneNameHierarchy}, {"ClonedPosition", p.ClonedPosition} };
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
		j.at("ClonedSceneNameHierarchy").get_to(p.ClonedSceneNameHierarchy);

		if (j.contains("ClonedPosition"))
			j.at("ClonedPosition").get_to(p.ClonedPosition);
		else
			p.ClonedPosition = tem::Vector3(0.0f);
	}

	void to_json(nlohmann::json& j, const tem::SceneHierarchy& p)
	{
		j = nlohmann::json{ {"Object", p.Object} };
		for (auto& child : p.SceneChildren) {
			if (child.second.Object.SceneIndexHierarchy.size() > 1 && child.second.Object.SceneIndexHierarchy[1] > 299 && child.second.Object.SceneIndexHierarchy[1] < 500)
				j["SceneChildren"][std::to_string(child.first)] = child.second;
		}
	}

	void from_json(const nlohmann::json& j, tem::SceneHierarchy& p)
	{
		j.at("Object").get_to(p.Object);
		if (j.contains("SceneChildren") == true)
		{
			for (auto& el : j.at("SceneChildren").items()) {
				tem::SceneHierarchy value = el.value();

				if (value.Object.SceneIndexHierarchy.size() > 1 && value.Object.SceneIndexHierarchy[1] > 299 && value.Object.SceneIndexHierarchy[1] < 500)
					p.SceneChildren[std::stoi(el.key())] = value;
			}
		}
	}

	void to_json(nlohmann::json& j, const tem::SceneData& p)
	{
		j = nlohmann::json{ {"Name", p.Name}, {"Position", p.Position}, {"Size", p.Size}, {"LoadingZone", p.LoadingZone} };
	}

	void from_json(const nlohmann::json& j, tem::SceneData& p)
	{
		j.at("Name").get_to(p.Name);
		j.at("Position").get_to(p.Position);
		j.at("Size").get_to(p.Size);
		j.at("LoadingZone").get_to(p.LoadingZone);
	}
}