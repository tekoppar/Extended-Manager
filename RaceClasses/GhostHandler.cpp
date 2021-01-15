#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include "StringUtils.h"
#include "ManagerDef.h"
#include "MessageHelper.h"
#include "GraphDrawer.h"
#include "Global.h"

#include "GhostHandler.h"

GhostHandler GhostHandler::Instance;
GhostHandlerState GhostHandler::State = GhostHandlerState::IsNull;
std::vector<std::future<bool>> GhostHandler::WaitingOnGhosts = std::vector<std::future<bool>>();
app::GhostManager* GhostHandler::BaseGhostManager = nullptr;
std::unordered_map<int, app::GhostPlayer*> GhostHandler::ActiveGhostPlayers = std::unordered_map<int, app::GhostPlayer*>();
std::unordered_map<int, app::GameObject*> GhostHandler::ActiveGhostIcons = std::unordered_map<int, app::GameObject*>();
app::GhostPlayer* GhostHandler::StreamGhost = nullptr;
std::string GhostHandler::AllStreamGhostFrames = "";
float GhostHandler::LastPosition = 0;
int GhostHandler::FilePosition = 0;
app::GhostCharacterAbilitiesPlugin* GhostHandler::ghostAP = nullptr;
app::GhostCharacterPlugin* GhostHandler::ghostCP = nullptr;
app::GhostStateMachinePlugin* GhostHandler::ghostSMP = nullptr;
app::GhostGenericEventsPlugin* GhostHandler::ghostGEP = nullptr;
app::GhostRecordingMetaDataPlugin* GhostHandler::ghostMDP = nullptr;
app::GhostFrame* GhostHandler::LastValidGhostFrame = nullptr;
int GhostHandler::LastValidGhostFrameIndex = 0;
std::size_t GhostHandler::LastReadGhostFrame = 0;
bool GhostHandler::ServerRespond = true;
bool GhostHandler::WaitingOnLastFrame = false;
std::vector<std::string> GhostHandler::ReadMessages = std::vector<std::string>();
int GhostHandler::GhostIndex = 0;

const std::chrono::milliseconds span(1);

void GhostHandler::Initialize()
{
	GhostHandler::Instance = GhostHandler();

	app::Type* ghostManagerType = GetType("", "GhostManager");
	app::Object_1__Array* ghostManagerArr = app::Object_1_FindObjectsOfType(ghostManagerType, NULL);

	GhostHandler::BaseGhostManager = (app::GhostManager*)ghostManagerArr->vector[0];
	GhostHandler::State = GhostHandlerState::IsNormal;
}

void GhostHandler::Cleanup()
{
	GhostHandler::BaseGhostManager = nullptr;

	GhostHandler::CleanupGhosts();
}

