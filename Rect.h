#pragma once

#include "Vector2.h"

#pragma pack(push, 1)
class UnityEngineRect
{
public:
	float X;
	float Y;
	float Width;
	float Height;

	UnityEngineRect(float x, float y, float w, float h)
	{
		this->X = x;
		this->Y = y;
		this->Width = w;
		this->Height = h;
	}

	UnityEngineRect()
	{
		this->X = 0.0f;
		this->Y = 0.0f;
		this->Width = 0.0f;
		this->Height = 0.0f;
	}

	/*inline void Set(float x, float y, float w, float h)
	{
		this->X = x;
		this->Y = y;
		this->Width = w;
		this->Height = h;
	}*/

	void Set(float x, float y, float w, float h) 
	{
		auto RectSet_address = Assembly_BaseAddr + 0x1255B0;
		using UnityEngineRect__RectSet = void(*)(UnityEngineRect*, float, float, float, float);
		auto RectSet = reinterpret_cast<UnityEngineRect__RectSet>(RectSet_address);
		RectSet(this, x, y, w, h);
		this->X = x;
		this->Y = y;
		this->Width = w;
		this->Height = h;
	}

	inline bool Contains(Vector2 position) 
	{
		return position.X > this->X && this->X + this->Width < position.X && position.Y > this->Y && this->Y + this->Height < position.Y;
	}
protected:
private:
};
#pragma pack(pop)