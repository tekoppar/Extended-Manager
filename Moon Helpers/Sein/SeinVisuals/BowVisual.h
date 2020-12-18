#pragma once

class ArrowVisualSettings
{
public:
	tem::Vector4 ArrowEffectColor;
	tem::Vector4 ArrowEffectEmissiveColor;
	tem::Vector4 ArrowSpearColor;
	tem::Vector4 ArrowSpearEmissiveColor;
	tem::Vector4 TipImpactColor;
	tem::Vector4 TipImpactEmissiveColor;
	tem::Vector4 TipParticleColor;
	tem::Vector4 TipParticleEmissiveColor;
};

class BowVisualSettings
{
public:
	tem::Vector4 BowShaftColor;
	tem::Vector4 BowShaftEmissiveColor;
	tem::Vector4 BowStringColor;
	tem::Vector4 BowStringEmissiveColor;
	ArrowVisualSettings ArrowVisualSettings;

	void SetBowVisuals(BowVisualSettings bowSettings);
};