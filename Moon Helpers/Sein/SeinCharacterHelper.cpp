#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <filesystem>

#include "StringUtils.h"
#include "ManagerDef.h"
#include "UberStateManager.h"

#include "SeinCharacterHelper.h"

std::vector<SeinStateUpdate> SeinCharacterHelper::SeinAbilitiesUpgrades;
std::vector<SeinStateUpdate> SeinCharacterHelper::SeinAbilitiesStates;
app::AbilityType__Enum SeinCharacterHelper::BoundAbility1 = app::AbilityType__Enum::AbilityType__Enum_None;
app::AbilityType__Enum SeinCharacterHelper::BoundAbility2 = app::AbilityType__Enum::AbilityType__Enum_None;
app::AbilityType__Enum SeinCharacterHelper::BoundAbility3 = app::AbilityType__Enum::AbilityType__Enum_None;
SeinRestoreState SeinCharacterHelper::CurrentState = SeinRestoreState::IsEmpty;
SeinRestoreState SeinCharacterHelper::CurrentShardState = SeinRestoreState::IsEmpty;
SeinRestoreState SeinCharacterHelper::CurrentBoundAbilitiesState = SeinRestoreState::IsEmpty;
SeinRestoreState SeinCharacterHelper::CurrentEquippedShardState = SeinRestoreState::IsEmpty;
std::vector< app::PlayerUberStateShards_Shard> SeinCharacterHelper::SeinShards = std::vector< app::PlayerUberStateShards_Shard>();
std::vector<app::SpiritShardType__Enum> SeinCharacterHelper::SeinEquippedShards = std::vector<app::SpiritShardType__Enum>();

void SeinCharacterHelper::UpdateSeinStates(std::unordered_map<int, SeinStateUpdate> newStates)
{
	app::HashSet_1_AbilityType_* currentAbilities = app::PlayerAbilities_GetAbilities(MDV::MoonSein->fields.PlayerAbilities, NULL);
	app::PlayerUberStateInventory* uberInventory = app::SeinInventory_get_PlayerUberInventory(MDV::MoonSein->fields.Inventory, NULL);
	app::List_1_Moon_uberSerializationWisp_PlayerUberStateInventory_InventoryItem_* inventoryList = app::PlayerUberStateInventory_get_Inventory(uberInventory, NULL);
	std::unordered_map<int, int> tempInventoryMap;

	for (int i = 0; i < inventoryList->fields._size; i++)
	{
		auto item = inventoryList->fields._items->vector[i];
		tempInventoryMap[item->fields.m_type] = i;
	}

	for (int i = 0; i < currentAbilities->fields._count; i++)
	{
		app::HashSet_1_T_Slot_AbilityType_ test = currentAbilities->fields._slots->vector[i];

		if (newStates.find((int)test.value) == newStates.end())
		{
			app::PlayerAbilities_SetAbility(MDV::MoonSein->fields.PlayerAbilities, test.value, false, NULL);
			int abilitTypeIndex = (int)test.value;

			if (AbilityTypeToInventoryItemType.find(abilitTypeIndex) != AbilityTypeToInventoryItemType.end())
			{
				int inventoryItemIndex = AbilityTypeToInventoryItemType.at(abilitTypeIndex);

				if (tempInventoryMap.find(inventoryItemIndex) != tempInventoryMap.end())
				{
					inventoryList->fields._items->vector[tempInventoryMap[inventoryItemIndex]]->fields.m_gained = false;
				}
			}
		}
	}

	app::PlayerAbilities_ResetAbilitiesCache(MDV::MoonSein->fields.PlayerAbilities, NULL);

	for (auto& state : newStates)
	{
		app::PlayerAbilities_SetAbility(MDV::MoonSein->fields.PlayerAbilities, state.second.AbilityType, state.second.Active, NULL);
		int abilitTypeIndex = (int)state.second.AbilityType;

		if (AbilityTypeToInventoryItemType.find(abilitTypeIndex) != AbilityTypeToInventoryItemType.end())
		{
			int inventoryItemIndex = AbilityTypeToInventoryItemType.at(abilitTypeIndex);

			if (tempInventoryMap.find(inventoryItemIndex) != tempInventoryMap.end())
			{
				inventoryList->fields._items->vector[tempInventoryMap[inventoryItemIndex]]->fields.m_gained = state.second.Active;
			}
		}
	}

	app::PlayerUberStateDescriptor_SetIsDirty(MDV::MoonSein->fields.PlayerAbilities->fields.StateDescriptor, NULL);
	app::PlayerAbilities_ResetAbilitiesCache(MDV::MoonSein->fields.PlayerAbilities, NULL);

	SeinCharacterHelper::CurrentState = SeinRestoreState::IsModified;
}

