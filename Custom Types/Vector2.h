#pragma once

#ifndef _VECTOR2_H
#define _VECTOR2_H

#include "StringUtils.h"

namespace tem 
{
	class Vector4;
	class Vector3;

	class Vector2 
	{
	public:
		float x = 0.0f;
		float y = 0.0f;

		Vector2(float x1 = 0.0f, float y1 = 0.0f);
		Vector2(int x1, int y1);
		Vector2(app::Vector2* other);
		Vector2(app::Vector2 other);
		Vector2(std::string& other);
		Vector2(app::Color other);

		tem::Vector2& operator+=(const tem::Vector2& other);
		tem::Vector2& operator+=(const tem::Vector3& other);
		tem::Vector2& operator+=(const float& other);
		tem::Vector2 operator+(const tem::Vector2& other);
		tem::Vector2 operator+(const tem::Vector3& other);
		tem::Vector2 operator+(const float& other);
		tem::Vector2 operator-(const tem::Vector2& other);
		tem::Vector2 operator-(const tem::Vector3& other);
		tem::Vector2& operator-=(const tem::Vector2& other);
		tem::Vector2& operator-=(const tem::Vector3& other);
		tem::Vector2 operator-(const float& other);
		tem::Vector2& operator-=(const float& other);
		tem::Vector2& operator*=(const float& other);
		tem::Vector2 operator*(const float& other);

		bool operator>(const float& other);
		bool operator<(const float& other);
		bool IsSet();
		static app::Vector2 ToVector2(float x = 0.0f, float y = 0.0f);
		app::Vector2 ToMoon();
		app::Vector2* ToMoonP();
		app::Color ToColor();
		app::Vector3 ToVector3Moon();
		std::string ToString();
		static float Distance(const tem::Vector2& position, const tem::Vector2& subtract);
		static bool IsPositionInsideRect(app::Rect* rect, tem::Vector2 position);
		static bool IsPositionInsideRect(app::Rect rect, tem::Vector2 position);
	};
}

#endif