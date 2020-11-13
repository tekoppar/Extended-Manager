#pragma once

#include "GhostFrame.h"

#pragma pack(push, 1)
namespace Moon {
	class GhostRecorderData
	{
		static const int DATA_VERSION = 8; // 0x0
		static const int DATA_BACKWARDS_COMPATABILITY_VERSION = 8; // 0x0

	public:
		unsigned char x10[0xA];
		const char FILE_FORMAT_IDENTIFIER[0x8]; // 0x10 string
		const char CurrentFormatIdentifier[0x8]; // 0x18 string
		unsigned int CurrentVersion; // 0x20
		unsigned char x24[0x4];
		unsigned char Frames[0x8]; // 0x28 List<GhostFrame>GhostFrame**
		const char CurrentReplayPath[0x8]; // 0x30 string
		float Duration; // 0x38
		unsigned int m_flushedFramesCount; // 0x3C
		unsigned char m_timesliceLoadMemoryStream[0x8]; // 0x40 MemoryStream
		unsigned char m_timesliceLoadBinaryReader[0x8]; // 0x48 BinaryReader
		bool m_timeslicedLoadSucceeded; // 0x50
		unsigned char x57[0x7];
		unsigned char m_timesliceLoadStopwatch[0x8]; // 0x58 Stopwatch

		/*GhostFrame GetFrame(int index) { }
		{
			auto Run_address = Assembly_BaseAddr + 0xB31740;
			using GhostPlayer__Run = void(*)(GhostPlayer*);
			auto Run = reinterpret_cast<GhostPlayer__Run>(Run_address);
			return Run(this);
		}*/

		Moon::GhostFrame* get_LastFrame()
		{
			auto get_LastFrame_address = Assembly_BaseAddr + 0xB31810;
			using __get_LastFrame = Moon::GhostFrame * (*)(Moon::GhostRecorderData*);
			auto get_LastFrame = reinterpret_cast<__get_LastFrame>(get_LastFrame_address);
			return get_LastFrame(this);
		}

		Moon::GhostFrame* GetFrame(int index)
		{
			auto GetFrame_address = Assembly_BaseAddr + 0xB31740;
			using __GetFrame = Moon::GhostFrame * (*)(Moon::GhostRecorderData*, int);
			auto GetFrame = reinterpret_cast<__GetFrame>(GetFrame_address);
			return GetFrame(this, index);
		}

		void LoadFromFile(char* filePath)
		{
			auto LoadFromFile_address = Assembly_BaseAddr + 0xA000C0;
			using GhostPlayer__LoadFromFile = void(*)(Moon::GhostRecorderData*, char*);
			auto LoadFromFile = reinterpret_cast<GhostPlayer__LoadFromFile>(LoadFromFile_address);
			LoadFromFile(this, filePath);
		}

		void LoadFromReplay(char* replay)
		{
			auto LoadFromReplay_address = Assembly_BaseAddr + 0xB31C00;
			using GhostPlayer__LoadFromReplay = void(*)(Moon::GhostRecorderData*, char*);
			auto LoadFromReplay = reinterpret_cast<GhostPlayer__LoadFromReplay>(LoadFromReplay_address);
			LoadFromReplay(this, replay);
		}

	protected:
	private:

	};
}
#pragma pack(pop)