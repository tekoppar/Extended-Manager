#pragma once

class GrenadeEffect
{
public:
    tem::Vector4 FireEffect = tem::Vector4(1.000000f, 1.000000f, 1.000000f, 1.000000f);
    tem::Vector4 Flame1 = tem::Vector4(2.000000f, 2.000000f, 2.000000f, 2.000000f);
    tem::Vector4 Flame2 = tem::Vector4(2.000000f, 2.000000f, 2.000000f, 2.000000f);
    tem::Vector4 Flame3 = tem::Vector4(2.000000f, 0.593643f, 0.000000f, 0.203922f);
    tem::Vector4 Smoke = tem::Vector4(4.000000f, 4.000000f, 4.000000f, 1.003922f);
    tem::Vector4 SnowPattern1 = tem::Vector4(2.000000f, 1.252412f, 0.424528f, 2.000000f);
    tem::Vector4 SnowPattern2 = tem::Vector4(2.000000f, 2.000000f, 2.000000f, 2.000000f);
    tem::Vector4 SnowPattern3 = tem::Vector4(0.588235f, 0.780168f, 1.545098f, 0.690196f);
    tem::Vector4 FireSprite = tem::Vector4(1.207547f, 1.078649f, 0.939836f, 2.000000f);
    tem::Vector4 LightCircle = tem::Vector4(2.608238f, 0.935601f, 0.000000f, 0.501961f);
    tem::Vector4 MainTrail = tem::Vector4(2.000000f, 2.000000f, 2.000000f, 2.000000f);
    tem::Vector4 ProtectiveLight = tem::Vector4(0.875000f, 0.398365f, 0.032169f, 0.501961f);
    tem::Vector4 TrailZigZag = tem::Vector4(0.735849f, 0.232879f, 0.038181f, 0.800000f);
};

class GrenadeEffectCharged
{
public:
    tem::Vector4 FireEffect = tem::Vector4(1.000000f, 0.435886f, 0.297170f, 1.000000f);
    tem::Vector4 Flame1 = tem::Vector4(1.000000f, 0.435886f, 0.297170f, 1.000000f);
    tem::Vector4 Flame2 = tem::Vector4(1.000000f, 0.435886f, 0.297170f, 0.000000f);
    tem::Vector4 Flame3 = tem::Vector4(2.000000f, 0.593643f, 0.000000f, 0.360784f);
    tem::Vector4 Smoke = tem::Vector4(4.000000f, 4.000000f, 4.000000f, 1.003922f);
    tem::Vector4 SnowPattern1 = tem::Vector4(2.000000f, 1.252412f, 0.424528f, 2.000000f);
    tem::Vector4 SnowPattern2 = tem::Vector4(2.000000f, 2.000000f, 2.000000f, 2.000000f);
    tem::Vector4 SnowPattern3 = tem::Vector4(2.000000f, 0.593643f, 0.000000f, 0.360784f);
    tem::Vector4 FireSprite = tem::Vector4(1.207547f, 1.078649f, 0.939836f, 2.000000f);
    tem::Vector4 LightCircle = tem::Vector4(2.608238f, 0.935601f, 0.000000f, 0.800000f);
    tem::Vector4 MainTrail = tem::Vector4(2.000000f, 2.000000f, 2.000000f, 2.000000f);
    tem::Vector4 ProtectiveLight = tem::Vector4(0.875000f, 0.398365f, 0.032169f, 1.000000f);
    tem::Vector4 TrailZigZag = tem::Vector4(0.735849f, 0.232879f, 0.038181f, 0.800000f);
};

class GrenadeExplosionFractured
{
public:
    tem::Vector4 Burst = tem::Vector4(0.177119f, 0.587285f, 1.852941f, 1.341177f);
    tem::Vector4 Distortion = tem::Vector4(0.500000f, 0.500000f, 0.500000f, 0.500000f);
    tem::Vector4 BurstPreGlow = tem::Vector4(0.779412f, 1.180585f, 2.000000f, 1.270588f);
    tem::Vector4 ArrowDistortion = tem::Vector4();
    tem::Vector4 ArrowGlow = tem::Vector4(0.465939f, 0.719772f, 2.000000f, 0.862000f);
    tem::Vector4 ArrowSingleParticle = tem::Vector4(1.264706f, 1.665314f, 2.000000f, 1.552941f);
    tem::Vector4 ArrowSmoke = tem::Vector4(0.192506f, 1.787911f, 1.943396f, 0.280000f);
    tem::Vector4 ArrowVignette = tem::Vector4();
    tem::Vector4 SnowPattern = tem::Vector4(4.919999f, 4.919999f, 4.919999f, 2.000000f);
};

class GrenadeFractured
{
public:
    tem::Vector4 OriSparkle = tem::Vector4(2.000000f, 1.071551f, 0.235294f, 0.345098f);
    tem::Vector4 OuterGlow = tem::Vector4(1.952941f, 0.820609f, 0.345098f, 1.474510f);
    tem::Vector4 ParticleDropGlow = tem::Vector4(4.886891f, 2.990678f, 1.267826f, 0.282000f);
    tem::Vector4 ParticleImpactGlow = tem::Vector4(1.000000f, 1.000000f, 1.000000f, 0.454902f);
    tem::Vector4 SingleSnowParticle = tem::Vector4(1.545098f, 1.053754f, 0.588235f, 0.690196f);
    tem::Vector4 SharedCircleGlow = tem::Vector4(6.000000f, 2.781645f, 0.596859f, 1.000000f);
    tem::Vector4 Sprite = tem::Vector4(0.415686f, 0.196506f, 0.000000f, 1.003922f);
    tem::Vector4 Trail = tem::Vector4(1.058824f, 1.058824f, 1.058824f, 1.003922f);
};

