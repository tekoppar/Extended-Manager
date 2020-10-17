#pragma once

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <filesystem>

#include "FrameLogger.h"
#include "DebugDrawer.h"

#ifndef _RACEMANAGER_H
#define _RACEMANAGER_H

class RaceAttempt {
public:
	std::string RaceName = "Race";
	float RaceTime = 10000000.0f;
	long long int Attempt = 0;

	std::string ToString()
	{
		return RaceName + "|" + std::to_string(RaceTime) + "|" + std::to_string(Attempt) + "\n";
	}
};

class RaceAttemptManager {
public:
	std::vector<RaceAttempt> Attempts;
	std::string RaceName = "Race";
	std::string Filename = "";
	RaceAttempt BestAttempt = RaceAttempt();

	void GetAttempts()
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

	void WriteAttempts()
	{
		std::string fileContent = "";
		for (auto& attempt : Attempts)
		{
			fileContent += attempt.ToString();
		}
		sutil::Write(Filename, fileContent);
	}

	void WriteAttempt(RaceAttempt attempt)
	{
		std::ofstream log(Filename, std::ios_base::app | std::ios_base::out);
		log << attempt.ToString();
	}

	void AddAttempt(float time)
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
};

class RaceManager
{
public:
	RaceAttemptManager AttemptManager;
	FrameLogger FrameLogger;

	std::vector<app::GhostPlayer*> ActiveGhostPlayers;
	std::vector< app::GameObject*> ActiveGhostIcons;
	app::GhostCharacterAbilitiesPlugin* ghostAP = nullptr;
	app::GhostCharacterPlugin* ghostCP = nullptr;
	app::GhostStateMachinePlugin* ghostSMP = nullptr;
	app::GhostGenericEventsPlugin* ghostGEP = nullptr;
	app::GhostRecordingMetaDataPlugin* ghostMDP = nullptr;
	app::GhostRecorder* ghostC = nullptr;
	app::RaceSystem* raceSC = nullptr;
	app::UnityRaceTimerDisplay* raceTimerText = nullptr;
	app::RaceTimer* ghostRaceTimer = nullptr;
	app::GhostManager* BaseGhostManager = nullptr;
	app::SeinCharacter* Sein = nullptr;
	app::Vector3 seinOldPosition;
	app::SeinPlayAnimationController* seinPlayAnimationController = nullptr;

	app::GhostRecorder* seinRecorder = nullptr;
	app::GhostPlayer* newSeinMimicGhost = nullptr;
	int lastMimicFrameUpdate = 0;
	unsigned long long lastMimicBytePosition = 0;
	bool ghostHasStarted = false;
	bool playingAnimation = false;
	unsigned long long startedWeRacing = 0;
	unsigned long long totalFrames = 0;

	app::MoonAnimation* RaceFinishAnimation = nullptr;
	app::MoonAnimation* RaceNewPBAnimation = nullptr;
	app::MoonAnimation* RaceTopScoreAnimation = nullptr;
	app::MoonAnimation* RaceLoopAnimation = nullptr;

	app::GameObject* RaceGoalObject = nullptr;
	app::PlayerInsideZoneChecker* raceFinishZone = nullptr;
	app::GameObject* RaceBody = nullptr;
	app::PlayerInsideZoneChecker* RaceGoal = nullptr;
	app::PhysicMaterial* RaceGoalMaterial = nullptr;

	app::Vector3* StartPosition = nullptr;
	app::Vector3* FinishPosition = nullptr;
	std::string raceName = "";
	std::string racePath = "";
	std::vector<app::GameObject*> raceCheckpoints;
	std::vector<app::PlayerInsideZoneChecker*> raceCheckpointsCollision;
	std::vector<app::Rect*> raceCheckpointsRects;
	std::vector<bool> raceCheckpointsHit;

	app::String* raceTimerDivisorMinute = nullptr;
	app::String* raceTimerDivisorSecond = nullptr;

	float RaceDuration = 60.0f;
	bool CountdownHasStarted = false;
	bool IsFinished = false;

	void SetupManager()
	{
		if (raceSC == nullptr)
			raceSC = (app::RaceSystem*)il2cpp_object_new((Il2CppClass*)app::RaceSystem__TypeInfo);

		if (ghostRaceTimer == nullptr)
			ghostRaceTimer = raceSC->klass->static_fields->_Instance_k__BackingField->fields.m_timer;

		if (raceTimerText == nullptr)
		{
			//Get race timer
			app::Type* type = GetType("", "UnityRaceTimerDisplay");
			app::Object_1__Array* arr2222 = app::Object_1_FindObjectsOfType(type, NULL);

			if (arr2222->vector[0] != nullptr)
				raceTimerText = (app::UnityRaceTimerDisplay*)arr2222->vector[0];
		}

		if (std::filesystem::exists(racePath + "Default") == false)
			std::filesystem::create_directory(racePath + "Default");

		raceTimerDivisorMinute = string_new(":");
		raceTimerDivisorSecond = string_new(".");

		CreateRecorder();

		AttemptManager.Filename = racePath + "Default\\default.ghostdata";
		AttemptManager.GetAttempts();

		FrameLogger.filePath = racePath + "Default\\default.framedata";
		FrameLogger.Initialize();
	}

