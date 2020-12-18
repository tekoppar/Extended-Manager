#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <filesystem>

#include "FrameLogger.h"
#include "DebugDrawer.h"
#include "GraphDrawer.h"
#include "SeinCharacterHelper.h"
#include "MessageHelper.h"
#include "TemSceneHelper.h"
#include "RaceTime.h"
#include "MoonAnimationHelper.h"
#include "SimpleJson.h"
#include "GhostHandler.h"
#include "TemSocket.h"
#include "ManagerDef.h"
#include "TemRecorder.h"
#include "UberStateManager.h"
#include "MD5.h"

#include "RaceManager.h"

RaceState RaceManager::State = RaceState::RaceIsNull;
RaceSetupPhase RaceManager::SetupPhase = RaceSetupPhase::Null;
int RaceManager::TickCount = 0;

std::string RaceAttempt::ToString()
{
	return RaceName + "|" + std::to_string(RaceTime) + "|" + std::to_string(Attempt) + "\n";
}

void RaceAttemptManager::GetAttempts()
{
	Attempts = std::vector<RaceAttempt>();
	BestAttempt = RaceAttempt();

	std::ifstream file(Filename);
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			auto data = sutil::SplitTem(line, "|");
			RaceAttempt attempt = RaceAttempt();
			attempt.RaceName = data[0];
			attempt.RaceTime = std::stof(data[1]);
			attempt.Attempt = std::stoi(data[2]);

			Attempts.push_back(attempt);

			if (BestAttempt.RaceTime > attempt.RaceTime)
			{
				BestAttempt = attempt;
			}
		}
		file.close();
	}
}

void RaceAttemptManager::WriteAttempts()
{
	std::string fileContent = "";
	for (auto& attempt : Attempts)
	{
		fileContent += attempt.ToString();
	}
	sutil::Write(Filename, fileContent);
}

void RaceAttemptManager::WriteAttempt(RaceAttempt attempt)
{
	std::ofstream log(Filename, std::ios_base::app | std::ios_base::out);
	log << attempt.ToString();
}

void RaceAttemptManager::AddAttempt(float time)
{
	RaceAttempt raceAttempt = RaceAttempt();
	raceAttempt.RaceTime = time;

	raceAttempt.RaceName = RaceName;

	if (Attempts.size() > 0)
		raceAttempt.Attempt = Attempts[Attempts.size() - 1].Attempt + 1;
	else
		raceAttempt.Attempt = 0;

	if (BestAttempt.RaceTime > raceAttempt.RaceTime)
	{
		BestAttempt = raceAttempt;
	}

	Attempts.push_back(raceAttempt);
	WriteAttempt(raceAttempt);
}

const int RaceManager::GhostLimit = 4;

void RaceManager::SetupManager()
{
	if (RaceManager::State == RaceState::RaceIsNull)
	{
		RaceManager::State = RaceState::RaceIsSettingUp;

		//RaceLoopAnimation = AnimationHelper::GetAnimationByName("oriStartRaceLoop");
		//RaceFinishAnimation = AnimationHelper::GetAnimationByName("oriFinishRace");
		//RaceNewPBAnimation = AnimationHelper::GetAnimationByName("oriNewPBRace");
		//RaceTopScoreAnimation = AnimationHelper::GetAnimationByName("oriTopScore");

		GhostHandler::Initialize();
		MDV::AllObjectsToCallUpdate.push_back(&GhostHandler::Instance);
		TemGhostRecorder = TemRecorder();
		TemGhostRecorder.CreateRecorder();

		app::Type* seinType = GetType("", "SeinCharacter");
		app::Object_1__Array* seinArr = app::Object_1_FindObjectsOfType(seinType, NULL);

		if (raceSC == nullptr)
			raceSC = (app::RaceSystem*)il2cpp_object_new((Il2CppClass*)(*app::RaceSystem__TypeInfo));

		if (std::filesystem::exists(racePath + "Default") == false)
			std::filesystem::create_directory(racePath + "Default");

		AttemptManager.Filename = racePath + "Default\\default.ghostdata";
		AttemptManager.GetAttempts();

		FrameLogger.filePath = racePath + "Default\\default.framedata";
		FrameLogger.Initialize();
		MDV::AllObjectsToCallUpdate.push_back(&FrameLogger);

		RaceTime.SetupRaceTimer(raceSC->klass->static_fields->_Instance_k__BackingField->fields.m_timer);

		app::RuntimeSceneMetaData* raceScene = TemSceneHelper::GetSceneByName("inkwaterMarshRaceSetups");
		CreateFinishLine();
		app::ScenesManager_UnsetPreventUnloading_1(TemSceneHelper::SceneManager, raceScene, NULL);

		MDV::AllObjectsToCallUpdate.push_back(this);
		RaceManager::State = RaceState::RaceIsNormal;
	}
}

void RaceManager::Update()
{
	if (RaceManager::State == RaceState::RaceIsStarting && RaceManager::SetupPhase != RaceSetupPhase::Done || (RaceManager::State == RaceState::RaceHasFinishedRestarting && RaceManager::SetupPhase == RaceSetupPhase::Phase0))
	{
		RaceManager::TickCount++;

		if (RaceManager::TickCount >= 5)
		{
			switch (RaceManager::SetupPhase)
			{

			case RaceSetupPhase::Phase0:
			{
				SetupRace(RaceDuration);
			}
			break;

			case RaceSetupPhase::Phase1:
			{
				if (RaceManager::TickCount >= 5)
				{
					SetupRacePhase2(RaceDuration);
				}
			}
			break;

			case RaceSetupPhase::Phase2:
			{
				app::GameplayCamera_MoveCameraToTargetInstantly(MDV::SeinGameplayCamera, true, NULL);
				SetupRacePhase3(RaceDuration);
			}
			break;

			case RaceSetupPhase::Phase3:
			{
				SetupRacePhase4(RaceDuration);
			}
			break;

			case RaceSetupPhase::Phase4:
			{
				SetupRacePhase5(RaceDuration);
			}
			break;

			case RaceSetupPhase::StartCountdown:
			{
				if (RaceManager::TickCount >= 5)
				{
					IsRacing = true;
					RaceTime.StartRaceCountdown();
					RaceManager::State = RaceState::RaceIsCountdown;
					RaceManager::SetupPhase = RaceSetupPhase::Done;
				}
			}
			break;
			}
		}
	}

	if (MDV::MoonGameController != nullptr && MDV::MoonGameController->fields._IsSuspended_k__BackingField == false && IsRacing == true)
		CheckTimer();
}

