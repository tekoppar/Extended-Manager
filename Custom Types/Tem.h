#pragma once

#ifndef _TEM_H
#define _TEM_H

#include "Vector3.h"
#include "Rect.h"
#include "Vector4.h"
#include "json.hpp"

namespace tem {
	void to_json(nlohmann::json& j, const tem::Vector4& p);
	void from_json(const nlohmann::json& j, tem::Vector4& p);
}

#endif