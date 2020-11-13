#pragma once
class GameWorldHelper
{
public:
	static std::unordered_map<std::string, app::RuntimeGameWorldArea*> RuntimeGameWorldAreas;

	static app::RuntimeGameWorldArea* GetRuntimeGameWorldArea(std::string);
};

