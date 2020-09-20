#pragma once

#include "String.h"
#include "MessageControllerB.h"

#pragma pack(push, 1)
class GameUI
{
public:
	//unsigned char x9[0x9];
	unsigned char* m_messageController; // 0x0
	unsigned char* MessageController; // 0x8
	unsigned char* Fader; // 0x10 FaderB 
	unsigned char* Vignette; // 0x18 Vignette
	unsigned char* SeinUI; // 0x20 SeinUI
	unsigned char* m_sMenu; // 0x28 MenuScreenManager
	//static MessageControllerB getm_MessageController() { return m_messageController; }
	//static MessageControllerB getMessageController() { return MessageController; }

	/*GameObject(MoonString* name)
	{
		auto GameObject_address = Assembly_BaseAddr + 0x2336C40;
		using __GameObject = void(*)(GameObject*, MoonString*);
		auto GameObject = reinterpret_cast<__GameObject>(GameObject_address);
		GameObject(this, name);
	}*/

protected:
private:
};
#pragma pack(pop)