#pragma once

#include "String.h"

#pragma pack(push, 1)
class GameParameters
{
public:
	// 0x0000 - 0x0009
	unsigned char uc_Unk0000_0009[0x10];
	unsigned char StartInScene[0x8]; // 0x10
	unsigned char RacesSuffix[0x8]; // 0x18
	bool DisableRaces; // 0x20
	bool AllowTelemetry; // 0x21
	bool ThreadedUpdateDelegator; // 0x22
	unsigned char x27[0x5];
	unsigned char BuildTag[0x8]; // 0x28
	bool InstantEnableFrustumObjectsOnTeleport; // 0x30
	bool DebugSceneRoots; // 0x31
	bool DebugTimeline; // 0x32
	bool DebugPhysicsIgnoreCalls; // 0x33
	bool BreakGameOnNonZeroCharacterPosition; // 0x34
	unsigned char x0037[0x3];
	int MinimumRevision; // 0x38
	bool DisableMotionBlur; // 0x3C
	bool SimpleBugReporter; // 0x3D
	bool runPerfTest; // 0x3E
	bool runExceptionsTest; // 0x3F
	unsigned char runStressTestFromScene[0x8]; // 0x40
	unsigned char startStressTestAtScene[0x8]; // 0x48
	unsigned char endStressTestAtScene[0x8]; // 0x50
	float stressTestSpeed; // 0x58
	bool collectPerfTestData; // 0x5C
	unsigned char x005F[0x3];
	unsigned char builderName[0x8]; // 0x60
	bool consecutiveStressTests; // 0x68
	unsigned char x006F[0x7];
	unsigned char stressTestPlaylist[0x8]; // 0x70
	int stressTestIndex; // 0x78
	int StressTestDelay; // 0x7C
	bool TakeMemorySnapshots; // 0x80
	unsigned char x0087[0x7];
	unsigned char LogFile[0x8]; // 0x88
	bool debugEnabled; // 0x90
	bool runSrpAsTask; // 0x91
	bool DoRecording; // 0x92
	unsigned char x0097[0x5];
	unsigned char RecordingServer[0x8]; // 0x98
	bool EnableExceptionReports; // 0xA0
	bool DisableBugReporter; // 0xA1
	bool DisableHDR; // 0xA2
	bool ChinaRegion; // 0xA3
	bool SetResoultionFromGameSettings; // 0xA4

protected:
private:
};
#pragma pack(pop)