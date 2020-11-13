#pragma once

#include "HString.h"

#pragma pack(push, 1)
namespace Moon {
	class Object
	{
		static int OffsetOfInstanceIDInCPlusPlusObject; // 0x0
		static const char* objectIsNullMessage; // 0x0
		static const char* cloneDestroyedMessage; // 0x0

	public:
		unsigned char x9[0x9];
		unsigned char m_CachedPtr[0x8]; // 0x10

		static void DestroyObject(Moon::Object obj)
		{
			auto DestroyObject_address = Assembly_BaseAddr + 0x23519B0;
			using Object_DestroyObject = void(*)(Moon::Object);
			auto DestroyObject = reinterpret_cast<Object_DestroyObject>(DestroyObject_address);
			DestroyObject(obj);
		}

		static void Destroy(Moon::Object* obj)
		{
			auto Destroy_address = Assembly_BaseAddr + 0x2351560;
			using __Destroy = void(*)(Moon::Object*);
			auto Destroy = reinterpret_cast<__Destroy>(Destroy_address);
			Destroy(obj);
		}

		static Moon::Object* Instantiate(Moon::Object* original)
		{
			auto Instantiate_address = Assembly_BaseAddr + 0x2351060;
			using Object_Instantiate = Moon::Object * (*)(Moon::Object*);
			auto Instantiate = reinterpret_cast<Object_Instantiate>(Instantiate_address);
			return Instantiate(original);
		}

		static Moon::Object* Instantiate(Moon::Object* original, Moon::Vector3 position, Moon::Quaternion rotation)
		{
			auto Instantiate_address = Assembly_BaseAddr + 0x2350B50;
			using Object_Instantiate = Moon::Object * (*)(Moon::Object*, Moon::Vector3, Moon::Quaternion);
			auto Instantiate = reinterpret_cast<Object_Instantiate>(Instantiate_address);
			return Instantiate(original, position, rotation);
		}

		/*template<typename T, class N>
		static T* FindObjectOfType(N obj)
		{
			auto FindObjectOfType_address = Assembly_BaseAddr + 0x136DA50;
			using Object_Instantiate = T(*)(T *);
			auto FindObjectOfType = reinterpret_cast<Object_Instantiate>(FindObjectOfType_address);
			return FindObjectOfType(reinterpret_cast<T*>(obj));
		}*/

		Moon::HString* get_name()
		{
			auto get_name_address = Assembly_BaseAddr + 0x2350990;
			using __get_name = Moon::HString * (*)(Moon::Object*);
			auto get_name = reinterpret_cast<__get_name>(get_name_address);
			return get_name(this);
		}

	protected:
	private:

	};
#pragma pack(pop)

	const char* Moon::Object::objectIsNullMessage = "The Object you want to instantiate is null.";
	const char* Moon::Object::cloneDestroyedMessage = "Instantiate failed because the clone was destroyed during creation. This can happen if DestroyImmediate is called in MonoBehaviour.Awake.";
}
/*template<class T>
	static T FindObjectOfType()
	{
		auto FindObjectOfType_address = Assembly_BaseAddr + 0x136DA50;
		using Object_Instantiate = T(*)();
		auto FindObjectOfType = reinterpret_cast<Object_Instantiate>(FindObjectOfType_address);
		return FindObjectOfType();
	}*/

	/*static SeinCharacter Instantiate(SeinCharacter obj)
		{
			auto Instantiate_address = Assembly_BaseAddr + 0x2351060;
			using Object_Instantiate = SeinCharacter(*)(SeinCharacter);
			auto Instantiate = reinterpret_cast<Object_Instantiate>(Instantiate_address);
			SeinCharacter clone = Instantiate(obj);
			return clone;
		}*/

		/*template<typename T>
		static T* Instantiate(T* original)
		{
			auto Instantiate_address = Assembly_BaseAddr + 0x136DB80;
			using Object_Instantiate = T*(*)(T*);
			auto Instantiate = reinterpret_cast<Object_Instantiate>(Instantiate_address);
			auto clone = Instantiate(original);
			return clone;
		}*/

		/*inline Object Instantiate(Object* object)
			{
				return ((Object(__fastcall*)(Object*))((Assembly_BaseAddr)+0x2350B50))(this);
			}*/

			/*template<typename T, typename N>
			static T Instantiate(N original)
			{
				return ((T(__fastcall*)(Object*))((Assembly_BaseAddr)+0x136DB80));
			};*/

			/*static Object__Array* FindObjectOfType(Type* type)
				{
					auto FindObjectOfType_address = Assembly_BaseAddr + 0x2351C40;
					using __FindObjectOfType = Object__Array *(*)(Type*);
					auto FindObjectOfType = reinterpret_cast<__FindObjectOfType>(FindObjectOfType_address);
					return FindObjectOfType(type);
				}*/