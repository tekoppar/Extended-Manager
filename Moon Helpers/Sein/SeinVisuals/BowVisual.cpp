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
			SeinVisualEditor::SetSkinnedMeshRendererColorByName(MDV::MoonSein->fields.Prefabs->fields.Bow->fields.m_gameObject, "Bow_Shaft_MDL", (bowSettings.BowShaftColor * 2).ToColor(), (bowSettings.BowShaftEmissiveColor).ToColor());
		}

		if (MDV::MoonSein->fields.Prefabs->fields.Bow->fields.m_gameObject != nullptr)
		{
			SeinVisualEditor::SetSkinnedMeshRendererColorByName(MDV::MoonSein->fields.Prefabs->fields.Bow->fields.m_gameObject, "Bow_String_MDL", (bowSettings.BowStringColor * 2).ToColor(), (bowSettings.BowStringEmissiveColor).ToColor());
		}

		std::vector<std::string> groupNames = { "arrow" };
		std::unordered_map<std::string, app::UberPoolGroup*> groupMap = SeinVisualEditor::GetUberGroups(groupNames);

		app::UberPoolGroup* uberPoolGroup = groupMap[groupNames[0]];
		for (int i = 0; i < uberPoolGroup->fields.m_poolObjects->fields._size; i++)
		{
			app::UberPoolItem* poolItem = uberPoolGroup->fields.m_poolObjects->fields._items->vector[i];
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "effect", bowSettings.ArrowVisualSettings.ArrowEffectColor.ToColor(), bowSettings.ArrowVisualSettings.ArrowEffectEmissiveColor.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(poolItem->fields.Target, "spear", bowSettings.ArrowVisualSettings.ArrowSpearColor.ToColor(), bowSettings.ArrowVisualSettings.ArrowSpearEmissiveColor.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "caveLaserSpawnerLaserbeamImpactGlowA", bowSettings.ArrowVisualSettings.TipImpactColor.ToColor(), bowSettings.ArrowVisualSettings.TipImpactEmissiveColor.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(poolItem->fields.Target, "sharedSingleSnowParticleA", bowSettings.ArrowVisualSettings.TipParticleColor.ToColor(), bowSettings.ArrowVisualSettings.TipParticleEmissiveColor.ToColor());
		}

		SeinVisualEditor::VisualSettings.BowVisualSettings = bowSettings;
		SeinVisualEditor::VisualSettingsUpdated.HasUpdatedBow = true;
	}
}