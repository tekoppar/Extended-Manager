#pragma once

#include "Tem.h"
#include "SeinVisuals/BowVisual.h"
#include "SeinVisuals/GlideVisual.h"
#include "SeinVisuals/TorchVisual.h"
#include "SeinVisuals/SeinVisual.h"
#include "SeinVisuals/HammerVisual.h"
#include "SeinVisuals/SwordVisual.h"
#include "SeinVisuals/OriVisual.h"
#include "json.hpp"

class VisualSettingsUpdated
{
public:
	bool HasUpdatedOri = false;
	bool HasUpdatedTorch = false;
	bool HasUpdatedGlide = false;
	bool HasUpdatedBow = false;
	bool HasUpdatedGoldenSein = false;
	bool HasUpdatedHammer = false;
	bool HasUpdatedSword = false;
	bool HasUpdatedGrenade = false;

	void ResetBooleans();
};

class SeinVisualEditor
{
public:
	static VisualSettingsUpdated VisualSettingsUpdated;
	static VisualSettings DefaultVisualSetting;
	static VisualSettings VisualSetting;
	static std::unordered_map<std::string, tem::Vector4> DefaultVisualColors;
	static app::GameObject* OriHat;
	static bool ManagerLoaded;

	static void Cleanup();
	static void SetAllVisuals();
	static void ResetAllVisuals();
	static void LoadJsonFile(std::string& path);

	static void SetSkinnedMeshRendererColorByName(app::GameObject* parent, std::string componentName, tem::Vector4 color, tem::Vector4 emissive, std::string masterName, int setActive = -1);
	static void SetSkinnedMeshRendererColor(app::GameObject* parent, std::string componentName, tem::Vector4 color, tem::Vector4 emissive, std::string masterName, int setActive = -1);
	static void SetSkinnedMeshRendererColor(app::SkinnedMeshRenderer* skinnedMesh, std::string componentName, tem::Vector4 color, tem::Vector4 emissive, std::string masterName, int setActive = -1);
	static void SetMeshRendererColorByName(app::GameObject* parent, std::string componentName, tem::Vector4 color, tem::Vector4 emissive, std::string masterName, int setActive = -1);
	static void SetMeshRendererColor(app::GameObject* parent, std::vector<std::string>& scenePath, tem::Vector4 color, std::string masterName, int setActive = -1);
	static void SetMeshRenderersColor(app::GameObject* parent, std::string componentName, tem::Vector4 color, tem::Vector4 emissive, std::string masterName, int setActive = -1);
	static void SetParticleRendererColorByName(app::GameObject* parent, std::string componentName, tem::Vector4 color, tem::Vector4 emissive, std::string masterName, int setActive = -1);
	static void SetParticleRendererColor(app::GameObject* parent, std::vector<std::string>& scenePath, tem::Vector4 color, std::string masterName, int setActive = -1);
	static void SetParticleRenderersColor(app::GameObject* parent, std::string componentName, tem::Vector4 color, tem::Vector4 emissive, std::string masterName, int setActive = -1);
	static std::unordered_map<std::string, app::UberPoolGroup*> GetUberGroups(std::vector<std::string> groupNames);
};