#pragma once

#pragma pack(push, 1)
namespace Moon {
	class Transform
	{

	public:

		Moon::Vector3 position;
		Moon::Vector3 localPosition;
		Moon::Vector3 eulerAngles;
		Moon::Vector3 localEulerAngles;
		Moon::Vector3 right;
		Moon::Vector3 up;
		Moon::Vector3 forward;
		Moon::Quaternion rotation;
		Moon::Quaternion localRotation;
		unsigned char rotationOrder; //RotationOrder
		Moon::Vector3 localScale;
		unsigned char parent[0xC]; //Transform
		unsigned char parentInternal[0xC]; //Transform
		unsigned char worldToLocalMatrix[0x10]; //Matrix4x4
		unsigned char localToWorldMatrix[0x10]; //Matrix4x4
		unsigned char root[0xC]; //Transform
		int childCount;
		Moon::Vector3 lossyScale;
		bool hasChanged;
		int hierarchyCapacity;
		int hierarchyCount;

		Vector3* get_position()
		{
			auto get_position_address = Assembly_BaseAddr + 0x2DF8A50;
			using __get_position = Moon::Vector3 * (*)(Moon::Transform*);
			auto get_position = reinterpret_cast<__get_position>(get_position_address);
			return get_position(this);
		}

	protected:
	private:
	};
}
#pragma pack(pop)