#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <filesystem>

#include "StringUtils.h"
#include "ManagerDef.h"
#include "UberStateManager.h"
#include "SeinVisualEditor.h"
#include "Tem.h"

#include "BowVisual.h"

void BowVisualSettings::SetBowVisuals(BowVisualSettings bowSettings)
{
	if (MDV::MoonSein != nullptr)
	{
		if (MDV::MoonSein->fields.Prefabs->fields.Bow->fields.m_gameObject != nullptr)
		{
			SeinVisualEditor::SetSkinnedMeshRendererColorByName(MDV::MoonSein->fields.Prefabs->fields.Bow->fields.m_gameObject, "Bow_Shaft_MDL", (bowSettings.BowShaftColor * 2).ToColor(), (bowSettings.BowShaftEmissiveColor).ToColor(), "Bow");
		}

		if (MDV::MoonSein->fields.Prefabs->fields.Bow->fields.m_gameObject != nullptr)
		{
			SeinVisualEditor::SetSkinnedMeshRendererColorByName(MDV::MoonSein->fields.Prefabs->fields.Bow->fields.m_gameObject, "Bow_String_MDL", (bowSettings.BowStringColor * 2).ToColor(), (bowSettings.BowStringEmissiveColor).ToColor(), "Bow");
		}

		std::vector<std::string> groupNames = { "arrow", "arrowHitEffect", "arrowTrail" };
		std::unordered_map<std::string, app::UberPoolGroup*> groupMap = SeinVisualEditor::GetUberGroups(groupNames);

		app::UberPoolGroup* uberPoolGroup = groupMap[groupNames[0]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "effect", bowSettings.ArrowVisualSettings.ArrowEffectColor.ToColor(), bowSettings.ArrowVisualSettings.ArrowEffectEmissiveColor.ToColor(), "ArrowVisualSettings");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "spear", bowSettings.ArrowVisualSettings.ArrowSpearColor.ToColor(), bowSettings.ArrowVisualSettings.ArrowSpearEmissiveColor.ToColor(), "ArrowVisualSettings");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "caveLaserSpawnerLaserbeamImpactGlowA", bowSettings.ArrowVisualSettings.TipImpactColor.ToColor(), bowSettings.ArrowVisualSettings.TipImpactEmissiveColor.ToColor(), "ArrowVisualSettings");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "sharedSingleSnowParticleA", bowSettings.ArrowVisualSettings.TipParticleColor.ToColor(), bowSettings.ArrowVisualSettings.TipParticleEmissiveColor.ToColor(), "ArrowVisualSettings");
		}

		uberPoolGroup = groupMap[groupNames[1]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "distortionNew", bowSettings.ArrowHitVisualSettings.DistortionNew.ToColor(), bowSettings.ArrowHitVisualSettings.DistortionNew.ToColor(), "ArrowHitVisualSettings");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "fxBox", bowSettings.ArrowHitVisualSettings.FxBox.ToColor(), bowSettings.ArrowHitVisualSettings.FxBox.ToColor(), "ArrowHitVisualSettings");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "bloodSplat", bowSettings.ArrowHitVisualSettings.BloodSplat.ToColor(), bowSettings.ArrowHitVisualSettings.BloodSplat.ToColor(), "ArrowHitVisualSettings");
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "debrisParticles", bowSettings.ArrowHitVisualSettings.DebrisParticles.ToColor(), bowSettings.ArrowHitVisualSettings.DebrisParticles.ToColor(), "ArrowHitVisualSettings");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "debrisParticlesFallBig", bowSettings.ArrowHitVisualSettings.DebrisParticlesFallBig.ToColor(), bowSettings.ArrowHitVisualSettings.DebrisParticlesFallBig.ToColor(), "ArrowHitVisualSettings");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "glowUnmask (2)", bowSettings.ArrowHitVisualSettings.GlowUnmask.ToColor(), bowSettings.ArrowHitVisualSettings.GlowUnmask.ToColor(), "ArrowHitVisualSettings");
			SeinVisualEditor::SetParticleRenderersColor(poolItem->fields.Target, "lensFlare20b", bowSettings.ArrowHitVisualSettings.LensFlare20b.ToColor(), bowSettings.ArrowHitVisualSettings.LensFlare20b.ToColor(), "ArrowHitVisualSettings");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "lensFlare9", bowSettings.ArrowHitVisualSettings.LensFlare9.ToColor(), bowSettings.ArrowHitVisualSettings.LensFlare9.ToColor(), "ArrowHitVisualSettings");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "radialBurned", bowSettings.ArrowHitVisualSettings.RadialBurned.ToColor(), bowSettings.ArrowHitVisualSettings.RadialBurned.ToColor(), "ArrowHitVisualSettings");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "radialBurned2", bowSettings.ArrowHitVisualSettings.RadialBurned2.ToColor(), bowSettings.ArrowHitVisualSettings.RadialBurned2.ToColor(), "ArrowHitVisualSettings");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "radialIrisImpact", bowSettings.ArrowHitVisualSettings.RadialIrisImpact.ToColor(), bowSettings.ArrowHitVisualSettings.RadialIrisImpact.ToColor(), "ArrowHitVisualSettings");
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "starSpike2", bowSettings.ArrowHitVisualSettings.StarSpike2.ToColor(), bowSettings.ArrowHitVisualSettings.StarSpike2.ToColor(), "ArrowHitVisualSettings");
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "vignetteMaskC", bowSettings.ArrowHitVisualSettings.VignetteMaskC.ToColor(), bowSettings.ArrowHitVisualSettings.VignetteMaskC.ToColor(), "ArrowHitVisualSettings");
		}

		uberPoolGroup = groupMap[groupNames[2]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "arrowTrail(Clone)", bowSettings.ArrowVisualSettings.ArrowTrail.ToColor(), bowSettings.ArrowVisualSettings.ArrowTrailEmissive.ToColor(), "ArrowVisualSettings");
		}

		SeinVisualEditor::VisualSetting.BowVisualSetting = bowSettings;
		SeinVisualEditor::VisualSettingsUpdated.HasUpdatedBow = true;
	}
}