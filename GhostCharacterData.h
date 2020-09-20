#pragma once

#include "Vector3.h"
#include "Vector2.h"
#include "MonoBehaviour.h"

#pragma pack(push, 1)
class GhostCharacterData : public MonoBehaviour
{
public:
	unsigned char x9[0x9];
	Vector3 Position; // 0x10
	bool FaceLeft; // 0x1C
	float FeetAngle; // 0x20
	Vector3 FeetPosition; // 0x24
	Vector2 LocalSpeed; // 0x30
	Quaternion MirrorHolderRotation; // 0x38
	bool Executed; // 0x48

	int GetDataSize()
	{
		auto GetDataSize_address = Assembly_BaseAddr + 0x9F1580;
		using oGetDataSize = int(*)(GhostCharacterData*);
		auto GetDataSize = reinterpret_cast<oGetDataSize>(GetDataSize_address);
		return GetDataSize(this);
	}
	//void SaveToFile(BinaryWriter binaryWriter) { } 0x9F4320
	/*void Run()
	{
		auto Run_address = Assembly_BaseAddr + 0x9FF830;
		using GhostPlayer__Run = void(*)(GhostPlayer*);
		auto Run = reinterpret_cast<GhostPlayer__Run>(Run_address);
		return Run(this);
	}

	void Stop()
	{
		auto Stop_address = Assembly_BaseAddr + 0xA000C0;
		using GhostPlayer__Stop = void(*)(GhostPlayer*);
		auto Stop = reinterpret_cast<GhostPlayer__Stop>(Stop_address);
		return Stop(this);
	}*/

protected:
private:

};
#pragma pack(pop)