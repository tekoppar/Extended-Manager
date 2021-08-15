#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <unordered_map>
#include <filesystem>

#include "StringUtils.h"
#include "ManagerDef.h"

#include "UberStateManager.h"

bool UberStateManager::RunnerUberStatesSaved = false;

std::string UberGroup::ToString() 
{
	std::string s = std::to_string(UberGroupID) + "||:";

	if (UberInts.size() > 0)
	{
		for (auto& v : UberInts)
		{
			s += std::to_string(v.first) + "|" + std::to_string(v.second) + "|";
		}
	}
	else
		s += "EMPTY";

	s += "||:";

	if (UberFloats.size() > 0)
	{
		for (auto& v : UberFloats)
		{
			s += std::to_string(v.first) + "|" + std::to_string(v.second) + "|";
		}
	}
	else
		s += "EMPTY";

	s += "||:";

	if (UberBools.size() > 0)
	{
		for (auto& v : UberBools)
		{
			s += std::to_string(v.first) + "|" + std::to_string(v.second) + "|";
		}
	}
	else
		s += "EMPTY";

	s += "||:";

	if (UberBools.size() > 0)
	{
		for (auto& v : UberBytes)
		{
			s += std::to_string(v.first) + "|" + std::to_string(v.second) + '|';
		}
	}
	else
		s += "EMPTY";

	return s;
}

void UberGroup::LoadData(std::string data)
{
	std::vector<std::string> maps = sutil::SplitTem(data, "||:");
	UberGroupID = std::stoi(maps[0]);

	for (int i = 1; i < maps.size(); i++)
	{
		if (maps[i] != "EMPTY")
		{
			std::string ss = maps[i];
			std::vector<std::string> values = sutil::SplitTem(ss, "|");

			for (int x = 0; x < values.size(); x += 2)
			{
				switch (i)
				{
				case 1:
				{
					UberInts[std::stoi(values[x])] = std::stoi(values[x + 1]);
				}
				break;

				case 2:
				{
					UberFloats[std::stoi(values[x])] = std::stof(values[x + 1]);
				}
				break;

				case 3:
				{
					UberBools[std::stoi(values[x])] = std::stoi(values[x + 1]);
				}
				break;

				case 4:
				{
					UberBytes[std::stoi(values[x])] = (std::uint8_t)std::stoi(values[x + 1]);
				}
				break;
				}
			}
		}
	}
}

void UberStateManager::SaveUberStates(std::string path) 
{
	app::UberStateValueStore* uberStates = app::UberStateController_get_CurrentStateValueStore(NULL);
	std::unordered_map<int, UberGroup> ubergroups;
	std::string textFile = "";
	for (int i = 0; i < uberStates->fields.m_groupMap->fields.count; i++)
	{
		app::UberStateValueGroup* group = uberStates->fields.m_groupMap->fields.entries->vector[i].value;
		UberGroup ubergroup = UberGroup();
		ubergroup.UberGroupID = group->fields.m_id->fields.m_id;
		UberStateManager::SaveBools(group, ubergroup.UberBools);
		UberStateManager::SaveBytes(group, ubergroup.UberBytes);
		UberStateManager::SaveFloats(group, ubergroup.UberFloats);
		UberStateManager::SaveIntegers(group, ubergroup.UberInts);
		ubergroups[group->fields.m_id->fields.m_id] = ubergroup;
		textFile += ubergroup.ToString() + "|;?;|";
	}

	sutil::Write(path, textFile);
}

