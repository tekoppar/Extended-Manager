#pragma once

#include <string>
#include "Adresses.h"

#pragma pack(push, 1)
namespace Moon {
	class MoonString
	{
		const int TrimHead = 0; // 0x0
		const int TrimTail = 1; // 0x0
		const int TrimBoth = 2; // 0x0
		const int charPtrAlignConst = 1; // 0x0
		const int alignConst = 3; // 0x0

	public:
		// 0x0000 - 0x0007
		unsigned long long m_qwUnk0000_0007;
		// 0x0008 - 0x000F
		unsigned long long m_qwUnk0008_000F;
		int m_stringLength = 0; // 0x10
		char* m_firstChar;

		MoonString(char* value = 0)
		{
			//const wchar_t* widecstr = value.data() + '\0';
			this->m_qwUnk0000_0007 = 1;
			this->m_qwUnk0008_000F = 0;
			this->m_stringLength = sizeof(value) + 1;// wcslen(widecstr) + 1;
			this->m_firstChar = value;
			/*auto MoonString_address = Assembly_BaseAddr + 0x1CD2DC0;
			using __MoonString = char(*)(MoonString*, char*);
			auto MoonString = reinterpret_cast<__MoonString>(MoonString_address);
			MoonString(this, string);*/
		}

		static void Set(MoonString* ref, const wchar_t* newBytes)
		{
			ref->m_stringLength = (int)wcslen(newBytes) + 1;
			//wmemset(&ref->m_firstChar[0], 0x0, 512 * 4);
			//wmemcpy(&ref->m_firstChar[0], newBytes, ref->m_stringLength);
		}

		char get_Chars(int index)
		{
			auto get_Chars_address = Assembly_BaseAddr + 0x1CD1490;
			using MoonString__get_Chars = char(*)(MoonString*, int);
			auto get_Chars = reinterpret_cast<MoonString__get_Chars>(get_Chars_address);
			return get_Chars(this, index);
		}

		MoonString CreateString(char c, int count)
		{
			auto CreateString_address = Assembly_BaseAddr + 0x1CDB780;
			using MoonString__CreateString = MoonString(*)(MoonString*, char, int);
			auto CreateString = reinterpret_cast<MoonString__CreateString>(CreateString_address);
			return CreateString(this, c, count);
		}

		/*MoonString CreateString(char string[])
		{
			auto CreateString_address = Assembly_BaseAddr + 0x1CDB690;
			using MoonString__CreateString = MoonString(*)(MoonString*, char[]);
			auto CreateString = reinterpret_cast<MoonString__CreateString>(CreateString_address);
			return CreateString(this, string);
		}*/

		MoonString CreateString(char* value)
		{
			auto CreateString_address = Assembly_BaseAddr + 0x1CDB660;
			using MoonString__CreateString = MoonString(*)(MoonString*, char*);
			auto CreateString = reinterpret_cast<MoonString__CreateString>(CreateString_address);
			return CreateString(this, value);
		}

	protected:
	private:

	};
}
#pragma pack(pop)