void RaceManager::LoadRaceData(std::string path)
{
	if (RaceManager::State == RaceState::RaceIsNormal || RaceManager::State == RaceState::RaceIsStopped || RaceManager::State == RaceState::RaceIsFinished)
	{
		if (std::filesystem::exists(path) == true)
		{
			if (std::filesystem::is_directory(path) == true)
			{
				IsRaceLoaded = false;
				IsRacing = false;
				return;
			}

			RaceManager::State = RaceState::RaceIsLoading;

			DebugDrawer debugDrawer = DebugDrawer();
			std::string contents = sutil::ReadFile(path);
			RaceHash = md5(contents);
			std::vector<TemJsonObject> jsonObjects = SimpleJson::ParseJsonFromString(contents);
			raceCheckpointsHit.clear();
			raceCheckpointsRects.clear();
			raceCheckpoints.clear();
			raceCheckpointsCollision.clear();
			shardsToEquip.clear();
			shardsInInventory.clear();
			abilitiesStates.clear();
			BoundAbility1 = "None";
			BoundAbility2 = "None";
			BoundAbility3 = "None";
			IsRacing = false;
			IsRaceCheckpointCreated = false;
			RaceTime.ResetGhostTimer(AttemptManager.BestAttempt.RaceTime, RaceDuration);
			RaceTime.StopRaceTimer();
			RaceTime.CleanUp();
			FrameLogger.CleanUpData();
			RaceManager::State = RaceState::RaceIsStopped;
			RaceManager::TickCount = 0;
			RaceManager::SetupPhase = RaceSetupPhase::Null;
			SeinCharacterHelper::ClearData();

			for (TemJsonObject& jsonObject : jsonObjects)
			{
				switch (sutil::hash(jsonObject.value.data.ObjectName.data()))
				{
				case (sutil::hash("RaceName")):
				{
					raceName = jsonObject.value.data.GetS();
					racePath = path;
					sutil::ReplaceS(racePath, raceName + ".race", "");

					//app::String* MRecorderPath = string_new((racePath + "tempGhostRecording.ghost").c_str());
					TemGhostRecorder.SetRecorderPath(racePath + "tempGhostRecording.ghost");
					//TemGhostRecorder.GhostRecorder->fields.m_filePath = MRecorderPath;

					AttemptManager.Filename = racePath + raceName + ".ghostdata";
					AttemptManager.RaceName = raceName;
					AttemptManager.GetAttempts();
					RaceDuration = AttemptManager.BestAttempt.RaceTime;

					FrameLogger.filePath = racePath + raceName + ".framedata";
					FrameLogger.Initialize();
				}
				break;

				case (sutil::hash("RaceStart")):
				{
					auto values = sutil::SplitTem(jsonObject.value.data.GetS(), "|");
					tem::Vector3 position = tem::Vector3(std::stof(values[0]), std::stof(values[1]), 0);
					StartPosition = (app::Vector3*)il2cpp_object_new((Il2CppClass*)(*app::Vector3__TypeInfo));
					StartPosition.X = (float)position.X;
					StartPosition.Y = (float)position.Y - 0.5f;
					StartPosition.Z = (float)position.Z;
				}
				break;

				case (sutil::hash("RaceFinish")):
				{
					auto values = sutil::SplitTem(jsonObject.value.data.GetS(), "|");
					tem::Vector3 position = tem::Vector3(std::stof(values[0]), std::stof(values[1]), 0);
					FinishPosition = (app::Vector3*)il2cpp_object_new((Il2CppClass*)(*app::Vector3__TypeInfo));
					FinishPosition.X = position.X;
					FinishPosition.Y = position.Y - 0.5f;
					FinishPosition.Z = position.Z;
				}
				break;

				case (sutil::hash("RaceCheckpoints")):
				{
					auto values = jsonObject.value.GetV();

					for (auto& checkpoint : values)
					{
						auto dictionaryCheckpoints = checkpoint.jsonobject->value.unorderedmap;

						tem::Vector3 position = tem::Vector3(dictionaryCheckpoints["x"].GetF(), dictionaryCheckpoints["y"].GetF(), 0);
						tem::Vector3 scale = tem::Vector3(dictionaryCheckpoints["w"].GetF(), dictionaryCheckpoints["h"].GetF(), 1.0f);
						raceCheckpointsRects.push_back(tem::Rect(position.X, position.Y, scale.X, scale.Y));
						position.X = position.X - ((scale.X / 2) * -1);
						position.Y = position.Y;// -scale.Y;

						auto debugObject = debugDrawer.CreateDebugObject(GraphColors::Pink, position, tem::Vector3(1.0f, 1.0f, 1.0f));
						TransformSetScale(debugObject, tem::Vector3(1.0f, 1.0f, 1));
						TransformSetLocalPosition(debugObject, tem::Vector3(1.0f / 2 * -1, 1.0f / 2, 0));
						TransformSetPosition(debugObject, position);

						TransformSetScale(debugObject, tem::Vector3(scale.X, scale.Y, 1));
						TransformSetPosition(debugObject, position);

						raceCheckpointsHit.push_back(false);
						raceCheckpoints.push_back(debugObject);
					}
				}
				break;

				case (sutil::hash("AbilitiesStates")):
				{
					auto values = jsonObject.value.GetD();
					std::string active = "";
					int abilityIndex = -1;

					for (auto& value : values)
					{
						SeinStateUpdate state;

						state.Active = value.second.GetB();
						abilityIndex = std::stoi(value.second.ObjectName);
						state.AbilityType = (app::AbilityType__Enum)abilityIndex;

						if (abilityIndex < 256)
							abilitiesStates[std::stoi(value.second.ObjectName)] = state;
						else
							abilitiesUpgradeStates[std::stoi(value.second.ObjectName)] = state;
					}
				}
				break;

				case (sutil::hash("ShardsInInventory")):
				{
					auto values = jsonObject.value.GetV();
					std::string active = "";

					shardsInInventory = std::unordered_map<int, SeinShard>();

					for (int i = 0; i < values.size(); i++)
					{
						auto& value = values[i];

						SeinShard seinShard;
						auto shardValues = value.jsonobject->value.GetD();
						seinShard.Active = shardValues["Active"].GetB();
						seinShard.Level = shardValues["Level"].GetI();
						seinShard.MaxLevel = shardValues["MaxLevel"].GetI();
						seinShard.ShardType = (app::SpiritShardType__Enum)shardValues["ShardType"].GetI();

						shardsInInventory[i] = seinShard;
					}
				}
				break;

				case (sutil::hash("EquippedShards")):
				{
					auto values = jsonObject.value.GetD();
					std::string active = "";

					for (auto& value : values)
					{
						shardsToEquip.push_back((app::SpiritShardType__Enum)value.second.GetI());
					}
				}
				break;

				case (sutil::hash("SeinFacesDirection")):
				{
					SeinFacingDirection = std::stoi(jsonObject.value.data.GetS());
				}
				break;

				case (sutil::hash("Ability1Bound")):
				{
					BoundAbility1 = jsonObject.value.data.GetS();
				}
				break;

				case (sutil::hash("Ability2Bound")):
				{
					BoundAbility2 = jsonObject.value.data.GetS();
				}
				break;

				case (sutil::hash("Ability3Bound")):
				{
					BoundAbility3 = jsonObject.value.data.GetS();
				}
				break;
				}
			}

			raceCheckpointsRects.push_back(tem::Rect(FinishPosition.X, FinishPosition.Y, 3.0f, 15.0f));
			raceCheckpointsHit.push_back(false);

			TransformSetPosition(RaceGoalObject, FinishPosition);
			IsRaceLoaded = true;
		}
	}

	RaceManager::State = RaceState::RaceIsNormal;
}

void RaceManager::CleanupManager()
{
	IsRacing = false;
	(*app::InvisibleCheckpoint__TypeInfo)->static_fields->ENABLE_INVISIBLE_CHECKPOINTS = true;

	GhostHandler::CleanupGhosts();

	app::Object_1_Destroy_1((app::Object_1*)RaceGoal, NULL);
	RaceGoal = nullptr;
	app::Object_1_Destroy_1((app::Object_1*)RaceGoalObject, NULL);
	RaceGoalObject = nullptr;
	app::Object_1_Destroy_1((app::Object_1*)RaceBody, NULL);
	RaceBody = nullptr;
	RaceGoalMaterial = nullptr;

	for (app::Material* mat : RaceGoalMaterials)
	{
		app::Object_1_Destroy_1((app::Object_1*)mat, NULL);
		mat = nullptr;
	}

	ghostAP = nullptr;
	ghostCP = nullptr;
	ghostSMP = nullptr;
	ghostGEP = nullptr;
	ghostMDP = nullptr;

	ghostC = nullptr;
	raceSC = nullptr;
	raceFinishZone = nullptr;

	for (auto& object : raceCheckpoints)
	{
		app::Object_1_Destroy_1((app::Object_1*)object, NULL);
	}
	raceCheckpoints.clear();

	for (auto& object : raceCheckpointsCollision)
	{
		app::Object_1_Destroy_1((app::Object_1*)object, NULL);
	}
	raceCheckpointsCollision.clear();
	raceCheckpointsHit.clear();
	raceCheckpointsRects.clear();
	abilitiesStates.clear();

	seinRecorder = nullptr;
	newSeinMimicGhost = nullptr;

	FrameLogger.CleanUp();
	RaceTime.CleanUp();
}

