#pragma once

class GrenadeEffect
{
public:
    tem::Vector4 FireEffect;
    tem::Vector4 Flame1;
    tem::Vector4 Flame2;
    tem::Vector4 Flame3;
    tem::Vector4 Smoke;
    tem::Vector4 SnowPattern1;
    tem::Vector4 SnowPattern2;
    tem::Vector4 SnowPattern3;
    tem::Vector4 FireSprite;
    tem::Vector4 LightCircle;
    tem::Vector4 MainTrail;
    tem::Vector4 ProtectiveLight;
    tem::Vector4 TrailZigZag;
};

class GrenadeExplosionFractured
{
public:
    tem::Vector4 Burst;
    tem::Vector4 Distortion;
    tem::Vector4 BurstPreGlow;
    tem::Vector4 ArrowDistortion;
    tem::Vector4 ArrowGlow;
    tem::Vector4 ArrowSingleParticle;
    tem::Vector4 ArrowSmoke;
    tem::Vector4 ArrowVignette;
    tem::Vector4 SnowPattern;
};

class GrenadeFractured
{
public:
    tem::Vector4 OriSparkle;
    tem::Vector4 OuterGlow;
    tem::Vector4 ParticleDropGlow;
    tem::Vector4 ParticleImpactGlow;
    tem::Vector4 SingleSnowParticle;
    tem::Vector4 SharedCircleGlow;
    tem::Vector4 Sprite;
    tem::Vector4 Trail;
};

class GrenadeExplosionEffect {
public:
    tem::Vector4 ForceField;
    tem::Vector4 Distortion;
    tem::Vector4 LightCircle;
    tem::Vector4 LightGlow;
    tem::Vector4 StarSpike;
    tem::Vector4 FX;
    tem::Vector4 FireEffect;
    tem::Vector4 Smoke;
    tem::Vector4 SpriteSheetFire;
    tem::Vector4 SnowPattern;
    tem::Vector4 RadialBurned;
    tem::Vector4 RadialBurned2;
    tem::Vector4 RadialCrack;
    tem::Vector4 RadialIrisImpact;
};

 class GrenadeCharging
 {
 public:
     tem::Vector4 VignetteMask1;
     tem::Vector4 VignetteMask2;
     tem::Vector4 ArcaneOrb;
     tem::Vector4 ChargingJump;
     tem::Vector4 SnowPattern;
     tem::Vector4 EnergySplash;
 };

 class GrenadeAiming
 {
 public:
     tem::Vector4 Sparkle;
     tem::Vector4 OuterGlow;
     tem::Vector4 Sprite1;
     tem::Vector4 Sprite2;
 };

class GrenadeVisualSettings
{
public:
    GrenadeEffect Grenade;
    GrenadeEffect Charged;
    GrenadeAiming GrenadeAiming;
    GrenadeCharging GrenadeCharging;
    GrenadeExplosionEffect GrenadeExplosion;
    GrenadeExplosionEffect GrenadeExplosionCharged;
    GrenadeFractured GrenadeFractured;
    GrenadeExplosionFractured GrenadeExplosionFractured;

	void SetGrenadeVisuals(GrenadeVisualSettings grenadeSettings);
};