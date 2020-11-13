#pragma once

#include "Tem.h"

class MessageHelper
{
public:
	static void ButtonAClicked();
	static app::MessageControllerB* MessageControllerB;
	static app::GameObject* CreateMessagebox(std::string text = "", tem::Vector3 position = tem::Vector3(0,0,0), float duration = 10.0f);
	static app::GameObject* CreateMessageboxNoBackground(std::string text = "", tem::Vector3 position = tem::Vector3(0, 0, 0), float duration = 10.0f);
	static app::NPCMessageBox* CreateNPCInteractionBox(std::string text = "", tem::Vector3 position = tem::Vector3(0, 0, 0), float duration = 10.0f);
	static void SetMessage(app::GameObject* messageBox, std::string text = "", float textSize = 16.0f, app::Color* color = nullptr);
};