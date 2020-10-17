#pragma once

#ifndef _HELPERCLASSES_H
#define _HELPERCLASSES_H

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

		Vector3(app::Vector3 other)
		{
			X = other.x;
			Y = other.y;
			Z = other.z;
		}

		Vector3(std::string other)
		{
			auto content = sutil::SplitTem(other, ";");
			X = std::stof(content[0]);
			Y = std::stof(content[1]);
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
	};
}

#endif