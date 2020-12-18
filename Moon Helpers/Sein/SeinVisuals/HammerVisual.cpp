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
			SeinVisualEditor::SetSkinnedMeshRendererColor((app::SkinnedMeshRenderer*)meleeHammer->fields.HammerRenderer, "meleeHammer", hammerSettings.HammerColor, hammerSettings.HammerEmissiveColor);
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
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "fireSprite", hammerSettings.HammerAttackAir1.FireSprite.ToColor(), hammerSettings.HammerAttackAir1.FireSprite.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "linearGradientMask", hammerSettings.HammerAttackAir1.LinearGradientMask.ToColor(), hammerSettings.HammerAttackAir1.LinearGradientMask.ToColor());
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "vignetteMaskC", hammerSettings.HammerAttackAir1.VignetteMaskC.ToColor(), hammerSettings.HammerAttackAir1.VignetteMaskC.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "energyEffect", hammerSettings.HammerAttackAir1.EnergyEffect.ToColor(), hammerSettings.HammerAttackAir1.EnergyEffect.ToColor());
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spriteSnowPettern2", hammerSettings.HammerAttackAir1.SpriteSnowPettern2.ToColor(), hammerSettings.HammerAttackAir1.SpriteSnowPettern2.ToColor());
		}

		uberPoolGroup = groupMap[groupNames[1]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "fireSprite3Flip", hammerSettings.HammerAttackAir2.FireSprite.ToColor(), hammerSettings.HammerAttackAir2.FireSprite.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "linearGradientMask", hammerSettings.HammerAttackAir2.LinearGradientMask.ToColor(), hammerSettings.HammerAttackAir2.LinearGradientMask.ToColor());
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "vignetteMaskC", hammerSettings.HammerAttackAir2.VignetteMaskC.ToColor(), hammerSettings.HammerAttackAir2.VignetteMaskC.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "energyEffect", hammerSettings.HammerAttackAir2.EnergyEffect.ToColor(), hammerSettings.HammerAttackAir2.EnergyEffect.ToColor());
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spriteSnowPettern2", hammerSettings.HammerAttackAir2.SpriteSnowPettern2.ToColor(), hammerSettings.HammerAttackAir2.SpriteSnowPettern2.ToColor());
		}

		uberPoolGroup = groupMap[groupNames[2]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "fireSprite", hammerSettings.HammerAttackAir3.FireSprite.ToColor(), hammerSettings.HammerAttackAir3.FireSprite.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "linearGradientMask", hammerSettings.HammerAttackAir3.LinearGradientMask.ToColor(), hammerSettings.HammerAttackAir3.LinearGradientMask.ToColor());
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "vignetteMaskC", hammerSettings.HammerAttackAir3.VignetteMaskC.ToColor(), hammerSettings.HammerAttackAir3.VignetteMaskC.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "energyEffect", hammerSettings.HammerAttackAir3.EnergyEffect.ToColor(), hammerSettings.HammerAttackAir3.EnergyEffect.ToColor());
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spriteSnowPettern2", hammerSettings.HammerAttackAir3.SpriteSnowPettern2.ToColor(), hammerSettings.HammerAttackAir3.SpriteSnowPettern2.ToColor());
		}

		uberPoolGroup = groupMap[groupNames[3]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "fireSprite", hammerSettings.HammerAttackAirUpSwipe.FireSprite.ToColor(), hammerSettings.HammerAttackAirUpSwipe.FireSprite.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "linearGradientMask", hammerSettings.HammerAttackAirUpSwipe.LinearGradientMask.ToColor(), hammerSettings.HammerAttackAirUpSwipe.LinearGradientMask.ToColor());
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "vignetteMaskC", hammerSettings.HammerAttackAirUpSwipe.VignetteMaskC.ToColor(), hammerSettings.HammerAttackAirUpSwipe.VignetteMaskC.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "energyEffect", hammerSettings.HammerAttackAirUpSwipe.EnergyEffect.ToColor(), hammerSettings.HammerAttackAirUpSwipe.EnergyEffect.ToColor());
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spriteSnowPettern2", hammerSettings.HammerAttackAirUpSwipe.SpriteSnowPettern2.ToColor(), hammerSettings.HammerAttackAirUpSwipe.SpriteSnowPettern2.ToColor());
		}

		uberPoolGroup = groupMap[groupNames[4]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "fireSprite", hammerSettings.HammerAttackGround.FireSprite.ToColor(), hammerSettings.HammerAttackGround.FireSprite.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "linearGradientMask", hammerSettings.HammerAttackGround.LinearGradientMask.ToColor(), hammerSettings.HammerAttackGround.LinearGradientMask.ToColor());
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "vignetteMaskC", hammerSettings.HammerAttackGround.VignetteMaskC.ToColor(), hammerSettings.HammerAttackGround.VignetteMaskC.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "energyEffect", hammerSettings.HammerAttackGround.EnergyEffect.ToColor(), hammerSettings.HammerAttackGround.EnergyEffect.ToColor());
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spriteSnowPettern2", hammerSettings.HammerAttackGround.SpriteSnowPettern2.ToColor(), hammerSettings.HammerAttackGround.SpriteSnowPettern2.ToColor());
		}

		uberPoolGroup = groupMap[groupNames[5]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "fireSprite3Flip", hammerSettings.HammerAttackGround2.FireSprite.ToColor(), hammerSettings.HammerAttackGround2.FireSprite.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "linearGradientMask", hammerSettings.HammerAttackGround2.LinearGradientMask.ToColor(), hammerSettings.HammerAttackGround2.LinearGradientMask.ToColor());
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "vignetteMaskC", hammerSettings.HammerAttackGround2.VignetteMaskC.ToColor(), hammerSettings.HammerAttackGround2.VignetteMaskC.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "energyEffect", hammerSettings.HammerAttackGround2.EnergyEffect.ToColor(), hammerSettings.HammerAttackGround2.EnergyEffect.ToColor());
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spriteSnowPettern2", hammerSettings.HammerAttackGround2.SpriteSnowPettern2.ToColor(), hammerSettings.HammerAttackGround2.SpriteSnowPettern2.ToColor());
		}

		uberPoolGroup = groupMap[groupNames[6]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "fireSprite3Flip", hammerSettings.HammerAttackGroundDown.FireSprite.ToColor(), hammerSettings.HammerAttackGroundDown.FireSprite.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "linearGradientMask", hammerSettings.HammerAttackGroundDown.LinearGradientMask.ToColor(), hammerSettings.HammerAttackGroundDown.LinearGradientMask.ToColor());
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "vignetteMaskC", hammerSettings.HammerAttackGroundDown.VignetteMaskC.ToColor(), hammerSettings.HammerAttackGroundDown.VignetteMaskC.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "energyEffect", hammerSettings.HammerAttackGroundDown.EnergyEffect.ToColor(), hammerSettings.HammerAttackGroundDown.EnergyEffect.ToColor());
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spriteSnowPettern2", hammerSettings.HammerAttackGroundDown.SpriteSnowPettern2.ToColor(), hammerSettings.HammerAttackGroundDown.SpriteSnowPettern2.ToColor());
		}

		uberPoolGroup = groupMap[groupNames[7]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "fireSprite", hammerSettings.HammerAttackGroundUpSwipe.FireSprite.ToColor(), hammerSettings.HammerAttackGroundUpSwipe.FireSprite.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "linearGradientMask", hammerSettings.HammerAttackGroundUpSwipe.LinearGradientMask.ToColor(), hammerSettings.HammerAttackGroundUpSwipe.LinearGradientMask.ToColor());
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "vignetteMaskC", hammerSettings.HammerAttackGroundUpSwipe.VignetteMaskC.ToColor(), hammerSettings.HammerAttackGroundUpSwipe.VignetteMaskC.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "energyEffect", hammerSettings.HammerAttackGroundUpSwipe.EnergyEffect.ToColor(), hammerSettings.HammerAttackGroundUpSwipe.EnergyEffect.ToColor());
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spriteSnowPettern2", hammerSettings.HammerAttackGroundUpSwipe.SpriteSnowPettern2.ToColor(), hammerSettings.HammerAttackGroundUpSwipe.SpriteSnowPettern2.ToColor());
		}

		uberPoolGroup = groupMap[groupNames[8]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "glow", hammerSettings.HammerAttackStomp.Glow.ToColor(), hammerSettings.HammerAttackStomp.Glow.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "theGiftLeafTransformationLightRing", hammerSettings.HammerAttackStomp.GiftLeafTransformationLightRing.ToColor(), hammerSettings.HammerAttackStomp.GiftLeafTransformationLightRing.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "glow(1)", hammerSettings.HammerAttackStomp.Glow1.ToColor(), hammerSettings.HammerAttackStomp.Glow1.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "smoke", hammerSettings.HammerAttackStomp.Smoke.ToColor(), hammerSettings.HammerAttackStomp.Smoke.ToColor());
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "sharedSingleSnowParticleA", hammerSettings.HammerAttackStomp.SingleSnowParticleA.ToColor(), hammerSettings.HammerAttackStomp.SingleSnowParticleA.ToColor());
		}

		uberPoolGroup = groupMap[groupNames[10]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "acidParticles", hammerSettings.HammerBlock.AcidParticles.ToColor(), hammerSettings.HammerBlock.AcidParticles.ToColor());
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "glow", hammerSettings.HammerBlock.Glow.ToColor(), hammerSettings.HammerBlock.Glow.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "characterGlow", hammerSettings.HammerBlock.CharacterGlow.ToColor(), hammerSettings.HammerBlock.CharacterGlow.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "circle", hammerSettings.HammerBlock.Circle.ToColor(), hammerSettings.HammerBlock.Circle.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "sharedLavaFountainA", hammerSettings.HammerBlock.LavaFountainA.ToColor(), hammerSettings.HammerBlock.LavaFountainA.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "sharedSingleSnowParticleA", hammerSettings.HammerBlock.SingleSnowParticleA.ToColor(), hammerSettings.HammerBlock.SingleSnowParticleA.ToColor());
		}

		uberPoolGroup = groupMap[groupNames[11]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "distortionNew", hammerSettings.HammerHit.DistortionNew.ToColor(), hammerSettings.HammerHit.DistortionNew.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "fxBox", hammerSettings.HammerHit.FxBox.ToColor(), hammerSettings.HammerHit.FxBox.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "glow", hammerSettings.HammerHit.Glow.ToColor(), hammerSettings.HammerHit.Glow.ToColor());
		}

		uberPoolGroup = groupMap[groupNames[13]];
		hammerSettings.HammerStompPreparation.FireSprite3Flip *= 0.003;
		hammerSettings.HammerStompPreparation.VignetteMaskC *= 0.003;
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "fireSprite3Flip", hammerSettings.HammerStompPreparation.FireSprite3Flip.ToColor(), hammerSettings.HammerStompPreparation.FireSprite3Flip.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "vignetteMaskC", hammerSettings.HammerStompPreparation.VignetteMaskC.ToColor(), hammerSettings.HammerStompPreparation.VignetteMaskC.ToColor());
		}

		SeinVisualEditor::VisualSettings.HammerVisualSettings = hammerSettings;
		SeinVisualEditor::VisualSettingsUpdated.HasUpdatedHammer = true;
	}
}