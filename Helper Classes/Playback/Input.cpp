#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <vector>

#include "StringUtils.h"
#include "ManagerDef.h"
#include "MessageHelper.h"
#include "Global.h"

#include "Input.h"

Input::Input(tem::KeyCode input, int startFrame, int length, int waitAfter, bool keyUp)
{
	this->InputCode = input;
	this->StartFrame = startFrame;
	this->Length = length;
	this->WaitAfter = waitAfter;
	this->KeyUp = keyUp;
}