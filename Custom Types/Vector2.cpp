#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include "StringUtils.h"
#include "Vector4.h"
#include "Vector3.h"

#include "Vector2.h"

namespace tem
{
	tem::Vector2::Vector2(float x1, float y1)
	{
		x = x1;
		y = y1;
	}

	tem::Vector2::Vector2(int x1, int y1)
	{
		x = static_cast<float>(x1);
		y = static_cast<float>(y1);
	}

	tem::Vector2::Vector2(app::Vector2* other)
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

	tem::Vector2::Vector2(app::Vector2 other)
	{
		x = other.x;
		y = other.y;
	}

	tem::Vector2::Vector2(std::string& other)
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

	tem::Vector2::Vector2(app::Color other)
	{
		x = other.r;
		y = other.g;
	}

	tem::Vector2& tem::Vector2::operator+=(const tem::Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	tem::Vector2& tem::Vector2::operator+=(const tem::Vector3& other)
	{
		x += other.X;
		y += other.Y;
		return *this;
	}

	tem::Vector2& tem::Vector2::operator+=(const float& other)
	{
		x += other;
		y += other;
		return *this;
	}

	tem::Vector2 tem::Vector2::operator+(const tem::Vector2& other)
	{
		return tem::Vector2(x + other.x, y + other.y);
	}

	tem::Vector2 tem::Vector2::operator+(const tem::Vector3& other)
	{
		return tem::Vector2(x + other.X, y + other.Y);
	}

	tem::Vector2 tem::Vector2::operator+(const float& other)
	{
		return tem::Vector2(x + other, y + other);
	}

	tem::Vector2 tem::Vector2::operator-(const tem::Vector2& other)
	{
		return tem::Vector2(x - other.x, y - other.y);
	}

	tem::Vector2 tem::Vector2::operator-(const tem::Vector3& other)
	{
		return tem::Vector2(x - other.X, y - other.Y);
	}

	tem::Vector2& tem::Vector2::operator-=(const tem::Vector2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	tem::Vector2& tem::Vector2::operator-=(const tem::Vector3& other)
	{
		x -= other.X;
		y -= other.Y;
		return *this;
	}

	tem::Vector2 tem::Vector2::operator-(const float& other)
	{
		return tem::Vector2(x - other, y - other);
	}

	tem::Vector2& tem::Vector2::operator-=(const float& other)
	{
		x -= other;
		y -= other;
		return *this;
	}

	tem::Vector2& tem::Vector2::operator*=(const float& other)
	{
		x *= other;
		y *= other;
		return *this;
	}

	tem::Vector2 tem::Vector2::operator*(const float& other)
	{
		return tem::Vector2(x * other, y * other);
	}

	bool tem::Vector2::operator>(const float& other) {
		return this->x > other && this->y > other;
	}

	bool tem::Vector2::operator<(const float& other) {
		return this->x < other&& this->y < other;
	}

	bool tem::Vector2::IsSet()
	{
		return (this->x != 0.0f || this->y != 0.0f);
	}

	app::Vector2 tem::Vector2::ToVector2(float x, float y)
	{
		app::Vector2* moon = (app::Vector2*)il2cpp_object_new((Il2CppClass*)(*app::Vector2__TypeInfo));
		moon->x = x;
		moon->y = x;
		return *moon;
	}

	app::Vector2 tem::Vector2::ToMoon()
	{
		app::Vector2* moon = (app::Vector2*)il2cpp_object_new((Il2CppClass*)(*app::Vector2__TypeInfo));
		moon->x = this->x;
		moon->y = this->y;

		return *moon;
	}

	app::Vector2* tem::Vector2::ToMoonP()
	{
		app::Vector2* moon = (app::Vector2*)il2cpp_object_new((Il2CppClass*)(*app::Vector2__TypeInfo));
		moon->x = this->x;
		moon->y = this->y;

		return moon;
	}

	app::Color tem::Vector2::ToColor()
	{
		app::Color moon = app::Color();
		moon.r = this->x;
		moon.g = this->y;
		moon.b = 1.0f;
		moon.a = 1.0f;

		return moon;
	}

	app::Vector3 tem::Vector2::ToVector3Moon()
	{
		app::Vector3* moon = (app::Vector3*)il2cpp_object_new((Il2CppClass*)(*app::Vector3__TypeInfo));
		moon->x = this->x;
		moon->y = this->y;
		moon->z = 0.0f;

		return *moon;
	}

	std::string tem::Vector2::ToString()
	{
		return std::to_string(this->x) + ", " + std::to_string(this->y);
	}

	float tem::Vector2::Distance(const tem::Vector2& position, const tem::Vector2& subtract) {
		return std::sqrt(((position.y - subtract.y) * (position.y - subtract.y)) + ((position.x - subtract.x) * (position.x - subtract.x)));
	}

	bool tem::Vector2::IsPositionInsideRect(app::Rect* rect, tem::Vector2 position)
	{
		return rect->m_YMin < position.y&& rect->m_YMin + rect->m_Height > position.y && rect->m_XMin - (rect->m_Width / 2) < position.x && position.x < rect->m_XMin + (rect->m_Width / 2);
	}

	bool tem::Vector2::IsPositionInsideRect(app::Rect rect, tem::Vector2 position)
	{
		return rect.m_YMin < position.y&& rect.m_YMin + rect.m_Height > position.y && rect.m_XMin - (rect.m_Width / 2) < position.x && position.x < rect.m_XMin + (rect.m_Width / 2);
	}
}