void RaceManager::RemoveCheckpoint(int index)
{
	std::vector<app::GameObject*> newCheckpoints;

	for (int i = 0; i < raceCheckpoints.size(); i++)
	{
		if (i != index)
		{
			newCheckpoints.push_back(raceCheckpoints[i]);
		}
		else
		{
			app::Object_1_Destroy_1((app::Object_1*)raceCheckpoints[i], NULL);
		}
	}
	raceCheckpoints = newCheckpoints;
}

void RaceManager::UpdateCheckpoint(tem::Vector3 position, tem::Vector3 scale, int index)
{
	if (raceCheckpoints.size() > index)
	{
		TransformSetScale(raceCheckpoints[index], scale);
		TransformSetPosition(raceCheckpoints[index], position);
	}
}

bool RaceManager::CheckIfHitAllCheckpoints()
{
	int count = 0;

	for (auto b : raceCheckpointsHit)
	{
		if (b == true)
			count++;
	}

	return count >= raceCheckpointsHit.size();
}

void RaceManager::ResetHitCheckpoints()
{
	for (auto b : raceCheckpointsHit)
	{
		b = false;
	}
}

void RaceManager::CheckIfInsideCheckpoint(tem::Vector3 previousPosition, tem::Vector3 currentPosition)
{
	for (int i = 0; i < raceCheckpointsRects.size(); i++)
	{
		tem::Rect rect = raceCheckpointsRects[i];
		bool wasInside = rect.IsPositionInsideRect(previousPosition);
		bool currentlyInside = rect.IsPositionInsideRect(currentPosition);
		bool wasBetween = rect.IsRectBetweenPositions(previousPosition, currentPosition);
		if (wasInside || currentlyInside || wasBetween)
		{
			raceCheckpointsHit[i] = true;
		}
	}
}

void RaceManager::CheckTimer()
{
	if (Graph::Instance != nullptr)
		Graph::Instance->Update();

	if (IsRaceLoaded == true && RaceTime.GhostRaceTimer != nullptr &&
		(RaceTime.RaceTimerState == TimerState::TimerHasStarted || RaceTime.RaceTimerState == TimerState::TimerHasFinished ||
			RaceTime.CountdownTimerState == TimerState::TimerHasStarted || RaceTime.CountdownTimerState == TimerState::TimerHasFinished))
	{
		if (RaceManager::State == RaceState::RaceIsStopping)
			return;

		float raceFloat = RaceTime.GhostRaceTimer->fields._ElapsedTime_k__BackingField;

		if (RaceTime.CountdownTimerState == TimerState::TimerHasFinished)
		{
			app::SeinController_set_IsSuspended(MDV::MoonSein->fields.Controller, false, NULL);
			app::CharacterPlatformMovement_set_IsSuspended(MDV::MoonSein->fields.PlatformBehaviour->fields.PlatformMovement, false, NULL);
			StartRace();
		}
		else
		{
			if (RaceTime.RaceTimerState == TimerState::TimerHasStarted && RaceManager::State != RaceState::RaceIsStopping &&
				RaceManager::State != RaceState::RaceIsStopped && RaceManager::State == RaceState::RaceIsRunning)
			{
#ifdef TEMSOCKET
				//std::string ghostframes = GetLastGhostFrame();
				//TemSocket::SendSocketMessage("WRITEGHOSTSYNC" + TemSocket::MD + raceName + TemSocket::MD + std::to_string(ghostC->fields.CurrentFrameIndex) + TemSocket::MD + ghostframes);
				//sutil::Append(ManagerPath + "\\RaceSettings\\test.ghostsync", ghostframes);
				//GhostHandler::InsertGhostFrames(ghostframes);
#endif
				app::Vector3 currentPosition = app::SeinCharacter_get_Position(MDV::MoonSein, NULL);
				app::Vector3 previousPosition = app::SeinCharacter_get_PreviousPosition(MDV::MoonSein, NULL);
				CheckIfInsideCheckpoint(previousPosition, currentPosition);

				if (RaceTime.CountdownTimerState != TimerState::TimerHasStarted)
					FrameLogger.LoggFrame();

				if (CheckIfHitAllCheckpoints() == true && RaceTime.RaceTimerState == TimerState::TimerHasStarted && RaceManager::State != RaceState::RaceIsStopping &&
					RaceManager::State != RaceState::RaceIsStopped && RaceManager::State == RaceState::RaceIsRunning)
				{
					FinishedRace(raceFloat);
				}

				raceCheckpointsHit[raceCheckpointsRects.size() - 1] = false;

#ifdef TEMSOCKET
				/*if (GhostHandler::ServerRespond == true)
				{
					TemSocket::SendSocketMessage("GETGHOSTSYNC" + TemSocket::MD + std::to_string(GhostHandler::LastReadGhostFrame) + TemSocket::MD + raceName);
					GhostHandler::ServerRespond = false;
				}*/
#endif
			}
		}

		if (RaceTime.CountdownTimerState == TimerState::TimerHasStarted)
			raceFloat = 3.0f - raceFloat;

		RaceTime.UpdateTimer(raceFloat);
	}
}

void RaceManager::FinishedRace(float time)
{
	RaceManager::State = RaceState::RaceIsFinished;

	RaceTime.StopRaceTimer();
	ResetHitCheckpoints();
	MDV::MessageToWrite.push_back("FINISHEDRACE");

	(*app::InvisibleCheckpoint__TypeInfo)->static_fields->ENABLE_INVISIBLE_CHECKPOINTS = true;
	app::SeinCharacter_set_Position(MDV::MoonSein, FinishPosition.ToMoon(), NULL);
	app::SeinCharacter_PlaceOnGround(MDV::MoonSein, NULL);
	app::Vector3* zeroSpeed = (app::Vector3*)il2cpp_object_new((Il2CppClass*)(*app::Vector3__TypeInfo));
	zeroSpeed->z = zeroSpeed->y = zeroSpeed->x = 0;
	app::Vector2 zeroSpeedV2;
	zeroSpeedV2.x = zeroSpeedV2.y = 0.0f;
	app::SeinCharacter_set_Speed(MDV::MoonSein, *zeroSpeed, NULL);
	app::CharacterInstantStop_LockForDuration(MDV::MoonSein->fields.PlatformBehaviour->fields.InstantStop, 1.0f, NULL);
	MDV::MoonSein->fields.PlatformBehaviour->fields.PlatformMovement->fields.AdditiveLocalSpeed = zeroSpeedV2;
	MDV::MoonSein->fields.PlatformBehaviour->fields.PlatformMovement->fields.AdditiveSpeed = zeroSpeedV2;
	MDV::MoonSein->fields.PlatformBehaviour->fields.PlatformMovement->fields._.m_localSpeed = *zeroSpeed;

	if (MDV::SeinPlayAnimationController != nullptr)
	{
		if (AttemptManager.BestAttempt.RaceTime > RaceTime.GhostRaceTimer->fields._ElapsedTime_k__BackingField)
		{
			TemGhostRecorder.WriteRecorder(racePath + raceName + ".topscore.ghost", LeaderboardEntryType::TopScore, raceName, RaceTime.GhostRaceTimer->fields._ElapsedTime_k__BackingField);
			FrameLogger.LogFrameData(racePath + raceName + ".topscore.frames");
			AnimationHelper::PlayAnimation("oriTopScore");
		}
		else if (AttemptManager.BestAttempt.RaceTime > RaceTime.GhostRaceTimer->fields._PersonalBestTime_k__BackingField)
		{
			TemGhostRecorder.WriteRecorder(racePath + raceName + ".newbp.ghost", LeaderboardEntryType::PersonalBest, raceName, RaceTime.GhostRaceTimer->fields._ElapsedTime_k__BackingField);
			FrameLogger.LogFrameData(racePath + raceName + ".newbp.frames");
			AnimationHelper::PlayAnimation("oriNewPBRace");
		}
		else
		{
			TemGhostRecorder.WriteRecorder(racePath + raceName + ".ghost", LeaderboardEntryType::FinishedRace, raceName, RaceTime.GhostRaceTimer->fields._ElapsedTime_k__BackingField);
			FrameLogger.LogFrameData(racePath + raceName + ".frames");
			AnimationHelper::PlayAnimation("oriFinishRace");
		}
	}

	AttemptManager.AddAttempt(time);
	FrameLogger.DisplayDataPublic();
	GhostHandler::CleanupGhosts();
	RaceTime.ResetGhostTimer(AttemptManager.BestAttempt.RaceTime, RaceDuration);
	TemGhostRecorder.ResetRecorder();

	if (abilitiesStates.size() > 0)
		SeinCharacterHelper::RestoreSeinAbilities();

	SeinCharacterHelper::RestoreBoundAbilities();
	SeinCharacterHelper::RestoreShards();
	SeinCharacterHelper::RestoreEquippedShards();
	SeinCharacterHelper::RestoreSeinAbilitiesUpgrades();
}

