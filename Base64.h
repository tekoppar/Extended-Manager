#ifndef _BASE64_H_
#define _BASE64_H_

#include <vector>
#include <string>
typedef unsigned char BYTE;

std::string base64Encode(const char* buf, unsigned int bufLen);
std::vector<BYTE> base64Decode(std::string const&);

#endif