#pragma once
class SceneObject
{
public:
	std::string Name;
	std::string ParentName;
	std::string ClassName;
    std::vector<std::string> SceneComponents;

    bool operator==(const SceneObject& other) const
    {
        return (Name == other.Name
            && ParentName == other.ParentName
            && ClassName == other.ClassName);
    }
};

class SceneHierarchy
{
public:
    SceneObject Object;
    std::vector<SceneHierarchy> SceneChildren;

    std::string ToString();
};

class SceneList
{
public:
	app::Type* ComponentType = nullptr;

    SceneHierarchy GetSceneStructureFromGameObject(app::GameObject* object);
    SceneHierarchy GetSceneStructureFromGameObjectNested(app::GameObject* object);
    app::GameObject* GetGameObjectFromNames(std::string parentName, std::string objectName, app::GameObject* root);
    app::GameObject* GetGameObjectFromHierarchyIndex(app::GameObject* object, std::string hierarchy);
};

namespace std {

    template <>
    struct hash<SceneObject>
    {
        std::size_t operator()(const SceneObject& k) const
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