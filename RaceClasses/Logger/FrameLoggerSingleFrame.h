#pragma once

enum class DroppedFrameDataType {
	DangerFrames = 0,
	DroppedFramesSingle = 1,
	DroppedFramesDouble = 2,
	DroppedFramesTriple = 3,
	DroppedFramesMultiple = 4
};

enum class FPSMonitorDataType {
	RenderedFrames = 0,
	CurrentSampleTime = 1,
	CurrentMaxFrameTime = 2,
	CurrentMinFrameTime = 3,
	FrameTime = 4,
	AverageFPS = 5,
	MinimumFPS = 6,
	MaximumFPS = 7,
	AverageFrameTime = 8,
	MinFrameTime = 9,
	MaxFrameTime = 10,
	DeltaTimeAverage = 11,
	HitchDeltaTimeAverage = 12,
	SlowDownDeltaTimeAverage = 13,
	HitchCount = 14,
	SlowdownCount = 15,
	FrameCount = 16,
	BadFrameCount = 17
};

enum class BashDataType {
	Bashing = 0,
	HoldAirTime = 1,
	FrictionTimeRemaining = 2
};

enum class BowDataType {
	AimDuration = 0,
	AimDurationCritical = 1,
	CurrentStateTime = 2,
	ChargeAmount = 3,
	IsAiming = 4,
};

enum class DoubleJumpDataType {
	DoubleJumpTime = 0,
	NumberOfJumpsAvailable = 1,
	RemainingLockTime = 2,
	IsDoubleJumping = 3
};

class DroppedFrameData {
public:
	int DangerFrames = 0;
	int DroppedFramesSingle = 0;
	int DroppedFramesDouble = 0;
	int DroppedFramesTriple = 0;
	int DroppedFramesMultiple = 0;

	DroppedFrameData(app::DroppedFrameMonitor* data = nullptr);
	DroppedFrameData(std::string content);
	std::string ToString();
};

class FPSMonitorData {
public:
	float RenderedFrames = 0.0f;
	float CurrentSampleTime = 0.0f;
	float CurrentMaxFrameTime = 0.0f;
	float CurrentMinFrameTime = 0.0f;
	float FrameTime = 0.0f;
	int AverageFPS = 0;
	int MinimumFPS = 0;
	int MaximumFPS = 0;
	float AverageFrameTime = 0.0f;
	float MinFrameTime = 0.0f;
	float MaxFrameTime = 0.0f;
	float DeltaTimeAverage = 0.0f;
	float HitchDeltaTimeAverage = 0.0f;
	float SlowDownDeltaTimeAverage = 0.0f;
	int HitchCount = 0;
	int SlowdownCount = 0;
	int FrameCount = 0;
	int BadFrameCount = 0;
	int FrameIndex = 0;

	FPSMonitorData(app::FPSMonitor* data = nullptr);
	FPSMonitorData(std::string content);
	std::string ToString();
};

class SeinPlatformMovementData {
public:
	app::Vector2 AdditiveLocalSpeed;
	app::Vector2 AdditiveSpeed;
	app::Vector2 PrevWorldSpeed;
	app::Vector2 CurrentSpeed;

	SeinPlatformMovementData(app::CharacterPlatformMovement* platform = nullptr);
	SeinPlatformMovementData(std::string content);
	std::string ToString();
};

class FrameLoggerSingleFrame {
public:
	DroppedFrameData droppedFrameData;
	FPSMonitorData fpsMonitorData;
	SeinPlatformMovementData seinPlatformMovement;

	FrameLoggerSingleFrame();
	FrameLoggerSingleFrame(std::string content);
	std::string ToString();
};

class FrameLoggerFrames {
public:
	std::vector<FrameLoggerSingleFrame> Frames;
	std::string Name;
};