#pragma once

#include "RaceEnums.h"

class RaceTime : public Global
{
public:
	app::RaceTimer* GhostRaceTimer = nullptr;
	app::GameObject* RaceCountdownBox = nullptr;
	app::GameObject* RaceTimerBox = nullptr;
	app::GameObject* Toptime = nullptr;
	app::GameObject* BPtime = nullptr;
	app::String* RaceTimerDivisorMinute = nullptr;
	app::String* RaceTimerDivisorSecond = nullptr;

	TimerState CountdownTimerState = TimerState::TimerIsStopped;
	TimerState RaceTimerState = TimerState::TimerIsStopped;

	virtual void Update() override;
	virtual void Cleanup() override;

	void SetupRaceTimer(app::RaceTimer* raceTimer);
	void ResetGhostTimer(float bestRaceTime, float raceDuration);
	void StartRaceTimer(float bestRaceTime, float bptime, float raceDuration);
	void StartRaceCountdown();
	void StopRaceTimer();
	void UpdateTimer(float time);
	static std::string FormatFloat(float time);
};