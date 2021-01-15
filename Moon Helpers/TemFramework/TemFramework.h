#pragma once

#ifndef _TEMFRAMEWORK_H
#define _TEMFRAMEWORK_H

#include "tem.h"

namespace tem {
	class TemFramework
	{
	public:
		static std::vector<std::string> IllegalClasses;

		static bool IsMethodVirtual(Il2CppClass* objectClass, Il2CppClass* returnClass, std::string methodName);
		static app::MethodBase* GetBaseMethodFromMethod(Il2CppClass* Class, std::string methodName);
		static Il2CppClass* GetDeclaringClassFromMethod(Il2CppClass* Class, std::string methodName);
	};

	template<typename Return>
	Return* StringToValue(std::string value, int type)
	{
		switch (type)
		{
			default:
			case 188:
			{
				app::Boolean* rValue = (app::Boolean*)il2cpp_object_new((Il2CppClass*)(*app::Boolean__TypeInfo));
				rValue->m_value = value == "True" ? true : false;
				return reinterpret_cast<Return*>(rValue);
			}

			case 192:
			{
				app::Char* rValue = (app::Char*)il2cpp_object_new((Il2CppClass*)(*app::Char__TypeInfo));
				rValue->m_value = value[0];
				return reinterpret_cast<Return*>(rValue);
			}

			case 270:
			{
				app::Int16* rValue = (app::Int16*)il2cpp_object_new((Il2CppClass*)(*app::Int16__TypeInfo));
				rValue->m_value = std::stoi(value);
				return reinterpret_cast<Return*>(rValue);
			}
			case 271:
			{
				app::Int32* rValue = (app::Int32*)il2cpp_object_new((Il2CppClass*)(*app::Int32__TypeInfo));
				rValue->m_value = std::stoi(value);
				return reinterpret_cast<Return*>(rValue);
			}
			case 272:
			{
				app::Int64* rValue = (app::Int64*)il2cpp_object_new((Il2CppClass*)(*app::Int64__TypeInfo));
				rValue->m_value = std::stoi(value);
				return reinterpret_cast<Return*>(rValue);
			}

			case 311:
			{
				app::Single* rValue = (app::Single*)il2cpp_object_new((Il2CppClass*)(*app::Single__TypeInfo));
				rValue->m_value = std::stof(value);
				return reinterpret_cast<Return*>(rValue);
			}

			case 313: return reinterpret_cast<Return*>(CreateString(value));
			case 338:
			{
				app::UInt16* rValue = (app::UInt16*)il2cpp_object_new((Il2CppClass*)(*app::UInt16__TypeInfo));
				rValue->m_value = std::stoi(value);
				return reinterpret_cast<Return*>(rValue);
			}
			case 339:
			{
				app::UInt32* rValue = (app::UInt32*)il2cpp_object_new((Il2CppClass*)(*app::UInt32__TypeInfo));
				rValue->m_value = std::stoi(value);
				return reinterpret_cast<Return*>(rValue);
			}
			case 340:
			{
				app::UInt64* rValue = (app::UInt64*)il2cpp_object_new((Il2CppClass*)(*app::UInt64__TypeInfo));
				rValue->m_value = std::stoi(value);
				return reinterpret_cast<Return*>(rValue);
			}
			/*case 382:
			{
				app::IntPtr* rValue = (app::IntPtr*)il2cpp_object_new((Il2CppClass*)(*app::IntPtr__TypeInfo));
				rValue->m_value = (void*)std::stoi(value);
				return reinterpret_cast<Return*>(rValue);
			}*/

			case 4490:
			{
				app::Bounds* rValue = tem::Bounds(value).ToMoonP();
				return reinterpret_cast<Return*>(rValue);
			}

			case 4643:
			{
				app::Vector3* rValue = tem::Vector3(value).ToMoonP();
				return reinterpret_cast<Return*>(rValue);
			}

			case 4644:
			{
				app::Quaternion* rValue = tem::Quaternion(value).ToMoonP();
				return reinterpret_cast<Return*>(rValue);
			}

			/*case 5082:
			{
				app::Transform* transform = reinterpret_cast<app::Transform*>(object);
				app::GameObject* gameObject = app::Component_1_get_gameObject((app::Component_1*)transform, NULL);
				app::String* oName = app::Object_1_get_name((app::Object_1*)gameObject, NULL);
				PropertyValue = il2cppi_to_string(oName);
			}
			break;*/

			case 4803:
			{
				app::Rect* rValue = tem::Rect(value).ToMoonP();
				return reinterpret_cast<Return*>(rValue);
			}

			case 4872:
			{
				app::Vector2* rValue = tem::Vector2(value).ToMoonP();
				return reinterpret_cast<Return*>(rValue);
			}

			case 4875:
			{
				app::Vector4* rValue = tem::Vector4(value).ToMoonP();
				return reinterpret_cast<Return*>(rValue);
			}
		}
	}
}
#endif