void RaceManager::StartRace()
{
	if (RaceManager::State == RaceState::RaceIsNormal || RaceManager::State == RaceState::RaceIsCountdown)
	{
		RaceManager::State = RaceState::RaceIsRunning;

		bool ghostsReady = GhostHandler::RunGhost();

		if (ghostsReady == false)
			return;

		TemGhostRecorder.StartRecorder();
		if (RaceTime.RaceCountdownBox != nullptr)
			MessageHelper::SetMessage(RaceTime.RaceCountdownBox, "00:00.000");

		app::SeinPlayAnimationController_StopAnimation(MDV::SeinPlayAnimationController, NULL);
		playingAnimation = false;
		RaceTime.StartRaceTimer(AttemptManager.BestAttempt.RaceTime, AttemptManager.BestAttempt.RaceTime, RaceDuration);
	}
}

void RaceManager::RestartRace()
{
	if (RaceManager::State == RaceState::RaceIsNormal || RaceManager::State == RaceState::RaceIsStopped ||
		RaceManager::State == RaceState::RaceIsFinished || RaceManager::State == RaceState::RaceIsRunning ||
		RaceManager::State == RaceState::RaceHasFinishedRestarting || (RaceManager::State == RaceState::RaceIsCountdown && GhostHandler::WaitingOnGhosts.size() == 0))
	{
		RaceManager::State = RaceState::RaceIsRestarting;
		ResetHitCheckpoints();

		RaceTime.ResetGhostTimer(AttemptManager.BestAttempt.RaceTime, RaceDuration);
		GhostHandler::CleanupGhosts();
		TemGhostRecorder.ResetRecorder();

		SeinCharacterHelper::RestoreSeinAbilities();
		SeinCharacterHelper::RestoreBoundAbilities();
		SeinCharacterHelper::RestoreShards();
		SeinCharacterHelper::RestoreEquippedShards();
		SeinCharacterHelper::RestoreSeinAbilitiesUpgrades();

		app::SeinController_set_IsSuspended(MDV::MoonSein->fields.Controller, false, NULL);
		app::CharacterPlatformMovement_set_IsSuspended(MDV::MoonSein->fields.PlatformBehaviour->fields.PlatformMovement, false, NULL);
		app::SeinCharacter_set_Position(MDV::MoonSein, StartPosition.ToMoon(), NULL);
		app::SeinCharacter_FillHealthAndEnergy(MDV::MoonSein, NULL);

		RaceManager::State = RaceState::RaceHasFinishedRestarting;
		RaceManager::TickCount = 0;
		RaceManager::SetupPhase = RaceSetupPhase::Phase0;
	}
}

void RaceManager::StopRace()
{
	if (RaceManager::State == RaceState::RaceIsNormal || RaceManager::State == RaceState::RaceIsRunning || RaceManager::State == RaceState::RaceIsFinished ||
		RaceManager::State == RaceState::RaceHasFinishedRestarting || (RaceManager::State == RaceState::RaceIsCountdown && GhostHandler::WaitingOnGhosts.size() == 0))
	{
		RaceManager::State = RaceState::RaceIsStopping;
		ResetHitCheckpoints();

		IsRacing = false;
		IsRaceCheckpointCreated = false;
		RaceTime.ResetGhostTimer(AttemptManager.BestAttempt.RaceTime, RaceDuration);
		RaceTime.StopRaceTimer();
		RaceTime.CleanUp();
		FrameLogger.CleanUpData();
		GhostHandler::CleanupGhosts();
		TemGhostRecorder.ResetRecorder();
		TransformSetPosition(RaceGoalObject, tem::Vector3(0, 0, 0));

		app::SeinController_set_IsSuspended(MDV::MoonSein->fields.Controller, false, NULL);
		app::CharacterPlatformMovement_set_IsSuspended(MDV::MoonSein->fields.PlatformBehaviour->fields.PlatformMovement, false, NULL);
		app::SeinCharacter_set_Position(MDV::MoonSein, tem::Vector3(StartPosition.X, StartPosition.Y + 0.1f, StartPosition.Z).ToMoon(), NULL);
		app::SeinCharacter_FillHealthAndEnergy(MDV::MoonSein, NULL);
		(*app::InvisibleCheckpoint__TypeInfo)->static_fields->ENABLE_INVISIBLE_CHECKPOINTS = true;
		app::SeinPlayAnimationController_StopAnimation(MDV::SeinPlayAnimationController, NULL);

		SeinCharacterHelper::RestoreSeinAbilities();
		SeinCharacterHelper::RestoreBoundAbilities();
		SeinCharacterHelper::RestoreShards();
		SeinCharacterHelper::RestoreEquippedShards();
		TemSceneHelper::SetAllScenesCanUnload();
		UberStateManager::ResetUberStates();
		SeinCharacterHelper::RestoreSeinAbilitiesUpgrades();

		RaceManager::State = RaceState::RaceIsStopped;
		RaceManager::TickCount = 0;
		RaceManager::SetupPhase = RaceSetupPhase::Null;
	}
}

bool RaceManager::HasRaceStopped()
{
	while (RaceManager::State != RaceState::RaceIsStopped)
		Sleep(16);

	return true;
}