	void LoadRaceData(std::string path)
	{
		if (racePath != path)
		{
			DebugDrawer debugDrawer = DebugDrawer();
			std::string contents = sutil::ReadFile(path);
			auto lines = sutil::SplitTem(contents, "\",\"");

			for (auto& line : lines)
			{
				auto lines = sutil::SplitTem(line, "\":\"");
				std::string type = lines[0];
				sutil::ReplaceS(type, "\"", "");
				sutil::ReplaceS(type, "{", "");
				std::string value = lines[1];
				sutil::ReplaceS(value, "\"", "");
				sutil::ReplaceS(value, "{", "");
				sutil::ReplaceS(value, "}", "");

				switch (sutil::hash(type.data()))
				{
				case (sutil::hash("RaceName")):
				{
					raceName = value;
					racePath = path;
					sutil::ReplaceS(racePath, raceName + ".race", "");

					app::String* MRecorderPath = string_new((racePath + "tempGhostRecording.ghost").c_str());
					ghostC->fields.m_filePath = MRecorderPath;

					AttemptManager.Filename = racePath + raceName + ".ghostdata";
					AttemptManager.RaceName = raceName;
					AttemptManager.GetAttempts();

					FrameLogger.filePath = racePath + raceName + ".framedata";
					FrameLogger.Initialize();
				}
				break;

				case (sutil::hash("RaceStart")):
				{
					auto values = sutil::SplitTem(value, "|");
					tem::Vector3 position = tem::Vector3(std::stof(values[0]), std::stof(values[1]), 0);
					StartPosition = (app::Vector3*)il2cpp_object_new((Il2CppClass*)app::Vector3__TypeInfo);
					StartPosition->x = (float)position.X;
					StartPosition->y = (float)position.Y - 0.5f;
					StartPosition->z = (float)position.Z;
				}
				break;

				case (sutil::hash("RaceFinish")):
				{
					auto values = sutil::SplitTem(value, "|");
					tem::Vector3 position = tem::Vector3(std::stof(values[0]), std::stof(values[1]), 0);
					FinishPosition = (app::Vector3*)il2cpp_object_new((Il2CppClass*)app::Vector3__TypeInfo);
					FinishPosition->x = position.X;
					FinishPosition->y = position.Y - 0.5f;
					FinishPosition->z = position.Z;
				}
				break;

				case (sutil::hash("RaceCheckpoints")):
				{
					auto values = sutil::SplitTem(value, "!");

					for (auto& sPosition : values)
					{
						if (sPosition.size() > 0)
						{
							auto values = sutil::SplitTem(sPosition, "|");
							tem::Vector3 position = tem::Vector3(std::stof(values[0]), std::stof(values[1]), 0);
							position.Y -= 0.5;

							raceCheckpoints.push_back(debugDrawer.CreateDebugObject(graphColors.Pink, position));
						}
					}
				}
				break;
				}
			}

			for (auto& point : raceCheckpoints)
			{
				app::Type* playerInsideZoneType = GetType("", "PlayerInsideZoneChecker");
				app::PlayerInsideZoneChecker* playerInsideZone = (app::PlayerInsideZoneChecker*)app::GameObject_AddComponent(point, playerInsideZoneType, NULL);

				playerInsideZone->fields.OnlyTriggerIfGrounded = false;
				app::Vector3 position = TransformGetPosition((app::GameObject*)point);
				app::Vector2* size2 = (app::Vector2*)il2cpp_object_new((Il2CppClass*)Vector2__TypeInfo);
				size2->x = 3;
				size2->y = 15;
				playerInsideZone->fields._.Size = *size2;
				auto rectcc = GetClass<>("UnityEngine", "Rect");
				app::Rect* rect2 = (app::Rect*)il2cpp_object_new((Il2CppClass*)rectcc);
				rect2->m_Height = 15;
				rect2->m_Width = 3;
				rect2->m_XMin = position.x;
				rect2->m_YMin = position.y - 0.5f;
				playerInsideZone->fields._.m_bounds = *rect2;
				raceCheckpointsRects.push_back(rect2);

				raceCheckpointsCollision.push_back(playerInsideZone);
				raceCheckpointsHit.push_back(false);
			}

			CreateFinishLine();
		}
	}

	void CleanupManager()
	{
		CleanupGhosts();
		Sein = nullptr;
		seinPlayAnimationController = nullptr;

		RaceFinishAnimation = nullptr;
		RaceNewPBAnimation = nullptr;
		RaceTopScoreAnimation = nullptr;
		RaceLoopAnimation = nullptr;

		app::Object_1_Destroy_1((app::Object_1*)RaceGoal, NULL);
		RaceGoal = nullptr;
		app::Object_1_Destroy_1((app::Object_1*)RaceGoalObject, NULL);
		RaceGoalObject = nullptr;
		app::Object_1_Destroy_1((app::Object_1*)RaceBody, NULL);
		RaceBody = nullptr;
		RaceGoalMaterial = nullptr;

		ghostAP = nullptr;
		ghostCP = nullptr;
		ghostSMP = nullptr;
		ghostGEP = nullptr;
		ghostMDP = nullptr;

		ghostC = nullptr;
		raceSC = nullptr;
		ghostRaceTimer = nullptr;
		BaseGhostManager = nullptr;

		StartPosition = nullptr;
		FinishPosition = nullptr;
		raceFinishZone = nullptr;

		raceTimerDivisorMinute = nullptr;
		raceTimerDivisorSecond = nullptr;
		raceTimerText = nullptr;

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

		seinRecorder = nullptr;
		newSeinMimicGhost = nullptr;

		FrameLogger.CleanUp();
	}

