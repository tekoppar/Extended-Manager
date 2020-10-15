#pragma once

#ifndef _DEBUGDRAWER_H
#define _DEBUGDRAWER_H

#include "../HelperClasses.h"

class DebugDrawer {
public:
	app::Texture2D* debugTexture = nullptr;
	app::Material* debugMaterial = nullptr;
	std::vector<app::GameObject*> debugObjects;

	void SetupTexture(app::Color color, tem::Vector3 position);
	static app::GameObject* CreateDebugObject(app::Color color, tem::Vector3 position);
	void CleanUp();
};

#endif