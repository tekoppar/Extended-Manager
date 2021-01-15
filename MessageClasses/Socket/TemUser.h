#pragma once

class TemUser {
private:
	std::string Username = "";
	bool HasUUID = false;
	app::CSteamID SteamID;

public:
	TemUser();
	void Initialize();
	bool IsValid();
	unsigned long long GetID();
};