	void RemoveCheckpoint(int index)
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

	void SetCheckpointPosition(tem::Vector3 position, int index)
	{
		if (raceCheckpoints.size() > index)
		{
			TransformSetPosition(raceCheckpoints[index], position);
		}
	}

	bool CheckIfHitAllCheckpoints()
	{
		int count = 0;

		for (auto b : raceCheckpointsHit)
		{
			if (b == true)
				count++;
		}

		return count >= raceCheckpointsHit.size();
	}

	void CheckIfInsideCheckpoint(tem::Vector3 previousPosition, tem::Vector3 currentPosition)
	{
		for (int i = 0; i < raceCheckpointsRects.size(); i++)
		{
			app::Rect* rect = raceCheckpointsRects[i];
			bool wasInside = IsPositionInsideRect(rect, previousPosition);
			bool currentlyInside = IsPositionInsideRect(rect, currentPosition);
			bool wasBetween = IsRectBetweenPositions(rect, previousPosition, currentPosition);
			if (wasInside || currentlyInside || wasBetween)
			{
 				raceCheckpointsHit[i] = true;
			}
		}
	}

	bool IsPositionInsideRect(app::Rect* rect, tem::Vector3 position)
	{
		return rect->m_YMin < position.Y&& rect->m_YMin + rect->m_Height > position.Y && rect->m_XMin - (rect->m_Width / 2) < position.X && position.X < rect->m_XMin + (rect->m_Width / 2);
	}

	bool IsRectBetweenPositions(app::Rect* rect, tem::Vector3 start, tem::Vector3 end)
	{
		return (start.X < rect->m_XMin && rect->m_XMin < end.X || start.X > rect->m_XMin && rect->m_XMin > end.X) && (start.Y < rect->m_YMin && rect->m_YMin < end.Y || start.Y > rect->m_YMin && rect->m_YMin > end.Y);
	}

	void CheckTimer()
	{
		if (ghostRaceTimer != nullptr && (ghostRaceTimer->fields.m_startedRace == true || CountdownHasStarted == true))
		{
			float raceFloat = ghostRaceTimer->fields._ElapsedTime_k__BackingField;

			if (CountdownHasStarted == true && playingAnimation == true && totalFrames >= startedWeRacing + (1000 / 16.6666f * 3))
			{
				app::SeinPlayAnimationController_StopAnimation(seinPlayAnimationController, NULL);
				playingAnimation = false;
				CountdownHasStarted = false;

				RunGhost();
			}
			else
			{
				CheckIfInsideCheckpoint(seinOldPosition, Sein->fields.PlatformBehaviour->fields.PlatformMovement->fields.m_oldPosition);
				seinOldPosition = Sein->fields.PlatformBehaviour->fields.PlatformMovement->fields.m_oldPosition;

				if (CountdownHasStarted == false)
					FrameLogger.LoggFrame();

				if (raceFloat >= RaceDuration + 60.0f)
				{
					app::RaceTimer_Stop(ghostRaceTimer, NULL);
				}

				app::Vector3 seinPosition = app::SeinCharacter_get_Position(Sein, NULL);
				if (raceFinishZone != nullptr)
					IsFinished = app::PlayerInsideZoneChecker_get_IsInside(raceFinishZone, NULL);

				if (IsFinished == true && CheckIfHitAllCheckpoints() == true)
				{
					FinishedRace(raceFloat);
				}
			}

			if (CountdownHasStarted == true)
				raceFloat = 3.0f - raceFloat;
			
			UpdateTimer(raceFloat);
			CheckIfGhostsFinished();
		}
	}

	void FinishedRace(float time)
	{
		app::RaceTimer_Stop(ghostRaceTimer, NULL);
		app::SeinCharacter_PlaceOnGround(Sein, NULL);
		app::Vector3* zeroSpeed = (app::Vector3*)il2cpp_object_new((Il2CppClass*)app::Vector3__TypeInfo);
		zeroSpeed->z = zeroSpeed->y = zeroSpeed->x = 0;
		app::SeinCharacter_set_Speed(Sein, *zeroSpeed, NULL);

		if (seinPlayAnimationController != nullptr && RaceFinishAnimation != nullptr)
		{
			if (AttemptManager.BestAttempt.RaceTime > ghostRaceTimer->fields._ElapsedTime_k__BackingField)
			{
				WriteRecorder();
				app::SeinPlayAnimationController_PlayAnimation_1(seinPlayAnimationController, RaceTopScoreAnimation, NULL);
			}
			else if (AttemptManager.BestAttempt.RaceTime > ghostRaceTimer->fields._PersonalBestTime_k__BackingField)
			{
				WriteRecorder();
				app::SeinPlayAnimationController_PlayAnimation_1(seinPlayAnimationController, RaceNewPBAnimation, NULL);
			}
			else
			{
				app::SeinPlayAnimationController_PlayAnimation_1(seinPlayAnimationController, RaceFinishAnimation, NULL);
			}
		}

		AttemptManager.AddAttempt(time);
		FrameLogger.DisplayData(tem::Vector3(FinishPosition->x, FinishPosition->y, FinishPosition->z));
		CleanupGhosts();
		app::RaceTimer_Stop(ghostRaceTimer, NULL);
		StopRecorder();
	}

