#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include "StringUtils.h"
#include "ManagerDef.h"
#include "Tem.h"
#include "RaceManager.h"

#include "TemRecorder.h"

void TemRecorder::CreateRecorder()
{
	/*app::Type* SeinSpiritSpearSpellPuppett = GetType("", "SeinSpiritSpearSpellPuppet");
	app::Object_1__Array* SeinSpiritSpearSpellPuppetarr = app::Object_1_FindObjectsOfTypeAll(SeinSpiritSpearSpellPuppett, NULL);
	app::SeinSpiritSpearSpellPuppet* spiritSpearPuppet = nullptr;
	if (SeinSpiritSpearSpellPuppetarr != nullptr)
		spiritSpearPuppet = (app::SeinSpiritSpearSpellPuppet*)SeinSpiritSpearSpellPuppetarr->vector[0];

	app::Type* SeinBowPuppett = GetType("", "SeinBowPuppet");
	app::Object_1__Array* SeinBowPuppetarr = app::Object_1_FindObjectsOfTypeAll(SeinBowPuppett, NULL);
	app::SeinBowPuppet* SeinBowPuppet = nullptr;
	if (SeinBowPuppetarr != nullptr)
		SeinBowPuppet = (app::SeinBowPuppet*)SeinBowPuppetarr->vector[0];

	app::Type* SeinFeatherFlapPuppett = GetType("", "SeinFeatherFlapPuppet");
	app::Object_1__Array* SeinFeatherFlapPuppetarr = app::Object_1_FindObjectsOfTypeAll(SeinFeatherFlapPuppett, NULL);
	app::SeinFeatherFlapPuppet* SeinFeatherFlapPuppet = nullptr;
	if (SeinFeatherFlapPuppetarr != nullptr)
		SeinFeatherFlapPuppet = (app::SeinFeatherFlapPuppet*)SeinFeatherFlapPuppetarr->vector[0];

	app::Type* SeinSpiritSlasht = GetType("", "SeinSpiritSlash");
	app::Object_1__Array* SeinSpiritSlasharr = app::Object_1_FindObjectsOfTypeAll(SeinSpiritSlasht, NULL);
	app::SeinSpiritSlash* SeinSpiritSlash = nullptr;
	if (SeinSpiritSlasharr != nullptr)
		SeinSpiritSlash = (app::SeinSpiritSlash*)SeinSpiritSlasharr->vector[0];

	app::Type* SeinBlazeSpellt = GetType("", "SeinBlazeSpell");
	app::Object_1__Array* SeinBlazeSpellarr = app::Object_1_FindObjectsOfTypeAll(SeinBlazeSpellt, NULL);
	app::SeinBlazeSpell* SeinBlazeSpell = nullptr;
	if (SeinBlazeSpellarr != nullptr)
		SeinBlazeSpell = (app::SeinBlazeSpell*)SeinBlazeSpellarr->vector[0];

	app::Type* SeinChakramSpellt = GetType("", "SeinChakramSpell");
	app::Object_1__Array* SeinChakramSpellarr = app::Object_1_FindObjectsOfTypeAll(SeinChakramSpellt, NULL);
	app::SeinChakramSpell* SeinChakramSpell = nullptr;
	if (SeinChakramSpellarr != nullptr)
		SeinChakramSpell = (app::SeinChakramSpell*)SeinChakramSpellarr->vector[0];

	app::Type* SeinCroucht = GetType("", "SeinCrouch");
	app::Object_1__Array* SeinCroucharr = app::Object_1_FindObjectsOfTypeAll(SeinCroucht, NULL);
	app::SeinCrouch* SeinCrouch = nullptr;
	if (SeinCroucharr != nullptr)
		SeinCrouch = (app::SeinCrouch*)SeinCroucharr->vector[0];

	app::Type* SeinGlowSpellt = GetType("", "SeinGlowSpell");
	app::Object_1__Array* SeinGlowSpellarr = app::Object_1_FindObjectsOfTypeAll(SeinGlowSpellt, NULL);
	app::SeinGlowSpell* SeinGlowSpell = nullptr;
	if (SeinGlowSpellarr != nullptr)
		SeinGlowSpell = (app::SeinGlowSpell*)SeinGlowSpellarr->vector[0];

	app::Type* SeinGrenadeAttackt = GetType("", "SeinGrenadeAttack");
	app::Object_1__Array* SeinGrenadeAttackarr = app::Object_1_FindObjectsOfTypeAll(SeinGrenadeAttackt, NULL);
	app::SeinGrenadeAttack* SeinGrenadeAttack = nullptr;
	if (SeinGrenadeAttackarr != nullptr)
		SeinGrenadeAttack = (app::SeinGrenadeAttack*)SeinGrenadeAttackarr->vector[0];

	app::Type* SeinMeditateSpellt = GetType("", "SeinMeditateSpell");
	app::Object_1__Array* SeinMeditateSpellarr = app::Object_1_FindObjectsOfTypeAll(SeinMeditateSpellt, NULL);
	app::SeinMeditateSpell* SeinMeditateSpell = nullptr;
	if (SeinMeditateSpellarr != nullptr)
		SeinMeditateSpell = (app::SeinMeditateSpell*)SeinMeditateSpellarr->vector[0];

	app::Type* SeinTurretSpellt = GetType("", "SeinTurretSpell");
	app::Object_1__Array* SeinTurretSpellarr = app::Object_1_FindObjectsOfTypeAll(SeinTurretSpellt, NULL);
	app::SeinTurretSpell* SeinTurretSpell = nullptr;
	if (SeinTurretSpellarr != nullptr)
		SeinTurretSpell = (app::SeinTurretSpell*)SeinTurretSpellarr->vector[0];

	
	app::Type* CharacterStatePuppett = GetType("", "CharacterStatePuppet");
	app::Object_1__Array* CharacterStatePuppettarr = app::Object_1_FindObjectsOfTypeAll(CharacterStatePuppett, NULL);

	std::vector<app::CharacterStatePuppet*> puppets;

	int length = app::Array_get_Length((app::Array*)CharacterStatePuppettarr, NULL);
	for (int i = 0; i < length; i++)
	{
		puppets.push_back((app::CharacterStatePuppet * )CharacterStatePuppettarr->vector[i]);
	}

	if (spiritSpearPuppet != nullptr)
		app::GhostRecorder_RegisterPuppet((app::GenericPuppet*)spiritSpearPuppet, NULL);

	if (SeinBowPuppet != nullptr)
		app::GhostRecorder_RegisterPuppet((app::GenericPuppet*)SeinBowPuppet, NULL);

	if (SeinFeatherFlapPuppet != nullptr)
		app::GhostRecorder_RegisterPuppet((app::GenericPuppet*)SeinFeatherFlapPuppet, NULL);*/

	/*if (SeinSpiritSlash != nullptr)
	app::GhostRecorder_RegisterPuppet((app::GenericPuppet*)SeinSpiritSlash->fields._.m_characterStatePuppet, NULL);

	if (SeinBlazeSpell != nullptr)
	app::GhostRecorder_RegisterPuppet((app::GenericPuppet*)SeinBlazeSpell->fields._.m_characterStatePuppet, NULL);

	if (SeinChakramSpell != nullptr)
	app::GhostRecorder_RegisterPuppet((app::GenericPuppet*)SeinChakramSpell->fields._.m_characterStatePuppet, NULL);

	if (SeinCrouch != nullptr)
	app::GhostRecorder_RegisterPuppet((app::GenericPuppet*)SeinCrouch->fields._.m_characterStatePuppet, NULL);

	if (SeinGlowSpell != nullptr)
	app::GhostRecorder_RegisterPuppet((app::GenericPuppet*)SeinGlowSpell->fields._.m_characterStatePuppet, NULL);

	if (SeinGrenadeAttack != nullptr)
	app::GhostRecorder_RegisterPuppet((app::GenericPuppet*)SeinGrenadeAttack->fields._.m_characterStatePuppet, NULL);

	if (SeinMeditateSpell != nullptr)
	app::GhostRecorder_RegisterPuppet((app::GenericPuppet*)SeinMeditateSpell->fields._.m_characterStatePuppet, NULL);

	if (SeinTurretSpell != nullptr)
	app::GhostRecorder_RegisterPuppet((app::GenericPuppet*)SeinTurretSpell->fields._.m_characterStatePuppet, NULL);*/

	GhostRecorder = app::GhostManager_GetOrCreateRecorder(NULL);

	if (GhostRecorder != nullptr)
	{
		if (GhostRecorder->fields.m_plugins->fields._size == 0)
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

			app::GhostRecorder_RegisterPlugin(GhostRecorder, (app::IGhostRecorderPlugin*)ghostAP, NULL);
			app::GhostRecorder_RegisterPlugin(GhostRecorder, (app::IGhostRecorderPlugin*)ghostCP, NULL);
			app::GhostRecorder_RegisterPlugin(GhostRecorder, (app::IGhostRecorderPlugin*)ghostSMP, NULL);
			app::GhostRecorder_RegisterPlugin(GhostRecorder, (app::IGhostRecorderPlugin*)ghostGEP, NULL);
			app::GhostRecorder_RegisterPlugin(GhostRecorder, (app::IGhostRecorderPlugin*)ghostMDP, NULL);

			ghostAP->fields._.m_recorder = GhostRecorder;
			ghostCP->fields._.m_recorder = GhostRecorder;
			ghostSMP->fields._.m_recorder = GhostRecorder;
			ghostGEP->fields._.m_recorder = GhostRecorder;
			ghostMDP->fields._.m_recorder = GhostRecorder;
		}

		if (GhostRecorder->fields.m_filePath == nullptr)
		{
			app::String* MRecorderPath = string_new((ManagerPath + "RaceSettings\\" + "Default").c_str());
			app::GhostRecorder_InitializeRecorder(GhostRecorder, MRecorderPath, NULL);

			auto Class1 = GetClass<>("", "GhostRecorderData");
			app::GhostRecorderData* ghostRecorderData = (app::GhostRecorderData*)il2cpp_object_new((Il2CppClass*)Class1);
			app::GhostRecorderData__ctor(ghostRecorderData, NULL);

			app::BinaryWriter* seinWriter = (app::BinaryWriter*)GhostRecorder->fields.m_binaryWriter;
			//app::Stream* seinMemoryStream = app::BinaryWriter_get_BaseStream(, NULL);

			if (seinWriter->fields.OutStream->fields._._identity != nullptr)
			{
				auto binaryReaderClass = GetClass<>("System.IO", "BinaryReader");
				app::BinaryReader* seinBinaryReader = (app::BinaryReader*)il2cpp_object_new((Il2CppClass*)binaryReaderClass);
				app::BinaryReader__ctor_2(seinBinaryReader, seinWriter->fields.OutStream, seinWriter->fields._encoding, true, NULL);
				app::GhostRecorderData_LoadFromBinaryReader(ghostRecorderData, seinBinaryReader, NULL);
				ghostRecorderData->fields.m_timesliceLoadBinaryReader = seinBinaryReader;
			}

			GhostRecorder->fields.GhostRecorderData = ghostRecorderData;
		}
	}
}

