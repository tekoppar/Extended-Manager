#pragma once

#include "Adresses.h"
#include "Object.h"
#include "MonoBehaviour.h"

#pragma pack(push, 1)
namespace Moon {
	class SeinCharacter : public MonoBehaviour
	{
	public:
		// 0x00 - 0x17
		unsigned char uc_Unk0000_0017[0x18];

		// 0x18 - 0x1F
		unsigned char* m_pLogicCycle;

		// 0x20 - 0x27
		unsigned char* m_pAbilities;

		// 0x28 - 0x97
		unsigned char uc_Unk0028_0097[0x98 - 0x28];

		// 0x98 - 0x9F
		unsigned char* pPlatformBehaviour;

		inline void FillHealthAndEnergy()
		{
			((void(__fastcall*)(SeinCharacter*))((Assembly_BaseAddr)+0xA79E60))(this);
		}

		inline float get_FeetAngle()
		{
			return ((float(__fastcall*)(SeinCharacter*))((Assembly_BaseAddr)+0xA79900))(this);
		}
	};
}
#pragma pack(pop)