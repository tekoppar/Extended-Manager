#pragma once

#include "il2cpp-appdata.h"
#include "helpers.h"

#include "GraphDrawer.h"
#include "ManagerDef.h"

#ifndef _FRAMELOGGER_H
#define _FRAMELOGGER_H

enum DroppedFrameDataType {
	DangerFrames = 0,
	DroppedFramesSingle = 1,
	DroppedFramesDouble = 2,
	DroppedFramesTriple = 3,
	DroppedFramesMultiple = 4
};

enum FPSMonitorDataType {
	RenderedFrames = 0,
	CurrentSampleTime = 1,
	CurrentMaxFrameTime = 2,
	CurrentMinFrameTime = 3,
	FrameTime = 4,
	AverageFPS = 5,
	MinimumFPS = 6,
	MaximumFPS = 7,
	AverageFrameTime = 8,
	MinFrameTime = 9,
	MaxFrameTime = 10,
	DeltaTimeAverage = 11,
	HitchDeltaTimeAverage = 12,
	SlowDownDeltaTimeAverage = 13,
	HitchCount = 14,
	SlowdownCount = 15,
	FrameCount = 16,
	BadFrameCount = 17
};

enum BashDataType {
	Bashing = 0,
	HoldAirTime = 1,
	FrictionTimeRemaining = 2
};

enum BowDataType {
	AimDuration = 0,
	AimDurationCritical = 1,
	CurrentStateTime = 2,
	ChargeAmount = 3,
	IsAiming = 4,
};

enum DoubleJumpDataType {
	DoubleJumpTime = 0,
	NumberOfJumpsAvailable = 1,
	RemainingLockTime = 2,
	IsDoubleJumping = 3
};

class DroppedFrameData {
public:
	int DangerFrames = 0;
	int DroppedFramesSingle = 0;
	int DroppedFramesDouble = 0;
	int DroppedFramesTriple = 0;
	int DroppedFramesMultiple = 0;

	DroppedFrameData(app::DroppedFrameMonitor* data = nullptr)
	{
		if (data != nullptr)
		{
			DangerFrames = data->fields.DangerFrames;
			DroppedFramesSingle = data->fields.DroppedFrames_Single;
			DroppedFramesDouble = data->fields.DroppedFrames_Double;
			DroppedFramesTriple = data->fields.DroppedFrames_Triple;
			DroppedFramesMultiple = data->fields.DroppedFrames_Multiple;
		}
		else
		{
			DangerFrames = 0;
			DroppedFramesSingle = 0;
			DroppedFramesDouble = 0;
			DroppedFramesTriple = 0;
			DroppedFramesMultiple = 0;
		}
	}

	std::string ToString()
	{
		return "0:" + std::to_string(DangerFrames) + " 1:" + std::to_string(DroppedFramesSingle) +
			" 2:" + std::to_string(DroppedFramesDouble) + " 3:" + std::to_string(DroppedFramesTriple) +
			" 4:" + std::to_string(DroppedFramesMultiple);
	}
};

class FPSMonitorData {
public:
	float RenderedFrames = 0.0f;
	float CurrentSampleTime = 0.0f;
	float CurrentMaxFrameTime = 0.0f;
	float CurrentMinFrameTime = 0.0f;
	float FrameTime = 0.0f;
	int AverageFPS = 0;
	int MinimumFPS = 0;
	int MaximumFPS = 0;
	float AverageFrameTime = 0.0f;
	float MinFrameTime = 0.0f;
	float MaxFrameTime = 0.0f;
	float DeltaTimeAverage = 0.0f;
	float HitchDeltaTimeAverage = 0.0f;
	float SlowDownDeltaTimeAverage = 0.0f;
	int HitchCount = 0;
	int SlowdownCount = 0;
	int FrameCount = 0;
	int BadFrameCount = 0;
	int FrameIndex = 0;

