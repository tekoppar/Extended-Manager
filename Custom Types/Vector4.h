#pragma once

#ifndef _VECTOR4_H
#define _VECTOR4_H

#include "../StringUtils.h"

namespace tem {
	class Vector4 {
	public:
		float X = 0.0f;
		float Y = 0.0f;
		float Z = 0.0f;
		float A = 0.0f;

		Vector4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float a = 0.0f)
		{
			X = x;
			Y = y;
			Z = z;
			A = a;
		}

		Vector4(app::Vector4* other)
		{
			if (other != nullptr)
			{
				X = other->x;
				Y = other->y;
				Z = other->z;
				A = other->w;
			}
			else
			{
				X = 0.0f;
				Y = 0.0f;
				Z = 0.0f;
				A = 1.0f;
			}
		}

		Vector4(app::Vector3* other)
		{
			if (other != nullptr)
			{
				X = other->x;
				Y = other->y;
				Z = other->z;
				A = 1.0f;
			}
			else
			{
				X = 0.0f;
				Y = 0.0f;
				Z = 0.0f;
				A = 1.0f;
			}
		}

		Vector4(app::Vector2* other)
		{
			if (other != nullptr)
			{
				X = other->x;
				Y = other->y;
				Z = 0.0f;
				A = 1.0f;
			}
			else
			{
				X = 0.0f;
				Y = 0.0f;
				Z = 0.0f;
				A = 1.0f;
			}
		}

		Vector4(app::Vector4 other)
		{
			X = other.x;
			Y = other.y;
			Z = other.z;
			A = other.w;
		}

		Vector4(app::Vector2 other)
		{
			X = other.x;
			Y = other.y;
			Z = 0.0f;
			A = 1.0f;
		}

		Vector4(std::string& other)
		{
			std::string temp = other;
			sutil::ReplaceS(temp, ",", ".");
			auto content = sutil::SplitTem(temp, ";");
			X = 0.0f;
			Y = 0.0f;
			Z = 0.0f;
			A = 0.0f;

			if (content.size() > 0)
				X = std::stof(content[0]);

			if (content.size() > 1)
				Y = std::stof(content[1]);

			if (content.size() > 2)
				Z = std::stof(content[2]);

			if (content.size() > 3)
				A = std::stof(content[3]);
		}

		Vector4(app::Color other)
		{
			X = other.r;
			Y = other.g;
			Z = other.b;
			A = other.a;
		}

		Vector4& operator+=(const Vector4& other) {
			X += other.X;
			Y += other.Y;
			Z += other.Z;
			A += other.A;
			return *this;
		}

		Vector4& operator+=(const float& other) {
			X += other;
			Y += other;
			Z += other;
			A += other;
			return *this;
		}

		Vector4& operator+(const Vector4& other) {
			X += other.X;
			Y += other.Y;
			Z += other.Z;
			A += other.A;
			return *this;
		}

		Vector4& operator+(const float& other) {
			X += other;
			Y += other;
			Z += other;
			A += other;
			return *this;
		}

		Vector4& operator-(const Vector4& other) {
			X -= other.X;
			Y -= other.Y;
			Z -= other.Z;
			A -= other.A;
			return *this;
		}

		Vector4& operator-=(const Vector4& other) {
			X -= other.X;
			Y -= other.Y;
			Z -= other.Z;
			A -= other.A;
			return *this;
		}

		Vector4& operator-(const float& other) {
			X -= other;
			Y -= other;
			Z -= other;
			A -= other;
			return *this;
		}

		Vector4& operator-=(const float& other) {
			X -= other;
			Y -= other;
			Z -= other;
			A -= other;
			return *this;
		}

		Vector4& operator*(const float& other) {
			X *= other;
			Y *= other;
			Z *= other;
			A *= other;
			return *this;
		}

		Vector4& operator*=(const float& other) {
			X *= other;
			Y *= other;
			Z *= other;
			A *= other;
			return *this;
		}

		bool IsEqual(const Vector4& other)
		{
			return this->A == other.A && this->X == other.X && this->Y == other.Y && this->Z == other.Z;
		}

		bool IsSet()
		{
			return (this->X != 0.0f || this->Y != 0.0f || this->Z != 0.0f);
		}

		static app::Vector2 ToVector2(float x = 0.0f, float y = 0.0f)
		{
			app::Vector2* moon = (app::Vector2*)il2cpp_object_new((Il2CppClass*)(*app::Vector2__TypeInfo));
			moon->x = x;
			moon->y = x;
			return *moon;
		}

		app::Vector4 ToMoon()
		{
			app::Vector4* moon = (app::Vector4*)il2cpp_object_new((Il2CppClass*)(*app::Vector4__TypeInfo));
			moon->x = this->X;
			moon->y = this->Y;
			moon->z = this->Z;
			moon->w = this->A;

			return *moon;
		}

		app::Color ToColor()
		{
			app::Color moon;
			moon.r = this->X;
			moon.g = this->Y;
			moon.b = this->Z;
			moon.a = this->A;

			return moon;
		}

		std::string ToString()
		{
			return std::to_string(this->X) + ", " + std::to_string(this->Y) + ", " + std::to_string(this->Z) + ", " + std::to_string(this->A);
		}
	};
}

#endif