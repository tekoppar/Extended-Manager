#pragma once

#pragma pack(push, 1)
namespace Moon {
	class GhostPlayer : public virtual Moon::MonoBehaviour
	{
	public:
		/*unsigned char x8[0x4];
		unsigned char x12[0x4];
		unsigned char x17[0x8];
		GameObject* OriRig; // 0x18
		Transform* Puppets; // 0x20
		GameObject* PuppetPrefabs; // 0x28
		GameObject* RecordableObjectPuppetPrefabs; // 0x30
		unsigned char Name[0x8]; // 0x38 TextBox
		unsigned char GhostFlagRtpc[0x8]; // 0x40 RTPC
		unsigned char ParticleSystems[0x8]; // 0x48 ParticleSystem[]
		GameObject* GhostDisappearEffect; // 0x50
		int Index; // 0x58
		unsigned char x5F[0x4];
		unsigned char PlayerPuppetAbilities[0x8]; // 0x60 PlayerPuppetAbilities
		unsigned char PlayerPuppetCharacterStates[0x8]; // 0x68 PlayerPuppetCharacterStates
		unsigned char GhostRecordingFilePath[0x8]; // 0x70 string
		unsigned char GhostReplay[0x8]; // 0x78 string
		Transform* MirrorHolder; // 0x80
		unsigned char RigVisuals[0x8]; // 0x88 OriGhostRigVisuals
		float CurrentTime; // 0x90
		unsigned char x97[0x4];
		GhostRecorderData* GhostRecorderData; // 0x98
		unsigned char VisualSettings[0x8]; // 0xA0 OriGhostRigVisuals.GhostVisualSettings
		bool IsFinished; // 0xA8
		bool m_isStarted; // 0xA9
		unsigned char xAF[0x6];
		unsigned char m_plugins[0x8]; // 0xB0 List<IGhostRecorderPlugin>
		unsigned char m_puppets[0x8]; // 0xB8 Dictionary<int, CharacterStatePuppet>
		unsigned char m_recordableObjectPuppets[0x8]; // 0xC0 List<RecordableObjectPuppet>
		unsigned char m_metaDataPlugin[0x8]; // 0xC8 GhostRecordingMetaDataPlugin
		GameObject* m_oriRig; // 0xD0
		unsigned char m_animation[0x8]; // 0xD8 CharacterAnimationSystem
		unsigned char m_animator[0x8]; // 0xE0 MoonAnimator
		unsigned char OnFinished[0x8]; // 0xE8 Action
		bool IsSuspended; // 0xF0
		unsigned char xF3[0x3];
		unsigned char m_suspensionMask[0x8]; // 0xF4 SuspendableMask
		GhostCharacterData* m_ghostCharacterData; // 0xF8
		unsigned char m_soundHost[0x8]; // 0x100 SoundHost*/

		void Run()
		{
			auto Run_address = Assembly_BaseAddr + 0x9FF830; //GameAssembly.dll+0x9FF830
			using GhostPlayer__Run = void(*)(Moon::GhostPlayer*);
			auto Run = reinterpret_cast<GhostPlayer__Run>(Run_address);
			return Run(this);
		}

		void Stop()
		{
			auto Stop_address = Assembly_BaseAddr + 0xA000C0;
			using GhostPlayer__Stop = void(*)(Moon::GhostPlayer*);
			auto Stop = reinterpret_cast<GhostPlayer__Stop>(Stop_address);
			return Stop(this);
		}

		Moon::GhostCharacterData* get_CurrentGhostCharacterData()
		{
			auto get_CurrentGhostCharacterData_address = Assembly_BaseAddr + 0xA00F40;
			using __get_CurrentGhostCharacterData = Moon::GhostCharacterData * (*)(Moon::GhostPlayer*);
			auto get_CurrentGhostCharacterData = reinterpret_cast<__get_CurrentGhostCharacterData>(get_CurrentGhostCharacterData_address);
			return get_CurrentGhostCharacterData(this);
		}

	protected:
	private:

	};
}
#pragma pack(pop)