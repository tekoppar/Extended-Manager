#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include "StringUtils.h"
#include "ManagerDef.h"
#include "Adresses.h"
#include "tem.h"

#include "TemFramework.h"

namespace tem {

	tem::ObjectData::ObjectData()
	{
		HasChanged = false;
		Namespace = "";
		ClassName = "";
		Name = "";
		Fields = std::vector<tem::ClassField>();
		Properties = std::vector<tem::ClassProperty>();
		NestedObjects = std::vector<tem::ObjectData>();
		Parent = nullptr;
	}

	std::vector<std::uintptr_t> tem::ObjectData::NestedPointers = std::vector<std::uintptr_t>();

	int  tem::ObjectData::HasField(std::string name)
	{
		for (int i = 0; i < Fields.size(); i++)
		{
			if (Fields[i].Name == name)
				return i;
		}

		return -1;
	}

	int tem::ObjectData::HasProperty(std::string name)
	{
		for (int i = 0; i < Properties.size(); i++)
		{
			if (Properties[i].Name == name)
				return i;
		}

		return -1;
	}

	int tem::ObjectData::HasObject(std::string name)
	{
		for (int i = 0; i < NestedObjects.size(); i++)
		{
			if (NestedObjects[i].Name == name)
				return i;
		}

		return -1;
	}

	bool tem::ObjectData::SetObjectData(std::string componentName, std::string fieldPropName, std::string value)
	{
		if (ClassName == componentName)
		{
			int index = HasField(fieldPropName);

			if (index != -1)
			{
				Fields[index].FieldValue = value;
				Fields[index].HasChanged = true;
				return true;
			}

			index = HasProperty(fieldPropName);

			if (index != -1)
			{
				Properties[index].PropertyValue = value;
				Properties[index].HasChanged = true;
				return true;
			}
		}

		bool wasSet = false;
		for (tem::ObjectData& child : NestedObjects)
		{
			wasSet = child.SetObjectData(componentName, fieldPropName, value);

			if (wasSet == true)
				return true;
		}

		return false;
	}

	bool tem::ObjectData::ShouldSave() const
	{
		if (this->HasChanged == true)
			return true;

		for (auto& field : Fields)
		{
			if (field.HasChanged == true || field.Name == "position" || field.Name == "eulerAngles" || field.Name == "localScale")
				return true;
		}

		for (auto& Property : Properties)
		{
			if (Property.HasChanged == true || Property.Name == "position" || Property.Name == "eulerAngles" || Property.Name == "localScale")
				return true;
		}

		for (auto& nestedObject : NestedObjects)
		{
			bool hasChanged = nestedObject.ShouldSave();
			if (hasChanged == true)
				return true;
		}

		return false;
	}

	void tem::ObjectData::UpdateObjectData(std::vector<std::string> namePath, std::string fieldPropName, std::string value)
	{
		int index = HasObject(namePath[0]);
		if (index != -1)
		{
			std::vector<std::string> newPath = namePath;
			newPath.erase(newPath.begin());

			if (newPath.size() > 0)
			{
				NestedObjects[index].UpdateObjectData(newPath, fieldPropName, value);
			}
		}

		index = HasProperty(namePath[0]);
		if (index != -1)
		{
			std::vector<std::string> newPath = namePath;
			newPath.erase(newPath.begin());

			if (newPath.size() == 0)
			{
				Properties[index].PropertyValue = value;
				Properties[index].HasChanged = true;
			}
		}

		index = HasField(namePath[0]);
		if (index != -1)
		{
			std::vector<std::string> newPath = namePath;
			newPath.erase(newPath.begin());

			if (newPath.size() == 0)
			{
				Fields[index].FieldValue = value;
				Fields[index].HasChanged = true;
			}
		}
	}

