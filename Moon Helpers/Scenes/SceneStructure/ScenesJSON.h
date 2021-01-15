#pragma once

#ifndef _SCENESJSON_H
#define _SCENESJSON_H
#include "Component.h"
#include "SceneObject.h"
#include "SceneHierarchy.h"
#include "json.hpp"

namespace tem {
	void to_json(nlohmann::json& j, const tem::Component& p);
	void from_json(const nlohmann::json& j, tem::Component& p);
	void to_json(nlohmann::json& j, const tem::SceneObject& p);
	void from_json(const nlohmann::json& j, tem::SceneObject& p);
	void to_json(nlohmann::json& j, const tem::SceneHierarchy& p);
	void from_json(const nlohmann::json& j, tem::SceneHierarchy& p);
}

#endif