bool TemRecorder::StartRecorder()
{
	if (GhostRecorder != nullptr)
	{
		app::GhostRecorder_StartRecorder(GhostRecorder, NULL);
		return true;
	}
	return false;
}

bool TemRecorder::StopRecorder()
{
	if (GhostRecorder != nullptr) {
		app::GhostRecorder_StopRecorder(GhostRecorder, NULL);
		return true;
	}
	return false;
}

bool TemRecorder::WriteRecorder(std::string filePath, LeaderboardEntryType type)
{
	if (GhostRecorder != nullptr) {
		/*if (std::filesystem::exists(filePath) && std::filesystem::is_regular_file(filePath) == true)
		{
			if (std::filesystem::exists(racePath + "ghosts") == false)
				std::filesystem::create_directory(racePath + "ghosts");

			std::filesystem::path currentPath = filePath;
			std::filesystem::path newPath = racePath + "ghosts\\" + raceName + std::to_string(AttemptManager.Attempts.size()) + ".ghost";
			std::filesystem::copy_file(currentPath, newPath);
		}*/

		app::GhostRecorder_FinalizeFrame(GhostRecorder, NULL);

#ifdef _DEBUG
		//std::string ghostframes = GetLastGhostFrame();
		//TemSocket::SendSocketMessage("WRITEGHOSTSYNC" + TemSocket::MD + raceName + TemSocket::MD + std::to_string(ghostC->fields.CurrentFrameIndex) + TemSocket::MD + ghostframes);
		//sutil::Append(ManagerPath + "\\RaceSettings\\test.ghostsync", ghostframes);
		//GhostHandler::WaitingOnLastFrame = true;
#endif
		//app::String* MRecorderPath = string_new((ManagerPath + "RaceSettings\\" + "Default").c_str());
		app::GhostRecorder_WriteToFile(GhostRecorder, GhostRecorder->fields.m_filePath, false, NULL);

		app::String* raceFile = app::GhostRecorder_get_FilePath(GhostRecorder, NULL);
		std::string raceFileS = sutil::convert_csstring(raceFile);
		std::string base64encodedGhost = sutil::ConvertGhostRecordingToBase64(raceFileS, filePath);
		sutil::Write(filePath, base64encodedGhost);
		std::remove(raceFileS.c_str());

#ifdef _DEBUG
		if (type != LeaderboardEntryType::FinishedRace && MDV::User.IsValid() == true)
		{
			std::string serverGhostMessage = raceName + TemSocket::MD + std::to_string(MDV::User.GetID()) + TemSocket::MD + "player" + TemSocket::MD + std::to_string(RaceTime.GhostRaceTimer->fields._ElapsedTime_k__BackingField) + TemSocket::MD + base64encodedGhost;
			TemSocket::SendSocketMessage("WRITEGHOST" + TemSocket::MD + serverGhostMessage);
		}
#endif
		return true;
	}
	return false;
}