	void tem::ObjectData::SetObjectData(std::uintptr_t objectPtr, std::vector<std::string> namePath, std::string parentNamespace, std::string parentClassName)
	{
		for (int i = 0; i < Fields.size(); i++)
		{
			if (Fields[i].HasChanged == true || (Fields[i].Name == "position" || Fields[i].Name == "eulerAngles" || Fields[i].Name == "localScale"))
			{
				bool isStatic = false;
				app::Type* fieldClassType = GetType(Namespace, ClassName);
				app::FieldInfo_1* field1 = app::TypeExtensions_2_GetField(fieldClassType, string_new(Fields[i].ClassName.data()), NULL);

				if (field1 != nullptr)
					isStatic = app::FieldInfo_1_get_IsStatic(field1, NULL);

				std::uintptr_t fieldPtr = objectPtr;
				if (isStatic == true)
					GetAddressOffset(fieldPtr, std::vector<unsigned int>{0xb8, 0x0 + (unsigned int)Fields[i].Offset});
				else
					fieldPtr = fieldPtr + (std::uintptr_t)Fields[i].Offset;

				std::vector<std::string> newNamePath = namePath;
				newNamePath.push_back(Fields[i].Name);
				Fields[i].HasChanged = true;
				TemLogger::Add("Trying to set field " + Fields[i].Name + " to value " + Fields[i].FieldValue);
				SetObjectData(newNamePath, objectPtr, parentNamespace, parentClassName, Fields[i].Name, Fields[i].FieldValue);
			}
		}

		for (std::size_t i = 0; i < Properties.size(); i++)
		{
			if (Properties[i].HasChanged == true || (Properties[i].Name == "position" || Properties[i].Name == "eulerAngles" || Properties[i].Name == "localScale"))
			{
				std::uintptr_t propertyPtr = objectPtr;
				std::vector<PropertyInfo*> propInfo = tem::PropertyHelper::GetPropertiesFromClass(Namespace, ClassName);

				for (PropertyInfo* prop : propInfo)
				{
					if (prop->name == Properties[i].Name && prop->name != "localPosition")
					{
						if (Properties[i].Name == "position" && Properties.size() > 2 && Properties[i + 1].Name == "localPosition")
						{
							for (PropertyInfo* propLP : propInfo)
							{
								if (prop->name == "localPosition")
								{
									std::vector<std::string> newNamePath = namePath;
									newNamePath.push_back(Properties[i + 1].Name);
									SetObjectData(newNamePath, objectPtr, parentNamespace, parentClassName, Properties[i + 1].Name, Properties[i + 1].PropertyValue);
								}
							}
						}

						std::vector<std::string> newNamePath1 = namePath;
						newNamePath1.push_back(Properties[i].Name);
						Properties[i].HasChanged = true;
						TemLogger::Add("Trying to set property " + Properties[i].Name + " to value " + Properties[i].PropertyValue);
						SetObjectData(newNamePath1, objectPtr, parentNamespace, parentClassName, Properties[i].Name, Properties[i].PropertyValue);
					}
				}
			}
		}

		for (int i = 0; i < NestedObjects.size(); i++)
		{
			std::vector<std::string> newNamePath = namePath;
			newNamePath.push_back(NestedObjects[i].ClassName);
			NestedObjects[i].SetObjectData(objectPtr, newNamePath, parentNamespace, parentClassName);
		}
	}

