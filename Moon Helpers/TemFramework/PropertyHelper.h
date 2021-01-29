#pragma once

#ifndef _PROPERTYHELPER_H
#define _PROPERTYHELPER_H

#include "tem.h"

namespace tem {
    class ClassProperty
    {
    public:
        bool HasChanged = false;
        std::string Name = "";
        std::string Namespace = "";
        std::string ClassName = "";
        tem::VariableType ReturnType = tem::VariableType::Null;
        std::string PropertyValue = "";
        void* Parent = nullptr;

        ClassProperty();
        ClassProperty(PropertyInfo* Property);

        tem::ClassProperty* GetPropertyByName(std::string name);
        void GetPropertyValue(void* object, PropertyInfo* Property);
        static Il2CppObject* GetPropertyObject(void* object, PropertyInfo* Property);
        void SetPropertyValue(void* object, std::string Namespace, std::string name, std::string fieldPropName, std::string value, ClassProperty* Property);
        std::string ToJsonString();
        std::string SaveJsonProperty();
    };

    class PropertyHelper
    {
    public:
        static Il2CppObject* InvokePropertyMethod(void* object, PropertyInfo* Property);
        static void InvokePropertySetterMethod(void* object, PropertyInfo* Property, std::string value);
        static std::vector<PropertyInfo*> GetPropertiesFromClass(std::string Namespace, std::string name);
        static std::vector<ClassProperty> FillProperties(void* object, std::vector<PropertyInfo*> properties);
    };
}
#endif