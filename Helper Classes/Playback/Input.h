#pragma once

class Input
{
public:
	tem::KeyCode InputCode;
	int StartFrame = 0;
	int Length = 0;
	int WaitAfter = 0;
	int WaitBefore = 0;
	bool KeyUp = false;

	Input(tem::KeyCode input, int startFrame, int length, int waitAfter = 0, bool keyUp = false);
};