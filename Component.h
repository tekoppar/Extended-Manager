#pragma once

#include "Object.h"
#include "Transform.h"
#include "HString.h"

#pragma pack(push, 1)
class Component : Object
{
public:
	unsigned char* transform[0x8];
	GameObject gameObject;
	int moonFlags;
	HString* tag;

	HString* get_tag()
	{
		auto get_tag_address = Assembly_BaseAddr + 0x2166C30;
		using __get_tag = HString *(*)(Component*);
		auto get_tag = reinterpret_cast<__get_tag>(get_tag_address);
		return get_tag(this);
	}

	void set_tag(HString* value)
	{
		auto set_tag_address = Assembly_BaseAddr + 0x2166CD0;
		using __set_tag = void(*)(Component*, HString*);
		auto set_tag = reinterpret_cast<__set_tag>(set_tag_address);
		set_tag(this, value);
	}

	Transform* get_transform()
	{
		auto set_tag_address = Assembly_BaseAddr + 0x44FCE0;
		using __set_tag = Transform*(*)(Component*);
		auto set_tag = reinterpret_cast<__set_tag>(set_tag_address);
		return set_tag(this);
	}

protected:
private:

};
#pragma pack(pop)