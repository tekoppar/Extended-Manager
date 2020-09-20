#pragma once

enum class MessageType 
{
	EndThread = 0,
	GameCompletion = 1,
	CreateCheckpoint = 2,
	CreateObject = 3,
	StopRecorder = 4,
	WriteRecorder = 5,
	GhostPlayerRun = 6,
	GhostPlayerStop = 7,
	GetQuestByName = 8,
	FrameStep = 9,
	FrameStepStop = 10
};

class Message {
public:
	MessageType Type = MessageType::GameCompletion;
};

enum class FrameStepping
{
	FrameSteppingDisabled = 0,
	FrameSteppingEnabled = 1,
	IsAutoFrameStepping = 2
};

class FrameStep
{
public:
	FrameStepping State = FrameStepping::FrameSteppingDisabled;
	bool ShouldFrameStep = false;
};