	FPSMonitorData(app::FPSMonitor* data = nullptr)
	{
		if (data != nullptr)
		{
			RenderedFrames = data->fields.m_renderedFrames;
			CurrentSampleTime = data->fields.m_currentSampleTime;
			CurrentMaxFrameTime = data->fields.m_currentMaxFrameTime;
			CurrentMinFrameTime = data->fields.m_currentMinFrameTime;
			FrameTime = data->fields.m_frameTime;
			AverageFPS = data->fields.AverageFPS;
			MinimumFPS = data->fields.MinimumFPS;
			MaximumFPS = data->fields.MaximumFPS;
			AverageFrameTime = data->fields.AverageFrameTime;
			MinFrameTime = data->fields.MinFrameTime;
			MaxFrameTime = data->fields.MaxFrameTime;
			DeltaTimeAverage = data->fields.m_deltaTimeAverage;
			HitchDeltaTimeAverage = data->fields.m_hitchDeltaTimeAverage;
			SlowDownDeltaTimeAverage = data->fields.m_slowDownDeltaTimeAverage;
			HitchCount = data->fields.m_hitchCount;
			SlowdownCount = data->fields.m_slowdownCount;
			FrameCount = data->fields.m_frameCount;
			BadFrameCount = data->fields.m_badFrameCount;
			FrameIndex = data->fields.m_frameIndex;
		}
		else
		{
			RenderedFrames = 0.0f;
			CurrentSampleTime = 0.0f;
			CurrentMaxFrameTime = 0.0f;
			CurrentMinFrameTime = 0.0f;
			FrameTime = 0.0f;
			AverageFPS = 0;
			MinimumFPS = 0;
			MaximumFPS = 0;
			AverageFrameTime = 0.0f;
			MinFrameTime = 0.0f;
			MaxFrameTime = 0.0f;
			DeltaTimeAverage = 0.0f;
			HitchDeltaTimeAverage = 0.0f;
			SlowDownDeltaTimeAverage = 0.0f;
			HitchCount = 0;
			SlowdownCount = 0;
			FrameCount = 0;
			BadFrameCount = 0;
			FrameIndex = 0;
		}
	}

	std::string ToString()
	{
		return "0:" + futil::TrimLeadingZeroes(std::to_string(RenderedFrames)) + " 1:" + futil::TrimLeadingZeroes(std::to_string(CurrentSampleTime)) +
			" 2:" + futil::TrimLeadingZeroes(std::to_string(CurrentMaxFrameTime)) + " 3:" + futil::TrimLeadingZeroes(std::to_string(CurrentMinFrameTime)) +
			" 4:" + futil::TrimLeadingZeroes(std::to_string(FrameTime)) + " 5:" + futil::TrimLeadingZeroes(std::to_string(AverageFPS)) +
			" 6:" + futil::TrimLeadingZeroes(std::to_string(MinimumFPS)) + " 7:" + futil::TrimLeadingZeroes(std::to_string(MaximumFPS)) +
			" 8:" + futil::TrimLeadingZeroes(std::to_string(AverageFrameTime)) + " 9:" + futil::TrimLeadingZeroes(std::to_string(MinFrameTime)) +
			" 10:" + futil::TrimLeadingZeroes(std::to_string(MaxFrameTime)) + " 11:" + futil::TrimLeadingZeroes(std::to_string(DeltaTimeAverage)) +
			" 12:" + futil::TrimLeadingZeroes(std::to_string(HitchDeltaTimeAverage)) + " 13:" + futil::TrimLeadingZeroes(std::to_string(SlowDownDeltaTimeAverage)) +
			" 14:" + futil::TrimLeadingZeroes(std::to_string(HitchCount)) + " 15:" + futil::TrimLeadingZeroes(std::to_string(SlowdownCount)) +
			" 16:" + futil::TrimLeadingZeroes(std::to_string(FrameCount)) + " 17:" + futil::TrimLeadingZeroes(std::to_string(BadFrameCount)) +
			" 18:" + futil::TrimLeadingZeroes(std::to_string(FrameIndex));
	}
};

class SeinPlatformMovementData {
public:
	app::Vector2 AdditiveLocalSpeed;
	app::Vector2 AdditiveSpeed;
	app::Vector2 PrevWorldSpeed;
	app::Vector2 CurrentSpeed;

	SeinPlatformMovementData(app::CharacterPlatformMovement* platform = nullptr)
	{
		if (platform != nullptr)
		{
			AdditiveLocalSpeed = platform->fields.AdditiveLocalSpeed;
			AdditiveSpeed = platform->fields.AdditiveSpeed;
			PrevWorldSpeed = platform->fields.m_prevWorldSpeed;
		}
		else
		{
			AdditiveLocalSpeed = app::Vector2();
			AdditiveLocalSpeed.x = 0.0f;
			AdditiveLocalSpeed.y = 0.0f;
			AdditiveSpeed = app::Vector2();
			AdditiveSpeed.x = 0.0f;
			AdditiveSpeed.y = 0.0f;
			PrevWorldSpeed = app::Vector2();
			PrevWorldSpeed.x = 0.0f;
			PrevWorldSpeed.y = 0.0f;
			CurrentSpeed = app::Vector2();
			CurrentSpeed.x = 0.0f;
			CurrentSpeed.y = 0.0f;
		}
	}
};

