#pragma once

#ifndef _VECTOR3_H
#define _VECTOR3_H

#include "../StringUtils.h"

namespace tem {
	class Vector3 {
	public:
		float X = 0.0f;
		float Y = 0.0f;
		float Z = 0.0f;

		Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f)
		{
			X = x;
			Y = y;
			Z = z;
		}

		Vector3(app::Vector3* other)
		{
			if (other != nullptr)
			{
				X = other->x;
				Y = other->y;
				Z = other->z;
			}
			else
			{
				X = 0.0f;
				Y = 0.0f;
				Z = 0.0f;
			}
		}

		Vector3(app::Vector2* other)
		{
			if (other != nullptr)
			{
				X = other->x;
				Y = other->y;
				Z = 0.0f;
			}
			else
			{
				X = 0.0f;
				Y = 0.0f;
				Z = 0.0f;
			}
		}

		Vector3(app::Vector3 other)
		{
			X = other.x;
			Y = other.y;
			Z = other.z;
		}

		Vector3(app::Vector2 other)
		{
			X = other.x;
			Y = other.y;
			Z = 0.0f;
		}

		Vector3(std::string& other)
		{
			std::string temp = other;
			sutil::ReplaceS(temp, ",", ".");
			auto content = sutil::SplitTem(temp, ";");
			X = 0.0f;
			Y = 0.0f;
			Z = 0.0f;

			if (content.size() > 0)
				X = std::stof(content[0]);

			if (content.size() > 1)
				Y = std::stof(content[1]);

			if (content.size() > 2)
				Z = std::stof(content[2]);
		}

		Vector3& operator+=(const Vector3& other) {
			X += other.X;
			Y += other.Y;
			Z += other.Z;
			return *this;
		}

		Vector3& operator+=(const float& other) {
			X += other;
			Y += other;
			Z += other;
			return *this;
		}

		Vector3& operator+(const Vector3& other) {
			X += other.X;
			Y += other.Y;
			Z += other.Z;
			return *this;
		}

		Vector3& operator+(const float& other) {
			X += other;
			Y += other;
			Z += other;
			return *this;
		}

		Vector3& operator-(const Vector3& other) {
			X -= other.X;
			Y -= other.Y;
			Z -= other.Z;
			return *this;
		}

		Vector3& operator-=(const Vector3& other) {
			X -= other.X;
			Y -= other.Y;
			Z -= other.Z;
			return *this;
		}

		Vector3& operator-(const float& other) {
			X -= other;
			Y -= other;
			Z -= other;
			return *this;
		}

		Vector3& operator-=(const float& other) {
			X -= other;
			Y -= other;
			Z -= other;
			return *this;
		}

		Vector3& operator*(const float& other) {
			X *= other;
			Y *= other;
			Z *= other;
			return *this;
		}

		bool IsSet()
		{
			return (this->X != 0.0f || this->Y != 0.0f || this->Z != 0.0f);
		}

		static app::Vector2 ToVector2(float x = 0.0f, float y = 0.0f)
		{
			app::Vector2* moon = (app::Vector2*)il2cpp_object_new((Il2CppClass*)app::Vector2__TypeInfo);
			moon->x = x;
			moon->y = x;
			return *moon;
		}

		app::Vector3 ToMoon()
		{
			app::Vector3* moon = (app::Vector3*)il2cpp_object_new((Il2CppClass*)app::Vector3__TypeInfo);
			moon->x = this->X;
			moon->y = this->Y;
			moon->z = this->Z;

			return *moon;
		}

		std::string ToString()
		{
			return std::to_string(this->X) + ", " + std::to_string(this->Y) + ", " + std::to_string(this->Z);
		}

		static float Distance(const Vector3& position, const Vector3& subtract) {
			return std::sqrt(((position.Y - subtract.Y) * (position.Y - subtract.Y)) + ((position.X - subtract.X) * (position.X - subtract.X)));
		}

		static bool IsPositionInsideRect(app::Rect* rect, tem::Vector3 position)
		{
			return rect->m_YMin < position.Y&& rect->m_YMin + rect->m_Height > position.Y && rect->m_XMin - (rect->m_Width / 2) < position.X && position.X < rect->m_XMin + (rect->m_Width / 2);
		}

		static bool IsPositionInsideRect(app::Rect rect, tem::Vector3 position)
		{
			return rect.m_YMin < position.Y&& rect.m_YMin + rect.m_Height > position.Y && rect.m_XMin - (rect.m_Width / 2) < position.X && position.X < rect.m_XMin + (rect.m_Width / 2);
		}
	};
}

#endif