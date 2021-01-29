#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <limits>

#include "StringUtils.h"
#include "ManagerDef.h"
#include "TemFramework.h"
#include "Tem.h"
#include "Adresses.h"

#include "FieldHelper.h"

namespace tem {

	std::vector<std::uintptr_t> tem::ClassField::NestedPointers = std::vector<std::uintptr_t>();

	ClassField::ClassField()
	{
		Name = "";
		TypeDefIndex = -1;
		Offset = -1;
		IsStatic = false;
		HasChanged = false;
		Type = tem::VariableType::Null;
		FieldValue = "";
		ParentName = "";
		ClassName = Namespace = "";
		Parent = nullptr;
	}


	ClassField::ClassField(FieldInfo* field)
	{
		Name = field->name;
		TypeDefIndex = field->type->data.klassIndex;
		Offset = field->offset;
		IsStatic = false;
		HasChanged = false;
		Type = tem::VariableType::Null;
		FieldValue = "";
		ParentName = "";
		Namespace = field->parent->namespaze;
		ClassName = field->parent->name;
		Parent = nullptr;
	}

	std::string tem::ClassField::ToJsonString()
	{
		return "{\"Name\":\"" + this->Name + "\",\"TypeDefIndex\":" + std::to_string(this->TypeDefIndex) + ",\"ParentName\":\"" + this->ParentName + "\",\"FieldValue\":\"" + this->FieldValue + "\",\"Type\":" + std::to_string(static_cast<int>(this->Type)) + "}";
	}

	std::string tem::ClassField::SaveJsonField()
	{
		return "{\"" + this->Name + "\":\"" + this->FieldValue + ",\"Type\":" + std::to_string(static_cast<int>(this->Type)) + "}";
	}

	std::uintptr_t tem::ClassField::GetFieldObject(void* object, FieldInfo* field, bool isStatic)
	{
		std::uintptr_t ptr = (std::uintptr_t)object;

		if (tem::PtrInRange(ptr) == false)
			return 0x0;

		if (isStatic == true)
		{
			return GetAddressOffset(ptr, std::vector<unsigned int>{0xb8, 0x0 + (unsigned int)field->offset});
		}
		else
			return ptr + (std::uintptr_t)field->offset;
	}

