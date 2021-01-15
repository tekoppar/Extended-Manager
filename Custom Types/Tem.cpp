#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <string>
#include <vector>

#include "StringUtils.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Rect.h"
#include "Vector4.h"
#include "Quaternion.h"
#include "json.hpp"
#include "Tem.h"

tem::Vector3 tem::Vector3::Forward = tem::Vector3(0.0f, 0.0f, 1.0f);
tem::Vector3 tem::Vector3::Back = tem::Vector3(0.0f, 0.0f, -1.0f);
tem::Vector3 tem::Vector3::Down = tem::Vector3(0.0f, -1.0f, 0.0f);
tem::Vector3 tem::Vector3::Left = tem::Vector3(-1.0f, 0.0f, 0.0f);
tem::Vector3 tem::Vector3::Right = tem::Vector3(1.0f, 0.0f, 0.0f);
tem::Vector3 tem::Vector3::Up = tem::Vector3(0.0f, 1.0f, 0.0f);

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

	void to_json(nlohmann::json& j, const tem::Vector3& p)
	{
		j = nlohmann::json{ {"x", p.X}, {"y", p.Y}, {"z", p.Z} };
	}

	void from_json(const nlohmann::json& j, tem::Vector3& p)
	{
		j.at("x").get_to(p.X);
		j.at("y").get_to(p.Y);
		j.at("z").get_to(p.Z);
	}

	void to_json(nlohmann::json& j, const tem::Vector2& p)
	{
		j = nlohmann::json{ {"x", p.x}, {"y", p.y} };
	}

	void from_json(const nlohmann::json& j, tem::Vector2& p)
	{
		j.at("x").get_to(p.x);
		j.at("y").get_to(p.y);
	}

	void to_json(nlohmann::json& j, const tem::Rect& p)
	{
		j = nlohmann::json{ {"x", p.X}, {"y", p.Y}, {"Width", p.Width}, {"Height", p.Height} };
	}

	void from_json(const nlohmann::json& j, tem::Rect& p)
	{
		j.at("x").get_to(p.X);
		j.at("y").get_to(p.Y);
		j.at("Width").get_to(p.Width);
		j.at("Height").get_to(p.Height);
	}

	void to_json(nlohmann::json& j, const tem::Bounds& p)
	{
		j = nlohmann::json{ {"Center", p.Center}, {"Extents", p.Extents} };
	}

	void from_json(const nlohmann::json& j, tem::Bounds& p)
	{
		j.at("Center").get_to(p.Center);
		j.at("Extents").get_to(p.Extents);
	}

	bool IsDigit(char& s)
	{
		return s == '0' || s == '1' || s == '2' || s == '3' || s == '4' || s == '5' || s == '6' || s == '7' || s == '8' || s == '9';
	}

	VariableType IsIntegerOrFloat(std::string& s)
	{
		if ((IsDigit(s[0]) || s[0] == '-' && IsDigit(s[1])) && IsDigit(s[s.size() - 1]))
		{
			if (s.find(',') != std::string::npos || s.find('.') != std::string::npos)
				return VariableType::Float;

			return VariableType::Integer;
		}

		return VariableType::String;
	}

	std::vector<int> StringToIntVector(std::string& s, std::string delimiter)
	{
		std::vector<std::string> numberStrings = sutil::SplitTem(s, delimiter);
		std::vector<int> intVector;

		for (std::string number : numberStrings)
		{
			if (number != delimiter && IsIntegerOrFloat(number) == VariableType::Integer)
				intVector.push_back(std::stoi(number));
		}

		return intVector;
	}	

	std::string IntVectorToString(std::vector<int>& s, std::string delimiter)
	{
		std::string ss = "";

		for (int i = 0; i < s.size(); i++)
		{
			if (i >= s.size() - 1)
				ss += std::to_string(s[i]);
			else
				ss += std::to_string(s[i]) + delimiter;
		}

		return ss;
	}

	std::string StringVectorToString(std::vector<std::string>& s, std::string delimiter)
	{
		std::string ss = "";

		for (int i = 0; i < s.size(); i++)
		{
			if (i >= s.size() - 1)
				ss += s[i];
			else
				ss += s[i] + delimiter;
		}

		return ss;
	}
};