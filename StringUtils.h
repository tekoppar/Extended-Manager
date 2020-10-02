#pragma once

#include <Windows.h>
#include <string>
#include <iostream>
#include <vector>
#include <xstring>
#include <set>
#include <locale>
#include <codecvt>
#include <fstream>
#include <sstream>
#include <tuple>

#include "Base64.h"

#ifndef STRINGUTILS_GUARD 
#define STRINGUTILS_GUARD

void ReplaceS(std::string& subject, const std::string& search, const std::string& replace)
{
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
}

///D _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS 
std::string getexepath()
{
	char result[MAX_PATH];
	return std::string(result, GetModuleFileNameA(NULL, result, MAX_PATH));
}

std::string readFile(const std::string& fileName)
{
	std::ifstream ifs(fileName.c_str(), std::ios::in | std::ios::binary | std::ios::ate);

	std::ifstream::pos_type fileSize = ifs.tellg();
	ifs.seekg(0, std::ios::beg);

	std::vector<char> bytes(fileSize);
	ifs.read(bytes.data(), fileSize);

	return std::string(bytes.data(), fileSize); 
}

void Write(std::string const& fileName, std::string const& data)
{
	std::ofstream binFile(fileName, std::ios::out | std::ios::binary);
	if (binFile.is_open())
	{
		binFile.write(data.c_str(), data.size());
	}
}

std::wstring readFile2(const std::string& fileName)
{
	std::ifstream fin(fileName, std::ios::binary);

	//skip BOM
	fin.seekg(2);

	//read as raw bytes
	std::stringstream ss;
	ss << fin.rdbuf();
	std::string bytes = ss.str();

	//make sure len is divisible by 2
	size_t len = bytes.size();
	if (len % 2) len--;

	std::wstring sw;
	for (size_t i = 0; i < len;)
	{
		//little-endian
		int lo = bytes[i++] & 0xFF;
		int hi = bytes[i++] & 0xFF;
		sw.push_back(hi << 8 | lo);
	}

	//std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
	//std::string utf8 = convert.to_bytes(sw);
	return sw;
}

std::tuple<const char*, size_t> readFileBytes(const std::string& fileName)
{
	std::ifstream ifs(fileName.c_str(), std::ios::in | std::ios::binary | std::ios::ate);

	std::ifstream::pos_type fileSize = ifs.tellg();
	ifs.seekg(0, std::ios::beg);

	std::vector<char> bytes(fileSize);
	ifs.read(bytes.data(), fileSize);

	std::string test123(bytes.data(), fileSize);

	return std::tuple<const char*, size_t >{bytes.data(), fileSize};
}

void ConvertGhostRecordingToBase64(const std::string& fileName)
{
	std::string fileContents = readFile(fileName);
	std::string raceContent = base64Encode(fileContents.data(), fileContents.length());
	raceContent += {"\0\0", 2};
	raceContent += 0x0B;
	Write(fileName, raceContent);
}

std::vector<std::string> SplitS(const std::string& s, char delim)
{
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> elems;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
		// elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
	}
	return elems;
}

constexpr unsigned int hash(const char* s, int off = 0) {
	return !s[off] ? 5381 : (hash(s, off + 1) * 33) ^ s[off];
}

std::string convert_csstring(String* str)
{
	std::string cppstr;
	if (str == nullptr)
		return cppstr;

	auto chars = String_ToCharArray(str, NULL);
	if (chars == nullptr)
		return cppstr;

	std::wstring wstr(reinterpret_cast<wchar_t*>(chars->vector), str->fields.m_stringLength);
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;
	cppstr = converter.to_bytes(wstr);

	return cppstr;
}

const std::string DoubleToStr(double x) {
	std::stringstream ss;
	ss << x;
	return ss.str();
}

#endif