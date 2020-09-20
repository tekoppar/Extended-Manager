#include <Windows.h>
#include <string>
//#include <iostream>
#include <vector>
#include <xstring>
//#include <set>
//#include <locale>
//#include <codecvt>
//#include <fstream>
//#include <sstream>

void ReplaceS(std::string& subject, const std::string& search, const std::string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
}

///D _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS 
/*std::string getexepath()
{
	char result[MAX_PATH];
	return std::string(result, GetModuleFileNameA(NULL, result, MAX_PATH));
}*/

/*std::string readFile(const std::string& fileName)
{
	std::ifstream ifs(fileName.c_str(), std::ios::in | std::ios::binary | std::ios::ate);

	std::ifstream::pos_type fileSize = ifs.tellg();
	ifs.seekg(0, std::ios::beg);

	std::vector<char> bytes(fileSize);
	ifs.read(bytes.data(), fileSize);

	return std::string(bytes.data(), fileSize);
}*/

/*std::wstring readFile2(const std::string& fileName) {
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

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
	std::string utf8 = convert.to_bytes(sw);
	return sw;
}*/

std::vector<std::string> SplitS(const std::string& s, char delim) {
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