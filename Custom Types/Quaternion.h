#pragma once

#ifndef _QUATERNION_H
#define _QUATERNION_H

#include "StringUtils.h"

namespace tem {
	class Quaternion {
	public:
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		float w = 0.0f;

		Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f)
		{
			x = x;
			y = y;
			z = z;
			w = w;
		}

		Quaternion(app::Quaternion* other)
		{
			if (other != nullptr)
			{
				x = other->x;
				y = other->y;
				z = other->z;
				w = other->w;
			}
			else
			{
				x = 0.0f;
				y = 0.0f;
				z = 0.0f;
				w = 1.0f;
			}
		}

		Quaternion(app::Vector3* other)
		{
			if (other != nullptr)
			{
				x = other->x;
				y = other->y;
				z = other->z;
				w = 1.0f;
			}
			else
			{
				x = 0.0f;
				y = 0.0f;
				z = 0.0f;
				w = 1.0f;
			}
		}

		Quaternion(app::Vector2* other)
		{
			if (other != nullptr)
			{
				x = other->x;
				y = other->y;
				z = 0.0f;
				w = 1.0f;
			}
			else
			{
				x = 0.0f;
				y = 0.0f;
				z = 0.0f;
				w = 1.0f;
			}
		}

		Quaternion(app::Vector4 other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
			w = other.w;
		}

		Quaternion(app::Vector2 other)
		{
			x = other.x;
			y = other.y;
			z = 0.0f;
			w = 1.0f;
		}

		Quaternion(std::string& other)
		{
			std::string temp = other;
			sutil::ReplaceS(temp, ",", ".");
			auto content = sutil::SplitTem(temp, ";");
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
			w = 0.0f;

			if (content.size() > 0)
				x = std::stof(content[0]);

			if (content.size() > 1)
				y = std::stof(content[1]);

			if (content.size() > 2)
				z = std::stof(content[2]);

			if (content.size() > 3)
				w = std::stof(content[3]);
		}

		Quaternion(app::Color other)
		{
			x = other.r;
			y = other.g;
			z = other.b;
			w = other.a;
		}

		Quaternion& operator+=(const Quaternion& other) {
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
			return *this;
		}

		Quaternion& operator+=(const float& other) {
			x += other;
			y += other;
			z += other;
			w += other;
			return *this;
		}

		Quaternion& operator+(const Quaternion& other) {
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
			return *this;
		}

		Quaternion& operator+(const float& other) {
			x += other;
			y += other;
			z += other;
			w += other;
			return *this;
		}

		Quaternion& operator-(const Quaternion& other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
			return *this;
		}

		Quaternion& operator-=(const Quaternion& other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
			return *this;
		}

		Quaternion& operator-(const float& other) {
			x -= other;
			y -= other;
			z -= other;
			w -= other;
			return *this;
		}

		Quaternion& operator-=(const float& other) {
			x -= other;
			y -= other;
			z -= other;
			w -= other;
			return *this;
		}

		Quaternion& operator*(const Quaternion& other) {
			x *= other.x;
			y *= other.y;
			z *= other.z;
			w *= other.w;
			return *this;
		}

		Quaternion& operator*(const float& other) {
			x *= other;
			y *= other;
			z *= other;
			w *= other;
			return *this;
		}

		Quaternion& operator*=(const float& other) {
			x *= other;
			y *= other;
			z *= other;
			w *= other;
			return *this;
		}

		bool IsEqual(const Quaternion& other)
		{
			return this->w == other.w && this->x == other.x && this->y == other.y && this->z == other.z;
		}

		bool IsSet()
		{
			return (this->x != 0.0f || this->y != 0.0f || this->z != 0.0f);
		}

		app::Quaternion ToMoon()
		{
			app::Quaternion* moon = (app::Quaternion*)il2cpp_object_new((Il2CppClass*)(*app::Quaternion__TypeInfo));
			moon->x = this->x;
			moon->y = this->y;
			moon->z = this->z;
			moon->w = this->w;

			return *moon;
		}

		app::Quaternion* ToMoonP()
		{
			app::Quaternion* moon = (app::Quaternion*)il2cpp_object_new((Il2CppClass*)(*app::Quaternion__TypeInfo));
			moon->x = this->x;
			moon->y = this->y;
			moon->z = this->z;
			moon->w = this->w;

			return moon;
		}

		std::string ToString()
		{
			return std::to_string(this->x) + ", " + std::to_string(this->y) + ", " + std::to_string(this->z) + ", " + std::to_string(this->w);
		}
	};
}

#endif