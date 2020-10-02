#include "pch-il2cpp.h"

/*#include <string>
#include <vector>
#include <unordered_map>

#include "Adresses.h"

namespace ClassUtil {
#include "FindClass.h"
}

std::unordered_map<std::string, ClassUtil::Il2CppClass*> resolved_classes;

typedef ClassUtil::Il2CppClass*(*Il2cpp_ClassFromName)(ClassUtil::Il2CppImage* image, const char* namezpace, const char* name);
//Il2cpp_ClassFromName oIl2cpp_ClassFromName;

typedef ClassUtil::Il2CppImage*(*Il2cpp_AssemblyGetImage)(ClassUtil::Il2CppAssembly* assembly);
//Il2cpp_AssemblyGetImage oIl2cpp_AssemblyGetImage;;

typedef ClassUtil::Il2CppAssembly**(*Il2cpp_DomainGetAssemblies)(ClassUtil::Il2CppDomain* domain, size_t* size);
//Il2cpp_DomainGetAssemblies oIl2cpp_DomainGetAssemblies;

typedef ClassUtil::Il2CppDomain*(*Il2cpp_DomainGet)();
//Il2cpp_DomainGet oIl2CppDomain;

Il2cpp_ClassFromName oIl2cpp_ClassFromName = Il2cpp_ClassFromName(Assembly_BaseAddr + 0x262560);
Il2cpp_AssemblyGetImage oIl2cpp_AssemblyGetImage = Il2cpp_AssemblyGetImage(Assembly_BaseAddr + 0x101220);
Il2cpp_DomainGetAssemblies oIl2cpp_DomainGetAssemblies = Il2cpp_DomainGetAssemblies(Assembly_BaseAddr + 0x262CE0);
Il2cpp_DomainGet oIl2CppDomain = Il2cpp_DomainGet(Assembly_BaseAddr + 0x262CA0);

void get_class(std::string_view namezpace, std::string_view name) //ClassUtil::Il2CppClass*
{
	ClassUtil::Il2CppClass* klass = nullptr;
	size_t i = 0;
	size_t size = 0;
	auto domain = oIl2CppDomain();
	auto assemblies = oIl2cpp_DomainGetAssemblies(domain, &size);

	while (klass == nullptr && i < size)
	{
		auto image = oIl2cpp_AssemblyGetImage(assemblies[i]);
		klass = oIl2cpp_ClassFromName(image, namezpace.data(), name.data());
	}
}*/