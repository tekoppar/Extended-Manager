#pragma once

#ifndef _DEBUGDRAWER_H
#define _DEBUGDRAWER_H

#include "Tem.h"

class DebugDrawer : public Global
{
public:
	static DebugDrawer Instance;
	app::GameObject* masterDebug = nullptr;
	bool toggleDebugObjects = true;
	app::Texture2D* debugTexture = nullptr;
	app::Material* debugMaterial = nullptr;
	bool HasCreatedResources = false;
	std::vector<app::GameObject*> debugObjects = std::vector<app::GameObject*>();

	virtual void Update() override;
	virtual void Cleanup() override;

	DebugDrawer();
	void Initialize();
	void ToggleDebugObjects();
	void SetupTexture(app::Color color, tem::Vector3 position);
	static app::GameObject* CreateDebugObjectStatic(app::Color color, tem::Vector3 position);
	app::GameObject* CreateDebugObject(app::Color color, tem::Vector3 position, tem::Vector3 scale = tem::Vector3(3.0f, 15.0f, 1.0f));
	app::GameObject* CreateDebugObjectDetached(app::Color color, tem::Vector2 position, tem::Vector2 scale);
};

#endif