#pragma once

#include "Component.h"

#pragma pack(push, 1)
namespace Moon {
	class Behaviour : public virtual Moon::Component
	{
	public:

		bool get_moonReady()
		{
			auto get_moonReadye_address = Assembly_BaseAddr + 0x215CFB0;
			using __get_moonReady = bool(*)(Moon::Behaviour*);
			auto get_moonReady = reinterpret_cast<__get_moonReady>(get_moonReadye_address);
			return get_moonReady(this);
		}
	protected:
	private:

	};
}
#pragma pack(pop)