void GhostHandler::Update()
{
	GhostHandler::UpdateStatic();

#ifdef TEMSOCKET
	if (StreamGhost != nullptr && StreamGhost->fields.GhostRecorderData != nullptr)
		LastPosition = std::min<float>(StreamGhost->fields.CurrentTime, StreamGhost->fields.GhostRecorderData->fields.Duration);

	if (StreamGhost != nullptr && StreamGhost->fields.GhostRecorderData != nullptr &&
		StreamGhost->fields.GhostRecorderData->fields.Frames->fields._size > LastValidGhostFrameIndex + 1)
		LastValidGhostFrameIndex++;

	if (StreamGhost != nullptr && StreamGhost->fields.m_plugins != nullptr && StreamGhost->fields.m_plugins->fields._size > 0 &&
		StreamGhost->fields.m_plugins->fields._items->vector[3] != nullptr &&
		StreamGhost->fields.GhostRecorderData != nullptr && StreamGhost->fields.GhostRecorderData->fields.Frames->fields._size > 1)
	{
		auto frames = StreamGhost->fields.GhostRecorderData->fields.Frames;
		StreamGhost->fields.m_plugins->fields._items->vector[3]->fields.CurrentFrameIndex = LastValidGhostFrameIndex - 1;
		StreamGhost->fields.m_plugins->fields._items->vector[3]->fields.CurrentFrame = frames->fields._items->vector[LastValidGhostFrameIndex - 1];
		StreamGhost->fields.m_plugins->fields._items->vector[3]->fields.NextFrameIndex = LastValidGhostFrameIndex;
		StreamGhost->fields.m_plugins->fields._items->vector[3]->fields.NextFrame = frames->fields._items->vector[LastValidGhostFrameIndex];
		StreamGhost->fields.m_plugins->fields._items->vector[0]->fields.CurrentFrameIndex = LastValidGhostFrameIndex - 1;
		StreamGhost->fields.m_plugins->fields._items->vector[0]->fields.CurrentFrame = frames->fields._items->vector[LastValidGhostFrameIndex - 1];
		StreamGhost->fields.m_plugins->fields._items->vector[0]->fields.NextFrameIndex = LastValidGhostFrameIndex;
		StreamGhost->fields.m_plugins->fields._items->vector[0]->fields.NextFrame = frames->fields._items->vector[LastValidGhostFrameIndex];

		StreamGhost->fields.CurrentTime = frames->fields._items->vector[LastValidGhostFrameIndex - 1]->fields.Time;
		StreamGhost->fields.m_isStarted = true;
		StreamGhost->fields._IsFinished_k__BackingField = false;
		StreamGhost->fields._IsSuspended_k__BackingField = false;
	}

	//RegisterGhostPlugins(StreamGhost);
	UpdateStreamGhost();
#endif
}

void GhostHandler::UpdateStatic()
{
	if (ActiveGhostPlayers.size() > 0)
	{
		GhostHandler::CheckIfGhostsFinished();
	}

	for (int i = 0; i < GhostHandler::WaitingOnGhosts.size(); i++)
	{
		if (GhostHandler::WaitingOnGhosts[i].wait_for(span) != std::future_status::ready)
		{
			continue;
		}
		else
		{
			GhostHandler::WaitingOnGhosts.erase(GhostHandler::WaitingOnGhosts.begin());

			if (GhostHandler::WaitingOnGhosts.size() == 0)
				GhostHandler::State = GhostHandlerState::IsNormal;
		}
	}
}

void GhostHandler::CreateGhostPublic(std::string path, std::string ghostName, tem::Vector3 startPosition)
{
	if (GhostHandler::State == GhostHandlerState::HasFinishedCleaningUpGhosts || GhostHandler::State == GhostHandlerState::IsNormal)
	{
		GhostHandler::State = GhostHandlerState::IsCreatingGhostPublic;

		app::GameObject* ghost = (app::GameObject*)app::Object_1_Instantiate_2((app::Object_1*)GhostHandler::BaseGhostManager->fields.GhostPrefab, NULL);

		app::Color purple = app::Color();
		purple.a = 0.8f;
		purple.b = 0.8f;
		purple.g = 0.2f;
		purple.r = 0.5f;
		app::GameObject* newGhostIcon = areaMapManager.CreateNewIconPlayerIcon(startPosition, purple);
		GhostHandler::ActiveGhostIcons[GhostHandler::GhostIndex] = newGhostIcon;

		GhostHandler::WaitingOnGhosts.push_back(std::async(GhostHandler::CreateGhost, path, ghost, ghostName, startPosition, GhostHandler::GhostIndex));
		GhostHandler::State = GhostHandlerState::IsNormal;
		GhostHandler::GhostIndex++;
	}
}

