#pragma once

#ifndef _FRAMEWORKJSON_H
#define _FRAMEWORKJSON_H
#include "FieldHelper.h"
#include "PropertyHelper.h"
#include "TemFramework.h"
#include "json.hpp"

namespace tem {
	void to_json(nlohmann::json& j, const tem::ClassField& p);
	void from_json(const nlohmann::json& j, tem::ClassField& p);
	void to_json(nlohmann::json& j, const tem::ClassProperty& p);
	void from_json(const nlohmann::json& j, tem::ClassProperty& p);
	void to_json(nlohmann::json& j, const tem::ObjectData& p);
	void from_json(const nlohmann::json& j, tem::ObjectData& p);
}

#endif