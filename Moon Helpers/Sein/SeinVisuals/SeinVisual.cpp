#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <filesystem>

#include "StringUtils.h"
#include "ManagerDef.h"
#include "UberStateManager.h"
#include "SeinVisualEditor.h"
#include "Tem.h"

#include "SeinVisual.h"

void GoldenSeinViualSettings::SetGoldenSeinVisuals(GoldenSeinViualSettings goldenSeinSettings)
{
	if (MDV::MoonSein != nullptr)
	{
		if (MDV::MoonSein->fields.Abilities->fields.GoldenSeinWrapper->fields.HasState == true && MDV::MoonSein->fields.Abilities->fields.GoldenSeinWrapper->fields.State->fields.m_goldenSeinInstance != nullptr)
		{
			SeinVisualEditor::SetMeshRendererColorByName(MDV::MoonSein->fields.Abilities->fields.GoldenSeinWrapper->fields.State->fields.m_goldenSeinInstance->fields.Root, "graphic", goldenSeinSettings.SeinBodyColor.ToColor(), goldenSeinSettings.SeinBodyEmissiveColor.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(MDV::MoonSein->fields.Abilities->fields.GoldenSeinWrapper->fields.State->fields.m_goldenSeinInstance->fields.Root, "glowUnmask", goldenSeinSettings.SeinBodyColor.ToColor(), goldenSeinSettings.SeinBodyEmissiveColor.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(MDV::MoonSein->fields.Abilities->fields.GoldenSeinWrapper->fields.State->fields.m_goldenSeinInstance->fields.Root, "oriCSparkle", goldenSeinSettings.SeinParticleColor.ToColor(), goldenSeinSettings.SeinParticleColor.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(MDV::MoonSein->fields.Abilities->fields.GoldenSeinWrapper->fields.State->fields.m_goldenSeinInstance->fields.Root, "spriteSnowPettern2", goldenSeinSettings.SeinParticleColor.ToColor(), goldenSeinSettings.SeinParticleColor.ToColor());
			SeinVisualEditor::SetParticleRendererColorByName(MDV::MoonSein->fields.Abilities->fields.GoldenSeinWrapper->fields.State->fields.m_goldenSeinInstance->fields.Root, "spriteSnowPettern2(1)", goldenSeinSettings.SeinParticleColor.ToColor(), goldenSeinSettings.SeinParticleColor.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(MDV::MoonSein->fields.Abilities->fields.GoldenSeinWrapper->fields.State->fields.m_goldenSeinInstance->fields.Root, "radialLightRays(2)", goldenSeinSettings.SeinRadialLightColor.ToColor(), goldenSeinSettings.SeinRadialLightColor.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(MDV::MoonSein->fields.Abilities->fields.GoldenSeinWrapper->fields.State->fields.m_goldenSeinInstance->fields.Root, "outerGlow", goldenSeinSettings.SeinRadialLightColor.ToColor(), goldenSeinSettings.SeinRadialLightColor.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(MDV::MoonSein->fields.Abilities->fields.GoldenSeinWrapper->fields.State->fields.m_goldenSeinInstance->fields.Root, "newTrail(2)", goldenSeinSettings.SeinTrailColor.ToColor(), goldenSeinSettings.SeinTrailColor.ToColor());
			SeinVisualEditor::SetMeshRendererColorByName(MDV::MoonSein->fields.Abilities->fields.GoldenSeinWrapper->fields.State->fields.m_goldenSeinInstance->fields.Root, "trailMesh(1)", goldenSeinSettings.SeinTrailMeshColor.ToColor(), goldenSeinSettings.SeinTrailMeshColor.ToColor());
		}

		SeinVisualEditor::VisualSettings.GoldenSeinVisualSettings = goldenSeinSettings;
		SeinVisualEditor::VisualSettingsUpdated.HasUpdatedGoldenSein = true;
	}
}