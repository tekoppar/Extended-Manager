#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include "StringUtils.h"
#include "ManagerDef.h"
#include "MessageHelper.h"
#include "GraphDrawer.h"
#include "RaceEnums.h"

#include "RaceTime.h"

void RaceTime::SetupRaceTimer(app::RaceTimer* raceTimer)
{
	if (GhostRaceTimer == nullptr)
		GhostRaceTimer = raceTimer;
}

void RaceTime::CleanUp()
{
	//GhostRaceTimer = nullptr;
	app::Object_1_Destroy_1((app::Object_1*)RaceCountdownBox, NULL);
	RaceCountdownBox = nullptr;
	app::Object_1_Destroy_1((app::Object_1*)RaceTimerBox, NULL);
	RaceTimerBox = nullptr;
	app::Object_1_Destroy_1((app::Object_1*)Toptime, NULL);
	Toptime = nullptr;
	app::Object_1_Destroy_1((app::Object_1*)BPtime, NULL);
	RaceTimerBox = nullptr;
	CountdownTimerState = TimerState::TimerIsStopped;
	RaceTimerState = TimerState::TimerIsStopped;
}

void RaceTime::ResetGhostTimer(float bestRaceTime, float raceDuration)
{
	if (GhostRaceTimer != nullptr)
	{
		GhostRaceTimer->fields._ElapsedTime_k__BackingField = 0.0f;
		GhostRaceTimer->fields.m_adjustedElapsedTime = 0.0f;
		GhostRaceTimer->fields.m_startedRace = false;
		GhostRaceTimer->fields._BestTime_k__BackingField = bestRaceTime;
		GhostRaceTimer->fields._PersonalBestTime_k__BackingField = bestRaceTime;
		GhostRaceTimer->fields._TimeToBeat_k__BackingField = raceDuration;
		GhostRaceTimer->fields._IsSuspended_k__BackingField = false;
	}
}

void RaceTime::StopRaceTimer()
{
	app::RaceTimer_Stop(GhostRaceTimer, NULL);
	CountdownTimerState = TimerState::TimerIsStopped;
	RaceTimerState = TimerState::TimerIsStopped;
}

void RaceTime::StartRaceTimer(float bestRaceTime, float bptime, float raceDuration)
{
	CountdownTimerState = TimerState::TimerIsStopped;
	RaceTimerState = TimerState::TimerHasStarted;

	if (GhostRaceTimer != nullptr)
	{
		if (RaceCountdownBox != nullptr)
			MessageHelper::SetMessage(RaceCountdownBox, "00:00.000");

		RaceCountdownBox = nullptr;

		app::RaceTimer_Reset(GhostRaceTimer, NULL);
		GhostRaceTimer->fields._ElapsedTime_k__BackingField = 0.0f;
		GhostRaceTimer->fields.m_adjustedElapsedTime = 0.0f;
		GhostRaceTimer->fields.m_startedRace = true;
		GhostRaceTimer->fields._TimeLimit_k__BackingField = raceDuration + 99999999.0f;
		GhostRaceTimer->fields._BestTime_k__BackingField = bestRaceTime;
		GhostRaceTimer->fields._PersonalBestTime_k__BackingField = bestRaceTime;
		GhostRaceTimer->fields._TimeToBeat_k__BackingField = raceDuration;
		GhostRaceTimer->fields._IsSuspended_k__BackingField = false;
		app::RaceTimer_SetTimeLimit(GhostRaceTimer, raceDuration + 99999999.0f, NULL);
		app::RaceTimer_StartTimer(GhostRaceTimer, NULL);

		RaceTimerBox = MessageHelper::CreateMessageboxNoBackground("00:00.000", tem::Vector3(0, 3, 0), 99999999.0f);

		Toptime = MessageHelper::CreateMessageboxNoBackground("00:00.000", tem::Vector3(0.5, 3.5, 0), 99999999.0f);
		MessageHelper::SetMessage(Toptime, RaceTime::FormatFloat(bestRaceTime), 16.0f);

		if (bestRaceTime < bptime)
		{
			BPtime = MessageHelper::CreateMessageboxNoBackground("00:00.000", tem::Vector3(-0.5, 3.5, 0), 99999999.0f);
			MessageHelper::SetMessage(BPtime, RaceTime::FormatFloat(bptime), 16.0f);
		}
	}
}

void RaceTime::StartRaceCountdown()
{
	if (GhostRaceTimer != nullptr)
	{
		CountdownTimerState = TimerState::TimerHasStarted;
		RaceTimerState = TimerState::TimerIsStopped;

		app::RaceTimer_Reset(GhostRaceTimer, NULL);
		GhostRaceTimer->fields._ElapsedTime_k__BackingField = 0.0f;
		GhostRaceTimer->fields.m_adjustedElapsedTime = 0.0f;
		app::RaceTimer_StartTimer(GhostRaceTimer, NULL);
	}

	RaceCountdownBox = MessageHelper::CreateMessageboxNoBackground("00:03.000", tem::Vector3(0, 2.5f, 0), 3.0f);
}

std::string RaceTime::FormatFloat(float time)
{
	double minutes = std::floor(std::fmod(time * 1000.0f / (1000.0f * 60.0f), 60));// std::floor(raceFloat / (1000.0f * 60.0f) % 60);
	double seconds = std::floor(std::fmod(time * 1000.0f / 1000.0f, 60));// std::floor(raceFloat / 1000.0f % 60);
	double milliseconds = std::floor(std::fmod(time * 1000.0f, 1000));

	std::string raceTimerMinute = sutil::DoubleToStr(minutes);
	std::string raceTimerSeconds = sutil::DoubleToStr(seconds);
	raceTimerSeconds = raceTimerSeconds.length() == 2 ? raceTimerSeconds : "0" + raceTimerSeconds;
	std::string raceTimerMilliseconds = sutil::DoubleToStr(milliseconds);
	raceTimerMilliseconds = raceTimerMilliseconds.length() == 3 ? raceTimerMilliseconds : (raceTimerMilliseconds.length() == 2 ? "0" + raceTimerMilliseconds : "00" + raceTimerMilliseconds);

	return raceTimerMinute + ":" + raceTimerSeconds + "." + raceTimerMilliseconds;
}

void RaceTime::UpdateTimer(float time)
{
	if (CountdownTimerState == TimerState::TimerIsStopped && RaceTimerState == TimerState::TimerIsStopped)
		return;

	std::string timeS = RaceTime::FormatFloat(time);
	if (RaceCountdownBox != nullptr)
	{
		if (time > 0.0f)
			MessageHelper::SetMessage(RaceCountdownBox, timeS, 24);
		else
		{
			MessageHelper::SetMessage(RaceCountdownBox, RaceTime::FormatFloat(0.0f), 24);
			CountdownTimerState = TimerState::TimerHasFinished;
			RaceTimerState = TimerState::TimerIsStopped;
		}
	}

	if (RaceTimerBox != nullptr)
	{
		if (time > GhostRaceTimer->fields._BestTime_k__BackingField)
			MessageHelper::SetMessage(RaceTimerBox, timeS, 32.0f, &GraphColors::Red);
		else
			MessageHelper::SetMessage(RaceTimerBox, timeS, 32.0f, &GraphColors::Grey);
	}
}