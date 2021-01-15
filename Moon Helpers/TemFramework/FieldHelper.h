#pragma once

#ifndef _FIELDHELPER_H
#define _FIELDHELPER_H

#include "tem.h"

namespace tem {
    class ClassField
    {
    public:
        std::string Name;
        int TypeDefIndex;
        int Offset;
        bool IsStatic = false;
        bool HasChanged = false;
        tem::VariableType Type;
        std::string FieldValue;
        std::vector<ClassField> Fields;
        std::string ParentName;
        std::string Namespace;
        std::string ClassName;

        static std::vector<std::uintptr_t> NestedPointers;

        ClassField();
        ClassField(FieldInfo* field);

        void GetFieldValue(std::uintptr_t fieldPtr, FieldInfo* field);
        tem::ClassField* GetFieldByName(std::string name);
        void SetGetFieldValue(int klassIndex, std::uintptr_t ptr, std::string Namespace, std::string ClassName, std::string name);
        void SetFieldValue(std::uintptr_t objectPtr, std::string Namespace, std::string name, std::string fieldPropName, std::string value, ClassField* Field);
        void SetNestedFieldValue(std::uintptr_t objectPtr, std::string Namespace, std::string name, std::vector<std::string> fieldHierarchy, std::string value);
        ClassField* GetNestedField(std::vector<std::string> &fieldName);
        std::string ToJsonString();
        std::string SaveJsonField();
    };

    class FieldHelper
    {
    public:
        static FieldInfo* GetNestedFieldFromField(std::uintptr_t& fieldPtr, FieldInfo* Field, std::vector<std::string>& fieldHierarchy);
        static std::vector<FieldInfo*> GetFieldsFromClass(Il2CppClass* Class);
        static std::vector<FieldInfo*> GetFieldsFromClass(std::string Namespace, std::string name);
        static std::vector<ClassField> FillFields(void* object, std::vector<FieldInfo*> fields);
        static FieldInfo* GetFieldByName(Il2CppObject* object, std::string Namespace, std::string name, std::string fieldName);
        static bool GetFieldBool(std::uintptr_t ptr, std::string Namespace, std::string name, std::string fieldName);
        static char GetFieldChar(std::uintptr_t ptr, std::string Namespace, std::string name, std::string fieldName);
        static std::string GetFieldString(std::uintptr_t ptr, std::string Namespace, std::string name, std::string fieldName);
        static std::uintptr_t GetFieldPtr(std::uintptr_t ptr, std::string Namespace, std::string name, std::string fieldName);
        static app::Vector3* GetFieldVector3(std::uintptr_t ptr, std::string Namespace, std::string name, std::string fieldName);
        static app::Vector4* GetFieldVector4(std::uintptr_t ptr, std::string Namespace, std::string name, std::string fieldName);
        static app::Color* GetFieldColor(std::uintptr_t ptr, std::string Namespace, std::string name, std::string fieldName);
        static app::Rect* GetFieldRect(std::uintptr_t ptr, std::string Namespace, std::string name, std::string fieldName);
        static float GetFieldFloat(std::uintptr_t ptr, std::string Namespace, std::string name, std::string fieldName);
        static app::Quaternion* GetFieldQuaternion(std::uintptr_t ptr, std::string Namespace, std::string name, std::string fieldName);
        static int GetFieldInt(std::uintptr_t ptr, std::string Namespace, std::string name, std::string fieldName);
        static app::Vector2* GetFieldVector2(std::uintptr_t ptr, std::string Namespace, std::string name, std::string fieldName);
        static std::string GetFieldEnum(std::uintptr_t ptr, std::string Namespace, std::string name, std::string fieldName, app::Type* enumType);
        static app::Bounds* GetFieldBounds(std::uintptr_t ptr, std::string Namespace, std::string name, std::string fieldName);
        static void InvokeFieldSetterMethod(std::uintptr_t ptr, FieldInfo* field, std::string value);
    };
}
#endif