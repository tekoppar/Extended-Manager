#pragma once

#include "HString.h"
#include "MonoBehaviour.h"
#include "GameObject.h"
#include "MessageProvider.h"
#include "MoonMessageBox.h"
#include "Quest.h"
#include "Vector3.h"

#pragma pack(push, 1)
namespace Moon {
	class MessageControllerB : public Moon::MonoBehaviour
	{
		const float DefaultDuration = 3; // 0x0
	public:

		unsigned char x17[0x11];
		Moon::GameObject AreaMessage; // 0x18
		Moon::GameObject AbilityMessage; // 0x20
		Moon::GameObject HintMessage; // 0x28
		Moon::GameObject HintSmallMessage; // 0x30
		Moon::GameObject BottomHintMessage; // 0x38
		Moon::GameObject PickupMessage; // 0x40
		Moon::GameObject StoryMessage; // 0x48
		Moon::GameObject HelpMessage; // 0x50
		Moon::GameObject SpiritTreeText; // 0x58
		Moon::GameObject QuestMessage; // 0x60
		Moon::GameObject CompleteQuestMessage; // 0x68
		Moon::GameObject UpdatedQuestMessage; // 0x70
		Moon::GameObject RaceFinishMessage; // 0x78
		Moon::GameObject AchievementMessage; // 0x80
		Moon::GameObject WispMessage; // 0x88
		Moon::GameObject CinematicStoryMessage; // 0x90
		Moon::GameObject CinematicMessageScreen; // 0x98
		Moon::GameObject NPCStoryMessage; // 0xA0
		Moon::GameObject NPCMessageScreen; // 0xA8
		Moon::GameObject NPCInteractionMessage; // 0xB0
		unsigned char NPCSideStoryMessages[0x8]; // 0xB8 List<GameObject>
		unsigned char NPCSideMessageScreens[0x8]; // 0xC0 List<GameObject>
		Moon::GameObject UrlAndCodeMessage; // 0xC8
		Moon::MoonMessageBox m_currentMessageBox; // 0xD0
		Moon::MoonMessageBox m_lastActiveNpcMessageScreen; // 0xD8
		unsigned char m_activeNpcMessageScreens[0x8]; // 0xE0 MoonMessageBox[]
		unsigned char m_activeNpcMessages[0x8]; // 0xE8 MoonMessageBox[]
		unsigned char DefaultVisuals[0x8]; // 0xF0 Dictionary<MessageControllerB.NpcMessageStyle, ShowFixedTimeTextEntity.TextVisuals>
		unsigned char m_currentNpcMessageStyle[0x4]; // 0xF8 MessageControllerB.NpcMessageStyle
		bool LastMessageWasShard; // 0xFC
		bool LastMessageWasQuest; // 0xFD
		unsigned char xFF[0x2];
		Moon::Quest LastQuest; // 0x100
		unsigned char LastShard[0x8]; // 0x108 SpiritShardType
		Moon::MoonMessageBox* m_lastWindow; // 0x110
		Moon::Vector2 spellMessageLocation; // 0x118
		Moon::Vector2 areaMessageLocation; // 0x120

		MessageControllerB() {}

		Moon::MoonMessageBox* ShowHintSmallMessage(Moon::MessageProvider* messageProvider, Moon::Vector3* position, float duration)
		{
			auto ShowHintSmallMessage_address = Assembly_BaseAddr + 0xD349C0;
			using __ShowHintSmallMessage = Moon::MoonMessageBox * (*)(Moon::MessageControllerB*, Moon::MessageProvider*, Moon::Vector3*, float);
			auto ShowHintSmallMessage = reinterpret_cast<__ShowHintSmallMessage>(ShowHintSmallMessage_address);
			return ShowHintSmallMessage(this, messageProvider, position, duration);
		}

	protected:
	private:
	};
}
#pragma pack(pop)