	void tem::ClassField::GetFieldValue(std::uintptr_t fieldPtr, FieldInfo* field)
	{
		std::uintptr_t ptr = fieldPtr;

		std::string fieldName = std::string(field->name);
		if (vector::contains<std::string>(tem::FieldHelper::IllegalFields, fieldName) == true)
			return;

		if (tem::PtrInRange(ptr) == false)
			return;

		if (IsStatic == true)
		{
			GetAddressOffset(ptr, std::vector<unsigned int>{0xb8, 0x0 + (unsigned int)field->offset});
		}
		else
			ptr = ptr + (std::uintptr_t)field->offset;

		Il2CppTypeEnum typeEnum = field->type->type;

		if (tem::PtrInRange(ptr) == false)
			return;

		bool isStruct = false;
		/*if (typeEnum == Il2CppTypeEnum::IL2CPP_TYPE_VALUETYPE)
		{
			Il2CppClass* typeClass = il2cpp_type_get_class_or_element_class(field->type);
			isStruct = tem::TemFramework::IsClassStruct(typeClass->namespaze, typeClass->name);
		}*/

		if (isStruct == true)
		{
			Il2CppClass* typeClass = il2cpp_type_get_class_or_element_class(field->type);
			std::vector<FieldInfo*> fields = tem::FieldHelper::GetFieldsFromClass(typeClass);
			tem::ClassField::NestedPointers.push_back((std::uintptr_t)field);

			for (FieldInfo* structdField : fields)
			{
				if (structdField->type->data.klassIndex > 0 && structdField->type->data.klassIndex < 1000000)
				{
					std::uintptr_t tempPtr = (std::uintptr_t)structdField;
					if (vector::contains<std::uintptr_t>(tem::ClassField::NestedPointers, tempPtr) == false)
					{
						tem::ClassField classField = tem::ClassField(structdField);

						classField.ParentName = typeClass->name;
						classField.GetFieldValue(ptr, structdField);
						//Fields.push_back(classField);
					}
				}
			}
		}
		else if (typeEnum == Il2CppTypeEnum::IL2CPP_TYPE_CLASS && field->type->data.klassIndex != 334)
		{
			Il2CppClass* nestedClass = il2cpp_type_get_class_or_element_class(field->type);
			std::string nestedClassName = nestedClass->name;

			if (nestedClassName == "PCMReaderCallback" || nestedClassName == "PCMSetPositionCallback")
				return;

			if (nestedClass != nullptr)
			{
				ptr = *(std::uintptr_t*)(ptr);

				if (tem::PtrInRange(ptr) == false)
					return;

				std::vector<FieldInfo*> fields = tem::FieldHelper::GetFieldsFromClass(nestedClass);
				tem::ClassField::NestedPointers.push_back((std::uintptr_t)field);

				for (FieldInfo* nestedField : fields)
				{
					if (nestedField->type->data.klassIndex > 0 && nestedField->type->data.klassIndex < 1000000)
					{
						std::uintptr_t tempPtr = (std::uintptr_t)nestedField;
						if (vector::contains<std::uintptr_t>(tem::ClassField::NestedPointers, tempPtr) == false)
						{
							tem::ClassField classField = tem::ClassField(nestedField);

							classField.ParentName = nestedClass->name;
							classField.GetFieldValue(ptr, nestedField);
							//Fields.push_back(classField);
						}
					}
				}
			}
		}
		else if (typeEnum == Il2CppTypeEnum::IL2CPP_TYPE_GENERICINST)
		{
			const Il2CppType* returnType = field->type->data.generic_class->context.class_inst->type_argv[0];
			Il2CppClass* nestedClass = il2cpp_class_from_type(returnType);
			//Il2CppClass* nestedClass = il2cpp_type_get_class_or_element_class(field->type);

			if (nestedClass != nullptr)
			{
				switch (field->type->data.type->data.klassIndex)
				{
					case 1563://list
					{
						std::uintptr_t countPtr = ptr;
						GetAddressOffset(countPtr, std::vector<unsigned int>{0x18});
						std::uintptr_t arrayPtr = ptr;
						GetAddressOffset(arrayPtr, std::vector<unsigned int>{0x10, 0x20});

						if (tem::PtrInRange(countPtr) == false)
							return;

						std::size_t count = *(unsigned long long*)countPtr;

						if (count > 0 && count < 1000)
						{
							for (std::size_t i = 0; i < count; i++)
							{
								if (returnType->type != Il2CppTypeEnum::IL2CPP_TYPE_CLASS && returnType->type != Il2CppTypeEnum::IL2CPP_TYPE_GENERICINST && returnType->type != Il2CppTypeEnum::IL2CPP_TYPE_ARRAY && returnType->type != Il2CppTypeEnum::IL2CPP_TYPE_SZARRAY)
								{
									SetGetFieldValue(returnType->data.klassIndex, arrayPtr + (i * 0x8), Namespace, ClassName, nestedClass->name);
								}
								else
								{
									std::uintptr_t tempPtr = *(std::uintptr_t*)(arrayPtr + (i * 0x8));

									if (tempPtr == 0 || tem::PtrInRange(tempPtr) == false)
										continue;

									std::vector<FieldInfo*> fields = tem::FieldHelper::GetFieldsFromClass(nestedClass);
									tem::ClassField::NestedPointers.push_back((std::uintptr_t)field);

									for (FieldInfo* nestedField : fields)
									{
										if (nestedField->type->data.klassIndex > 0 && nestedField->type->data.klassIndex < 1000000)
										{
											if (vector::contains<std::uintptr_t>(tem::ClassField::NestedPointers, tempPtr) == false)
											{
												tem::ClassField classField = tem::ClassField(nestedField);

												if (classField.Name == "PCMReaderCallback" || classField.Name == "PCMSetPositionCallback")
													return;

												classField.ParentName = nestedClass->name;
												classField.GetFieldValue(tempPtr, nestedField);
												//Fields.push_back(classField);
											}
										}
									}
								}
							}
						}
					}
					break;

					case 1521://dictionary
					{

					}
					break;

					case 151://action
					{

					}
					break;

					case 4405://hashset
					{

					}
					break;
				}
			}
		}
		else
		{
			Il2CppClass* typeClass = il2cpp_type_get_class_or_element_class(field->type);
			if (typeClass != nullptr)
			{
				app::Type* typeType = GetType(typeClass->namespaze, typeClass->name);
				bool isEnum = false;

				if (typeType != nullptr)
					isEnum = app::Type_get_IsEnum(typeType, NULL);

				if (isEnum == true)
				{
					FieldValue = tem::FieldHelper::GetFieldEnum(ptr, Namespace, ClassName, field->name, typeType);
					Type = tem::VariableType::Enum;
				}
			}

			if (field->type->data.klassIndex == 334)
				SetGetFieldValue(field->type->data.klassIndex, fieldPtr, Namespace, ClassName, field->name);
			else
				SetGetFieldValue(field->type->data.klassIndex, ptr, Namespace, ClassName, field->name);
		}
	}

