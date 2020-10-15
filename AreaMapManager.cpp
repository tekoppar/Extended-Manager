#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include "Adresses.h"
#include "detours.h"

#include "StringUtils.h"
#include "ManagerDef.h"

#include "AreaMapManager.h"

void AreaMapManager::Initialize()
{
	app::Type* tAreaMapUI = GetType("", "AreaMapUI");
	app::Object_1__Array* arrAAreaMapUI = app::Object_1_FindObjectsOfTypeAll(tAreaMapUI, NULL);

	areaMapUI = (app::AreaMapUI*)arrAAreaMapUI->vector[0];
}

app::GameObject* AreaMapManager::CreateNewIconPlayerIcon(tem::Vector3 position, app::Color color)
{
	app::IconPlacementScaler* iconScaler = areaMapUI->fields._IconScaler_k__BackingField;
	app::GameObject* newPlayerPositionMarker = nullptr;

	if (areaMapUI->fields.PlayerPositionMarkerPrefab != nullptr)
	{
		newPlayerPositionMarker = (app::GameObject*)app::Object_1_Instantiate_2((app::Object_1*)areaMapUI->fields.PlayerPositionMarkerPrefab, NULL);

		app::Vector3* newPlayerIconPos = (app::Vector3*)il2cpp_object_new((Il2CppClass*)app::Vector3__TypeInfo);
		newPlayerIconPos->x = position.X;
		newPlayerIconPos->y = position.Y;
		newPlayerIconPos->z = position.Z;

		AllAreaIconsIndex.push_back(iconScaler->fields.m_icons->fields.count);
		app::IconPlacementScaler_PlaceIcon(iconScaler, newPlayerPositionMarker, *newPlayerIconPos, false, NULL);

		app::GameObject* areaMapNavigationObject = app::Component_1_get_gameObject((app::Component_1*)areaMapUI->fields._IconManager_k__BackingField, NULL);
		TransformSetParentFromObject(newPlayerPositionMarker, areaMapNavigationObject);
		MeshRendererSetColor(newPlayerPositionMarker, color);

		AllAreaIcons.push_back(newPlayerPositionMarker);
	}

	return newPlayerPositionMarker;
}

void AreaMapManager::UpdateIconPosition(app::GameObject* object, tem::Vector3 position)
{
	for (int i = 0; i < AllAreaIcons.size(); i++)
	{
		if (AllAreaIcons[i] == object)
		{
			app::IconPlacementScaler* iconScaler = areaMapUI->fields._IconScaler_k__BackingField;
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