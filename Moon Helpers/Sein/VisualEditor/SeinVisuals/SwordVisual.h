#pragma once

class SwordHit {
public:
    tem::Vector4 DistortionNew = tem::Vector4(0.500000f, 0.500000f, 0.500000f, 0.440000f);
    tem::Vector4 FxBox = tem::Vector4(1.000000f, 1.000000f, 1.000000f, 1.000000f);
    tem::Vector4 DropGlowB = tem::Vector4(0.957725f, 0.960449f, 0.962264f, 0.611765f);
    tem::Vector4 DebrisParticles = tem::Vector4();
    tem::Vector4 DebrisParticlesFallBig = tem::Vector4();
    tem::Vector4 GlowUnmask = tem::Vector4(0.136570f, 0.165466f, 0.311321f, 1.000000f);
    tem::Vector4 VignetteMaskC = tem::Vector4(0.965085f, 1.103263f, 1.411021f, 1.000000f);
    tem::Vector4 LensCrossStart = tem::Vector4(2.118547f, 2.118547f, 2.118547f, 2.000000f);
    tem::Vector4 LensFlare20b = tem::Vector4(0.847059f, 1.223529f, 1.317647f, 2.000000f);
    tem::Vector4 LensFlare9 = tem::Vector4(0.035294f, 0.047059f, 0.078431f, 1.662745f);
    tem::Vector4 LensRadialSpike = tem::Vector4(0.652545f, 0.915415f, 0.981132f, 0.078431f);
    tem::Vector4 LightCircleShape = tem::Vector4(0.085618f, 0.595013f, 1.396226f, 0.705882f);
    tem::Vector4 LightGlow = tem::Vector4();
    tem::Vector4 RadialBurned2 = tem::Vector4(0.000000f, 0.000000f, 0.000000f, 2.000000f);
    tem::Vector4 RadialLightRays = tem::Vector4(0.957725f, 0.960449f, 0.962264f, 0.611765f);
    tem::Vector4 RadialMaskB = tem::Vector4();
    tem::Vector4 SparksLong = tem::Vector4(1.518868f, 1.705653f, 2.000000f, 2.000000f);
    tem::Vector4 SplashEdge = tem::Vector4(1.518868f, 1.705653f, 2.000000f, 2.000000f);
    tem::Vector4 SplashEdge2 = tem::Vector4();
    tem::Vector4 StarSpike2 = tem::Vector4(0.652545f, 0.915415f, 0.981132f, 1.639216f);
};

class SwordDamageBlue {
public:
    tem::Vector4 BurningCoreParticles = tem::Vector4(0.820896f, 0.867453f, 2.000000f, 0.305882f);
    tem::Vector4 BurnMarks = tem::Vector4(0.308824f, 0.600406f, 2.000000f, 0.501961f);
    tem::Vector4 ImpactSparklesA = tem::Vector4(0.447553f, 0.264706f, 4.000000f, 1.152000f);
    tem::Vector4 DebrisParticles = tem::Vector4(0.000000f, 0.000000f, 0.000000f, 0.000000f);
    tem::Vector4 Distortion = tem::Vector4(0.500000f, 0.500000f, 0.500000f, 0.500000f);
    tem::Vector4 ImpactCenter = tem::Vector4(1.986223f, 1.507463f, 2.000000f, 2.000000f);
    tem::Vector4 SmokeParticles = tem::Vector4(1.835821f, 1.835821f, 1.835821f, 2.000000f);
    tem::Vector4 SparkStartParticles = tem::Vector4(2.776119f, 3.865569f, 6.000000f, 1.568627f);
    tem::Vector4 VignetteMaskC = tem::Vector4(5.514704f, 10.749484f, 29.999998f, 0.741000f);
};

class SwordBlock {
public:
    tem::Vector4 AcidParticles = tem::Vector4(1.661765f, 1.661765f, 1.661765f, 1.121569f);
    tem::Vector4 CharacterGlow = tem::Vector4(0.115282f, 0.671642f, 0.204766f, 0.603922f);
    tem::Vector4 Distortion = tem::Vector4(0.500000f, 0.500000f, 0.500000f, 0.500000f);
    tem::Vector4 Circle = tem::Vector4(0.928201f, 1.480623f, 1.705882f, 1.000000f);
    tem::Vector4 FxBox = tem::Vector4(1.000000f, 1.000000f, 1.000000f, 1.000000f);
    tem::Vector4 CircleGlowC = tem::Vector4(0.250980f, 0.649105f, 1.733333f, 2.000000f);
    tem::Vector4 NoiseCaustic = tem::Vector4(1.747582f, 3.655005f, 11.226892f, 2.000000f);
    tem::Vector4 LavaFountainA = tem::Vector4(2.000000f, 2.000000f, 2.000000f, 1.090196f);
    tem::Vector4 SnowPattern = tem::Vector4(0.533064f, 1.163929f, 3.424529f, 1.372549f);
    tem::Vector4 SnowPattern2 = tem::Vector4(4.919999f, 4.919999f, 4.919999f, 2.000000f);
    tem::Vector4 StarSpike = tem::Vector4(0.510381f, 1.329805f, 1.735294f, 1.372549f);
    tem::Vector4 Glow = tem::Vector4();
    tem::Vector4 SingleSnowParticleA = tem::Vector4(0.510381f, 1.329805f, 1.735294f, 1.372549f);
};

