#pragma once

#include "HString.h"

namespace Moon {
	enum ScenarioRecorderState // TypeDefIndex: 14247
	{
		Disabled = 0, // 0x0
		PreRecording = 1, // 0x0
		Recording = 2 // 0x0
	};

#pragma pack(push, 1)
	class ScenariosRecorder : public virtual MonoBehaviour
	{
		const char* REPLAY_BASE_PATH = "\\Assets\\frameworks\\ghost\\timeline\\replays\\"; // 0x0
		static ScenarioRecorderState m_state; // 0x0
		static const char* m_scenarioName; // 0x8
	public:

		GhostRecorder m_recorder; // 0x18

		void StartRecording()
		{
			auto StartRecording_address = Assembly_BaseAddr + 0xDAAB70;
			using __StartRecording = void* (*)(ScenariosRecorder*);
			auto StartRecording = reinterpret_cast<__StartRecording>(StartRecording_address);
			StartRecording(this);
		}

		void EndRecording()
		{
			auto EndRecording_address = Assembly_BaseAddr + 0xDABCE0;
			using __EndRecording = void* (*)(ScenariosRecorder*);
			auto EndRecording = reinterpret_cast<__EndRecording>(EndRecording_address);
			EndRecording(this);
		}

	protected:
	private:

	};
#pragma pack(pop)

	const char* ScenariosRecorder::m_scenarioName = "spooky";
}