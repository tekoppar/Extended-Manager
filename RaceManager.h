#include "il2cpp-appdata.h"
#include "helpers.h"
using namespace app;

/*#include "Adresses.h"
#include "ManagerDef.h"
#include "StringUtils.h"
#include "GhostManager.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Transform.h"*/

class RaceManager
{
public :
	std::vector<GhostPlayer*> ActiveGhostPlayers;
	GhostCharacterAbilitiesPlugin* ghostAP;
	GhostCharacterPlugin* ghostCP;
	GhostStateMachinePlugin* ghostSMP;
	GhostGenericEventsPlugin* ghostGEP;
	GhostRecordingMetaDataPlugin* ghostMDP;
	GhostRecorder* ghostC;
	RaceSystem* raceSC;
	UnityRaceTimerDisplay* raceTimerText;
	RaceTimer* ghostRaceTimer;
	GhostManager* BaseGhostManager;

	String* raceTimerDivisorMinute = nullptr; 
	String* raceTimerDivisorSecond = nullptr;

	/*void SetupManager();
	void CheckTimer();
	void CreateRecorder();
	bool StartRecorder();
	bool StopRecorder();
	bool WriteRecorder();
	bool CreateGhost(std::string path);
	bool RunGhost();
	void CheckIfGhostsFinished();*/

	void SetupManager()
	{
		if (raceSC == nullptr)
			raceSC = (RaceSystem*)il2cpp_object_new((Il2CppClass*)RaceSystem__TypeInfo);

		if (ghostRaceTimer == nullptr)
			ghostRaceTimer = raceSC->klass->static_fields->_Instance_k__BackingField->fields.m_timer;

		if (raceTimerText == nullptr)
		{
			//Get race timer
			Type* type = GetType("", "UnityRaceTimerDisplay");
			Object_1__Array* arr2222 = Object_1_FindObjectsOfType(type, NULL);

			if (arr2222->vector[0] != nullptr)
				raceTimerText = (UnityRaceTimerDisplay*)arr2222->vector[0];
		}

		raceTimerDivisorMinute = string_new(":");
		raceTimerDivisorSecond = string_new(".");
	}

