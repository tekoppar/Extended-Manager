#pragma once

#include "GhostRecorder.h"
#include "GhostPlayer.h"
#include "GhostRecorderData.h"
#include "GhostCharacterData.h"
#include "GhostService.h"
#include "GhostFrame.h"
#include "GameObject.h"

#pragma pack(push, 1)
namespace Moon {
	class GhostManager : public virtual Moon::MonoBehaviour
	{
	public:
		static Moon::GhostManager instance; // 0x0
		static bool s_preRecordTrackingEnabled; // 0x8
		unsigned char x17[0x10]; // 0x17
		Moon::GameObject* GhostPrefab;//GameObject GhostPrefab; // 0x18

		static Moon::HString* GetRaceDirectory(String* RaceID)
		{
			auto GetRaceDirectory_address = Assembly_BaseAddr + 0x9FC4C0; // GameAssembly.dll+0x9FC4C0
			using GhostManager__GetRaceDirectory = Moon::HString * (*)(String*);
			auto GetRaceDirectory = reinterpret_cast<GhostManager__GetRaceDirectory>(GetRaceDirectory_address);
			return GetRaceDirectory(RaceID);
		}

		static Moon::HString* GetGhostFile(String* directory)
		{
			auto GetGhostFile_address = Assembly_BaseAddr + 0x9FC5E0;
			using GhostManager__GetGhostFile = Moon::HString * (*)(String*);
			auto GetGhostFile = reinterpret_cast<GhostManager__GetGhostFile>(GetGhostFile_address);
			return GetGhostFile(directory);
		}

		static app::GhostRecorder* GetRecorder()
		{
			auto GetRecorder_address = Assembly_BaseAddr + 0x9FCD30;
			using GhostManager__GetRecorder = app::GhostRecorder * (*)();
			auto GetRecorder = reinterpret_cast<GhostManager__GetRecorder>(GetRecorder_address);
			return GetRecorder();
		}

		static app::GhostRecorder* GetOrCreateRecorder()
		{
			auto GetOrCreateRecorder_address = Assembly_BaseAddr + 0x9FCE10;
			using __GetOrCreateRecorder = app::GhostRecorder* (*)();
			auto GetOrCreateRecorder = reinterpret_cast<__GetOrCreateRecorder>(GetOrCreateRecorder_address);
			return GetOrCreateRecorder();
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

		Moon::GhostPlayer* createGhost(String* ghostInputFile)
		{
			auto createGhost_address = Assembly_BaseAddr + 0x9FC680;
			using GhostManager__createGhost = Moon::GhostPlayer * (*)(Moon::GhostManager*, String*);
			auto createGhost = reinterpret_cast<GhostManager__createGhost>(createGhost_address);
			return createGhost(this, ghostInputFile);
		}

		Moon::GhostPlayer* createGhost(String* displayName, String* replay) //ScenariosRecorder to record?
		{
			auto createGhost_address = Assembly_BaseAddr + 0x9FC930; //GameAssembly.dll+0x9FC930
			using GhostManager__createGhost = Moon::GhostPlayer * (*)(GhostManager*, String*, String*);
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
}