#pragma once

#include "HString.h"
#include "MonoBehaviour.h"
#include "Quest.h"

namespace Moon {
#pragma pack(push, 1)
	class QuestsController : public Moon::MonoBehaviour
	{
	public:
		static Moon::QuestsController Instance; // 0x0
		unsigned char x9[0x9];

		Moon::Quest GetQuestByName(String* name)
		{
			auto GetQuestByName_address = Assembly_BaseAddr + 0xB2AB00; // GameAssembly.dll+0xB2AB00
			using __GetQuestByName = Moon::Quest(*)(Moon::QuestsController*, String*);
			auto GetQuestByName = reinterpret_cast<__GetQuestByName>(GetQuestByName_address);
			return GetQuestByName(this, name);
		}

		Moon::Quest GetActiveQuest()
		{
			auto GetActiveQuest_address = Assembly_BaseAddr + 0xB28C40;
			using __GetActiveQuest = Moon::Quest(*)(Moon::QuestsController*);
			auto GetActiveQuest = reinterpret_cast<__GetActiveQuest>(GetActiveQuest_address);
			return GetActiveQuest(this);
		}

	protected:
	private:
	};
}
#pragma pack(pop)