	void tem::ClassField::SetGetFieldValue(int klassIndex, std::uintptr_t ptr, std::string Namespace, std::string ClassName, std::string name)
	{
		if (tem::PtrInRange(ptr) == false)
		{
			TemLogger::Add("Pointer value out of range or nullptr", LogType::Warning);
			FieldValue = "NULL";
			Type = tem::VariableType::String;
			return;
		}

		switch (klassIndex)
		{
			case 188: FieldValue = std::to_string(tem::FieldHelper::GetFieldBool(ptr, Namespace, ClassName, name)); Type = tem::VariableType::Bool; break;
			case 192: FieldValue = tem::FieldHelper::GetFieldChar(ptr, Namespace, ClassName, name); Type = tem::VariableType::Char; break;
			case 271: FieldValue = std::to_string(tem::FieldHelper::GetFieldInt(ptr, Namespace, ClassName, name)); Type = tem::VariableType::Integer; break;
			case 382: FieldValue = std::to_string(tem::FieldHelper::GetFieldPtr(ptr, Namespace, ClassName, name)); Type = tem::VariableType::Pointer; break;
			case 311: FieldValue = std::to_string(tem::FieldHelper::GetFieldFloat(ptr, Namespace, ClassName, name)); Type = tem::VariableType::Float; break;
			case 313: FieldValue = tem::FieldHelper::GetFieldString(ptr, Namespace, ClassName, name); Type = tem::VariableType::String; break;
			case 334: FieldValue = tem::FieldHelper::GetType(ptr, Namespace, ClassName, name); Type = tem::VariableType::String; break;
			case 4490: FieldValue = tem::Bounds(tem::FieldHelper::GetFieldBounds(ptr, Namespace, ClassName, name)).ToString(); Type = tem::VariableType::Bounds; break;
			case 4502: FieldValue = tem::Vector4(tem::FieldHelper::GetFieldColor(ptr, Namespace, ClassName, name)).ToString(); Type = tem::VariableType::Color; break;
			case 4642: FieldValue = tem::Matrix4x4(tem::FieldHelper::GetMatrix4x4(ptr, Namespace, ClassName, name)).ToString(); Type = tem::VariableType::Matrix4x4; break;
			case 4643: FieldValue = tem::Vector3(tem::FieldHelper::GetFieldVector3(ptr, Namespace, ClassName, name)).ToString(); Type = tem::VariableType::Vector3; break;
			case 4644: FieldValue = tem::Quaternion(tem::FieldHelper::GetFieldQuaternion(ptr, Namespace, ClassName, name)).ToString(); Type = tem::VariableType::Quaternion; break;
			case 4803: FieldValue = tem::Rect(tem::FieldHelper::GetFieldRect(ptr, Namespace, ClassName, name)).ToString(); Type = tem::VariableType::Rect; break;
			case 4872: FieldValue = tem::Vector2(tem::FieldHelper::GetFieldVector2(ptr, Namespace, ClassName, name)).ToString(); Type = tem::VariableType::Vector2; break;
			case 4875: FieldValue = tem::Vector4(tem::FieldHelper::GetFieldVector4(ptr, Namespace, ClassName, name)).ToString(); Type = tem::VariableType::Vector4; break;
		}
	}

