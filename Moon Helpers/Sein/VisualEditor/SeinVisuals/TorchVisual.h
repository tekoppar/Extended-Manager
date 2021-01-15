#pragma once

class TorchAttack
{
public:
	tem::Vector4 FireSprite = tem::Vector4();
	tem::Vector4 TrailZigZag = tem::Vector4();
};

class TorchBreak
{
public:
	tem::Vector4 AcidParticles = tem::Vector4();
	tem::Vector4 CharacterGlow = tem::Vector4();
	tem::Vector4 Smoke = tem::Vector4();
};

class TorchHitEffect
{
public:
	tem::Vector4 FsBox = tem::Vector4();
	tem::Vector4 FlameFireC = tem::Vector4();
	tem::Vector4 FlameGlow = tem::Vector4();
	tem::Vector4 FireEffect = tem::Vector4();
	tem::Vector4 FireEffect2 = tem::Vector4();
	tem::Vector4 RadialBurned = tem::Vector4();
	tem::Vector4 RadialBurned2 = tem::Vector4();
	tem::Vector4 SpriteSnowPattern = tem::Vector4();
	tem::Vector4 Glow = tem::Vector4();
	tem::Vector4 GlowUnmask = tem::Vector4();
};

class TorchVisualSettings
{
public:
	bool HideGlow = false;
	tem::Vector4 TorchColor = tem::Vector4();
	tem::Vector4 TorchFloatingSparkColor = tem::Vector4();
	tem::Vector4 TorchRunningColor = tem::Vector4();
	bool TorchTrailMeshEnable = false;
	tem::Vector4 TorchTrailMeshColor = tem::Vector4();
	std::vector<TorchAttack> TorchAirAttacks;
	std::vector<TorchAttack> TorchGroundAttacks;
	TorchBreak TorchBreak;
	TorchHitEffect TorchHit;
	TorchHitEffect TorchHitSmall;
	tem::Vector4 TorchLightEffect = tem::Vector4();
	tem::Vector4 TorchSpark = tem::Vector4();

	void SetTorchVisuals(TorchVisualSettings torchSettings);
};