class FrameLoggerSingleFrame {
public:
	DroppedFrameData droppedFrameData;
	FPSMonitorData fpsMonitorData;
	SeinPlatformMovementData seinPlatformMovement;
};

class FrameLogger {
public:
	app::DroppedFrameMonitor* droppedFrameMonitor = nullptr;
	app::FPSMonitor* fpsMonitor = nullptr;
	app::SeinCharacter* sein = nullptr;
	app::NanoProfiler* nanoProfiler = nullptr;
	app::Vector3 oldSeinPosition = app::Vector3();

	bool DataIsDisplayed = false;

	std::string filePath = "";
	std::vector<std::string> FrameData;
	std::vector<FrameLoggerSingleFrame> AllFrames;

	void Initialize()
	{
		droppedFrameMonitor = GetObjectByType<app::DroppedFrameMonitor>("", "DroppedFrameMonitor");
		fpsMonitor = GetObjectByType<app::FPSMonitor>("", "FPSMonitor");
		sein = GetObjectByType<app::SeinCharacter>("", "SeinCharacter");

		if (droppedFrameMonitor == nullptr && fpsMonitor != nullptr && fpsMonitor->fields.m_DroppedFrameMonitor != nullptr)
			droppedFrameMonitor = fpsMonitor->fields.m_DroppedFrameMonitor;

		graphDrawer.Initialize();
		Graph::Instance = &graphDrawer;
	}

	void ResetData()
	{
		if (fpsMonitor != nullptr)
			app::FPSMonitor_Reset(fpsMonitor, NULL);

		FrameData = std::vector<std::string>();
		AllFrames = std::vector<FrameLoggerSingleFrame>();
		oldSeinPosition = app::Vector3();
	}

	void LoggFrame()
	{
		std::string frameData = "";
		frameData += GetDroppedFrameData();
		frameData += GetFPSMonitorData();
		frameData += GetSeinStatesData();
		FrameLoggerSingleFrame singleFrame = FrameLoggerSingleFrame();
		singleFrame.droppedFrameData = DroppedFrameData(droppedFrameMonitor);
		singleFrame.fpsMonitorData = FPSMonitorData(fpsMonitor);
		singleFrame.seinPlatformMovement = SeinPlatformMovementData(sein->fields.PlatformBehaviour->fields.PlatformMovement);

		if (oldSeinPosition.x != 0.0f && oldSeinPosition.y != 0.0f)
		{
			singleFrame.seinPlatformMovement.CurrentSpeed.x = (std::fabs(oldSeinPosition.x) - std::fabs(sein->fields.PlatformBehaviour->fields.PlatformMovement->fields.m_oldPosition.x)) * singleFrame.fpsMonitorData.AverageFPS;
			singleFrame.seinPlatformMovement.CurrentSpeed.y = (std::fabs(oldSeinPosition.y) - std::fabs(sein->fields.PlatformBehaviour->fields.PlatformMovement->fields.m_oldPosition.y)) * singleFrame.fpsMonitorData.AverageFPS;
		}
		oldSeinPosition = sein->fields.PlatformBehaviour->fields.PlatformMovement->fields.m_oldPosition;

		AllFrames.push_back(singleFrame);
		FrameData.push_back(frameData);
		sutil::Write(filePath, frameData + "\n");
	}

	std::string GetDroppedFrameData()
	{
		std::string droppedFrameData = "";

		if (droppedFrameMonitor != nullptr)
		{
			droppedFrameData += "0:" + std::to_string(droppedFrameMonitor->fields.DangerFrames);
			droppedFrameData += " 1:" + std::to_string(droppedFrameMonitor->fields.DroppedFrames_Single);
			droppedFrameData += " 2:" + std::to_string(droppedFrameMonitor->fields.DroppedFrames_Double);
			droppedFrameData += " 3:" + std::to_string(droppedFrameMonitor->fields.DroppedFrames_Triple);
			droppedFrameData += " 4:" + std::to_string(droppedFrameMonitor->fields.DroppedFrames_Multiple) + "|";
		}

		return droppedFrameData;
	}