	void tem::ObjectData::SetObjectData(std::vector<std::string> namePath, std::uintptr_t objectPtr, std::string Namespace, std::string Name, std::string fieldPropName, std::string value)
	{
		if (namePath.size() == 0)
		{
			TemLogger::Add("Name path size was 0, not setting object data: " + fieldPropName + " with value: " + value, LogType::Warning);
			return;
		}

		if (namePath[0] == Name)
			namePath.erase(namePath.begin());

		std::vector<FieldInfo*> fields = tem::FieldHelper::GetFieldsFromClass(Namespace, Name);
		std::vector<PropertyInfo*> properties = tem::PropertyHelper::GetPropertiesFromClass(Namespace, Name);

		for (FieldInfo* field : fields)
		{
			if (namePath.size() == 0)
			{
				TemLogger::Add("Field was not found, not setting object data: " + fieldPropName + " with value: " + value, LogType::Warning);
				return;
			}

			if (field->name == namePath[0])
			{
				namePath.erase(namePath.begin());

				bool isStatic = false;
				app::Type* fieldClassType = GetType(Namespace, Name);
				app::FieldInfo_1* field1 = app::TypeExtensions_2_GetField(fieldClassType, string_new(field->name), NULL);

				if (field1 != nullptr)
					isStatic = app::FieldInfo_1_get_IsStatic(field1, NULL);

				if (namePath.size() == 0)
				{
					if (isStatic == true)
						GetAddressOffset(objectPtr, std::vector<unsigned int>{0xb8, 0x0});

					tem::FieldHelper::InvokeFieldSetterMethod(objectPtr, field, value);
					return;
				}
				else 
				{
					if (isStatic == true)
						GetAddressOffset(objectPtr, std::vector<unsigned int>{0xb8, 0x0 + (unsigned int)field->offset});
					else
						objectPtr = objectPtr + (std::uintptr_t)field->offset;

					Il2CppClass* typeClass = il2cpp_class_from_type(field->type);
					std::vector<std::string> newPath = namePath;
					SetObjectData(newPath, objectPtr, typeClass->namespaze, typeClass->name, fieldPropName, value);
				}
			}
		}

		for (PropertyInfo* Property : properties)
		{
			if (namePath.size() == 0)
			{
				TemLogger::Add("Property was not found, not setting object data: " + fieldPropName + " with value: " + value, LogType::Warning);
				return;
			}

			if (Property->name == namePath[0])
			{
				namePath.erase(namePath.begin());

				if (namePath.size() == 0)
				{
					tem::PropertyHelper::InvokePropertySetterMethod((void*)objectPtr, Property, value);
					return;
				}
				else
				{
					if (Property->get != nullptr)
					{
						Il2CppClass* typeClass = il2cpp_class_from_type(Property->get->return_type);
						Il2CppTypeEnum typeEnum = Property->get->return_type->type;

						bool isStruct = false;
						if (typeEnum == Il2CppTypeEnum::IL2CPP_TYPE_VALUETYPE)
						{
							Il2CppClass* typeClass = il2cpp_type_get_class_or_element_class(Property->get->return_type);
							isStruct = tem::TemFramework::IsClassStruct(typeClass->namespaze, typeClass->name);
						}

						if (typeEnum == Il2CppTypeEnum::IL2CPP_TYPE_CLASS || isStruct == true)
						{
							Il2CppObject* nestedObject = tem::ClassProperty::GetPropertyObject((void*)objectPtr, Property);

							if (tem::PtrInRange(nestedObject) == true)
							{
								std::uintptr_t objectPtr = *(std::uintptr_t*)nestedObject;
								std::vector<std::string> newPath = namePath;
								SetObjectData(newPath, objectPtr, typeClass->namespaze, typeClass->name, fieldPropName, value);
							}
						}
					}
				}
			}
		}

		Il2CppClass* Class = GetClass(Namespace, Name);

		if (Class != nullptr && Class->parent != nullptr && Class->parent->name == namePath[0])
		{
			std::vector<std::string> newPath = namePath;
			newPath.erase(newPath.begin());
			SetObjectData(newPath, objectPtr, Class->parent->namespaze, Class->parent->name, fieldPropName, value);
		}

		return;
	}