void RaceManager::CreateFinishLine()
{
	if (RaceGoalObject == nullptr)
	{
		app::String* raceFinishName = string_new("RaceFinish");
		RaceGoalObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
		app::GameObject__ctor(RaceGoalObject, raceFinishName, NULL);

		DebugDrawer debugDrawer = DebugDrawer();
		app::GameObject* raceFinishDebug = debugDrawer.CreateDebugObject(GraphColors::Pink, tem::Vector3(0, 0, 0));

		app::Type* playerInsideZoneType = GetType("", "PlayerInsideZoneChecker");
		raceFinishZone = (app::PlayerInsideZoneChecker*)app::GameObject_AddComponent(raceFinishDebug, playerInsideZoneType, NULL);

		raceFinishZone->fields.OnlyTriggerIfGrounded = false;
		app::Vector2* size2 = (app::Vector2*)il2cpp_object_new((Il2CppClass*)(*app::Vector2__TypeInfo));
		size2->x = 3.0f;
		size2->y = 15.0f;
		raceFinishZone->fields._.Size = *size2;
		auto rectcc = GetClass<>("UnityEngine", "Rect");
		app::Rect* rect2 = (app::Rect*)il2cpp_object_new((Il2CppClass*)rectcc);
		rect2->m_Height = 15.0f;
		rect2->m_Width = 3.0f;
		rect2->m_XMin = 0;
		rect2->m_YMin = 0 - 0.5f;
		raceFinishZone->fields._.m_bounds = *rect2;

		raceCheckpointsRects.push_back(tem::Rect(0.0f, 0.0f - 0.5f, 3.0f, 15.0f));

		TransformSetParent(raceFinishDebug, RaceGoalObject);
		TransformSetPosition(raceFinishDebug, tem::Vector3(0, 0, 0));

		app::Transform* transform = app::GameObject_get_transform(RaceGoalObject, NULL);
		std::vector<std::string> scenePath = { "raceData", "raceStop", "art", "guideStoneSetup", "raceMarkerEnd", "body" };
		app::GameObject* foundObject = GetComponentByScenePath("inkwaterMarshRaceSetups", scenePath);

		app::Type* type45 = GetType("UnityEngine", "MeshFilter");
		app::Component_1__Array* components = app::GameObject_GetComponentsInChildren_1(foundObject, type45, true, NULL);

		type45 = GetType("UnityEngine", "MeshRenderer");
		app::Component_1__Array* componentsRenderers = app::GameObject_GetComponentsInChildren_1(foundObject, type45, true, NULL);

		std::vector<std::string> objectNames;
		std::vector< app::MeshFilter*> meshFilters;
		for (int i = 0; i < components->max_length; i++)
		{
			app::GameObject* gamyobj = app::Component_1_get_gameObject(components->vector[i], NULL);
			app::String* name = app::Object_1_get_name((app::Object_1*)gamyobj, NULL);
			std::string nameS = sutil::convert_csstring(name);
			objectNames.push_back(nameS);
			meshFilters.push_back((app::MeshFilter*)components->vector[i]);
		}

		std::vector<app::MeshRenderer*> meshRenderers;
		for (int i = 0; i < componentsRenderers->max_length; i++)
		{
			app::GameObject* gamyobj = app::Component_1_get_gameObject(componentsRenderers->vector[i], NULL);
			app::String* name = app::Object_1_get_name((app::Object_1*)gamyobj, NULL);
			std::string nameS = sutil::convert_csstring(name);
			objectNames.push_back(nameS);
			meshRenderers.push_back((app::MeshRenderer*)componentsRenderers->vector[i]);
		}

		app::String* raceBodyName = string_new("RaceBase");
		app::GameObject* RaceBodyA = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
		app::GameObject__ctor(RaceBodyA, raceBodyName, NULL);
		app::Transform* transformRaceBodyA = app::GameObject_get_transform(RaceBodyA, NULL);

		raceBodyName = string_new("RaceCenter");
		app::GameObject* RaceBodyB = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
		app::GameObject__ctor(RaceBodyB, raceBodyName, NULL);
		app::Transform* transformRaceBodyB = app::GameObject_get_transform(RaceBodyB, NULL);

		raceBodyName = string_new("RaceCollar");
		app::GameObject* RaceBodyC = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
		app::GameObject__ctor(RaceBodyC, raceBodyName, NULL);
		app::Transform* transformRaceBodyC = app::GameObject_get_transform(RaceBodyC, NULL);

		raceBodyName = string_new("RaceCollarGlow");
		app::GameObject* RaceBodyD = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
		app::GameObject__ctor(RaceBodyD, raceBodyName, NULL);
		app::Transform* transformRaceBodyD = app::GameObject_get_transform(RaceBodyD, NULL);

		TransformSetScale(RaceBodyA, tem::Vector3(3.0f, 1.0f, 0.0f));
		TransformSetScale(RaceBodyB, tem::Vector3(2.0f, 2.0f, 0.0f));
		TransformSetScale(RaceBodyC, tem::Vector3(5.0f, 5.0f, 0.0f));
		TransformSetScale(RaceBodyD, tem::Vector3(4.0f, 4.2f, 0.0f));

		TransformSetLocalPosition(RaceBodyA, tem::Vector3(0.0f, -0.4f, 0.0f));
		TransformSetLocalPosition(RaceBodyB, tem::Vector3(-0.1f, 0.7f, 0.0f));
		TransformSetLocalPosition(RaceBodyC, tem::Vector3(-0.1f, 1.6f, 0.0f));
		TransformSetLocalPosition(RaceBodyD, tem::Vector3(0.0f, 1.5f, 0.0f));

		app::Transform_SetParent(transformRaceBodyA, transform, NULL);
		app::Transform_SetParent(transformRaceBodyD, transform, NULL);
		app::Transform_SetParent(transformRaceBodyB, transform, NULL);
		app::Transform_SetParent(transformRaceBodyC, transform, NULL);

		app::Type* meshRendererType = GetType("UnityEngine", "MeshRenderer");
		app::Type* meshFilterType = GetType("UnityEngine", "MeshFilter");
		std::vector<int> sortingOrder = { 32428, 30185, -1858, 14537 };
		std::vector<app::GameObject*> BodyParts = { RaceBodyA, RaceBodyB, RaceBodyC, RaceBodyD };

		for (int i = 0; i < meshFilters.size(); i++)
		{
			app::MeshRenderer* meshRenderer = (app::MeshRenderer*)app::GameObject_AddComponent(BodyParts[i], meshRendererType, NULL);
			app::Material* meshMat = app::Renderer_GetMaterial((app::Renderer*)meshRenderers[i], NULL);

			app::Material* raceMaterial = (app::Material*)il2cpp_object_new((Il2CppClass*)(*app::Material__TypeInfo));
			app::Material__ctor_1(raceMaterial, meshMat, NULL);
			app::Material_CopyPropertiesFromMaterial(raceMaterial, meshMat , NULL);
			RaceGoalMaterials.push_back(raceMaterial);

			app::Renderer_SetMaterial((app::Renderer*)meshRenderer, raceMaterial, NULL);
			app::Renderer_set_sortingOrder((app::Renderer*)meshRenderer, sortingOrder[i], NULL);

			app::MeshFilter* meshFilter = (app::MeshFilter*)app::GameObject_AddComponent(BodyParts[i], meshFilterType, NULL);
			app::Mesh* mesh = app::MeshFilter_get_mesh(meshFilters[i], NULL);
			app::MeshFilter_set_mesh(meshFilter, mesh, NULL);

			app::GameObject_set_active(BodyParts[i], true, NULL);
		}
		//Renderer_set_sortingOrder((Renderer*)cubeMeshRenderer, 14000, NULL);
		//Renderer_SetMaterial((Renderer*)cubeMeshRenderer, RaceDataMaterial, NULL);
		//GameObject_set_active(cube, true, NULL);
		TransformSetPosition(RaceGoalObject, tem::Vector3(0, 0, 0));

		app::GameObject_set_active(RaceGoalObject, true, NULL);
	}
	/*else
	{
		TransformSetPosition(RaceGoalObject, FinishPosition);
	}*/
}

