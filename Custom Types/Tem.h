#pragma once

#ifndef _TEM_H
#define _TEM_H
#define PI 3.14159265f

#include <string>
#include <vector>

#include "Vector2.h"
#include "Vector3.h"
#include "Rect.h"
#include "Vector4.h"
#include "Quaternion.h"
#include "Bounds.h"
#include "Matrix4x4.h"
#include "AnimationContext.h"
#include "AnimatorStateInfo.h"
#include "ExplosionSettings.h"
#include "SharedUpdateData.h"
#include "UVCalculator.h"
#include "TemMath.h"
#include "VectorAlgo.h"
#include "json.hpp"

namespace tem {
	extern std::uintptr_t LOWPTRVALUE;
	extern std::uintptr_t HIGHPTRVALUE;
	static const bool PtrInRange(void* ptr)
	{
		return ptr != nullptr && (std::uintptr_t)ptr > LOWPTRVALUE && (std::uintptr_t)ptr < HIGHPTRVALUE;
	}
	static const bool PtrInRange(std::uintptr_t ptr)
	{
		return ptr > LOWPTRVALUE && ptr < HIGHPTRVALUE;
	}

	enum class AxisType {
		X = 0,
		Y = 1,
		Z = 2,
		NONE = 3,
		XY = 4
	};
	enum class VariableType {
		Null = -1,
		String = 0,
		Integer = 1,
		Char = 2,
		Pointer = 3,
		Vector = 4,
		Map = 5,
		Float = 6,
		Bool = 7,
		Rect = 8,
		Quaternion = 9,
		Vector3 = 10,
		Vector4 = 11,
		Color = 12,
		Vector2 = 13, 
		Enum = 14,
		Bounds = 15,
		Long = 16,
		Short = 17,
		UShort = 18,
		UInt = 19,
		ULong = 20,
		Matrix4x4 = 21
	};

	void to_json(nlohmann::json& j, const tem::Vector4& p);
	void from_json(const nlohmann::json& j, tem::Vector4& p);
	void to_json(nlohmann::json& j, const tem::Vector3& p);
	void from_json(const nlohmann::json& j, tem::Vector3& p);
	void to_json(nlohmann::json& j, const tem::Vector2& p);
	void from_json(const nlohmann::json& j, tem::Vector2& p);
	void to_json(nlohmann::json& j, const tem::Rect& p);
	void from_json(const nlohmann::json& j, tem::Rect& p);
	void to_json(nlohmann::json& j, const tem::Bounds& p);
	void from_json(const nlohmann::json& j, tem::Bounds& p);
	bool IsDigit(char& s);
	VariableType IsIntegerOrFloat(std::string& s);
	std::vector<int> StringToIntVector(std::string& s, std::string delimiter);
	std::string IntVectorToString(std::vector<int>& s, std::string delimiter);
	std::string StringVectorToString(std::vector<std::string>& s, std::string delimiter);
}

#endif