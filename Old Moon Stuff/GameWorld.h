#pragma once

#pragma pack(push, 1)
namespace Moon {
	float gameCompletionHooked = 0.0f;
	class GameWorld
	{
	public:
		// 0x0000 - 0x0017
		unsigned char uc_Unk0000_0017[0x18];

		float GetGameCompletion();

	protected:
	private:

	};
}
#pragma pack(pop)