bool GhostHandler::CreateGhost(std::string path, app::GameObject* ghost, std::string ghostName, tem::Vector3 startPosition, int index)
{
	if (GhostHandler::BaseGhostManager != nullptr)
	{
		std::string contents = sutil::readFile(path);
		const char* gP = contents.data();
		app::String* gPath = string_new(gP);
		const char* gPN = ghostName.data();
		app::String* gName = string_new(gPN);

		app::GhostPlayer* ghostPlayer = (app::GhostPlayer*)GetComponentByType(ghost, "", "GhostPlayer");
		app::GhostPlayer_SetDisplayName(ghostPlayer, gName, NULL);
		app::GhostPlayer_set_GhostReplay(ghostPlayer, gPath, NULL);
		//app::GhostRecorderData_LoadFromFile(ghostPlayer->fields.GhostRecorderData, gPath, NULL);

		if (ghostPlayer != nullptr)
		{
			GhostHandler::ActiveGhostPlayers[index] = ghostPlayer;
			app::GhostPlayer_ExtractMetaData(ghostPlayer, NULL);

			app::GameObject* nameObject = app::Component_1_get_gameObject((app::Component_1*)ghostPlayer->fields.Name, NULL);
			TransformSetRotation(nameObject, tem::Vector3(0, -90, 0));

			//app::GhostRecorderData_LoadFromReplay(ghostC->fields.GhostRecorderData, gPath, NULL);
			/*std::vector< app::IGhostFrameData*> frameData;
			app::GhostFrame* firstFrame = app::GhostRecorderData_GetFrame(ghostC->fields.GhostRecorderData, 0, NULL);

			int lastGhostFrame = ghostC->fields.GhostRecorderData->fields.Frames->fields._size - 1;
			app::GhostFrame* lastFrame = app::GhostRecorderData_GetFrame(ghostC->fields.GhostRecorderData, lastGhostFrame, NULL);
			while (lastFrame->fields.FrameData->fields._size == 0)
			{
				lastFrame = app::GhostRecorderData_GetFrame(ghostC->fields.GhostRecorderData, lastGhostFrame, NULL);
				lastGhostFrame--;
			}*/

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

				/*if (ghostC->fields.GhostRecorderData != nullptr)
					RaceDuration = ghostC->fields.GhostRecorderData->fields.Duration;*/
			return true;
		}
	}
	return false;
}

app::GameObject* GhostHandler::CreateEmptyGhost(std::string ghostName, tem::Vector3 startPosition)
{
	app::GameObject* ghost = (app::GameObject*)app::Object_1_Instantiate_2((app::Object_1*)GhostHandler::BaseGhostManager->fields.GhostPrefab, NULL);

	app::GhostPlayer* ghostPlayer = (app::GhostPlayer*)GetComponentByType(ghost, "", "GhostPlayer");
	app::String* ghostN = string_new(ghostName.data());
	app::GhostPlayer_SetDisplayName(ghostPlayer, ghostN, NULL);
	GhostHandler::ActiveGhostPlayers[GhostHandler::GhostIndex] = ghostPlayer;
	GhostHandler::GhostIndex++;

	app::GameObject* nameObject = app::Component_1_get_gameObject((app::Component_1*)ghostPlayer->fields.Name, NULL);
	TransformSetRotation(nameObject, tem::Vector3(0, -90, 0));

	return ghost;
}

