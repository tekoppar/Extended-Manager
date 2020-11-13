#pragma once

#include <future>
#include <chrono>
#include "RaceEnums.h"

class GhostHandler : public Global
{
public:
	static GhostHandler Instance;
	static GhostHandlerState State;

	static std::vector<std::future<bool>> WaitingOnGhosts;
	static app::GhostManager* BaseGhostManager;
	static std::unordered_map<int, app::GhostPlayer*> ActiveGhostPlayers;
	static std::unordered_map<int,  app::GameObject*> ActiveGhostIcons;
	static app::GhostPlayer* StreamGhost;
	static std::string AllStreamGhostFrames;
	static float LastPosition;
	static int FilePosition;
	static app::GhostCharacterAbilitiesPlugin* ghostAP;
	static app::GhostCharacterPlugin* ghostCP;
	static app::GhostStateMachinePlugin* ghostSMP;
	static app::GhostGenericEventsPlugin* ghostGEP;
	static app::GhostRecordingMetaDataPlugin* ghostMDP;
	static app::GhostFrame* LastValidGhostFrame;
	static std::size_t LastReadGhostFrame;
	static int LastValidGhostFrameIndex;
	static bool ServerRespond;
	static bool WaitingOnLastFrame;
	static std::vector<std::string> ReadMessages;
	static int GhostIndex;

	static void Initialize();
	static void Cleanup();
	virtual void Update() override;
	static void UpdateStatic();
	static bool RunGhost();
	static void CreateGhostPublic(std::string path, std::string ghostName = "", tem::Vector3 startPosition = tem::Vector3(0, 0, 0));
	static void CleanupGhosts();
	static app::GameObject* CreateEmptyGhost(std::string ghostName, tem::Vector3 startPosition);
	static void CreateStreamGhost(tem::Vector3 position);
	static void InsertGhostFrames(std::string frames);
	static void RegisterGhostPlugins(app::GhostPlayer* ghost);

private:
	static void CheckIfGhostsFinished();
	static bool CreateGhost(std::string path, app::GameObject* ghost, std::string ghostName = "", tem::Vector3 startPosition = tem::Vector3(0, 0, 0), int index = 0);
	static void UpdateStreamGhost();
};