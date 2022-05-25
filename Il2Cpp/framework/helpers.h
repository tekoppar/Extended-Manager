// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Helper functions

#pragma once

#include <string>
#include <sstream>
#include <iomanip>
#include <unordered_map>

#ifdef _WOTW_PATCH_THREE
#include "il2cpp-metadata-version.h"
#endif

#ifdef _WOTW_PATCH_TWO
#include "../appdata_1_2/il2cpp-metadata-version.h"
#endif

// Helper function to get the module base address
uintptr_t il2cppi_get_base_address();

// Helper function to append text to a file
void il2cppi_log_write(std::string text);

// Helper function to open a new console window and redirect stdout there
void il2cppi_new_console();

#if _MSC_VER >= 1920
// Helper function to convert Il2CppString to std::string
std::string il2cppi_to_string(Il2CppString* str);

// Helper function to convert System.String to std::string
std::string il2cppi_to_string(app::String* str);

void utf16_to_utf8(const std::u16string& utf16, std::string& utf8);
void utf8_to_utf16(const std::string& utf8, std::u16string& utf16);
#endif

// Helper function to check if a metadata usage pointer is initialized
template<typename T> bool il2cppi_is_initialized(T* metadataItem)
{
#if __IL2CPP_METADATA_VERISON < 270
	return *metadataItem != 0;
#else
	// Metadata >=27 (Unity 2020.2)
	return !((uintptr_t)*metadataItem & 1);
#endif
}

// Helper function to convert a pointer to hex
template<typename T> std::string to_hex_string(T i)
{
	std::stringstream stream;
	stream << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << i;
	return stream.str();
}

app::String* CreateString(std::string& s);
app::Type* GetTypeFromObject(app::Object_1* object);
app::Type* GetTypeFromClass(Il2CppClass* Class);
char* GetQualifiedFromClass(Il2CppClass* Class);
app::Type* GetType(std::string Namespace, std::string name);
app::Type* GetTypeFromName(std::string name);
char* GetQualified(std::string Namespace, std::string name);
template<typename Return = Il2CppClass>
Return* GetClass(std::string Namespace, std::string name);

template<typename Return>
static Return* GetObjectByType(std::string Namespace, std::string Name)
{
	app::Type* objectType = GetType(Namespace, Name);
	app::Object_1__Array* objectArr = app::Object_1_FindObjectsOfType(objectType, NULL);

	if (objectArr != nullptr && objectArr->vector[0] != nullptr)
		return reinterpret_cast<Return*>(objectArr->vector[0]);

	return nullptr;
}

/*template<typename Return = Il2CppClass>
Return* GetClass(std::string Namespace, std::string name)
{
	return reinterpret_cast<Return*>(untype::GetClass(Namespace, name));
}*/