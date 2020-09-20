#pragma once

#include "HString.h"
#include "MonoBehaviour.h"
#include "GameObject.h"
#include "MessageProvider.h"
#include "MoonMessageBox.h"
#include "Quest.h"
#include "Vector3.h"

#pragma pack(push, 1)
class MessageControllerB : public MonoBehaviour
{
	const float DefaultDuration = 3; // 0x0
public:

	unsigned char x17[0x11];
	GameObject AreaMessage; // 0x18
	GameObject AbilityMessage; // 0x20
	GameObject HintMessage; // 0x28
	GameObject HintSmallMessage; // 0x30
	GameObject BottomHintMessage; // 0x38
	GameObject PickupMessage; // 0x40
	GameObject StoryMessage; // 0x48
	GameObject HelpMessage; // 0x50
	GameObject SpiritTreeText; // 0x58
	GameObject QuestMessage; // 0x60
	GameObject CompleteQuestMessage; // 0x68
	GameObject UpdatedQuestMessage; // 0x70
	GameObject RaceFinishMessage; // 0x78
	GameObject AchievementMessage; // 0x80
	GameObject WispMessage; // 0x88
	GameObject CinematicStoryMessage; // 0x90
	GameObject CinematicMessageScreen; // 0x98
	GameObject NPCStoryMessage; // 0xA0
	GameObject NPCMessageScreen; // 0xA8
	GameObject NPCInteractionMessage; // 0xB0
	unsigned char NPCSideStoryMessages[0x8]; // 0xB8 List<GameObject>
	unsigned char NPCSideMessageScreens[0x8]; // 0xC0 List<GameObject>
	GameObject UrlAndCodeMessage; // 0xC8
	MoonMessageBox m_currentMessageBox; // 0xD0
	MoonMessageBox m_lastActiveNpcMessageScreen; // 0xD8
	unsigned char m_activeNpcMessageScreens[0x8]; // 0xE0 MoonMessageBox[]
	unsigned char m_activeNpcMessages[0x8]; // 0xE8 MoonMessageBox[]
	unsigned char DefaultVisuals[0x8]; // 0xF0 Dictionary<MessageControllerB.NpcMessageStyle, ShowFixedTimeTextEntity.TextVisuals>
	unsigned char m_currentNpcMessageStyle[0x4]; // 0xF8 MessageControllerB.NpcMessageStyle
	bool LastMessageWasShard; // 0xFC
	bool LastMessageWasQuest; // 0xFD
	unsigned char xFF[0x2];
	Quest LastQuest; // 0x100
	unsigned char LastShard[0x8]; // 0x108 SpiritShardType
	MoonMessageBox* m_lastWindow; // 0x110
	Vector2 spellMessageLocation; // 0x118
	Vector2 areaMessageLocation; // 0x120

	MessageControllerB(){}

	MoonMessageBox* ShowHintSmallMessage(MessageProvider* messageProvider, Vector3* position, float duration)
	{
		auto ShowHintSmallMessage_address = Assembly_BaseAddr + 0xD349C0;
		using __ShowHintSmallMessage = MoonMessageBox*(*)(MessageControllerB*, MessageProvider*, Vector3*, float);
		auto ShowHintSmallMessage = reinterpret_cast<__ShowHintSmallMessage>(ShowHintSmallMessage_address);
		return ShowHintSmallMessage(this, messageProvider, position, duration);
	}

protected:
private:
};
#pragma pack(pop)