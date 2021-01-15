#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include "StringUtils.h"
#include "ManagerDef.h"
#include "Tem.h"
#include "TemFramework.h"

#include "PropertyHelper.h"

namespace tem {

	ClassProperty::ClassProperty()
	{
		HasChanged = false;
		Name = "";
		ReturnType = tem::VariableType::Null;
		PropertyValue = "";
	}

	ClassProperty::ClassProperty(PropertyInfo* Property)
	{
		HasChanged = false;
		Name = Property->name;

		if (Property->get != nullptr)
		{
			ReturnType = tem::VariableType::Null;
			PropertyValue = "";
		}
		else
		{
			ReturnType = tem::VariableType::Null;
			PropertyValue = "";
		}
	}

	std::string tem::ClassProperty::ToJsonString()
	{
		return "{\"Name\":\"" + this->Name + "\",\"ReturnType\":" + std::to_string(static_cast<int>(this->ReturnType)) + ",\"PropertyValue\":\"" + this->PropertyValue + "\"}";
	}

	std::string tem::ClassProperty::SaveJsonProperty()
	{
		return "{\"" + this->Name + "\":\"" + this->PropertyValue + "\",\"ReturnType\":" + std::to_string(static_cast<int>(this->ReturnType)) + "}";
	}

	tem::ClassProperty* tem::ClassProperty::GetPropertyByName(std::string name)
	{
		if (this->Name == name)
			return this;

		return nullptr;
	}

