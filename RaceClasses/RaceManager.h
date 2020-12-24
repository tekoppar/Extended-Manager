#pragma once

#include "FrameLogger.h"
#include "RaceTime.h"
#include "TemRecorder.h"
#include "SeinCharacterHelper.h"
#include "Tem.h"
#include "RaceEnums.h"

class RaceAttempt {
public:
	std::string RaceName = "Race";
	float RaceTime = 10000000.0f;
	long long int Attempt = 0;

	std::string ToString();
};

class RaceAttemptManager {
public:
	std::vector<RaceAttempt> Attempts;
	std::string RaceName = "Race";
	std::string Filename = "";
	RaceAttempt BestAttempt = RaceAttempt();

	void GetAttempts();
	void WriteAttempts();
	void WriteAttempt(RaceAttempt attempt);
	void AddAttempt(float time);
};

class RaceManager : public Global
{
public:
	RaceAttemptManager AttemptManager;
	FrameLogger FrameLogger;
	RaceTime RaceTime;
	TemRecorder TemGhostRecorder;
	static RaceState State;
	static RaceSetupPhase SetupPhase;
	static int TickCount;

	static const int GhostLimit;

	/*app::GhostCharacterAbilitiesPlugin* ghostAP = nullptr;
	app::GhostCharacterPlugin* ghostCP = nullptr;
	app::GhostStateMachinePlugin* ghostSMP = nullptr;
	app::GhostGenericEventsPlugin* ghostGEP = nullptr;
	app::GhostRecordingMetaDataPlugin* ghostMDP = nullptr;*/
	app::GhostRecorder* ghostC = nullptr;
	app::RaceSystem* raceSC = nullptr;

	app::GhostRecorder* seinRecorder = nullptr;
	app::GhostPlayer* newSeinMimicGhost = nullptr;
	int lastMimicFrameUpdate = 0;
	unsigned long long lastMimicBytePosition = 0;
	bool ghostHasStarted = false;
	bool playingAnimation = false;
	unsigned long long startedWeRacing = 0;
	unsigned long long totalFrames = 0;

	//app::MoonAnimation* RaceFinishAnimation = nullptr;
	//app::MoonAnimation* RaceNewPBAnimation = nullptr;
	//app::MoonAnimation* RaceTopScoreAnimation = nullptr;
	//app::MoonAnimation* RaceLoopAnimation = nullptr;

	app::GameObject* RaceGoalObject = nullptr;
	std::vector<app::Material*> RaceGoalMaterials = std::vector<app::Material*>();
	app::PlayerInsideZoneChecker* raceFinishZone = nullptr;
	app::GameObject* RaceBody = nullptr;
	app::PlayerInsideZoneChecker* RaceGoal = nullptr;
	app::PhysicMaterial* RaceGoalMaterial = nullptr;

	unsigned long long LastReadBytePosition = 0;

	tem::Vector3 StartPosition;
	tem::Vector3 FinishPosition;
	int SeinFacingDirection = 0;
	std::string raceName = "";
	std::string racePath = "";
	std::vector<app::GameObject*> raceCheckpoints;
	std::vector<app::PlayerInsideZoneChecker*> raceCheckpointsCollision;
	std::vector<tem::Rect> raceCheckpointsRects;
	std::vector<bool> raceCheckpointsHit;
	std::unordered_map<int, SeinStateUpdate> abilitiesStates;
	std::unordered_map<int, SeinStateUpdate> abilitiesUpgradeStates;
	std::vector<SeinShardUpdate> shardsStates;
	std::unordered_map<int, SeinShard> shardsInInventory;
	std::vector<app::SpiritShardType__Enum> shardsToEquip;
	std::string BoundAbility1 = "None";
	std::string BoundAbility2 = "None";
	std::string BoundAbility3 = "None";
	std::string RaceHash = "";

	float RaceDuration = -1.0f;
	bool CountdownHasStarted = false;
	bool IsRacing = false;
	bool IsRaceLoaded = false;
	bool IsRaceCheckpointCreated = false;

	void SetupManager();
	virtual void Update() override;
	void LoadRaceData(std::string path);
	void CleanupManager();
	void RemoveCheckpoint(int index);
	void UpdateCheckpoint(tem::Vector3 position, tem::Vector3 scale, int index);
	bool CheckIfHitAllCheckpoints();
	void ResetHitCheckpoints();
	void CheckIfInsideCheckpoint(tem::Vector3 previousPosition, tem::Vector3 currentPosition);
	void CheckTimer();
	void FinishedRace(float time);
	void StartRace();
	void RestartRace();
	void StopRace();
	static bool HasRaceStopped();
	//void CreateRecorder();
	//bool StartRecorder();
	//bool StopRecorder();
	//bool WriteRecorder(std::string filePath = "", LeaderboardEntryType type = LeaderboardEntryType::FinishedRace);
	//void FinalizeGhostFrame();
	//void ResetRecorder();
	void CreateFinishLine();
	void SetupRace(float raceDuration = 60.0f);
	void SetupRacePhase2(float raceDuration = 60.0f);
	void SetupRacePhase3(float raceDuration = 60.0f);
	void SetupRacePhase4(float raceDuration = 60.0f);
	void SetupRacePhase5(float raceDuration = 60.0f);
	void SetupRacePhase6(float raceDuration = 60.0f);
	std::string GetLastGhostFrame();
	//void CreateMimicGhost();
	//void RegisterGhostPlayerPlugins(app::GhostPlayer* ghostPlayer);
	//void UpdateMimicGhostFrameData(int lastFrame);
	//app::GhostRecorder* CreateNewGhostRecorder();
	//void CreateSeinRecorder();
	void GetSeinFrames();
	void CheckHash();
};