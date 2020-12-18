#pragma once

class TorchAttack
{
public:
	tem::Vector4 FireSprite;
	tem::Vector4 TrailZigZag;
};

class TorchBreak
{
public:
	tem::Vector4 AcidParticles;
	tem::Vector4 CharacterGlow;
};

class TorchHitEffect
{
public:
	tem::Vector4 FsBox;
	tem::Vector4 FlameFireC;
	tem::Vector4 FlameGlow;
	tem::Vector4 FireEffect;
	tem::Vector4 FireEffect2;
	tem::Vector4 RadialBurned;
	tem::Vector4 RadialBurned2;
	tem::Vector4 SpriteSnowPattern;
	tem::Vector4 Glow;
	tem::Vector4 GlowUnmask;
};

class TorchVisualSettings
{
public:
	bool HideGlow;
	tem::Vector4 TorchColor;
	tem::Vector4 TorchFloatingSparkColor;
	tem::Vector4 TorchRunningColor;
	bool TorchTrailMeshEnable;
	tem::Vector4 TorchTrailMeshColor;
	std::vector<TorchAttack> TorchAirAttacks;
	std::vector<TorchAttack> TorchGroundAttacks;
	TorchBreak TorchBreak;
	TorchHitEffect TorchHit;
	TorchHitEffect TorchHitSmall;
	tem::Vector4 TorchLightEffect;
	tem::Vector4 TorchSpark;

	void SetTorchVisuals(TorchVisualSettings torchSettings);
};