	std::string GetFPSMonitorData()
	{
		std::string fpsMonitorData = "";

		if (fpsMonitor != nullptr)
		{
			fpsMonitorData += "0:" + futil::TrimLeadingZeroes(std::to_string(fpsMonitor->fields.m_renderedFrames));
			fpsMonitorData += " 1:" + futil::TrimLeadingZeroes(std::to_string(fpsMonitor->fields.m_currentSampleTime));
			fpsMonitorData += " 2:" + futil::TrimLeadingZeroes(std::to_string(fpsMonitor->fields.m_currentMaxFrameTime));
			fpsMonitorData += " 3:" + futil::TrimLeadingZeroes(std::to_string(fpsMonitor->fields.m_currentMinFrameTime));
			fpsMonitorData += " 4:" + futil::TrimLeadingZeroes(std::to_string(fpsMonitor->fields.m_frameTime));
			fpsMonitorData += " 5:" + futil::TrimLeadingZeroes(std::to_string(fpsMonitor->fields.AverageFPS));
			fpsMonitorData += " 6:" + futil::TrimLeadingZeroes(std::to_string(fpsMonitor->fields.MinimumFPS));
			fpsMonitorData += " 7:" + futil::TrimLeadingZeroes(std::to_string(fpsMonitor->fields.MaximumFPS));
			fpsMonitorData += " 8:" + futil::TrimLeadingZeroes(std::to_string(fpsMonitor->fields.AverageFrameTime));
			fpsMonitorData += " 9:" + futil::TrimLeadingZeroes(std::to_string(fpsMonitor->fields.MinFrameTime));
			fpsMonitorData += " 10:" + futil::TrimLeadingZeroes(std::to_string(fpsMonitor->fields.MaxFrameTime));
			fpsMonitorData += " 11:" + futil::TrimLeadingZeroes(std::to_string(fpsMonitor->fields.m_deltaTimeAverage));
			fpsMonitorData += " 12:" + futil::TrimLeadingZeroes(std::to_string(fpsMonitor->fields.m_hitchDeltaTimeAverage));
			fpsMonitorData += " 13:" + futil::TrimLeadingZeroes(std::to_string(fpsMonitor->fields.m_slowDownDeltaTimeAverage));
			fpsMonitorData += " 14:" + futil::TrimLeadingZeroes(std::to_string(fpsMonitor->fields.m_hitchCount));
			fpsMonitorData += " 15:" + futil::TrimLeadingZeroes(std::to_string(fpsMonitor->fields.m_slowdownCount));
			fpsMonitorData += " 16:" + futil::TrimLeadingZeroes(std::to_string(fpsMonitor->fields.m_frameCount));
			fpsMonitorData += " 17:" + futil::TrimLeadingZeroes(std::to_string(fpsMonitor->fields.m_badFrameCount)) + "|";
		}

		return fpsMonitorData;
	}

