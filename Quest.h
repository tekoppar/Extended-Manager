#pragma once

#include "HString.h"
#include "MonoBehaviour.h"

namespace Moon {
	namespace QuestEnums {
		enum QuestType // TypeDefIndex: 14649
		{
			Main = 0, // 0x0
			Side = 1, // 0x0
			Rumor = 2 // 0x0
		};

		enum QuestState // TypeDefIndex: 14650
		{
			Unassigned = 0, // 0x0
			Assigned = 1, // 0x0
			Completed = 2 // 0x0
		};

		enum QuestItemType // TypeDefIndex: 14651
		{
			None = 0, // 0x0
			IronNeedle = 1 // 0x0
		};
	}

#pragma pack(push, 1)
	class Quest : public Moon::MonoBehaviour
	{
		static Moon::Quest Instance; // 0x0
	public:
		unsigned char x9[0x9];

		Moon::MessageProvider NameMessageProvider; // 0x20
		Moon::MessageProvider ShortDescriptionMessageProvider; // 0x28
		Moon::MessageProvider DescriptionMessageProvider; // 0x30
		Moon::MessageProvider RewardMessageProvider; // 0x38
		Moon::QuestEnums::QuestType Type; // 0x40
		bool SilentUpdate; // 0x44
		bool HideObjectiveMarker; // 0x45
		unsigned char x47[0x2];
		Moon::Vector2 Position; // 0x48
		unsigned char Icon[0x8]; // 0x50 Texture2D
		Moon::Quest* ChainQuest; // 0x58
		unsigned char OnWelcomeReward[0x8]; // 0x60 QuestReward
		unsigned char OnCompleteReward[0x8]; // 0x68 QuestReward
		unsigned char NonInteractionReward[0x8]; // 0x70 QuestReward
		int StateOffset; // 0x78
		bool SaveOnUpdate; // 0x7C
		bool ShownOnMapByTimeline; // 0x7D
		unsigned char x7F[0x2];
		unsigned char m_resolvedUberState[0x8]; // 0x80 IGenericUberState
		unsigned char m_uberState[0x8]; // 0x88 MoonReference_IGenericUberState

		Moon::Quest get_LastInChain()
		{
			auto get_LastInChain_address = Assembly_BaseAddr + 0xB223F0;
			using __get_LastInChain = void(*)(Moon::Quest*);
			auto get_LastInChain = reinterpret_cast<__get_LastInChain>(get_LastInChain_address);
			get_LastInChain(this);
		}

	protected:
	private:
	};
}
#pragma pack(pop)