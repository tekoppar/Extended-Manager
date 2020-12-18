#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <filesystem>

#include "StringUtils.h"
#include "ManagerDef.h"
#include "UberStateManager.h"
#include "SeinVisualEditor.h"
#include "Tem.h"

#include "GrenadeVisual.h"

void GrenadeVisualSettings::SetGrenadeVisuals(GrenadeVisualSettings grenadeSettings)
{
	if (MDV::MoonSein != nullptr)
	{
		std::vector<std::string> groupNames = { "spiritGrenade", "spiritGrenadeAiming", "spiritGrenadeAir",
		"spiritGrenadeCharge", "spiritGrenadeExplosionAir", "spiritGrenadeExplosion", "spiritGrenadeExplosionFractured",
		"spiritGrenadeFractured", "spiritGrenadeFracturedNew" };
		std::unordered_map<std::string, app::UberPoolGroup*> groupMap = SeinVisualEditor::GetUberGroups(groupNames);

		app::UberPoolGroup* uberPoolGroup = groupMap[groupNames[0]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "fireEffectA (1)", grenadeSettings.Charged.FireEffect.ToColor(), grenadeSettings.Charged.FireEffect.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "glow", grenadeSettings.Charged.FireEffect.ToColor(), grenadeSettings.Charged.FireEffect.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "light", grenadeSettings.Charged.FireEffect.ToColor(), grenadeSettings.Charged.FireEffect.ToColor());
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "flame", grenadeSettings.Charged.Flame1.ToColor(), grenadeSettings.Charged.Flame1.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "flame (1)", grenadeSettings.Charged.Flame2.ToColor(), grenadeSettings.Charged.Flame2.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "sharedSingleSnowParticleA", grenadeSettings.Charged.SnowPattern1.ToColor(), grenadeSettings.Charged.SnowPattern1.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "sharedSmokeA", grenadeSettings.Charged.Smoke.ToColor(), grenadeSettings.Charged.Smoke.ToColor());
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spriteSnowPettern2", grenadeSettings.Charged.SnowPattern1.ToColor(), grenadeSettings.Charged.SnowPattern1.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "spriteSnowPettern2 (1)", grenadeSettings.Charged.SnowPattern2.ToColor(), grenadeSettings.Charged.SnowPattern2.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "fireSprite2 (1)", grenadeSettings.Charged.FireSprite.ToColor(), grenadeSettings.Charged.FireSprite.ToColor());
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "CircleShape1", grenadeSettings.Charged.LightCircle.ToColor(), grenadeSettings.Charged.LightCircle.ToColor());
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "quadraticRadialMaskNoise", grenadeSettings.Charged.LightCircle.ToColor(), grenadeSettings.Charged.LightCircle.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "quadraticRadialMaskNoise", grenadeSettings.Charged.LightCircle.ToColor(), grenadeSettings.Charged.LightCircle.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "quadraticRadialMaskNoise (1)", grenadeSettings.Charged.LightCircle.ToColor(), grenadeSettings.Charged.LightCircle.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "quadraticRadialMaskNoise", grenadeSettings.Charged.LightCircle.ToColor(), grenadeSettings.Charged.LightCircle.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "mainTrail", grenadeSettings.Charged.MainTrail.ToColor(), grenadeSettings.Charged.MainTrail.ToColor());
			//SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "protectiveLight", grenadeSettings.Charged.ProtectiveLight.ToColor(), grenadeSettings.Charged.ProtectiveLight.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "trailZigzag", grenadeSettings.Charged.TrailZigZag.ToColor(), grenadeSettings.Charged.TrailZigZag.ToColor());
		}

		uberPoolGroup = groupMap[groupNames[1]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "outerGlow", grenadeSettings.GrenadeAiming.OuterGlow.ToColor(), grenadeSettings.GrenadeAiming.OuterGlow.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "oriCSparkle", grenadeSettings.GrenadeAiming.Sparkle.ToColor(), grenadeSettings.GrenadeAiming.Sparkle.ToColor());
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "sprite", grenadeSettings.GrenadeAiming.Sprite1.ToColor(), grenadeSettings.GrenadeAiming.Sprite1.ToColor());
		}

		uberPoolGroup = groupMap[groupNames[2]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "fireEffectA (1)", grenadeSettings.Grenade.FireEffect.ToColor(), grenadeSettings.Grenade.FireEffect.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "glow", grenadeSettings.Grenade.FireEffect.ToColor(), grenadeSettings.Grenade.FireEffect.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "light", grenadeSettings.Grenade.FireEffect.ToColor(), grenadeSettings.Grenade.FireEffect.ToColor());
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "flame", grenadeSettings.Grenade.Flame1.ToColor(), grenadeSettings.Grenade.Flame1.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "flame (1)", grenadeSettings.Grenade.Flame2.ToColor(), grenadeSettings.Grenade.Flame2.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "sharedSingleSnowParticleA", grenadeSettings.Grenade.SnowPattern1.ToColor(), grenadeSettings.Grenade.SnowPattern1.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "sharedSmokeA", grenadeSettings.Grenade.Smoke.ToColor(), grenadeSettings.Grenade.Smoke.ToColor());
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spriteSnowPettern2", grenadeSettings.Grenade.SnowPattern1.ToColor(), grenadeSettings.Grenade.SnowPattern1.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "spriteSnowPettern2 (1)", grenadeSettings.Grenade.SnowPattern2.ToColor(), grenadeSettings.Grenade.SnowPattern2.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "fireSprite2 (1)", grenadeSettings.Grenade.FireSprite.ToColor(), grenadeSettings.Grenade.FireSprite.ToColor());
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "CircleShape1", grenadeSettings.Grenade.LightCircle.ToColor(), grenadeSettings.Grenade.LightCircle.ToColor());
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "quadraticRadialMaskNoise", grenadeSettings.Grenade.LightCircle.ToColor(), grenadeSettings.Grenade.LightCircle.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "quadraticRadialMaskNoise", grenadeSettings.Grenade.LightCircle.ToColor(), grenadeSettings.Grenade.LightCircle.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "quadraticRadialMaskNoise (1)", grenadeSettings.Grenade.LightCircle.ToColor(), grenadeSettings.Grenade.LightCircle.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "quadraticRadialMaskNoise", grenadeSettings.Grenade.LightCircle.ToColor(), grenadeSettings.Grenade.LightCircle.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "mainTrail", grenadeSettings.Grenade.MainTrail.ToColor(), grenadeSettings.Grenade.MainTrail.ToColor());
			//SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "protectiveLight", grenadeSettings.Grenade.ProtectiveLight.ToColor(), grenadeSettings.Grenade.ProtectiveLight.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "trailZigzag", grenadeSettings.Grenade.TrailZigZag.ToColor(), grenadeSettings.Grenade.TrailZigZag.ToColor());
		}

		uberPoolGroup = groupMap[groupNames[3]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "spriteSheetArcaneorb", grenadeSettings.GrenadeCharging.ArcaneOrb.ToColor(), grenadeSettings.GrenadeCharging.ArcaneOrb.ToColor());
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "vignetteMaskC", grenadeSettings.GrenadeCharging.VignetteMask1.ToColor(), grenadeSettings.GrenadeCharging.VignetteMask1.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "chargingJumpEffect (1)", grenadeSettings.GrenadeCharging.ChargingJump.ToColor(), grenadeSettings.GrenadeCharging.ChargingJump.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "spriteSnowPattern", grenadeSettings.GrenadeCharging.SnowPattern.ToColor(), grenadeSettings.GrenadeCharging.SnowPattern.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "energySplash (1)", grenadeSettings.GrenadeCharging.EnergySplash.ToColor(), grenadeSettings.GrenadeCharging.EnergySplash.ToColor());
		}

		uberPoolGroup = groupMap[groupNames[4]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "distortion", grenadeSettings.GrenadeExplosion.Distortion.ToColor(), grenadeSettings.GrenadeExplosion.Distortion.ToColor());
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "CircleShape1", grenadeSettings.GrenadeExplosion.LightCircle.ToColor(), grenadeSettings.GrenadeExplosion.LightCircle.ToColor());
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "glow", grenadeSettings.GrenadeExplosion.LightGlow.ToColor(), grenadeSettings.GrenadeExplosion.LightGlow.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "starSpike2", grenadeSettings.GrenadeExplosion.StarSpike.ToColor(), grenadeSettings.GrenadeExplosion.StarSpike.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "debrisParticles (2)", grenadeSettings.GrenadeExplosion.StarSpike.ToColor(), grenadeSettings.GrenadeExplosion.StarSpike.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "debrisParticles (1)", grenadeSettings.GrenadeExplosion.StarSpike.ToColor(), grenadeSettings.GrenadeExplosion.StarSpike.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "theGiftLeafTransformationLightRingB", grenadeSettings.GrenadeExplosion.StarSpike.ToColor(), grenadeSettings.GrenadeExplosion.StarSpike.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "fx (1)", grenadeSettings.GrenadeExplosion.FX.ToColor(), grenadeSettings.GrenadeExplosion.FX.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "fireEffect", grenadeSettings.GrenadeExplosion.FireEffect.ToColor(), grenadeSettings.GrenadeExplosion.FireEffect.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "smoke", grenadeSettings.GrenadeExplosion.Smoke.ToColor(), grenadeSettings.GrenadeExplosion.Smoke.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "spritesheetFire2", grenadeSettings.GrenadeExplosion.SpriteSheetFire.ToColor(), grenadeSettings.GrenadeExplosion.SpriteSheetFire.ToColor());
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spriteSnowPettern2", grenadeSettings.GrenadeExplosion.SnowPattern.ToColor(), grenadeSettings.GrenadeExplosion.SnowPattern.ToColor());
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "radialBurned", grenadeSettings.GrenadeExplosion.RadialBurned.ToColor(), grenadeSettings.GrenadeExplosion.RadialBurned.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "radialBurned2", grenadeSettings.GrenadeExplosion.RadialBurned2.ToColor(), grenadeSettings.GrenadeExplosion.RadialBurned2.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "radialCrack", grenadeSettings.GrenadeExplosion.RadialCrack.ToColor(), grenadeSettings.GrenadeExplosion.RadialCrack.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "radialIrisImpact", grenadeSettings.GrenadeExplosion.RadialIrisImpact.ToColor(), grenadeSettings.GrenadeExplosion.RadialIrisImpact.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "quadraticRadialMaskNoise", grenadeSettings.GrenadeExplosion.LightCircle.ToColor(), grenadeSettings.GrenadeExplosion.LightCircle.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "quadraticRadialMaskNoise (1)", grenadeSettings.GrenadeExplosion.LightCircle.ToColor(), grenadeSettings.GrenadeExplosion.LightCircle.ToColor());
		}

		uberPoolGroup = groupMap[groupNames[5]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "distortion", grenadeSettings.GrenadeExplosionCharged.Distortion.ToColor(), grenadeSettings.GrenadeExplosionCharged.Distortion.ToColor());
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "CircleShape1", grenadeSettings.GrenadeExplosionCharged.LightCircle.ToColor(), grenadeSettings.GrenadeExplosionCharged.LightCircle.ToColor());
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "glow", grenadeSettings.GrenadeExplosionCharged.LightGlow.ToColor(), grenadeSettings.GrenadeExplosionCharged.LightGlow.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "starSpike2", grenadeSettings.GrenadeExplosionCharged.StarSpike.ToColor(), grenadeSettings.GrenadeExplosionCharged.StarSpike.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "debrisParticles (2)", grenadeSettings.GrenadeExplosionCharged.StarSpike.ToColor(), grenadeSettings.GrenadeExplosionCharged.StarSpike.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "debrisParticles (1)", grenadeSettings.GrenadeExplosionCharged.StarSpike.ToColor(), grenadeSettings.GrenadeExplosionCharged.StarSpike.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "theGiftLeafTransformationLightRingB", grenadeSettings.GrenadeExplosionCharged.StarSpike.ToColor(), grenadeSettings.GrenadeExplosionCharged.StarSpike.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "fx (1)", grenadeSettings.GrenadeExplosionCharged.FX.ToColor(), grenadeSettings.GrenadeExplosionCharged.FX.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "fireEffect", grenadeSettings.GrenadeExplosionCharged.FireEffect.ToColor(), grenadeSettings.GrenadeExplosionCharged.FireEffect.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "smoke", grenadeSettings.GrenadeExplosionCharged.Smoke.ToColor(), grenadeSettings.GrenadeExplosionCharged.Smoke.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "spritesheetFire2", grenadeSettings.GrenadeExplosionCharged.SpriteSheetFire.ToColor(), grenadeSettings.GrenadeExplosionCharged.SpriteSheetFire.ToColor());
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spriteSnowPettern2", grenadeSettings.GrenadeExplosionCharged.SnowPattern.ToColor(), grenadeSettings.GrenadeExplosionCharged.SnowPattern.ToColor());
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "radialBurned", grenadeSettings.GrenadeExplosionCharged.RadialBurned.ToColor(), grenadeSettings.GrenadeExplosionCharged.RadialBurned.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "radialBurned2", grenadeSettings.GrenadeExplosionCharged.RadialBurned2.ToColor(), grenadeSettings.GrenadeExplosionCharged.RadialBurned2.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "radialCrack", grenadeSettings.GrenadeExplosionCharged.RadialCrack.ToColor(), grenadeSettings.GrenadeExplosionCharged.RadialCrack.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "radialIrisImpact", grenadeSettings.GrenadeExplosionCharged.RadialIrisImpact.ToColor(), grenadeSettings.GrenadeExplosionCharged.RadialIrisImpact.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "quadraticRadialMaskNoise", grenadeSettings.GrenadeExplosionCharged.LightCircle.ToColor(), grenadeSettings.GrenadeExplosionCharged.LightCircle.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "quadraticRadialMaskNoise (1)", grenadeSettings.GrenadeExplosionCharged.LightCircle.ToColor(), grenadeSettings.GrenadeExplosionCharged.LightCircle.ToColor());
		}

		uberPoolGroup = groupMap[groupNames[6]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "distortion", grenadeSettings.GrenadeExplosionFractured.Distortion.ToColor(), grenadeSettings.GrenadeExplosionFractured.Distortion.ToColor());
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "glow", grenadeSettings.GrenadeExplosionFractured.ArrowGlow.ToColor(), grenadeSettings.GrenadeExplosionFractured.ArrowGlow.ToColor());
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "preliminaryGlow", grenadeSettings.GrenadeExplosionFractured.BurstPreGlow.ToColor(), grenadeSettings.GrenadeExplosionFractured.BurstPreGlow.ToColor());
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "burstGraphic", grenadeSettings.GrenadeExplosionFractured.Burst.ToColor(), grenadeSettings.GrenadeExplosionFractured.Burst.ToColor());
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "lensFlare15a", grenadeSettings.GrenadeExplosionFractured.ArrowGlow.ToColor(), grenadeSettings.GrenadeExplosionFractured.ArrowGlow.ToColor());
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "lensPointH2", grenadeSettings.GrenadeExplosionFractured.ArrowGlow.ToColor(), grenadeSettings.GrenadeExplosionFractured.ArrowGlow.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "starSpike2", grenadeSettings.GrenadeExplosionFractured.Burst.ToColor(), grenadeSettings.GrenadeExplosionFractured.Burst.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "debrisParticles", grenadeSettings.GrenadeExplosionFractured.Burst.ToColor(), grenadeSettings.GrenadeExplosionFractured.Burst.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "theGiftLeafTransformationLightRing", grenadeSettings.GrenadeExplosionFractured.Burst.ToColor(), grenadeSettings.GrenadeExplosionFractured.Burst.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "sharedLavaFountainA", grenadeSettings.GrenadeExplosionFractured.Burst.ToColor(), grenadeSettings.GrenadeExplosionFractured.Burst.ToColor());
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "radialBurned", grenadeSettings.GrenadeExplosionFractured.Burst.ToColor(), grenadeSettings.GrenadeExplosionFractured.Burst.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "radialBurned2", grenadeSettings.GrenadeExplosionFractured.Burst.ToColor(), grenadeSettings.GrenadeExplosionFractured.Burst.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "radialCircle2", grenadeSettings.GrenadeExplosionFractured.Burst.ToColor(), grenadeSettings.GrenadeExplosionFractured.Burst.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "radialCrack", grenadeSettings.GrenadeExplosionFractured.Burst.ToColor(), grenadeSettings.GrenadeExplosionFractured.Burst.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "radialIrisImpact", grenadeSettings.GrenadeExplosionFractured.Burst.ToColor(), grenadeSettings.GrenadeExplosionFractured.Burst.ToColor());
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spriteSnowPettern2", grenadeSettings.GrenadeExplosionFractured.SnowPattern.ToColor(), grenadeSettings.GrenadeExplosionFractured.SnowPattern.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "sharedSingleSnowParticleA", grenadeSettings.GrenadeExplosionFractured.ArrowSingleParticle.ToColor(), grenadeSettings.GrenadeExplosionFractured.ArrowSingleParticle.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "smoke", grenadeSettings.GrenadeExplosionFractured.ArrowSmoke.ToColor(), grenadeSettings.GrenadeExplosionFractured.ArrowSmoke.ToColor());
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "smoke", grenadeSettings.GrenadeExplosionFractured.SnowPattern.ToColor(), grenadeSettings.GrenadeExplosionFractured.SnowPattern.ToColor());
		}

		uberPoolGroup = groupMap[groupNames[7]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "oriCSparkle", grenadeSettings.GrenadeFractured.OriSparkle.ToColor(), grenadeSettings.GrenadeFractured.OriSparkle.ToColor());
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "outerGlow", grenadeSettings.GrenadeFractured.OuterGlow.ToColor(), grenadeSettings.GrenadeFractured.OuterGlow.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "altarDropGlowA", grenadeSettings.GrenadeFractured.ParticleDropGlow.ToColor(), grenadeSettings.GrenadeFractured.ParticleDropGlow.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "caveLaserSpawnerLaserbeamImpactGlowA", grenadeSettings.GrenadeFractured.ParticleImpactGlow.ToColor(), grenadeSettings.GrenadeFractured.ParticleImpactGlow.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "sharedSingleSnowParticleC", grenadeSettings.GrenadeFractured.SingleSnowParticle.ToColor(), grenadeSettings.GrenadeFractured.SingleSnowParticle.ToColor());
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "sharedCircleGlowB", grenadeSettings.GrenadeFractured.SharedCircleGlow.ToColor(), grenadeSettings.GrenadeFractured.SharedCircleGlow.ToColor());
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "sprite", grenadeSettings.GrenadeFractured.Sprite.ToColor(), grenadeSettings.GrenadeFractured.Sprite.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "trail", grenadeSettings.GrenadeFractured.Trail.ToColor(), grenadeSettings.GrenadeFractured.Trail.ToColor());
		}

		uberPoolGroup = groupMap[groupNames[8]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "oriCSparkle", grenadeSettings.GrenadeFractured.OriSparkle.ToColor(), grenadeSettings.GrenadeFractured.OriSparkle.ToColor());
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "CircleShape1", grenadeSettings.GrenadeFractured.OriSparkle.ToColor(), grenadeSettings.GrenadeFractured.OriSparkle.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "starSpike2", grenadeSettings.GrenadeFractured.OriSparkle.ToColor(), grenadeSettings.GrenadeFractured.OriSparkle.ToColor());
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "outerGlow", grenadeSettings.GrenadeFractured.OuterGlow.ToColor(), grenadeSettings.GrenadeFractured.OuterGlow.ToColor());
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "glow", grenadeSettings.GrenadeFractured.OuterGlow.ToColor(), grenadeSettings.GrenadeFractured.OuterGlow.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "altarDropGlowA", grenadeSettings.GrenadeFractured.ParticleDropGlow.ToColor(), grenadeSettings.GrenadeFractured.ParticleDropGlow.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "fx (1)", grenadeSettings.GrenadeFractured.ParticleDropGlow.ToColor(), grenadeSettings.GrenadeFractured.ParticleDropGlow.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "fireEffect", grenadeSettings.GrenadeFractured.ParticleDropGlow.ToColor(), grenadeSettings.GrenadeFractured.ParticleDropGlow.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "caveLaserSpawnerLaserbeamImpactGlowA", grenadeSettings.GrenadeFractured.ParticleImpactGlow.ToColor(), grenadeSettings.GrenadeFractured.ParticleImpactGlow.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "debrisParticles (2)", grenadeSettings.GrenadeFractured.ParticleImpactGlow.ToColor(), grenadeSettings.GrenadeFractured.ParticleImpactGlow.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "debrisParticles (1)", grenadeSettings.GrenadeFractured.ParticleImpactGlow.ToColor(), grenadeSettings.GrenadeFractured.ParticleImpactGlow.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "sharedSingleSnowParticleC", grenadeSettings.GrenadeFractured.SingleSnowParticle.ToColor(), grenadeSettings.GrenadeFractured.SingleSnowParticle.ToColor());
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "sharedCircleGlowB", grenadeSettings.GrenadeFractured.SharedCircleGlow.ToColor(), grenadeSettings.GrenadeFractured.SharedCircleGlow.ToColor());
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "sprite", grenadeSettings.GrenadeFractured.Sprite.ToColor(), grenadeSettings.GrenadeFractured.Sprite.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "trail", grenadeSettings.GrenadeFractured.Trail.ToColor(), grenadeSettings.GrenadeFractured.Trail.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "smoke", grenadeSettings.GrenadeFractured.Trail.ToColor(), grenadeSettings.GrenadeFractured.Trail.ToColor());
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "radialBurned", grenadeSettings.GrenadeFractured.SingleSnowParticle.ToColor(), grenadeSettings.GrenadeFractured.SingleSnowParticle.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "radialBurned2", grenadeSettings.GrenadeFractured.SingleSnowParticle.ToColor(), grenadeSettings.GrenadeFractured.SingleSnowParticle.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "radialCrack", grenadeSettings.GrenadeFractured.Sprite.ToColor(), grenadeSettings.GrenadeFractured.Sprite.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "radialIrisImpact", grenadeSettings.GrenadeFractured.Sprite.ToColor(), grenadeSettings.GrenadeFractured.Sprite.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "spritesheetFire2", grenadeSettings.GrenadeFractured.ParticleImpactGlow.ToColor(), grenadeSettings.GrenadeFractured.ParticleImpactGlow.ToColor());
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spriteSnowPettern2", grenadeSettings.GrenadeFractured.Trail.ToColor(), grenadeSettings.GrenadeFractured.Trail.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "theGiftLeafTransformationLightRingB", grenadeSettings.GrenadeFractured.OriSparkle.ToColor(), grenadeSettings.GrenadeFractured.OriSparkle.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "quadraticRadialMaskNoise", grenadeSettings.GrenadeFractured.OuterGlow.ToColor(), grenadeSettings.GrenadeFractured.OuterGlow.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "quadraticRadialMaskNoise (1)", grenadeSettings.GrenadeFractured.ParticleDropGlow.ToColor(), grenadeSettings.GrenadeFractured.ParticleDropGlow.ToColor());
		}

		SeinVisualEditor::VisualSettings.GrenadeVisualSettings = grenadeSettings;
		SeinVisualEditor::VisualSettingsUpdated.HasUpdatedGrenade = true;
	}
}