void SeinCharacterHelper::SetSeinState(SeinStateUpdate newState)
{
	app::PlayerUberStateInventory* uberInventory = app::SeinInventory_get_PlayerUberInventory(MDV::MoonSein->fields.Inventory, NULL);
	app::List_1_Moon_uberSerializationWisp_PlayerUberStateInventory_InventoryItem_* inventoryList = app::PlayerUberStateInventory_get_Inventory(uberInventory, NULL);
	std::unordered_map<int, int> tempInventoryMap;

	for (int i = 0; i < inventoryList->fields._size; i++)
	{
		auto item = inventoryList->fields._items->vector[i];
		tempInventoryMap[item->fields.m_type] = i;
	}

	app::PlayerAbilities_SetAbility(MDV::MoonSein->fields.PlayerAbilities, newState.AbilityType, newState.Active, NULL);
	int abilitTypeIndex = (int)newState.AbilityType;

	if (AbilityTypeToInventoryItemType.find(abilitTypeIndex) != AbilityTypeToInventoryItemType.end())
	{
		int inventoryItemIndex = AbilityTypeToInventoryItemType.at(abilitTypeIndex);

		if (tempInventoryMap.find(inventoryItemIndex) != tempInventoryMap.end())
		{
			inventoryList->fields._items->vector[tempInventoryMap[inventoryItemIndex]]->fields.m_gained = newState.Active;
		}
	}
}

