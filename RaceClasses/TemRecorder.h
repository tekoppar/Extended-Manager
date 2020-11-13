#pragma once

#include "RaceEnums.h"

class TemRecorder
{
public:
	app::GhostRecorder* GhostRecorder = nullptr;
	app::GhostCharacterAbilitiesPlugin* ghostAP = nullptr;
	app::GhostCharacterPlugin* ghostCP = nullptr;
	app::GhostStateMachinePlugin* ghostSMP = nullptr;
	app::GhostGenericEventsPlugin* ghostGEP = nullptr;
	app::GhostRecordingMetaDataPlugin* ghostMDP = nullptr;

	//std::string RacePath = "";

	void CreateRecorder();
	bool StartRecorder();
	bool StopRecorder();
	bool WriteRecorder(std::string filePath, LeaderboardEntryType type = LeaderboardEntryType::FinishedRace);
	void FinalizeGhostFrame();
	void ResetRecorder();
	void SetRecorderPath(std::string path);
};

