#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <future>
#include <unordered_map>

#include "StringUtils.h"
#include "ManagerDef.h"

#include "ObjectCreator.h"

app::Scene tem::ObjectCreator::temUnityScene1;
app::GameObject* tem::ObjectCreator::temScene1 = nullptr;
app::SceneMetaData* tem::ObjectCreator::temScene1MetaData = nullptr;
app::RuntimeSceneMetaData* tem::ObjectCreator::temScene1RuntimeMetaData = nullptr;
app::SceneRoot* tem::ObjectCreator::temScene1Root = nullptr;
app::SceneManagerScene* tem::ObjectCreator::temScene1ManagerScene = nullptr;
app::SceneSettingsComponent* tem::ObjectCreator::SceneCopySettings = nullptr;

app::GameObject* tem::ObjectCreator::CreateClone(app::GameObject* object)
{
	app::GameObject* gameObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
	app::GameObject__ctor(gameObject, string_new("ClonedObject"), NULL);

	app::Type* ComponentType = GetType("UnityEngine", "Component");
	if (ComponentType->klass->_0.name != "Component")
	{
		ComponentType = GetTypeFromClass((Il2CppClass*)(*app::Component_1__TypeInfo));
	}

	app::MeshRenderer* cloneRenderer = (app::MeshRenderer*)GetComponentByTypeInChildren(object, "UnityEngine", "MeshRenderer");
	app::MeshFilter* cloneFilter = (app::MeshFilter*)GetComponentByTypeInChildren(object, "UnityEngine", "MeshFilter");

	app::Type* meshRendererType = GetType("UnityEngine", "MeshRenderer");
	app::Type* meshFilterType = GetType("UnityEngine", "MeshFilter");

	app::MeshRenderer* meshRenderer = (app::MeshRenderer*)app::GameObject_AddComponent(gameObject, meshRendererType, NULL);
	app::Material* meshMat = app::Renderer_GetMaterial((app::Renderer*)cloneRenderer, NULL);

	app::Material* newMaterial = (app::Material*)il2cpp_object_new((Il2CppClass*)(*app::Material__TypeInfo));
	app::Material__ctor_1(newMaterial, meshMat, NULL);
	app::Material_CopyPropertiesFromMaterial(newMaterial, meshMat, NULL);

	app::Renderer_SetMaterial((app::Renderer*)meshRenderer, newMaterial, NULL);

	app::MeshFilter* meshFilter = (app::MeshFilter*)app::GameObject_AddComponent(gameObject, meshFilterType, NULL);
	app::Mesh* mesh = app::MeshFilter_get_mesh(cloneFilter, NULL);
	app::MeshFilter_set_mesh(meshFilter, mesh, NULL);

	app::GameObject_set_active(gameObject, true, NULL);

	TransformSetPosition(gameObject, TransformGetPosition(object));
	TransformSetQuatRotation(gameObject, TransformGetEulerAngles(object));
	TransformSetScale(gameObject, TransformGetScale(object));

	return gameObject;
}