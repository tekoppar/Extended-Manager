#pragma once

class SwordHit {
public:
    tem::Vector4 DistortionNew;
    tem::Vector4 FxBox;
    tem::Vector4 DropGlowB;
    tem::Vector4 DebrisParticles;
    tem::Vector4 DebrisParticlesFallBig;
    tem::Vector4 GlowUnmask;
    tem::Vector4 VignetteMaskC;
    tem::Vector4 LensCrossStart;
    tem::Vector4 LensFlare20b;
    tem::Vector4 LensFlare9;
    tem::Vector4 LensRadialSpike;
    tem::Vector4 LightCircleShape;
    tem::Vector4 LightGlow;
    tem::Vector4 RadialBurned2;
    tem::Vector4 RadialLightRays;
    tem::Vector4 RadialMaskB;
    tem::Vector4 SparksLong;
    tem::Vector4 SplashEdge;
    tem::Vector4 SplashEdge2;
    tem::Vector4 StarSpike2;
};

class SwordDamageBlue {
public:
    tem::Vector4 BurningCoreParticles;
    tem::Vector4 BurnMarks;
    tem::Vector4 ImpactSparklesA;
    tem::Vector4 DebrisParticles;
    tem::Vector4 Distortion;
    tem::Vector4 ImpactCenter;
    tem::Vector4 SmokeParticles;
    tem::Vector4 SparkStartParticles;
    tem::Vector4 VignetteMaskC;
};

class SwordBlock {
public:
    tem::Vector4 AcidParticles;
    tem::Vector4 CharacterGlow;
    tem::Vector4 Distortion;
    tem::Vector4 Circle;
    tem::Vector4 FxBox;
    tem::Vector4 CircleGlowC;
    tem::Vector4 NoiseCaustic;
    tem::Vector4 LavaFountainA;
    tem::Vector4 SnowPattern;
    tem::Vector4 SnowPattern2;
    tem::Vector4 StarSpike;
    tem::Vector4 Glow;
    tem::Vector4 SingleSnowParticleA;
};

class SwordAttackC {
public:
    tem::Vector4 BlowingSand;
    tem::Vector4 SnowPattern;
    tem::Vector4 SnowPattern2;
    tem::Vector4 VignetteMaskC;
};

class SwordAttack {
public:
    tem::Vector4 EnergyEffect;
    tem::Vector4 SnowPattern;
    tem::Vector4 FireSprite;
    tem::Vector4 VignetteMaskC;
};

class SwordAttackAirPoke {
public:
    tem::Vector4 BlowingSand;
    tem::Vector4 Glow;
};

class SwordVisualSettings
{
public:
	tem::Vector4 SwordColor;
	tem::Vector4 SwordEmissiveColor;
	tem::Vector4 SwordHitEffectColor;
	tem::Vector4 SwordHitEffectEmissiveColor;
    SwordAttackAirPoke SwordAttackAirPoke;
    SwordAttack SwordAttackDownAir;
    SwordAttack SwordAttackGroundA;
    SwordAttack SwordAttackGroundB;
    SwordAttackC SwordAttackGroundC;
    SwordAttack SwordAttackUp;
    SwordBlock SwordBlock;
    SwordDamageBlue SwordDamageBlue;
    SwordHit SwordHit;

	void SetSwordVisuals(SwordVisualSettings swordSettings);
};