#pragma once

#include "HString.h"
#include <string>

#pragma pack(push, 1)
namespace Moon {
	class AkLogger
	{
	public:
		//unsigned char x9[0x9];
		static AkLogger ms_Instance; // 0x0
		unsigned char x9[0x2];
		unsigned char errorLoggerDelegate; // 0x10 AkLogger.ErrorLoggerInteropDelegate

		static AkLogger* get_Instance()
		{
			auto AkLogger_address = Assembly_BaseAddr + 0x259DDF0;
			using __AkLogger = AkLogger * (*)();
			auto AkLogger = reinterpret_cast<__AkLogger>(AkLogger_address);
			return AkLogger();
		}

		static void Message(std::wstring message)
		{
			auto Message_address = Assembly_BaseAddr + 0x2DE000;
			using __Message = void* (*)(const wchar_t*);
			auto Message = reinterpret_cast<__Message>(Message_address);
			Message(message.data());
		}

		static void Warning(std::wstring message)
		{
			auto Warning_address = Assembly_BaseAddr + 0x2DE000;
			using __Warning = void* (*)(const wchar_t*);
			auto Warning = reinterpret_cast<__Warning>(Warning_address);
			Warning(message.data());
		}

		static void Error(std::wstring message)
		{
			auto Error_address = Assembly_BaseAddr + 0x259E180;
			using __Error = void* (*)(const wchar_t*);
			auto Error = reinterpret_cast<__Error>(Error_address);
			Error(message.data());
		}

	protected:
	private:
	};
}
#pragma pack(pop)