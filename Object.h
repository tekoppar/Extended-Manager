#pragma once

#include "Quaternion.h"

#pragma pack(push, 1)
class Object
{
	static int OffsetOfInstanceIDInCPlusPlusObject; // 0x0
	const char* objectIsNullMessage = "The Object you want to instantiate is null."; // 0x0
	const char* cloneDestroyedMessage = "Instantiate failed because the clone was destroyed during creation. This can happen if DestroyImmediate is called in MonoBehaviour.Awake."; // 0x0

public:
	unsigned char x9[0x10];
	unsigned char m_CachedPtr[0x8]; // 0x10

	/*inline Object Instantiate(Object* object)
	{
		return ((Object(__fastcall*)(Object*))((Assembly_BaseAddr)+0x2350B50))(this);
	}*/

	/*template<typename T, typename N>
	static T Instantiate(N original)
	{
		return ((T(__fastcall*)(Object*))((Assembly_BaseAddr)+0x136DB80));
	};*/

	static void DestroyObject(Object obj)
	{ 
		auto DestroyObject_address = Assembly_BaseAddr + 0x23519B0;
		using Object_DestroyObject = void(*)(Object);
		auto DestroyObject = reinterpret_cast<Object_DestroyObject>(DestroyObject_address);
		DestroyObject(obj);
	}

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

	static Object* Instantiate(Object* original)
	{ 
		auto Instantiate_address = Assembly_BaseAddr + 0x2351060;
		using Object_Instantiate = Object*(*)(Object*);
		auto Instantiate = reinterpret_cast<Object_Instantiate>(Instantiate_address);
		return Instantiate(original);
	}

	static Object* Instantiate(Object* original, Vector3 position, Quaternion rotation)
	{
		auto Instantiate_address = Assembly_BaseAddr + 0x2350B50;
		using Object_Instantiate = Object * (*)(Object*, Vector3, Quaternion);
		auto Instantiate = reinterpret_cast<Object_Instantiate>(Instantiate_address);
		return Instantiate(original, position, rotation);
	}

	template<typename T>
	static T FindObjectOfType()
	{
		auto FindObjectOfType_address = Assembly_BaseAddr + 0x136DA50;
		using Object_Instantiate = T(*)();
		auto FindObjectOfType = reinterpret_cast<Object_Instantiate>(FindObjectOfType_address);
		return FindObjectOfType();
	}

	template<typename T>
	static Object FindObjectOfType(T type) 
	{
		auto FindObjectOfType_address = Assembly_BaseAddr + 0x2351C40;
		using Object_Instantiate = Object(*)(T);
		auto FindObjectOfType = reinterpret_cast<Object_Instantiate>(FindObjectOfType_address);
		return FindObjectOfType(type);
	}

protected:
private:

};
#pragma pack(pop)