	void tem::ClassProperty::GetPropertyValue(void* object, PropertyInfo* Property)
	{
		if (Property->get != nullptr && Property->get->klass->byval_arg.data.klassIndex != -1)
		{
			Il2CppTypeEnum typeEnum = Property->get->return_type->type;
			if (typeEnum != Il2CppTypeEnum::IL2CPP_TYPE_SZARRAY && typeEnum != Il2CppTypeEnum::IL2CPP_TYPE_ARRAY && typeEnum != Il2CppTypeEnum::IL2CPP_TYPE_GENERICINST)
			{
				Il2CppObject* iL2object = PropertyHelper::InvokePropertyMethod(object, Property);
				void* objectUnboxed = il2cpp_object_unbox(iL2object);
				if (iL2object != nullptr && iL2object->klass != nullptr && (std::uintptr_t)iL2object->klass > 0x00ffffff && iL2object->klass->klass != nullptr)
				{
					Il2CppClass* typeClass = il2cpp_class_from_type(Property->get->return_type);
					if (typeClass != nullptr)
					{
						app::Type* typeType = GetType(typeClass->namespaze, typeClass->name);
						bool isEnum = false;

						if (typeType != nullptr)
							isEnum = app::Type_get_IsEnum(typeType, NULL);

						if (isEnum == true)
						{
							uint64_t* value = (uint64_t*)(objectUnboxed);

							if (value != nullptr)
							{
								app::Object* object = app::Enum_ToObject_8(typeType, *value, (*app::Enum_ToObject_8__MethodInfo));

								if (object == nullptr)
									PropertyValue = "";

								app::String* enumValue = app::Enum_GetName(typeType, object, (*app::Enum_GetName__MethodInfo));

								if (enumValue == nullptr || enumValue == 0x0)
									PropertyValue = "";
								else
									PropertyValue = il2cppi_to_string(enumValue);
							}
							else
								PropertyValue = "";

							ReturnType = tem::VariableType::Enum;
							return;
						}
					}

					switch (iL2object->klass->byval_arg.data.klassIndex)
					{
						case 188:
						{
							app::Boolean* boolean = (app::Boolean*)iL2object;
							PropertyValue = std::to_string(boolean->m_value);
							ReturnType = tem::VariableType::Bool;
						}
						break;

						case 192:
						{
							app::Char* character = (app::Char*)iL2object;
							PropertyValue = std::to_string(character->m_value);
							ReturnType = tem::VariableType::Char;
						}
						break;

						case 220:
						{
							app::Enum__Boxed* enumValue = reinterpret_cast<app::Enum__Boxed*>(iL2object);
							PropertyValue = il2cppi_to_string(app::Enum_ToString(enumValue, NULL)); ReturnType = tem::VariableType::String; break;
						}
						break;

						case 270:
						{
							app::Int16* int16 = reinterpret_cast<app::Int16*>(objectUnboxed);
							PropertyValue = std::to_string(int16->m_value);
							ReturnType = tem::VariableType::Short;
						}
						break;

						case 271:
						{
							app::Int32* int32 = reinterpret_cast<app::Int32*>(objectUnboxed);
							PropertyValue = std::to_string(int32->m_value);
							ReturnType = tem::VariableType::Integer;
						}
						break;

						case 272:
						{
							app::Int64* int64 = reinterpret_cast<app::Int64*>(objectUnboxed);
							PropertyValue = std::to_string(int64->m_value);
							ReturnType = tem::VariableType::Long;
						}
						break;

						case 311:
						{
							app::Single* single = reinterpret_cast<app::Single*>(objectUnboxed);
							PropertyValue = std::to_string(single->m_value);
							ReturnType = tem::VariableType::Float;
						}
						break;

						case 313: PropertyValue = il2cppi_to_string((app::String*)iL2object); ReturnType = tem::VariableType::String; break;
						case 338:
						{
							app::UInt16* int16 = reinterpret_cast<app::UInt16*>(objectUnboxed);
							PropertyValue = std::to_string(int16->m_value);
							ReturnType = tem::VariableType::UShort;
						}
						break;

						case 339:
						{
							app::UInt32* int32 = reinterpret_cast<app::UInt32*>(objectUnboxed);
							PropertyValue = std::to_string(int32->m_value);
							ReturnType = tem::VariableType::UInt;
						}
						break;

						case 340:
						{
							app::UInt64* int64 = reinterpret_cast<app::UInt64*>(objectUnboxed);
							PropertyValue = std::to_string(int64->m_value);
							ReturnType = tem::VariableType::ULong;
						}
						break;

						case 382:
						{
							app::IntPtr* intPtr = (app::IntPtr*)iL2object;
							PropertyValue = std::to_string((unsigned long long)intPtr->m_value);
							ReturnType = tem::VariableType::Pointer;
						}
						break;

						case 4490:
						{
							app::Bounds* vectorValue = reinterpret_cast<app::Bounds*>(objectUnboxed);
							PropertyValue = tem::Bounds(vectorValue).ToString();
							ReturnType = tem::VariableType::Bounds;
						}
						break;

						case 4643:
						{
							app::Vector3* vectorValue = reinterpret_cast<app::Vector3*>(objectUnboxed);
							PropertyValue = tem::Vector3(vectorValue).ToString();
							ReturnType = tem::VariableType::Vector3;
						}
						break;

						case 4644:
						{
							app::Quaternion* quat = reinterpret_cast<app::Quaternion*>(objectUnboxed);
							PropertyValue = tem::Quaternion(quat).ToString();
							ReturnType = tem::VariableType::Quaternion;
						}
						break;

						case 4803:
						{
							app::Rect* rect = reinterpret_cast<app::Rect*>(objectUnboxed);
							PropertyValue = tem::Rect(rect).ToString();
							ReturnType = tem::VariableType::Rect;
						}
						break;

						case 4872:
						{
							app::Vector2* vectorValue = reinterpret_cast<app::Vector2*>(objectUnboxed);
							PropertyValue = tem::Vector2(vectorValue).ToString();
							ReturnType = tem::VariableType::Vector2;
						}
						break;

						/*case 5082:
						{
							app::Transform* transform = reinterpret_cast<app::Transform*>(iL2object);
							app::GameObject* gameObject = app::Component_1_get_gameObject((app::Component_1*)transform, NULL);
							app::String* oName = app::Object_1_get_name((app::Object_1*)gameObject, NULL);
							PropertyValue = il2cppi_to_string(oName);
							ReturnType = tem::VariableType::String;
						}
						break;*/
					}
				}
			}
		}
		else
		{
			PropertyValue = "NO GET METHOD";
			ReturnType = tem::VariableType::String;
		}
	}

	void tem::ClassProperty::SetPropertyValue(void* object, std::string Namespace, std::string name, std::string fieldPropName, std::string value, tem::ClassProperty* Property)
	{
		std::vector<PropertyInfo*> propInfo = tem::PropertyHelper::GetPropertiesFromClass(Namespace, name);

		for (PropertyInfo* prop : propInfo)
		{
			if (prop->name == Property->Name)
			{
				HasChanged = true;
				tem::PropertyHelper::InvokePropertySetterMethod(object, prop, value);
			}
		}
	}

	std::vector<PropertyInfo*> tem::PropertyHelper::GetPropertiesFromClass(std::string Namespace, std::string name)
	{
		std::vector<PropertyInfo*> properties;
		auto Class = GetClass<>(Namespace, name);
		void* it = nullptr;
		for (int i = 0; i < Class->property_count; i++)
		{
			PropertyInfo* Property = const_cast<PropertyInfo*>(il2cpp_class_get_properties(Class, &it));
			properties.push_back(Property);
		}

		if (Class->parent != nullptr)
		{
			std::vector<PropertyInfo*> parentProperties = tem::PropertyHelper::GetPropertiesFromClass(Class->parent->namespaze, Class->parent->name);
			if (parentProperties.size() > 0)
				properties.insert(properties.end(), parentProperties.begin(), parentProperties.end());
		}

		return properties;
	}

