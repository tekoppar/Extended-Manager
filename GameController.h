#pragma once

#include "Adresses.h"
#include "SaveGameController.h"
#include "GameParameters.h"
#include "HString.h"

const float m_timeBetweenCharacterHeartbeats = 20; // 0x0
const float m_timeBetweenPerfSamples = 5; // 0x0

#pragma pack(push, 1)
class GameController
{
public:
	static GameController Instance; // 0x0
	static bool IsContentPackage; // 0x8
	static bool IsDoingAnyAutomation; // 0x9
	static bool FreezeFixedUpdate; // 0xA
	static bool IsClosing; // 0xB
	static bool IsFocused; // 0xC
	static int XboxHardwareVersion; // 0x10
	static bool m_isPackageFullyInstalled; // 0x14
	static unsigned char DeviceUniqueIdentifier[0x8]; // 0x18
	static unsigned char UserLocale[0x8]; // 0x20
	static long UserGeoIDRegion; // 0x28
	static long UserGeoIDNation; // 0x30
	static bool IsChinaRegion; // 0x38
	static GameParameters Parameters_k__BackingField; // 0x40
	static unsigned char ProfilingConfig[0x8]; // 0x48
	static int m_totalExceptionCount; // 0x4C
	static int m_recentExceptionCount; // 0x50
	static bool m_showDebug; // 0x54
	static bool ShowBackupSaveDebug; // 0x55

	unsigned char x20[0x20];
	bool IsPressTourBuild_k__BackingField; // 0x20
	unsigned char x27[0x7];
	unsigned char Timer[0x8]; // 0x28
	unsigned char DeathUberStateManager[0x8]; // 0x30
	unsigned char SaveGameController[0x8]; // 0x38
	unsigned char Systems[0x8]; // 0x40
	unsigned char GameScheduler[0x8]; // 0x48
	unsigned char ActiveObjectives[0x8]; // 0x50
	unsigned char Objectives[0x8]; // 0x58
	unsigned char UberStateCollectionReference[0x8]; // 0x60
	unsigned char OfflineMessageProvider[0x8]; // 0x68
	unsigned char GameDifficultyModeUberState[0x8]; // 0x70
	unsigned char GameFinishedUberState[0x8]; // 0x78
	unsigned char EasyModeBalanceSettings[0x8]; // 0x80
	unsigned char NormalModeBalanceSettings[0x8]; // 0x88
	unsigned char HardModeBalanceSettings[0x8]; // 0x90
	HString* BuildID[0x1]; // 0x98
	HString* BuildIDString[0x1]; // 0xA0
	HString* BuildName[0x1]; // 0xA8
	unsigned char AtlasPlatform[0x8]; // 0xB0
	unsigned char m_suspendablesToIgnoreForGameplay[0x8]; // 0xB8
	unsigned char m_systemsGameObject[0x8]; // 0xC0
	unsigned char m_logCallbackHandler[0x8]; // 0xC8
	unsigned char m_restoreCheckpointController[0x8]; // 0xD0
	int VSyncCount; // 0xD8
	unsigned char xDC[0x4];
	unsigned char m_logOutputFile[0x8]; // 0xE0
	float m_gameTime; // 0xE8
	unsigned char xEC[0x4];
	unsigned char GameSaveSequence[0x8]; // 0xF0
	bool PCTrialValue; // 0xF8
	bool EditorTrialValue; // 0xF9
	unsigned char xFF[0x6];
	unsigned char DebugWorldEvents[0x8]; // 0x100
	bool m_isRestartingGame; // 0x108
	bool m_setRunInBackgroundToFalse; // 0x109
	bool RequireInitialValues; // 0x10A
	bool m_isLoadingGame; // 0x10B
	unsigned char x10F[0x4];
	unsigned char Resources[0x8]; // 0x110
	bool m_lastDebugControlsEnabledValue; // 0x118
	unsigned char x11B[0x3];
	int m_previousScreenWidth; // 0x11C
	int m_previousScreenHeight; // 0x120
	float m_isPackageFullyInstalledTimer; // 0x124
	unsigned char m_onRestoreCheckpointFinished[0x8]; // 0x128
	bool MainMenuCanBeOpened_k__BackingField; // 0x130
	bool SecondaryMapAndInventoryCanBeOpened_k__BackingField; // 0x131
	bool IsTrailerRecordingBuild; // 0x132
	unsigned char x137[0x5];
	unsigned char BrokenSaveFixingInfo[0x4]; // 0x138
	//offsets are wrong they all should be -0x40
	unsigned char x177[0x3C];
	int GameplaySuspensionTicket; // 0x178
	int GameplayUISuspensionTicket; // 0x17C
	bool m_lockByAction; // 0x180
	bool m_lockInput; // 0x181
	unsigned char x183[0x2];
	float m_inputLockTime; // 0x184
	bool PreventFocusPause_k__BackingField; // 0x188
	bool IsSuspended_k__BackingField; // 0x189
	unsigned char x18B[0x2];
	int m_suspensionMask; // 0x18C
	bool m_canSendNetCommunications; // 0x190
	bool AutomaticGC; // 0x191
	unsigned char x196[0x6];
	unsigned char PlatformServiceProvider_k__BackingField[0x8]; // 0x198
	unsigned char RestartReason_k__BackingField[0x8]; // 0x1A0
	unsigned char m_switch[0x8]; // 0x1A8
	unsigned char m_exceptionCache[0x8]; // 0x1B0
	float m_timer; // 0x1B8
	float m_lastTime; // 0x1BC
	float m_internetCheckTimer; // 0x1C0
	bool m_previousIsOnline; // 0x1C4
	unsigned char x1C7[0x3];
	unsigned char OnNetworkStatusChangedCallback[0x8]; // 0x1C8
	float m_controllerDetectionTimer; // 0x1D0
	unsigned char x1D7[0x4];
	unsigned char m_lastControllers[0x8]; // 0x1D8
	bool UnityInputJoystickConnected_k__BackingField; // 0x1E0
	bool IsGameplaySuspended; // 0x1E1
	unsigned char x1E2[0x2];
	float m_timeUntilNextCharacterHeartbeat; // 0x1E4
	float m_timeUntilNextPerfSample; // 0x1E8
	int m_frameIndexSinceLastSample; // 0x1EC
	unsigned char m_fpsSamples[0x8]; // 0x1F0

