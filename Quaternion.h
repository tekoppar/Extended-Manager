#pragma once

#pragma pack(push, 1)
class Quaternion
{
	static Quaternion identityQuaternion; // 0x0
	const float kEpsilon = (float)1E-06; // 0x0

public:

	Quaternion(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Quaternion()
	{
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
		this->w = 0.0f;
	}

	float x;
	float y;
	float z;
	float w;

protected:
private:
};
#pragma pack(pop)