	std::vector<tem::ClassProperty> tem::PropertyHelper::FillProperties(void* object, std::vector<PropertyInfo*> properties)
	{
		std::vector<tem::ClassProperty> classProperties;
		for (PropertyInfo* Property : properties)
		{
			tem::ClassProperty CProperty = tem::ClassProperty(Property);
			CProperty.GetPropertyValue(object, Property);
			classProperties.push_back(CProperty);
		}

		return classProperties;
	}

	Il2CppObject* tem::PropertyHelper::InvokePropertyMethod(void* object, PropertyInfo* Property)
	{
		Il2CppClass* declaringType = il2cpp_method_get_declaring_type(Property->get);
		const Il2CppType* returnType = il2cpp_method_get_return_type(Property->get);
		Il2CppClass* returnTypeClass = il2cpp_class_from_type(returnType);
		Il2CppObject* il2object = reinterpret_cast<Il2CppObject*>(object);

		bool isInterface = il2cpp_class_is_interface(declaringType);
		bool isReturnTypeInterface = il2cpp_class_is_interface(returnTypeClass);
		bool isVirtualMethod = tem::TemFramework::IsMethodVirtual(declaringType, returnTypeClass, Property->name);
		auto baseClass = tem::TemFramework::GetBaseMethodFromMethod(declaringType, Property->get->name);
		auto declaringClass = tem::TemFramework::GetDeclaringClassFromMethod(declaringType, Property->get->name);
		//Il2CppException** mExec = nullptr;

		if (isInterface == false && isReturnTypeInterface == false && Property->get != nullptr && Property->get->klass != nullptr && Property->get->klass->byval_arg.data.klassIndex != -1 && (baseClass != nullptr || declaringClass != nullptr))
		{
			std::string className = declaringClass->name;
			bool isIllegal = vector::contains(tem::TemFramework::IllegalClasses, className);

			if (isIllegal == true)
				return nullptr;

			try
			{
				Il2CppException* exec = nullptr;
				const MethodInfo* virtualMethod = il2cpp_object_get_virtual_method(il2object, Property->get);

				void* params = (void*)Property->get->parameters;
				Il2CppObject* returnObject = nullptr;

				if (isVirtualMethod == false && (virtualMethod == nullptr || virtualMethod->methodPointer == Property->get->methodPointer))
				{
					//il2cpp_runtime_object_init_exception((Il2CppObject*)object, mExec);
					try { returnObject = il2cpp_runtime_invoke(Property->get, object, &params, &exec); }
					catch (...)
					{
						std::ofstream binFile("C:\\moon\\manager_error.log", std::ios_base::app | std::ios::out | std::ios::binary);
						if (binFile.is_open())
						{
							std::string errorMessage = "Il2CppExceptionWrapper occured\r\n";
							binFile.write(errorMessage.c_str(), errorMessage.size());
						}
					}
				}
				else
					return nullptr;

				if (returnObject != nullptr && returnObject->klass != nullptr)
				{
					return returnObject;
				}
			}
			catch (Il2CppExceptionWrapper e)
			{
				std::ofstream binFile("C:\\moon\\manager_error.log", std::ios_base::app | std::ios::out | std::ios::binary);
				if (binFile.is_open())
				{
					std::string errorMessage = "Il2CppExceptionWrapper occured:" + il2cppi_to_string(e.ex->message) + "\r\n";
					binFile.write(errorMessage.c_str(), errorMessage.size());
				}
			}
		}

		return nullptr;
	}

