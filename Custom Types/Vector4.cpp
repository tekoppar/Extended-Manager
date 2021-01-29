#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include "StringUtils.h"
#include "Vector3.h"
#include "Vector2.h"

#include "Vector4.h"

namespace tem
{
	tem::Vector4::Vector4()
	{
		X = 0.0f;
		Y = 0.0f;
		Z = 0.0f;
		A = 0.0f;
	}

	tem::Vector4::Vector4(float x, float y, float z, float a)
	{
		X = x;
		Y = y;
		Z = z;
		A = a;
	}

	tem::Vector4::Vector4(float all)
	{
		X = all;
		Y = all;
		Z = all;
		A = all;
	}

	tem::Vector4::Vector4(tem::Vector3& vec)
	{
		X = vec.X;
		Y = vec.Y;
		Z = vec.Z;
		A = 0.0f;
	}

	tem::Vector4::Vector4(tem::Vector2& vec)
	{
		X = vec.x;
		Y = vec.y;
		Z = 0.0f;
		A = 0.0f;
	}

	tem::Vector4::Vector4(app::Vector4* other)
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

	tem::Vector4::Vector4(app::Vector3* other)
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

	tem::Vector4::Vector4(app::Vector2* other)
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

	tem::Vector4::Vector4(app::Vector4 other)
	{
		X = other.x;
		Y = other.y;
		Z = other.z;
		A = other.w;
	}

	tem::Vector4::Vector4(app::Vector2 other)
	{
		X = other.x;
		Y = other.y;
		Z = 0.0f;
		A = 1.0f;
	}

	tem::Vector4::Vector4(const char*& other)
	{
		std::string temp = std::string(other);
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

	tem::Vector4::Vector4(std::string& other)
	{
		std::string temp = other;
		auto content = sutil::SplitTem(temp, ",");
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

	tem::Vector4::Vector4(app::Color other)
	{
		X = other.r;
		Y = other.g;
		Z = other.b;
		A = other.a;
	}

	tem::Vector4::Vector4(app::Color* other)
	{
		X = other->r;
		Y = other->g;
		Z = other->b;
		A = other->a;
	}

	tem::Vector4& tem::Vector4::operator+=(const tem::Vector4& other)
	{
		X += other.X;
		Y += other.Y;
		Z += other.Z;
		A += other.A;
		return *this;
	}

	tem::Vector4& tem::Vector4::operator+=(const float& other)
	{
		X += other;
		Y += other;
		Z += other;
		A += other;
		return *this;
	}

	tem::Vector4 tem::Vector4::operator+(const tem::Vector4& other)
	{
		return tem::Vector4(X + other.X, Y + other.Y, Z + other.Z, A + other.A);
	}

	tem::Vector4 tem::Vector4::operator+(const float& other)
	{
		return tem::Vector4(X + other, Y + other, Z + other, A + other);
	}

	tem::Vector4 tem::Vector4::operator-(const tem::Vector4& other)
	{
		return tem::Vector4(X - other.X, Y - other.Y, Z - other.Z, A - other.A);
	}

	tem::Vector4& tem::Vector4::operator-=(const tem::Vector4& other)
	{
		X -= other.X;
		Y -= other.Y;
		Z -= other.Z;
		A -= other.A;
		return *this;
	}

	tem::Vector4 tem::Vector4::operator-(const float& other)
	{
		return tem::Vector4(X - other, Y - other, Z - other, A - other);
	}

	tem::Vector4& tem::Vector4::operator-=(const float& other)
	{
		X -= other;
		Y -= other;
		Z -= other;
		A -= other;
		return *this;
	}

	tem::Vector4 tem::Vector4::operator*(const tem::Vector4& other)
	{
		return tem::Vector4(X * other.X, Y * other.Y, Z * other.Z, A * other.A);
	}

	tem::Vector4 tem::Vector4::operator*(const float& other)
	{
		return tem::Vector4(X * other, Y * other, Z * other, A * other);
	}

	tem::Vector4& tem::Vector4::operator*=(const float& other)
	{
		X *= other;
		Y *= other;
		Z *= other;
		A *= other;
		return *this;
	}

	bool tem::Vector4::IsEqual(const tem::Vector4& other)
	{
		return this->A == other.A && this->X == other.X && this->Y == other.Y && this->Z == other.Z;
	}

	bool tem::Vector4::IsSet()
	{
		return (this->X != 0.0f || this->Y != 0.0f || this->Z != 0.0f);
	}

	app::Vector2 tem::Vector4::ToVector2(float x, float y)
	{
		app::Vector2* moon = (app::Vector2*)il2cpp_object_new((Il2CppClass*)(*app::Vector2__TypeInfo));
		moon->x = x;
		moon->y = x;
		return *moon;
	}

	app::Vector4 tem::Vector4::ToMoon()
	{
		app::Vector4* moon = (app::Vector4*)il2cpp_object_new((Il2CppClass*)(*app::Vector4__TypeInfo));
		moon->x = this->X;
		moon->y = this->Y;
		moon->z = this->Z;
		moon->w = this->A;

		return *moon;
	}

	app::Vector4* tem::Vector4::ToMoonP()
	{
		app::Vector4* moon = (app::Vector4*)il2cpp_object_new((Il2CppClass*)(*app::Vector4__TypeInfo));
		moon->x = this->X;
		moon->y = this->Y;
		moon->z = this->Z;
		moon->w = this->A;

		return moon;
	}

	app::Color tem::Vector4::ToColor()
	{
		app::Color moon = app::Color();
		moon.r = this->X;
		moon.g = this->Y;
		moon.b = this->Z;
		moon.a = this->A;

		return moon;
	}

	std::string tem::Vector4::ToString()
	{
		return std::to_string(this->X) + ", " + std::to_string(this->Y) + ", " + std::to_string(this->Z) + ", " + std::to_string(this->A);
	}
}