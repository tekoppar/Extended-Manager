#pragma once

class HammerStompPreparation {
public:
    tem::Vector4 FireSprite3Flip;
    tem::Vector4 VignetteMaskC;
};

class HammerHit {
public:
    tem::Vector4 DistortionNew;
    tem::Vector4 FxBox;
    tem::Vector4 Glow;
};

class HammerBlock {
public:
    tem::Vector4 AcidParticles;
    tem::Vector4 Glow;
    tem::Vector4 CharacterGlow;
    tem::Vector4 Circle;
    tem::Vector4 LavaFountainA;
    tem::Vector4 SingleSnowParticleA;
};

class HammerStomp {
public:
    tem::Vector4 Glow;
    tem::Vector4 GiftLeafTransformationLightRing;
    tem::Vector4 Glow1;
    tem::Vector4 Smoke;
    tem::Vector4 SingleSnowParticleA;
};

class HammerAttack {
public:
    tem::Vector4 FireSprite;
    tem::Vector4 LinearGradientMask;
    tem::Vector4 VignetteMaskC;
    tem::Vector4 EnergyEffect;
    tem::Vector4 SpriteSnowPettern2;
};

class HammerVisualSettings
{
public:
	tem::Vector4 HammerColor;
	tem::Vector4 HammerEmissiveColor;
	tem::Vector4 HammerHitEffectColor;
	tem::Vector4 HammerHitEffectEmissiveColor;
    HammerAttack HammerAttackAir1;
    HammerAttack HammerAttackAir2;
    HammerAttack HammerAttackAir3;
    HammerAttack HammerAttackAirUpSwipe;
    HammerAttack HammerAttackGround;
    HammerAttack HammerAttackGround2;
    HammerAttack HammerAttackGroundDown;
    HammerAttack HammerAttackGroundUpSwipe;
    HammerStomp HammerAttackStomp;
    HammerBlock HammerBlock;
    HammerHit HammerHit;
    HammerStompPreparation HammerStompPreparation;

	void SetHammerVisuals(HammerVisualSettings hammerSettings);
};

