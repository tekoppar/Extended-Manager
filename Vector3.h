#pragma once

#pragma pack(push, 1)
typedef struct t_Vector3
{
public:

	t_Vector3(float argx, float argy)
	{
		this->x = argx;
		this->y = argy;
		this->z = 0.0f;
	}
	t_Vector3()
	{
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
	}

	inline void Set(float ax, float ay, float az)
	{
		this->x = ax;
		this->y = ay;
		this->z = az;
	}

	// 0x00 - 0x03
	float x;

	// 0x04 - 0x07
	float y;

	// 0x08 - 0x0B
	float z;
protected:
private:
} Vector3;
#pragma pack(pop)