#pragma once

#include <string>
#include "Object.h"
#include "HString.h"
//il2cpp generated
#include "il2cpp-appdata.h"
#include "helpers.h"
using namespace app;

#pragma pack(push, 1)
namespace Moon {
	class GameObject : public virtual Moon::Object
	{

	public:
		//unsigned char x9[0x9];
		/*Transform transform; //Transform
		int layer;
		bool active;
		bool activeSelf;
		bool activeInHierarchy;
		bool isStatic;
		bool isStaticBatchable;
		int moonFlags;
		bool moonReady;
		const char* tag;*/
		//unsigned char scene[0x8];
		//unsigned char gameObject[0x8];

		/*GameObject(){}

		GameObject(HString* name)
		{
			auto GameObject_address = Assembly_BaseAddr + 0x2336C40;
			using __GameObject = void(*)(GameObject*, HString*);
			auto GameObject = reinterpret_cast<__GameObject>(GameObject_address);
			GameObject(this, name);
		}*/

		Moon::HString* get_tag()
		{
			auto get_tag_address = Assembly_BaseAddr + 0x2338410;
			using __get_tag = Moon::HString * (*)(Moon::GameObject*);
			auto get_tag = reinterpret_cast<__get_tag>(get_tag_address);
			return get_tag(this);
		}

		void set_tag(std::string value)
		{
			auto set_tag_address = Assembly_BaseAddr + 0x2338460;
			using __set_tag = void(*)(Moon::GameObject*, const char*);
			auto set_tag = reinterpret_cast<__set_tag>(set_tag_address);
			set_tag(this, value.data());
		}

		static Moon::GameObject* Find(String* name)
		{
			auto Find_address = Assembly_BaseAddr + 0x2338810;
			using __Find = Moon::GameObject * (*)(String*);
			auto Find = reinterpret_cast<__Find>(Find_address);
			return Find(name);
		}

	protected:
	private:
	};
}
#pragma pack(pop)