void UberStateManager::LoadUberStates(std::string path)
{	
	app::UberStateController_ApplyPendingChanges(NULL);
	app::UberStateController_ApplyChanges(app::UberStateController_get_Instance(NULL), NULL);

	if (UberStateManager::RunnerUberStatesSaved == false)
	{
		UberStateManager::SaveUberStates(ManagerPath + "\\RaceSettings\\temp.uberstates");
		UberStateManager::RunnerUberStatesSaved = true;
	}

	if (std::filesystem::exists(path) == true && std::filesystem::is_regular_file(path) == true)
	{
		app::UberStateValueStore* uberStates = app::UberStateController_get_CurrentStateValueStore(NULL);
		std::string s = sutil::readFile(path);
		std::vector<std::string> maps = sutil::SplitTem(s, "|;?;|");
		std::unordered_map<int, UberGroup> ubergroups;

		for (auto& map : maps)
		{
			UberGroup ubergroup = UberGroup();
			ubergroup.LoadData(map);
			ubergroups[ubergroup.UberGroupID] = ubergroup;
		}

		for (int i = 0; i < uberStates->fields.m_groupMap->fields.count; i++)
		{
			app::UberStateValueGroup* group = uberStates->fields.m_groupMap->fields.entries->vector[i].value;

			if (group->fields.m_id->fields.m_id != 3440 && ubergroups.find(group->fields.m_id->fields.m_id) != ubergroups.end())
			{
				UberGroup ugroup = ubergroups[group->fields.m_id->fields.m_id];
				UberStateManager::LoadBools(group, ugroup.UberBools);
				UberStateManager::LoadBytes(group, ugroup.UberBytes);
				UberStateManager::LoadFloats(group, ugroup.UberFloats);
				UberStateManager::LoadIntegers(group, ugroup.UberInts);
			}
		}

		app::UberStateController_SetState(uberStates, NULL);
		app::UberStateController_ApplyAll(app::UberStateApplyContext__Enum::UberStateApplyContext__Enum_ValueChanged, NULL);
	}
}

void UberStateManager::SetUberState(int UberGroupID, int UberID, std::uint8_t value)
{
	app::UberStateValueStore* uberStates = app::UberStateController_get_CurrentStateValueStore(NULL);
	app::UberStateValueGroup* UberStateValueGroup = UberStateManager::GetUberGroup(UberGroupID);

	if (UberStateValueGroup != nullptr)
	{
		app::UberID* uberID = (app::UberID*)il2cpp_object_new((Il2CppClass*)(*app::UberID__TypeInfo));
		app::UberID__ctor_1(uberID, UberID, NULL);
		uberID->fields.m_id = UberID;

		for (int i = 0; i < UberStateValueGroup->fields.m_byteStateMap->fields.count; i++)
		{
			if (UberStateValueGroup->fields.m_byteStateMap->fields.entries->vector[i].key->fields.m_id == UberID)
				UberStateValueGroup->fields.m_byteStateMap->fields.entries->vector[i].value = value;
		}
	}
}

void UberStateManager::AddUberStates(int UberGroupID, int UberID, bool value)
{
	app::UberStateValueStore* uberStates = app::UberStateController_get_CurrentStateValueStore(NULL);
	app::UberStateValueGroup* UberStateValueGroup = UberStateManager::GetUberGroup(UberGroupID);

	if (UberStateValueGroup != nullptr)
	{
		app::UberID* uberID = (app::UberID*)il2cpp_object_new((Il2CppClass*)(*app::UberID__TypeInfo));
		app::UberID__ctor_1(uberID, UberID, NULL);
		uberID->fields.m_id = UberID;
		app::Dictionary_2_Moon_UberID_System_Boolean__set_Item(UberStateValueGroup->fields.m_boolStateMap, uberID, value, (*app::Dictionary_2_Moon_UberID_System_Boolean__set_Item__MethodInfo));

		app::UberStateController_SetState(uberStates, NULL);
		app::UberStateController_ApplyAll(app::UberStateApplyContext__Enum::UberStateApplyContext__Enum_ValueChanged, NULL);
	}
}

std::uint8_t UberStateManager::GetUberState(int UberGroupID, int UberID)
{
	app::UberStateValueStore* uberStates = app::UberStateController_get_CurrentStateValueStore(NULL);
	app::UberStateValueGroup* UberStateValueGroup = UberStateManager::GetUberGroup(UberGroupID);

	if (UberStateValueGroup != nullptr)
	{
		for (int i = 0; i < UberStateValueGroup->fields.m_byteStateMap->fields.count; i++)
		{
			app::Dictionary_2_TKey_TValue_Entry_Moon_UberID_System_Byte_ item = UberStateValueGroup->fields.m_byteStateMap->fields.entries->vector[i];

			if (item.key->fields.m_id == UberID)
				return item.value;
		}
	}

	return '0';
}

void UberStateManager::ResetUberStates()
{
	if (std::filesystem::exists(ManagerPath + "\\RaceSettings\\temp.uberstates") == true && std::filesystem::is_regular_file(ManagerPath + "\\RaceSettings\\temp.uberstates") == true)
	{
		UberStateManager::LoadUberStates(ManagerPath + "\\RaceSettings\\temp.uberstates");
		std::filesystem::remove(ManagerPath + "\\RaceSettings\\temp.uberstates");
		UberStateManager::RunnerUberStatesSaved = false;
	}
}

