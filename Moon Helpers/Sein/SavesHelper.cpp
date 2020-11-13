#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include "StringUtils.h"
#include "ManagerDef.h"

#include "SavesHelper.h"

bool SavesHelper::IsBackupsLoaded(int count, int index)
{
	int currentCount = 0;
	
	while (count > currentCount)
	{
		if (MDV::CanCallMethods == true)
		{
			app::SaveSlotBackup* backupSaves = app::SaveSlotBackupsManager_SaveSlotBackupAtIndex(index, NULL);
			currentCount = backupSaves->fields.Count;
		}
		Sleep(16);
	}

	return true;
}