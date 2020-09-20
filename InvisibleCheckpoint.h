#pragma once

#include "Adresses.h"
#include "Object.h"
#include "MonoBehaviour.h"
#include "Rect.h"
#include "Vector2.h"

#pragma pack(push, 1)

class InvisibleCheckpoint : public GameObject, public Transform
{
public:
	// 0x0000 - 0x0017
	unsigned char uc_Unk0000_0017[0x18];
	unsigned char Condition[0x8]; // 0x18
	Vector2 RespawnPosition; // 0x20
	bool m_shouldAcceptRecievers; // 0x28
	unsigned char x2B[0x3];
	UnityEngineRect Bounds; // 0x2C
	unsigned char x38[0x4];
	unsigned char m_tempWaterZoneList[0x8]; // 0x40

	inline void Awake() 
	{
		if (Assembly_BaseAddr + 0x70CCE0)
			((void(__fastcall*)(InvisibleCheckpoint*))((Assembly_BaseAddr)+0x70CCE0))(this);
	}

	inline void ctor()
	{
		if (Assembly_BaseAddr + 0x70E6C0)
			((void(__fastcall*)(InvisibleCheckpoint*))((Assembly_BaseAddr)+0x70E6C0))(this);
	}

	UnityEngineRect CalculateBounds()
	{
		auto CalculateBounds_address = Assembly_BaseAddr + 0x70E3A0;
		using InvisibleCheckpoint__CalculateBounds = UnityEngineRect(*)(InvisibleCheckpoint*);
		auto CalculateBounds = reinterpret_cast<InvisibleCheckpoint__CalculateBounds>(CalculateBounds_address);
		return CalculateBounds(this);
	}

protected:
private:
	static void cctor()
	{
		if (Assembly_BaseAddr + 0x70E860)
			((void(__fastcall*)(InvisibleCheckpoint*))((Assembly_BaseAddr)+0x70E860));
	}
};
#pragma pack(pop)