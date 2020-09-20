#pragma once

#include "GhostCharacterData.h"
#include "GhostRecorderData.h"
#include "HString.h"
#include "Component.h"

#pragma pack(push, 1)
class GhostRecorder : public MonoBehaviour, public Component
{
	const int PRE_RECORDING_TRACKING_MAX_SIZE = 1024; // 0x0
	static unsigned char m_stream[0x8]; // 0x0
	static GhostRecorder Instance; // 0x8
	static unsigned char s_puppets[0x8]; // 0x10 HashSet<GenericPuppet>
public:

	bool Enabled; // 0x18
	int CurrentFrameIndex; // 0x1C
	float Time; // 0x20
	unsigned char x27[0x4];
	unsigned char m_preRecordingData[0x8]; // 0x28 PreRecordingData
	unsigned char m_globalTable[0x8]; // 0x30 GlobalRecordingTable
	long m_previousCaret; // 0x38
	float m_previousFrameTime; // 0x40
	unsigned char x47[0x4];
	GhostRecorderData GhostRecorderData; // 0x48 GhostRecorderData
	char m_filePath[0x8]; // 0x50
	unsigned char m_binaryWriter[0x8]; // 0x58 BinaryWriter
	unsigned char m_plugins[0x8]; // 0x60 List<IGhostRecorderPlugin>
	GhostCharacterData PreviousCharacterData; // 0x68 GhostCharacterData
	bool IsSuspended; // 0x70
	unsigned char x73[0x3];
	unsigned char m_suspensionMask[0x8]; // 0x74 SuspendableMask

	GhostFrame get_CurrentFrame()
	{
		auto get_CurrentFrame_address = Assembly_BaseAddr + 0xB2E5B0;
		using oGet_CurrentFrame = GhostFrame(*)(GhostRecorder*);
		auto get_CurrentFrame = reinterpret_cast<oGet_CurrentFrame>(get_CurrentFrame_address);
		return get_CurrentFrame(this);
	}

	HString* get_FilePath()
	{ 
		auto get_FilePath_address = Assembly_BaseAddr + 0x2DFB40;
		using GhostRecorder__get_FilePath = HString *(*)(GhostRecorder*);
		auto get_FilePath = reinterpret_cast<GhostRecorder__get_FilePath>(get_FilePath_address);
		return get_FilePath(this);
	}

	void InitializeRecorder(HString* outputPath)
	{
		auto InitializeRecorder_address = Assembly_BaseAddr + 0xB2E760;
		using GhostRecorder__InitializeRecorder = void(*)(GhostRecorder*, HString*);
		auto InitializeRecorder = reinterpret_cast<GhostRecorder__InitializeRecorder>(InitializeRecorder_address);
		InitializeRecorder(this, outputPath);
	}

	void WriteToFile()
	{
		auto WriteToFile_address = Assembly_BaseAddr + 0xB2F7D0;
		using GhostRecorder__WriteToFile = void(*)(GhostRecorder*);
		auto WriteToFile = reinterpret_cast<GhostRecorder__WriteToFile>(WriteToFile_address);
		return WriteToFile(this);
	}

	void StartRecorder()
	{
		auto StartRecorder_address = Assembly_BaseAddr + 0xB2F350;
		using GhostRecorder__StartRecorder = void(*)(GhostRecorder*);
		auto StartRecorder = reinterpret_cast<GhostRecorder__StartRecorder>(StartRecorder_address);
		return StartRecorder(this);
	}

	void StopRecorder()
	{
		auto StopRecorder_address = Assembly_BaseAddr + 0xB2F4C0;
		using GhostRecorder__StopRecorder = void(*)(GhostRecorder*);
		auto StopRecorder = reinterpret_cast<GhostRecorder__StopRecorder>(StopRecorder_address);
		return StopRecorder(this);
	}

	bool get_IsSuspended()
	{
		auto get_IsSuspended_address = Assembly_BaseAddr + 0x4D94F0;
		using GhostRecorder__get_IsSuspended = bool(*)(GhostRecorder*);
		auto get_IsSuspended = reinterpret_cast<GhostRecorder__get_IsSuspended>(get_IsSuspended_address);
		return get_IsSuspended(this);
	}

	void FinalizeFrame() { }
	void Awake() { }
	void OnDestroy() { }
	void Cancel() { }
	void DestroyRecorder() { }
	void InitializeMemoryStream() { }
	//void InitializeRecorder(char* outputPath) { }

protected:
private:

};
#pragma pack(pop)