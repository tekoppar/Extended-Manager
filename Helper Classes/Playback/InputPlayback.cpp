#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <vector>
#include <filesystem>

#include "StringUtils.h"
#include "ManagerDef.h"
#include "MessageHelper.h"
#include "Global.h"

#include "Input.h"

#include "InputPlayback.h"

InputPlayback InputPlayback::_Instance;

void InputPlayback::Update()
{
	if (this->StartPlayback == true && this->FinishedPlayback == false && this->GeneratedInputs.size() > 0)
	{
		this->Playback();
		this->Frame++;
	}
}

void InputPlayback::Cleanup()
{
	this->Reset();
}

void InputPlayback::Playback()
{
	Input input = this->GeneratedInputs[this->InputIndex];

	if (input.StartFrame == this->Frame)
	{
		INPUT inputs[1] = {};
		ZeroMemory(inputs, sizeof(inputs));

		if (input.KeyUp == false)
		{
			if (input.InputCode == tem::KeyCode::LMOUSE || input.InputCode == tem::KeyCode::RMOUSE)
			{
				inputs[0].type = INPUT_MOUSE;

				switch (input.InputCode) {
					case tem::KeyCode::LMOUSE: inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN; break;
					case tem::KeyCode::RMOUSE: inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN; break;
				}
			}
			else
			{
				inputs[0].type = INPUT_KEYBOARD;
				inputs[0].ki.wVk = (int)input.InputCode;
			}
		}
		else if (input.KeyUp == true)
		{
			if (input.InputCode == tem::KeyCode::LMOUSE || input.InputCode == tem::KeyCode::RMOUSE)
			{
				inputs[0].type = INPUT_MOUSE;

				switch (input.InputCode) {
					case tem::KeyCode::LMOUSE: inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTUP; break;
					case tem::KeyCode::RMOUSE: inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTUP; break;
				}
			}
			else
			{
				inputs[0].type = INPUT_KEYBOARD;
				inputs[0].ki.wVk = (int)input.InputCode;
				inputs[0].ki.dwFlags = KEYEVENTF_KEYUP;
			}
		}

		UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
		this->InputIndex++;

		if (this->InputIndex >= this->GeneratedInputs.size())
		{
			this->FinishedPlayback = true;
		}
	}
}

void InputPlayback::GenerateInputs()
{
	int currentFrame = 0;
	for (int i = 0; i < this->Inputs.size(); ++i)
	{
		currentFrame += this->Inputs[i].WaitBefore;
		currentFrame += this->Inputs[i].StartFrame;
		this->GeneratedInputs.push_back(Input(this->Inputs[i].InputCode, currentFrame, 0));
		currentFrame += this->Inputs[i].Length;
		this->GeneratedInputs.push_back(Input(this->Inputs[i].InputCode, currentFrame, 0, 0, true));
		currentFrame += this->Inputs[i].WaitAfter;
	}
}

void InputPlayback::AddInput(Input input)
{
	if (this->StartPlayback == false)
	{
		this->Inputs.push_back(input);
	}
}

void InputPlayback::Reset()
{
	this->Frame = 0;
	this->GeneratedInputs.clear();
	this->InputIndex = 0;
	this->Inputs.clear();
	this->StartPlayback = false;
	this->FinishedPlayback = false;
}

bool InputPlayback::ReadPlaybackFile()
{
	std::string path = "\\playbackInputs.txt";
	if (path != "" && std::filesystem::exists(ManagerPath + path) == true && std::filesystem::is_regular_file(ManagerPath + path) == true)
	{
		std::vector<std::string> lines = sutil::ReadFileByLine(ManagerPath + path);

		for (std::string &line : lines)
		{
			if (line != "")
			{
				std::vector<std::string> values = sutil::SplitTem(line, ";");

				if (values.size() == 4)
				{
					tem::KeyCode keyCode = (tem::KeyCode)std::atoi(values[0].c_str());
					int startFrame = std::atoi(values[1].c_str());
					int length = std::atoi(values[2].c_str());
					int waitAfter = std::atoi(values[3].c_str());

					this->Inputs.push_back(Input(keyCode, startFrame, length, waitAfter));
				}
			}
		}

		return true;
	}
	else
	{
		return false;
	}
}