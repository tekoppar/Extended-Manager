#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <filesystem>
#include <future>
#include <chrono>

#include "StringUtils.h"
#include "ManagerDef.h"
#include "MessageHelper.h"
#include "GraphDrawer.h"
#include "FrameLoggerSingleFrame.h"

#include "FrameLogger.h"

std::vector<std::future<FrameLoggerFrames>> FrameLogger::WaitingOnData = std::vector<std::future<FrameLoggerFrames>>();
const std::chrono::milliseconds span(1);

void FrameLogger::Update()
{
	for (int i = 0; i < FrameLogger::WaitingOnData.size(); i++)
	{
		if (FrameLogger::WaitingOnData[i].valid() == false)
		{
			FrameLogger::WaitingOnData.erase(FrameLogger::WaitingOnData.begin() + i);
			continue;
		}

		if (FrameLogger::WaitingOnData[i].wait_for(span) != std::future_status::ready)
		{
			continue;
		}
		else
		{
			auto value = FrameLogger::WaitingOnData[i].get();

			if (value.Name == "topscore")
				FrameLogger::AllFramesTop = value.Frames;

			if (value.Name == "lastattempt")
				FrameLogger::AllFramesLast = value.Frames;

			FrameLogger::WaitingOnData.erase(FrameLogger::WaitingOnData.begin() + i);
		}
	}

	if (ShouldDisplayData == true && FrameLogger::WaitingOnData.size() == 0)
	{
		DisplayData();
		ShouldDisplayData = false;
	}
}

void FrameLogger::Initialize()
{
	droppedFrameMonitor = GetObjectByType<app::DroppedFrameMonitor>("", "DroppedFrameMonitor");
	fpsMonitor = GetObjectByType<app::FPSMonitor>("", "FPSMonitor");

	if (droppedFrameMonitor == nullptr && fpsMonitor != nullptr && fpsMonitor->fields.m_DroppedFrameMonitor != nullptr)
		droppedFrameMonitor = fpsMonitor->fields.m_DroppedFrameMonitor;

	std::string topPath = filePath;
	sutil::ReplaceS(topPath, ".framedata", ".topscore.frames");
	FrameLogger::WaitingOnData.push_back(std::async(FrameLogger::LoadFrames, topPath, "topscore"));
	std::string lastPath = filePath;
	sutil::ReplaceS(lastPath, ".framedata", ".frames");
	FrameLogger::WaitingOnData.push_back(std::async(FrameLogger::LoadFrames, lastPath, "lastattempt"));
}

FrameLoggerFrames FrameLogger::LoadFrames(std::string path, std::string name)
{
	auto content = sutil::ReadFileByLine(path);
	FrameLoggerFrames frame = FrameLoggerFrames();
	frame.Frames.reserve(content.size());
	frame.Name = name;

	for (auto& s : content)
	{
		if (s != "")
			frame.Frames.push_back(FrameLoggerSingleFrame(s));
	}

	return frame;
}

void FrameLogger::LoadLastData(std::string path)
{
	auto content = sutil::ReadFileByLine(path);
	AllFramesLast.reserve(content.size());

	for (auto& s : content)
	{
		if (s != "")
			AllFramesLast.push_back(FrameLoggerSingleFrame(s));
	}
}

void FrameLogger::ResetData()
{
	if (fpsMonitor != nullptr)
		app::FPSMonitor_Reset(fpsMonitor, NULL);

	FrameData = std::vector<std::string>();

	if (AllFrames.size() > 0)
		AllFramesLast = AllFrames;
	AllFrames = std::vector<FrameLoggerSingleFrame>();
}

void FrameLogger::LogFrameData(std::string filePath)
{
	std::string log = "";
	for (auto& singleFrame : AllFrames)
	{
		log += singleFrame.ToString();
	}

	sutil::Write(filePath, log + "\n");
}

void FrameLogger::LoggFrame()
{
	std::string frameData = "";
	frameData += GetDroppedFrameData();
	frameData += GetFPSMonitorData();
	frameData += GetSeinStatesData();
	FrameLoggerSingleFrame singleFrame = FrameLoggerSingleFrame();
	singleFrame.droppedFrameData = DroppedFrameData(droppedFrameMonitor);
	singleFrame.fpsMonitorData = FPSMonitorData(fpsMonitor);
	singleFrame.seinPlatformMovement = SeinPlatformMovementData(MDV::MoonSein->fields.PlatformBehaviour->fields.PlatformMovement);

	app::Vector3 currentPosition = app::SeinCharacter_get_Position(MDV::MoonSein, NULL);
	app::Vector3 previousPosition = app::SeinCharacter_get_PreviousPosition(MDV::MoonSein, NULL);

	singleFrame.seinPlatformMovement.CurrentSpeed.x = std::fabs((previousPosition.x - currentPosition.x) * singleFrame.fpsMonitorData.AverageFPS);
	singleFrame.seinPlatformMovement.CurrentSpeed.y = std::fabs((previousPosition.y - currentPosition.y) * singleFrame.fpsMonitorData.AverageFPS);

	AllFrames.push_back(singleFrame);
	FrameData.push_back(frameData);
	//sutil::Append(filePath, frameData + "\n");
}