	inline void CreateCheckpointWithSave()
	{
		((void(__fastcall *)(GameController*))((Assembly_BaseAddr)+0x997230))(this);
	}

	inline void SuspendGameplay()
	{
		((void(__fastcall *)(GameController*))((Assembly_BaseAddr)+0x997010))(this);
	}

	inline void ResumeGameplay()
	{
		((void(__fastcall *)(GameController*))((Assembly_BaseAddr)+0x9970C0))(this);
	}

	inline void PerformSaveGameSequence()
	{
		((void(__fastcall *)(GameController*))((Assembly_BaseAddr)+0x98CC40))(this);
	}

	GameParameters get_Parameters()
	{
		auto GetParameters_address = Assembly_BaseAddr + 0x98C450;
		using GameController__get_ShowDebug = GameParameters(*)(GameController*);
		auto GetParameters = reinterpret_cast<GameController__get_ShowDebug>(GetParameters_address);
		return GetParameters(this);
	}

	unsigned int get_TotalExceptionsCount()
	{
		auto get_TotalExceptionsCount_address = Assembly_BaseAddr + 0x990FB0;
		using GameController__get_ShowDebug = int(*)(GameController*);
		auto get_TotalExceptionsCount = reinterpret_cast<GameController__get_ShowDebug>(get_TotalExceptionsCount_address);
		return get_TotalExceptionsCount(this);
	}

	bool get_ShowDebug()
	{
		//return ((bool(__fastcall*)(GameController*))((Assembly_BaseAddr)+0x9950E0));
		auto show_debug_address = Assembly_BaseAddr + 0x9950E0;
		using GameController__get_ShowDebug = bool(*)(GameController*);
		auto show_debug = reinterpret_cast<GameController__get_ShowDebug>(show_debug_address);
		return show_debug(this);
	}

protected:
private:
};
#pragma pack(pop)