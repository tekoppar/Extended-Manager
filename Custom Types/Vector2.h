#pragma once

#ifndef _VECTOR2_H
#define _VECTOR2_H

#include "StringUtils.h"
#include "Vector3.h"

namespace tem {
	class Vector2 {
	public:
		float x = 0.0f;
		float y = 0.0f;

		Vector2(float x1 = 0.0f, float y1 = 0.0f)
		{
			x = x1;
			y = y1;
		}

		Vector2(int x1, int y1)
		{
			x = static_cast<float>(x1);
			y = static_cast<float>(y1);
		}

		Vector2(app::Vector2* other)
		{
			if (other != nullptr)
			{
				x = other->x;
				y = other->y;
			}
			else
			{
				x = 0.0f;
				y = 0.0f;
			}
		}

		Vector2(app::Vector2 other)
		{
			x = other.x;
			y = other.y;
		}

		/*Vector3(std::string& other)
		{
			std::string temp = other;
			sutil::ReplaceS(temp, ",", ".");
			auto content = sutil::SplitTem(temp, ";");
			x = 0.0f;
			y = 0.0f;
			Z = 0.0f;

			if (content.size() > 0)
				x = std::stof(content[0]);

			if (content.size() > 1)
				y = std::stof(content[1]);

			if (content.size() > 2)
				Z = std::stof(content[2]);
		}*/

		Vector2(std::string& other)
		{
			std::string temp = other;
			auto content = sutil::SplitTem(temp, ",");
			x = 0.0f;
			y = 0.0f;

			if (content.size() > 0)
				x = std::stof(content[0]);

			if (content.size() > 1)
				y = std::stof(content[1]);
		}

		Vector2(app::Color other)
		{
			x = other.r;
			y = other.g;
		}

		Vector2& operator+=(const Vector2& other) {
			x += other.x;
			y += other.y;
			return *this;
		}

		Vector2& operator+=(const tem::Vector3& other) {
			x += other.X;
			y += other.Y;
			return *this;
		}

		Vector2& operator+=(const float& other) {
			x += other;
			y += other;
			return *this;
		}

		Vector2 operator+(const Vector2& other) {
			return tem::Vector2(x + other.x, y + other.y);
		}

		Vector2 operator+(const tem::Vector3& other) {
			return tem::Vector2(x + other.X, y + other.Y);
		}

		Vector2 operator+(const float& other) {
			return tem::Vector2(x + other, y + other);
		}

		Vector2 operator-(const Vector2& other) {
			return tem::Vector2(x - other.x, y - other.y);
		}

		Vector2 operator-(const tem::Vector3& other) {
			return tem::Vector2(x - other.X, y - other.Y);
		}

		Vector2& operator-=(const Vector2& other) {
			x -= other.x;
			y -= other.y;
			return *this;
		}

		Vector2& operator-=(const tem::Vector3& other) {
			x -= other.X;
			y -= other.Y;
			return *this;
		}

		Vector2 operator-(const float& other) {
			return tem::Vector2(x - other, y - other);
		}

		Vector2& operator-=(const float& other) {
			x -= other;
			y -= other;
			return *this;
		}

		Vector2& operator*=(const float& other) {
			x *= other;
			y *= other;
			return *this;
		}

		Vector2 operator*(const float& other) {
			return tem::Vector2(x * other, y * other);
		}

		bool operator>(const float& other) {
			return this->x > other && this->y > other;
		}

		bool operator<(const float& other) {
			return this->x < other && this->y < other;
		}

		bool IsSet()
		{
			return (this->x != 0.0f || this->y != 0.0f);
		}

		static app::Vector2 ToVector2(float x = 0.0f, float y = 0.0f)
		{
			app::Vector2* moon = (app::Vector2*)il2cpp_object_new((Il2CppClass*)(*app::Vector2__TypeInfo));
			moon->x = x;
			moon->y = x;
			return *moon;
		}

		app::Vector2 ToMoon()
		{
			app::Vector2* moon = (app::Vector2*)il2cpp_object_new((Il2CppClass*)(*app::Vector2__TypeInfo));
			moon->x = this->x;
			moon->y = this->y;

			return *moon;
		}

		app::Vector2* ToMoonP()
		{
			app::Vector2* moon = (app::Vector2*)il2cpp_object_new((Il2CppClass*)(*app::Vector2__TypeInfo));
			moon->x = this->x;
			moon->y = this->y;

			return moon;
		}

		app::Color ToColor()
		{
			app::Color moon = app::Color();
			moon.r = this->x;
			moon.g = this->y;
			moon.b = 1.0f;
			moon.a = 1.0f;

			return moon;
		}

		app::Vector3 ToVector3Moon()
		{
			app::Vector3* moon = (app::Vector3*)il2cpp_object_new((Il2CppClass*)(*app::Vector3__TypeInfo));
			moon->x = this->x;
			moon->y = this->y;
			moon->z = 0.0f;

			return *moon;
		}

		std::string ToString()
		{
			return std::to_string(this->x) + ", " + std::to_string(this->y);
		}

		static float Distance(const Vector2& position, const Vector2& subtract) {
			return std::sqrt(((position.y - subtract.y) * (position.y - subtract.y)) + ((position.x - subtract.x) * (position.x - subtract.x)));
		}

		static bool IsPositionInsideRect(app::Rect* rect, tem::Vector2 position)
		{
			return rect->m_YMin < position.y&& rect->m_YMin + rect->m_Height > position.y && rect->m_XMin - (rect->m_Width / 2) < position.x && position.x < rect->m_XMin + (rect->m_Width / 2);
		}

		static bool IsPositionInsideRect(app::Rect rect, tem::Vector2 position)
		{
			return rect.m_YMin < position.y&& rect.m_YMin + rect.m_Height > position.y && rect.m_XMin - (rect.m_Width / 2) < position.x && position.x < rect.m_XMin + (rect.m_Width / 2);
		}
	};
}

#endif