	void UpdateTimer(float time)
	{
		double minutes = std::floor(std::fmod(time * 1000.0f / (1000.0f * 60.0f), 60));// std::floor(raceFloat / (1000.0f * 60.0f) % 60);
		double seconds = std::floor(std::fmod(time * 1000.0f / 1000.0f, 60));// std::floor(raceFloat / 1000.0f % 60);
		double milliseconds = std::floor(std::fmod(time * 1000.0f, 1000));

		std::string raceTimerMinute = sutil::DoubleToStr(minutes);
		app::String* raceTimerMinuteS = string_new(raceTimerMinute.data());

		std::string raceTimerSeconds = sutil::DoubleToStr(seconds);
		raceTimerSeconds = raceTimerSeconds.length() == 2 ? raceTimerSeconds : "0" + raceTimerSeconds;
		std::string raceTimerSecondsOne = raceTimerSeconds.substr(1, 1);
		std::string raceTimerSecondsTen = raceTimerSeconds.substr(0, 1);
		app::String* raceTimerSecondsTenS = string_new(raceTimerSecondsTen.data());
		app::String* raceTimerSecondsOneS = string_new(raceTimerSecondsOne.data());

		std::string raceTimerMilliseconds = sutil::DoubleToStr(milliseconds);
		raceTimerMilliseconds = raceTimerMilliseconds.length() == 3 ? raceTimerMilliseconds : (raceTimerMilliseconds.length() == 2 ? "0" + raceTimerMilliseconds : "00" + raceTimerMilliseconds);
		std::string raceTimerMillisecondsOne = raceTimerMilliseconds.substr(2, 1);
		std::string raceTimerMillisecondsTen = raceTimerMilliseconds.substr(1, 1);
		std::string raceTimerMillisecondsHundred = raceTimerMilliseconds.substr(0, 1);
		app::String* raceTimerMillisecondsOneS = string_new(raceTimerMillisecondsOne.data());
		app::String* raceTimerMillisecondsTenS = string_new(raceTimerMillisecondsTen.data());
		app::String* raceTimerMillisecondsHundredS = string_new(raceTimerMillisecondsHundred.data());

		SetTimer(raceTimerMinuteS, raceTimerSecondsTenS, raceTimerSecondsOneS, raceTimerMillisecondsOneS, raceTimerMillisecondsTenS, raceTimerMillisecondsHundredS);
	}

