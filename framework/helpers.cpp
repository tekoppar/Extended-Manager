// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Helper functions
#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>
#include "helpers.h"

std::unordered_map<std::string, Il2CppClass*> resolved_classes;

// Log file location
extern const LPCWSTR LOG_FILE;

// Helper function to get the module base address
uintptr_t GetBaseAddress() {
    return (uintptr_t) GetModuleHandleW(L"GameAssembly.dll");
}

// Helper function to append text to a file
void LogWrite(std::string text) {
    HANDLE hfile = CreateFileW(LOG_FILE, FILE_APPEND_DATA, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hfile == INVALID_HANDLE_VALUE)
        MessageBoxW(0, L"Could not open log file", 0, 0);

    DWORD written;
    WriteFile(hfile, text.c_str(), (DWORD) text.length(), &written, NULL);
    WriteFile(hfile, "\r\n", 2, &written, NULL);
    CloseHandle(hfile);
}

// Helper function to open a new console window and redirect stdout there
void NewConsole() {
    AllocConsole();
    freopen_s((FILE**) stdout, "CONOUT$", "w", stdout);
}

template<typename Return>
Return* GetClass(std::string Namespace, std::string name)
{
    std::string const& fullName = Namespace + "." + name;
    auto it = resolved_classes.find(fullName);
    if (it != resolved_classes.end())
        return it->second;

    Il2CppClass* Class = nullptr;
    size_t i = 0;
    size_t size = 0;
    auto domain = il2cpp_domain_get();
    auto assemblies = il2cpp_domain_get_assemblies(domain, &size);
    while (Class == nullptr && i < size)
    {
        auto image = il2cpp_assembly_get_image(assemblies[i]);
        Class = il2cpp_class_from_name(image, Namespace.data(), name.data());
        ++i;
    }

    // Add it to resolved classes anyway to prevent trace spam and future lookups.
    resolved_classes[fullName] = Class;

    return reinterpret_cast<Return*>(Class);
}

char* GetQualified(std::string Namespace, std::string name)
{
    auto Class = GetClass<>(Namespace, name);
    auto type = il2cpp_class_get_type(Class);
    return il2cpp_type_get_assembly_qualified_name(type);
}

app::Type* GetType(std::string Namespace, std::string name)
{
    auto qualified = GetQualified(Namespace, name);
    auto type_str = reinterpret_cast<app::String*>(il2cpp_string_new(qualified));
    return app::Type_GetType_5(type_str, false, NULL);
}