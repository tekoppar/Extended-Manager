#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <unordered_map>
#include <filesystem>
#include <chrono>

#include "StringUtils.h"
#include "ManagerDef.h"
#include "TemLogger.h"

TemLogger TemLogger::Logger = TemLogger();
std::unordered_map<int, std::string> TemLogger::LogTypeMap = {
	{0, "Warning"},
	{1,"Error" },
	{2,"Normal"}
};

std::string TemLogger::GetClockString()
{
	std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
	std::time_t t = std::chrono::system_clock::to_time_t(p);
	std::stringstream ss;
	ss << t;
	return ss.str();
}

void TemLogger::Add(std::string log, LogType type)
{
	if (TemLogger::Logger.IsWriting == false)
		TemLogger::Logger.Lines.push_back(TemLogger::LogTypeMap[static_cast<int>(type)] + "\t" + TemLogger::GetClockString() + "\t" + log);
	else
		TemLogger::Logger.Temp.push_back(TemLogger::LogTypeMap[static_cast<int>(type)] + "\t" + TemLogger::GetClockString() + "\t" + log);

	if (TemLogger::Logger.Lines.size() > 100)
		TemLogger::Logger.WriteLog();
}

void TemLogger::WriteLog()
{
	std::string log = "";
	this->IsWriting = true;
	for (std::string s : this->Lines)
	{
		log += s + "\r\n";
	}

	if (std::filesystem::exists(ManagerPath + "TemLogs.log") == true)
	{
		std::uintmax_t fileSize = std::filesystem::file_size(ManagerPath + "TemLogs.log");

		if (fileSize > 2503192)
			std::filesystem::remove(ManagerPath + "TemLogs.log");
	}

	sutil::Append(ManagerPath + "TemLogs.log", log);
	this->IsWriting = false;
	TemLogger::Logger.Lines = TemLogger::Logger.Temp;
	TemLogger::Logger.Temp.clear();
}