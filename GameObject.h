#pragma once

#include "HString.h"
#include <string>
#include "MonoBehaviour.h"

#pragma pack(push, 1)
class GameObject : public MonoBehaviour
{
	static GameObject* gameObject; // 0x0
public:
	//unsigned char x9[0x9];
	unsigned char transform; //Transform
	int layer;
	bool active;
	bool activeSelf;
	bool activeInHierarchy;
	bool isStatic;
	bool isStaticBatchable;
	int moonFlags;
	bool moonReady;
	HString* tag;
	unsigned char scene;

	GameObject(){}

	GameObject(HString* name)
	{
		auto GameObject_address = Assembly_BaseAddr + 0x2336C40;
		using __GameObject = void(*)(GameObject*, HString*);
		auto GameObject = reinterpret_cast<__GameObject>(GameObject_address);
		GameObject(this, name);
	}

	HString* get_tag()
	{
		auto get_tag_address = Assembly_BaseAddr + 0x2338410;
		using __get_tag = HString *(*)(GameObject*);
		auto get_tag = reinterpret_cast<__get_tag>(get_tag_address);
		return get_tag(this);
	}

	void set_tag(std::string value)
	{
		auto set_tag_address = Assembly_BaseAddr + 0x2338460;
		using __set_tag = void(*)(GameObject*, const char*);
		auto set_tag = reinterpret_cast<__set_tag>(set_tag_address);
		set_tag(this, value.data());
	}

	static GameObject* Find(std::wstring name)
	{
		auto Find_address = Assembly_BaseAddr + 0x2338810;
		using __Find = GameObject*(*)(const wchar_t*);
		auto Find = reinterpret_cast<__Find>(Find_address);
		return Find(name.data());
	}

protected:
private:
};
#pragma pack(pop)