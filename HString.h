#pragma once

#include <string>
#include <wchar.h>

#pragma pack(push, 1)

class HString
{
public:

	HString()
	{
		// Turns out it does care what these are, at least inst\vtable
		// Setting it to 1 seems to fix the crashing resulted in injecting
		// too early and also doesn't seem to cause any issues.
		this->m_qwUnk0000_0007 = 0x0;

		this->m_qwUnk0008_000F = 0x0;

		this->m_nLength = 0;
		wmemset(&this->m_wszBytes[0], 0x0, 512 * 4);
	}

	HString(std::wstring value, unsigned long long instVal) : m_qwUnk0000_0007(instVal)
	{
		this->m_qwUnk0008_000F = 0x0;
		const wchar_t* widecstr = value.data();
		this->m_nLength = (unsigned long)wcslen(widecstr) + 1;
		wmemset(&this->m_wszBytes[0], 0x0, 512 * 4);
		wmemcpy(&this->m_wszBytes[0], widecstr, this->m_nLength);
	}

	HString(unsigned long long instVal) : m_qwUnk0000_0007(instVal)
	{
		this->m_qwUnk0008_000F = 0x0;
		this->m_nLength = 0;
		wmemset(&this->m_wszBytes[0], 0x0, 512 * 4);
	}

	// 0x0000 - 0x0007
	unsigned long long m_qwUnk0000_0007;

	// 0x0008 - 0x000F
	unsigned long long m_qwUnk0008_000F;

	// 0x0010 - 0x0013
	unsigned long m_nLength;


	// This expands
	// 0x0014 - 
	wchar_t m_wszBytes[512 * 4];

	static void SetUnknown0(HString* ref, unsigned long long value)
	{
		ref->m_qwUnk0000_0007 = value;
	}

	static void SetUnknown1(HString* ref, unsigned long long value)
	{
		ref->m_qwUnk0008_000F = value;
	}

	static void Set(HString* ref, const wchar_t* newBytes)
	{
		ref->m_nLength = (unsigned long)wcslen(newBytes) + 1;
		wmemset(&ref->m_wszBytes[0], 0x0, 512 * 4);
		wmemcpy(&ref->m_wszBytes[0], newBytes, ref->m_nLength);
	}

	static void Recalcuate(HString* ref)
	{
		ref->m_nLength = (unsigned long)wcslen(ref->m_wszBytes) + 1;
	}
	static void Clear(HString* ref)
	{
		ref->m_nLength = 0;
		wmemset(&ref->m_wszBytes[0], 0x0, 512 * 4);
	}
protected:
private:
};
#pragma pack(pop)