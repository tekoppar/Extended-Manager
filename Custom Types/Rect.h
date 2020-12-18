#pragma once

#ifndef _RECT_H
#define _RECT_H

#include "../StringUtils.h"

namespace tem {
	class Rect
	{
	public:
		float X = 0.0f;
		float Y = 0.0f;
		float Width = 0.0f;
		float Height = 0.0f;

		Rect(float x = 0.0f, float y = 0.0f, float width = 0.0f, float height = 0.0f)
		{
			X = x;
			Y = y;
			Width = width;
			Height = height;
		}

		Rect(app::Rect* other)
		{
			if (other != nullptr)
			{
				X = other->m_XMin;
				Y = other->m_YMin;
				Width = other->m_Width;
				Height = other->m_Height;
			}
			else
			{
				X = 0.0f;
				Y = 0.0f;
				Width = 0.0f;
				Height = 0.0f;
			}
		}

		Rect(app::Rect other)
		{
			X = other.m_XMin;
			Y = other.m_YMin;
			Width = other.m_Width;
			Height = other.m_Height;
		}

		app::Rect ToMoon()
		{
			app::Rect* moon = (app::Rect*)il2cpp_object_new((Il2CppClass*)(*app::Rect__TypeInfo));
			moon->m_XMin = this->X;
			moon->m_YMin = this->Y;
			moon->m_Width = this->Width;
			moon->m_Height = this->Height;

			return *moon;
		}

		bool IsPositionInsideRect(tem::Vector3 position)
		{
			return this->Y < position.Y&& this->Y + this->Height > position.Y && this->X - (this->Width / 2) < position.X && position.X < this->X + (this->Width / 2);
		}

		static bool IsPositionInsideRect(tem::Rect rect, tem::Vector3 position)
		{
			return rect.Y < position.Y&& rect.Y + rect.Height > position.Y && rect.X - (rect.Width / 2) < position.X && position.X < rect.X + (rect.Width / 2);
		}

		static bool IsPositionInsideRect(app::Rect* rect, tem::Vector3 position)
		{
			return rect->m_YMin < position.Y&& rect->m_YMin + rect->m_Height > position.Y && rect->m_XMin - (rect->m_Width / 2) < position.X && position.X < rect->m_XMin + (rect->m_Width / 2);
		}

		bool IsRectBetweenPositions(tem::Vector3 start, tem::Vector3 end)
		{
			return (start.X < this->X&& this->X < end.X || start.X > this->X&& this->X > end.X) && (start.Y < this->Y&& this->Y < end.Y || start.Y > this->Y&& this->Y > end.Y);
		}

		bool IsRectBetweenPositions(app::Rect* rect, tem::Vector3 start, tem::Vector3 end)
		{
			return (start.X < rect->m_XMin&& rect->m_XMin < end.X || start.X > rect->m_XMin&& rect->m_XMin > end.X) && (start.Y < rect->m_YMin&& rect->m_YMin < end.Y || start.Y > rect->m_YMin&& rect->m_YMin > end.Y);
		}

		static bool IsRectBetweenPositions(tem::Rect rect, tem::Vector3 start, tem::Vector3 end)
		{
			return (start.X < rect.X&& rect.X < end.X || start.X > rect.X&& rect.X > end.X) && (start.Y < rect.Y&& rect.Y < end.Y || start.Y > rect.Y&& rect.Y > end.Y);
		}

		static bool IsRectInsideRect(app::Rect rect, app::Rect rectToCheck)
		{
			bool isInside = false;
			isInside = tem::Vector3::IsPositionInsideRect(rect, tem::Vector3(rectToCheck.m_XMin, rectToCheck.m_YMin));

			if (isInside)
				return isInside;

			isInside = tem::Vector3::IsPositionInsideRect(rect, tem::Vector3(rectToCheck.m_XMin + rectToCheck.m_Width, rectToCheck.m_YMin));

			if (isInside)
				return isInside;

			isInside = tem::Vector3::IsPositionInsideRect(rect, tem::Vector3(rectToCheck.m_XMin, rectToCheck.m_YMin + rectToCheck.m_Height));

			if (isInside)
				return isInside;

			isInside = tem::Vector3::IsPositionInsideRect(rect, tem::Vector3(rectToCheck.m_XMin + rectToCheck.m_Width, rectToCheck.m_YMin + rectToCheck.m_Height));

			if (isInside)
				return isInside;

			return false;
		}
	};
}

#endif