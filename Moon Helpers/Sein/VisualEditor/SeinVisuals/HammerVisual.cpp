#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <filesystem>

#include "StringUtils.h"
#include "ManagerDef.h"
#include "UberStateManager.h"
#include "SeinVisualEditor.h"
#include "Tem.h"

#include "HammerVisual.h"

void HammerVisualSettings::SetHammerVisuals(HammerVisualSettings hammerSettings)
{
	if (MDV::MoonSein != nullptr)
	{
		if (MDV::MoonSein != nullptr && MDV::MoonSein->fields.Abilities->fields.ComboWrapper->fields.HasState == true)
		{
			app::MeleeWeapon* sword = MDV::MoonSein->fields.Abilities->fields.ComboWrapper->fields.State->fields.Weapons->vector[0];
			app::MeleeWeaponHammer* meleeHammer = (app::MeleeWeaponHammer*)sword;
			SeinVisualEditor::SetSkinnedMeshRendererColor((app::SkinnedMeshRenderer*)meleeHammer->fields.HammerRenderer, "meleeHammer", hammerSettings.HammerColor, hammerSettings.HammerEmissiveColor, "Hammer");
		}

		std::vector<std::string> groupNames = { "hammerAttackAir1EffectV2", "hammerAttackAir2EffectV2", "hammerAttackAir3EffectV2",
		"hammerAttackAirUpSwipeEffect", "hammerAttackGround1EffectII", "hammerAttackGround2EffectII", "hammerAttackGroundDownV2",
		"hammerAttackGroundUpSwipeEffectV2", "hammerAttackStompEffect", "hammerAttackTrail", "hammerBlockEffect", "hammerHitEffect",
		"hammerShockwaveEffect", "hammerStompPreparationEffectNewV2"};
		std::unordered_map<std::string, app::UberPoolGroup*> groupMap = SeinVisualEditor::GetUberGroups(groupNames);

		app::UberPoolGroup* uberPoolGroup = groupMap[groupNames[0]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "fireSprite", hammerSettings.HammerAttackAir1.FireSprite.ToColor(), hammerSettings.HammerAttackAir1.FireSprite.ToColor(), "HammerAttackAir1");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "linearGradientMask", hammerSettings.HammerAttackAir1.LinearGradientMask.ToColor(), hammerSettings.HammerAttackAir1.LinearGradientMask.ToColor(), "HammerAttackAir1");
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "vignetteMaskC", hammerSettings.HammerAttackAir1.VignetteMaskC.ToColor(), hammerSettings.HammerAttackAir1.VignetteMaskC.ToColor(), "HammerAttackAir1");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "energyEffect", hammerSettings.HammerAttackAir1.EnergyEffect.ToColor(), hammerSettings.HammerAttackAir1.EnergyEffect.ToColor(), "HammerAttackAir1");
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spriteSnowPettern2", hammerSettings.HammerAttackAir1.SpriteSnowPettern2.ToColor(), hammerSettings.HammerAttackAir1.SpriteSnowPettern2.ToColor(), "HammerAttackAir1");
		}

		uberPoolGroup = groupMap[groupNames[1]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "fireSprite3Flip", hammerSettings.HammerAttackAir2.FireSprite.ToColor(), hammerSettings.HammerAttackAir2.FireSprite.ToColor(), "HammerAttackAir2");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "linearGradientMask", hammerSettings.HammerAttackAir2.LinearGradientMask.ToColor(), hammerSettings.HammerAttackAir2.LinearGradientMask.ToColor(), "HammerAttackAir2");
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "vignetteMaskC", hammerSettings.HammerAttackAir2.VignetteMaskC.ToColor(), hammerSettings.HammerAttackAir2.VignetteMaskC.ToColor(), "HammerAttackAir2");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "energyEffect", hammerSettings.HammerAttackAir2.EnergyEffect.ToColor(), hammerSettings.HammerAttackAir2.EnergyEffect.ToColor(), "HammerAttackAir2");
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spriteSnowPettern2", hammerSettings.HammerAttackAir2.SpriteSnowPettern2.ToColor(), hammerSettings.HammerAttackAir2.SpriteSnowPettern2.ToColor(), "HammerAttackAir2");
		}

		uberPoolGroup = groupMap[groupNames[2]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "fireSprite", hammerSettings.HammerAttackAir3.FireSprite.ToColor(), hammerSettings.HammerAttackAir3.FireSprite.ToColor(), "HammerAttackAir3");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "linearGradientMask", hammerSettings.HammerAttackAir3.LinearGradientMask.ToColor(), hammerSettings.HammerAttackAir3.LinearGradientMask.ToColor(), "HammerAttackAir3");
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "vignetteMaskC", hammerSettings.HammerAttackAir3.VignetteMaskC.ToColor(), hammerSettings.HammerAttackAir3.VignetteMaskC.ToColor(), "HammerAttackAir3");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "energyEffect", hammerSettings.HammerAttackAir3.EnergyEffect.ToColor(), hammerSettings.HammerAttackAir3.EnergyEffect.ToColor(), "HammerAttackAir3");
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spriteSnowPettern2", hammerSettings.HammerAttackAir3.SpriteSnowPettern2.ToColor(), hammerSettings.HammerAttackAir3.SpriteSnowPettern2.ToColor(), "HammerAttackAir3");
		}

		uberPoolGroup = groupMap[groupNames[3]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "fireSprite", hammerSettings.HammerAttackAirUpSwipe.FireSprite.ToColor(), hammerSettings.HammerAttackAirUpSwipe.FireSprite.ToColor(), "HammerAttackAirUpSwipe");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "linearGradientMask", hammerSettings.HammerAttackAirUpSwipe.LinearGradientMask.ToColor(), hammerSettings.HammerAttackAirUpSwipe.LinearGradientMask.ToColor(), "HammerAttackAirUpSwipe");
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "vignetteMaskC", hammerSettings.HammerAttackAirUpSwipe.VignetteMaskC.ToColor(), hammerSettings.HammerAttackAirUpSwipe.VignetteMaskC.ToColor(), "HammerAttackAirUpSwipe");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "energyEffect", hammerSettings.HammerAttackAirUpSwipe.EnergyEffect.ToColor(), hammerSettings.HammerAttackAirUpSwipe.EnergyEffect.ToColor(), "HammerAttackAirUpSwipe");
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spriteSnowPettern2", hammerSettings.HammerAttackAirUpSwipe.SpriteSnowPettern2.ToColor(), hammerSettings.HammerAttackAirUpSwipe.SpriteSnowPettern2.ToColor(), "HammerAttackAirUpSwipe");
		}

		uberPoolGroup = groupMap[groupNames[4]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "fireSprite", hammerSettings.HammerAttackGround.FireSprite.ToColor(), hammerSettings.HammerAttackGround.FireSprite.ToColor(), "HammerAttackGround");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "linearGradientMask", hammerSettings.HammerAttackGround.LinearGradientMask.ToColor(), hammerSettings.HammerAttackGround.LinearGradientMask.ToColor(), "HammerAttackGround");
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "vignetteMaskC", hammerSettings.HammerAttackGround.VignetteMaskC.ToColor(), hammerSettings.HammerAttackGround.VignetteMaskC.ToColor(), "HammerAttackGround");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "energyEffect", hammerSettings.HammerAttackGround.EnergyEffect.ToColor(), hammerSettings.HammerAttackGround.EnergyEffect.ToColor(), "HammerAttackGround");
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spriteSnowPettern2", hammerSettings.HammerAttackGround.SpriteSnowPettern2.ToColor(), hammerSettings.HammerAttackGround.SpriteSnowPettern2.ToColor(), "HammerAttackGround");
		}

		uberPoolGroup = groupMap[groupNames[5]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "fireSprite3Flip", hammerSettings.HammerAttackGround2.FireSprite.ToColor(), hammerSettings.HammerAttackGround2.FireSprite.ToColor(), "HammerAttackGround2");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "linearGradientMask", hammerSettings.HammerAttackGround2.LinearGradientMask.ToColor(), hammerSettings.HammerAttackGround2.LinearGradientMask.ToColor(), "HammerAttackGround2");
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "vignetteMaskC", hammerSettings.HammerAttackGround2.VignetteMaskC.ToColor(), hammerSettings.HammerAttackGround2.VignetteMaskC.ToColor(), "HammerAttackGround2");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "energyEffect", hammerSettings.HammerAttackGround2.EnergyEffect.ToColor(), hammerSettings.HammerAttackGround2.EnergyEffect.ToColor(), "HammerAttackGround2");
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spriteSnowPettern2", hammerSettings.HammerAttackGround2.SpriteSnowPettern2.ToColor(), hammerSettings.HammerAttackGround2.SpriteSnowPettern2.ToColor(), "HammerAttackGround2");
		}

		uberPoolGroup = groupMap[groupNames[6]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "fireSprite3Flip", hammerSettings.HammerAttackGroundDown.FireSprite.ToColor(), hammerSettings.HammerAttackGroundDown.FireSprite.ToColor(), "HammerAttackGroundDown");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "linearGradientMask", hammerSettings.HammerAttackGroundDown.LinearGradientMask.ToColor(), hammerSettings.HammerAttackGroundDown.LinearGradientMask.ToColor(), "HammerAttackGroundDown");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "vignetteMaskC", hammerSettings.HammerAttackGroundDown.VignetteMaskC.ToColor(), hammerSettings.HammerAttackGroundDown.VignetteMaskC.ToColor(), "HammerAttackGroundDown");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "energyEffect", hammerSettings.HammerAttackGroundDown.EnergyEffect.ToColor(), hammerSettings.HammerAttackGroundDown.EnergyEffect.ToColor(), "HammerAttackGroundDown");
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spriteSnowPettern2", hammerSettings.HammerAttackGroundDown.SpriteSnowPettern2.ToColor(), hammerSettings.HammerAttackGroundDown.SpriteSnowPettern2.ToColor(), "HammerAttackGroundDown");
		}

		uberPoolGroup = groupMap[groupNames[7]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "fireSprite", hammerSettings.HammerAttackGroundUpSwipe.FireSprite.ToColor(), hammerSettings.HammerAttackGroundUpSwipe.FireSprite.ToColor(), "HammerAttackGroundUpSwipe");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "linearGradientMask", hammerSettings.HammerAttackGroundUpSwipe.LinearGradientMask.ToColor(), hammerSettings.HammerAttackGroundUpSwipe.LinearGradientMask.ToColor(), "HammerAttackGroundUpSwipe");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "vignetteMaskC", hammerSettings.HammerAttackGroundUpSwipe.VignetteMaskC.ToColor(), hammerSettings.HammerAttackGroundUpSwipe.VignetteMaskC.ToColor(), "HammerAttackGroundUpSwipe");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "energyEffect", hammerSettings.HammerAttackGroundUpSwipe.EnergyEffect.ToColor(), hammerSettings.HammerAttackGroundUpSwipe.EnergyEffect.ToColor(), "HammerAttackGroundUpSwipe");
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spriteSnowPettern2", hammerSettings.HammerAttackGroundUpSwipe.SpriteSnowPettern2.ToColor(), hammerSettings.HammerAttackGroundUpSwipe.SpriteSnowPettern2.ToColor(), "HammerAttackGroundUpSwipe");
		}

		uberPoolGroup = groupMap[groupNames[8]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "glow", hammerSettings.HammerAttackStomp.Glow.ToColor(), hammerSettings.HammerAttackStomp.Glow.ToColor(), "HammerAttackStomp");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "theGiftLeafTransformationLightRing", hammerSettings.HammerAttackStomp.GiftLeafTransformationLightRing.ToColor(), hammerSettings.HammerAttackStomp.GiftLeafTransformationLightRing.ToColor(), "HammerAttackStomp");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "glow(1)", hammerSettings.HammerAttackStomp.Glow1.ToColor(), hammerSettings.HammerAttackStomp.Glow1.ToColor(), "HammerAttackStomp");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "smoke", hammerSettings.HammerAttackStomp.Smoke.ToColor(), hammerSettings.HammerAttackStomp.Smoke.ToColor(), "HammerAttackStomp");
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "sharedSingleSnowParticleA", hammerSettings.HammerAttackStomp.SingleSnowParticleA.ToColor(), hammerSettings.HammerAttackStomp.SingleSnowParticleA.ToColor(), "HammerAttackStomp");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "debrisParticles", hammerSettings.HammerAttackStomp.DebrisParticles.ToColor(), hammerSettings.HammerAttackStomp.DebrisParticles.ToColor(), "HammerAttackStomp");
		}

		uberPoolGroup = groupMap[groupNames[10]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "acidParticles", hammerSettings.HammerBlock.AcidParticles.ToColor(), hammerSettings.HammerBlock.AcidParticles.ToColor(), "HammerBlock");
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "glow", hammerSettings.HammerBlock.Glow.ToColor(), hammerSettings.HammerBlock.Glow.ToColor(), "HammerBlock");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "characterGlow", hammerSettings.HammerBlock.CharacterGlow.ToColor(), hammerSettings.HammerBlock.CharacterGlow.ToColor(), "HammerBlock");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "circle", hammerSettings.HammerBlock.Circle.ToColor(), hammerSettings.HammerBlock.Circle.ToColor(), "HammerBlock");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "sharedLavaFountainA", hammerSettings.HammerBlock.LavaFountainA.ToColor(), hammerSettings.HammerBlock.LavaFountainA.ToColor(), "HammerBlock");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "sharedSingleSnowParticleA", hammerSettings.HammerBlock.SingleSnowParticleA.ToColor(), hammerSettings.HammerBlock.SingleSnowParticleA.ToColor(), "HammerBlock");
		}

		uberPoolGroup = groupMap[groupNames[11]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "distortionNew", hammerSettings.HammerHit.DistortionNew.ToColor(), hammerSettings.HammerHit.DistortionNew.ToColor(), "HammerHit");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "fxBox", hammerSettings.HammerHit.FxBox.ToColor(), hammerSettings.HammerHit.FxBox.ToColor(), "HammerHit");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "glow", hammerSettings.HammerHit.Glow.ToColor(), hammerSettings.HammerHit.Glow.ToColor(), "HammerHit");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "debrisParticles", hammerSettings.HammerHit.DebrisParticles.ToColor(), hammerSettings.HammerHit.DebrisParticles.ToColor(), "HammerHit");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "debrisParticles (1)", hammerSettings.HammerHit.DebrisParticles1.ToColor(), hammerSettings.HammerHit.DebrisParticles1.ToColor(), "HammerHit");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "debrisParticles (2)", hammerSettings.HammerHit.DebrisParticles2.ToColor(), hammerSettings.HammerHit.DebrisParticles2.ToColor(), "HammerHit");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "debrisParticles (3)", hammerSettings.HammerHit.DebrisParticles3.ToColor(), hammerSettings.HammerHit.DebrisParticles3.ToColor(), "HammerHit");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "debrisParticlesFallBig", hammerSettings.HammerHit.DebrisParticlesFallBig.ToColor(), hammerSettings.HammerHit.DebrisParticlesFallBig.ToColor(), "HammerHit");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "glowUnmask (1)", hammerSettings.HammerHit.GlowUnmask.ToColor(), hammerSettings.HammerHit.GlowUnmask.ToColor(), "HammerHit");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "kuroNestEggCrackD", hammerSettings.HammerHit.KuroNestEggCrackD.ToColor(), hammerSettings.HammerHit.KuroNestEggCrackD.ToColor(), "HammerHit");
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "lensFlare20b", hammerSettings.HammerHit.LensFlare20b.ToColor(), hammerSettings.HammerHit.LensFlare20b.ToColor(), "HammerHit");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "lensFlare3", hammerSettings.HammerHit.LensFlare3.ToColor(), hammerSettings.HammerHit.LensFlare3.ToColor(), "HammerHit");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "lensFlare9", hammerSettings.HammerHit.LensFlare9.ToColor(), hammerSettings.HammerHit.LensFlare9.ToColor(), "HammerHit");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "lensRadialSpike", hammerSettings.HammerHit.LensRadialSpike.ToColor(), hammerSettings.HammerHit.LensRadialSpike.ToColor(), "HammerHit");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "radialBurned2", hammerSettings.HammerHit.RadialBurned2.ToColor(), hammerSettings.HammerHit.RadialBurned2.ToColor(), "HammerHit");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "radialIrisImpact", hammerSettings.HammerHit.RadialIrisImpact.ToColor(), hammerSettings.HammerHit.RadialIrisImpact.ToColor(), "HammerHit");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "radialLightRays", hammerSettings.HammerHit.RadialLightRays.ToColor(), hammerSettings.HammerHit.RadialLightRays.ToColor(), "HammerHit");
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "radialMaskB (4)", hammerSettings.HammerHit.RadialMaskB.ToColor(), hammerSettings.HammerHit.RadialMaskB.ToColor(), "HammerHit");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "spikeHitLarge (3)", hammerSettings.HammerHit.SpikeHitLarge1.ToColor(), hammerSettings.HammerHit.SpikeHitLarge1.ToColor(), "HammerHit");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "spikeHitLarge (4)", hammerSettings.HammerHit.SpikeHitLarge2.ToColor(), hammerSettings.HammerHit.SpikeHitLarge2.ToColor(), "HammerHit");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "spriteheetParticleShape", hammerSettings.HammerHit.ParticleShape.ToColor(), hammerSettings.HammerHit.ParticleShape.ToColor(), "HammerHit");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "starSpike2", hammerSettings.HammerHit.StarSpike2.ToColor(), hammerSettings.HammerHit.StarSpike2.ToColor(), "HammerHit");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "vignetteMaskC", hammerSettings.HammerHit.VignetteMaskC.ToColor(), hammerSettings.HammerHit.VignetteMaskC.ToColor(), "HammerHit");
		}

		uberPoolGroup = groupMap[groupNames[12]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "atlantisRockFarBackgroundAg", hammerSettings.HammerShockwave.AtlantisRockFarBackgroundAg.ToColor(), hammerSettings.HammerShockwave.AtlantisRockFarBackgroundAg.ToColor(), "HammerShockwave");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "bulletGlow (1)", hammerSettings.HammerShockwave.BulletGlow.ToColor(), hammerSettings.HammerShockwave.BulletGlow.ToColor(), "HammerShockwave");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "fxBox", hammerSettings.HammerShockwave.FxBox.ToColor(), hammerSettings.HammerShockwave.FxBox.ToColor(), "HammerShockwave");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "radialMaskB (1)", hammerSettings.HammerShockwave.RadialMaskB.ToColor(), hammerSettings.HammerShockwave.RadialMaskB.ToColor(), "HammerShockwave");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "sharedSmokeA", hammerSettings.HammerShockwave.SharedSmokeA.ToColor(), hammerSettings.HammerShockwave.SharedSmokeA.ToColor(), "HammerShockwave");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "sparks", hammerSettings.HammerShockwave.Sparks.ToColor(), hammerSettings.HammerShockwave.Sparks.ToColor(), "HammerShockwave");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "splashEdge2localOrient", hammerSettings.HammerShockwave.SplashEdge2localOrient.ToColor(), hammerSettings.HammerShockwave.SplashEdge2localOrient.ToColor(), "HammerShockwave");
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spritesheetSpikes", hammerSettings.HammerShockwave.SpritesheetSpikes.ToColor(), hammerSettings.HammerShockwave.SpritesheetSpikes.ToColor(), "HammerShockwave");
		}

		uberPoolGroup = groupMap[groupNames[13]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "fireSprite3Flip", hammerSettings.HammerStompPreparation.FireSprite3Flip.ToColor(), hammerSettings.HammerStompPreparation.FireSprite3Flip.ToColor(), "HammerStompPreparation");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "vignetteMaskC", hammerSettings.HammerStompPreparation.VignetteMaskC.ToColor(), hammerSettings.HammerStompPreparation.VignetteMaskC.ToColor(), "HammerStompPreparation");
		}

		SeinVisualEditor::VisualSetting.HammerVisualSetting = hammerSettings;
		SeinVisualEditor::VisualSettingsUpdated.HasUpdatedHammer = true;
	}
}