#pragma once

class ArrowVisualSettings
{
public:
	tem::Vector4 ArrowEffectColor = tem::Vector4(1.000000f, 1.000000f, 1.000000f, 1.000000f);
	tem::Vector4 ArrowEffectEmissiveColor = tem::Vector4(0.000000f, 0.000000f, 0.000000f, 0.000000f);
	tem::Vector4 ArrowSpearColor = tem::Vector4(1.705882f, 1.705882f, 1.705882f, 1.000000f);
	tem::Vector4 ArrowSpearEmissiveColor = tem::Vector4(0.191176f, 0.431034f, 1.000000f, 1.000000f);
	tem::Vector4 TipImpactColor = tem::Vector4(1.000000f, 1.000000f, 1.000000f, 0.454902f);
	tem::Vector4 TipImpactEmissiveColor = tem::Vector4(0.000000f, 0.000000f, 0.000000f, 0.000000f);
	tem::Vector4 TipParticleColor = tem::Vector4(1.279412f, 1.279412f, 1.279412f, 0.690196f);
	tem::Vector4 TipParticleEmissiveColor = tem::Vector4(0.000000f, 0.000000f, 0.000000f, 0.000000f);
	tem::Vector4 ArrowTrail = tem::Vector4();
	tem::Vector4 ArrowTrailEmissive = tem::Vector4();
};

class ArrowHitVisualSettings {
public:
	tem::Vector4 DistortionNew = tem::Vector4(0.500000f, 0.500000f, 0.500000f, 0.440000f);
	tem::Vector4 FxBox = tem::Vector4(1.000000f, 1.000000f, 1.000000f, 1.000000f);
	tem::Vector4 BloodSplat = tem::Vector4(1.367924f, 1.662504f, 2.000000f, 1.819608f);
	tem::Vector4 DebrisParticles = tem::Vector4(1.518868f, 1.705653f, 2.000000f, 2.000000f);
	tem::Vector4 DebrisParticlesFallBig = tem::Vector4(1.650943f, 1.782555f, 2.000000f, 2.000000f);
	tem::Vector4 GlowUnmask = tem::Vector4(0.136570f, 0.165466f, 0.311321f, 1.000000f);
	tem::Vector4 VignetteMaskC = tem::Vector4(0.915844f, 1.109486f, 1.578528f, 1.000000f);
	tem::Vector4 BlowingUpForceField = tem::Vector4();
	tem::Vector4 LensFlare20b = tem::Vector4(0.847059f, 1.223529f, 1.317647f, 2.000000f);
	tem::Vector4 LensFlare9 = tem::Vector4(0.035294f, 0.047059f, 0.078431f, 1.662745f);
	tem::Vector4 RadialBurned = tem::Vector4(2.118547f, 2.118547f, 2.118547f, 2.000000f);
	tem::Vector4 RadialBurned2 = tem::Vector4(0.000000f, 0.000000f, 0.000000f, 2.000000f);
	tem::Vector4 RadialIrisImpact = tem::Vector4(0.000000f, 0.000000f, 0.000000f, 2.000000f);
	tem::Vector4 StarSpike2 = tem::Vector4(0.652545f, 0.915415f, 0.981132f, 1.639216f);
};

class BowVisualSettings
{
public:
	tem::Vector4 BowShaftColor = tem::Vector4(1.188257f, 1.323019f, 1.455882f, 1.400000f);
	tem::Vector4 BowShaftEmissiveColor = tem::Vector4(0.000000f, 0.246369f, 1.000000f, 0.698039f);
	tem::Vector4 BowStringColor = tem::Vector4(1.311321f, 1.655660f, 2.000000f, 2.000000f);
	tem::Vector4 BowStringEmissiveColor = tem::Vector4(0.000000f, 0.190175f, 1.000000f, 0.698039f);
	ArrowVisualSettings ArrowVisualSettings;
	ArrowHitVisualSettings ArrowHitVisualSettings;

	void SetBowVisuals(BowVisualSettings bowSettings);
};