	std::string GetSeinStatesData()
	{
		std::string seinStatesData = "";

		if (sein != nullptr)
		{
			app::SeinAbilities* seinAbilities = sein->fields.Abilities;

			if (seinAbilities != nullptr)
			{
				if (seinAbilities->fields.BashWrapper->fields.HasState == true)
				{
					app::SeinBashAttack* bashAttack = seinAbilities->fields.BashWrapper->fields.State;
					seinStatesData += "0:" + std::to_string(bashAttack->fields.IsBashing);
					seinStatesData += " 1:" + futil::TrimLeadingZeroes(std::to_string(bashAttack->fields.m_holdAirTime));
					seinStatesData += " 2:" + futil::TrimLeadingZeroes(std::to_string(bashAttack->fields.m_frictionTimeRemaining)) + "|";
				}

				if (seinAbilities->fields.BowWrapper->fields.HasState == true)
				{
					app::SeinBowAttack* bowAttack = seinAbilities->fields.BowWrapper->fields.State;
					seinStatesData += "0:" + futil::TrimLeadingZeroes(std::to_string(bowAttack->fields.AimDuration));
					seinStatesData += " 1:" + futil::TrimLeadingZeroes(std::to_string(bowAttack->fields.AimDurationCritical));
					seinStatesData += " 2:" + futil::TrimLeadingZeroes(std::to_string(bowAttack->fields.m_currentStateTime));
					seinStatesData += " 3:" + futil::TrimLeadingZeroes(std::to_string(bowAttack->fields.m_chargeAmount));
					seinStatesData += " 4:" + std::to_string(SeinBowAttack_get_IsAiming(bowAttack, NULL)) + "|";
				}

				if (seinAbilities->fields.DoubleJumpWrapper->fields.HasState == true)
				{
					app::SeinDoubleJump* doubleJump = seinAbilities->fields.DoubleJumpWrapper->fields.State;
					seinStatesData += "0:" + futil::TrimLeadingZeroes(std::to_string(doubleJump->fields.m_doubleJumpTime));
					seinStatesData += " 1:" + std::to_string(doubleJump->fields.m_numberOfJumpsAvailable);
					seinStatesData += " 2:" + futil::TrimLeadingZeroes(std::to_string(doubleJump->fields.m_remainingLockTime));
					seinStatesData += " 3:" + std::to_string(doubleJump->fields.m_isDoubleJumping) + "|";
				}

				if (seinAbilities->fields.GlideWrapper->fields.HasState == true)
				{
					app::SeinGlide* glide = seinAbilities->fields.GlideWrapper->fields.State;
				}

				if (seinAbilities->fields.JumpWrapper->fields.HasState == true)
				{
					app::SeinJump* jump = seinAbilities->fields.JumpWrapper->fields.State;
				}

				if (seinAbilities->fields.SpiritSpearWrapper->fields.HasState == true)
				{
					app::SeinSpiritSpearSpell* spiritSpear = seinAbilities->fields.SpiritSpearWrapper->fields.State;
				}

				if (seinAbilities->fields.WallJumpWrapper->fields.HasState == true)
				{
					app::SeinWallJump* wallJump = seinAbilities->fields.WallJumpWrapper->fields.State;
				}
			}

			app::CharacterPlatformMovement* platformMovement = sein->fields.PlatformBehaviour->fields.PlatformMovement;

			if (platformMovement != nullptr)
			{
				platformMovement->fields.AdditiveLocalSpeed;
				platformMovement->fields.AdditiveSpeed;
				platformMovement->fields.m_prevWorldSpeed;
			}
		}

		return seinStatesData;
	}

	void DisplayData(tem::Vector3 position)
	{
		//change to FpsGraph?
		DataIsDisplayed = true;


		std::vector<std::vector<float>> floatData;
		floatData.resize(6);

		for (int i = 0; i < AllFrames.size(); i++)
		{
			floatData[0].push_back((float)AllFrames[i].fpsMonitorData.MaximumFPS);
			floatData[1].push_back((float)AllFrames[i].fpsMonitorData.MinimumFPS);
			floatData[2].push_back((float)AllFrames[i].fpsMonitorData.AverageFPS);
			floatData[3].push_back(std::fabs(AllFrames[i].seinPlatformMovement.PrevWorldSpeed.x));
			floatData[4].push_back(11.666666f);
			floatData[5].push_back(AllFrames[i].seinPlatformMovement.CurrentSpeed.x);
		}
		graphDrawer.StartDrawing();

		//Graph.DrawFloats(floatData[0], graphColors.Red, 2, 1);
		//Graph.DrawFloats(floatData[1], graphColors.Green, 2, 1);
		//Graph.DrawFloats(floatData[2], graphColors.Blue, 2, 1);
		graphDrawer.AddFloatData(floatData[3], graphColors.Blue, 2, 1);
		graphDrawer.AddFloatData(floatData[4], graphColors.Orange, 2, 1);
		graphDrawer.AddFloatData(floatData[5], graphColors.Green, 2, 1);
		graphDrawer.AddGraphLabel("Previous World Speed", 16, graphColors.Blue, 0);
		graphDrawer.AddGraphLabel("Base Sein Speed", 16, graphColors.Orange, 1);
		graphDrawer.AddGraphLabel("Calculated Speed", 16, graphColors.Green, 2);
	}

	void CleanUpData()
	{
		Graph::Instance->CloseGraph();
		ResetData();
	}

	void CleanUp()
	{
		droppedFrameMonitor = nullptr;
		fpsMonitor = nullptr;
		sein = nullptr;
		nanoProfiler = nullptr;

		Graph::CleanUpStatic();
	}
};

#endif