#pragma once

class UberID {
public:
	int ID;
	int Integer;
	float Float;
	bool Bool;
	char Byte;
};

class UberGroup {
public:
	int UberGroupID;
	std::unordered_map<int, int> UberInts;
	std::unordered_map<int, float> UberFloats;
	std::unordered_map<int, bool> UberBools;
	std::unordered_map<int, std::uint8_t> UberBytes;

	std::string ToString();
	void LoadData(std::string data);
};

class UberStateManager
{
public:
	static std::unordered_map<int, UberGroup> UberGroups;
	static bool RunnerUberStatesSaved;

	static void SaveUberStates(std::string path);
	static void LoadUberStates(std::string path);
	static void ResetUberStates();
	static void AddUberStates(int UberGroupID, int UberID, bool value);
	static void SetUberState(int UberGroupID, int UberID, std::uint8_t value);
	static std::uint8_t GetUberState(int UberGroupID, int UberID);
	static app::UberStateValueGroup* GetUberGroup(int UberGroupID);
	static void SaveIntegers(app::UberStateValueGroup* group, std::unordered_map<int, int>& uberids);
	static void SaveBools(app::UberStateValueGroup* group, std::unordered_map<int, bool>& uberids);
	static void SaveFloats(app::UberStateValueGroup* group, std::unordered_map<int, float>& uberids);
	static void SaveBytes(app::UberStateValueGroup* group, std::unordered_map<int, std::uint8_t>& uberids);
	static void LoadIntegers(app::UberStateValueGroup* group, std::unordered_map<int, int>& uberids);
	static void LoadBools(app::UberStateValueGroup* group, std::unordered_map<int, bool>& uberids);
	static void LoadFloats(app::UberStateValueGroup* group, std::unordered_map<int, float>& uberids);
	static void LoadBytes(app::UberStateValueGroup* group, std::unordered_map<int, std::uint8_t>& uberids);
};