void TemRecorder::FinalizeGhostFrame()
{
	if (GhostRecorder != nullptr && GhostRecorder->fields.Enabled == true)
		app::GhostRecorder_FinalizeFrame(GhostRecorder, NULL);
}

void TemRecorder::ResetRecorder()
{
	app::String* raceFile = app::GhostRecorder_get_FilePath(GhostRecorder, NULL);
	std::string raceFileS = sutil::convert_csstring(raceFile);
	app::BinaryWriter* seinWriter = (app::BinaryWriter*)GhostRecorder->fields.m_binaryWriter;
	app::MemoryStream* seinStream = (app::MemoryStream*)seinWriter->fields.OutStream;
	StopRecorder();
	uint8_t arr1 = seinStream->fields._buffer->vector[0];
	uint8_t arr2 = seinStream->fields._buffer->vector[1];
	uint8_t arr3 = seinStream->fields._buffer->vector[2];
	uint8_t arr4 = seinStream->fields._buffer->vector[3];
	uint8_t arr5 = seinStream->fields._buffer->vector[4];
	uint8_t arr6 = seinStream->fields._buffer->vector[5];
	uint8_t arr7 = seinStream->fields._buffer->vector[6];
	uint8_t arr8 = seinStream->fields._buffer->vector[7];
	uint8_t arr9 = seinStream->fields._buffer->vector[8];
	uint8_t arr10 = seinStream->fields._buffer->vector[9];
	uint8_t arr11 = seinStream->fields._buffer->vector[10];
	app::Array_Clear((app::Array*)seinStream->fields._buffer, 0, (int32_t)seinStream->fields._buffer->max_length, NULL);
	app::MemoryStream_SetLength(seinStream, 11, NULL);
	seinStream->fields._buffer->vector[0] = arr1;
	seinStream->fields._buffer->vector[1] = arr2;
	seinStream->fields._buffer->vector[2] = arr3;
	seinStream->fields._buffer->vector[3] = arr4;
	seinStream->fields._buffer->vector[4] = arr5;
	seinStream->fields._buffer->vector[5] = arr6;
	seinStream->fields._buffer->vector[6] = arr7;
	seinStream->fields._buffer->vector[7] = arr8;
	seinStream->fields._buffer->vector[8] = arr9;
	seinStream->fields._buffer->vector[9] = arr10;
	seinStream->fields._buffer->vector[10] = arr11;
	/*app::BinaryWriter* seinWriter = (app::BinaryWriter*)ghostC->fields.m_binaryWriter;
	app::BinaryWriter_Close(seinWriter, NULL);
	app::Stream_Close(seinWriter->fields.OutStream, NULL);
	app::GhostRecorder_DestroyRecorder(ghostC, NULL);*/
	std::remove(raceFileS.c_str());

	//CreateRecorder();

	if (GhostRecorder->fields.GhostRecorderData == nullptr)
	{
		auto Class1 = GetClass<>("", "GhostRecorderData");
		app::GhostRecorderData* ghostRecorderData = (app::GhostRecorderData*)il2cpp_object_new((Il2CppClass*)Class1);
		app::GhostRecorderData__ctor(ghostRecorderData, NULL);
		GhostRecorder->fields.GhostRecorderData = ghostRecorderData;
	}

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

	app::GhostRecorder_RegisterPlugin(GhostRecorder, (app::IGhostRecorderPlugin*)ghostAP, NULL);
	app::GhostRecorder_RegisterPlugin(GhostRecorder, (app::IGhostRecorderPlugin*)ghostCP, NULL);
	app::GhostRecorder_RegisterPlugin(GhostRecorder, (app::IGhostRecorderPlugin*)ghostSMP, NULL);
	app::GhostRecorder_RegisterPlugin(GhostRecorder, (app::IGhostRecorderPlugin*)ghostGEP, NULL);
	app::GhostRecorder_RegisterPlugin(GhostRecorder, (app::IGhostRecorderPlugin*)ghostMDP, NULL);
}

void TemRecorder::SetRecorderPath(std::string path)
{
	if (GhostRecorder == nullptr)
	{
		CreateRecorder();
	}

	app::String* newPath = string_new(path.c_str());
	GhostRecorder->fields.m_filePath = newPath;
}