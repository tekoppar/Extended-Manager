#pragma once

#ifndef _FRAMELOGGER_H
#define _FRAMELOGGER_H

#include <future>
#include "Global.h"
#include "FrameLoggerSingleFrame.h"

class FrameLogger : public Global {
public:
	static std::vector<std::future<FrameLoggerFrames>> WaitingOnData;

	app::DroppedFrameMonitor* droppedFrameMonitor = nullptr;
	app::FPSMonitor* fpsMonitor = nullptr;
	app::NanoProfiler* nanoProfiler = nullptr;
	app::Vector3 oldSeinPosition = app::Vector3();

	bool ShouldDisplayData = false;
	bool DataIsDisplayed = false;

	std::string filePath = "";
	std::vector<std::string> FrameData;
	std::vector<FrameLoggerSingleFrame> AllFrames;
	std::vector<FrameLoggerSingleFrame> AllFramesTop;
	std::vector<FrameLoggerSingleFrame> AllFramesLast;

	virtual void Update() override;
	static FrameLoggerFrames LoadFrames(std::string path, std::string name);
	void LoadLastData(std::string path);
	void ResetData();
	void LogFrameData(std::string filePath);
	void LoggFrame();
	std::string GetDroppedFrameData();
	std::string GetFPSMonitorData();
	std::string GetSeinStatesData();
	void DisplayDataPublic();
	void CleanUpData();
	void CleanUp();
	void Initialize();

private:
	void DisplayData();
};

#endif