void RaceManager::SetupRace(float raceDuration)
{
	if (RaceManager::State == RaceState::RaceIsNormal || RaceManager::State == RaceState::RaceIsStopped ||
		RaceManager::State == RaceState::RaceIsFinished || RaceManager::State == RaceState::RaceHasFinishedRestarting)
	{
		RaceManager::State = RaceState::RaceIsStarting;

		ResetHitCheckpoints();

		MDV::MessageToWrite.push_back("STARTEDRACE");
		(*app::InvisibleCheckpoint__TypeInfo)->static_fields->ENABLE_INVISIBLE_CHECKPOINTS = false;

		FrameLogger.CleanUpData();

		if (StartPosition.X != 0.0f && StartPosition.Y != 0.0f)
		{
			//app::SeinCharacter_set_Position(MDV::MoonSein, tem::Vector3(StartPosition.X, StartPosition.Y + 0.5f, StartPosition.Z).ToMoon(), NULL);
			app::ScenesManager_set_CurrentCameraTargetPosition(TemSceneHelper::SceneManager, StartPosition.ToVector2(), NULL);
			app::ScenesManager_SetTargetPositions(TemSceneHelper::SceneManager, StartPosition.ToMoon(), NULL);
			app::CharacterPlatformMovement_TeleportAndPlaceOnGround(MDV::MoonSein->fields.PlatformBehaviour->fields.PlatformMovement, tem::Vector3(StartPosition.X, StartPosition.Y, StartPosition.Z).ToMoon(), 0.0f, 0.01f, NULL);
			//app::SeinCharacter_PlaceOnGround(MDV::MoonSein, NULL);
			app::GameplayCamera_MoveToTargetCharacter(MDV::SeinGameplayCamera, 0.01f, NULL);
		}
		app::SeinCharacter_FillHealthAndEnergy(MDV::MoonSein, NULL);
		app::SeinCharacter_set_FaceLeft(MDV::MoonSein, (SeinFacingDirection == 0 ? true : false), NULL);

		app::SeinController_set_IsSuspended(MDV::MoonSein->fields.Controller, true, NULL);
		app::CharacterPlatformMovement_set_IsSuspended(MDV::MoonSein->fields.PlatformBehaviour->fields.PlatformMovement, true, NULL);

		RaceManager::TickCount = 0;
		RaceManager::SetupPhase = RaceSetupPhase::Phase1;
	}
}

void RaceManager::SetupRacePhase2(float raceDuration)
{
	if (std::filesystem::exists(racePath + raceName + ".uberstates") == true && std::filesystem::is_regular_file(racePath + raceName + ".uberstates") == true)
	{
		UberStateManager::LoadUberStates(racePath + raceName + ".uberstates");
	}

	SeinCharacterHelper::StoreSeinAbilities();
	SeinCharacterHelper::StoreBoundAbilities();
	SeinCharacterHelper::StoreEquippedShards();
	SeinCharacterHelper::StoreShards();
	SeinCharacterHelper::StoreSeinAbilitiesUpgrades();

	if (IsRaceCheckpointCreated == true)
	{
		app::GameController_RestoreCheckpointImmediate(MDV::MoonGameController, NULL);
	}

	if (IsRaceCheckpointCreated == false) {
		app::GameController_CreateCheckpoint(MDV::MoonGameController, false, false, NULL);
		IsRaceCheckpointCreated = true;
	}
	
	RaceManager::TickCount = 0;
	RaceManager::SetupPhase = RaceSetupPhase::Phase2;
}

void RaceManager::SetupRacePhase3(float raceDuration)
{
	if (TemGhostRecorder.GhostRecorder->fields.m_binaryWriter != nullptr)
	{
		app::BinaryWriter* seinWriter = (app::BinaryWriter*)TemGhostRecorder.GhostRecorder->fields.m_binaryWriter;
		app::MemoryStream* seinStream = (app::MemoryStream*)seinWriter->fields.OutStream;
	}

	RaceDuration = raceDuration;
	TransformSetPosition(RaceGoalObject, FinishPosition);

	raceFinishZone->fields._.m_bounds.m_XMin = FinishPosition.X;
	raceFinishZone->fields._.m_bounds.m_YMin = FinishPosition.Y;

	AnimationHelper::PlayAnimation("oriStartRaceLoop");
	startedWeRacing = totalFrames;
	playingAnimation = true;

	RaceManager::TickCount = 0;
	RaceManager::SetupPhase = RaceSetupPhase::Phase3;
}

void RaceManager::SetupRacePhase4(float raceDuration)
{

	if (abilitiesStates.size() > 0)
	{
		SeinCharacterHelper::UpdateSeinStates(abilitiesStates);
	}

	if (abilitiesUpgradeStates.size() > 0)
	{
		SeinCharacterHelper::UpdateSeinAbilitiesUpgradesStates(abilitiesUpgradeStates);
	}

	if (shardsInInventory.size() > 0)
	{
		SeinCharacterHelper::GiveShards(shardsInInventory);
	}

	if (shardsToEquip.size() > 0)
	{
		SeinCharacterHelper::EquippShards(shardsToEquip);
	}

	SeinCharacterHelper::SetBoundAbility(1, BoundAbility1);
	SeinCharacterHelper::SetBoundAbility(2, BoundAbility2);
	SeinCharacterHelper::SetBoundAbility(3, BoundAbility3);

	RaceManager::TickCount = 0;
	RaceManager::SetupPhase = RaceSetupPhase::Phase4;
}

void RaceManager::SetupRacePhase5(float raceDuration)
{
	if (std::filesystem::exists(racePath + raceName + ".ghost") == true)
	{
		GhostHandler::CreateGhostPublic(racePath + raceName + ".ghost", "Last Attempt", StartPosition);
	}

	if (std::filesystem::exists(racePath + raceName + ".topscore.ghost") == true)
	{
		GhostHandler::CreateGhostPublic(racePath + raceName + ".topscore.ghost", "Top Ghost", StartPosition);
	}

	if (std::filesystem::exists(racePath + raceName + ".newbp.ghost") == true)
	{
		GhostHandler::CreateGhostPublic(racePath + raceName + ".newbp.ghost", "BP Ghost", StartPosition);
	}

#ifdef TEMSOCKET
	//GhostHandler::CreateStreamGhost(StartPosition);
#endif

	int ghostIndex = 0;
	if (std::filesystem::exists(ManagerPath + "Ghosts\\" + raceName) == true)
	{
		for (auto& p : std::filesystem::directory_iterator(ManagerPath + "Ghosts\\" + raceName))
		{
			if (ghostIndex <= GhostLimit)
			{
				std::filesystem::path filePath = p.path();
				if (filePath.extension().string() == ".ghost")
					GhostHandler::CreateGhostPublic(filePath.string(), filePath.stem().string(), StartPosition);
			}
			ghostIndex++;
		}
	}

	RaceManager::TickCount = 0;
	RaceManager::SetupPhase = RaceSetupPhase::StartCountdown;
}

std::string RaceManager::GetLastGhostFrame()
{
	app::BinaryWriter* seinWriter = (app::BinaryWriter*)TemGhostRecorder.GhostRecorder->fields.m_binaryWriter;
	app::MemoryStream* seinStream = (app::MemoryStream*)seinWriter->fields.OutStream;
	std::string bytes = "";

	auto MemoryStreamClass = GetClass<>("System.IO", "MemoryStream");
	app::MemoryStream* seinMemoryStream = (app::MemoryStream*)il2cpp_object_new((Il2CppClass*)MemoryStreamClass);
	app::MemoryStream__ctor_5(seinMemoryStream, seinStream->fields._buffer, 0, seinStream->fields._length, true, true, NULL);

	if (seinMemoryStream->fields._length > 0)
	{
		for (std::size_t i = LastReadBytePosition; i < seinMemoryStream->fields._length; i++)
		{
			unsigned char value = seinMemoryStream->fields._buffer->vector[i];
			bytes += value;
		}
		LastReadBytePosition = seinMemoryStream->fields._length;
	}
	//bytes = base64Encode(bytes.data(), bytes.size());

	return bytes;
}