std::string FrameLogger::GetDroppedFrameData()
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

std::string FrameLogger::GetFPSMonitorData()
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

std::string FrameLogger::GetSeinStatesData()
{
	std::string seinStatesData = "";

	if (MDV::MoonSein != nullptr)
	{
		app::SeinAbilities* seinAbilities = MDV::MoonSein->fields.Abilities;

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
				seinStatesData += " 4:" + std::to_string(app::SeinBowAttack_get_IsAiming(bowAttack, NULL)) + "|";
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

		app::CharacterPlatformMovement* platformMovement = MDV::MoonSein->fields.PlatformBehaviour->fields.PlatformMovement;

		if (platformMovement != nullptr)
		{
			platformMovement->fields.AdditiveLocalSpeed;
			platformMovement->fields.AdditiveSpeed;
			platformMovement->fields.m_prevWorldSpeed;
		}
	}

	return seinStatesData;
}

void FrameLogger::DisplayDataPublic()
{
	ShouldDisplayData = true;
	Update();
}

void FrameLogger::DisplayData()
{
	DataIsDisplayed = true;

	graphDrawer.Initialize(static_cast<int>(AllFrames.size()));
	Graph::Instance = &graphDrawer;
	graphDrawer.SeinCharacter = MDV::MoonSein;

	std::vector<std::vector<float>> floatData;
	floatData.resize(9);

	for (int i = 0; i < AllFrames.size(); i++)
	{
		floatData[0].push_back((float)AllFrames[i].fpsMonitorData.MaximumFPS);
		floatData[1].push_back((float)AllFrames[i].fpsMonitorData.MinimumFPS);
		floatData[2].push_back((float)AllFrames[i].fpsMonitorData.AverageFPS);
		floatData[3].push_back(std::fabs(AllFrames[i].seinPlatformMovement.PrevWorldSpeed.x));
		floatData[4].push_back(11.666666f);
		floatData[5].push_back(AllFrames[i].seinPlatformMovement.CurrentSpeed.x + AllFrames[i].seinPlatformMovement.CurrentSpeed.y);

		if (AllFramesTop.size() > i)
			floatData[6].push_back(AllFramesTop[i].seinPlatformMovement.CurrentSpeed.x + AllFramesTop[i].seinPlatformMovement.CurrentSpeed.y);

		if (AllFramesLast.size() > i)
			floatData[7].push_back(AllFramesLast[i].seinPlatformMovement.CurrentSpeed.x + AllFramesLast[i].seinPlatformMovement.CurrentSpeed.y);
	}
	graphDrawer.StartDrawing(static_cast<int>(AllFrames.size()));

	//Graph.DrawFloats(floatData[0], GraphColors::Red, 2, 1);
	//Graph.DrawFloats(floatData[1], GraphColors::Green, 2, 1);
	//Graph.DrawFloats(floatData[2], GraphColors::Blue, 2, 1);
	graphDrawer.AddFloatData(floatData[5], GraphColors::Orange, 1, 1);

	if (floatData[6].size() > 0)
		graphDrawer.AddFloatData(floatData[6], GraphColors::Green, 1, 1);

	if (floatData[7].size() > 0)
		graphDrawer.AddFloatData(floatData[7], GraphColors::Pink, 1, 1);

	graphDrawer.AddGraphLabel("Calculated Speed", 16, GraphColors::Orange, 0);

	if (floatData[6].size() > 0)
		graphDrawer.AddGraphLabel("Calculated Speed Top Ghost", 16, GraphColors::Green, 1);

	if (floatData[7].size() > 0)
		graphDrawer.AddGraphLabel("Calculated Speed Last Attempt", 16, GraphColors::Pink, 2);

	app::SeinController_set_IsSuspended(MDV::MoonSein->fields.Controller, true, NULL);
	app::CharacterPlatformMovement_set_IsSuspended(MDV::MoonSein->fields.PlatformBehaviour->fields.PlatformMovement, true, NULL);
}

void FrameLogger::CleanUpData()
{
	if (Graph::Instance != nullptr)
		Graph::Instance->CloseGraph();

	ResetData();
}

void FrameLogger::Cleanup()
{
	droppedFrameMonitor = nullptr;
	fpsMonitor = nullptr;
	nanoProfiler = nullptr;

	Graph::CleanUpStatic();
}