void SeinCharacterHelper::StoreSeinAbilities()
{
	if (SeinCharacterHelper::CurrentState == SeinRestoreState::IsStored || SeinCharacterHelper::CurrentState == SeinRestoreState::IsModified)
		return;

	app::SeinAbilities_RefreshStateCache(MDV::MoonSein->fields.Abilities, NULL);
	app::SeinSpells_RefreshStateCache(MDV::MoonSein->fields.Spells, NULL);
	app::PlayerAbilities_ResetAbilitiesCache(MDV::MoonSein->fields.PlayerAbilities, NULL);

	SeinStateUpdate seinStateUpdate;
	SeinAbilitiesStates = std::vector<SeinStateUpdate>();

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.AbilityMarkers->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.AbilityMarkers, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.AirDash->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.AirDash, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.Bash->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.Bash, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.BashBuff->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.BashBuff, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.BlazeSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.BlazeSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.Bounce->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.Bounce, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.Bow->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.Bow, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.BowCharge->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.BowCharge, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.Chainsword->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.Chainsword, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.ChakramSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.ChakramSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.ChargeDash->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.ChargeDash, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.ChargeFlame->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.ChargeFlame, NULL);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.ChargeFlameBlast->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.ChargeFlameBlast, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.ChargeFlameBurn->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.ChargeFlameBurn, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.ChargeFlameEfficiency->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.ChargeFlameEfficiency, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.ChargeJump->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.ChargeJump, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.ChargeShotSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.ChargeShotSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.CinderFlame->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.CinderFlame, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.Climb->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.Climb, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.Dash->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.Dash, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.DashNew->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.DashNew, NULL);
	bool isbetter = app::PlayerAbilities_HasAbility(MDV::MoonSein->fields.PlayerAbilities, MDV::MoonSein->fields.PlayerAbilities->fields.DashNew->fields.m_abilityType, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.Digging->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.Digging, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.DoubleJump->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.DoubleJump, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.DoubleJumpUpgrade->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.DoubleJumpUpgrade, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.Drill->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.Drill, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.EarthShatterSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.EarthShatterSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.EnergyEfficiency->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.EnergyEfficiency, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.EnergyMarkers->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.EnergyMarkers, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.EnergyWallSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.EnergyWallSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.EntanglingRootsSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.EntanglingRootsSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.FeatherFlap->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.FeatherFlap, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.FireburstSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.FireburstSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.FirewhirlSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.FirewhirlSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.Glide->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.Glide, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.GlowSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.GlowSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.GoldenSein->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.GoldenSein, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.Grenade->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.Grenade, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.GrenadeUpgrade->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.GrenadeUpgrade, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.GrenadeEfficiency->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.GrenadeEfficiency, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.HammerCharge->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.HammerCharge, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.Hammer->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.Hammer, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.HealthEfficiency->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.HealthEfficiency, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.HealthMarkers->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.HealthMarkers, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.HeavySpiritSlash->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.HeavySpiritSlash, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.HomingMissileSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.HomingMissileSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.JumpShotSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.JumpShotSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.Launch->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.Launch, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.Leached->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.Leached, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.LifeAbsorbSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.LifeAbsorbSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.LightningSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.LightningSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.LightSpearSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.LightSpearSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.LightSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.LightSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.LockOnSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.LockOnSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.MarkOfTheWildsSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.MarkOfTheWildsSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.Magnet->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.Magnet, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.MeditateSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.MeditateSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.MindControlSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.MindControlSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.MineSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.MineSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.MirageSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.MirageSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.Pinned->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.Pinned, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.PowerOfFriendshipSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.PowerOfFriendshipSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.PowerslideSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.PowerslideSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.QuickFlame->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.QuickFlame, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.RapidFire->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.RapidFire, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.Regroup->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.Regroup, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.Rekindle->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.Rekindle, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.RoundupLeashSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.RoundupLeashSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.SparkFlame->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.SparkFlame, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.Sense->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.Sense, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.ShieldSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.ShieldSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.SoulEfficiency->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.SoulEfficiency, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.SoulFlameEfficiency->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.SoulFlameEfficiency, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.SpiritCrescentSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.SpiritCrescentSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.SpiritFlame->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.SpiritFlame, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.SpiritFlareSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.SpiritFlareSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.SpiritLeash->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.SpiritLeash, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.SpiritMagnet->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.SpiritMagnet, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.SpiritSentrySpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.SpiritSentrySpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.SpiritShardsSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.SpiritShardsSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.SpiritSlash->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.SpiritSlash, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.SpiritSpearSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.SpiritSpearSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.SplitFlameUpgrade->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.SplitFlameUpgrade, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.StickyMineSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.StickyMineSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.Stomp->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.Stomp, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.StompUpgrade->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.StompUpgrade, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.Sword->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.Sword, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.SwordCharge->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.SwordCharge, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.Swordstaff->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.Swordstaff, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.TeleportSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.TeleportSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.TimeWarpSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.TimeWarpSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.Torch->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.Torch, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.TrapSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.TrapSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.TurretSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.TurretSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.UltraDefense->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.UltraDefense, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.UltraMagnet->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.UltraMagnet, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.UltraSoulFlame->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.UltraSoulFlame, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.UltraSplitFlame->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.UltraSplitFlame, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.WallJump->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.WallJump, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.WarpSpell->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.WarpSpell, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.WaterBreath->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.WaterBreath, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.WaterDash->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.WaterDash, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.WeaponCharge->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.WeaponCharge, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = MDV::MoonSein->fields.PlayerAbilities->fields.WeaponCharge->fields.m_abilityType;
	seinStateUpdate.Active = app::CharacterAbility_get_HasAbility(MDV::MoonSein->fields.PlayerAbilities->fields.WeaponCharge, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = app::AbilityType__Enum::AbilityType__Enum_DamageUpgradeA;
	seinStateUpdate.Active = app::PlayerAbilities_HasAbility(MDV::MoonSein->fields.PlayerAbilities, app::AbilityType__Enum::AbilityType__Enum_DamageUpgradeA, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	seinStateUpdate.AbilityType = app::AbilityType__Enum::AbilityType__Enum_DamageUpgradeB;
	seinStateUpdate.Active = app::PlayerAbilities_HasAbility(MDV::MoonSein->fields.PlayerAbilities, app::AbilityType__Enum::AbilityType__Enum_DamageUpgradeB, NULL);
	SeinAbilitiesStates.push_back(seinStateUpdate);

	SeinCharacterHelper::CurrentState = SeinRestoreState::IsStored;
}

void SeinCharacterHelper::RestoreSeinAbilities()
{
	if (SeinCharacterHelper::CurrentState != SeinRestoreState::HasBeenRestored && SeinCharacterHelper::SeinAbilitiesStates.size() > 0)
	{
		app::PlayerUberStateInventory* uberInventory = app::SeinInventory_get_PlayerUberInventory(MDV::MoonSein->fields.Inventory, NULL);
		app::List_1_Moon_uberSerializationWisp_PlayerUberStateInventory_InventoryItem_* inventoryList = app::PlayerUberStateInventory_get_Inventory(uberInventory, NULL);
		std::unordered_map<int, int> tempInventoryMap;

		for (int i = 0; i < inventoryList->fields._size; i++)
		{
			auto item = inventoryList->fields._items->vector[i];
			tempInventoryMap[item->fields.m_type] = i;
		}

		for (auto& state : SeinCharacterHelper::SeinAbilitiesStates)
		{
			app::PlayerAbilities_SetAbility(MDV::MoonSein->fields.PlayerAbilities, state.AbilityType, state.Active, NULL);
			int abilitTypeIndex = (int)state.AbilityType;

			if (AbilityTypeToInventoryItemType.find(abilitTypeIndex) != AbilityTypeToInventoryItemType.end())
			{
				int inventoryItemIndex = AbilityTypeToInventoryItemType.at(abilitTypeIndex);

				if (tempInventoryMap.find(inventoryItemIndex) != tempInventoryMap.end())
				{
					inventoryList->fields._items->vector[tempInventoryMap[inventoryItemIndex]]->fields.m_gained = state.Active;
					inventoryList->fields._items->vector[tempInventoryMap[inventoryItemIndex]]->fields.m_isNew = true;
				}
			}
		}

		app::SeinAbilities_RefreshStateCache(MDV::MoonSein->fields.Abilities, NULL);
		app::SeinSpells_RefreshStateCache(MDV::MoonSein->fields.Spells, NULL);
		//app::PlayerAbilities_ResetAbilitiesCache(MDV::MoonSein->fields.PlayerAbilities, NULL);
		//app::PlayerUberStateDescriptor_SetIsDirty(MDV::MoonSein->fields.PlayerAbilities->fields.StateDescriptor, NULL);
		SeinCharacterHelper::SeinAbilitiesStates.clear();

		SeinCharacterHelper::CurrentState = SeinRestoreState::HasBeenRestored;
	}
}

void SeinCharacterHelper::UpdateSeinAbilitiesUpgradesStates(std::unordered_map<int, SeinStateUpdate> newStates)
{
	for (auto state : newStates)
	{
		if (AbilityUpgradeToByte.find(state.second.AbilityType) != AbilityUpgradeToByte.end())
		{
			char active = state.second.Active == true ? 0x1 : 0x0;
			int value = AbilityUpgradeToByte.at(state.second.AbilityType);
			UberStateManager::SetUberState(3440, value, active);
		}
	}
}

void SeinCharacterHelper::StoreSeinAbilitiesUpgrades()
{
	SeinAbilitiesUpgrades = std::vector<SeinStateUpdate>();

	for (auto type : AbilityUpgradeToByte)
	{
		SeinStateUpdate seinStateUpdate;
		seinStateUpdate.AbilityType = (app::AbilityType__Enum)type.first;
		std::uint8_t value = UberStateManager::GetUberState(3440, type.second);

		if (value > 0)
			seinStateUpdate.Active = true;
		else
			seinStateUpdate.Active = false;

		SeinAbilitiesUpgrades.push_back(seinStateUpdate);
	}
}

void SeinCharacterHelper::RestoreSeinAbilitiesUpgrades()
{
	for (auto state : SeinAbilitiesUpgrades)
	{
		if (AbilityUpgradeToByte.find(state.AbilityType) != AbilityUpgradeToByte.end())
		{
			char active = state.Active == true ? 0x1 : 0x0;
			int value = AbilityUpgradeToByte.at(state.AbilityType);
			UberStateManager::SetUberState(3440, value, active);
		}
	}
}

app::AbilityType__Enum SeinCharacterHelper::StringToAbilityType(std::string ability)
{
	switch (sutil::hash(ability.data()))
	{
	case sutil::hash("None"):
	{
		return app::AbilityType__Enum::AbilityType__Enum_None;
	}
	break;

	case sutil::hash("Sword"):
	{
		return app::AbilityType__Enum::AbilityType__Enum_Sword;
	}
	break;

	case sutil::hash("Bow"):
	{
		return app::AbilityType__Enum::AbilityType__Enum_Bow;
	}
	break;

	case sutil::hash("SpiritSpearSpell"):
	{
		return app::AbilityType__Enum::AbilityType__Enum_SpiritSpearSpell;
	}
	break;

	case sutil::hash("Hammer"):
	{
		return app::AbilityType__Enum::AbilityType__Enum_Hammer;
	}
	break;

	case sutil::hash("ChakramSpell"):
	{
		return app::AbilityType__Enum::AbilityType__Enum_ChakramSpell;
	}
	break;

	case sutil::hash("Grenade"):
	{
		return app::AbilityType__Enum::AbilityType__Enum_Grenade;
	}
	break;

	case sutil::hash("MeditateSpell"):
	{
		return app::AbilityType__Enum::AbilityType__Enum_MeditateSpell;
	}
	break;

	case sutil::hash("FeatherFlap"):
	{
		return app::AbilityType__Enum::AbilityType__Enum_FeatherFlap;
	}
	break;

	case sutil::hash("Blaze"):
	{
		return app::AbilityType__Enum::AbilityType__Enum_Blaze;
	}
	break;

	case sutil::hash("LightSpell"):
	{
		return app::AbilityType__Enum::AbilityType__Enum_LightSpell;
	}
	break;

	case sutil::hash("TurretSpell"):
	{
		return app::AbilityType__Enum::AbilityType__Enum_TurretSpell;
	}
	break;

	case sutil::hash("ChargeJump"):
	{
		return app::AbilityType__Enum::AbilityType__Enum_ChargeJump;
	}
	break;

	case sutil::hash("DamageUpgradeA"):
	{
		return app::AbilityType__Enum::AbilityType__Enum_DamageUpgradeA;
	}
	break;

	case sutil::hash("DamageUpgradeB"):
	{
		return app::AbilityType__Enum::AbilityType__Enum_DamageUpgradeB;
	}
	break;

	default:
		return app::AbilityType__Enum::AbilityType__Enum_None;
	}
}

void SeinCharacterHelper::StoreBoundAbilities()
{
	SeinCharacterHelper::BoundAbility1 = app::SeinInput_GetAssignedAbility(MDV::MoonSein->fields.Input, app::Input_Command__Enum::Input_Command__Enum_Ability1, NULL);
	SeinCharacterHelper::BoundAbility2 = app::SeinInput_GetAssignedAbility(MDV::MoonSein->fields.Input, app::Input_Command__Enum::Input_Command__Enum_Ability2, NULL);
	SeinCharacterHelper::BoundAbility3 = app::SeinInput_GetAssignedAbility(MDV::MoonSein->fields.Input, app::Input_Command__Enum::Input_Command__Enum_Ability3, NULL);

	SeinCharacterHelper::CurrentBoundAbilitiesState = SeinRestoreState::IsStored;
}

void SeinCharacterHelper::SetBoundAbility(int index, std::string ability)
{
	app::AbilityType__Enum abilityType = SeinCharacterHelper::StringToAbilityType(ability);
	app::AbilityType__Enum boundAbility = app::AbilityType__Enum::AbilityType__Enum_None;
	app::EquipmentType__Enum equipmentType = app::EquipmentType__Enum::EquipmentType__Enum_None;
	app::EquipmentType__Enum boundEquipment = app::EquipmentType__Enum::EquipmentType__Enum_None;

	if (AbilityTypeToEquipmentType.find(abilityType) != AbilityTypeToEquipmentType.end())
		equipmentType = AbilityTypeToEquipmentType.at(abilityType);

	switch (index)
	{
	default:
	case 1:
	{
		boundEquipment = app::SpellInventory_GetBoundEquipmentType(MDV::MoonSein->fields.PlayerSpells, app::SpellInventory_Binding__Enum::SpellInventory_Binding__Enum_ButtonX, NULL);
		boundAbility = app::SeinInput_GetAssignedAbility(MDV::MoonSein->fields.Input, app::Input_Command__Enum::Input_Command__Enum_Ability1, NULL);
		if (equipmentType != app::EquipmentType__Enum::EquipmentType__Enum_None && equipmentType != boundEquipment)
			app::SpellInventory_UpdateBinding_1(MDV::MoonSein->fields.PlayerSpells, app::SpellInventory_Binding__Enum::SpellInventory_Binding__Enum_ButtonX, equipmentType, NULL);
		
		if (boundAbility != abilityType)
			app::SeinInput_BindButton(MDV::MoonSein->fields.Input, abilityType, app::Input_Command__Enum::Input_Command__Enum_Ability1, NULL);
	}
	break;

	case 2:
	{
		boundEquipment = app::SpellInventory_GetBoundEquipmentType(MDV::MoonSein->fields.PlayerSpells, app::SpellInventory_Binding__Enum::SpellInventory_Binding__Enum_ButtonY, NULL);
		boundAbility = app::SeinInput_GetAssignedAbility(MDV::MoonSein->fields.Input, app::Input_Command__Enum::Input_Command__Enum_Ability2, NULL);
		if (equipmentType != app::EquipmentType__Enum::EquipmentType__Enum_None && equipmentType != boundEquipment)
			app::SpellInventory_UpdateBinding_1(MDV::MoonSein->fields.PlayerSpells, app::SpellInventory_Binding__Enum::SpellInventory_Binding__Enum_ButtonY, equipmentType, NULL);

		if (boundAbility != abilityType)
			app::SeinInput_BindButton(MDV::MoonSein->fields.Input, abilityType, app::Input_Command__Enum::Input_Command__Enum_Ability2, NULL);
	}
	break;

	case 3:
	{
		boundEquipment = app::SpellInventory_GetBoundEquipmentType(MDV::MoonSein->fields.PlayerSpells, app::SpellInventory_Binding__Enum::SpellInventory_Binding__Enum_ButtonB, NULL);
		boundAbility = app::SeinInput_GetAssignedAbility(MDV::MoonSein->fields.Input, app::Input_Command__Enum::Input_Command__Enum_Ability3, NULL);
		if (equipmentType != app::EquipmentType__Enum::EquipmentType__Enum_None && equipmentType != boundEquipment)
			app::SpellInventory_UpdateBinding_1(MDV::MoonSein->fields.PlayerSpells, app::SpellInventory_Binding__Enum::SpellInventory_Binding__Enum_ButtonB, equipmentType, NULL);
		
		if (boundAbility != abilityType)
			app::SeinInput_BindButton(MDV::MoonSein->fields.Input, abilityType, app::Input_Command__Enum::Input_Command__Enum_Ability3, NULL);
	}
	break;
	}

	//app::PlayerUberStateAbilities_SetAbility(MDV::MoonSein->fields.PlayerAbilities->fields.StateDescriptor->fields.m_state->fields.Abilities, abilityType, true, NULL);

	SeinCharacterHelper::CurrentBoundAbilitiesState = SeinRestoreState::IsModified;
}

void SeinCharacterHelper::RestoreBoundAbilities()
{
	if (SeinCharacterHelper::CurrentBoundAbilitiesState == SeinRestoreState::IsModified)
	{
		app::EquipmentType__Enum boundEquipment = app::SpellInventory_GetBoundEquipmentType(MDV::MoonSein->fields.PlayerSpells, app::SpellInventory_Binding__Enum::SpellInventory_Binding__Enum_ButtonX, NULL);
		app::AbilityType__Enum boundAbility = app::SeinInput_GetAssignedAbility(MDV::MoonSein->fields.Input, app::Input_Command__Enum::Input_Command__Enum_Ability1, NULL);
		app::SpellInventory_UnbindItem(MDV::MoonSein->fields.PlayerSpells, boundEquipment, NULL);
		if (AbilityTypeToEquipmentType.find(SeinCharacterHelper::BoundAbility1) != AbilityTypeToEquipmentType.end() && SeinCharacterHelper::BoundAbility1 != app::AbilityType__Enum::AbilityType__Enum_None)
		{
			if (boundEquipment != AbilityTypeToEquipmentType.at(SeinCharacterHelper::BoundAbility1) || boundEquipment != AbilityTypeToEquipmentType.at(boundAbility))
				app::SpellInventory_UpdateBinding_1(MDV::MoonSein->fields.PlayerSpells, app::SpellInventory_Binding__Enum::SpellInventory_Binding__Enum_ButtonX, AbilityTypeToEquipmentType.at(SeinCharacterHelper::BoundAbility1), NULL);
		}

		if (boundAbility != SeinCharacterHelper::BoundAbility1)
			app::SeinInput_BindButton(MDV::MoonSein->fields.Input, SeinCharacterHelper::BoundAbility1, app::Input_Command__Enum::Input_Command__Enum_Ability1, NULL);


		boundEquipment = app::SpellInventory_GetBoundEquipmentType(MDV::MoonSein->fields.PlayerSpells, app::SpellInventory_Binding__Enum::SpellInventory_Binding__Enum_ButtonY, NULL);
		boundAbility = app::SeinInput_GetAssignedAbility(MDV::MoonSein->fields.Input, app::Input_Command__Enum::Input_Command__Enum_Ability2, NULL);
		app::SpellInventory_UnbindItem(MDV::MoonSein->fields.PlayerSpells, boundEquipment, NULL);
		if (AbilityTypeToEquipmentType.find(SeinCharacterHelper::BoundAbility2) != AbilityTypeToEquipmentType.end() && SeinCharacterHelper::BoundAbility2 != app::AbilityType__Enum::AbilityType__Enum_None)
		{
			if (boundEquipment != AbilityTypeToEquipmentType.at(SeinCharacterHelper::BoundAbility2) || boundEquipment != AbilityTypeToEquipmentType.at(boundAbility))
				app::SpellInventory_UpdateBinding_1(MDV::MoonSein->fields.PlayerSpells, app::SpellInventory_Binding__Enum::SpellInventory_Binding__Enum_ButtonY, AbilityTypeToEquipmentType.at(SeinCharacterHelper::BoundAbility2), NULL);
		}

		if (boundAbility != SeinCharacterHelper::BoundAbility2)
			app::SeinInput_BindButton(MDV::MoonSein->fields.Input, SeinCharacterHelper::BoundAbility2, app::Input_Command__Enum::Input_Command__Enum_Ability2, NULL);


		boundEquipment = app::SpellInventory_GetBoundEquipmentType(MDV::MoonSein->fields.PlayerSpells, app::SpellInventory_Binding__Enum::SpellInventory_Binding__Enum_ButtonB, NULL);
		boundAbility = app::SeinInput_GetAssignedAbility(MDV::MoonSein->fields.Input, app::Input_Command__Enum::Input_Command__Enum_Ability3, NULL);
		app::SpellInventory_UnbindItem(MDV::MoonSein->fields.PlayerSpells, boundEquipment, NULL);
		if (AbilityTypeToEquipmentType.find(SeinCharacterHelper::BoundAbility3) != AbilityTypeToEquipmentType.end() && SeinCharacterHelper::BoundAbility3 != app::AbilityType__Enum::AbilityType__Enum_None)
		{
			if (boundEquipment != AbilityTypeToEquipmentType.at(SeinCharacterHelper::BoundAbility3) || boundEquipment != AbilityTypeToEquipmentType.at(boundAbility))
				app::SpellInventory_UpdateBinding_1(MDV::MoonSein->fields.PlayerSpells, app::SpellInventory_Binding__Enum::SpellInventory_Binding__Enum_ButtonB, AbilityTypeToEquipmentType.at(SeinCharacterHelper::BoundAbility3), NULL);
		}

		if (boundAbility != SeinCharacterHelper::BoundAbility3)
			app::SeinInput_BindButton(MDV::MoonSein->fields.Input, SeinCharacterHelper::BoundAbility3, app::Input_Command__Enum::Input_Command__Enum_Ability3, NULL);

		app::SeinAbilities_RefreshStateCache(MDV::MoonSein->fields.Abilities, NULL);
		app::SeinSpells_RefreshStateCache(MDV::MoonSein->fields.Spells, NULL);
		//app::PlayerAbilities_ResetAbilitiesCache(MDV::MoonSein->fields.PlayerAbilities, NULL);
		//app::PlayerUberStateDescriptor_SetIsDirty(MDV::MoonSein->fields.PlayerAbilities->fields.StateDescriptor, NULL);

		SeinCharacterHelper::CurrentBoundAbilitiesState = SeinRestoreState::HasBeenRestored;
	}
}

void SeinCharacterHelper::StoreShards()
{
	app::List_1_Moon_uberSerializationWisp_PlayerUberStateShards_Shard_* shards = app::PlayerSpiritShards_get_Shards(MDV::MoonSein->fields.PlayerSpiritShards, NULL);

	for (int i = 0; i < shards->fields._size; i++)
	{
		app::PlayerUberStateShards_Shard shard = *shards->fields._items->vector[i];
		SeinCharacterHelper::SeinShards.push_back(shard);
	}

	SeinCharacterHelper::CurrentShardState = SeinRestoreState::IsStored;
}

void SeinCharacterHelper::GiveShards(std::unordered_map<int, SeinShard> shards)
{
	for (auto& shard : shards)
	{
		if (app::PlayerSpiritShards_HasShard(MDV::MoonSein->fields.PlayerSpiritShards, shard.second.ShardType, NULL) == false)
		{
			app::PlayerUberStateShards_Shard* shardItem = app::PlayerSpiritShards_AddNewShardToInventory(MDV::MoonSein->fields.PlayerSpiritShards, shard.second.ShardType, NULL);
			shardItem->fields.m_gained = shard.second.Active;
			shardItem->fields.m_level = shard.second.Level;
		}
		else
		{
			app::PlayerUberStateShards_Shard* shardItem = app::PlayerSpiritShards_GetActualInventoryItem(MDV::MoonSein->fields.PlayerSpiritShards, shard.second.ShardType, NULL);
			shardItem->fields.m_gained = shard.second.Active;
			shardItem->fields.m_level = shard.second.Level;
		}

	}

	SeinCharacterHelper::CurrentShardState = SeinRestoreState::IsModified;
}

void SeinCharacterHelper::RestoreShards()
{
	if (SeinCharacterHelper::CurrentShardState == SeinRestoreState::IsModified)
	{
		app::List_1_Moon_uberSerializationWisp_PlayerUberStateShards_Shard_* shards = app::PlayerSpiritShards_get_Shards(MDV::MoonSein->fields.PlayerSpiritShards, NULL);

		for (int i = 0; i < shards->fields._size; i++)
		{
			app::PlayerUberStateShards_Shard* currentShard = shards->fields._items->vector[i];
			app::PlayerUberStateShards_Shard shard = SeinCharacterHelper::SeinShards[i];

			currentShard->fields.m_gained = shard.fields.m_gained;
			currentShard->fields.m_level = shard.fields.m_level;
		}

		app::PlayerSpiritShards_ApplyShards(MDV::MoonSein->fields.PlayerSpiritShards, NULL);

		SeinCharacterHelper::CurrentShardState = SeinRestoreState::HasBeenRestored;
	}
}

void SeinCharacterHelper::StoreEquippedShards()
{
	app::List_1_Moon_uberSerializationWisp_PlayerUberStateShards_Shard_* shards = MDV::MoonSein->fields.PlayerSpiritShards->fields.m_currentEquippedShards;

	for (int i = 0; i < shards->fields._size; i++)
	{
		app::PlayerUberStateShards_Shard shard = *shards->fields._items->vector[i];
		SeinCharacterHelper::SeinEquippedShards.push_back(shard.fields.m_type);
	}
	app::PlayerSpiritShards_UnequipAllShards(MDV::MoonSein->fields.PlayerSpiritShards, NULL, NULL);

	SeinCharacterHelper::CurrentEquippedShardState = SeinRestoreState::IsModified;
}

void SeinCharacterHelper::EquippShards(std::vector<app::SpiritShardType__Enum> shards)
{
	app::PlayerSpiritShards_UnequipAllShards(MDV::MoonSein->fields.PlayerSpiritShards, NULL, NULL);

	for (auto& shard : shards)
	{
		app::PlayerUberStateShards_Shard* shardItem = app::PlayerSpiritShards_GetActualInventoryItem(MDV::MoonSein->fields.PlayerSpiritShards, shard, NULL);

		if (shardItem != nullptr)
		{
			app::PlayerSpiritShards_EquipShard(MDV::MoonSein->fields.PlayerSpiritShards, shardItem, NULL);
			app::PlayerSpiritShards_ApplyEquip(MDV::MoonSein->fields.PlayerSpiritShards, shardItem, NULL);
		}
	}

	app::PlayerSpiritShards_ApplyShards(MDV::MoonSein->fields.PlayerSpiritShards, NULL);

	SeinCharacterHelper::CurrentEquippedShardState = SeinRestoreState::IsModified;
}

void SeinCharacterHelper::RestoreEquippedShards()
{
	app::PlayerSpiritShards_UnequipAllShards(MDV::MoonSein->fields.PlayerSpiritShards, NULL, NULL);

	if (SeinCharacterHelper::CurrentEquippedShardState == SeinRestoreState::IsModified)
	{
		for (auto& shard : SeinCharacterHelper::SeinEquippedShards)
		{
			app::PlayerUberStateShards_Shard* shardItem = app::PlayerSpiritShards_GetActualInventoryItem(MDV::MoonSein->fields.PlayerSpiritShards, shard, NULL);

			if (shardItem != nullptr)
			{
				app::PlayerSpiritShards_EquipShard(MDV::MoonSein->fields.PlayerSpiritShards, shardItem, NULL);
				app::PlayerSpiritShards_ApplyEquip(MDV::MoonSein->fields.PlayerSpiritShards, shardItem, NULL);
			}
		}

		app::PlayerSpiritShards_ApplyShards(MDV::MoonSein->fields.PlayerSpiritShards, NULL);

		SeinCharacterHelper::SeinEquippedShards.clear();
		SeinCharacterHelper::CurrentEquippedShardState = SeinRestoreState::HasBeenRestored;
	}
}

void SeinCharacterHelper::ClearData()
{
	SeinCharacterHelper::SeinAbilitiesStates.clear();
	SeinCharacterHelper::SeinShards.clear();
	SeinCharacterHelper::SeinShards.clear();
	SeinCharacterHelper::SeinEquippedShards.clear();
	SeinCharacterHelper::BoundAbility1 = app::AbilityType__Enum::AbilityType__Enum_None;
	SeinCharacterHelper::BoundAbility2 = app::AbilityType__Enum::AbilityType__Enum_None;
	SeinCharacterHelper::BoundAbility3 = app::AbilityType__Enum::AbilityType__Enum_None;
}