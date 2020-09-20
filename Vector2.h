#pragma once

#pragma pack(push, 1)
typedef struct t_Vector2
{
public:

	t_Vector2()
	{
		this->X = 0.0f;
		this->Y = 0.0f;
	}

	t_Vector2(float x, float y)
	{
		this->X = x;
		this->Y = y;
	}

	// 0x00 - 0x03
	float X;

	// 0x04 - 0x07
	float Y;
protected:
private:

} Vector2;
#pragma pack(pop)