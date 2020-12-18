#pragma once

#include <algorithm>
#include <vector>
#include <future> 

#ifndef _MESSAGECLASS_H
#define _MESSAGECLASS_H

#include "ManagerDef.h"

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
	NextAnimation = 11,
	GetShriekData = 12,
	CreateRaceCheckpoint = 13,
	RunRace = 14,
	RemoveCheckpoint = 15,
	LoadRace = 16,
	KuDash = 17,
	UpdateRaceCheckpoint = 18,
	SetManagerPath = 19,
	ToggleDebugObjects = 20,
	GetSeinFaces = 21,
	UpdateHitbox = 22,
	RemoveHitbox = 23,
	RestartRace = 24,
	StopRace = 25,
	SaveUberStates = 26,
	LoadUberStates = 27,
	SetSeinPosition = 28,
	CreateBackupSave = 29,
	GetSaveInfo = 30,
	RefreshBackups = 31,
	SetOriVisuals = 32,
	SetTransform = 33,
	GetTransform = 34
};

class Message {
public:
	MessageType Type = MessageType::GameCompletion;
	int TypeInt = 1;
	long long Timeout = 5000;
	std::string Content = "";
};

class MessageManager {
public:
	//std::vector<Message> Messages;
	//std::vector<int> CurrentMessagesType;
	//std::vector<Message> NextMessages;
	//std::vector<int> NextMessagesType;
	std::unordered_map<MessageType, Message> Messages;
	std::unordered_map<MessageType, Message> NextMessages;
	std::unordered_map<MessageType, std::future<bool>> MessagesFutures;

	void AddMessage(Message message)
	{
		PullTemp();
		//sutil::Append(ManagerPath + "message_error_dll.log", "DLL:" + message.Content + " - " + std::to_string(message.TypeInt) + "\n");

		if (IsPulling == true)
		{
			if (this->Temp.find(message.Type) == this->Temp.end())
			{
				this->Temp[message.Type] = message;
			}
		}
		else
		{
			if (this->NextMessages.find(message.Type) == this->NextMessages.end())
			{
				this->NextMessages[message.Type] = message;
			}
		}
	}

	void PullMessages()
	{
		PullTemp();

		IsPulling = true;
		std::unordered_map<MessageType, Message> temp;
		for (auto& message : this->NextMessages)
		{
			if (this->Messages.find(message.second.Type) == this->Messages.end())
			{
				this->Messages[message.second.Type] = message.second;
			}
			else
				temp[message.second.Type] = message.second;
		}
		this->NextMessages = temp;
		IsPulling = false;
	}

	std::unordered_map<MessageType, Message> GetMessages()
	{
		return this->Messages;
	}

	void RemoveMessage(MessageType type)
	{
		if (this->Messages.find(type) != this->Messages.end())
			this->Messages.erase(type);
		
		if (this->MessagesFutures.find(type) != this->MessagesFutures.end())
			this->MessagesFutures.erase(type);
	}

	void SetTimeout(int64_t value, MessageType type)
	{
		if (this->Messages.find(type) != this->Messages.end())
			this->Messages[type].Timeout = value;
	}

	void DecrementTimeout(int64_t value, MessageType type)
	{
		if (this->Messages.find(type) != this->Messages.end())
			this->Messages[type].Timeout -= value;
	}

private:
	std::unordered_map<MessageType, Message> Temp;
	bool IsPulling = false;

	void PullTemp()
	{
		std::unordered_map<MessageType, Message> temp;
		if (Temp.size() > 0)
		{
			for (auto& tMessage : Temp)
			{
				if (this->NextMessages.find(tMessage.second.Type) == this->NextMessages.end())
				{
					this->NextMessages[tMessage.second.Type] = tMessage.second;
				}
				else
					temp[tMessage.second.Type] = tMessage.second;
			}
		}
		Temp = temp;
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

#endif