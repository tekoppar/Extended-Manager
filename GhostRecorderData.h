#pragma once

#include "GhostFrame.h"
#include "MonoBehaviour.h"

#pragma pack(push, 1)

class GhostRecorderData : public MonoBehaviour
{
	const int DATA_VERSION = 8; // 0x0
	const int DATA_BACKWARDS_COMPATABILITY_VERSION = 8; // 0x0

public:
	unsigned char x9[0x9];
	char FILE_FORMAT_IDENTIFIER[0x8]; // 0x10 string
	char CurrentFormatIdentifier[0x8]; // 0x18 string
	int CurrentVersion; // 0x20
	unsigned char Frames[0x8]; // 0x28 List<GhostFrame>
	char CurrentReplayPath[0x8]; // 0x30 string
	float Duration; // 0x38
	int m_flushedFramesCount; // 0x3C
	unsigned char m_timesliceLoadMemoryStream[0x8]; // 0x40 MemoryStream
	unsigned char m_timesliceLoadBinaryReader[0x8]; // 0x48 BinaryReader
	bool m_timeslicedLoadSucceeded; // 0x50
	unsigned char x57[0x8];
	unsigned char m_timesliceLoadStopwatch[0x8]; // 0x58 Stopwatch

	/*GhostFrame GetFrame(int index) { }
	{
		auto Run_address = Assembly_BaseAddr + 0xB31740;
		using GhostPlayer__Run = void(*)(GhostPlayer*);
		auto Run = reinterpret_cast<GhostPlayer__Run>(Run_address);
		return Run(this);
	}*/

	void LoadFromFile(char* filePath)
	{
		auto LoadFromFile_address = Assembly_BaseAddr + 0xA000C0;
		using GhostPlayer__LoadFromFile = void(*)(GhostRecorderData*, char*);
		auto LoadFromFile = reinterpret_cast<GhostPlayer__LoadFromFile>(LoadFromFile_address);
		LoadFromFile(this, filePath);
	}

	void LoadFromReplay(char* replay)
	{
		auto LoadFromReplay_address = Assembly_BaseAddr + 0xB31C00;
		using GhostPlayer__LoadFromReplay = void(*)(GhostRecorderData*, char*);
		auto LoadFromReplay = reinterpret_cast<GhostPlayer__LoadFromReplay>(LoadFromReplay_address);
		LoadFromReplay(this, replay);
	}

protected:
private:

};
#pragma pack(pop)