#pragma once

#include "Vector2.h"
#include "Vector3.h"

#pragma pack(push, 1)
class Transform
{
	Vector3 position;

public:

	Vector3* get_position()
	{
		auto get_position_address = Assembly_BaseAddr + 0x2DF8A50;
		using __get_position = Vector3*(*)(Transform*);
		auto get_position = reinterpret_cast<__get_position>(get_position_address);
		return get_position(this);
	}

protected:
private:
};
#pragma pack(pop)