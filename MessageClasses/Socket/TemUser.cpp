#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include "StringUtils.h"
#include "ManagerDef.h"
#include "Adresses.h"

#include "TemUser.h"

TemUser::TemUser()
{
	this->Username = "";
}

void TemUser::Initialize()
{
	if (app::NativeMethods_1_SteamAPI_Init(NULL) == true)
	{
		this->SteamID = app::SteamUser_1_GetSteamID(NULL);
		this->HasUUID = true;
	}
}

bool TemUser::IsValid()
{
	return this->HasUUID;
}

unsigned long long TemUser::GetID()
{
	if (this->HasUUID == true)
	{
		return this->SteamID.m_SteamID;
	}

	return NULL;
}