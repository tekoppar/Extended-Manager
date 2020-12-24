#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <filesystem>

#include "StringUtils.h"
#include "ManagerDef.h"
#include "UberStateManager.h"
#include "SeinVisualEditor.h"
#include "Tem.h"

#include "TorchVisual.h"

void TorchVisualSettings::SetTorchVisuals(TorchVisualSettings torchSettings)
{
	if (MDV::MoonSein->fields.Abilities->fields.HoldWrapper->fields.HasState == false || MDV::MoonSein->fields.Abilities->fields.HoldWrapper->fields.State->fields.m_currentHoldable == nullptr)
		return;

	if (MDV::MoonSein != nullptr && MDV::MoonSein->fields.Abilities->fields.ComboWrapper->fields.HasState == true &&
		MDV::MoonSein->fields.Abilities->fields.ComboWrapper->fields.State->fields.m_currentWeapon != nullptr &&
		MDV::MoonSein->fields.Abilities->fields.ComboWrapper->fields.State->fields.m_currentWeapon->fields.AbilityType == app::AbilityType__Enum::AbilityType__Enum_Torch)
	{
		app::String* TextureName = string_new("_MainTex");
		app::String* TextureName1 = string_new("_Color");
		app::String* EmiColor = string_new("_EmissivityColor");

		std::vector<std::string> sceneSeinLeftItem = { "ori3D", "mirrorHolder", "rigHolder", "oriRig", "Skeleton_GRP", "root_JNT", "pelvis_JNT", "spine_joint01_JNT", "ItemSlotPalmL" };
		app::GameObject* seinLeftItem = app::Component_1_get_gameObject((app::Component_1*)MDV::MoonSein, NULL);

		if (seinLeftItem == nullptr)
			return;

		app::GameObject* sceneSeinLeftItemModel = GetComponentByPath(seinLeftItem, sceneSeinLeftItem);

		if (sceneSeinLeftItemModel == nullptr)
			return;

		app::Type* meshRendererType = GetType("UnityEngine", "MeshRenderer");
		app::Type* skinnedMeshRendererType = GetType("UnityEngine", "SkinnedMeshRenderer");
		app::Type* particleRendererType = GetType("UnityEngine", "ParticleSystemRenderer");

		std::vector < std::string> sceneTorchFlame = { "fireEffectStatic", "fireEffectA", "flame" };
		SeinVisualEditor::SetParticleRendererColor(sceneSeinLeftItemModel, sceneTorchFlame, torchSettings.TorchColor, "Torch");
		std::vector < std::string> sceneTorchFireC = { "fireEffectStatic", "fireEffectA", "fireC" };
		SeinVisualEditor::SetMeshRendererColor(sceneSeinLeftItemModel, sceneTorchFireC, torchSettings.TorchColor, "Torch");
		std::vector < std::string> sceneTorchTrailMesh = { "fireEffectStatic", "newTrail (2)" };
		SeinVisualEditor::SetMeshRendererColor(sceneSeinLeftItemModel, sceneTorchTrailMesh, torchSettings.TorchTrailMeshColor, "Torch", (torchSettings.TorchTrailMeshEnable == true ? 1 : 0));
		std::vector < std::string> sceneTorchFireEffectMove = { "fireEffectStatic", "fireEffectmove" };
		SeinVisualEditor::SetParticleRendererColor(sceneSeinLeftItemModel, sceneTorchFireEffectMove, torchSettings.TorchRunningColor, "Torch");
		std::vector<std::string> sceneTorchParticle = { "fireEffectStatic", "spriteSnowPettern2" };
		SeinVisualEditor::SetParticleRendererColor(seinLeftItem, sceneTorchParticle, torchSettings.TorchFloatingSparkColor, "Torch");
		std::vector < std::string> sceneTorchParticle2 = { "fireEffectStatic", "spriteSnowPettern2", "spriteSnowPettern2" };
		SeinVisualEditor::SetParticleRendererColor(seinLeftItem, sceneTorchParticle2, torchSettings.TorchFloatingSparkColor, "Torch");
		std::vector < std::string> sceneTorchLight = { "lightHolder", "CirlceShape1" };
		SeinVisualEditor::SetMeshRendererColor(sceneSeinLeftItemModel, sceneTorchLight, torchSettings.TorchColor, "Torch");
		std::vector < std::string> sceneTorchGlow = { "lightHolder", "CirlceShape1", "glow" };
		SeinVisualEditor::SetMeshRendererColor(sceneSeinLeftItemModel, sceneTorchGlow, torchSettings.TorchColor, "Torch");

		std::vector<std::string> groupNames = { "torchAttackAir1Effect", "torchAttackAir2Effect" , "torchAttackAir3Effect", "torchAttackGround1Effect",
			"torchAttackGround2Effect", "torchAttackGround3Effect", "torchBreakEffect", "torchHitEffect", "torchHitEffectSmall" };
		std::unordered_map<std::string, app::UberPoolGroup*> groupMap = SeinVisualEditor::GetUberGroups(groupNames);

		app::UberPoolGroup* uberPoolGroup = groupMap[groupNames[0]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "fireSprite2", torchSettings.TorchAirAttacks[0].FireSprite.ToColor(), torchSettings.TorchAirAttacks[0].FireSprite.ToColor(), "torchAttackAir1Effect");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "trailZigzag", torchSettings.TorchAirAttacks[0].TrailZigZag.ToColor(), torchSettings.TorchAirAttacks[0].TrailZigZag.ToColor(), "torchAttackAir1Effect");
		}

		uberPoolGroup = groupMap[groupNames[1]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "fireSprite2", torchSettings.TorchAirAttacks[1].FireSprite.ToColor(), torchSettings.TorchAirAttacks[1].FireSprite.ToColor(), "torchAttackAir2Effect");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "trailZigzag", torchSettings.TorchAirAttacks[1].TrailZigZag.ToColor(), torchSettings.TorchAirAttacks[1].TrailZigZag.ToColor(), "torchAttackAir2Effect");
		}

		uberPoolGroup = groupMap[groupNames[2]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "fireSprite2", torchSettings.TorchAirAttacks[2].FireSprite.ToColor(), torchSettings.TorchAirAttacks[2].FireSprite.ToColor(), "torchAttackAir3Effect");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "trailZigzag", torchSettings.TorchAirAttacks[2].TrailZigZag.ToColor(), torchSettings.TorchAirAttacks[2].TrailZigZag.ToColor(), "torchAttackAir3Effect");
		}

		uberPoolGroup = groupMap[groupNames[3]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "fireSprite2", torchSettings.TorchGroundAttacks[0].FireSprite.ToColor(), torchSettings.TorchGroundAttacks[0].FireSprite.ToColor(), "torchAttackGround1Effect");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "trailZigzag", torchSettings.TorchGroundAttacks[0].TrailZigZag.ToColor(), torchSettings.TorchGroundAttacks[0].TrailZigZag.ToColor(), "torchAttackGround1Effect");
		}

		uberPoolGroup = groupMap[groupNames[4]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "fireSprite2", torchSettings.TorchGroundAttacks[1].FireSprite.ToColor(), torchSettings.TorchGroundAttacks[1].FireSprite.ToColor(), "torchAttackGround2Effect");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "trailZigzag", torchSettings.TorchGroundAttacks[1].TrailZigZag.ToColor(), torchSettings.TorchGroundAttacks[1].TrailZigZag.ToColor(), "torchAttackGround2Effect");
		}

		uberPoolGroup = groupMap[groupNames[5]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "fireSprite2", torchSettings.TorchGroundAttacks[2].FireSprite.ToColor(), torchSettings.TorchGroundAttacks[2].FireSprite.ToColor(), "torchAttackGround3Effect");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "trailZigzag", torchSettings.TorchGroundAttacks[2].TrailZigZag.ToColor(), torchSettings.TorchGroundAttacks[2].TrailZigZag.ToColor(), "torchAttackGround3Effect");
		}

		uberPoolGroup = groupMap[groupNames[6]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "acidParticles", torchSettings.TorchBreak.AcidParticles.ToColor(), torchSettings.TorchBreak.AcidParticles.ToColor(), "torchBreakEffect");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "characterGlow", torchSettings.TorchBreak.CharacterGlow.ToColor(), torchSettings.TorchBreak.CharacterGlow.ToColor(), "torchBreakEffect");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "smoke", torchSettings.TorchBreak.Smoke.ToColor(), torchSettings.TorchBreak.Smoke.ToColor(), "torchBreakEffect");
		}

		uberPoolGroup = groupMap[groupNames[7]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "fireEffect", torchSettings.TorchHit.FireEffect.ToColor(), torchSettings.TorchHit.FireEffect.ToColor(), "torchHitEffect");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "fireEffect (1)", torchSettings.TorchHit.FireEffect2.ToColor(), torchSettings.TorchHit.FireEffect2.ToColor(), "torchHitEffect");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "fireC", torchSettings.TorchHit.FlameFireC.ToColor(), torchSettings.TorchHit.FlameFireC.ToColor(), "torchHitEffect");
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "glow", torchSettings.TorchHit.FlameGlow.ToColor(), torchSettings.TorchHit.FlameGlow.ToColor(), "torchHitEffect");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "fxBox", torchSettings.TorchHit.FsBox.ToColor(), torchSettings.TorchHit.FsBox.ToColor(), "torchHitEffect");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "radialBurned", torchSettings.TorchHit.RadialBurned.ToColor(), torchSettings.TorchHit.RadialBurned.ToColor(), "torchHitEffect");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "radialBurned2", torchSettings.TorchHit.RadialBurned2.ToColor(), torchSettings.TorchHit.RadialBurned2.ToColor(), "torchHitEffect");
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spriteSnowPettern2", torchSettings.TorchHit.SpriteSnowPattern.ToColor(), torchSettings.TorchHit.SpriteSnowPattern.ToColor(), "torchHitEffect");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "glowUnmask", torchSettings.TorchHit.GlowUnmask.ToColor(), torchSettings.TorchHit.GlowUnmask.ToColor(), "torchHitEffect");
		}

		uberPoolGroup = groupMap[groupNames[8]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "fireEffect", torchSettings.TorchHitSmall.FireEffect.ToColor(), torchSettings.TorchHitSmall.FireEffect.ToColor(), "torchHitEffectSmall");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "fireEffect (1)", torchSettings.TorchHitSmall.FireEffect2.ToColor(), torchSettings.TorchHitSmall.FireEffect2.ToColor(), "torchHitEffectSmall");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "fireC", torchSettings.TorchHitSmall.FlameFireC.ToColor(), torchSettings.TorchHitSmall.FlameFireC.ToColor(), "torchHitEffectSmall");
			SeinVisualEditor::SetMeshRenderersColor(poolItem->fields.Target, "glow", torchSettings.TorchHitSmall.FlameGlow.ToColor(), torchSettings.TorchHitSmall.FlameGlow.ToColor(), "torchHitEffectSmall");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "fxBox", torchSettings.TorchHitSmall.FsBox.ToColor(), torchSettings.TorchHitSmall.FsBox.ToColor(), "torchHitEffectSmall");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "radialBurned", torchSettings.TorchHitSmall.RadialBurned.ToColor(), torchSettings.TorchHitSmall.RadialBurned.ToColor(), "torchHitEffectSmall");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "radialBurned2", torchSettings.TorchHitSmall.RadialBurned2.ToColor(), torchSettings.TorchHitSmall.RadialBurned2.ToColor(), "torchHitEffectSmall");
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spriteSnowPettern2", torchSettings.TorchHitSmall.SpriteSnowPattern.ToColor(), torchSettings.TorchHitSmall.SpriteSnowPattern.ToColor(), "torchHitEffectSmall");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "glowUnmask", torchSettings.TorchHitSmall.GlowUnmask.ToColor(), torchSettings.TorchHitSmall.GlowUnmask.ToColor(), "torchHitEffectSmall");
		}

		groupMap.clear();

		SeinVisualEditor::VisualSetting.TorchVisualSetting = torchSettings;
		SeinVisualEditor::VisualSettingsUpdated.HasUpdatedTorch = true;
	}
}