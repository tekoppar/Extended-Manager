#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include "StringUtils.h"
#include "ManagerDef.h"
#include "tem.h"

#include "TemFramework.h"

namespace tem {
	std::vector<std::string> tem::TemFramework::IllegalClasses = { "UberShaderModifier" };

	bool tem::TemFramework::IsMethodVirtual(Il2CppClass* objectClass, Il2CppClass* returnClass, std::string methodName)
	{
		app::Type* returnType = GetType(returnClass->namespaze, returnClass->name);
		app::Type* objectType = GetType(objectClass->namespaze, objectClass->name);
		if (returnType == nullptr || objectType == nullptr)
			return false;

		app::String* propertyName = CreateString(methodName);
		app::PropertyInfo_1* propertyInfo = app::Type_GetProperty_3(objectType, propertyName, returnType, (*app::Type_GetProperty_3__MethodInfo));

		if (propertyInfo == nullptr)
			return false;

		return app::ReflectionUtils_IsVirtual(propertyInfo, NULL);
	}

	app::MethodBase* tem::TemFramework::GetBaseMethodFromMethod(Il2CppClass* Class, std::string methodName)
	{
		app::Type* objectType = GetType(Class->namespaze, Class->name);
		if (objectType == nullptr)
			return nullptr;

		app::String* methodNameT = CreateString(methodName);
		app::Object* method = (app::Object*)app::TypeExtensions_2_GetMethod(objectType, methodNameT, NULL);
		app::RuntimeMethodHandle handle;

		if (method == nullptr)
			return nullptr;

		std::string methodNameTemp = method->klass->_0.name;

		if (methodNameTemp == "MonoMethod")
		{
			handle = app::MonoMethod_get_MethodHandle((app::MonoMethod*)method, NULL);
		}
		else if (methodNameTemp == "MonoCMethod")
		{
			handle = app::MonoCMethod_get_MethodHandle((app::MonoCMethod*)method, NULL);
		}
		else if (methodNameTemp == "DynamicMethod")
		{
			handle = app::DynamicMethod_get_MethodHandle((app::DynamicMethod*)method, NULL);
		}
		else if (methodNameTemp == "ConstructorBuilder")
		{
			handle = app::ConstructorBuilder_get_MethodHandle((app::ConstructorBuilder*)method, NULL);
		}
		else if (methodNameTemp == "MethodBuilder")
		{
			handle = app::MethodBuilder_get_MethodHandle((app::MethodBuilder*)method, NULL);
		}
		else
			return nullptr;

		app::MethodBase* baseMethod = app::MethodBase_GetMethodFromHandle(handle, NULL);

		if (baseMethod != nullptr)
			return baseMethod;

		return nullptr;
	}

	Il2CppClass* tem::TemFramework::GetDeclaringClassFromMethod(Il2CppClass* Class, std::string methodName)
	{
		app::Type* objectType = GetType(Class->namespaze, Class->name);
		if (objectType == nullptr)
			return nullptr;

		app::String* methodNameT = CreateString(methodName);
		app::Object* method = (app::Object*)app::TypeExtensions_2_GetMethod(objectType, methodNameT, NULL);

		if (method == nullptr)
			return nullptr;

		Il2CppClass* declaringClass = nullptr;
		app::Type* declaringType = nullptr;
		std::string className = method->klass->_0.name;

		if (className == "MonoMethod")
		{
			declaringType = app::MonoMethod_get_DeclaringType((app::MonoMethod*)method, NULL);
		}
		else if (className == "MonoCMethod")
		{
			declaringType = app::MonoCMethod_get_DeclaringType((app::MonoCMethod*)method, NULL);
		}
		else if (className == "MonoProperty")
		{
			declaringType = app::MonoProperty_get_DeclaringType((app::MonoProperty*)method, NULL);
		}
		else if (className == "DynamicMethod")
		{
			declaringType = app::DynamicMethod_get_DeclaringType((app::DynamicMethod*)method, (*app::DynamicMethod_get_DeclaringType__MethodInfo));
		}
		else if (className == "ConstructorBuilder")
		{
			declaringType = app::ConstructorBuilder_get_DeclaringType((app::ConstructorBuilder*)method, (*app::ConstructorBuilder_get_DeclaringType__MethodInfo));
		}
		else if (className == "FieldBuilder")
		{
			declaringType = app::FieldBuilder_get_DeclaringType((app::FieldBuilder*)method, (*app::FieldBuilder_get_DeclaringType__MethodInfo));
		}
		else if (className == "MethodBuilder")
		{
			declaringType = app::MethodBuilder_get_DeclaringType((app::MethodBuilder*)method, (*app::MethodBuilder_get_DeclaringType__MethodInfo));
		}
		else if (className == "PropertyBuilder")
		{
			declaringType = app::PropertyBuilder_get_DeclaringType((app::PropertyBuilder*)method, (*app::PropertyBuilder_get_DeclaringType__MethodInfo));
		}
		else if (className == "SerializationFieldInfo")
		{
			declaringType = app::SerializationFieldInfo_get_DeclaringType((app::SerializationFieldInfo*)method, NULL);
		}
		else if (className == "RuntimeType")
		{
			declaringType = app::RuntimeType_get_DeclaringType((app::RuntimeType*)method, NULL);
		}
		else
			return nullptr;

		std::uintptr_t ptr = (std::uintptr_t)declaringType->fields._impl.value;
		ptr = ptr - 0x20;
		declaringClass = (Il2CppClass*)(ptr);

		if (declaringClass == Class)
			return declaringClass;

		Il2CppType* il2type = (Il2CppType*)(declaringType->fields._impl.value);
		declaringClass = il2cpp_class_from_il2cpp_type(il2type);

		return declaringClass;
	}
}