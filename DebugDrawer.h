#pragma once

#ifndef _DEBUGDRAWER_H
#define _DEBUGDRAWER_H

#include "../HelperClasses.h"

class DebugDrawer {
public:
	static app::GameObject* masterDebug;
	static bool toggleDebugObjects;

	app::Texture2D* debugTexture = nullptr;
	app::Material* debugMaterial = nullptr;
	std::vector<app::GameObject*> debugObjects;

	DebugDrawer();
	static void Initialize();
	static void ToggleDebugObjects();
	void SetupTexture(app::Color color, tem::Vector3 position);
	static app::GameObject* CreateDebugObjectStatic(app::Color color, tem::Vector3 position);
	app::GameObject* CreateDebugObject(app::Color color, tem::Vector3 position);
	void CleanUp();
};

#endif