	void tem::ObjectData::FillObjectData(std::uintptr_t objectPtr, bool IsParent)
	{
		if (vector::contains(tem::ObjectData::NestedPointers, objectPtr) == true && IsParent == false)
			return;

		tem::ObjectData::NestedPointers.push_back(objectPtr);
		std::vector<FieldInfo*> fields = tem::FieldHelper::GetFieldsFromClass(Namespace, ClassName);
		std::vector<PropertyInfo*> properties = tem::PropertyHelper::GetPropertiesFromClass(Namespace, ClassName);

		for (FieldInfo* field : fields)
		{
			int index = HasField(field->name);
			Il2CppTypeEnum typeEnum = field->type->type;
			bool isStatic = false;

			app::Type* fieldClassType = GetType(Namespace, ClassName);
			app::FieldInfo_1* field1 = app::TypeExtensions_2_GetField(fieldClassType, string_new(field->name), NULL);
			if (field1 != nullptr)
				isStatic = app::FieldInfo_1_get_IsStatic(field1, NULL);

			bool isStruct = false;
			if (typeEnum == Il2CppTypeEnum::IL2CPP_TYPE_VALUETYPE)
			{
				Il2CppClass* typeClass = il2cpp_type_get_class_or_element_class(field->type);
				isStruct = tem::TemFramework::IsClassStruct(typeClass->namespaze, typeClass->name);
			}

			if (typeEnum == Il2CppTypeEnum::IL2CPP_TYPE_CLASS || isStruct == true)
			{
				std::uintptr_t nestedObject = tem::ClassField::GetFieldObject((void*)objectPtr, field, isStatic);

				if (tem::PtrInRange(nestedObject) == true)
				{
					Il2CppClass* typeClass = il2cpp_class_from_type(field->type);

					if (this->HasObject(field->name) == -1)
					{
						tem::ObjectData newNestedObject;
						newNestedObject.Namespace = typeClass->namespaze;
						newNestedObject.ClassName = typeClass->name;
						newNestedObject.Name = field->name;
						newNestedObject.Parent = this;
						std::uintptr_t newPtr = *(std::uintptr_t*)nestedObject;

						if (tem::PtrInRange(newPtr) == true)
						{
							newNestedObject.FillObjectData(newPtr);
							NestedObjects.push_back(newNestedObject);
						}
					}
					else
					{
						std::uintptr_t newPtr = *(std::uintptr_t*)nestedObject;
						if (tem::PtrInRange(newPtr) == true)
						{
							NestedObjects[this->HasObject(field->name)].FillObjectData(newPtr);
						}
					}
				}
			}
			else if (typeEnum == Il2CppTypeEnum::IL2CPP_TYPE_GENERICINST)
			{
				const Il2CppType* returnType = field->type->data.generic_class->context.class_inst->type_argv[0];
				Il2CppClass* nestedClass = il2cpp_class_from_type(returnType);
				Il2CppClass* typeClass = il2cpp_class_from_type(field->type);

				if (nestedClass != nullptr)
				{
					std::uintptr_t nestedObject = tem::ClassField::GetFieldObject((void*)objectPtr, field, isStatic);

					if (tem::PtrInRange(nestedObject) == false)
						goto AbortList;

					nestedObject = *(std::uintptr_t*)nestedObject;

					if (tem::PtrInRange(nestedObject) == false)
						goto AbortList;

					int nestedObjectIndex = -1;
					if (this->HasObject(field->name) == -1)
					{
						tem::ObjectData newNestedObject;
						newNestedObject.Namespace = typeClass->namespaze;
						newNestedObject.ClassName = typeClass->name;
						newNestedObject.Name = field->name;
						newNestedObject.Parent = this;
						nestedObjectIndex = NestedObjects.size();
						NestedObjects.push_back(newNestedObject);
					}
					else
						nestedObjectIndex = this->HasObject(field->name);

					switch (field->type->data.type->data.klassIndex)
					{
						case 1563://list
						{
							std::uintptr_t countPtr = nestedObject + 0x18;
							std::uintptr_t arrayPtr = nestedObject + 0x10;
							GetAddressOffset(arrayPtr, std::vector<unsigned int>{0x20});

							if (tem::PtrInRange(countPtr) == false || tem::PtrInRange(arrayPtr) == false)
								goto AbortList;

							std::size_t count = *(unsigned long long*)countPtr;

							if (count > 0 && count < 1000)
							{
								for (std::size_t i = 0; i < count; i++)
								{
									if (returnType->type != Il2CppTypeEnum::IL2CPP_TYPE_CLASS && returnType->type != Il2CppTypeEnum::IL2CPP_TYPE_GENERICINST && returnType->type != Il2CppTypeEnum::IL2CPP_TYPE_ARRAY && returnType->type != Il2CppTypeEnum::IL2CPP_TYPE_SZARRAY)
									{
										tem::ClassField classField = tem::ClassField(field);
										classField.IsStatic = isStatic;
										classField.SetGetFieldValue(returnType->data.klassIndex, (arrayPtr + (i * nestedClass->native_size)), nestedClass->namespaze, nestedClass->name, field->name);
										classField.Parent = &NestedObjects[nestedObjectIndex];
										NestedObjects[nestedObjectIndex].Fields.push_back(classField);
									}
									else
									{
										if (NestedObjects[nestedObjectIndex].HasObject(nestedClass->name) == -1)
										{
											tem::ObjectData newNestedObjectList;
											newNestedObjectList.Namespace = nestedClass->namespaze;
											newNestedObjectList.ClassName = nestedClass->name;
											newNestedObjectList.Name = nestedClass->name;
											newNestedObjectList.Parent = &NestedObjects[nestedObjectIndex];
											std::uintptr_t newPtr = *(std::uintptr_t*)(arrayPtr + (i * 0x8));

											if (tem::PtrInRange(newPtr) == true)
											{
												newNestedObjectList.FillObjectData(newPtr);
												NestedObjects[nestedObjectIndex].NestedObjects.push_back(newNestedObjectList);
											}
										}
										else
										{
											std::uintptr_t newPtr = *(std::uintptr_t*)(arrayPtr + (i * 0x8));
											if (tem::PtrInRange(newPtr) == true)
											{
												NestedObjects[nestedObjectIndex].NestedObjects[NestedObjects[nestedObjectIndex].HasObject(nestedClass->name)].FillObjectData(newPtr);
											}
										}
									}
								}
							}
						}
					}
				}
			AbortList:
				continue;
			}
			else
			{
				if (index == -1)
				{
					tem::ClassField classField = tem::ClassField(field);
					classField.IsStatic = isStatic;
					classField.GetFieldValue(objectPtr, field);
					classField.Parent = this;
					this->Fields.push_back(classField);
				}
				else
				{
					Fields[index].Parent = this;
					Fields[index].GetFieldValue(objectPtr, field);
				}
			}
		}

		for (PropertyInfo* Property : properties)
		{
			if (Property->get == nullptr)
			{
				tem::ClassProperty CProperty = tem::ClassProperty(Property);
				CProperty.PropertyValue = "NO GET METHOD";
				CProperty.Parent = this;
				this->Properties.push_back(CProperty);
				continue;
			}

			int index = HasProperty(Property->name);
			Il2CppTypeEnum typeEnum = Property->get->return_type->type;

			bool isStruct = false;
			if (typeEnum == Il2CppTypeEnum::IL2CPP_TYPE_VALUETYPE)
			{
				Il2CppClass* typeClass = il2cpp_type_get_class_or_element_class(Property->get->return_type);
				isStruct = tem::TemFramework::IsClassStruct(typeClass->namespaze, typeClass->name);
			}

			if (typeEnum == Il2CppTypeEnum::IL2CPP_TYPE_CLASS || isStruct == true)
			{
				Il2CppObject* nestedObject = tem::ClassProperty::GetPropertyObject((void*)objectPtr, Property);

				if (nestedObject != nullptr)
				{
					Il2CppClass* typeClass = il2cpp_class_from_type(Property->get->return_type);

					if (this->HasObject(Property->name) == -1)
					{
						tem::ObjectData newNestedObject;
						newNestedObject.Namespace = typeClass->namespaze;
						newNestedObject.ClassName = typeClass->name;
						newNestedObject.Name = Property->name;
						newNestedObject.Parent = this;
						std::uintptr_t newPtr = *(std::uintptr_t*)nestedObject;

						if (tem::PtrInRange(newPtr) == true)
						{
							newNestedObject.FillObjectData(newPtr);
							NestedObjects.push_back(newNestedObject);
						}
					}
					else if (tem::PtrInRange(objectPtr) == true)
					{
						std::uintptr_t newPtr = *(std::uintptr_t*)nestedObject;
						NestedObjects[this->HasObject(Property->name)].FillObjectData(newPtr);
					}
				}
			}
			else
			{
				if (index == -1)
				{
					tem::ClassProperty CProperty = tem::ClassProperty(Property);
					CProperty.GetPropertyValue((void*)objectPtr, Property);
					CProperty.Parent = this;
					this->Properties.push_back(CProperty);
				}
				else
				{
					Properties[index].Parent = this;
					Properties[index].GetPropertyValue((void*)objectPtr, Property);
				}
			}
		}

		Il2CppClass* Class = GetClass(Namespace, ClassName);

		if (Class != nullptr && Class->parent != nullptr)
		{
			if (this->HasObject(Class->parent->name) == -1)
			{
				tem::ObjectData newNestedObject;
				newNestedObject.Namespace = Class->parent->namespaze;
				newNestedObject.Name = newNestedObject.ClassName = Class->parent->name;
				newNestedObject.Parent = this;

				if (tem::PtrInRange(objectPtr) == true)
				{
					newNestedObject.FillObjectData(objectPtr, true);
					NestedObjects.push_back(newNestedObject);
				}
			}
			else if (tem::PtrInRange(objectPtr) == true)
				NestedObjects[this->HasObject(Class->parent->name)].FillObjectData(objectPtr, true);
		}
	}

