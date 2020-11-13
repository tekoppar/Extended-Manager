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




///// MESSAGE POPUPS
/*
if (doOnce1 == false)
	{
		app::Type* MessageControllerBType = GetType("", "MessageControllerB");
		app::Object_1__Array* MessageControllerBArr = app::Object_1_FindObjectsOfTypeAll(MessageControllerBType, NULL);

		app::MessageControllerB* MessageControllerB = (app::MessageControllerB*)MessageControllerBArr->vector[0];

		app::Vector3* anchorSize = (app::Vector3*)il2cpp_object_new((Il2CppClass*)app::Vector3__TypeInfo);
		anchorSize->x = 0;
		anchorSize->y = 0;

		auto Class2 = GetClass<>("", "MessageDescriptor");
		app::MessageDescriptor__Boxed* messageDescriptor = (app::MessageDescriptor__Boxed*)il2cpp_object_new((Il2CppClass*)Class2);
		app::String* messageText1 = string_new("test<xbox>p</>");
		app::MessageDescriptor__ctor_1(messageDescriptor, messageText1, NULL);

		newBox = app::MessageControllerB_ShowHintMessage_1(MessageControllerB, messageDescriptor->fields, *anchorSize, 10.0f, NULL);
		//newBox->fields.MessageIndex = 1;

		doOnce1 = true;
	}

	if (newBox != nullptr)
	{
		auto Class1 = GetClass<>("", "MessageBox");
		app::MessageBox* MessageBox = (app::MessageBox*)il2cpp_object_new((Il2CppClass*)Class1);

		app::String* messageText = string_new("test");
		app::MessageBox__ctor(MessageBox, NULL);
		app::GameObject__ctor((app::GameObject*)MessageBox, messageText, NULL);
		MessageBox->fields.LanguageStyles = newBox->fields.LanguageStyles;
		MessageBox->fields.TextBox = newBox->fields.TextBox;
		MessageBox->fields.Visibility = newBox->fields.Visibility;

		auto Class2 = GetClass<>("", "MessageDescriptor");
		app::MessageDescriptor__Boxed* messageDescriptor = (app::MessageDescriptor__Boxed*)il2cpp_object_new((Il2CppClass*)Class2);
		std::string replaceS = "test<xbox>p</>" + std::to_string(totalFrames);
		app::String* messageText1 = string_new(replaceS.data());
		app::MessageDescriptor__ctor_1(messageDescriptor, messageText1, NULL);
		MessageBox->fields.OverrideText = messageText1;
		MessageBox->fields.m_currentMessage = messageDescriptor->fields;
		MessageBox->fields.Visibility->fields.DestroyOnHide = false;
		MessageBox->fields.Visibility->fields.m_time = 999999999.0f;
		app::MessageBox_SetMessageFade(MessageBox, 10, NULL);
		app::MessageBox_RefreshText(MessageBox, NULL);
	}
*/