app::UberStateValueGroup* UberStateManager::GetUberGroup(int UberGroupID)
{
	app::UberStateValueStore* uberStates = app::UberStateController_get_CurrentStateValueStore(NULL);

	for (int i = 0; i < uberStates->fields.m_groupMap->fields.count; i++)
	{
		if (uberStates->fields.m_groupMap->fields.entries->vector[i].key->fields.m_id == UberGroupID)
			return uberStates->fields.m_groupMap->fields.entries->vector[i].value;
	}

	return nullptr;
}

void UberStateManager::SaveIntegers(app::UberStateValueGroup* group, std::unordered_map<int, int>& uberids)
{
	for (int i = 0; i < group->fields.m_intStateMap->fields.count; i++)
	{
		uberids[group->fields.m_intStateMap->fields.entries->vector[i].key->fields.m_id] = group->fields.m_intStateMap->fields.entries->vector[i].value;
	}
}

void UberStateManager::SaveBools(app::UberStateValueGroup* group, std::unordered_map<int, bool>& uberids)
{
	for (int i = 0; i < group->fields.m_boolStateMap->fields.count; i++)
	{
		uberids[group->fields.m_boolStateMap->fields.entries->vector[i].key->fields.m_id] = group->fields.m_boolStateMap->fields.entries->vector[i].value;
	}
}

void UberStateManager::SaveFloats(app::UberStateValueGroup* group, std::unordered_map<int, float>& uberids)
{
	for (int i = 0; i < group->fields.m_floatStateMap->fields.count; i++)
	{
		uberids[group->fields.m_floatStateMap->fields.entries->vector[i].key->fields.m_id] = group->fields.m_floatStateMap->fields.entries->vector[i].value;
	}
}

void UberStateManager::SaveBytes(app::UberStateValueGroup* group, std::unordered_map<int, std::uint8_t>& uberids)
{
	for (int i = 0; i < group->fields.m_byteStateMap->fields.count; i++)
	{
		uberids[group->fields.m_byteStateMap->fields.entries->vector[i].key->fields.m_id] = group->fields.m_byteStateMap->fields.entries->vector[i].value;
	}
}

void UberStateManager::LoadIntegers(app::UberStateValueGroup* group, std::unordered_map<int, int>& uberids)
{
	for (int i = 0; i < group->fields.m_intStateMap->fields.count; i++)
	{
		if (uberids.find(group->fields.m_intStateMap->fields.entries->vector[i].key->fields.m_id) != uberids.end())
		{
			group->fields.m_intStateMap->fields.entries->vector[i].value = uberids[group->fields.m_intStateMap->fields.entries->vector[i].key->fields.m_id];
		}
	}
}

void UberStateManager::LoadBools(app::UberStateValueGroup* group, std::unordered_map<int, bool>& uberids)
{
	for (int i = 0; i < group->fields.m_boolStateMap->fields.count; i++)
	{
		if (uberids.find(group->fields.m_boolStateMap->fields.entries->vector[i].key->fields.m_id) != uberids.end())
		{
			group->fields.m_boolStateMap->fields.entries->vector[i].value = uberids[group->fields.m_boolStateMap->fields.entries->vector[i].key->fields.m_id];
		}
	}
}

void UberStateManager::LoadFloats(app::UberStateValueGroup* group, std::unordered_map<int, float>& uberids)
{
	for (int i = 0; i < group->fields.m_floatStateMap->fields.count; i++)
	{
		if (uberids.find(group->fields.m_floatStateMap->fields.entries->vector[i].key->fields.m_id) != uberids.end())
		{
			group->fields.m_floatStateMap->fields.entries->vector[i].value = uberids[group->fields.m_floatStateMap->fields.entries->vector[i].key->fields.m_id];
		}
	}
}

void UberStateManager::LoadBytes(app::UberStateValueGroup* group, std::unordered_map<int, std::uint8_t>& uberids)
{
	for (int i = 0; i < group->fields.m_byteStateMap->fields.count; i++)
	{
		if (uberids.find(group->fields.m_byteStateMap->fields.entries->vector[i].key->fields.m_id) != uberids.end())
		{
			group->fields.m_byteStateMap->fields.entries->vector[i].value = uberids[group->fields.m_byteStateMap->fields.entries->vector[i].key->fields.m_id];
		}
	}
}