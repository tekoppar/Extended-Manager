#pragma once

#pragma pack(push, 1)
namespace Moon {
	typedef struct Vector3
	{
	public:

		Vector3(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
		Vector3(float x, float y)
		{
			this->x = x;
			this->y = y;
			this->z = 0.0f;
		}
		Vector3()
		{
			this->x = 0.0f;
			this->y = 0.0f;
			this->z = 0.0f;
		}

		inline void Set(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		float x; //0x0
		float y; //0x4
		float z; //0x8

	protected:
	private:
	} Vector3;
}
#pragma pack(pop)