#pragma once

#ifndef _SCENESOBJECT_H
#define _SCENESOBJECT_H

#include "Adresses.h"

namespace tem {
	class SceneObject
	{
	public:
		bool IsCustomObject = false;
		bool HasChanged = false;
		std::string Name;
		std::string ParentName;
		std::uintptr_t Parent;
		std::string ClassName;
		std::vector<tem::Component> SceneComponents;
		int HierarchyIndex;
		std::vector<int> SceneIndexHierarchy;
		std::vector<tem::ClassField> Fields;
		std::vector<tem::ClassProperty> Properties;
		std::vector<std::string> ClonedSceneNameHierarchy;
		//tem::TreeItem TreeItem;

		bool HasComponent(std::string className);

		SceneObject();
		SceneObject(bool isCustomObject, bool hasChanged, std::string name, std::string parentName, std::uintptr_t parent,
			std::string className, std::vector<tem::Component> sceneComponents, std::vector<int> sceneIndexHierarchy, int hierarchyIndex);

		void GetObjectData();
		void GetObjectData(app::GameObject* object);
		void GetObjectDataGameObject(app::GameObject* object);
		void FieldPropertyHasChanged(app::GameObject* object, std::string componentName, std::string fieldPropertyName, std::string value);
		void SetComponentDataField(std::string componentName, tem::ClassField field);
		void SetComponentDataProperty(std::string componentName, tem::ClassProperty prop);
		void SetComponentData(std::string componentName, std::string fieldPropName, std::string value, bool isField);
		void SetComponentData(app::GameObject* object, std::string componentName, std::string fieldPropPath, std::string fieldPropName, std::string value, bool isField);
		tem::ClassProperty* FindProperty(std::string name, std::vector<tem::ClassProperty> &properties);
		tem::ClassField* FindField(std::string name, std::vector<tem::ClassField> &fields);

		bool operator==(const SceneObject& other) const
		{
			return (Name == other.Name
				&& ParentName == other.ParentName
				&& ClassName == other.ClassName);
		}
	};
}

namespace std {

	template <>
	struct hash<tem::SceneObject>
	{
		std::size_t operator()(const tem::SceneObject& k) const
		{
			using std::size_t;
			using std::hash;
			using std::string;

			// Compute individual hash values for first,
			// second and third and combine them using XOR
			// and bit shifting:

			return ((hash<string>()(k.Name)
				^ (hash<string>()(k.ParentName) << 1)) >> 1)
				^ (hash<string>()(k.ClassName) << 1);
		}
	};

}

#endif