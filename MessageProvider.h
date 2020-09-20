#pragma once

#include "HString.h"

#pragma pack(push, 1)
class MessageProvider
{
public:

	MessageProvider()
	{
		this->m_messages = new HString(0x1);
		this->x17[0x11] = 0x0;
	}

	MessageProvider(std::wstring message)
	{
		this->x17[0x11] = 0x0;
		this->m_messages = new HString(message, 0x1);
	}

	unsigned char x17[0x17];
	HString* m_messages; // 0x18 string[]

protected:
private:
};
#pragma pack(pop)