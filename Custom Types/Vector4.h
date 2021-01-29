#pragma once

#ifndef _VECTOR4_H
#define _VECTOR4_H

#include "StringUtils.h"

namespace tem 
{
	class Vector2;
	class Vector3;

	class Vector4 
	{
	public:
		float X = 0.0f;
		float Y = 0.0f;
		float Z = 0.0f;
		float A = 0.0f;

		Vector4();
		Vector4(float x, float y, float z, float a);
		Vector4(float all);
		Vector4(tem::Vector2& vec);
		Vector4(tem::Vector3& vec);
		Vector4(app::Vector4* other);
		Vector4(app::Vector3* other);
		Vector4(app::Vector2* other);
		Vector4(app::Vector4 other);
		Vector4(app::Vector2 other);
		Vector4(const char*& other);
		Vector4(std::string& other);
		Vector4(app::Color other);
		Vector4(app::Color* other);

		tem::Vector4& operator+=(const tem::Vector4& other);
		tem::Vector4& operator+=(const float& other);
		tem::Vector4 operator+(const tem::Vector4& other);
		tem::Vector4 operator+(const float& other);
		tem::Vector4 operator-(const tem::Vector4& other);
		tem::Vector4& operator-=(const tem::Vector4& other);
		tem::Vector4 operator-(const float& other);
		tem::Vector4& operator-=(const float& other);
		tem::Vector4 operator*(const tem::Vector4& other);
		tem::Vector4 operator*(const float& other);
		tem::Vector4& operator*=(const float& other);

		bool IsEqual(const tem::Vector4& other);
		bool IsSet();
		static app::Vector2 ToVector2(float x = 0.0f, float y = 0.0f);
		app::Vector4 ToMoon();
		app::Vector4* ToMoonP();
		app::Color ToColor();
		std::string ToString();
	};
}

#endif