	void CheckTimer()
	{
		if (ghostRaceTimer != nullptr && ghostRaceTimer->fields.m_startedRace == true)
		{
			float raceFloat = ghostRaceTimer->fields._ElapsedTime_k__BackingField;

			if (raceFloat >= 60.0f)
			{
				RaceTimer_Stop(ghostRaceTimer, NULL);
			}

			double minutes = std::floor(std::fmod(raceFloat * 1000.0f / (1000.0f * 60.0f), 60));// std::floor(raceFloat / (1000.0f * 60.0f) % 60);
			double seconds = std::floor(std::fmod(raceFloat * 1000.0f / 1000.0f, 60));// std::floor(raceFloat / 1000.0f % 60);
			double milliseconds = std::floor(std::fmod(raceFloat * 1000.0f, 1000));

			std::string raceTimerMinute = DoubleToStr(minutes);
			String* raceTimerMinuteS = string_new(raceTimerMinute.data());

			std::string raceTimerSeconds = DoubleToStr(seconds);
			raceTimerSeconds = raceTimerSeconds.length() == 2 ? raceTimerSeconds : "0" + raceTimerSeconds;
			std::string raceTimerSecondsOne = raceTimerSeconds.substr(1, 1);
			std::string raceTimerSecondsTen = raceTimerSeconds.substr(0, 1);
			String* raceTimerSecondsTenS = string_new(raceTimerSecondsTen.data());
			String* raceTimerSecondsOneS = string_new(raceTimerSecondsOne.data());

			std::string raceTimerMilliseconds = DoubleToStr(milliseconds);
			raceTimerMilliseconds = raceTimerMilliseconds.length() == 3 ? raceTimerMilliseconds : (raceTimerMilliseconds.length() == 2 ? "0" + raceTimerMilliseconds : "00" + raceTimerMilliseconds);
			std::string raceTimerMillisecondsOne = raceTimerMilliseconds.substr(2, 1);
			std::string raceTimerMillisecondsTen = raceTimerMilliseconds.substr(1, 1);
			std::string raceTimerMillisecondsHundred = raceTimerMilliseconds.substr(0, 1);
			String* raceTimerMillisecondsOneS = string_new(raceTimerMillisecondsOne.data());
			String* raceTimerMillisecondsTenS = string_new(raceTimerMillisecondsTen.data());
			String* raceTimerMillisecondsHundredS = string_new(raceTimerMillisecondsHundred.data());

			if (raceTimerText != nullptr)
			{
				TextBox_SetText_1(raceTimerText->fields.Minute, raceTimerMinuteS, NULL);
				TextBox_SetText_1(raceTimerText->fields.ColonMin, raceTimerDivisorMinute, NULL);
				TextBox_SetText_1(raceTimerText->fields.SecondTen, raceTimerSecondsTenS, NULL);
				TextBox_SetText_1(raceTimerText->fields.SecondOne, raceTimerSecondsOneS, NULL);
				TextBox_SetText_1(raceTimerText->fields.ColonSec, raceTimerDivisorSecond, NULL);
				TextBox_SetText_1(raceTimerText->fields.MiliHund, raceTimerMillisecondsHundredS, NULL);
				TextBox_SetText_1(raceTimerText->fields.MiliTen, raceTimerMillisecondsTenS, NULL);
				TextBox_SetText_1(raceTimerText->fields.MiliOne, raceTimerMillisecondsOneS, NULL);

				if (ghostRaceTimer->fields._ElapsedTime_k__BackingField >= ghostRaceTimer->fields._BestTime_k__BackingField)
				{
					Color redColor = Color();
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

				TextBox_RefreshText(raceTimerText->fields.Minute, NULL);
				TextBox_RefreshText(raceTimerText->fields.ColonMin, NULL);
				TextBox_RefreshText(raceTimerText->fields.SecondTen, NULL);
				TextBox_RefreshText(raceTimerText->fields.SecondOne, NULL);
				TextBox_RefreshText(raceTimerText->fields.ColonSec, NULL);
				TextBox_RefreshText(raceTimerText->fields.MiliHund, NULL);
				TextBox_RefreshText(raceTimerText->fields.MiliTen, NULL);
				TextBox_RefreshText(raceTimerText->fields.MiliOne, NULL);
			}

			RaceManager::CheckIfGhostsFinished();
		}
	}

	void CreateRecorder()
	{
		ghostC = Moon::GhostManager::GetOrCreateRecorder();

		auto Class1 = GetClass<>("", "GhostCharacterAbilitiesPlugin");
		ghostAP = (GhostCharacterAbilitiesPlugin*)il2cpp_object_new((Il2CppClass*)Class1);
		auto Class2 = GetClass<>("", "GhostCharacterPlugin");
		ghostCP = (GhostCharacterPlugin*)il2cpp_object_new((Il2CppClass*)Class2);
		auto Class3 = GetClass<>("", "GhostStateMachinePlugin");
		ghostSMP = (GhostStateMachinePlugin*)il2cpp_object_new((Il2CppClass*)Class3);
		auto Class4 = GetClass<>("", "GhostGenericEventsPlugin");
		ghostGEP = (GhostGenericEventsPlugin*)il2cpp_object_new((Il2CppClass*)Class4);
		auto Class5 = GetClass<>("", "GhostRecordingMetaDataPlugin");
		ghostMDP = (GhostRecordingMetaDataPlugin*)il2cpp_object_new((Il2CppClass*)Class5);

		GhostRecorder_RegisterPluginAbilities(ghostC, ghostAP, NULL);
		GhostRecorder_RegisterPlugin(ghostC, (IGhostRecorderPlugin*)ghostCP, NULL);
		GhostRecorder_RegisterPlugin(ghostC, (IGhostRecorderPlugin*)ghostSMP, NULL);
		GhostRecorder_RegisterPlugin(ghostC, (IGhostRecorderPlugin*)ghostGEP, NULL);
		GhostRecorder_RegisterPlugin(ghostC, (IGhostRecorderPlugin*)ghostMDP, NULL);

		std::string ghostPath = getexepath();
		ReplaceS(ghostPath, "oriwotw.exe", "oriwotw_Data\\output\\ghosts\\swamp1\\test.ghost");
		String* MRecorderPath = string_new(ghostPath.c_str());

		GhostRecorder_InitializeRecorder(ghostC, MRecorderPath, NULL);
	}

	bool StartRecorder()
	{
		if (ghostC != nullptr)
		{
			GhostRecorder_StartRecorder(ghostC, NULL);
			return true;
		}
		return false;
	}

	bool StopRecorder()
	{
		if (ghostC != nullptr) {
			GhostRecorder_StopRecorder(ghostC, NULL);
			return true;
		}
		return false;
	}

	bool WriteRecorder()
	{
		if (ghostC != nullptr) {
			GhostRecorder_FinalizeFrame(ghostC, NULL);
			GhostRecorder_WriteToFile(ghostC, NULL);

			String* raceFile = GhostRecorder_get_FilePath(ghostC, NULL);
			std::string raceFileS = convert_csstring(raceFile);
			ConvertGhostRecordingToBase64(raceFileS);
			return true;
		}
		return false;
	}

	bool CreateGhost(std::string path)
	{
		std::string ghostPath = getexepath();
		ReplaceS(ghostPath, "oriwotw.exe", "oriwotw_Data\\output\\ghosts\\test.ghost");
		std::string contents = readFile(ghostPath);
		const char* gP = contents.data();
		String* gPath = string_new(gP);
		const char* gPN = "SPOOOOOKKKYYY";
		String* gName = string_new(gPN);
		GhostPlayer* ghostPlayer = GhostManager_createGhost_1(BaseGhostManager, gName, gPath, NULL);

		if (ghostPlayer != nullptr)
		{
			ActiveGhostPlayers.push_back(ghostPlayer);
			return true;
		}
		return false;
	}

	bool RunGhost()
	{
		for (GhostPlayer*& ghostPlayer : ActiveGhostPlayers)
		{
			GhostPlayer_Run(ghostPlayer, NULL);
		}

		if (ghostRaceTimer != nullptr)
		{
			ghostRaceTimer->fields._TimeLimit_k__BackingField = 60.0f;
			ghostRaceTimer->fields._BestTime_k__BackingField = 35.6f;
			ghostRaceTimer->fields._TimeToBeat_k__BackingField = 35.6f;
			ghostRaceTimer->fields._IsSuspended_k__BackingField = false;
			RaceTimer_SetTimeLimit(ghostRaceTimer, 60.0f, NULL);
			RaceTimer_StartTimer(ghostRaceTimer, NULL);

			return true;
		}

		return false;
	}

	void CheckIfGhostsFinished()
	{
		std::vector<GhostPlayer*> ghostsStillRunning;
		for (auto& ghost : ActiveGhostPlayers)
		{
			if (ghost->fields._IsFinished_k__BackingField)
			{
				GhostPlayer_Stop(ghost, NULL);
			}
			else
			{
				ghostsStillRunning.push_back(ghost);
			}
		}
		ActiveGhostPlayers = ghostsStillRunning;
	}
};