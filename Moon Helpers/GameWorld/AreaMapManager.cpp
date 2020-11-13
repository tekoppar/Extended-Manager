#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include "Adresses.h"
#include "detours.h"

#include "StringUtils.h"
#include "ManagerDef.h"

#include "AreaMapManager.h"

app::GameObject* AreaMapManager::CreateNewIconPlayerIcon(tem::Vector3 position, app::Color color)
{
	app::IconPlacementScaler* iconScaler = MDV::AreaMapUI->fields._IconScaler_k__BackingField;
	app::GameObject* newPlayerPositionMarker = nullptr;

	if (MDV::AreaMapUI->fields.PlayerPositionMarkerPrefab != nullptr)
	{
		newPlayerPositionMarker = (app::GameObject*)app::Object_1_Instantiate_2((app::Object_1*)MDV::AreaMapUI->fields.PlayerPositionMarkerPrefab, NULL);

		app::Vector3* newPlayerIconPos = (app::Vector3*)il2cpp_object_new((Il2CppClass*)app::Vector3__TypeInfo);
		newPlayerIconPos->x = position.X;
		newPlayerIconPos->y = position.Y;
		newPlayerIconPos->z = position.Z;

		AllAreaIconsIndex.push_back(iconScaler->fields.m_icons->fields.count);
		app::IconPlacementScaler_PlaceIcon(iconScaler, newPlayerPositionMarker, *newPlayerIconPos, false, NULL);

		app::GameObject* areaMapNavigationObject = app::Component_1_get_gameObject((app::Component_1*)MDV::AreaMapUI->fields._IconManager_k__BackingField, NULL);
		TransformSetParentFromObject(newPlayerPositionMarker, areaMapNavigationObject);
		MeshRendererSetColor(newPlayerPositionMarker, color);

		AllAreaIcons.push_back(newPlayerPositionMarker);
	}

	return newPlayerPositionMarker;
}

void AreaMapManager::UpdateIconPosition(app::GameObject* object, tem::Vector3 position)
{
	if (MDV::AreaMapUI != nullptr)
	{
		for (int i = 0; i < AllAreaIcons.size(); i++)
		{
			if (AllAreaIcons[i] == object)
			{
				app::IconPlacementScaler* iconScaler = MDV::AreaMapUI->fields._IconScaler_k__BackingField;
				app::IconPlacementScaler_IconOffsetPosition* iconOffsetPosition = iconScaler->fields.m_icons->fields.entries->vector[AllAreaIconsIndex[i]].value;

				if (iconOffsetPosition != nullptr)
				{
					iconOffsetPosition->fields.RealPosition.x = position.X;
					iconOffsetPosition->fields.RealPosition.y = position.Y;
					iconOffsetPosition->fields.RealPosition.z = position.Z;
				}
			}
		}
	}
}