void RaceManager::CreateMimicGhost()
{
	std::string ghostPath = sutil::getexepath();
	sutil::ReplaceS(ghostPath, "oriwotw.exe", "oriwotw_Data\\output\\ghosts\\works.ghost");
	std::string contents = sutil::readFile(ghostPath);
	const char* gP = contents.data();
	app::String* gPath = string_new(gP);
	const char* gPN = "SPOOOOOKKKYYY";
	app::String* gName = string_new(gPN);
	newSeinMimicGhost = app::GhostManager_createGhost_1(GhostHandler::BaseGhostManager, gName, gPath, NULL);

	//app::List_1_GhostFrame__Clear(newSeinMimicGhost->fields.GhostRecorderData->fields.Frames, NULL);
	//newSeinMimicGhost->fields.GhostRecorderData->fields.Duration = 0.0f;

	auto Class1 = GetClass<>("", "GhostRecorderData");
	app::GhostRecorderData* ghostRecorderData = (app::GhostRecorderData*)il2cpp_object_new((Il2CppClass*)Class1);
	app::GhostRecorderData__ctor(ghostRecorderData, NULL);
	newSeinMimicGhost->fields.GhostRecorderData = ghostRecorderData;

	//UpdateMimicGhostFrameData(0);
	app::BinaryWriter* seinWriter = (app::BinaryWriter*)seinRecorder->fields.m_binaryWriter;
	app::MemoryStream* seinStream = (app::MemoryStream*)seinWriter->fields.OutStream;
	//app::Stream* seinMemoryStream = app::BinaryWriter_get_BaseStream(, NULL);

	auto MemoryStreamClass = GetClass<>("System.IO", "MemoryStream");
	app::MemoryStream* seinMemoryStream = (app::MemoryStream*)il2cpp_object_new((Il2CppClass*)MemoryStreamClass);
	app::MemoryStream__ctor_5(seinMemoryStream, seinStream->fields._buffer, 0, seinStream->fields._length, true, true, NULL);
	lastMimicBytePosition = seinStream->fields._position;

	auto binaryReaderClass = GetClass<>("System.IO", "BinaryReader");
	app::BinaryReader* seinBinaryReader = (app::BinaryReader*)il2cpp_object_new((Il2CppClass*)binaryReaderClass);
	app::BinaryReader__ctor_2(seinBinaryReader, (app::Stream*)seinMemoryStream, seinWriter->fields._encoding, true, NULL);
	app::GhostRecorderData_LoadFromBinaryReader(newSeinMimicGhost->fields.GhostRecorderData, seinBinaryReader, NULL);

	lastMimicFrameUpdate = newSeinMimicGhost->fields.GhostRecorderData->fields.Frames->fields._size;

	app::GhostPlayer_Run(newSeinMimicGhost, NULL);
	newSeinMimicGhost->fields.m_isStarted = true;
	newSeinMimicGhost->fields._IsFinished_k__BackingField = false;
	ghostHasStarted = true;

	RegisterGhostPlayerPlugins(newSeinMimicGhost);
}

void RaceManager::RegisterGhostPlayerPlugins(app::GhostPlayer* ghostPlayer)
{
	bool ghostCharacterPluginB = false;
	bool ghostStateMachinePluginB = false;
	bool ghostAnimationPluginB = false;
	bool ghostTransformPluginB = false;
	bool ghostCharacterAbilitiesPluginB = false;
	bool ghostGenericEventsPluginB = false;

	for (int i = 0; i < ghostPlayer->fields.m_plugins->fields._size; i++)
	{
		std::string ghostFrameType = ghostPlayer->fields.m_plugins->fields._items->vector[i]->klass->_0.name;

		if (ghostFrameType == "GhostCharacterPlugin")
		{
			ghostCharacterPluginB = true;
		}
		else if (ghostFrameType == "GhostStateMachinePlugin")
		{
			ghostStateMachinePluginB = true;
		}
		else if (ghostFrameType == "GhostAnimationPlugin")
		{
			ghostAnimationPluginB = true;
		}
		else if (ghostFrameType == "GhostTransformPlugin")
		{
			ghostTransformPluginB = true;
		}
		else if (ghostFrameType == "GhostCharacterAbilitiesPlugin")
		{
			ghostCharacterAbilitiesPluginB = true;
		}
		else if (ghostFrameType == "GhostGenericEventsPlugin")
		{
			ghostGenericEventsPluginB = true;
		}
	}

	if (ghostCharacterPluginB == false)
	{
		auto Class2 = GetClass<>("", "GhostCharacterPlugin");
		app::GhostCharacterPlugin* ghostCP1 = (app::GhostCharacterPlugin*)il2cpp_object_new((Il2CppClass*)Class2);
		app::GhostPlayer_RegisterPlugin(ghostPlayer, (app::IGhostRecorderPlugin*)ghostCP1, NULL);
		ghostCP1->fields._.m_player = ghostPlayer;
	}

	if (ghostGenericEventsPluginB == false)
	{
		auto Class4 = GetClass<>("", "GhostGenericEventsPlugin");
		app::GhostGenericEventsPlugin* ghostGEP1 = (app::GhostGenericEventsPlugin*)il2cpp_object_new((Il2CppClass*)Class4);
		app::GhostPlayer_RegisterPlugin(ghostPlayer, (app::IGhostRecorderPlugin*)ghostGEP1, NULL);
		ghostGEP1->fields._.m_player = ghostPlayer;
	}

	if (ghostCharacterAbilitiesPluginB == false)
	{
		auto Class1 = GetClass<>("", "GhostCharacterAbilitiesPlugin");
		app::GhostCharacterAbilitiesPlugin* ghostAP1 = (app::GhostCharacterAbilitiesPlugin*)il2cpp_object_new((Il2CppClass*)Class1);
		app::GhostPlayer_RegisterPlugin(ghostPlayer, (app::IGhostRecorderPlugin*)ghostAP1, NULL);
		ghostAP1->fields._.m_player = ghostPlayer;
	}

	if (ghostStateMachinePluginB == false)
	{
		auto Class3 = GetClass<>("", "GhostStateMachinePlugin");
		app::GhostStateMachinePlugin* ghostSMP1 = (app::GhostStateMachinePlugin*)il2cpp_object_new((Il2CppClass*)Class3);
		app::GhostPlayer_RegisterPlugin(ghostPlayer, (app::IGhostRecorderPlugin*)ghostSMP1, NULL);
		ghostSMP1->fields._.m_player = ghostPlayer;
	}
}

void RaceManager::UpdateMimicGhostFrameData(int lastFrame)
{
	if (ghostHasStarted == true)
	{
		app::GhostRecorder_FinalizeFrame(seinRecorder, NULL);
		GetSeinFrames();
		newSeinMimicGhost->fields.m_isStarted = true;
		newSeinMimicGhost->fields._IsFinished_k__BackingField = false;
	}
}

app::GhostRecorder* RaceManager::CreateNewGhostRecorder()
{
	auto Class1 = GetClass<>("", "GhostRecorder");
	app::GhostRecorder* ghostRecorder = (app::GhostRecorder*)il2cpp_object_new((Il2CppClass*)Class1);
	app::GhostRecorder__ctor(ghostRecorder, NULL);
	app::String* gName = string_new("SeinRecorder");
	app::GameObject__ctor((app::GameObject*)ghostRecorder, gName, NULL);

	return ghostRecorder;
}

