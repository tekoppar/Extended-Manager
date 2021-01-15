#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <filesystem>

#include "StringUtils.h"
#include "ManagerDef.h"
#include "UberStateManager.h"
#include "SeinVisualEditor.h"
#include "Tem.h"

#include "GlideVisual.h"

void GlideVisualSettings::SetGlideVisuals(GlideVisualSettings glideSettings)
{
	if (MDV::MoonSein != nullptr)
	{
		if (MDV::MoonSein->fields.Prefabs->fields.Glide->fields.m_gameObject != nullptr)
		{
			SeinVisualEditor::SetSkinnedMeshRendererColor(MDV::MoonSein->fields.Prefabs->fields.Glide->fields.m_gameObject, "feather", glideSettings.FeatherColor.ToColor(), glideSettings.FeatherEmissiveColor.ToColor(), "Glide");
		}

		if (MDV::MoonSein->fields.Prefabs->fields.FeatherFlap->fields.m_gameObject != nullptr)
		{
			SeinVisualEditor::SetSkinnedMeshRendererColor(MDV::MoonSein->fields.Prefabs->fields.FeatherFlap->fields.m_gameObject, "featherflap", glideSettings.FeatherflapColor.ToColor(), glideSettings.FeatherflapEmissiveColor.ToColor(), "FeatherFlap");
		}

		SeinVisualEditor::VisualSetting.GlideVisualSetting = glideSettings;
		SeinVisualEditor::VisualSettingsUpdated.HasUpdatedGlide = true;
	}
}