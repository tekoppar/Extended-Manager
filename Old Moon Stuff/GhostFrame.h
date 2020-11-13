#pragma once

#pragma pack(push, 1)
namespace Moon {
	class GhostFrame
	{
	public:
		unsigned char x9[0x9];
		float Time; // 0x10
		unsigned char x4[0x4];
		unsigned char FrameData[0x8]; // 0x18  List<IGhostFrameData>


		//void SaveToFile(BinaryWriter binaryWriter) { } 0x9F4320
		/*void Run()
		{
			auto Run_address = Assembly_BaseAddr + 0x9FF830;
			using GhostPlayer__Run = void(*)(GhostPlayer*);
			auto Run = reinterpret_cast<GhostPlayer__Run>(Run_address);
			return Run(this);
		}

		void Stop()
		{
			auto Stop_address = Assembly_BaseAddr + 0xA000C0;
			using GhostPlayer__Stop = void(*)(GhostPlayer*);
			auto Stop = reinterpret_cast<GhostPlayer__Stop>(Stop_address);
			return Stop(this);
		}*/

	protected:
	private:

	};
#pragma pack(pop)

	enum class GhostFrame_FrameDataTypes // TypeDefIndex: 14131
	{
		None = 0, // 0x0
		Transform = 1, // 0x0
		Animation = 2, // 0x0
		StateMachine = 3, // 0x0
		CharacterData = 4, // 0x0
		CharacterAbilities = 5, // 0x0
		CharacterStates = 6, // 0x0
		GenericEvents = 7, // 0x0
		RecordingMetaDataData = 8, // 0x0
		PhysicaSystemManagerData = 9, // 0x0
		ServerEvents = 10, // 0x0
		WorldEvents = 11, // 0x0
		TimelineEvents = 12, // 0x0
		Camera = 13, // 0x0
		UberState = 14, // 0x0
		SceneTracking = 15, // 0x0
		TimeTracking = 16, // 0x0
		LineRenderer = 17, // 0x0
		AnimationParameters = 18 // 0x0
	};
}