	void SetTimer(app::String* Minute, app::String* SecondsTen, app::String* SecondsOne, app::String* MillisecondsHundred, app::String* MillisecondsTen, app::String* MillisecondsOne)
	{
		if (raceTimerText != nullptr && raceTimerText->fields._._._._.m_CachedPtr != nullptr && raceTimerText->fields.Minute != nullptr &&
			raceTimerText->fields.Minute->fields._._._._.m_CachedPtr != nullptr && raceTimerText->fields.ColonMin != nullptr && raceTimerText->fields.ColonMin->fields._._._._.m_CachedPtr != nullptr &&
			raceTimerDivisorMinute != nullptr && raceTimerText->fields.SecondTen != nullptr && raceTimerText->fields.SecondTen->fields._._._._.m_CachedPtr != nullptr &&
			raceTimerText->fields.SecondOne != nullptr && raceTimerText->fields.SecondOne->fields._._._._.m_CachedPtr != nullptr && raceTimerDivisorSecond != nullptr &&
			raceTimerText->fields.MiliHund != nullptr && raceTimerText->fields.MiliHund->fields._._._._.m_CachedPtr != nullptr && raceTimerText->fields.MiliTen != nullptr &&
			raceTimerText->fields.MiliTen->fields._._._._.m_CachedPtr != nullptr)
		{
			app::TextBox_SetText_1(raceTimerText->fields.Minute, Minute, NULL);
			app::TextBox_SetText_1(raceTimerText->fields.ColonMin, raceTimerDivisorMinute, NULL);
			app::TextBox_SetText_1(raceTimerText->fields.SecondTen, SecondsTen, NULL);
			app::TextBox_SetText_1(raceTimerText->fields.SecondOne, SecondsOne, NULL);
			app::TextBox_SetText_1(raceTimerText->fields.ColonSec, raceTimerDivisorSecond, NULL);
			app::TextBox_SetText_1(raceTimerText->fields.MiliHund, MillisecondsHundred, NULL);
			app::TextBox_SetText_1(raceTimerText->fields.MiliTen, MillisecondsTen, NULL);


			app::TextBox_SetText_1(raceTimerText->fields.MiliOne, MillisecondsOne, NULL);

			if (ghostRaceTimer->fields._ElapsedTime_k__BackingField >= ghostRaceTimer->fields._BestTime_k__BackingField)
			{
				app::Color redColor = Color();
				redColor.a = 1.0f;
				redColor.b = 0.0f;
				redColor.g = 0.0f;
				redColor.r = 1.0f;

				raceTimerText->fields.Minute->fields.color = redColor;
				raceTimerText->fields.ColonMin->fields.color = redColor;
				raceTimerText->fields.SecondTen->fields.color = redColor;
				raceTimerText->fields.SecondOne->fields.color = redColor;
				raceTimerText->fields.ColonSec->fields.color = redColor;
				raceTimerText->fields.MiliHund->fields.color = redColor;
				raceTimerText->fields.MiliTen->fields.color = redColor;
				raceTimerText->fields.MiliOne->fields.color = redColor;
			}
			else
			{
				app::Color whiteColor = Color();
				whiteColor.a = 1.0f;
				whiteColor.b = 1.0f;
				whiteColor.g = 1.0f;
				whiteColor.r = 1.0f;

				raceTimerText->fields.Minute->fields.color = whiteColor;
				raceTimerText->fields.ColonMin->fields.color = whiteColor;
				raceTimerText->fields.SecondTen->fields.color = whiteColor;
				raceTimerText->fields.SecondOne->fields.color = whiteColor;
				raceTimerText->fields.ColonSec->fields.color = whiteColor;
				raceTimerText->fields.MiliHund->fields.color = whiteColor;
				raceTimerText->fields.MiliTen->fields.color = whiteColor;
				raceTimerText->fields.MiliOne->fields.color = whiteColor;
			}

			app::TextBox_RefreshText(raceTimerText->fields.Minute, NULL);
			app::TextBox_RefreshText(raceTimerText->fields.ColonMin, NULL);
			app::TextBox_RefreshText(raceTimerText->fields.SecondTen, NULL);
			app::TextBox_RefreshText(raceTimerText->fields.SecondOne, NULL);
			app::TextBox_RefreshText(raceTimerText->fields.ColonSec, NULL);
			app::TextBox_RefreshText(raceTimerText->fields.MiliHund, NULL);
			app::TextBox_RefreshText(raceTimerText->fields.MiliTen, NULL);
			app::TextBox_RefreshText(raceTimerText->fields.MiliOne, NULL);
		}
		else
		{
			//Get race timer
			app::Type* type = GetType("", "UnityRaceTimerDisplay");
			app::Object_1__Array* arr2222 = app::Object_1_FindObjectsOfType(type, NULL);

			if (arr2222->vector[0] != nullptr)
				raceTimerText = (app::UnityRaceTimerDisplay*)arr2222->vector[0];
		}
	}

