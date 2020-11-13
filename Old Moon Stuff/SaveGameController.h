#pragma once

#include "Adresses.h"

#pragma pack(push, 1)
namespace Moon {
	class SaveGameController
	{
	public:
		inline int get_CurrentSlotIndex()
		{
			return ((int(__fastcall*)(SaveGameController*))((Assembly_BaseAddr)+0x7DAC30))(this);
		}

		inline int get_CurrentBackupIndex()
		{
			return ((int(__fastcall*)(SaveGameController*))((Assembly_BaseAddr)+0x7DAC40))(this);
		}

		inline bool get_SaveGameQueried()
		{
			return ((bool(__fastcall*)(SaveGameController*))((Assembly_BaseAddr)+0x7DAC50))(this);
		}

		inline bool CanPerformSave()
		{
			return ((bool(__fastcall*)(SaveGameController*))((Assembly_BaseAddr)+0x7DE090))(this);
		}

		inline bool CanPerformLoad()
		{
			return ((bool(__fastcall*)(SaveGameController*))((Assembly_BaseAddr)+0x7DDDF0))(this);
		}

		inline bool PerformLoad() //can't call crashes game
		{
			if (Assembly_BaseAddr + 0x7DD280)
				return ((bool(__fastcall*)(SaveGameController*))((Assembly_BaseAddr)+0x7DD280))(this);
			return false;
		}

		inline void PerformSave() //can't call crashes game
		{
			((void(__fastcall*)(SaveGameController*))((Assembly_BaseAddr)+0x7DD990))(this);
		}

		inline void RestoreCheckpoint()
		{
			if (Assembly_BaseAddr + 0x7DE210)
				((void(__fastcall*)(SaveGameController*))((Assembly_BaseAddr)+0x7DE210))(this);
		}

		inline bool get_IsStorageBusy()
		{
			return ((bool(__fastcall*)(SaveGameController*))((Assembly_BaseAddr)+0x7DAD40))(this);
		}

	protected:
	private:
		// 0x0000 - 0x0019
		unsigned char uc_Unk0000_0019[0x10];
		unsigned char m_saveSnapshot[0x8];
		unsigned int m_lastSavedFrameIndex;
		float m_startTime;
	};
}
#pragma pack(pop)

/*class CDetour /* add ": public CMember" to enable access to member variables... */
/*{
public:
	void Mine_Target(void);
	static void (CDetour::* Real_Target)(void);

	// Class shouldn't have any member variables or virtual functions.
};

void CDetour::Mine_Target(void)
{
	gameCompletionHooked = 100.0f;
	(this->*Real_Target)();
}

void (CDetour::* CDetour::Real_Target)(void) = (void (CDetour::*)(void))&SaveGameController::RestoreCheckpoint;*/