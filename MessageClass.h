#pragma once

#include <algorithm>
#include <vector>

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
	FrameStepStop = 10,
	NextAnimation = 11
};

class Message {
public:
	MessageType Type = MessageType::GameCompletion;
	int TypeInt;
};

class MessageManager {
public:
	std::vector<Message> Messages;
	std::vector<int> CurrentMessagesType;

	void AddMessage(Message message)
	{
		if (this->CurrentMessagesType.size()) {
			auto it = std::find(this->CurrentMessagesType.begin(), this->CurrentMessagesType.end(), message.TypeInt);
			if (it == this->CurrentMessagesType.end()) {
				this->Messages.push_back(message);
				this->CurrentMessagesType.push_back(message.TypeInt);
			}
		}
		else {
			this->Messages.push_back(message);
			this->CurrentMessagesType.push_back(message.TypeInt);
		}
	}
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