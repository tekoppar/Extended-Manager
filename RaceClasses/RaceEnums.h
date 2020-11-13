#pragma once

enum class GhostHandlerState {
	IsCleaningUpGhosts = 0,
	IsStartingGhosts = 1,
	IsCreatingEmptyGhost = 2,
	IsCreatingGhostPublic = 3,
	HasFinishedCleaningUpGhosts = 4,
	IsNormal = 5,
	IsNull = 6,
	IsCheckingGhostsFinished = 7,
};

enum class LeaderboardEntryType {
	PersonalBest = 0,
	TopScore = 1,
	FinishedRace = 2
};

enum class RaceState {
	RaceIsRestarting = 0,
	RaceIsStopping = 1,
	RaceIsStopped = 2,
	RaceIsRunning = 3,
	RaceIsStarting = 4,
	RaceIsCountdown = 5,
	RaceIsSettingUp = 6,
	RaceIsLoading = 7,
	RaceIsNormal = 8,
	RaceIsNull = 9,
	RaceIsFinished = 10,
	RaceHasFinishedRestarting = 11
};

enum class RaceSetupPhase {
	Phase0 = 6,
	Phase1 = 0,
	Phase2 = 1,
	Phase3 = 7,
	Phase4 = 8,
	StartCountdown = 5,
	Done = 3,
	Null = 4
};

enum class TimerState {
	TimerHasStarted = 0,
	TimerHasFinished = 1,
	TimerIsStopped = 2
};