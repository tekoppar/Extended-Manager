#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <future>
#include <chrono>

#include "StringUtils.h"
#include "ManagerDef.h"
#include "MessageHelper.h"
#include "GraphDrawer.h"

#include "FrameLoggerSingleFrame.h"

DroppedFrameData::DroppedFrameData(app::DroppedFrameMonitor* data)
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

DroppedFrameData::DroppedFrameData(std::string content)
{
	auto splitContent = sutil::SplitTem(content, " ");
	std::vector<int> dataContent;
	std::string value = "";

	for (auto& s : splitContent)
	{
		//auto ss = sutil::SplitTem(s, ":");
		//value = s.substr(s.find(":") + 1, std::string::npos);
		dataContent.push_back(std::stoi(s.substr(s.find(":") + 1, std::string::npos)));
	}

	DangerFrames = dataContent[0];
	DroppedFramesSingle = dataContent[1];
	DroppedFramesDouble = dataContent[2];
	DroppedFramesTriple = dataContent[3];
	DroppedFramesMultiple = dataContent[4];
}

std::string DroppedFrameData::ToString()
{
	return "0:" + std::to_string(DangerFrames) + " 1:" + std::to_string(DroppedFramesSingle) +
		" 2:" + std::to_string(DroppedFramesDouble) + " 3:" + std::to_string(DroppedFramesTriple) +
		" 4:" + std::to_string(DroppedFramesMultiple);
}

FPSMonitorData::FPSMonitorData(app::FPSMonitor* data)
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

FPSMonitorData::FPSMonitorData(std::string content)
{
	auto splitContent = sutil::SplitTem(content, " ");
	std::vector<float> dataContent(20);
	std::fill(dataContent.begin(), dataContent.end(), 0.0f);
	std::string value = "";

	for (auto& s : splitContent)
	{
		//split = sutil::SplitTem(s, ":");
		//value = s.substr(s.find(":") + 1, std::string::npos);
		dataContent.push_back(std::stof(s.substr(s.find(":") + 1, std::string::npos)));
	}

	RenderedFrames = dataContent[0];
	CurrentSampleTime = dataContent[1];
	CurrentMaxFrameTime = dataContent[2];
	CurrentMinFrameTime = dataContent[3];
	FrameTime = dataContent[4];
	AverageFPS = (int)dataContent[5];
	MinimumFPS = (int)dataContent[6];
	MaximumFPS = (int)dataContent[7];
	AverageFrameTime = dataContent[8];
	MinFrameTime = dataContent[9];
	MaxFrameTime = dataContent[10];
	DeltaTimeAverage = dataContent[11];
	HitchDeltaTimeAverage = dataContent[12];
	SlowDownDeltaTimeAverage = dataContent[13];
	HitchCount = (int)dataContent[14];
	SlowdownCount = (int)dataContent[15];
	FrameCount = (int)dataContent[16];
	BadFrameCount = (int)dataContent[17];
	FrameIndex = (int)dataContent[18];
}

std::string FPSMonitorData::ToString()
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

SeinPlatformMovementData::SeinPlatformMovementData(app::CharacterPlatformMovement* platform)
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

SeinPlatformMovementData::SeinPlatformMovementData(std::string content)
{
	auto splitContent = sutil::SplitTem(content, " ");
	std::vector<app::Vector2> dataContent;
	std::string value = "";
	app::Vector2 tempVector;

	for (auto& s : splitContent)
	{
		//auto ss = sutil::SplitTem(s, ":");
		value = s.substr(s.find(":") + 1, std::string::npos);
		//auto sss = sutil::SplitTem(ss[1], ";");

		tempVector.x = std::stof(value.substr(0, value.find(";")));
		tempVector.y = std::stof(value.substr(value.find(";") + 1, std::string::npos));

		dataContent.push_back(tempVector);
	}

	AdditiveLocalSpeed = dataContent[0];
	AdditiveSpeed = dataContent[1];
	PrevWorldSpeed = dataContent[2];
	CurrentSpeed = dataContent[3];
}

std::string SeinPlatformMovementData::ToString()
{
	return "0:" + futil::TrimLeadingZeroes(std::to_string(AdditiveLocalSpeed.x)) + ";" + futil::TrimLeadingZeroes(std::to_string(AdditiveLocalSpeed.y)) +
		" 1:" + futil::TrimLeadingZeroes(std::to_string(AdditiveSpeed.x)) + ";" + futil::TrimLeadingZeroes(std::to_string(AdditiveSpeed.y)) +
		" 2:" + futil::TrimLeadingZeroes(std::to_string(PrevWorldSpeed.x)) + ";" + futil::TrimLeadingZeroes(std::to_string(PrevWorldSpeed.y)) +
		" 3:" + futil::TrimLeadingZeroes(std::to_string(CurrentSpeed.x)) + ";" + futil::TrimLeadingZeroes(std::to_string(CurrentSpeed.y));
}

FrameLoggerSingleFrame::FrameLoggerSingleFrame() {}

FrameLoggerSingleFrame::FrameLoggerSingleFrame(std::string content)
{
	auto splitContent = sutil::SplitTem(content, "|");

	droppedFrameData = DroppedFrameData(splitContent[0]);
	fpsMonitorData = FPSMonitorData(splitContent[1]);
	seinPlatformMovement = SeinPlatformMovementData(splitContent[2]);
}

std::string FrameLoggerSingleFrame::ToString()
{
	std::string frame = "";
	frame += droppedFrameData.ToString() + "|";
	frame += fpsMonitorData.ToString() + "|";
	frame += seinPlatformMovement.ToString() + "\n";

	return frame;
}