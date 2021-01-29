#pragma once

#include <unordered_map>

enum class LogType {
	Warning = 0,
	Error = 1,
	Normal = 2
};

class TemLogger
{
public:
	static TemLogger Logger;
	std::vector<std::string> Lines;
	std::vector<std::string> Temp;
	bool IsWriting = false;

	TemLogger()
	{
		Lines.push_back("\n\r");
	}

	void Cleanup();

	static void Add(std::string log, LogType type = LogType::Normal);

private:
	static std::unordered_map<int, std::string> LogTypeMap;

	static std::string GetClockString();
	void WriteLog();
};