	void CreateRecorder()
	{
		ghostC = Moon::GhostManager::GetOrCreateRecorder();

		if (ghostC != nullptr)
		{
			if (ghostC->fields.m_plugins->fields._size == 0)
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

				app::GhostRecorder_RegisterPluginAbilities(ghostC, ghostAP, NULL);
				app::GhostRecorder_RegisterPlugin(ghostC, (app::IGhostRecorderPlugin*)ghostCP, NULL);
				app::GhostRecorder_RegisterPlugin(ghostC, (app::IGhostRecorderPlugin*)ghostSMP, NULL);
				app::GhostRecorder_RegisterPlugin(ghostC, (app::IGhostRecorderPlugin*)ghostGEP, NULL);
				app::GhostRecorder_RegisterPlugin(ghostC, (app::IGhostRecorderPlugin*)ghostMDP, NULL);
			}

			if (ghostC->fields.m_filePath == nullptr)
			{
				app::String* MRecorderPath = string_new((racePath + "Default").c_str());

				app::GhostRecorder_InitializeRecorder(ghostC, MRecorderPath, NULL);
			}
		}
	}

	bool StartRecorder()
	{
		if (ghostC != nullptr)
		{
			app::GhostRecorder_StartRecorder(ghostC, NULL);
			return true;
		}
		return false;
	}

	bool StopRecorder()
	{
		if (ghostC != nullptr) {
			app::GhostRecorder_StopRecorder(ghostC, NULL);
			return true;
		}
		return false;
	}

	bool WriteRecorder()
	{
		if (ghostC != nullptr) {
			app::GhostRecorder_FinalizeFrame(ghostC, NULL);
			app::GhostRecorder_WriteToFile(ghostC, NULL);

			app::String* raceFile = app::GhostRecorder_get_FilePath(ghostC, NULL);
			std::string raceFileS = sutil::convert_csstring(raceFile);
			sutil::ConvertGhostRecordingToBase64(raceFileS, racePath + raceName + ".ghost");
			return true;
		}
		return false;
	}

	void FinalizeGhostFrame()
	{
		if (ghostC != nullptr && ghostC->fields.Enabled == true)
			app::GhostRecorder_FinalizeFrame(ghostC, NULL);
	}

	bool CreateGhost(std::string path)
	{
		if (BaseGhostManager != nullptr)
		{
			std::string contents = sutil::readFile(path);
			const char* gP = contents.data();
			app::String* gPath = string_new(gP);
			const char* gPN = "SPOOOOOKKKYYY";
			app::String* gName = string_new(gPN);
			app::GhostPlayer* ghostPlayer = app::GhostManager_createGhost_1(BaseGhostManager, gName, gPath, NULL);

			if (ghostPlayer != nullptr)
			{
				ActiveGhostPlayers.push_back(ghostPlayer);
				app::GhostPlayer_ExtractMetaData(ghostPlayer, NULL);
				app::GhostRecorderData_LoadFromReplay(ghostC->fields.GhostRecorderData, gPath, NULL);
				std::vector< app::IGhostFrameData*> frameData;
				app::GhostFrame* firstFrame = app::GhostRecorderData_GetFrame(ghostC->fields.GhostRecorderData, 0, NULL);

				int lastGhostFrame = ghostC->fields.GhostRecorderData->fields.Frames->fields._size - 1;
				app::GhostFrame* lastFrame = app::GhostRecorderData_GetFrame(ghostC->fields.GhostRecorderData, lastGhostFrame, NULL);
				while (lastFrame->fields.FrameData->fields._size == 0)
				{
					lastFrame = app::GhostRecorderData_GetFrame(ghostC->fields.GhostRecorderData, lastGhostFrame, NULL);
					lastGhostFrame--;
				}

				/*for (int i = 0; i < firstFrame->fields.FrameData->fields._size; i++)
				{
					app::GhostTransformData* data = (app::GhostTransformData*)firstFrame->fields.FrameData->fields._items->vector[i];
					if (data != nullptr && data->fields.m_position.x != 0.0f && data->fields.m_position.y != 0.0f)
						StartPosition = &data->fields.m_position;
				}

				for (int i = 0; i < lastFrame->fields.FrameData->fields._size; i++)
				{
					app::GhostTransformData* data = (app::GhostTransformData*)lastFrame->fields.FrameData->fields._items->vector[i];
					if (data != nullptr && data->fields.m_position.x != 0.0f && data->fields.m_position.y != 0.0f)
						FinishPosition = &data->fields.m_position;
				}*/

				/*if (StartPosition != nullptr)
					app::SeinCharacter_set_Position(Sein, *StartPosition, NULL);*/

				if (ghostC->fields.GhostRecorderData != nullptr)
					RaceDuration = ghostC->fields.GhostRecorderData->fields.Duration;

				app::Color purple;
				purple.a = 0.8f;
				purple.b = 0.8f;
				purple.g = 0.2f;
				purple.r = 0.5f;
				app::GameObject* newGhostIcon = areaMapManager.CreateNewIconPlayerIcon(StartPosition, purple);
				ActiveGhostIcons.push_back(newGhostIcon);

				CountdownHasStarted = true;
				app::RaceTimer_StartTimer(ghostRaceTimer, NULL);

				app::SeinPlayAnimationController_PlayAnimation_1(seinPlayAnimationController, RaceLoopAnimation, NULL);
				startedWeRacing = totalFrames;
				playingAnimation = true;

				return true;
			}
		}
		return false;
	}

	void CreateFinishLine()
	{
		if (RaceGoalObject == nullptr)
		{
			app::String* raceFinishName = string_new("RaceFinish");
			RaceGoalObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)app::GameObject__TypeInfo);
			app::GameObject__ctor(RaceGoalObject, raceFinishName, NULL);

			DebugDrawer debugDrawer = DebugDrawer();
			app::GameObject* raceFinishDebug = debugDrawer.CreateDebugObject(graphColors.Pink, FinishPosition);

			app::Type* playerInsideZoneType = GetType("", "PlayerInsideZoneChecker");
			raceFinishZone = (app::PlayerInsideZoneChecker*)app::GameObject_AddComponent(raceFinishDebug, playerInsideZoneType, NULL);

			raceFinishZone->fields.OnlyTriggerIfGrounded = false;
			app::Vector2* size2 = (app::Vector2*)il2cpp_object_new((Il2CppClass*)Vector2__TypeInfo);
			size2->x = 3.0f;
			size2->y = 15.0f;
			raceFinishZone->fields._.Size = *size2;
			auto rectcc = GetClass<>("UnityEngine", "Rect");
			app::Rect* rect2 = (app::Rect*)il2cpp_object_new((Il2CppClass*)rectcc);
			rect2->m_Height = 15.0f;
			rect2->m_Width = 3.0f;
			rect2->m_XMin = FinishPosition->x;
			rect2->m_YMin = FinishPosition->y - 0.5f;
			raceFinishZone->fields._.m_bounds = *rect2;

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
			app::GameObject* RaceBodyA = (app::GameObject*)il2cpp_object_new((Il2CppClass*)app::GameObject__TypeInfo);
			app::GameObject__ctor(RaceBodyA, raceBodyName, NULL);
			app::Transform* transformRaceBodyA = app::GameObject_get_transform(RaceBodyA, NULL);

			raceBodyName = string_new("RaceCenter");
			app::GameObject* RaceBodyB = (app::GameObject*)il2cpp_object_new((Il2CppClass*)app::GameObject__TypeInfo);
			app::GameObject__ctor(RaceBodyB, raceBodyName, NULL);
			app::Transform* transformRaceBodyB = app::GameObject_get_transform(RaceBodyB, NULL);

			raceBodyName = string_new("RaceCollar");
			app::GameObject* RaceBodyC = (app::GameObject*)il2cpp_object_new((Il2CppClass*)app::GameObject__TypeInfo);
			app::GameObject__ctor(RaceBodyC, raceBodyName, NULL);
			app::Transform* transformRaceBodyC = app::GameObject_get_transform(RaceBodyC, NULL);

			raceBodyName = string_new("RaceCollarGlow");
			app::GameObject* RaceBodyD = (app::GameObject*)il2cpp_object_new((Il2CppClass*)app::GameObject__TypeInfo);
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
			std::vector<GameObject*> BodyParts = { RaceBodyA, RaceBodyB, RaceBodyC, RaceBodyD };
			for (int i = 0; i < meshFilters.size(); i++)
			{
				app::MeshRenderer* meshRenderer = (app::MeshRenderer*)app::GameObject_AddComponent(BodyParts[i], meshRendererType, NULL);
				app::Material* meshMat = app::Renderer_GetMaterial((app::Renderer*)meshRenderers[i], NULL);
				app::Renderer_SetMaterial((app::Renderer*)meshRenderer, meshMat, NULL);
				app::Renderer_set_sortingOrder((app::Renderer*)meshRenderer, sortingOrder[i], NULL);

				app::MeshFilter* meshFilter = (app::MeshFilter*)app::GameObject_AddComponent(BodyParts[i], meshFilterType, NULL);
				app::Mesh* mesh = app::MeshFilter_get_mesh(meshFilters[i], NULL);
				app::MeshFilter_set_mesh(meshFilter, mesh, NULL);

				app::GameObject_set_active(BodyParts[i], true, NULL);
			}
			//Renderer_set_sortingOrder((Renderer*)cubeMeshRenderer, 14000, NULL);
			//Renderer_SetMaterial((Renderer*)cubeMeshRenderer, RaceDataMaterial, NULL);
			//GameObject_set_active(cube, true, NULL);
			TransformSetPosition(RaceGoalObject, FinishPosition);

			app::GameObject_set_active(RaceGoalObject, true, NULL);
		}
		/*else
		{
			TransformSetPosition(RaceGoalObject, FinishPosition);
		}*/
	}

	void SetupRace(float raceDuration = 60.0f)
	{
		FrameLogger.CleanUpData();

		if (ghostC->fields.GhostRecorderData == nullptr)
		{
			auto Class1 = GetClass<>("", "GhostRecorderData");
			app::GhostRecorderData* ghostRecorderData = (app::GhostRecorderData*)il2cpp_object_new((Il2CppClass*)Class1);
			app::GhostRecorderData__ctor(ghostRecorderData, NULL);
			ghostC->fields.GhostRecorderData = ghostRecorderData;
		}

		if (StartPosition != nullptr)
			app::SeinCharacter_set_Position(Sein, *StartPosition, NULL);

		RaceDuration = raceDuration;
		CreateFinishLine();

		if (std::filesystem::exists(racePath + raceName + ".ghost") == true)
		{
			CreateGhost(racePath + raceName + ".ghost");
		}

		CountdownHasStarted = true;
		app::RaceTimer_StartTimer(ghostRaceTimer, NULL);

		app::SeinPlayAnimationController_PlayAnimation_1(seinPlayAnimationController, RaceLoopAnimation, NULL);
		startedWeRacing = totalFrames;
		playingAnimation = true;
	}

	void StartRaceTimer()
	{
		if (ghostRaceTimer != nullptr)
		{
			if (ghostC == nullptr)
				CreateRecorder();

			StopRecorder();
			StartRecorder();

			CountdownHasStarted = false;
			app::RaceTimer_Reset(ghostRaceTimer, NULL);
			ghostRaceTimer->fields._TimeLimit_k__BackingField = RaceDuration + 60.0f;

			if (AttemptManager.BestAttempt.RaceTime != 10000000.0f)
			{
				ghostRaceTimer->fields._BestTime_k__BackingField = AttemptManager.BestAttempt.RaceTime;
				ghostRaceTimer->fields._PersonalBestTime_k__BackingField = AttemptManager.BestAttempt.RaceTime;
			}
			ghostRaceTimer->fields._TimeToBeat_k__BackingField = RaceDuration;
			ghostRaceTimer->fields._IsSuspended_k__BackingField = false;
			app::RaceTimer_SetTimeLimit(ghostRaceTimer, RaceDuration + 60.0f, NULL);
			app::RaceTimer_StartTimer(ghostRaceTimer, NULL);
		}
	}

	void RunGhost()
	{
		for (app::GhostPlayer*& ghostPlayer : ActiveGhostPlayers)
		{
			app::GhostPlayer_Run(ghostPlayer, NULL);
		}

		StartRaceTimer();
	}

	void CheckIfGhostsFinished()
	{
		std::vector<app::GhostPlayer*> ghostsStillRunning;
		std::vector< app::GameObject*> activeGhostIconsRunning;
		for (int i = 0; i < ActiveGhostPlayers.size(); i++)
		{
			app::GhostPlayer* ghost = ActiveGhostPlayers[i];
			areaMapManager.UpdateIconPosition(ActiveGhostIcons[i], app::GhostPlayer_get_Position(ghost, NULL));

			if (ghost->fields._IsFinished_k__BackingField)
			{
				auto ghostIcon = ActiveGhostIcons[i];
				app::GhostPlayer_Stop(ghost, NULL);
				app::Object_1_Destroy_1((app::Object_1*)ghost, NULL);
				app::Object_1_Destroy_1((app::Object_1*)ghostIcon, NULL);
			}
			else
			{
				ghostsStillRunning.push_back(ghost);
				activeGhostIconsRunning.push_back(ActiveGhostIcons[i]);
			}
		}
		ActiveGhostPlayers = ghostsStillRunning;
		ActiveGhostIcons = activeGhostIconsRunning;
	}

	void CleanupGhosts()
	{
		for (int i = 0; i < ActiveGhostPlayers.size(); i++)
		{
			auto ghost = ActiveGhostPlayers[i];
			auto ghostIcon = ActiveGhostIcons[i];
			app::GhostPlayer_Stop(ghost, NULL);
			app::Object_1_Destroy_1((app::Object_1*)ghost, NULL);
			app::Object_1_Destroy_1((app::Object_1*)ghostIcon, NULL);
		}
		ActiveGhostPlayers.clear();
		ActiveGhostIcons.clear();
	}

	/*if (totalFrames >= 200 && raceManager.newSeinMimicGhost == nullptr)
	{
		raceManager.CreateMimicGhost();
	}

	if (totalFrames >= 249 && raceManager.newSeinMimicGhost != nullptr && totalFrames % 50 == 0)
	{
		raceManager.UpdateMimicGhostFrameData(raceManager.lastMimicFrameUpdate);
	}*/

	void CreateMimicGhost()
	{
		std::string ghostPath = sutil::getexepath();
		sutil::ReplaceS(ghostPath, "oriwotw.exe", "oriwotw_Data\\output\\ghosts\\works.ghost");
		std::string contents = sutil::readFile(ghostPath);
		const char* gP = contents.data();
		app::String* gPath = string_new(gP);
		const char* gPN = "SPOOOOOKKKYYY";
		app::String* gName = string_new(gPN);
		newSeinMimicGhost = app::GhostManager_createGhost_1(BaseGhostManager, gName, gPath, NULL);

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

	void RegisterGhostPlayerPlugins(app::GhostPlayer* ghostPlayer)
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
			ghostCP = (app::GhostCharacterPlugin*)il2cpp_object_new((Il2CppClass*)Class2);
			app::GhostPlayer_RegisterPlugin(ghostPlayer, (app::IGhostRecorderPlugin*)ghostCP, NULL);
			ghostCP->fields._.m_player = ghostPlayer;
		}

		if (ghostGenericEventsPluginB == false)
		{
			auto Class4 = GetClass<>("", "GhostGenericEventsPlugin");
			ghostGEP = (app::GhostGenericEventsPlugin*)il2cpp_object_new((Il2CppClass*)Class4);
			app::GhostPlayer_RegisterPlugin(ghostPlayer, (app::IGhostRecorderPlugin*)ghostGEP, NULL);
			ghostGEP->fields._.m_player = ghostPlayer;
		}

		if (ghostCharacterAbilitiesPluginB == false)
		{
			auto Class1 = GetClass<>("", "GhostCharacterAbilitiesPlugin");
			ghostAP = (app::GhostCharacterAbilitiesPlugin*)il2cpp_object_new((Il2CppClass*)Class1);
			app::GhostPlayer_RegisterPlugin(ghostPlayer, (app::IGhostRecorderPlugin*)ghostAP, NULL);
			ghostAP->fields._.m_player = ghostPlayer;
		}

		if (ghostStateMachinePluginB == false)
		{
			auto Class3 = GetClass<>("", "GhostStateMachinePlugin");
			ghostSMP = (app::GhostStateMachinePlugin*)il2cpp_object_new((Il2CppClass*)Class3);
			app::GhostPlayer_RegisterPlugin(ghostPlayer, (app::IGhostRecorderPlugin*)ghostSMP, NULL);
			ghostSMP->fields._.m_player = ghostPlayer;
		}
	}

	void UpdateMimicGhostFrameData(int lastFrame)
	{
		if (ghostHasStarted == true)
		{
			app::GhostRecorder_FinalizeFrame(seinRecorder, NULL);
			GetSeinFrames();
			newSeinMimicGhost->fields.m_isStarted = true;
			newSeinMimicGhost->fields._IsFinished_k__BackingField = false;
		}
	}

	app::GhostRecorder* CreateNewGhostRecorder()
	{
		auto Class1 = GetClass<>("", "GhostRecorder");
		app::GhostRecorder* ghostRecorder = (app::GhostRecorder*)il2cpp_object_new((Il2CppClass*)Class1);
		app::GhostRecorder__ctor(ghostRecorder, NULL);
		app::String* gName = string_new("SeinRecorder");
		app::GameObject__ctor((app::GameObject*)ghostRecorder, gName, NULL);

		return ghostRecorder;
	}

	void CreateSeinRecorder()
	{
		seinRecorder = Moon::GhostManager::GetOrCreateRecorder();// CreateNewGhostRecorder();

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

				app::GhostRecorder_RegisterPluginAbilities(seinRecorder, ghostAP, NULL);
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

	void GetSeinFrames()
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
};

#endif