	std::string tem::ObjectData::ToJsonString()
	{
		std::string json = "{\"Name\":\"" + this->Name + "\",\"Fields\":[";
		for (int i = 0; i < this->Fields.size(); i++)
		{
			tem::ClassField field = this->Fields[i];
			json += field.ToJsonString();
			if (this->Fields.size() - 1 > i)
				json += ",";
		}

		json += "],\"Properties\":[";

		for (int i = 0; i < this->Properties.size(); i++)
		{
			tem::ClassProperty Property = this->Properties[i];
			json += Property.ToJsonString();
			if (this->Properties.size() - 1 > i)
				json += ",";
		}

		json += "],\"NestedObjects\":[";

		for (int i = 0; i < NestedObjects.size(); i++)
		{
			json += NestedObjects[i].ToJsonString();
			if (NestedObjects.size() - 1 > i)
				json += ",";
		}

		return json + "]}";
	}

	std::vector<std::string> tem::TemFramework::IllegalClasses = { "UberShaderModifier", "StringBuilder"};

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

	
	bool tem::TemFramework::IsClassStruct(Il2CppClass* Class)
	{
		app::Type* objectType = GetType(Class->namespaze, Class->name);

		if (objectType != nullptr)
			return IsClassStruct(objectType);

		return false;
	}

	bool tem::TemFramework::IsClassStruct(std::string Namespace, std::string Name)
	{
		app::Type* objectType = GetType(Namespace, Name);

		if (objectType != nullptr)
			return IsClassStruct(objectType);

		return false;
	}

	bool tem::TemFramework::IsClassStruct(app::Type* type)
	{
		
		if (type != nullptr && app::Type_get_IsValueType(type, NULL) == true && app::Type_get_IsEnum(type, NULL) == false)
		{
			app::ConstructorInfo__Array* constructorArr = app::Type_GetConstructors(type, NULL);

			if (constructorArr != nullptr)
			{
				int count = app::Array_System_Collections_ICollection_get_Count((app::Array*)constructorArr, NULL);

				return count == 0;
			}
			else
				return false;
		}

		return false;
	}
}