	void tem::ClassField::SetFieldValue(std::uintptr_t objectPtr, std::string Namespace, std::string name, std::string fieldPropName, std::string value, ClassField* Field)
	{
		std::vector<FieldInfo*> fields = tem::FieldHelper::GetFieldsFromClass(Namespace, name);

		for (FieldInfo* field : fields)
		{
			if (field->name == Field->Name)
			{
				HasChanged = true;
				tem::FieldHelper::InvokeFieldSetterMethod(objectPtr + field->offset, field, value);
			}
		}
	}

	std::vector<std::string> tem::FieldHelper::IllegalFields = { "Delimiter" };

	void tem::FieldHelper::InvokeFieldSetterMethod(std::uintptr_t ptr, FieldInfo* field, std::string value)
	{
		if (field == nullptr)
			return;

		ptr += field->offset;

		InvokeFieldSetterMethod(ptr, field->type->data.klassIndex, value);
	}

	void tem::FieldHelper::InvokeFieldSetterMethod(std::uintptr_t ptr, int klassIndex, std::string value)
	{
		if (value == "NULL")
			return;

		switch (klassIndex)
		{
			case 188:
			{
				app::Boolean* temp1 = (app::Boolean*)ptr;

				if (tem::PtrInRange(temp1) == true)
					temp1->m_value = tem::StringToValue<app::Boolean*>(value, klassIndex);
			}
			break;
			case 192:
			{
				app::Char* temp2 = (app::Char*)ptr;

				if (tem::PtrInRange(temp2) == true)
					*temp2 = *tem::StringToValue<app::Char>(value, klassIndex);
			}
			break;

			/*case 220:
			{
				app::Enum* tempE = (app::Enum*)(ptr);
				int val = std::stoi(value);
				*tempE = val;
			}
			break;*/

			case 271:
			{
				app::Int32* temp3 = (app::Int32*)ptr;

				if (tem::PtrInRange(temp3) == true)
					temp3->m_value = std::stoi(value);
				//*temp3 = *tem::StringToValue<app::Int32>(value, klassIndex);
			}
			break;
			case 311:
			{
				app::Single* temp4 = (app::Single*)ptr;

				if (tem::PtrInRange(temp4) == true)
					temp4->m_value = std::stof(value);
				//*temp4 = *tem::StringToValue<app::Single>(value, klassIndex);
			}
			break;
			case 313:
			{
				app::String* temp5 = (app::String*)ptr;

				if (tem::PtrInRange(temp5) == true)
				{
					app::String* newString = string_new(value.data());
					temp5->fields.m_firstChar = newString->fields.m_firstChar;
					temp5->fields.m_stringLength = newString->fields.m_stringLength;
				}
				//*temp5 = *tem::StringToValue<app::String>(value, klassIndex);
			}
			break;

			case 4490:
			{
				app::Bounds* tempBounds = (app::Bounds*)ptr;

				if (tem::PtrInRange(tempBounds) == true)
				{
					tem::Bounds values = tem::Bounds(value);
					tempBounds->m_Center = values.Center.ToMoon();
					tempBounds->m_Extents = values.Extents.ToMoon();
				}
			}

			case 4502:
			{
				app::Color* temp9 = (app::Color*)ptr;

				if (tem::PtrInRange(temp9) == true)
				{
					tem::Vector4 values = tem::Vector4(value);
					temp9->r = values.X;
					temp9->g = values.Y;
					temp9->b = values.Z;
					temp9->a = values.A;
				}
			}
			break;
			//case 382: values.push_back((void*)tem::StringToValue<app::IntPtr*>(value, field->set->parameters[i].parameter_type->data.klassIndex)); break;
			case 4642:
			{
				app::Matrix4x4* temp6 = (app::Matrix4x4*)ptr;

				if (tem::PtrInRange(temp6) == true)
				{
					tem::Matrix4x4 values = tem::Matrix4x4(value);
					temp6 = values.ToMoonP();
				}
			}
			break;
			case 4643:
			{
				app::Vector3* temp6 = (app::Vector3*)ptr;

				if (tem::PtrInRange(temp6) == true)
				{
					tem::Vector3 values = tem::Vector3(value);
					temp6->x = values.X;
					temp6->y = values.Y;
					temp6->z = values.Z;
				}
				//*temp6 = *tem::StringToValue<app::Vector3>(value, klassIndex);
			}
			break;
			case 4644:
			{
				app::Quaternion* temp7 = (app::Quaternion*)ptr;

				if (tem::PtrInRange(temp7) == true)
					*temp7 = *tem::StringToValue<app::Quaternion>(value, klassIndex);
			}
			break;
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
				app::Rect* temp8 = (app::Rect*)ptr;

				if (tem::PtrInRange(temp8) == true)
				{
					tem::Vector4 values = tem::Vector4(value);
					temp8->m_XMin = values.X;
					temp8->m_YMin = values.Y;
					temp8->m_Width = values.Z;
					temp8->m_Height = values.A;
				}
				//*temp8 = *tem::StringToValue<app::Rect>(value, klassIndex);
			}
			break;

			case 4872:
			{
				app::Vector2* temp10 = (app::Vector2*)ptr;

				if (tem::PtrInRange(temp10) == true)
				{
					tem::Vector2 values = tem::Vector2(value);
					temp10->x = values.x;
					temp10->y = values.y;
				}
				//*temp6 = *tem::StringToValue<app::Vector3>(value, klassIndex);
			}
			break;

			case 4875:
			{
				app::Vector4* temp9 = (app::Vector4*)ptr;

				if (tem::PtrInRange(temp9) == true)
				{
					tem::Vector4 values = tem::Vector4(value);
					temp9->x = values.X;
					temp9->y = values.Y;
					temp9->z = values.Z;
					temp9->w = values.A;
				}
			}
			break;
		}
	}

	FieldInfo* tem::FieldHelper::GetNestedFieldFromField(std::uintptr_t& fieldPtr, FieldInfo* Field, std::vector<std::string>& fieldHierarchy)
	{
		Il2CppClass* nestedClass = il2cpp_type_get_class_or_element_class(Field->type);

		if (nestedClass != nullptr && fieldHierarchy.size() > 0)
		{
			std::size_t count = il2cpp_class_num_fields(nestedClass);
			void* it = nullptr;

			if (count > 0)
			{
				fieldPtr = fieldPtr + (std::uintptr_t)Field->offset;

				for (int i = 0; i < count; i++)
				{
					FieldInfo* field = il2cpp_class_get_fields(nestedClass, &it);

					if (field != nullptr && field->offset > 0 && field->name == fieldHierarchy[0])
					{
						std::uintptr_t newPtr = fieldPtr;
						Il2CppTypeEnum typeEnum = Field->type->type;
						if (typeEnum == Il2CppTypeEnum::IL2CPP_TYPE_CLASS)
							newPtr = *(std::uintptr_t*)fieldPtr;

						if (tem::PtrInRange(newPtr) == false)
							newPtr = fieldPtr;

						fieldPtr = newPtr;
						fieldHierarchy.erase(fieldHierarchy.begin());

						if (fieldHierarchy.size() > 0)
							return tem::FieldHelper::GetNestedFieldFromField(fieldPtr, field, fieldHierarchy);
						else
							return field;
					}
				}
			}
		}

		return Field;
	}

	std::vector<FieldInfo*> tem::FieldHelper::GetFieldsFromClass(std::string Namespace, std::string name)
	{
		std::vector<FieldInfo*> fields;
		auto Class = GetClass<>(Namespace, name);

		if (Class != NULL)
		{
			std::size_t count = il2cpp_class_num_fields(Class);
			void* it = nullptr;
			for (int i = 0; i < count; i++)
			{
				FieldInfo* field = il2cpp_class_get_fields(Class, &it);
				fields.push_back(field);
			}
		}

		return fields;
	}

	std::vector<FieldInfo*> tem::FieldHelper::GetNonNestedFieldsFromClass(std::string Namespace, std::string name)
	{
		std::vector<FieldInfo*> fields;
		auto Class = GetClass<>(Namespace, name);
		std::size_t count = il2cpp_class_num_fields(Class);
		void* it = nullptr;
		for (int i = 0; i < count; i++)
		{
			FieldInfo* field = il2cpp_class_get_fields(Class, &it);
			fields.push_back(field);
		}

		return fields;
	}

	std::vector<FieldInfo*> tem::FieldHelper::GetFieldsFromClass(Il2CppClass* Class)
	{
		std::vector<FieldInfo*> fields;
		std::size_t count = il2cpp_class_num_fields(Class);
		void* it = nullptr;
		for (int i = 0; i < count; i++)
		{
			FieldInfo* field = il2cpp_class_get_fields(Class, &it);

			if (field != nullptr && field->offset > 0)
				fields.push_back(field);
		}

		return fields;
	}

	std::vector<tem::ClassField> tem::FieldHelper::FillFields(void* object, std::vector<FieldInfo*> fields)
	{
		std::vector<tem::ClassField> classFields;
		std::uintptr_t ptr = (std::uintptr_t)object;
		for (FieldInfo* field : fields)
		{
			std::string fieldName = std::string(field->name);
			if (vector::contains<std::string>(tem::FieldHelper::IllegalFields, fieldName) == false)
			{
				tem::ClassField CField = tem::ClassField(field);
				CField.GetFieldValue(ptr, field);
				classFields.push_back(CField);
			}
		}

		return classFields;
	}

	FieldInfo* tem::FieldHelper::GetFieldByName(Il2CppObject* object, std::string Namespace, std::string name, std::string fieldName)
	{
		auto Class = GetClass<>(Namespace, name);
		std::size_t count = il2cpp_class_num_fields(Class);
		void* it = nullptr;
		for (int i = 0; i < count; i++)
		{
			FieldInfo* field = il2cpp_class_get_fields(Class, &it);
			if (field->name == fieldName)
			{
				return field;
			}
		}
		return nullptr;
	}

	bool tem::FieldHelper::GetFieldBool(std::uintptr_t ptr, std::string Namespace, std::string name, std::string fieldName)
	{
		app::Boolean* value = (app::Boolean*)(ptr);

		if (tem::PtrInRange(value) == true)
			return value->m_value;

		return false;
	}

	char tem::FieldHelper::GetFieldChar(std::uintptr_t ptr, std::string Namespace, std::string name, std::string fieldName)
	{
		app::Char* value = (app::Char*)(ptr);

		if (tem::PtrInRange(value) == true)
			return value->m_value;

		return 0x0;
	}

	std::string tem::FieldHelper::GetFieldString(std::uintptr_t ptr, std::string Namespace, std::string name, std::string fieldName)
	{
		app::String* value = (app::String*)(ptr);

		if (tem::PtrInRange(value) == true && tem::PtrInRange(value->klass) == true)
		{
			bool isNullOrEmpty = app::String_IsNullOrEmpty(value, NULL);
			if (isNullOrEmpty == false && value->fields.m_stringLength > 0 && value->fields.m_stringLength < 5000)
			{
				return il2cppi_to_string(value);
			}
		}

		return "NULL";
	}

	std::uintptr_t tem::FieldHelper::GetFieldPtr(std::uintptr_t ptr, std::string Namespace, std::string name, std::string fieldName)
	{
		std::uintptr_t* value = (std::uintptr_t*)(ptr);

		if (tem::PtrInRange(value) == true)
			return *value;

		return 0x0;
	}

	app::Vector3* tem::FieldHelper::GetFieldVector3(std::uintptr_t ptr, std::string Namespace, std::string name, std::string fieldName)
	{
		app::Vector3* value = (app::Vector3*)(ptr);

		if (tem::PtrInRange(value) == true)
			return value;

		return nullptr;
	}

	app::Vector4* tem::FieldHelper::GetFieldVector4(std::uintptr_t ptr, std::string Namespace, std::string name, std::string fieldName)
	{
		app::Vector4* value = (app::Vector4*)(ptr);

		if (tem::PtrInRange(value) == true)
			return value;

		return nullptr;
	}

	app::Color* tem::FieldHelper::GetFieldColor(std::uintptr_t ptr, std::string Namespace, std::string name, std::string fieldName)
	{
		app::Color* value = (app::Color*)(ptr);

		if (tem::PtrInRange(value) == true)
			return value;

		return nullptr;
	}

	app::Rect* tem::FieldHelper::GetFieldRect(std::uintptr_t ptr, std::string Namespace, std::string name, std::string fieldName)
	{
		app::Rect* value = (app::Rect*)(ptr);

		if (tem::PtrInRange(value) == true)
			return value;

		return nullptr;
	}

	float tem::FieldHelper::GetFieldFloat(std::uintptr_t ptr, std::string Namespace, std::string name, std::string fieldName)
	{
		float* value = (float*)(ptr);

		if (tem::PtrInRange(ptr) == true && tem::PtrInRange(value) == true && *value > FLT_TRUE_MIN && *value < FLT_MAX)
			return *value;

		return -1.0f;
	}

	app::Quaternion* tem::FieldHelper::GetFieldQuaternion(std::uintptr_t ptr, std::string Namespace, std::string name, std::string fieldName)
	{
		app::Quaternion* value = (app::Quaternion*)(ptr);

		if (tem::PtrInRange(value) == true)
			return value;

		return nullptr;
	}

	int tem::FieldHelper::GetFieldInt(std::uintptr_t ptr, std::string Namespace, std::string name, std::string fieldName)
	{
		int* value = (int*)(ptr);

		if (tem::PtrInRange(ptr) == true && tem::PtrInRange(value) == true && *value > INT_MIN && *value < INT_MAX)
			return *value;

		return -1;
	}

	app::Vector2* tem::FieldHelper::GetFieldVector2(std::uintptr_t ptr, std::string Namespace, std::string name, std::string fieldName)
	{
		app::Vector2* value = (app::Vector2*)(ptr);

		if (tem::PtrInRange(value) == true)
			return value;

		return nullptr;
	}

	std::string tem::FieldHelper::GetFieldEnum(std::uintptr_t ptr, std::string Namespace, std::string name, std::string fieldName, app::Type* enumType)
	{
		uint64_t* value = (uint64_t*)(ptr);

		if (tem::PtrInRange(value) == true)
		{
			app::Object* object = app::Enum_ToObject_8(enumType, *value, (*app::Enum_ToObject_8__MethodInfo));

			if (object == nullptr)
				return "NULL";

			app::String* enumValue = app::Enum_GetName(enumType, object, (*app::Enum_GetName__MethodInfo));

			if (enumValue == nullptr)
				return "NULL";

			return il2cppi_to_string(enumValue);
		}

		return "NULL";
	}

	app::Bounds* tem::FieldHelper::GetFieldBounds(std::uintptr_t ptr, std::string Namespace, std::string name, std::string fieldName)
	{
		app::Bounds* value = (app::Bounds*)(ptr);

		if (tem::PtrInRange(value) == true)
			return value;

		return nullptr;
	}

	std::string tem::FieldHelper::GetType(std::uintptr_t ptr, std::string Namespace, std::string name, std::string fieldName)
	{
		app::Type* value = (app::Type*)(ptr);

		if (tem::PtrInRange(value) == true)
			return value->klass->_0.name;

		return "NULL";
	}

	app::Matrix4x4* tem::FieldHelper::GetMatrix4x4(std::uintptr_t ptr, std::string Namespace, std::string name, std::string fieldName)
	{
		app::Matrix4x4* value = (app::Matrix4x4*)(ptr);

		if (tem::PtrInRange(value) == true)
			return value;

		return nullptr;
	}
}