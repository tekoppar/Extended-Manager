#pragma once

#ifndef _VECTOR3_H
#define _VECTOR3_H

#include "StringUtils.h"

namespace tem 
{
	class Vector4;
	class Vector2;

	class Vector3 
	{
	public:
		static tem::Vector3 Forward;
		static tem::Vector3 Back;
		static tem::Vector3 Down;
		static tem::Vector3 Left;
		static tem::Vector3 Right;
		static tem::Vector3 Up;

		float X = 0.0f;
		float Y = 0.0f;
		float Z = 0.0f;

		Vector3();
		Vector3(float x, float y, float z);
		Vector3(float x, float y);
		Vector3(float all);
		Vector3(tem::Vector4& vec);
		Vector3(tem::Vector2& vec);
		Vector3(int x, int y, int z);
		Vector3(app::Vector3* other);
		Vector3(app::Vector2* other);
		Vector3(app::Vector3 other);
		Vector3(app::Vector2 other);
		Vector3(std::string& other);
		Vector3(app::Color other);

		tem::Vector3& operator+=(const tem::Vector3& other);
		tem::Vector3& operator+=(const float& other);
		tem::Vector3 operator+(const tem::Vector3& other);
		tem::Vector3 operator+(const float& other);
		tem::Vector3 operator-(const tem::Vector3& other);
		tem::Vector3& operator-=(const tem::Vector3& other);
		tem::Vector3 operator-(const float& other);
		tem::Vector3& operator-=(const float& other);
		tem::Vector3& operator*=(const float& other);
		tem::Vector3 operator*(const float& other);
		bool operator==(tem::Vector3& other);

		bool IsSet();
		bool Equals(tem::Vector3& vec);
		bool Equals(tem::Vector3 vec);
		bool NearlyEqual(tem::Vector3 vec);
		static app::Vector2 ToVector2(float x = 0.0f, float y = 0.0f);
		app::Vector3 ToMoon();
		app::Vector3* ToMoonP();
		app::Color ToColor();
		std::string ToString();
		static float Distance(const tem::Vector3& position, const tem::Vector3& subtract);
		static bool IsPositionInsideRect(app::Rect* rect, tem::Vector3 position);
		static bool IsPositionInsideRect(app::Rect rect, tem::Vector3 position);
	};
}

#endif