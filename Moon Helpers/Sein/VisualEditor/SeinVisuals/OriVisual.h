#pragma once

#include "TorchVisual.h"
#include "GlideVisual.h"
#include "BowVisual.h"
#include "SeinVisual.h"
#include "HammerVisual.h"
#include "SwordVisual.h"
#include "GrenadeVisual.h"

class OriHatVisualSettings 
{
public:
	std::string TexturePath = "NONE";
	tem::Vector4 Hat = tem::Vector4();
	tem::Vector4 HatEmissive = tem::Vector4();
};

class OriVisualSettings
{
public:
	tem::Vector4 Ori = tem::Vector4(1.20000005f, 1.20000005f, 1.20000005f, 1.0f);
	tem::Vector4 OriGlow = tem::Vector4(0.173159018f, 0.329188257f, 0.853000045f, 1.0f);
	tem::Vector4 OriTrail = tem::Vector4(0.309986f, 0.627807f, 1.528302f, 0.039216f);
	bool HideGlow = false;
	std::string TexturePath = "NONE";
	OriHatVisualSettings HatVisualSettings = OriHatVisualSettings();

	OriVisualSettings() {}

	void SetOriVisuals(OriVisualSettings oriSettings);
	void SetOriHat(OriHatVisualSettings hatSettings);
};

class VisualSettings
{
public:
	OriVisualSettings OriVisualSetting;
	TorchVisualSettings TorchVisualSetting;
	GlideVisualSettings GlideVisualSetting;
	BowVisualSettings BowVisualSetting;
	GoldenSeinViualSettings GoldenSeinVisualSetting;
	HammerVisualSettings HammerVisualSetting;
	SwordVisualSettings SwordVisualSetting;
	GrenadeVisualSettings GrenadeVisualSetting;

	VisualSettings()
	{
		this->OriVisualSetting = OriVisualSettings();
		this->TorchVisualSetting = TorchVisualSettings();
		this->GlideVisualSetting = GlideVisualSettings();
		this->BowVisualSetting = BowVisualSettings();
		this->GoldenSeinVisualSetting = GoldenSeinViualSettings();
		this->HammerVisualSetting = HammerVisualSettings();
		this->SwordVisualSetting = SwordVisualSettings();
		this->GrenadeVisualSetting = GrenadeVisualSettings();
	}
};