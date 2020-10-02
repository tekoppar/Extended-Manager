#pragma once

#include "GameObject.h"
//il2cpp generated
#include "il2cpp-appdata.h"
#include "helpers.h"
using namespace app;

#pragma pack(push, 1)
namespace Moon {
	class FindObjectsWrapper
	{
	public:

		static Moon::GameObject* Find(String* name)
		{
			auto Find_address = Assembly_BaseAddr + 0x2457EF0;
			using __Find = Moon::GameObject * (*)(String*);
			auto Find = reinterpret_cast<__Find>(Find_address);
			return Find(name);
		}
	protected:
	private:

	};
}
#pragma pack(pop)
