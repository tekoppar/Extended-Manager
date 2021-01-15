#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <filesystem>

#include "StringUtils.h"
#include "ManagerDef.h"
#include "UberStateManager.h"
#include "SeinVisualEditor.h"
#include "Tem.h"

#include "SwordVisual.h"

void SwordVisualSettings::SetSwordVisuals(SwordVisualSettings swordSettings)
{
	if (MDV::MoonSein != nullptr)
	{
		if (MDV::MoonSein != nullptr && MDV::MoonSein->fields.Abilities->fields.ComboWrapper->fields.HasState == true)
		{
			app::MeleeWeapon* sword = MDV::MoonSein->fields.Abilities->fields.ComboWrapper->fields.State->fields.Weapons->vector[1];
			app::MeleeWeaponSword* meleeSword = (app::MeleeWeaponSword*)sword;
			SeinVisualEditor::SetSkinnedMeshRendererColor((app::SkinnedMeshRenderer*)meleeSword->fields.SwordRenderer, "meleeSword", swordSettings.SwordColor, swordSettings.SwordEmissiveColor, "Sword");
		}

		std::vector<std::string> groupNames = { "swordAttackAirPokeEffect", "swordAttackDownAirEffectV3", "swordAttackGroundAEffectV4",
		"swordAttackGroundBEffectV4", "swordAttackGroundCEffect", "swordAttackUpEffectV3", "swordBlockEffect",
		"swordDamageEffectBlue", "swordHitEffect" };
		std::unordered_map<std::string, app::UberPoolGroup*> groupMap = SeinVisualEditor::GetUberGroups(groupNames);

		app::UberPoolGroup* uberPoolGroup = groupMap[groupNames[0]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "glow", swordSettings.SwordAttackAirPoke.BlowingSand.ToColor(), swordSettings.SwordAttackAirPoke.BlowingSand.ToColor(), "SwordAttackAirPoke");
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "sharedBlowingSand", swordSettings.SwordAttackAirPoke.Glow.ToColor(), swordSettings.SwordAttackAirPoke.Glow.ToColor(), "SwordAttackAirPoke");
		}

		uberPoolGroup = groupMap[groupNames[1]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "fireSprite3", swordSettings.SwordAttackDownAir.FireSprite.ToColor(), swordSettings.SwordAttackDownAir.FireSprite.ToColor(), "SwordAttackDownAir");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "quadraticGradientMaskHorizontal", swordSettings.SwordAttackDownAir.FireSprite.ToColor(), swordSettings.SwordAttackDownAir.FireSprite.ToColor(), "SwordAttackDownAir");
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "vignetteMaskC", swordSettings.SwordAttackDownAir.VignetteMaskC.ToColor(), swordSettings.SwordAttackDownAir.VignetteMaskC.ToColor(), "SwordAttackDownAir");
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "energyEffect", swordSettings.SwordAttackDownAir.EnergyEffect.ToColor(), swordSettings.SwordAttackDownAir.EnergyEffect.ToColor(), "SwordAttackDownAir");
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spriteSnowPettern2", swordSettings.SwordAttackDownAir.SnowPattern.ToColor(), swordSettings.SwordAttackDownAir.SnowPattern.ToColor(), "SwordAttackDownAir");
		}

		uberPoolGroup = groupMap[groupNames[2]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "fireSprite3", swordSettings.SwordAttackGroundA.FireSprite.ToColor(), swordSettings.SwordAttackGroundA.FireSprite.ToColor(), "SwordAttackGroundA");
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "vignetteMaskC", swordSettings.SwordAttackGroundA.VignetteMaskC.ToColor(), swordSettings.SwordAttackGroundA.VignetteMaskC.ToColor(), "SwordAttackGroundA");
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "energyEffect", swordSettings.SwordAttackGroundA.EnergyEffect.ToColor(), swordSettings.SwordAttackGroundA.EnergyEffect.ToColor(), "SwordAttackGroundA");
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spriteSnowPettern2", swordSettings.SwordAttackGroundA.SnowPattern.ToColor(), swordSettings.SwordAttackGroundA.SnowPattern.ToColor(), "SwordAttackGroundA");
		}

		uberPoolGroup = groupMap[groupNames[3]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "fireSprite3", swordSettings.SwordAttackGroundB.FireSprite.ToColor(), swordSettings.SwordAttackGroundB.FireSprite.ToColor(), "SwordAttackGroundB");
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "vignetteMaskC", swordSettings.SwordAttackGroundB.VignetteMaskC.ToColor(), swordSettings.SwordAttackGroundB.VignetteMaskC.ToColor(), "SwordAttackGroundB");
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "energyEffect", swordSettings.SwordAttackGroundB.EnergyEffect.ToColor(), swordSettings.SwordAttackGroundB.EnergyEffect.ToColor(), "SwordAttackGroundB");
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spriteSnowPettern2", swordSettings.SwordAttackGroundB.SnowPattern.ToColor(), swordSettings.SwordAttackGroundB.SnowPattern.ToColor(), "SwordAttackGroundB");
		}

		uberPoolGroup = groupMap[groupNames[4]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "linearGradientMaskHorizontal", swordSettings.SwordAttackGroundC.VignetteMaskC.ToColor(), swordSettings.SwordAttackGroundC.VignetteMaskC.ToColor(), "SwordAttackGroundC");
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "vignetteMaskC", swordSettings.SwordAttackGroundC.VignetteMaskC.ToColor(), swordSettings.SwordAttackGroundC.VignetteMaskC.ToColor(), "SwordAttackGroundC");
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spriteSnowPettern", swordSettings.SwordAttackGroundC.SnowPattern.ToColor(), swordSettings.SwordAttackGroundC.SnowPattern.ToColor(), "SwordAttackGroundC");
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spriteSnowPettern2", swordSettings.SwordAttackGroundC.SnowPattern2.ToColor(), swordSettings.SwordAttackGroundC.SnowPattern2.ToColor(), "SwordAttackGroundC");
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "sharedBlowingSand", swordSettings.SwordAttackGroundC.BlowingSand.ToColor(), swordSettings.SwordAttackGroundC.BlowingSand.ToColor(), "SwordAttackGroundC");
		}

		uberPoolGroup = groupMap[groupNames[5]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "fireSprite3", swordSettings.SwordAttackUp.FireSprite.ToColor(), swordSettings.SwordAttackUp.FireSprite.ToColor(), "SwordAttackUp");
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "vignetteMaskC", swordSettings.SwordAttackUp.VignetteMaskC.ToColor(), swordSettings.SwordAttackUp.VignetteMaskC.ToColor(), "SwordAttackUp");
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "energyEffect", swordSettings.SwordAttackUp.EnergyEffect.ToColor(), swordSettings.SwordAttackUp.EnergyEffect.ToColor(), "SwordAttackUp");
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spriteSnowPettern2", swordSettings.SwordAttackUp.SnowPattern.ToColor(), swordSettings.SwordAttackUp.SnowPattern.ToColor(), "SwordAttackUp");
		}

		uberPoolGroup = groupMap[groupNames[6]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "acidParticles", swordSettings.SwordBlock.AcidParticles.ToColor(), swordSettings.SwordBlock.AcidParticles.ToColor(), "SwordBlock");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "characterGlow", swordSettings.SwordBlock.CharacterGlow.ToColor(), swordSettings.SwordBlock.CharacterGlow.ToColor(), "SwordBlock");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "circle", swordSettings.SwordBlock.Circle.ToColor(), swordSettings.SwordBlock.Circle.ToColor(), "SwordBlock");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "distortion", swordSettings.SwordBlock.Distortion.ToColor(), swordSettings.SwordBlock.Distortion.ToColor(), "SwordBlock");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "fxBox", swordSettings.SwordBlock.FxBox.ToColor(), swordSettings.SwordBlock.FxBox.ToColor(), "SwordBlock");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "circleGlowC", swordSettings.SwordBlock.CircleGlowC.ToColor(), swordSettings.SwordBlock.CircleGlowC.ToColor(), "SwordBlock");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "noiseCaustic2", swordSettings.SwordBlock.NoiseCaustic.ToColor(), swordSettings.SwordBlock.NoiseCaustic.ToColor(), "SwordBlock");
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "sharedLavaFountainA", swordSettings.SwordBlock.LavaFountainA.ToColor(), swordSettings.SwordBlock.LavaFountainA.ToColor(), "SwordBlock");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "spriteSnowPattern", swordSettings.SwordBlock.SnowPattern.ToColor(), swordSettings.SwordBlock.SnowPattern.ToColor(), "SwordBlock");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "spriteSnowPettern2", swordSettings.SwordBlock.SnowPattern2.ToColor(), swordSettings.SwordBlock.SnowPattern2.ToColor(), "SwordBlock");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "starSpike2", swordSettings.SwordBlock.StarSpike.ToColor(), swordSettings.SwordBlock.StarSpike.ToColor(), "SwordBlock");
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "glow", swordSettings.SwordBlock.Glow.ToColor(), swordSettings.SwordBlock.Glow.ToColor(), "SwordBlock");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "sharedSingleSnowParticleA", swordSettings.SwordBlock.SingleSnowParticleA.ToColor(), swordSettings.SwordBlock.SingleSnowParticleA.ToColor(), "SwordBlock");
		}

		uberPoolGroup = groupMap[groupNames[7]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "vignetteMaskC", swordSettings.SwordDamageBlue.VignetteMaskC.ToColor(), swordSettings.SwordDamageBlue.VignetteMaskC.ToColor(), "SwordDamageBlue");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "burningCoreParticles", swordSettings.SwordDamageBlue.BurningCoreParticles.ToColor(), swordSettings.SwordDamageBlue.BurningCoreParticles.ToColor(), "SwordDamageBlue");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "distortion", swordSettings.SwordDamageBlue.Distortion.ToColor(), swordSettings.SwordDamageBlue.Distortion.ToColor(), "SwordDamageBlue");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "burnMarks", swordSettings.SwordDamageBlue.BurnMarks.ToColor(), swordSettings.SwordDamageBlue.BurnMarks.ToColor(), "SwordDamageBlue");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "caveLaserSpawnerLaserbeamImpactSparklesA", swordSettings.SwordDamageBlue.ImpactSparklesA.ToColor(), swordSettings.SwordDamageBlue.ImpactSparklesA.ToColor(), "SwordDamageBlue");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "debrisParticles", swordSettings.SwordDamageBlue.DebrisParticles.ToColor(), swordSettings.SwordDamageBlue.DebrisParticles.ToColor(), "SwordDamageBlue");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "impactCenter", swordSettings.SwordDamageBlue.ImpactCenter.ToColor(), swordSettings.SwordDamageBlue.ImpactCenter.ToColor(), "SwordDamageBlue");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "smokeParticles", swordSettings.SwordDamageBlue.SmokeParticles.ToColor(), swordSettings.SwordDamageBlue.SmokeParticles.ToColor(), "SwordDamageBlue");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "sparkStartParticles", swordSettings.SwordDamageBlue.SparkStartParticles.ToColor(), swordSettings.SwordDamageBlue.SparkStartParticles.ToColor(), "SwordDamageBlue");
		}

		uberPoolGroup = groupMap[groupNames[8]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "vignetteMaskC", swordSettings.SwordHit.VignetteMaskC.ToColor(), swordSettings.SwordHit.VignetteMaskC.ToColor(), "SwordHit");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "altarDropGlowB", swordSettings.SwordHit.DropGlowB.ToColor(), swordSettings.SwordHit.DropGlowB.ToColor(), "SwordHit");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "lensCrossStar", swordSettings.SwordHit.LensCrossStart.ToColor(), swordSettings.SwordHit.LensCrossStart.ToColor(), "SwordHit");
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "lensFlare20b", swordSettings.SwordHit.LensFlare20b.ToColor(), swordSettings.SwordHit.LensFlare20b.ToColor(), "SwordHit");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "lensFlare9", swordSettings.SwordHit.LensFlare9.ToColor(), swordSettings.SwordHit.LensFlare9.ToColor(), "SwordHit");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "lensRadialSpike", swordSettings.SwordHit.LensRadialSpike.ToColor(), swordSettings.SwordHit.LensRadialSpike.ToColor(), "SwordHit");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "radialBurned2", swordSettings.SwordHit.RadialBurned2.ToColor(), swordSettings.SwordHit.RadialBurned2.ToColor(), "SwordHit");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "radialLightRays", swordSettings.SwordHit.RadialLightRays.ToColor(), swordSettings.SwordHit.RadialLightRays.ToColor(), "SwordHit");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "radialMaskB(3)", swordSettings.SwordHit.RadialMaskB.ToColor(), swordSettings.SwordHit.RadialMaskB.ToColor(), "SwordHit");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "sparksLong", swordSettings.SwordHit.SparksLong.ToColor(), swordSettings.SwordHit.SparksLong.ToColor(), "SwordHit");
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "splashEdge", swordSettings.SwordHit.SplashEdge.ToColor(), swordSettings.SwordHit.SplashEdge.ToColor(), "SwordHit");
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "glow", swordSettings.SwordHit.LightGlow.ToColor(), swordSettings.SwordHit.LightGlow.ToColor(), "SwordHit");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "starSpike2", swordSettings.SwordHit.StarSpike2.ToColor(), swordSettings.SwordHit.StarSpike2.ToColor(), "SwordHit");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "CircleShape1", swordSettings.SwordHit.LightCircleShape.ToColor(), swordSettings.SwordHit.LightCircleShape.ToColor(), "SwordHit");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "glowUnmask (2)", swordSettings.SwordHit.GlowUnmask.ToColor(), swordSettings.SwordHit.GlowUnmask.ToColor(), "SwordHit");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "debrisParticle", swordSettings.SwordHit.DebrisParticles.ToColor(), swordSettings.SwordHit.DebrisParticles.ToColor(), "SwordHit");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "debrisParticleFallBig", swordSettings.SwordHit.DebrisParticlesFallBig.ToColor(), swordSettings.SwordHit.DebrisParticlesFallBig.ToColor(), "SwordHit");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "fxBox", swordSettings.SwordHit.FxBox.ToColor(), swordSettings.SwordHit.FxBox.ToColor(), "SwordHit");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "distortionNew", swordSettings.SwordHit.DistortionNew.ToColor(), swordSettings.SwordHit.DistortionNew.ToColor(), "SwordHit");
		}

		SeinVisualEditor::VisualSetting.SwordVisualSetting = swordSettings;
		SeinVisualEditor::VisualSettingsUpdated.HasUpdatedSword = true;
	}
}