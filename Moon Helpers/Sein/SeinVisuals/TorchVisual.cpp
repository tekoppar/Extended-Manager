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
		SeinVisualEditor::SetParticleRendererColor(sceneSeinLeftItemModel, sceneTorchFlame, torchSettings.TorchColor);
		std::vector < std::string> sceneTorchFireC = { "fireEffectStatic", "fireEffectA", "fireC" };
		SeinVisualEditor::SetMeshRendererColor(sceneSeinLeftItemModel, sceneTorchFireC, torchSettings.TorchColor);
		std::vector < std::string> sceneTorchTrailMesh = { "fireEffectStatic", "newTrail (2)" };
		SeinVisualEditor::SetMeshRendererColor(sceneSeinLeftItemModel, sceneTorchTrailMesh, torchSettings.TorchTrailMeshColor, (torchSettings.TorchTrailMeshEnable == true ? 1 : 0));
		std::vector < std::string> sceneTorchFireEffectMove = { "fireEffectStatic", "fireEffectmove" };
		SeinVisualEditor::SetParticleRendererColor(sceneSeinLeftItemModel, sceneTorchFireEffectMove, torchSettings.TorchRunningColor);
		std::vector<std::string> sceneTorchParticle = { "fireEffectStatic", "spriteSnowPettern2" };
		SeinVisualEditor::SetParticleRendererColor(seinLeftItem, sceneTorchParticle, torchSettings.TorchFloatingSparkColor);
		std::vector < std::string> sceneTorchParticle2 = { "fireEffectStatic", "spriteSnowPettern2", "spriteSnowPettern2" };
		SeinVisualEditor::SetParticleRendererColor(seinLeftItem, sceneTorchParticle2, torchSettings.TorchFloatingSparkColor);
		std::vector < std::string> sceneTorchLight = { "lightHolder", "CirlceShape1" };
		SeinVisualEditor::SetMeshRendererColor(sceneSeinLeftItemModel, sceneTorchLight, torchSettings.TorchColor);
		std::vector < std::string> sceneTorchGlow = { "lightHolder", "CirlceShape1", "glow" };
		SeinVisualEditor::SetMeshRendererColor(sceneSeinLeftItemModel, sceneTorchGlow, torchSettings.TorchColor);

		/*std::vector<std::string> groupNames = { "torchAttackAir1Effect", "torchAttackAir2Effect" , "torchAttackAir3Effect", "torchAttackGround1Effect", "torchAttackGround2Effect", "torchAttackGround3Effect", "torchBreakEffect", "torchHitEffect", "torchHitEffectSmall", "torchLightEffect", "torchSpark" };
		std::unordered_map<std::string, app::UberPoolGroup*> groupMap = SeinVisualEditor::GetUberGroups(groupNames);

		app::UberPoolGroup* uberPoolGroup = groupMap[groupNames[0]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			std::vector < std::string> torchAttackAir = { "trailBox", "fireSprite2" };
			SeinVisualEditor::SetMeshRendererColor(poolItem->fields.Target, torchAttackAir, torchSettings.TorchAirAttacks[0].FireSprite);
			std::vector < std::string> torchAttackAirTrail = { "trailBox", "trailZigzag" };
			SeinVisualEditor::SetMeshRendererColor(poolItem->fields.Target, torchAttackAirTrail, torchSettings.TorchAirAttacks[0].TrailZigZag);
		}

		uberPoolGroup = groupMap[groupNames[1]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			std::vector < std::string> torchAttackAir = { "trailBox", "fireSprite2" };
			SeinVisualEditor::SetMeshRendererColor(poolItem->fields.Target, torchAttackAir, torchSettings.TorchAirAttacks[1].FireSprite);
			std::vector < std::string> torchAttackAirTrail = { "trailBox", "trailZigzag" };
			SeinVisualEditor::SetMeshRendererColor(poolItem->fields.Target, torchAttackAirTrail, torchSettings.TorchAirAttacks[1].TrailZigZag);
		}

		uberPoolGroup = groupMap[groupNames[2]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			std::vector < std::string> torchAttackAir = { "trailBox", "fireSprite2" };
			SeinVisualEditor::SetMeshRendererColor(poolItem->fields.Target, torchAttackAir, torchSettings.TorchAirAttacks[2].FireSprite);
			std::vector < std::string> torchAttackAirTrail = { "trailBox", "trailZigzag" };
			SeinVisualEditor::SetMeshRendererColor(poolItem->fields.Target, torchAttackAirTrail, torchSettings.TorchAirAttacks[2].TrailZigZag);
		}

		uberPoolGroup = groupMap[groupNames[3]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			std::vector < std::string> torchAttackAir = { "trailBox", "fireSprite2" };
			SeinVisualEditor::SetMeshRendererColor(poolItem->fields.Target, torchAttackAir, torchSettings.TorchGroundAttacks[0].FireSprite);
			std::vector < std::string> torchAttackAirTrail = { "trailBox", "trailZigzag" };
			SeinVisualEditor::SetMeshRendererColor(poolItem->fields.Target, torchAttackAirTrail, torchSettings.TorchGroundAttacks[0].TrailZigZag);
		}

		uberPoolGroup = groupMap[groupNames[4]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			std::vector < std::string> torchAttackAir = { "trailBox", "fireSprite2" };
			SeinVisualEditor::SetMeshRendererColor(poolItem->fields.Target, torchAttackAir, torchSettings.TorchGroundAttacks[1].FireSprite);
			std::vector < std::string> torchAttackAirTrail = { "trailBox", "trailZigzag" };
			SeinVisualEditor::SetMeshRendererColor(poolItem->fields.Target, torchAttackAirTrail, torchSettings.TorchGroundAttacks[1].TrailZigZag);
		}

		uberPoolGroup = groupMap[groupNames[5]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			std::vector < std::string> torchAttackAir = { "trailBox", "fireSprite2" };
			SeinVisualEditor::SetMeshRendererColor(poolItem->fields.Target, torchAttackAir, torchSettings.TorchGroundAttacks[2].FireSprite);
			std::vector < std::string> torchAttackAirTrail = { "trailBox", "trailZigzag" };
			SeinVisualEditor::SetMeshRendererColor(poolItem->fields.Target, torchAttackAirTrail, torchSettings.TorchGroundAttacks[2].TrailZigZag);
		}

		uberPoolGroup = groupMap[groupNames[6]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			std::vector < std::string> torchAttackAir = { "acidParticles" };
			SeinVisualEditor::SetParticleRendererColor(poolItem->fields.Target, torchAttackAir, torchSettings.TorchBreak.AcidParticles);
			std::vector < std::string> torchAttackAirTrail = { "characterGlow" };
			SeinVisualEditor::SetMeshRendererColor(poolItem->fields.Target, torchAttackAirTrail, torchSettings.TorchBreak.CharacterGlow);
		}

		uberPoolGroup = groupMap[groupNames[7]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			std::vector < std::string> torchAttackAir = { "flame", "fireC" };
			SeinVisualEditor::SetMeshRendererColor(poolItem->fields.Target, torchAttackAir, torchSettings.TorchHit.FlameFireC);
			std::vector < std::string> torchAttackAirTrail = { "flame", "glow" };
			SeinVisualEditor::SetMeshRendererColor(poolItem->fields.Target, torchAttackAirTrail, torchSettings.TorchHit.FlameGlow);
			std::vector < std::string> fsBox = { "fsBox" };
			SeinVisualEditor::SetParticleRendererColor(poolItem->fields.Target, fsBox, torchSettings.TorchHit.FsBox);
			std::vector < std::string> fireEffect = { "fsBox", "fireEffect" };
			SeinVisualEditor::SetParticleRendererColor(poolItem->fields.Target, fireEffect, torchSettings.TorchHit.FireEffect);
			std::vector < std::string> fireEffect1 = { "fsBox", "fireEffect(1)" };
			SeinVisualEditor::SetParticleRendererColor(poolItem->fields.Target, fireEffect1, torchSettings.TorchHit.FireEffect2);
			std::vector < std::string> radialBurned = { "fsBox", "radialBurned" };
			SeinVisualEditor::SetParticleRendererColor(poolItem->fields.Target, radialBurned, torchSettings.TorchHit.RadialBurned);
			std::vector < std::string> radialBurned2 = { "fsBox", "radialBurned2" };
			SeinVisualEditor::SetParticleRendererColor(poolItem->fields.Target, radialBurned2, torchSettings.TorchHit.RadialBurned2);
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spriteSnowPettern2", torchSettings.TorchHit.SpriteSnowPattern);
			std::vector < std::string> glow = { "glow" };
			SeinVisualEditor::SetMeshRendererColor(poolItem->fields.Target, glow, torchSettings.TorchHit.Glow);
			std::vector < std::string> glowUnMask = { "glowUnmask" };
			SeinVisualEditor::SetMeshRendererColor(poolItem->fields.Target, glow, torchSettings.TorchHit.GlowUnmask);
		}

		uberPoolGroup = groupMap[groupNames[8]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			std::vector < std::string> torchAttackAir = { "flame", "fireC" };
			SeinVisualEditor::SetMeshRendererColor(poolItem->fields.Target, torchAttackAir, torchSettings.TorchHitSmall.FlameFireC);
			std::vector < std::string> torchAttackAirTrail = { "flame", "glow" };
			SeinVisualEditor::SetMeshRendererColor(poolItem->fields.Target, torchAttackAirTrail, torchSettings.TorchHitSmall.FlameGlow);
			std::vector < std::string> fsBox = { "fsBox" };
			SeinVisualEditor::SetParticleRendererColor(poolItem->fields.Target, fsBox, torchSettings.TorchHitSmall.FsBox);
			std::vector < std::string> fireEffect = { "fsBox", "fireEffect" };
			SeinVisualEditor::SetParticleRendererColor(poolItem->fields.Target, fireEffect, torchSettings.TorchHitSmall.FireEffect);
			std::vector < std::string> fireEffect1 = { "fsBox", "fireEffect(1)" };
			SeinVisualEditor::SetParticleRendererColor(poolItem->fields.Target, fireEffect1, torchSettings.TorchHitSmall.FireEffect2);
			std::vector < std::string> radialBurned = { "fsBox", "radialBurned" };
			SeinVisualEditor::SetParticleRendererColor(poolItem->fields.Target, radialBurned, torchSettings.TorchHitSmall.RadialBurned);
			std::vector < std::string> radialBurned2 = { "fsBox", "radialBurned2" };
			SeinVisualEditor::SetParticleRendererColor(poolItem->fields.Target, radialBurned2, torchSettings.TorchHitSmall.RadialBurned2);
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "spriteSnowPettern2", torchSettings.TorchHitSmall.SpriteSnowPattern);
			std::vector < std::string> glow = { "glow" };
			SeinVisualEditor::SetMeshRendererColor(poolItem->fields.Target, glow, torchSettings.TorchHitSmall.Glow);
			std::vector < std::string> glowUnMask = { "glowUnmask" };
			SeinVisualEditor::SetMeshRendererColor(poolItem->fields.Target, glow, torchSettings.TorchHitSmall.GlowUnmask);
		}

		uberPoolGroup = groupMap[groupNames[9]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			std::vector < std::string> torchAttackAir = { "CircleShape1" };
			SeinVisualEditor::SetMeshRendererColor(poolItem->fields.Target, torchAttackAir, torchSettings.TorchLightEffect);
		}

		uberPoolGroup = groupMap[groupNames[10]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			std::vector < std::string> torchAttackAir = { "redSpark" };
			SeinVisualEditor::SetParticleRendererColor(poolItem->fields.Target, torchAttackAir, torchSettings.TorchSpark);
		}

		groupMap.clear();*/
SeinVisualEditor::VisualSettings.TorchVisualSettings = torchSettings;
		SeinVisualEditor::VisualSettingsUpdated.HasUpdatedTorch = true;
	}
}