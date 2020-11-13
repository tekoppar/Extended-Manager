#pragma once

#ifndef _CREATEUI_H
#define _CREATEUI_H

class DrawUI {
public:
	static std::vector<app::Texture2D*> AllTexture2D;
	static std::vector<std::string> AllTexture2DNames;

	static int FindTextureIndex(std::string name);
	static app::GameObject* EventSystem(const std::string& name);
	static app::GameObject* Image(const std::string& name, app::Material* material);
	static app::GameObject* Button(const std::string& name);
	static app::Button* Button(app::GameObject* object, const std::string& text, int fontSize, app::Color color);
	static app::GameObject* VerticalLayoutGroup(const std::string& name, app::TextAnchor__Enum textAnchor = app::TextAnchor__Enum::TextAnchor__Enum_UpperLeft);
	static app::GameObject* HorizontalLayoutGroup(const std::string& name, app::TextAnchor__Enum textAnchor = app::TextAnchor__Enum::TextAnchor__Enum_UpperLeft);
	static app::GameObject* RectMask2D(const std::string& name, float minWidth = 10, float minHeight = 10, float preferedWidth = 100, float preferedHeight = 100);
	static app::GameObject* Text(const std::string& name, const std::string& text, int fontSize, app::Color color);
	static app::GameObject* Scrollbar(app::GameObject* rectHandle, const std::string& name, app::Color color, app::Color colorHandle, bool horizontal = true);
	static app::GameObject* Dropdown(const std::string& name);
};

#endif