	void tem::PropertyHelper::InvokePropertySetterMethod(void* object, PropertyInfo* Property, std::string value)
	{
		if (Property->set == nullptr || object == nullptr)
			return;

		Il2CppClass* declaringType = il2cpp_method_get_declaring_type(Property->set);
		const Il2CppType* returnType = il2cpp_method_get_return_type(Property->set);
		Il2CppClass* returnTypeClass = il2cpp_class_from_type(returnType);
		Il2CppObject* il2object = reinterpret_cast<Il2CppObject*>(object);

		bool isInterface = il2cpp_class_is_interface(declaringType);
		bool isReturnTypeInterface = il2cpp_class_is_interface(returnTypeClass);
		bool isVirtualMethod = tem::TemFramework::IsMethodVirtual(declaringType, returnTypeClass, Property->name);
		auto baseClass = tem::TemFramework::GetBaseMethodFromMethod(declaringType, Property->set->name);
		auto declaringClass = tem::TemFramework::GetDeclaringClassFromMethod(declaringType, Property->set->name);
		Il2CppException** mExec = nullptr;

		if (isInterface == false && isReturnTypeInterface == false && Property->set != nullptr && Property->set->klass != nullptr && Property->set->klass->byval_arg.data.klassIndex != -1 && (baseClass != nullptr || declaringClass != nullptr))
		{
			try
			{
				Il2CppException* exec = nullptr;
				const MethodInfo* virtualMethod = il2cpp_object_get_virtual_method(il2object, Property->set);

				std::vector<void*> values;
				for (int i = 0; i < Property->set->parameters_count; i++)
				{
					switch (Property->set->parameters[i].parameter_type->data.klassIndex)
					{
						case 188: values.push_back((void*)tem::StringToValue<app::Boolean*>(value, Property->set->parameters[i].parameter_type->data.klassIndex)); break;
						case 192: values.push_back((void*)tem::StringToValue<app::Char*>(value, Property->set->parameters[i].parameter_type->data.klassIndex)); break;
						case 270: values.push_back((void*)tem::StringToValue<app::Int16*>(value, Property->set->parameters[i].parameter_type->data.klassIndex)); break;
						case 271: values.push_back((void*)tem::StringToValue<app::Int32*>(value, Property->set->parameters[i].parameter_type->data.klassIndex)); break;
						case 272: values.push_back((void*)tem::StringToValue<app::Int64*>(value, Property->set->parameters[i].parameter_type->data.klassIndex)); break;
						case 311: values.push_back((void*)tem::StringToValue<app::Single*>(value, Property->set->parameters[i].parameter_type->data.klassIndex)); break;
						case 313: values.push_back((void*)tem::StringToValue<app::String*>(value, Property->set->parameters[i].parameter_type->data.klassIndex)); break;
						case 338: values.push_back((void*)tem::StringToValue<app::UInt16*>(value, Property->set->parameters[i].parameter_type->data.klassIndex)); break;
						case 339: values.push_back((void*)tem::StringToValue<app::UInt32*>(value, Property->set->parameters[i].parameter_type->data.klassIndex)); break;
						case 340: values.push_back((void*)tem::StringToValue<app::UInt64*>(value, Property->set->parameters[i].parameter_type->data.klassIndex)); break;
							//case 382: values.push_back((void*)tem::StringToValue<app::IntPtr*>(value, Property->set->parameters[i].parameter_type->data.klassIndex)); break;
						case 4490: values.push_back((void*)tem::StringToValue<app::Bounds*>(value, Property->set->parameters[i].parameter_type->data.klassIndex)); break;
						case 4643:values.push_back((void*)tem::StringToValue<app::Vector3*>(value, Property->set->parameters[i].parameter_type->data.klassIndex)); break;
						case 4644:values.push_back((void*)tem::StringToValue<app::Quaternion*>(value, Property->set->parameters[i].parameter_type->data.klassIndex)); break;
							//case 5082: values.push_back((void*)tem::StringToValue<app::String*>(value, Property->set->parameters[i].parameter_type->data.klassIndex)); break;
						case 4803: values.push_back((void*)tem::StringToValue<app::Rect*>(value, Property->set->parameters[i].parameter_type->data.klassIndex)); break;
						case 4872: values.push_back((void*)tem::StringToValue<app::Vector2*>(value, Property->set->parameters[i].parameter_type->data.klassIndex)); break;
						case 4875: values.push_back((void*)tem::StringToValue<app::Vector4*>(value, Property->set->parameters[i].parameter_type->data.klassIndex)); break;
					}
				}

				if (values.size() > 0)
				{
					void** params = values.data();
					Il2CppObject* returnObject = nullptr;

					if (isVirtualMethod == false && (virtualMethod == nullptr || virtualMethod->methodPointer == Property->set->methodPointer))
					{
						il2cpp_runtime_object_init_exception((Il2CppObject*)object, mExec);
						try { returnObject = il2cpp_runtime_invoke(Property->set, object, params, &exec); }
						catch (...)
						{
							std::ofstream binFile("C:\\moon\\manager_error.log", std::ios_base::app | std::ios::out | std::ios::binary);
							if (binFile.is_open())
							{
								std::string errorMessage = "Il2CppExceptionWrapper occured\r\n";
								binFile.write(errorMessage.c_str(), errorMessage.size());
							}
						}
					}
					else
						return;
				}
				else
					return;
			}
			catch (Il2CppExceptionWrapper e)
			{
				std::ofstream binFile("C:\\moon\\manager_error.log", std::ios_base::app | std::ios::out | std::ios::binary);
				if (binFile.is_open())
				{
					std::string errorMessage = "Il2CppExceptionWrapper occured:" + il2cppi_to_string(e.ex->message) + "\r\n";
					binFile.write(errorMessage.c_str(), errorMessage.size());
				}
			}
		}
	}
}