bool GhostHandler::RunGhost()
{
	if (GhostHandler::State == GhostHandlerState::HasFinishedCleaningUpGhosts || GhostHandler::State == GhostHandlerState::IsNormal)
	{
		GhostHandler::State = GhostHandlerState::IsStartingGhosts;

		if (GhostHandler::WaitingOnGhosts.size() > 0)
		{
			GhostHandler::State = GhostHandlerState::IsNormal;
			return false;
		}

		srand((unsigned int)time(NULL));

		for (auto& ghostPlayer : ActiveGhostPlayers)
		{
			app::GhostPlayer* ghost = ghostPlayer.second;
			app::GhostPlayer_Run(ghost, NULL);

			app::Color newColor = GraphColors::RandomColor(1.0f);
			app::Color newColorBright = newColor;
			newColorBright.r *= 2;
			newColorBright.g *= 2;
			newColorBright.b *= 2;
			newColor.a = 0.5f;
			app::UberShaderColor_set_Color(ghost->fields.VisualSettings->fields.TrailColor, newColor, NULL);
			app::UberShaderColor_set_Color(ghost->fields.VisualSettings->fields.FirstVignetteColor, newColor, NULL);
			app::UberShaderColor_set_Color(ghost->fields.VisualSettings->fields.GhostIndicatorColor, newColor, NULL);
			app::UberShaderColor_set_Color(ghost->fields.VisualSettings->fields.MultiplyLayerColor, newColorBright, NULL);
			app::UberShaderColor_set_Color(ghost->fields.VisualSettings->fields.ParticleColor, newColor, NULL);
			app::UberShaderColor_set_Color(ghost->fields.VisualSettings->fields.SecondVignetteColor, newColor, NULL);
			app::UberShaderColor_set_Color(ghost->fields.VisualSettings->fields.EmissivityColor, newColor, NULL);

			app::String* TextureName1 = string_new("_Color");

			app::Material* mat = app::Renderer_GetMaterial(ghost->fields.RigVisuals->fields.Body_MDL, NULL);
			newColor.a = 0.5f;
			app::Material_SetColor(mat, TextureName1, newColor, NULL);
			newColor.a = 1.0f;
			mat = app::Renderer_GetMaterial(ghost->fields.RigVisuals->fields.FirstVignette, NULL);
			app::Material_SetColor(mat, TextureName1, newColor, NULL);
			mat = app::Renderer_GetMaterial(ghost->fields.RigVisuals->fields.FourthVignette, NULL);
			app::Material_SetColor(mat, TextureName1, newColor, NULL);
			//mat = app::Renderer_GetMaterial(ghostPlayer->fields.RigVisuals->fields.Trail, NULL);
			//newColor.a = 0.25f;
			//app::Material_SetColor(mat, TextureName1, newColor, NULL);

			newColor.a = 0.5f;
			for (int i = 0; i < ghost->fields.ParticleSystems->max_length; i++)
			{
				if (ghost->fields.ParticleSystems->vector[i] != nullptr)
				{
					app::ParticleSystem* particle = (app::ParticleSystem*)ghost->fields.ParticleSystems->vector[i];
					app::ParticleSystem_set_startColor(particle, newColor, NULL);
				}
			}
		}
		GhostHandler::State = GhostHandlerState::IsNormal;

		return true;
	}

	return false;
}

void GhostHandler::CheckIfGhostsFinished()
{
	if (GhostHandler::State == GhostHandlerState::HasFinishedCleaningUpGhosts || GhostHandler::State == GhostHandlerState::IsNormal)
	{
		GhostHandler::State = GhostHandlerState::IsCheckingGhostsFinished;

		for (auto& ghostPlayer : ActiveGhostPlayers)
		{
			app::GhostPlayer* ghost = ghostPlayer.second;

			if (ghost == nullptr)
			{
				if (ActiveGhostIcons.find(ghostPlayer.first) != ActiveGhostIcons.end())
				{
					auto ghostIcon = ActiveGhostIcons[ghostPlayer.first];
					app::Object_1_Destroy_1((app::Object_1*)ghostIcon, NULL);
					ActiveGhostIcons.erase(ghostPlayer.first);
				}
				continue;
			}

			if (ActiveGhostIcons.find(ghostPlayer.first) != ActiveGhostIcons.end())
				areaMapManager.UpdateIconPosition(ActiveGhostIcons[ghostPlayer.first], app::GhostPlayer_get_Position(ghost, NULL));

			if (ghost != nullptr && ghost->fields._IsFinished_k__BackingField)
			{
				if (ActiveGhostIcons.find(ghostPlayer.first) != ActiveGhostIcons.end())
				{
					auto ghostIcon = ActiveGhostIcons[ghostPlayer.first];
					app::Object_1_Destroy_1((app::Object_1*)ghostIcon, NULL);
					ActiveGhostIcons.erase(ghostPlayer.first);
				}

				app::GhostPlayer_Stop(ghost, NULL);
			}
		}
		GhostHandler::State = GhostHandlerState::IsNormal;
	}
}

