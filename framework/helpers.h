// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Helper functions

#pragma once

#include <string>
#include <sstream>
#include <iomanip>
#include <unordered_map>

// Helper function to get the module base address
uintptr_t GetBaseAddress();

// Helper function to append text to a file
void LogWrite(std::string text);

// Helper function to open a new console window and redirect stdout there
void NewConsole();

// Helper function to convert a pointer to hex
template<typename T> std::string to_hex_string(T i) {
    std::stringstream stream;
    stream << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << i;
    return stream.str();
}

app::Type* GetType(std::string Namespace, std::string name);
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