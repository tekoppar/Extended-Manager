#pragma once

#include "Object.h"
#include "HString.h"
#include "Transform.h"

#pragma pack(push, 1)
namespace Moon {
	class Component : public virtual Moon::Object
	{
	public:
		/*unsigned char* transform[0x8];
		GameObject gameObject;
		int moonFlags;
		HString* tag;*/

		Moon::HString* get_tag()
		{
			auto get_tag_address = Assembly_BaseAddr + 0x2166C30;
			using __get_tag = Moon::HString * (*)(Moon::Component*);
			auto get_tag = reinterpret_cast<__get_tag>(get_tag_address);
			return get_tag(this);
		}

		void set_tag(Moon::HString* value)
		{
			auto set_tag_address = Assembly_BaseAddr + 0x2166CD0;
			using __set_tag = void(*)(Moon::Component*, Moon::HString*);
			auto set_tag = reinterpret_cast<__set_tag>(set_tag_address);
			set_tag(this, value);
		}

		Moon::Transform* get_transform()
		{
			auto set_tag_address = Assembly_BaseAddr + 0x44FCE0;
			using __set_tag = Moon::Transform * (*)(Moon::Component*);
			auto set_tag = reinterpret_cast<__set_tag>(set_tag_address);
			return set_tag(this);
		}

	protected:
	private:

	};
}
#pragma pack(pop)