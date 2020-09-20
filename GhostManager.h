#pragma once

#include "Object.h"
#include "GhostRecorder.h"
#include "GhostPlayer.h"
#include "GhostRecorderData.h"
#include "GhostCharacterData.h"
#include "GhostService.h"
#include "GhostFrame.h"
#include "GameObject.h"
#include "Component.h"
/*namespace Moon {
#include "SystemString2.h"
}*/
namespace Moon3 {
#include "SystemString3.h"
}

#pragma pack(push, 1)
class GhostManager : public MonoBehaviour
{
public:
	static GhostManager instance; // 0x0
	static bool s_preRecordTrackingEnabled; // 0x8
	unsigned char x17[0x8];
	GameObject GhostPrefab; // 0x18

	static HString* GetRaceDirectory(Moon3::Moon_MoonString_o* RaceID)
	{ 
		auto GetRaceDirectory_address = Assembly_BaseAddr + 0x9FC4C0; // GameAssembly.dll+0x9FC4C0
		using GhostManager__GetRaceDirectory = HString* (*)(Moon3::Moon_MoonString_o*);
		auto GetRaceDirectory = reinterpret_cast<GhostManager__GetRaceDirectory>(GetRaceDirectory_address);
		return GetRaceDirectory(RaceID);
	}

	static HString* GetGhostFile(Moon3::Moon_MoonString_o directory)
	{
		auto GetGhostFile_address = Assembly_BaseAddr + 0x9FC5E0;
		using GhostManager__GetGhostFile = HString * (*)(Moon3::Moon_MoonString_o);
		auto GetGhostFile = reinterpret_cast<GhostManager__GetGhostFile>(GetGhostFile_address);
		return GetGhostFile(directory);
	}

	static GhostRecorder* GetRecorder()
	{
		auto GetRecorder_address = Assembly_BaseAddr + 0x9FCD30;
		using GhostManager__GetRecorder = GhostRecorder*(*)();
		auto GetRecorder = reinterpret_cast<GhostManager__GetRecorder>(GetRecorder_address);
		return GetRecorder();
	}

	static void StartPreRecording()
	{ 
		auto StartPreRecording_address = Assembly_BaseAddr + 0x9FCFD0;
		using GhostManager__StartPreRecording = void(*)();
		auto StartPreRecording = reinterpret_cast<GhostManager__StartPreRecording>(StartPreRecording_address);
		return StartPreRecording();
	}

	static void StopPreRecording()
	{ 
		auto StopPreRecording_address = Assembly_BaseAddr + 0x9FD050;
		using GhostManager__StopPreRecording = void(*)();
		auto StopPreRecording = reinterpret_cast<GhostManager__StopPreRecording>(StopPreRecording_address);
		return StopPreRecording();
	}

	GhostPlayer* createGhost(Moon3::Moon_MoonString_o ghostInputFile)
	{
		auto createGhost_address = Assembly_BaseAddr + 0x9FC680;
		using GhostManager__createGhost = GhostPlayer*(*)(GhostManager*, Moon3::Moon_MoonString_o);
		auto createGhost = reinterpret_cast<GhostManager__createGhost>(createGhost_address);
		return createGhost(this, ghostInputFile);
	}

	GhostPlayer* createGhost(Moon3::Moon_MoonString_o displayName, Moon3::Moon_MoonString_o replay) //ScenariosRecorder to record?
	{
		auto createGhost_address = Assembly_BaseAddr + 0x9FC930; //GameAssembly.dll+0x9FC930
		using GhostManager__createGhost = GhostPlayer * (*)(GhostManager*, Moon3::Moon_MoonString_o, Moon3::Moon_MoonString_o);
		auto createGhost = reinterpret_cast<GhostManager__createGhost>(createGhost_address);
		return createGhost(this, displayName, replay);
	}

protected:
private:
};
#pragma pack(pop)

enum RaceID // TypeDefIndex: 12501
{
	NotDefined = 0, // 0x0
	lumaPools = 1,// 0x0
	wellspringGlades = 2, // 0x0
	baursReach = 3, // 0x0
	kwolokDrop = 4, // 0x0
	inkwaterMarsh = 5, // 0x0
	silentWoodland = 6, // 0x0
	desert = 7, // 0x0
	mouldwoodDepths = 8 // 0x0
};