class GrenadeExplosionEffect {
public:
    tem::Vector4 ForceField = tem::Vector4(0.532000f, 0.233351f, 0.122892f, 0.544000f);
    tem::Vector4 Distortion = tem::Vector4(1.000000f, 1.000000f, 1.000000f, 1.000000f);
    tem::Vector4 LightCircle = tem::Vector4(2.608238f, 0.935601f, 0.000000f, 0.800000f);
    tem::Vector4 LightGlow = tem::Vector4(2.000000f, 0.593643f, 0.000000f, 0.360784f);
    tem::Vector4 StarSpike = tem::Vector4(0.510381f, 1.329805f, 1.735294f, 1.372549f);
    tem::Vector4 FX = tem::Vector4(1.000000f, 1.000000f, 1.000000f, 1.000000f);
    tem::Vector4 FireEffect = tem::Vector4(2.000000f, 2.000000f, 2.000000f, 2.000000f);
    tem::Vector4 Smoke = tem::Vector4(1.364706f, 1.219166f, 1.184314f, 0.158000f);
    tem::Vector4 SpriteSheetFire = tem::Vector4(1.000000f, 1.000000f, 1.000000f, 2.000000f);
    tem::Vector4 SnowPattern = tem::Vector4(2.000000f, 1.501591f, 0.820755f, 2.000000f);
    tem::Vector4 RadialBurned = tem::Vector4(2.118547f, 2.118547f, 2.118547f, 2.000000f);
    tem::Vector4 RadialBurned2 = tem::Vector4(0.000000f, 0.000000f, 0.000000f, 2.000000f);
    tem::Vector4 RadialCrack = tem::Vector4(0.188679f, 0.090096f, 0.043610f, 0.658824f);
    tem::Vector4 RadialIrisImpact = tem::Vector4(0.000000f, 0.000000f, 0.000000f, 2.000000f);
};

class GrenadeExplosionChargedEffect {
public:
    tem::Vector4 ForceField = tem::Vector4(0.532000f, 0.233351f, 0.122892f, 0.544000f);
    tem::Vector4 Distortion = tem::Vector4(1.000000f, 1.000000f, 1.000000f, 1.000000f);
    tem::Vector4 LightCircle = tem::Vector4(2.608238f, 0.935601f, 0.000000f, 0.800000f);
    tem::Vector4 LightGlow = tem::Vector4(2.000000f, 0.593643f, 0.000000f, 0.360784f);
    tem::Vector4 StarSpike = tem::Vector4(0.510381f, 1.329805f, 1.735294f, 1.372549f);
    tem::Vector4 FX = tem::Vector4(1.000000f, 1.000000f, 1.000000f, 1.000000f);
    tem::Vector4 FireEffect = tem::Vector4(2.000000f, 2.000000f, 2.000000f, 2.000000f);
    tem::Vector4 Smoke = tem::Vector4(1.364706f, 1.219166f, 1.184314f, 0.158000f);
    tem::Vector4 SpriteSheetFire = tem::Vector4(1.000000f, 1.000000f, 1.000000f, 2.000000f);
    tem::Vector4 SnowPattern = tem::Vector4(9.518762f, 4.315554f, 4.175683f, 1.262745f);
    tem::Vector4 RadialBurned = tem::Vector4(2.118547f, 2.118547f, 2.118547f, 2.000000f);
    tem::Vector4 RadialBurned2 = tem::Vector4(0.000000f, 0.000000f, 0.000000f, 2.000000f);
    tem::Vector4 RadialCrack = tem::Vector4(0.188679f, 0.090096f, 0.043610f, 0.658824f);
    tem::Vector4 RadialIrisImpact = tem::Vector4(0.000000f, 0.000000f, 0.000000f, 2.000000f);
};

 class GrenadeCharging
 {
 public:
     tem::Vector4 VignetteMask1 = tem::Vector4(2.996078f, 1.470417f, 0.501961f, 1.000000f);
     tem::Vector4 VignetteMask2 = tem::Vector4(2.996078f, 1.470417f, 0.501961f, 1.000000f);
     tem::Vector4 ArcaneOrb = tem::Vector4(2.996078f, 1.470417f, 0.501961f, 1.000000f);
     tem::Vector4 ChargingJump = tem::Vector4(1.000000f, 1.000000f, 1.000000f, 1.000000f);
     tem::Vector4 SnowPattern = tem::Vector4(4.000000f, 1.604268f, 1.339623f, 2.000000f);
     tem::Vector4 EnergySplash = tem::Vector4(2.000000f, 2.000000f, 2.000000f, 1.600000f);
 };

 class GrenadeAiming
 {
 public:
     tem::Vector4 Sparkle = tem::Vector4(2.000000f, 1.897059f, 1.897059f, 0.345098f);
     tem::Vector4 OuterGlow = tem::Vector4(0.535900f, 0.544171f, 1.735294f, 0.894118f);
     tem::Vector4 Sprite1 = tem::Vector4(0.205882f, 0.205882f, 0.205882f, 1.003922f);
     tem::Vector4 Sprite2 = tem::Vector4(0.205882f, 0.205882f, 0.205882f, 1.003922f);
 };

class GrenadeVisualSettings
{
public:
    GrenadeEffect Grenade;
    GrenadeEffectCharged Charged;
    GrenadeAiming GrenadeAiming;
    GrenadeCharging GrenadeCharging;
    GrenadeExplosionEffect GrenadeExplosion;
    GrenadeExplosionChargedEffect GrenadeExplosionCharged;
    GrenadeFractured GrenadeFractured;
    GrenadeExplosionFractured GrenadeExplosionFractured;

	void SetGrenadeVisuals(GrenadeVisualSettings grenadeSettings);
};