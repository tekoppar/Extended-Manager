#pragma once

#include "HString.h"
#include "MonoBehaviour.h"

#pragma pack(push, 1)
class RaceSystem : public MonoBehaviour
{
public:
	unsigned char x9[0x9];

	void UnloadScene(HString* sceneName)
	{
		auto UnloadScene_address = Assembly_BaseAddr + 0xBAFB70;
		using __UnloadScene = void(*)(RaceSystem*, HString*);
		auto UnloadScene = reinterpret_cast<__UnloadScene>(UnloadScene_address);
		UnloadScene(this, sceneName);
	}

	void RestartRace()
	{
		auto RestartRace_address = Assembly_BaseAddr + 0xBAEDE0;
		using __RestartRace = void(*)(RaceSystem*);
		auto RestartRace = reinterpret_cast<__RestartRace>(RestartRace_address);
		RestartRace(this);
	}

protected:
private:
};
#pragma pack(pop)