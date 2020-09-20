#pragma once

#include "HString.h"
#include "MonoBehaviour.h"
#include "Quest.h"
namespace Moon {
#include "SystemString2.h"
}

#pragma pack(push, 1)
class QuestsController : public MonoBehaviour
{
public:
	static QuestsController Instance; // 0x0
	unsigned char x9[0x9];

	Quest GetQuestByName(Moon3::Moon_MoonString_o* name)
	{
		auto GetQuestByName_address = Assembly_BaseAddr + 0xB2AB00; // GameAssembly.dll+0xB2AB00
		using __GetQuestByName = Quest(*)(QuestsController*, Moon3::Moon_MoonString_o*);
		auto GetQuestByName = reinterpret_cast<__GetQuestByName>(GetQuestByName_address);
		return GetQuestByName(this, name);
	}

	Quest GetActiveQuest()
	{
		auto GetActiveQuest_address = Assembly_BaseAddr + 0xB28C40;
		using __GetActiveQuest = Quest(*)(QuestsController*);
		auto GetActiveQuest = reinterpret_cast<__GetActiveQuest>(GetActiveQuest_address);
		return GetActiveQuest(this);
	}

protected:
private:
};
#pragma pack(pop)