#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <future>
#include <unordered_map>

#include "StringUtils.h"
#include "ManagerDef.h"

#include "GameWorldHelper.h"

std::unordered_map<std::string, app::RuntimeGameWorldArea*> GameWorldHelper::RuntimeGameWorldAreas;

app::RuntimeGameWorldArea* GameWorldHelper::GetRuntimeGameWorldArea(std::string name)
{
	if (GameWorldHelper::RuntimeGameWorldAreas.find(name) != GameWorldHelper::RuntimeGameWorldAreas.end())
		return GameWorldHelper::RuntimeGameWorldAreas[name];

	app::List_1_RuntimeGameWorldArea_* areas = MDV::MoonGameWorld->fields.RuntimeAreas;
	
	for (int i = 0; i < areas->fields._size; i++)
	{
		app::RuntimeGameWorldArea* area = areas->fields._items->vector[i];

		if (area != nullptr)
		{
			app::GameWorldArea* gameArea = area->fields.Area;

			if (gameArea != nullptr)
			{
				std::string areaName = sutil::convert_csstring(gameArea->fields.AreaNameString);
				RuntimeGameWorldAreas[areaName] = area;

				if (areaName == name)
					return area;
			}
		}
	}

	return nullptr;
}