class SwordAttackC {
public:
    tem::Vector4 BlowingSand = tem::Vector4(0.572549f, 0.847451f, 1.756863f, 2.000000f);
    tem::Vector4 SnowPattern = tem::Vector4(4.919999f, 4.919999f, 4.919999f, 2.000000f);
    tem::Vector4 SnowPattern2 = tem::Vector4();
    tem::Vector4 VignetteMaskC = tem::Vector4(1.597229f, 3.061357f, 8.474190f, 0.279000f);
};

class SwordAttack {
public:
    tem::Vector4 EnergyEffect;
    tem::Vector4 SnowPattern;
    tem::Vector4 FireSprite;
    tem::Vector4 VignetteMaskC;

    SwordAttack(tem::Vector4 EnergyEffect, tem::Vector4 SnowPattern, tem::Vector4 FireSprite, tem::Vector4 VignetteMaskC)
    {
        this->EnergyEffect = EnergyEffect;
        this->SnowPattern = SnowPattern;
        this->FireSprite = FireSprite;
        this->VignetteMaskC = VignetteMaskC;
    }
};

class SwordAttackAirPoke {
public:
    tem::Vector4 BlowingSand = tem::Vector4(0.572549f, 0.847451f, 1.756863f, 2.000000f);
    tem::Vector4 Glow = tem::Vector4(0.000000f, 0.659277f, 2.000000f, 0.340000f);
};

class SwordVisualSettings
{
public:
	tem::Vector4 SwordColor = tem::Vector4(1.198113f, 1.465409f, 2.000000f, 0.501961f);
	tem::Vector4 SwordEmissiveColor = tem::Vector4(0.391509f, 0.586226f, 1.000000f, 0.733333f);
	tem::Vector4 SwordHitEffectColor = tem::Vector4();
	tem::Vector4 SwordHitEffectEmissiveColor = tem::Vector4();
    SwordAttackAirPoke SwordAttackAirPoke;
    SwordAttack SwordAttackDownAir = SwordAttack(tem::Vector4(0.000000f, 0.000000f, 0.000000f, 0.000000f), tem::Vector4(1.388928f, 1.564535f, 1.924528f, 2.000000f), tem::Vector4(2.789111f, 2.825722f, 3.063687f, 1.858824f), tem::Vector4(0.282353f, 0.541176f, 1.498039f, 1.000000));
    SwordAttack SwordAttackGroundA = SwordAttack(tem::Vector4(0.000000f, 0.000000f, 0.000000f, 0.000000f), tem::Vector4(1.388928f, 1.564535f, 1.924528f, 2.000000f), tem::Vector4(2.789111f, 2.825722f, 3.063687f, 0.196078f), tem::Vector4(0.282353f, 0.541176f, 1.498039f, 1.000000));
    SwordAttack SwordAttackGroundB = SwordAttack(tem::Vector4(0.000000f, 0.000000f, 0.000000f, 0.000000f), tem::Vector4(1.388928f, 1.564535f, 1.924528f, 2.000000f), tem::Vector4(2.789111f, 2.825722f, 3.063687f, 0.196078f), tem::Vector4(0.282353f, 0.541176f, 1.498039f, 1.000000));
    SwordAttackC SwordAttackGroundC;
    SwordAttack SwordAttackUp = SwordAttack(tem::Vector4(0.000000f, 0.000000f, 0.000000f, 0.000000f), tem::Vector4(1.388928f, 1.564535f, 1.924528f, 2.000000f), tem::Vector4(2.789111f, 2.825722f, 3.063687f, 1.858824f), tem::Vector4(0.282353f, 0.541176f, 1.498039f, 1.000000));
    SwordBlock SwordBlock;
    SwordDamageBlue SwordDamageBlue;
    SwordHit SwordHit;

	void SetSwordVisuals(SwordVisualSettings swordSettings);
};