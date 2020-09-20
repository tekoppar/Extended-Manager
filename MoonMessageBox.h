#pragma once

#include "HString.h"
#include "MonoBehaviour.h"
#include "GameObject.h"
#include "MessageProvider.h"

#pragma pack(push, 1)
class MoonMessageBox : public MonoBehaviour
{
	const float WaitTimeBetweenMessages = 0.3f; // 0x0

public:
	unsigned char x17[0x11];
	unsigned char LanguageStyles[0x8]; // 0x18 MessageBoxLanguageStyles
	unsigned char WriteOutTextBox[0x8]; // 0x20 WriteOutTextBox
	unsigned char Visibility[0x8]; // 0x28 MessageBoxVisibility
	unsigned char TextBox[0x8]; // 0x30 TextBox
	unsigned char Avatar[0x8]; // 0x38 Transform
	int MessageIndex; // 0x40
	unsigned char x47[0x4];
	MessageProvider* MessageProvider; // 0x48
	unsigned char ScaleOverLetterCount[0x8]; // 0x50 AnimationCurve
	unsigned char OnFinishWriting[0x8]; // 0x58 Action
	unsigned char OnTextRefreshed[0x8]; // 0x60 Action
	GameObject Button; // 0x68
	GameObject Separator; // 0x70
	bool ShouldWriteOut; // 0x78

	HString* get_CurrentMessage()
	{
		auto get_CurrentMessage_address = Assembly_BaseAddr + 0x486280;
		using __get_CurrentMessage = HString *(*)(MoonMessageBox*);
		auto get_CurrentMessage = reinterpret_cast<__get_CurrentMessage>(get_CurrentMessage_address);
		return get_CurrentMessage(this);
	}

protected:
private:
};
#pragma pack(pop)