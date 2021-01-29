#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include "StringUtils.h"
#include "Vector4.h"
#include "Vector2.h"

#include "Vector3.h"

namespace tem
{
	tem::Vector3 tem::Vector3::Forward = tem::Vector3(0.0f, 0.0f, 1.0f);
	tem::Vector3 tem::Vector3::Back = tem::Vector3(0.0f, 0.0f, -1.0f);
	tem::Vector3 tem::Vector3::Down = tem::Vector3(0.0f, -1.0f, 0.0f);
	tem::Vector3 tem::Vector3::Left = tem::Vector3(-1.0f, 0.0f, 0.0f);
	tem::Vector3 tem::Vector3::Right = tem::Vector3(1.0f, 0.0f, 0.0f);
	tem::Vector3 tem::Vector3::Up = tem::Vector3(0.0f, 1.0f, 0.0f);

	tem::Vector3::Vector3()
	{
		X = 0.0f;
		Y = 0.0f;
		Z = 0.0f;
	}

	tem::Vector3::Vector3(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;
	}

	tem::Vector3::Vector3(float x, float y)
	{
		X = x;
		Y = y;
		Z = 0.0f;
	}

	tem::Vector3::Vector3(float all)
	{
		X = all;
		Y = all;
		Z = all;
	}

	tem::Vector3::Vector3(tem::Vector4& vec)
	{
		X = vec.X;
		Y = vec.Y;
		Z = vec.Z;
	}

	tem::Vector3::Vector3(tem::Vector2& vec)
	{
		X = vec.x;
		Y = vec.y;
		Z = 0.0f;
	}

	tem::Vector3::Vector3(int x, int y, int z)
	{
		X = static_cast<float>(x);
		Y = static_cast<float>(y);
		Z = static_cast<float>(z);
	}

	tem::Vector3::Vector3(app::Vector3* other)
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

	tem::Vector3::Vector3(app::Vector2* other)
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

	tem::Vector3::Vector3(app::Vector3 other)
	{
		X = other.x;
		Y = other.y;
		Z = other.z;
	}

	tem::Vector3::Vector3(app::Vector2 other)
	{
		X = other.x;
		Y = other.y;
		Z = 0.0f;
	}

	tem::Vector3::Vector3(std::string& other)
	{
		std::string temp = other;
		auto content = sutil::SplitTem(temp, ",");
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

	tem::Vector3::Vector3(app::Color other)
	{
		X = other.r;
		Y = other.g;
		Z = other.b;
	}

	tem::Vector3& tem::Vector3::operator+=(const tem::Vector3& other) {
		X += other.X;
		Y += other.Y;
		Z += other.Z;
		return *this;
	}

	tem::Vector3& tem::Vector3::operator+=(const float& other) {
		X += other;
		Y += other;
		Z += other;
		return *this;
	}

	tem::Vector3 tem::Vector3::operator+(const tem::Vector3& other) {
		return tem::Vector3(X + other.X, Y + other.Y, Z + other.Z);
	}

	tem::Vector3 tem::Vector3::operator+(const float& other) {
		return tem::Vector3(X + other, Y + other, Z + other);
	}

	tem::Vector3 tem::Vector3::operator-(const tem::Vector3& other) {
		return tem::Vector3(X - other.X, Y - other.Y, Z - other.Z);
	}

	tem::Vector3& tem::Vector3::operator-=(const tem::Vector3& other) {
		X -= other.X;
		Y -= other.Y;
		Z -= other.Z;
		return *this;
	}

	tem::Vector3 tem::Vector3::operator-(const float& other) {
		return tem::Vector3(X - other, Y - other, Z - other);
	}

	tem::Vector3& tem::Vector3::operator-=(const float& other) {
		X -= other;
		Y -= other;
		Z -= other;
		return *this;
	}

	tem::Vector3& tem::Vector3::operator*=(const float& other) {
		X *= other;
		Y *= other;
		Z *= other;
		return *this;
	}

	tem::Vector3 tem::Vector3::operator*(const float& other) {
		return tem::Vector3(X * other, Y * other, Z * other);
	}

	bool tem::Vector3::operator==(tem::Vector3& other) {
		return (this->X == other.X && this->Y == other.Y && this->Z == other.Z);
	}

	bool tem::Vector3::IsSet()
	{
		return (this->X != 0.0f || this->Y != 0.0f || this->Z != 0.0f);
	}

	bool tem::Vector3::Equals(tem::Vector3& vec)
	{
		return (this->X == vec.X && this->Y == vec.Y && this->Z == vec.Z);
	}

	bool tem::Vector3::Equals(tem::Vector3 vec)
	{
		return (this->X == vec.X && this->Y == vec.Y && this->Z == vec.Z);
	}

	bool tem::Vector3::NearlyEqual(tem::Vector3 vec)
	{
		return this->X - 0.1f < vec.X && this->X + 0.1f > vec.X && this->Y - 0.1f < vec.Y && this->Y + 0.1f > vec.Y;
	}

	app::Vector2 tem::Vector3::ToVector2(float x, float y)
	{
		app::Vector2* moon = (app::Vector2*)il2cpp_object_new((Il2CppClass*)(*app::Vector2__TypeInfo));
		moon->x = x;
		moon->y = x;
		return *moon;
	}

	app::Vector3 tem::Vector3::ToMoon()
	{
		app::Vector3* moon = (app::Vector3*)il2cpp_object_new((Il2CppClass*)(*app::Vector3__TypeInfo));
		moon->x = this->X;
		moon->y = this->Y;
		moon->z = this->Z;

		return *moon;
	}

	app::Vector3* tem::Vector3::ToMoonP()
	{
		app::Vector3* moon = (app::Vector3*)il2cpp_object_new((Il2CppClass*)(*app::Vector3__TypeInfo));
		moon->x = this->X;
		moon->y = this->Y;
		moon->z = this->Z;

		return moon;
	}

	app::Color tem::Vector3::ToColor()
	{
		app::Color moon = app::Color();
		moon.r = this->X;
		moon.g = this->Y;
		moon.b = this->Z;
		moon.a = 1.0f;

		return moon;
	}

	std::string tem::Vector3::ToString()
	{
		return std::to_string(this->X) + ", " + std::to_string(this->Y) + ", " + std::to_string(this->Z);
	}

	float tem::Vector3::Distance(const tem::Vector3& position, const tem::Vector3& subtract) {
		return std::sqrt(((position.Y - subtract.Y) * (position.Y - subtract.Y)) + ((position.X - subtract.X) * (position.X - subtract.X)));
	}

	bool tem::Vector3::IsPositionInsideRect(app::Rect* rect, tem::Vector3 position)
	{
		return rect->m_YMin < position.Y&& rect->m_YMin + rect->m_Height > position.Y && rect->m_XMin - (rect->m_Width / 2) < position.X && position.X < rect->m_XMin + (rect->m_Width / 2);
	}

	bool tem::Vector3::IsPositionInsideRect(app::Rect rect, tem::Vector3 position)
	{
		return rect.m_YMin < position.Y&& rect.m_YMin + rect.m_Height > position.Y && rect.m_XMin - (rect.m_Width / 2) < position.X && position.X < rect.m_XMin + (rect.m_Width / 2);
	}
}