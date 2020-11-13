#pragma once

#ifndef _AREAMAPMANAGER_H
#define _AREAMAPMANAGER_H


class AreaMapManager
{
public:
	std::vector<app::GameObject*> AllAreaIcons;
	std::vector<int> AllAreaIconsIndex;

	app::GameObject* CreateNewIconPlayerIcon(tem::Vector3 position, app::Color color);
	void UpdateIconPosition(app::GameObject* object, tem::Vector3 position);
};

#endif