void RaceManager::CreateSeinRecorder()
{
	seinRecorder = app::GhostManager_GetOrCreateRecorder(NULL);

	if (seinRecorder != nullptr)
	{
		if (seinRecorder->fields.m_plugins->fields._size == 0)
		{
			auto Class1 = GetClass<>("", "GhostCharacterAbilitiesPlugin");
			ghostAP = (app::GhostCharacterAbilitiesPlugin*)il2cpp_object_new((Il2CppClass*)Class1);
			auto Class2 = GetClass<>("", "GhostCharacterPlugin");
			ghostCP = (app::GhostCharacterPlugin*)il2cpp_object_new((Il2CppClass*)Class2);
			auto Class3 = GetClass<>("", "GhostStateMachinePlugin");
			ghostSMP = (app::GhostStateMachinePlugin*)il2cpp_object_new((Il2CppClass*)Class3);
			auto Class4 = GetClass<>("", "GhostGenericEventsPlugin");
			ghostGEP = (app::GhostGenericEventsPlugin*)il2cpp_object_new((Il2CppClass*)Class4);
			auto Class5 = GetClass<>("", "GhostRecordingMetaDataPlugin");
			ghostMDP = (app::GhostRecordingMetaDataPlugin*)il2cpp_object_new((Il2CppClass*)Class5);

			app::GhostRecorder_RegisterPlugin(seinRecorder, (app::IGhostRecorderPlugin*)ghostAP, NULL);
			app::GhostRecorder_RegisterPlugin(seinRecorder, (app::IGhostRecorderPlugin*)ghostCP, NULL);
			app::GhostRecorder_RegisterPlugin(seinRecorder, (app::IGhostRecorderPlugin*)ghostSMP, NULL);
			app::GhostRecorder_RegisterPlugin(seinRecorder, (app::IGhostRecorderPlugin*)ghostGEP, NULL);
			app::GhostRecorder_RegisterPlugin(seinRecorder, (app::IGhostRecorderPlugin*)ghostMDP, NULL);
		}

		std::string ghostPath = sutil::getexepath();
		sutil::ReplaceS(ghostPath, "oriwotw.exe", "oriwotw_Data\\output\\ghosts\\swamp1\\playerdata.ghost");
		app::String* MRecorderPath = string_new(ghostPath.c_str());
		//seinRecorder->fields.m_filePath = MRecorderPath;

		app::GhostRecorder_InitializeRecorder(seinRecorder, MRecorderPath, NULL);
		app::GhostRecorder_StartRecorder(seinRecorder, NULL);
	}
}

void RaceManager::GetSeinFrames()
{
	std::vector<app::GhostCharacterData*> getFrames;

	auto Class1 = GetClass<>("", "GhostRecorderData");
	app::GhostRecorderData* ghostRecorderData = (app::GhostRecorderData*)il2cpp_object_new((Il2CppClass*)Class1);
	app::GhostRecorderData__ctor(ghostRecorderData, NULL);

	//auto MemoryStreamClass = GetClass<>("System.IO", "MemoryStream");
	//app::MemoryStream* seinMemoryStream = (app::MemoryStream*)il2cpp_object_new((Il2CppClass*)MemoryStreamClass);
	//app::MemoryStream__ctor_2(seinMemoryStream, seinRecorder->fields.m_binaryWriter->fields._buffer, NULL);
	app::BinaryWriter* seinWriter = (app::BinaryWriter*)seinRecorder->fields.m_binaryWriter;
	app::MemoryStream* seinStream = (app::MemoryStream*)seinWriter->fields.OutStream;
	//app::Stream* seinMemoryStream = app::BinaryWriter_get_BaseStream(, NULL);

	auto MemoryStreamClass = GetClass<>("System.IO", "MemoryStream");
	app::MemoryStream* seinMemoryStream = (app::MemoryStream*)il2cpp_object_new((Il2CppClass*)MemoryStreamClass);
	app::MemoryStream__ctor_5(seinMemoryStream, seinStream->fields._buffer, 0, seinStream->fields._length, true, true, NULL);
	lastMimicBytePosition = seinStream->fields._position;

	auto binaryReaderClass = GetClass<>("System.IO", "BinaryReader");
	app::BinaryReader* seinBinaryReader = (app::BinaryReader*)il2cpp_object_new((Il2CppClass*)binaryReaderClass);
	app::BinaryReader__ctor_2(seinBinaryReader, (app::Stream*)seinMemoryStream, seinWriter->fields._encoding, true, NULL);
	app::GhostRecorderData_LoadFromBinaryReader(ghostRecorderData, seinBinaryReader, NULL);

	int lastGhostFrameIndex = newSeinMimicGhost->fields.GhostRecorderData->fields.Frames->fields._size;
	app::GhostFrame* lastGhostFrame;// = app::GhostRecorderData_GetFrame(tempRecorderData, lastGhostFrameIndex, NULL);
	//getFrames.push_back(lastGhostFrame);

	if (newSeinMimicGhost->fields.GhostRecorderData->fields.Frames->fields._items->max_length != ghostRecorderData->fields.Frames->fields._items->max_length)
	{
		newSeinMimicGhost->fields.GhostRecorderData->fields.Frames = ghostRecorderData->fields.Frames;
	}
	else {
		for (int i = lastGhostFrameIndex; i < ghostRecorderData->fields.Frames->fields._size; i++)
		{
			lastGhostFrame = app::GhostRecorderData_GetFrame(ghostRecorderData, i, NULL);
			app::List_1_GhostFrame__Add(newSeinMimicGhost->fields.GhostRecorderData->fields.Frames, lastGhostFrame, NULL);

			/*for (int i2 = 0; i2 < lastGhostFrame->fields.FrameData->fields._size; i2++)
			{
				std::string ghostFrameType = lastGhostFrame->fields.FrameData->fields._items->vector[i2]->klass->_0.name;

				if (ghostFrameType == "GhostCharacterData")
				{
					app::GhostCharacterData* ghostFrameData = (app::GhostCharacterData*)lastGhostFrame->fields.FrameData->fields._items->vector[i2];
					getFrames.push_back(ghostFrameData);
				}
				else if (ghostFrameType == "GhostStateMachineData")
				{
					app::GhostStateMachineData* ghostFrameData = (app::GhostStateMachineData*)lastGhostFrame->fields.FrameData->fields._items->vector[i2];
				}
				else if (ghostFrameType == "GhostAnimationData")
				{
					app::GhostAnimationData* ghostFrameData = (app::GhostAnimationData*)lastGhostFrame->fields.FrameData->fields._items->vector[i2];
				}
				else if (ghostFrameType == "GhostTransformData")
				{
					app::GhostTransformData* ghostFrameData = (app::GhostTransformData*)lastGhostFrame->fields.FrameData->fields._items->vector[i2];
				}
				else if (ghostFrameType == "GhostCharacterAbilitiesData")
				{
					app::GhostCharacterAbilitiesData* ghostFrameData = (app::GhostCharacterAbilitiesData*)lastGhostFrame->fields.FrameData->fields._items->vector[i2];
				}
			}*/
		}
	}

	//newSeinMimicGhost->fields.GhostRecorderData->fields.Frames = ghostRecorderData->fields.Frames;
	newSeinMimicGhost->fields.GhostRecorderData->fields.Duration = ghostRecorderData->fields.Duration;
	//newSeinMimicGhost->fields.GhostRecorderData->fields.Frames->fields._items->max_length = ghostRecorderData->fields.Frames->fields._items->max_length;
	//GhostPlayer_set_IsSuspended(newSeinMimicGhost, false, NULL);
	app::GhostCharacterPlugin* plugin = (app::GhostCharacterPlugin*)newSeinMimicGhost->fields.m_plugins->fields._items->vector[0];
	app::GhostStateMachinePlugin* statePlugin = (app::GhostStateMachinePlugin*)newSeinMimicGhost->fields.m_plugins->fields._items->vector[3];
	plugin->fields._.CurrentFrameIndex = statePlugin->fields._.CurrentFrameIndex;
	plugin->fields._.NextFrameIndex = statePlugin->fields._.NextFrameIndex;
	plugin->fields._.CurrentFrame = statePlugin->fields._.CurrentFrame;
	plugin->fields._.NextFrame = statePlugin->fields._.NextFrame;
	app::GhostCharacterPlugin_PlayCycle(plugin, newSeinMimicGhost->fields.GhostRecorderData->fields.Duration, NULL);
}

void RaceManager::CheckHash()
{
	if (std::filesystem::exists(racePath + raceName + ".race") == true)
	{
		std::string raceContent = sutil::ReadFile(racePath + raceName + ".race");
		std::string newHash = md5(raceContent);

		if (RaceHash == "")
		{
			IsRaceLoaded = false;
		}
		else if (newHash != RaceHash)
			IsRaceLoaded = false;
	}
}