void GhostHandler::CleanupGhosts()
{
	if (GhostHandler::State == GhostHandlerState::HasFinishedCleaningUpGhosts || GhostHandler::State == GhostHandlerState::IsNormal)
	{
		GhostHandler::State = GhostHandlerState::IsCleaningUpGhosts;
		for (auto& ghostPlayer : ActiveGhostPlayers)
		{
			if (ActiveGhostIcons.find(ghostPlayer.first) != ActiveGhostIcons.end())
			{
				app::Object_1_Destroy_1((app::Object_1*)ActiveGhostIcons[ghostPlayer.first], NULL);
				ActiveGhostIcons[ghostPlayer.first] = nullptr;
				//ActiveGhostIcons.erase(ghostPlayer.first);
			}

			if (ghostPlayer.second != nullptr)
			{
				app::GhostPlayer_Stop(ghostPlayer.second, NULL);
				app::GameObject* parentObject = app::Component_1_get_gameObject((app::Component_1*)ghostPlayer.second, NULL);
				auto components = GetComponentsByTypeInChildren(parentObject, "UnityEngine", "Transform");

				for (auto& comp : components)
				{
					app::GameObject* parentObject = app::Component_1_get_gameObject(comp, NULL);
					if (parentObject != nullptr)
						app::Object_1_Destroy((app::Object_1*)parentObject, 1.0f, NULL);
				}
				ghostPlayer.second = nullptr;
				//ActiveGhostPlayers.erase(ghostPlayer.first);
			}
		}

		ActiveGhostPlayers.clear();
		ActiveGhostIcons.clear();
		GhostHandler::State = GhostHandlerState::HasFinishedCleaningUpGhosts;
	}
}

void GhostHandler::CreateStreamGhost(tem::Vector3 position)
{
	app::GameObject* byteGhost = GhostHandler::CreateEmptyGhost("I'm bytes", position);
	StreamGhost = (app::GhostPlayer*)GetComponentByType(byteGhost, "", "GhostPlayer");

	auto Class1 = GetClass<>("", "GhostRecorderData");
	app::GhostRecorderData* ghostRecorderData = (app::GhostRecorderData*)il2cpp_object_new((Il2CppClass*)Class1);
	app::GhostRecorderData__ctor(ghostRecorderData, NULL);
	StreamGhost->fields.GhostRecorderData = ghostRecorderData;

	app::GhostPlayer_Run(StreamGhost, NULL);
	StreamGhost->fields.m_isStarted = true;
	StreamGhost->fields._IsFinished_k__BackingField = false;
	StreamGhost->fields.OnFinished = NULL;
}

void GhostHandler::InsertGhostFrames(std::string frames)
{
	AllStreamGhostFrames.insert(AllStreamGhostFrames.end(), frames.begin(), frames.end());
}

