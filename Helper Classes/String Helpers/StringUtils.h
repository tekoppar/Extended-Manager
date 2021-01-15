#pragma once

#include <Windows.h>
#undef MessageBox 
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
#include <regex>

#include "Base64.h"

#ifndef _STRINGUTILS_H
#define _STRINGUTILS_H

namespace sutil {

	static void ReplaceS(std::string& subject, const std::string& search, const std::string& replace)
	{
		size_t pos = 0;
		while ((pos = subject.find(search, pos)) != std::string::npos) {
			subject.replace(pos, search.length(), replace);
			pos += replace.length();
		}
	}

	static std::string ReplaceSR(std::string subject, const std::string& search, const std::string& replace)
	{
		size_t pos = 0;
		std::string newString = subject;
		while ((pos = newString.find(newString, pos)) != std::string::npos) {
			newString.replace(pos, newString.length(), newString);
			pos += newString.length();
		}
		return newString;
	}

	///D _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS 
	static std::string getexepath()
	{
		char result[MAX_PATH];
		return std::string(result, GetModuleFileNameA(NULL, result, MAX_PATH));
	}

	static std::string readFile(const std::string& fileName)
	{
		std::ifstream ifs(fileName.c_str(), std::ios::in | std::ios::binary | std::ios::ate);

		std::ifstream::pos_type fileSize = ifs.tellg();
		ifs.seekg(0, std::ios::beg);

		std::vector<char> bytes(fileSize);
		ifs.read(bytes.data(), fileSize);

		return std::string(bytes.data(), fileSize);
	}

	static std::string ReadFile(const std::string& fileName)
	{
		std::string returnValue = "";
		std::string line;
		std::ifstream myfile(fileName);

		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				returnValue += line;
			}
			myfile.close();
		}

		return returnValue;
	}

	static std::vector<std::string> ReadFileByLine(const std::string& fileName, char delimiter = '\n')
	{
		std::vector<std::string> returnValue;
		returnValue.reserve(800);
		std::string line;
		std::ifstream myfile(fileName);

		if (myfile.is_open())
		{
			while (getline(myfile, line, delimiter))
			{
				returnValue.push_back(line);
			}
			myfile.close();
		}

		return returnValue;
	}

	static void Write(std::string const& fileName, std::string const& data)
	{
		std::ofstream binFile(fileName, std::ios::out | std::ios::binary);
		if (binFile.is_open())
		{
			binFile.write(data.c_str(), data.size());
		}
	}

	static void Append(std::string const& fileName, std::string const& data)
	{
		std::ofstream binFile(fileName, std::ios_base::app | std::ios::out | std::ios::binary);
		if (binFile.is_open())
		{
			binFile.write(data.c_str(), data.size());
		}
	}

	static std::wstring readFile2(const std::string& fileName)
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

	static std::tuple<const char*, size_t> readFileBytes(const std::string& fileName)
	{
		std::ifstream ifs(fileName.c_str(), std::ios::in | std::ios::binary | std::ios::ate);

		std::ifstream::pos_type fileSize = ifs.tellg();
		ifs.seekg(0, std::ios::beg);

		std::vector<char> bytes(fileSize);
		ifs.read(bytes.data(), fileSize);

		std::string test123(bytes.data(), fileSize);

		return std::tuple<const char*, size_t >{bytes.data(), fileSize};
	}

	static std::string ConvertGhostRecordingToBase64(const std::string& fileName, std::string newFileName)
	{
		std::string fileContents = readFile(fileName);
		std::string raceContent = base64Encode(fileContents.data(), (unsigned int)fileContents.length());
		raceContent += {"\0\0", 2};
		return raceContent += 0x0B;
		//Write(newFileName, raceContent);
		//std::remove(fileName.c_str());
	}

	static std::vector<std::string> SplitSs(const std::string& s, const std::string& delim)
	{
		std::stringstream ss(s);
		std::string item;
		std::vector<std::string> elems;
		while (std::getline(ss, item, *delim.data())) {
			elems.push_back(item);
			// elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
		}
		return elems;
	}

	static std::vector<std::string> SplitRegex(const std::string& s, const std::string& delimiters)
	{
		std::regex regex(delimiters);
		std::sregex_token_iterator first{ s.begin(), s.end(), regex, -1 }, last;//the '-1' is what makes the regex split (-1 := what was not matched)
		std::vector<std::string> tokens{ first, last };

		return tokens;
	}

	static std::vector<std::string> SplitTem(const std::string& s, const std::string& delimiters)
	{
		std::vector<std::string> results;
		results.reserve(64);
		std::size_t position = 0;
		std::size_t found = s.find(delimiters, position);
		std::string temp = "";

		while (found != std::string::npos && found <= s.size())
		{
			temp = "";
			temp = s.substr(position, found - position);

			if (temp != "")
			{
				results.push_back(temp);
			}

			position = found + delimiters.size();
			found = s.find(delimiters, position);
		}

		if (position < s.size())
		{
			temp = "";
			temp = s.substr(position, s.size() - position);

			if (temp != "")
			{
				results.push_back(temp);
			}
		}

		return results;
	}

	static std::vector<std::string> SplitTemNeighbours(const std::string& s, const std::string& delimiters)
	{
		std::vector<std::string> results;
		results.reserve(64);
		int position = 0;
		std::size_t found = s.find(delimiters, position);

		if (found != std::string::npos)
			found++;

		std::string temp = "";

		while (found != std::string::npos && found <= s.size())
		{
			temp = "";
			temp = s.substr(position, found - position);

			if (temp != "")
			{
				results.push_back(temp);
			}

			position = (int)found + 1;
			found = s.find(delimiters, position);

			if (found != std::string::npos)
				found++;
		}

		if (position < s.size())
		{
			temp = "";
			temp = s.substr(position, s.size() - position);

			if (temp != "")
			{
				results.push_back(temp);
			}
		}

		return results;
	}

	constexpr unsigned int hash(const char* s, int off = 0) {
		return !s[off] ? 5381 : (hash(s, off + 1) * 33) ^ s[off];
	}

	static std::string convert_csstring(app::String* str)
	{
		std::string cppstr;
		if (str == nullptr)
			return cppstr;

		auto chars = app::String_ToCharArray(str, NULL);
		if (chars == nullptr)
			return cppstr;

		std::wstring wstr(reinterpret_cast<wchar_t*>(chars->vector), str->fields.m_stringLength);
		using convert_type = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_type, wchar_t> converter;
		cppstr = converter.to_bytes(wstr);

		return cppstr;
	}

	static std::string DoubleToStr(double x) {
		std::stringstream ss;
		ss << x;
		return ss.str();
	}

	static bool StringStartsWith(std::string &s, std::string needle)
	{
		return s.substr(0, needle.size()) == needle;
	}

}

namespace futil {

	static std::string TrimLeadingZeroes(std::string string)
	{
		int position = (int)string.find_last_of('0');
		if (position == -1 || position < string.size() - 1)
			return string;

		bool trimComplete = false;
		while (trimComplete == false)
		{
			if (string[position] == '0')
			{
				position--;
				if (position == -1)
					return string;
			}
			else
			{
				return string.substr(0, position + 2);
			}
		}

		return string;
	}

}

#endif