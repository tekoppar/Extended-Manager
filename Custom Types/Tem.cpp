#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include "json.hpp"
#include "Tem.h"

namespace tem {
	void to_json(nlohmann::json& j, const tem::Vector4& p)
	{
		j = nlohmann::json{ {"r", p.X}, {"g", p.Y}, {"b", p.Z}, {"a", p.A} };
	}

	void from_json(const nlohmann::json& j, tem::Vector4& p)
	{
		j.at("r").get_to(p.X);
		j.at("g").get_to(p.Y);
		j.at("b").get_to(p.Z);
		j.at("a").get_to(p.A);
	}
}