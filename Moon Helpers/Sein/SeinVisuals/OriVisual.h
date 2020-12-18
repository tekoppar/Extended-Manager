#pragma once

#include "TorchVisual.h"
#include "GlideVisual.h"
#include "BowVisual.h"
#include "SeinVisual.h"
#include "HammerVisual.h"
#include "SwordVisual.h"
#include "GrenadeVisual.h"

class OriVisualSettings 
{
public:
	tem::Vector4 Ori;
	tem::Vector4 OriGlow;
	tem::Vector4 OriTrail;
	bool HideGlow = false;
	std::string TexturePath = "NONE";

	void SetOriVisuals(OriVisualSettings oriSettings);
};

class VisualSettings
{
public:
	OriVisualSettings OriVisualSettings;
	TorchVisualSettings TorchVisualSettings;
	GlideVisualSettings GlideVisualSettings;
	BowVisualSettings BowVisualSettings;
	GoldenSeinViualSettings GoldenSeinVisualSettings;
	HammerVisualSettings HammerVisualSettings;
	SwordVisualSettings SwordVisualSettings;
	GrenadeVisualSettings GrenadeVisualSettings;
};