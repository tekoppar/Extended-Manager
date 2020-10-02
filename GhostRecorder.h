#pragma once

#include "GhostRecorderPlugins.h"
#include "GhostCharacterData.h"
#include "GhostRecorderData.h"
#include "HString.h"
#include "Component.h"

#pragma pack(push, 1)
namespace Moon {
	class GhostRecorder : public virtual Moon::MonoBehaviour
	{
		static const int PRE_RECORDING_TRACKING_MAX_SIZE = 1024; // 0x0
		static unsigned char m_stream[0x8]; // 0x0
		static Moon::GhostRecorder Instance; // 0x8
		static unsigned char s_puppets[0x8]; // 0x10 HashSet<GenericPuppet>
	public:

		unsigned char x4[0x4];
		unsigned char x8[0x4];
		unsigned char x12[0x4];
		unsigned char x16[0x4];
		bool Enabled; // 0x18
		unsigned char x1B[0x3];
		int CurrentFrameIndex; // 0x1C
		float Time; // 0x20
		unsigned char x24[0x4];
		unsigned char m_preRecordingData[0x8]; // 0x28 PreRecordingData
		unsigned char m_globalTable[0x8]; // 0x30 GlobalRecordingTable
		long m_previousCaret; // 0x38
		unsigned char x3C[0x4];
		float m_previousFrameTime; // 0x40
		unsigned char x47[0x4];
		Moon::GhostRecorderData* GhostRecorderData; // 0x48 GhostRecorderData
		const char m_filePath[0x8]; // 0x50
		unsigned char m_binaryWriter[0x8]; // 0x58 BinaryWriter
		unsigned char m_plugins[0x8]; // 0x60 List<IGhostRecorderPlugin>
		Moon::GhostCharacterData* PreviousCharacterData; // 0x68 GhostCharacterData
		bool IsSuspended; // 0x70
		unsigned char x73[0x3];
		unsigned char m_suspensionMask[0x8]; // 0x74 SuspendableMask

		Moon::GhostFrame get_CurrentFrame()
		{
			auto get_CurrentFrame_address = Assembly_BaseAddr + 0xB2E5B0;
			using oGet_CurrentFrame = Moon::GhostFrame(*)(Moon::GhostRecorder*);
			auto get_CurrentFrame = reinterpret_cast<oGet_CurrentFrame>(get_CurrentFrame_address);
			return get_CurrentFrame(this);
		}

		String* get_FilePath()
		{
			auto get_FilePath_address = Assembly_BaseAddr + 0x2DFB40;
			using GhostRecorder__get_FilePath = String* (*)(Moon::GhostRecorder*);
			auto get_FilePath = reinterpret_cast<GhostRecorder__get_FilePath>(get_FilePath_address);
			return get_FilePath(this);
		}

		void InitializeRecorder(String* outputPath)
		{
			auto InitializeRecorder_address = Assembly_BaseAddr + 0xB2E760;
			using GhostRecorder__InitializeRecorder = void(*)(Moon::GhostRecorder*, String*);
			auto InitializeRecorder = reinterpret_cast<GhostRecorder__InitializeRecorder>(InitializeRecorder_address);
			InitializeRecorder(this, outputPath);
		}

		void WriteToFile()
		{
			auto WriteToFile_address = Assembly_BaseAddr + 0xB2F7D0;
			using GhostRecorder__WriteToFile = void(*)(Moon::GhostRecorder*);
			auto WriteToFile = reinterpret_cast<GhostRecorder__WriteToFile>(WriteToFile_address);
			return WriteToFile(this);
		}

		void StartRecorder()
		{
			auto StartRecorder_address = Assembly_BaseAddr + 0xB2F350;
			using GhostRecorder__StartRecorder = void(*)(Moon::GhostRecorder*);
			auto StartRecorder = reinterpret_cast<GhostRecorder__StartRecorder>(StartRecorder_address);
			return StartRecorder(this);
		}

		void StopRecorder()
		{
			auto StopRecorder_address = Assembly_BaseAddr + 0xB2F4C0;
			using GhostRecorder__StopRecorder = void(*)(Moon::GhostRecorder*);
			auto StopRecorder = reinterpret_cast<GhostRecorder__StopRecorder>(StopRecorder_address);
			return StopRecorder(this);
		}

		bool get_IsSuspended()
		{
			auto get_IsSuspended_address = Assembly_BaseAddr + 0x4D94F0;
			using GhostRecorder__get_IsSuspended = bool(*)(Moon::GhostRecorder*);
			auto get_IsSuspended = reinterpret_cast<GhostRecorder__get_IsSuspended>(get_IsSuspended_address);
			return get_IsSuspended(this);
		}

		void FinalizeFrame()
		{
			auto FinalizeFrame_address = Assembly_BaseAddr + 0xB2FA80;
			using __FinalizeFrame = void* (*)(Moon::GhostRecorder*);
			auto FinalizeFrame = reinterpret_cast<__FinalizeFrame>(FinalizeFrame_address);
			FinalizeFrame(this);
		}

		Moon::GhostCharacterPlugin* GetPlugin()
		{
			auto GetPlugine_address = Assembly_BaseAddr + 0x13B2E00;
			using __GetPlugin = Moon::GhostCharacterPlugin * (*)(Moon::GhostRecorder*);
			auto GetPlugin = reinterpret_cast<__GetPlugin>(GetPlugine_address);
			return GetPlugin(this);
		}

		void Awake() { }
		void OnDestroy() { }
		void Cancel() { }
		void DestroyRecorder() { }
		void InitializeMemoryStream() { }
		//void InitializeRecorder(char* outputPath) { }

	protected:
	private:

	};
}
#pragma pack(pop)