void GhostHandler::RegisterGhostPlugins(app::GhostPlayer* ghost)
{
	if (ghost != nullptr && ghost->fields.m_plugins->fields._size < 4 && ghost->fields.GhostRecorderData != nullptr)
	{
		bool ghostCharacterPluginB = false;
		bool ghostStateMachinePluginB = false;
		bool ghostAnimationPluginB = false;
		bool ghostTransformPluginB = false;
		bool ghostCharacterAbilitiesPluginB = false;
		bool ghostGenericEventsPluginB = false;

		for (int i = 0; i < ghost->fields.m_plugins->fields._size; i++)
		{
			std::string ghostFrameType = ghost->fields.m_plugins->fields._items->vector[i]->klass->_0.name;

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


		auto ghostFrames = ghost->fields.GhostRecorderData->fields.Frames;
		if (ghostCharacterPluginB == false)
		{
			auto Class2 = GetClass<>("", "GhostCharacterPlugin");
			ghostCP = (app::GhostCharacterPlugin*)il2cpp_object_new((Il2CppClass*)Class2);
			app::GhostPlayer_RegisterPlugin(ghost, (app::IGhostRecorderPlugin*)ghostCP, NULL);
			ghostCP->fields._.m_player = ghost;

			if (LastValidGhostFrameIndex > 1)
			{
				ghostCP->fields._.CurrentFrameIndex = LastValidGhostFrameIndex - 1;
				ghostCP->fields._.CurrentFrame = ghostFrames->fields._items->vector[LastValidGhostFrameIndex - 1];
				ghostCP->fields._.NextFrameIndex = LastValidGhostFrameIndex;
				ghostCP->fields._.NextFrame = ghostFrames->fields._items->vector[LastValidGhostFrameIndex];
			}
		}

		if (ghostGenericEventsPluginB == false)
		{
			auto Class4 = GetClass<>("", "GhostGenericEventsPlugin");
			ghostGEP = (app::GhostGenericEventsPlugin*)il2cpp_object_new((Il2CppClass*)Class4);
			app::GhostPlayer_RegisterPlugin(ghost, (app::IGhostRecorderPlugin*)ghostGEP, NULL);
			ghostGEP->fields._.m_player = ghost;

			if (LastValidGhostFrameIndex > 1)
			{
				ghostGEP->fields._.CurrentFrameIndex = LastValidGhostFrameIndex - 1;
				ghostGEP->fields._.CurrentFrame = ghostFrames->fields._items->vector[LastValidGhostFrameIndex - 1];
				ghostGEP->fields._.NextFrameIndex = LastValidGhostFrameIndex;
				ghostGEP->fields._.NextFrame = ghostFrames->fields._items->vector[LastValidGhostFrameIndex];
			}
		}

		if (ghostCharacterAbilitiesPluginB == false)
		{
			auto Class1 = GetClass<>("", "GhostCharacterAbilitiesPlugin");
			ghostAP = (app::GhostCharacterAbilitiesPlugin*)il2cpp_object_new((Il2CppClass*)Class1);
			app::GhostPlayer_RegisterPlugin(ghost, (app::IGhostRecorderPlugin*)ghostAP, NULL);
			ghostAP->fields._.m_player = ghost;

			if (LastValidGhostFrameIndex > 1)
			{
				ghostAP->fields._.CurrentFrameIndex = LastValidGhostFrameIndex - 1;
				ghostAP->fields._.CurrentFrame = ghostFrames->fields._items->vector[LastValidGhostFrameIndex - 1];
				ghostAP->fields._.NextFrameIndex = LastValidGhostFrameIndex;
				ghostAP->fields._.NextFrame = ghostFrames->fields._items->vector[LastValidGhostFrameIndex];
			}
		}

		if (ghostStateMachinePluginB == false)
		{
			auto Class3 = GetClass<>("", "GhostStateMachinePlugin");
			ghostSMP = (app::GhostStateMachinePlugin*)il2cpp_object_new((Il2CppClass*)Class3);
			app::GhostPlayer_RegisterPlugin(ghost, (app::IGhostRecorderPlugin*)ghostSMP, NULL);
			ghostSMP->fields._.m_player = ghost;

			if (LastValidGhostFrameIndex > 1)
			{
				ghostSMP->fields._.CurrentFrameIndex = LastValidGhostFrameIndex - 1;
				ghostSMP->fields._.CurrentFrame = ghostFrames->fields._items->vector[LastValidGhostFrameIndex - 1];
				ghostSMP->fields._.NextFrameIndex = LastValidGhostFrameIndex;
				ghostSMP->fields._.NextFrame = ghostFrames->fields._items->vector[LastValidGhostFrameIndex];
			}
		}
	}
}

void GhostHandler::UpdateStreamGhost()
{
	if (StreamGhost != nullptr && StreamGhost->fields.GhostRecorderData != nullptr && AllStreamGhostFrames.size() > 0)
	{
		StreamGhost->fields._IsSuspended_k__BackingField = false;
		app::GameObject* gamyobj = app::Component_1_get_gameObject((app::Component_1*)StreamGhost, NULL);
		app::GameObject_SetActiveRecursively(gamyobj, true, NULL);

		StreamGhost->fields.OnFinished = NULL;
		auto Class1 = GetClass<>("", "GhostRecorderData");
		app::GhostRecorderData* ghostRecorderData = (app::GhostRecorderData*)il2cpp_object_new((Il2CppClass*)Class1);
		app::GhostRecorderData__ctor(ghostRecorderData, NULL);

		//app::BinaryWriter* seinWriter = (app::BinaryWriter*)ghostC->fields.m_binaryWriter;
		app::Encoding* encoding = (app::Encoding*)il2cpp_object_new((Il2CppClass*)(*app::Encoding__TypeInfo));
		encoding = (*app::Encoding__TypeInfo)->static_fields->utf8Encoding;

		auto MemoryStreamClass = GetClass<>("System.IO", "MemoryStream");
		app::MemoryStream* seinMemoryStream = (app::MemoryStream*)il2cpp_object_new((Il2CppClass*)MemoryStreamClass);
		app::MemoryStream__ctor_1(seinMemoryStream, static_cast<int32_t>(AllStreamGhostFrames.capacity()), NULL);
		app::MemoryStream_SetLength(seinMemoryStream, AllStreamGhostFrames.size(), NULL);

		std::string tempGhostFrames = "";

		for (auto& frame : ReadMessages)
		{
			tempGhostFrames += frame;
		}

		for (int i = 0; i < AllStreamGhostFrames.size(); i++)
		{
			if (seinMemoryStream->fields._capacity > i)
			{
				char value = AllStreamGhostFrames[i];
				seinMemoryStream->fields._buffer->vector[i] = value;
			}
		}

		auto binaryReaderClass = GetClass<>("System.IO", "BinaryReader");
		app::BinaryReader* seinBinaryReader = (app::BinaryReader*)il2cpp_object_new((Il2CppClass*)binaryReaderClass);
		app::BinaryReader__ctor_2(seinBinaryReader, (app::Stream*)seinMemoryStream, encoding, true, NULL);
		app::GhostRecorderData_LoadFromBinaryReader(ghostRecorderData, seinBinaryReader, NULL);

		if (StreamGhost->fields.CurrentTime > StreamGhost->fields.GhostRecorderData->fields.Duration)
			StreamGhost->fields.CurrentTime = StreamGhost->fields.GhostRecorderData->fields.Duration;

		int totalGhostFrames = ghostRecorderData->fields.Frames->fields._size;
		int totalOldFrames = StreamGhost->fields.GhostRecorderData->fields.Frames->fields._size;

		int lastGhostFrameIndex = StreamGhost->fields.GhostRecorderData->fields.Frames->fields._size;
		app::GhostFrame* lastGhostFrame;

		if (StreamGhost->fields.GhostRecorderData->fields.Frames->fields._items->max_length != ghostRecorderData->fields.Frames->fields._items->max_length)
		{
			StreamGhost->fields.GhostRecorderData->fields.Frames = ghostRecorderData->fields.Frames;
		}
		else {
			for (int i = lastGhostFrameIndex; i < ghostRecorderData->fields.Frames->fields._size; i++)
			{
				lastGhostFrame = app::GhostRecorderData_GetFrame(ghostRecorderData, i, NULL);
				app::List_1_GhostFrame__Add(StreamGhost->fields.GhostRecorderData->fields.Frames, lastGhostFrame, NULL);
			}
		}
		StreamGhost->fields.GhostRecorderData->fields.Duration = ghostRecorderData->fields.Duration;

		if (StreamGhost->fields.m_isStarted == false && StreamGhost->fields.GhostRecorderData->fields.Frames->fields._size > 0 && totalOldFrames < totalGhostFrames)
		{
			app::GhostPlayer_Run(StreamGhost, NULL);
			StreamGhost->fields.m_isStarted = true;
			StreamGhost->fields._IsFinished_k__BackingField = false;
		}

		/*StreamGhost->fields.GhostRecorderData->fields.Duration = ghostRecorderData->fields.Duration;
		app::GhostCharacterPlugin* plugin = (app::GhostCharacterPlugin*)StreamGhost->fields.m_plugins->fields._items->vector[0];
		app::IGhostRecorderPlugin* plugin1 = (app::IGhostRecorderPlugin*)StreamGhost->fields.m_plugins->fields._items->vector[1];
		app::IGhostRecorderPlugin* plugin2 = (app::IGhostRecorderPlugin*)StreamGhost->fields.m_plugins->fields._items->vector[2];
		app::IGhostRecorderPlugin* statePlugin = (app::IGhostRecorderPlugin*)StreamGhost->fields.m_plugins->fields._items->vector[3];
		if (statePlugin != nullptr && plugin != nullptr)
		{
			if (statePlugin->fields.CurrentFrameIndex < totalOldFrames && statePlugin->fields.NextFrameIndex > 0)
			{
				plugin->fields._.CurrentFrameIndex = statePlugin->fields.CurrentFrameIndex;
				plugin->fields._.NextFrameIndex = statePlugin->fields.NextFrameIndex;
				plugin->fields._.CurrentFrame = statePlugin->fields.CurrentFrame;
				plugin->fields._.NextFrame = statePlugin->fields.NextFrame;
				app::GhostCharacterPlugin_PlayCycle(plugin, StreamGhost->fields.GhostRecorderData->fields.Duration, NULL);
			}
			else if (LastValidGhostFrameIndex > 0 && (statePlugin->fields.NextFrameIndex == -1 || statePlugin->fields.NextFrameIndex >= totalOldFrames))
			{
				//statePlugin->fields.NextFrameIndex = plugin->fields._.NextFrameIndex = plugin->fields._.CurrentFrameIndex = statePlugin->fields.CurrentFrameIndex;
				//plugin->fields._.NextFrame = statePlugin->fields.NextFrame = plugin->fields._.CurrentFrame = statePlugin->fields.CurrentFrame;
				plugin->fields._.CurrentFrameIndex = statePlugin->fields.CurrentFrameIndex = LastValidGhostFrameIndex - 1;
				plugin->fields._.NextFrameIndex = statePlugin->fields.NextFrameIndex = LastValidGhostFrameIndex;
				plugin->fields._.CurrentFrame = statePlugin->fields.CurrentFrame = ghostRecorderData->fields.Frames->fields._items->vector[LastValidGhostFrameIndex - 1];
				plugin->fields._.NextFrame = statePlugin->fields.NextFrame = ghostRecorderData->fields.Frames->fields._items->vector[LastValidGhostFrameIndex];
			}
			else if (LastValidGhostFrameIndex > 0 && (statePlugin->fields.CurrentFrameIndex == -1 || statePlugin->fields.CurrentFrameIndex >= totalOldFrames))
			{
				plugin->fields._.CurrentFrameIndex = statePlugin->fields.CurrentFrameIndex = LastValidGhostFrameIndex - 1;
				plugin->fields._.NextFrameIndex = statePlugin->fields.NextFrameIndex = LastValidGhostFrameIndex;
				plugin->fields._.CurrentFrame = statePlugin->fields.CurrentFrame = ghostRecorderData->fields.Frames->fields._items->vector[LastValidGhostFrameIndex - 1];
				plugin->fields._.NextFrame = statePlugin->fields.NextFrame = ghostRecorderData->fields.Frames->fields._items->vector[LastValidGhostFrameIndex];
			}
		}*/
	}
}