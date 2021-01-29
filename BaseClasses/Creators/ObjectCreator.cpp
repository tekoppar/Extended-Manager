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

void tem::ObjectCreator::CreateScene(std::string name, tem::Vector3 position, tem::Vector2 size, tem::Rect loadingRect)
{
	app::GameObject* gameObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
	app::GameObject__ctor(gameObject, string_new(name.data()), NULL);
	MDV::GCHandles.push_back(il2cpp_gchandle_new((Il2CppObject*)gameObject, true));
	app::Object_1_DontDestroyOnLoad((app::Object_1*)gameObject, NULL);
	TransformSetPosition(gameObject, position.ToMoon());


	tem::Rect rect = tem::Rect(position.X, position.Y, size.x, size.y);
	rect.Y -= rect.Height;
	//loadingRect.Y -= rect.Height;
	position.Y -= rect.Height;

	temScene1 = gameObject;
	app::Transform* gameObjectT = app::GameObject_get_transform(temScene1, NULL);

	app::GameObject* sceneBoundariesObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
	app::GameObject__ctor(sceneBoundariesObject, string_new("sceneBoundaries"), NULL);
	//MDV::GCHandles.push_back(il2cpp_gchandle_new((Il2CppObject*)sceneBoundariesObject, true));
	app::Object_1_DontDestroyOnLoad((app::Object_1*)sceneBoundariesObject, NULL);
	app::GameObject* sceneBoundaryObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
	app::GameObject__ctor(sceneBoundaryObject, string_new("sceneBoundary"), NULL);
	//MDV::GCHandles.push_back(il2cpp_gchandle_new((Il2CppObject*)sceneBoundaryObject, true));
	app::Object_1_DontDestroyOnLoad((app::Object_1*)sceneBoundaryObject, NULL);

	auto Il2ClassSceneBoundary = GetClass("", "SceneBoundary");
	app::Type* sceneBoundaryType = GetTypeFromClass(Il2ClassSceneBoundary);
	app::SceneBoundary* sceneBoundary = (app::SceneBoundary*)app::GameObject_AddComponent(sceneBoundaryObject, sceneBoundaryType, NULL);
	app::SceneBoundary__ctor(sceneBoundary, NULL);
	app::Object_1_DontDestroyOnLoad((app::Object_1*)sceneBoundary, NULL);
	//sceneBoundary->fields._.m_previousPosition = position.ToMoon();
	//sceneBoundary->fields._.m_previousScale = tem::Vector3(rect.Width, rect.Height, 0.0f).ToMoon();

	TransformSetParent(sceneBoundaryObject, sceneBoundariesObject);
	TransformSetParent(sceneBoundariesObject, temScene1);
	TransformSetPosition(sceneBoundariesObject, position);
	TransformSetLocalPosition(sceneBoundariesObject, tem::Vector3(0.0f, 0.0f, 0.0f));
	TransformSetPosition(sceneBoundaryObject, tem::Vector3(0.0f, 0.0f, 0.0f));
	TransformSetScale(sceneBoundaryObject, tem::Vector3(rect.Width, rect.Height, 0.0f));


	app::GameObject* scenePaddingBoundariesObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
	app::GameObject__ctor(scenePaddingBoundariesObject, string_new("scenePaddingBoundaries"), NULL);
	//MDV::GCHandles.push_back(il2cpp_gchandle_new((Il2CppObject*)scenePaddingBoundariesObject, true));
	app::Object_1_DontDestroyOnLoad((app::Object_1*)scenePaddingBoundariesObject, NULL);
	app::GameObject* scenePaddingBoundaryObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
	app::GameObject__ctor(scenePaddingBoundaryObject, string_new("scenePaddingBoundary"), NULL);
	//MDV::GCHandles.push_back(il2cpp_gchandle_new((Il2CppObject*)scenePaddingBoundaryObject, true));
	app::Object_1_DontDestroyOnLoad((app::Object_1*)scenePaddingBoundaryObject, NULL);

	auto Il2ClassScenePaddingBoundary = GetClass("", "ScenePaddingBoundary");
	app::Type* scenePaddingBoundaryType = GetTypeFromClass(Il2ClassScenePaddingBoundary);
	app::ScenePaddingBoundary* scenePaddingBoundary = (app::ScenePaddingBoundary*)app::GameObject_AddComponent(scenePaddingBoundaryObject, scenePaddingBoundaryType, NULL);
	app::ScenePaddingBoundary__ctor(scenePaddingBoundary, NULL);
	app::Object_1_DontDestroyOnLoad((app::Object_1*)scenePaddingBoundary, NULL);
	//scenePaddingBoundary->fields._.m_previousPosition = position.ToMoon();
	//scenePaddingBoundary->fields._.m_previousScale = tem::Vector3(rect.Width, rect.Height, 0.0f).ToMoon();

	TransformSetParent(scenePaddingBoundaryObject, scenePaddingBoundariesObject);
	TransformSetParent(scenePaddingBoundariesObject, temScene1);
	TransformSetPosition(scenePaddingBoundariesObject, position);
	TransformSetLocalPosition(scenePaddingBoundariesObject, tem::Vector3(0.0f, 0.0f, 0.0f));
	TransformSetScale(scenePaddingBoundaryObject, tem::Vector3(rect.Width, rect.Height, 0.0f));


	app::GameObject* scrollLocksObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
	app::GameObject__ctor(scrollLocksObject, string_new("scrollLocks"), NULL);
	//MDV::GCHandles.push_back(il2cpp_gchandle_new((Il2CppObject*)scrollLocksObject, true));
	app::Object_1_DontDestroyOnLoad((app::Object_1*)scrollLocksObject, NULL);
	app::GameObject* cameraScrollLockObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
	app::GameObject__ctor(cameraScrollLockObject, string_new("scrollLock"), NULL);
	//MDV::GCHandles.push_back(il2cpp_gchandle_new((Il2CppObject*)cameraScrollLockObject, true));
	app::Object_1_DontDestroyOnLoad((app::Object_1*)cameraScrollLockObject, NULL);

	auto Il2ClassCameraScrollLock = GetClass("", "CameraScrollLock");
	app::Type* cameraScrollLockType = GetTypeFromClass(Il2ClassCameraScrollLock);
	app::CameraScrollLock* cameraScrollLock = (app::CameraScrollLock*)app::GameObject_AddComponent(cameraScrollLockObject, cameraScrollLockType, NULL);
	app::CameraScrollLock__ctor(cameraScrollLock, NULL);
	app::Object_1_DontDestroyOnLoad((app::Object_1*)cameraScrollLock, NULL);
	cameraScrollLock->fields._ScrollCenter_k__BackingField = tem::Vector3(rect.X + (rect.Width / 2), rect.Y + rect.Height, 0.0f).ToMoon();
	cameraScrollLock->fields.m_boundingRect = tem::Rect(rect.X, rect.Y, rect.Width, 1.0f).ToMoon();
	cameraScrollLock->fields.m_boundingRectCalculated = true;

	TransformSetParent(cameraScrollLockObject, scrollLocksObject);
	TransformSetParent(scrollLocksObject, temScene1);
	TransformSetPosition(scrollLocksObject, position);
	TransformSetLocalPosition(scrollLocksObject, tem::Vector3(0.0f, 0.0f, 0.0f));
	TransformSetScale(cameraScrollLockObject, tem::Vector3(rect.Width, rect.Height, 0.0f));


	app::Texture2D* debugTexture = (app::Texture2D*)il2cpp_object_new((Il2CppClass*)(*app::Texture2D__TypeInfo));
	app::Texture2D__ctor_3(debugTexture, 1, 1, app::TextureFormat__Enum::TextureFormat__Enum_RGBA32, false, false, NULL);
	app::Texture_set_wrapMode((app::Texture*)debugTexture, app::TextureWrapMode__Enum::TextureWrapMode__Enum_Repeat, NULL);
	app::Texture_set_filterMode((app::Texture*)debugTexture, app::FilterMode__Enum::FilterMode__Enum_Point, NULL);
	app::Material* debugMaterial = CreateNewMaterial("Hidden/UberShader/4B897D76B847170D884884FBA5CEBC13");

	FillPixels(debugTexture, 1, 1, GraphColors::Pink);
	app::Texture2D_Apply_1(debugTexture, true, NULL);

	FillPixels(debugTexture, 1, 1, GraphColors::Pink);
	app::Texture2D_Apply_1(debugTexture, true, NULL);

	app::String* TextureName = string_new("_MainTex");
	app::String* TextureName1 = string_new("_Color");

	app::Material_SetColor(debugMaterial, TextureName1, GraphColors::Grey, NULL);
	app::Material_SetTexture(debugMaterial, TextureName, (app::Texture*)debugTexture, NULL);
	app::Material_set_mainTexture(debugMaterial, (app::Texture*)debugTexture, NULL);

	app::GameObject* gameObject1 = app::GameObject_CreatePrimitive(app::PrimitiveType__Enum_Cube, NULL);
	app::Object_1_set_name((app::Object_1*)gameObject1, string_new("art"), NULL);

	app::MeshRenderer* meshRenderer = (app::MeshRenderer*)GetComponentByType(gameObject1, "UnityEngine", "MeshRenderer");
	app::Renderer_SetMaterial((app::Renderer*)meshRenderer, debugMaterial, NULL);
	app::Renderer_set_sortingOrder((app::Renderer*)meshRenderer, 30842, NULL);
	app::Renderer_set_renderingLayerMask((app::Renderer*)meshRenderer, 4102, NULL); //xxx0 nothing, xxx1 transparent, xxx2 full color, xxx3 full color shades everything inside
	app::Renderer_set_moonOffsetZ((app::Renderer*)meshRenderer, 0.0f, NULL);
	app::Material_set_renderQueue(debugMaterial, 2000, NULL);

	TransformSetParent(gameObject1, temScene1);
	TransformSetPosition(gameObject1, position.ToMoon());
	TransformSetLocalPosition(gameObject1, tem::Vector3(0.0f, 0.0f, 0.0f));
	TransformSetScale(gameObject1, tem::Vector3(1.0f, 1.0f, 1.0f));

	app::GameObject_SetActive(temScene1, false, NULL);
	app::MoonGuid* sceneGuid = app::GuidOwner_GenerateGUID(NULL);
	app::String* moonGuidString = app::MoonGuid_get_GUIDString(sceneGuid, NULL);

	auto Il2ClassSceneMetaData = GetClass("", "SceneMetaData");
	app::Type* typeSceneMetaData = GetTypeFromClass((Il2CppClass*)Il2ClassSceneMetaData);
	temScene1MetaData = (app::SceneMetaData*)app::ScriptableObject_CreateInstance(typeSceneMetaData, NULL);
	app::SceneMetaData__ctor(temScene1MetaData, NULL);
	app::Object_1_DontDestroyOnLoad((app::Object_1*)temScene1MetaData, NULL);
	temScene1MetaData->fields.SceneMoonGuid = sceneGuid;
	temScene1MetaData->fields.CanTimeSlice = true;

	auto Il2ClassRuntimeSceneMetaData = GetClass("", "RuntimeSceneMetaData");
	temScene1RuntimeMetaData = (app::RuntimeSceneMetaData*)il2cpp_object_new((Il2CppClass*)Il2ClassRuntimeSceneMetaData);
	app::RuntimeSceneMetaData__ctor_1(temScene1RuntimeMetaData, temScene1MetaData, NULL);
	app::Object_1_DontDestroyOnLoad((app::Object_1*)temScene1RuntimeMetaData, NULL);
	temScene1RuntimeMetaData->fields.SceneMoonGuid = sceneGuid;
	temScene1RuntimeMetaData->fields.Scene = string_new(name.data());
	temScene1RuntimeMetaData->fields.CanTimeSlice = true;
	temScene1RuntimeMetaData->fields.DependantScene = false;
	temScene1RuntimeMetaData->fields.SceneInCurrentFrame = true;
	temScene1RuntimeMetaData->fields.m_doneTotal = true;


	app::ScenesManager* scenesManager = (*app::Scenes__TypeInfo)->static_fields->Manager;
	//temScene1MetaData->fields.LoadingCondition = temScene1RuntimeMetaData->fields.LoadingCondition = scenesManager->fields.ActiveScenes->fields._items->vector[0]->fields.MetaData->fields.LoadingCondition;
	app::List_1_UnityEngine_Rect_* sceneLoadingBounds = (app::List_1_UnityEngine_Rect_*)il2cpp_object_new((Il2CppClass*)(*app::List_1_UnityEngine_Rect___TypeInfo));
	app::Type* rectArrType = GetType("UnityEngine", "Rect");
	app::Rect__Array* rectArr1 = (app::Rect__Array*)app::Array_CreateInstance_1(rectArrType, 1, NULL);
	sceneLoadingBounds->fields._items = rectArr1;
	app::Rect tempRect1 = loadingRect.ToMoon();
	app::List_1_UnityEngine_Rect__Insert(sceneLoadingBounds, 0, tempRect1, NULL);
	temScene1MetaData->fields.SceneLoadingBoundaries = sceneLoadingBounds;

	app::List_1_UnityEngine_Rect_* sceneLoadingBounds1 = (app::List_1_UnityEngine_Rect_*)il2cpp_object_new((Il2CppClass*)(*app::List_1_UnityEngine_Rect___TypeInfo));
	app::Rect__Array* rectArr11 = (app::Rect__Array*)app::Array_CreateInstance_1(rectArrType, 1, NULL);
	sceneLoadingBounds1->fields._items = rectArr11;
	app::List_1_UnityEngine_Rect__Insert(sceneLoadingBounds1, 0, loadingRect.ToMoon(), NULL);
	//temScene1RuntimeMetaData->fields.SceneLoadingBoundaries = sceneLoadingBounds1;

	app::List_1_UnityEngine_Rect_* sceneBounds = (app::List_1_UnityEngine_Rect_*)il2cpp_object_new((Il2CppClass*)(*app::List_1_UnityEngine_Rect___TypeInfo));
	app::Rect__Array* rectArr2 = (app::Rect__Array*)app::Array_CreateInstance_1(rectArrType, 1, NULL);
	sceneBounds->fields._items = rectArr2;
	app::List_1_UnityEngine_Rect__Insert(sceneBounds, 0, rect.ToMoon(), NULL);
	temScene1MetaData->fields.SceneBoundaries = sceneBounds;

	app::List_1_UnityEngine_Rect_* sceneBounds1 = (app::List_1_UnityEngine_Rect_*)il2cpp_object_new((Il2CppClass*)(*app::List_1_UnityEngine_Rect___TypeInfo));
	app::Rect__Array* rectArr22 = (app::Rect__Array*)app::Array_CreateInstance_1(rectArrType, 1, NULL);
	sceneBounds1->fields._items = rectArr22;
	app::List_1_UnityEngine_Rect__Insert(sceneBounds1, 0, rect.ToMoon(), NULL);
	temScene1RuntimeMetaData->fields.SceneBoundaries = sceneBounds1;

	app::List_1_UnityEngine_Rect_* scenePaddingBounds = (app::List_1_UnityEngine_Rect_*)il2cpp_object_new((Il2CppClass*)(*app::List_1_UnityEngine_Rect___TypeInfo));
	app::Rect__Array* rectArr3 = (app::Rect__Array*)app::Array_CreateInstance_1(rectArrType, 1, NULL);
	scenePaddingBounds->fields._items = rectArr3;
	app::List_1_UnityEngine_Rect__Insert(scenePaddingBounds, 0, rect.ToMoon(), NULL);
	temScene1MetaData->fields.ScenePaddingBoundaries = scenePaddingBounds;

	app::List_1_UnityEngine_Rect_* scenePaddingBounds1 = (app::List_1_UnityEngine_Rect_*)il2cpp_object_new((Il2CppClass*)(*app::List_1_UnityEngine_Rect___TypeInfo));
	app::Rect__Array* rectArr33 = (app::Rect__Array*)app::Array_CreateInstance_1(rectArrType, 1, NULL);
	scenePaddingBounds1->fields._items = rectArr33;
	app::List_1_UnityEngine_Rect__Insert(scenePaddingBounds1, 0, rect.ToMoon(), NULL);
	temScene1RuntimeMetaData->fields.ScenePaddingBoundaries = scenePaddingBounds1;

	temScene1RuntimeMetaData->fields.m_totalRect = rect.ToMoon();

	app::Type* singleArrType = GetTypeFromClass((Il2CppClass*)(*app::Single__TypeInfo));
	app::Single__Array* singleArr1 = (app::Single__Array*)app::Array_CreateInstance_1(singleArrType, 1, NULL);
	singleArr1->vector[0] = 1.0f;
	temScene1MetaData->fields.ScenePaddingWideScreenExpansion->fields._items = singleArr1;
	temScene1MetaData->fields.ScenePaddingWideScreenExpansion->fields._size = 1;
	temScene1RuntimeMetaData->fields.ScenePaddingWideScreenExpansion->fields._items = singleArr1;
	temScene1RuntimeMetaData->fields.ScenePaddingWideScreenExpansion->fields._size = 1;

	app::List_1_SceneMetaData_* includedScenes = (app::List_1_SceneMetaData_*)il2cpp_object_new((Il2CppClass*)(*app::List_1_SceneMetaData___TypeInfo));
	app::List_1_SceneMetaData___ctor(includedScenes, (*app::List_1_SceneMetaData___ctor__MethodInfo));
	temScene1MetaData->fields.IncludedScenes = includedScenes;

	temScene1MetaData->fields.InitialValuesBlindForest = scenesManager->fields.ActiveScenes->fields._items->vector[0]->fields.SceneRoot->fields.MetaData->fields.InitialValuesBlindForest;
	temScene1MetaData->fields.InitialValuesWisp = scenesManager->fields.ActiveScenes->fields._items->vector[0]->fields.SceneRoot->fields.MetaData->fields.InitialValuesWisp;
	temScene1MetaData->fields.RootPosition = (position + tem::Vector3(345.89f, 238.96f, 0.0f)).ToMoon();
	temScene1MetaData->fields.DependantScene = false;

	app::Dictionary_2_MoonGuid_NearbySceneData_* nearbyScenes = (app::Dictionary_2_MoonGuid_NearbySceneData_*)il2cpp_object_new((Il2CppClass*)(*app::Dictionary_2_MoonGuid_NearbySceneData___TypeInfo));
	app::Dictionary_2_MoonGuid_NearbySceneData___ctor(nearbyScenes, 10, (*app::Dictionary_2_MoonGuid_NearbySceneData___ctor__MethodInfo));
	app::List_1_SceneMetaData_* connectedScenes = (app::List_1_SceneMetaData_*)il2cpp_object_new((Il2CppClass*)(*app::List_1_SceneMetaData___TypeInfo));
	app::List_1_SceneMetaData___ctor(connectedScenes, (*app::List_1_SceneMetaData___ctor__MethodInfo));

	std::vector<TemSceneNodeData> nearbyScenesNodes = TemSceneHelper::GetNearbyScenes(position);
	nearbyScenes = TemSceneHelper::TemSceneNodeDataToDictionary(nearbyScenesNodes);
	temScene1RuntimeMetaData->fields.m_nearbyReachableScenes = nearbyScenes;
	connectedScenes->fields._items->vector[0] = app::ScenesManager_GetSceneMetaDataFromRuntimeMetaData(scenesManager, app::ScenesManager_FindRuntimeSceneMetaData(scenesManager, nearbyScenesNodes[0].SceneGuid, NULL), NULL);
	temScene1MetaData->fields.ConnectedScenes = connectedScenes;

	auto Il2ClassSceneRoot = GetClass("", "SceneRoot");
	app::Type* rootType = GetTypeFromClass(Il2ClassSceneRoot);
	temScene1Root = (app::SceneRoot*)app::GameObject_AddComponent(temScene1, rootType, NULL);
	app::Object_1_DontDestroyOnLoad((app::Object_1*)temScene1Root, NULL);
	MDV::GCHandles.push_back(il2cpp_gchandle_new((Il2CppObject*)temScene1Root, true));
	temScene1RuntimeMetaData->fields.MapPositionOverride = temScene1MetaData->fields.RootPosition;
	temScene1RuntimeMetaData->fields.PlaceholderPosition = position.ToVector2();


	app::Type* boolArrType = GetTypeFromClass((Il2CppClass*)(*app::Boolean__TypeInfo));
	app::Boolean__Array* boolArr1 = (app::Boolean__Array*)app::Array_CreateInstance_1(boolArrType, 1, NULL);
	temScene1RuntimeMetaData->fields.m_cachedIsInsideSceneBounds = boolArr1;
	app::Boolean__Array* boolArr2 = (app::Boolean__Array*)app::Array_CreateInstance_1(boolArrType, 1, NULL);
	temScene1RuntimeMetaData->fields.m_cachedIsInsideScenePaddingBounds = boolArr2;
	app::Boolean__Array* boolArr3 = (app::Boolean__Array*)app::Array_CreateInstance_1(boolArrType, 1, NULL);
	temScene1RuntimeMetaData->fields.m_IsInsideSceneBoundsIsCached = boolArr3;
	app::Boolean__Array* boolArr4 = (app::Boolean__Array*)app::Array_CreateInstance_1(boolArrType, 1, NULL);
	temScene1RuntimeMetaData->fields.m_IsInsideScenePaddingBoundsIsCached = boolArr4;


	app::TimeSlicedActivationTask* sceneActivation = (app::TimeSlicedActivationTask*)il2cpp_object_new((Il2CppClass*)(*app::TimeSlicedActivationTask__TypeInfo));

	app::List_1_UnityEngine_GameObject_* gameObjectsToEnable = (app::List_1_UnityEngine_GameObject_*)il2cpp_object_new((Il2CppClass*)(*app::List_1_UnityEngine_GameObject___TypeInfo));
	app::List_1_UnityEngine_GameObject___ctor(gameObjectsToEnable, 2, (*app::List_1_UnityEngine_GameObject___ctor__MethodInfo));
	app::List_1_UnityEngine_GameObject__Add(gameObjectsToEnable, gameObject, (*app::List_1_UnityEngine_GameObject__Add__MethodInfo));
	app::List_1_UnityEngine_GameObject__Add(gameObjectsToEnable, gameObject1, (*app::List_1_UnityEngine_GameObject__Add__MethodInfo));

	app::List_1_UnityEngine_Component_* preEnableObservers = (app::List_1_UnityEngine_Component_*)il2cpp_object_new((Il2CppClass*)(*app::List_1_UnityEngine_Component___TypeInfo));
	app::List_1_UnityEngine_Component___ctor_2(preEnableObservers, 0, (*app::List_1_UnityEngine_Component___ctor_2__MethodInfo));
	app::List_1_UnityEngine_Component_* postEnableObservers = (app::List_1_UnityEngine_Component_*)il2cpp_object_new((Il2CppClass*)(*app::List_1_UnityEngine_Component___TypeInfo));
	app::List_1_UnityEngine_Component___ctor_2(postEnableObservers, 0, (*app::List_1_UnityEngine_Component___ctor_2__MethodInfo));


	app::AnimationCurve* rCurve = (app::AnimationCurve*)il2cpp_object_new((Il2CppClass*)(*app::AnimationCurve__TypeInfo));
	app::AnimationCurve__ctor_1(rCurve, NULL);
	app::AnimationCurve_CopyFrom(rCurve, SceneCopySettings->fields.CameraSettings->fields.ColorCorrection->fields.Red, NULL);
	app::AnimationCurve* gCurve = (app::AnimationCurve*)il2cpp_object_new((Il2CppClass*)(*app::AnimationCurve__TypeInfo));
	app::AnimationCurve__ctor_1(gCurve, NULL);
	app::AnimationCurve_CopyFrom(gCurve, SceneCopySettings->fields.CameraSettings->fields.ColorCorrection->fields.Green, NULL);
	app::AnimationCurve* bCurve = (app::AnimationCurve*)il2cpp_object_new((Il2CppClass*)(*app::AnimationCurve__TypeInfo));
	app::AnimationCurve__ctor_1(bCurve, NULL);
	app::AnimationCurve_CopyFrom(bCurve, SceneCopySettings->fields.CameraSettings->fields.ColorCorrection->fields.Blue, NULL);


	auto Il2ClassColor = GetClass("UnityEngine", "Color");
	app::Type* colorArrType = GetTypeFromClass(Il2ClassColor);
	app::Color__Array* colorArr1 = (app::Color__Array*)app::Array_CreateInstance_1(colorArrType, 128, NULL);
	app::Color__Array* colorArr2 = (app::Color__Array*)app::Array_CreateInstance_1(colorArrType, 128, NULL);

	for (int i = 0; i < 128; i++)
	{
		colorArr1->vector[i] = tem::Vector4(0.0f).ToColor();
		colorArr2->vector[i] = tem::Vector4(0.5f).ToColor();
	}


	app::TimeSlicedActivationTask__ctor(sceneActivation, gameObjectsToEnable, preEnableObservers, postEnableObservers, false, true, gameObject, NULL, string_new(name.data()), NULL);
	sceneActivation->fields._.m_hasStarted = false;
	sceneActivation->fields._._AvailableBudget_k__BackingField = sceneActivation->fields._._CustomTimeBudget_k__BackingField = 1.0f;
	temScene1Root->fields.m_postEnabledObservers = postEnableObservers;
	temScene1Root->fields.m_preDisableObservers = postEnableObservers;

	auto Il2ClassSceneSettingsComponent = GetClass("", "SceneSettingsComponent");
	app::Type* sceneSettingsComponentType = GetTypeFromClass(Il2ClassSceneSettingsComponent);
	app::SceneSettingsComponent* sceneSettingsComponent = (app::SceneSettingsComponent*)app::GameObject_AddComponent(temScene1, sceneSettingsComponentType, NULL);
	app::SceneSettingsComponent__ctor(sceneSettingsComponent, NULL);
	sceneSettingsComponent->fields.LayeredRenderSettings = SceneCopySettings->fields.LayeredRenderSettings;

	auto Il2ClassCameraSettingsAsset = GetClass("", "CameraSettingsAsset");
	app::CameraSettingsAsset* cameraSettingsAsset = (app::CameraSettingsAsset*)il2cpp_object_new((Il2CppClass*)Il2ClassCameraSettingsAsset);
	app::CameraSettingsAsset__ctor(cameraSettingsAsset, NULL);
	cameraSettingsAsset->fields.ColorCorrection->fields.Red = rCurve;
	cameraSettingsAsset->fields.ColorCorrection->fields.Green = gCurve;
	cameraSettingsAsset->fields.ColorCorrection->fields.Blue = bCurve;
	cameraSettingsAsset->fields.Fog.a = -1.0f;
	cameraSettingsAsset->fields.Fog.g = cameraSettingsAsset->fields.Fog.r = cameraSettingsAsset->fields.Fog.b = -1.0f;
	cameraSettingsAsset->fields.BloomSettings->fields.BlurSpread = 0.0f;
	cameraSettingsAsset->fields.BloomSettings->fields.Intensity = 0.0f;
	cameraSettingsAsset->fields.TwirlSettings->fields.Strength = -1.0f;
	cameraSettingsAsset->fields.Vignetting->fields.Intensity = 0.0f;
	cameraSettingsAsset->fields.ColorVariationSettings->fields.IntensityMultiplier = 1.0f;
	cameraSettingsAsset->fields.Contrast->fields.Contrast = 1.25f;

	auto Il2ClassFogGradientController = GetClass("", "FogGradientController");
	app::FogGradientController* fogGradientController = (app::FogGradientController*)il2cpp_object_new((Il2CppClass*)Il2ClassFogGradientController);
	app::FogGradientController__ctor(fogGradientController, NULL);
	fogGradientController->fields.FogRange = -50000000.0f;
	fogGradientController->fields.FogGradient = nullptr;

	app::CameraSettings* cameraSettings = (app::CameraSettings*)il2cpp_object_new((Il2CppClass*)(*app::CameraSettings__TypeInfo));
	app::CameraSettings__ctor_1(cameraSettings, cameraSettingsAsset, fogGradientController, NULL);
	cameraSettings->fields.Fog = cameraSettingsAsset->fields.Fog;
	cameraSettings->fields.FogRange = 0.0f;
	cameraSettings->fields.ColorCorrection->fields.Red = rCurve;
	cameraSettings->fields.ColorCorrection->fields.Green = gCurve;
	cameraSettings->fields.ColorCorrection->fields.Blue = bCurve;
	cameraSettings->fields.FogGradient = colorArr1;
	cameraSettings->fields.MultiplyFogGradient = colorArr2;
	cameraSettings->fields.Contrast->fields.Contrast = 1.25f;

	auto Il2ClassDynamicLightsSettings = GetClass("", "DynamicLightsSettings");
	app::DynamicLightsSettings* dynamicLightsSettings = (app::DynamicLightsSettings*)il2cpp_object_new((Il2CppClass*)Il2ClassDynamicLightsSettings);
	app::DynamicLightsSettings__ctor(dynamicLightsSettings, NULL);

	auto Il2ClassMixerSnapshot = GetClass("", "MixerSnapshot");
	app::MixerSnapshot* mixerSnapshot = (app::MixerSnapshot*)il2cpp_object_new((Il2CppClass*)Il2ClassMixerSnapshot);
	app::MixerSnapshot__ctor(mixerSnapshot, NULL);

	auto Il2ClassMotionBlurController = GetClass("", "MotionBlurController");
	app::MotionBlurController* motionBlurController = (app::MotionBlurController*)il2cpp_object_new((Il2CppClass*)Il2ClassMotionBlurController);
	app::MotionBlurController__ctor(motionBlurController, NULL);

	auto Il2ClassDepthOfFieldController = GetClass("", "DepthOfFieldController");
	app::DepthOfFieldController* depthOfFieldController = (app::DepthOfFieldController*)il2cpp_object_new((Il2CppClass*)Il2ClassDepthOfFieldController);
	app::DepthOfFieldController__ctor(depthOfFieldController, NULL);
	depthOfFieldController->fields.DofDepthMax = 0.0f;
	depthOfFieldController->fields.DofDepthMin = 0.0f;

	auto Il2ClassSceneSettings = GetClass("", "SceneSettings");
	app::SceneSettings* sceneSettings = (app::SceneSettings*)il2cpp_object_new((Il2CppClass*)Il2ClassDepthOfFieldController);
	app::SceneSettings__ctor(sceneSettings, sceneSettingsComponent, NULL);
	sceneSettings->fields.CameraSettings = cameraSettings;

	sceneSettingsComponent->fields.CameraSettings = cameraSettingsAsset;
	sceneSettingsComponent->fields.m_sceneFogSettings = fogGradientController;
	sceneSettingsComponent->fields.DynamicLightsSettings = dynamicLightsSettings;
	sceneSettingsComponent->fields.DefaultMixerSnapshot = mixerSnapshot;
	sceneSettings->fields.MotionBlurController = sceneSettingsComponent->fields.MotionBlurController = motionBlurController;
	sceneSettings->fields.DepthOfFieldController = sceneSettingsComponent->fields.DepthOfFieldController = depthOfFieldController;
	sceneSettings->fields.CameraSettings->fields.Fog = cameraSettingsAsset->fields.Fog;
	sceneSettings->fields.CameraSettings->fields.FogRange = 0.0f;
	sceneSettingsComponent->fields.BlurredBackgroundDepth = sceneSettings->fields.BlurredBackgroundDepth = 0.0f;
	sceneSettingsComponent->fields.m_sceneSettings = sceneSettings;

	/*if (scenesManager->fields.ActiveScenes->fields._items->vector[0]->fields.SceneRoot->fields.m_sceneSettings != nullptr)
	{
		sceneSettingsComponent->fields.CameraSettings = scenesManager->fields.ActiveScenes->fields._items->vector[0]->fields.SceneRoot->fields.m_sceneSettings->fields.CameraSettings;
		sceneSettingsComponent->fields.CameraSettings->fields.BloomSettings = scenesManager->fields.ActiveScenes->fields._items->vector[0]->fields.SceneRoot->fields.m_sceneSettings->fields.CameraSettings->fields.BloomSettings;
		sceneSettingsComponent->fields.CameraSettings->fields.ColorCorrection = scenesManager->fields.ActiveScenes->fields._items->vector[0]->fields.SceneRoot->fields.m_sceneSettings->fields.CameraSettings->fields.ColorCorrection;
		sceneSettingsComponent->fields.CameraSettings->fields.EmissiveSettings = scenesManager->fields.ActiveScenes->fields._items->vector[0]->fields.SceneRoot->fields.m_sceneSettings->fields.CameraSettings->fields.EmissiveSettings;
		sceneSettingsComponent->fields.CameraSettings->fields.Vignetting = scenesManager->fields.ActiveScenes->fields._items->vector[0]->fields.SceneRoot->fields.m_sceneSettings->fields.CameraSettings->fields.Vignetting;
		sceneSettingsComponent->fields.CameraSettings->fields.TwirlSettings = scenesManager->fields.ActiveScenes->fields._items->vector[0]->fields.SceneRoot->fields.m_sceneSettings->fields.CameraSettings->fields.TwirlSettings;
		sceneSettingsComponent->fields.LayeredRenderSettings = scenesManager->fields.ActiveScenes->fields._items->vector[0]->fields.SceneRoot->fields.m_sceneSettings->fields.LayeredRenderSettings;
		sceneSettingsComponent->fields.m_cameraSetting = scenesManager->fields.ActiveScenes->fields._items->vector[0]->fields.SceneRoot->fields.m_sceneSettings->fields.m_cameraSetting;
		sceneSettingsComponent->fields.m_sceneSettings = scenesManager->fields.ActiveScenes->fields._items->vector[0]->fields.SceneRoot->fields.m_sceneSettings->fields.m_sceneSettings;
		sceneSettingsComponent->fields.m_transitionCameraSettings = scenesManager->fields.ActiveScenes->fields._items->vector[0]->fields.SceneRoot->fields.m_sceneSettings->fields.m_transitionCameraSettings;
		sceneSettingsComponent->fields.DynamicLightsSettings = scenesManager->fields.ActiveScenes->fields._items->vector[0]->fields.SceneRoot->fields.m_sceneSettings->fields.DynamicLightsSettings;
	}*/

	auto Il2ClassFirstExecutionOrder = GetClass("", "FirstExecutionOrder");
	app::Type* firstExecutionOrderType = GetTypeFromClass(Il2ClassFirstExecutionOrder);
	app::FirstExecutionOrder* firstExecutionOrder = (app::FirstExecutionOrder*)app::GameObject_AddComponent(temScene1, firstExecutionOrderType, NULL);
	app::FirstExecutionOrder__ctor(firstExecutionOrder, NULL);
	firstExecutionOrder->fields.metaData = temScene1MetaData;

	auto Il2ClassSLastExecutionOrder = GetClass("", "LastExecutionOrder");
	app::Type* lastExecutionOrderType = GetTypeFromClass(Il2ClassSLastExecutionOrder);
	app::LastExecutionOrder* lastExecutionOrder = (app::LastExecutionOrder*)app::GameObject_AddComponent(temScene1, lastExecutionOrderType, NULL);
	app::LastExecutionOrder__ctor(lastExecutionOrder, NULL);
	lastExecutionOrder->fields.sceneMetaData = temScene1MetaData;

	app::GameObject* gameObjectEnemies = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
	app::GameObject__ctor(gameObjectEnemies, string_new("enemies"), NULL);
	app::Object_1_DontDestroyOnLoad((app::Object_1*)gameObjectEnemies, NULL);
	TransformSetParent(gameObjectEnemies, temScene1);
	TransformSetPosition(gameObjectEnemies, position);

	app::GameObject* gameObjectEffects = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
	app::GameObject__ctor(gameObjectEffects, string_new("effects"), NULL);
	app::Object_1_DontDestroyOnLoad((app::Object_1*)gameObjectEffects, NULL);
	TransformSetParent(gameObjectEffects, temScene1);
	TransformSetPosition(gameObjectEffects, position);

	app::GameObject* gameObjectInteractives = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
	app::GameObject__ctor(gameObjectInteractives, string_new("interactives"), NULL);
	app::Object_1_DontDestroyOnLoad((app::Object_1*)gameObjectInteractives, NULL);
	TransformSetParent(gameObjectInteractives, temScene1);
	TransformSetPosition(gameObjectInteractives, position);

	app::GameObject* gameObjectCheckpoints = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
	app::GameObject__ctor(gameObjectCheckpoints, string_new("checkpoints"), NULL);
	app::Object_1_DontDestroyOnLoad((app::Object_1*)gameObjectCheckpoints, NULL);
	TransformSetParent(gameObjectCheckpoints, temScene1);
	TransformSetPosition(gameObjectCheckpoints, position);

	temUnityScene1 = app::SceneManager_CreateScene_1(string_new(name.data()), NULL);

	app::SceneRoot__ctor(temScene1Root, NULL);
	app::SceneRoot_StoreActiveObjectsFor(temScene1Root, app::GameObject_get_transform(gameObject1, NULL), NULL);
	temScene1Root->fields.MetaData = temScene1MetaData;
	temScene1Root->fields.m_sceneSettings = sceneSettingsComponent;
	temScene1Root->fields.m_highPriorityEnabling = false;
	temScene1Root->fields.m_state = app::SceneState__Enum::SceneState__Enum_Disabled;
	temScene1Root->fields.m_activationTask = sceneActivation;
	temScene1Root->fields.m_objectsToTimesliceDisable = gameObjectsToEnable;
	temScene1Root->fields.m_objectsToTimeSliceEnable = gameObjectsToEnable;
	temScene1Root->fields._IsVisible_k__BackingField = true;

	app::Type* componentArrType = GetTypeFromClass((Il2CppClass*)(*app::Component_1__TypeInfo));
	app::Component_1__Array* componentArr = (app::Component_1__Array*)app::Array_CreateInstance_1(componentArrType, 1, NULL);
	componentArr->vector[0] = (app::Component_1*)gameObjectT;
	temScene1Root->fields.m_frustumOptimizedObjects = componentArr;
	temScene1Root->fields._._._.m_cachedGameObject = temScene1;
	temScene1Root->fields._._._.m_cachedTransform = gameObjectT;

	/*app::List_1_UnityEngine_GameObject_* gameObjectsToEnable = (app::List_1_UnityEngine_GameObject_*)il2cpp_object_new((Il2CppClass*)(*app::List_1_UnityEngine_GameObject___TypeInfo));
	app::List_1_UnityEngine_GameObject___ctor(gameObjectsToEnable, 10, (*app::List_1_UnityEngine_GameObject___ctor__MethodInfo));
	temScene1Root->fields.m_objectsToTimeSliceEnable = gameObjectsToEnable;
	app::List_1_UnityEngine_GameObject__Add(temScene1Root->fields.m_objectsToTimeSliceEnable, gameObject, (*app::List_1_UnityEngine_GameObject__Add__MethodInfo));
	app::List_1_UnityEngine_GameObject__Add(temScene1Root->fields.m_objectsToTimeSliceEnable, gameObject1, (*app::List_1_UnityEngine_GameObject__Add__MethodInfo));
	temScene1Root->fields.m_objectsToTimesliceDisable = temScene1Root->fields.m_objectsToTimeSliceEnable;

	app::Component_1__Array* componentsToEnable = (app::Component_1__Array*)app::Array_CreateInstance_1(componentArrType, 10, NULL);
	temScene1Root->fields.m_sceneRootPostEnabledObservers = componentsToEnable;
	//temScene1Root->fields.m_sceneRootPostEnabledObservers->vector[0] = (app::Component_1*)temScene1Root;
	//temScene1Root->fields.m_sceneRootPostEnabledObservers->vector[1] = (app::Component_1*)sceneSettingsComponent;
	temScene1Root->fields.sceneRootPreDisableObservers = temScene1Root->fields.m_sceneRootPostEnabledObservers;*/

	//app::GameObject_SetActive(temScene1, true, NULL);

	app::List_1_RuntimeSceneMetaData__Add(scenesManager->fields.m_tempList, temScene1RuntimeMetaData, (*app::List_1_RuntimeSceneMetaData__Add__MethodInfo));
	app::List_1_Moon_IRectProvider__Add(scenesManager->klass->static_fields->m_tempRectProviderList, (app::IRectProvider*)temScene1RuntimeMetaData, (*app::List_1_Moon_IRectProvider__Add__MethodInfo));
	app::HashSet_1_MoonGuid__Add(scenesManager->fields.m_scenes, sceneGuid, (*app::HashSet_1_MoonGuid__Add__MethodInfo));
	int hashcode = app::String_GetHashCode(string_new(name.data()), NULL);
	scenesManager->fields.AllScenes->fields._items->max_length *= 2;
	scenesManager->fields.AllScenes->fields._items->vector[scenesManager->fields.AllScenes->fields._size] = temScene1RuntimeMetaData;
	scenesManager->fields.m_linearScenesArray->max_length *= 2;
	app::Dictionary_2_MoonGuid_RuntimeSceneMetaData__set_Item(scenesManager->fields.m_guidToRuntimeSceneMetaDatas, sceneGuid, temScene1RuntimeMetaData, (*app::Dictionary_2_MoonGuid_RuntimeSceneMetaData__set_Item__MethodInfo));
	app::Dictionary_2_System_Int32_RuntimeSceneMetaData__set_Item(scenesManager->fields.m_sceneNameToRuntimeSceneMetaDatas, hashcode, temScene1RuntimeMetaData, (*app::Dictionary_2_System_Int32_RuntimeSceneMetaData__set_Item__MethodInfo));

	bool firstNullptr = false;
	int placedIndex = -1;
	for (int i = 0; i < scenesManager->fields.m_linearScenesArray->max_length; i++)
	{
		if (firstNullptr == false && scenesManager->fields.m_linearScenesArray->vector[i] == nullptr)
		{
			firstNullptr = true;
			temScene1RuntimeMetaData->fields.LinearId = temScene1MetaData->fields.LinearId = i;
			placedIndex = i;
			scenesManager->fields.m_linearScenesArray->vector[i] = temScene1RuntimeMetaData;
		}
	}

	auto Il2ClassSceneManagerScene = GetClass("", "SceneManagerScene");
	temScene1ManagerScene = (app::SceneManagerScene*)il2cpp_object_new((Il2CppClass*)Il2ClassSceneManagerScene);
	app::SceneManagerScene__ctor(temScene1ManagerScene, temScene1Root, temScene1RuntimeMetaData, app::SceneState__Enum::SceneState__Enum_Loaded, NULL);
	temScene1ManagerScene->fields.HasStartBeenCalled = true;
	app::Object_1_DontDestroyOnLoad((app::Object_1*)temScene1ManagerScene, NULL);
	MDV::GCHandles.push_back(il2cpp_gchandle_new((Il2CppObject*)temScene1ManagerScene, true));
	MDV::GCHandles.push_back(il2cpp_gchandle_new((Il2CppObject*)temScene1RuntimeMetaData, true));


	/*app::ScenesManager_Register(scenesManager, temScene1Root, true, NULL);
	temScene1ManagerScene = scenesManager->fields.ActiveScenes->fields._items->vector[scenesManager->fields.ActiveScenes->fields._size - 1];
	temScene1ManagerScene->fields.MetaData = temScene1RuntimeMetaData;
	temScene1ManagerScene->fields.SceneRoot = temScene1Root;
	app::SceneManagerScene_SetSceneRoot(temScene1ManagerScene, temScene1Root, NULL);
	app::Object_1_DontDestroyOnLoad((app::Object_1*)temScene1ManagerScene, NULL);
	MDV::GCHandles.push_back(il2cpp_gchandle_new((Il2CppObject*)temScene1ManagerScene, true));
	MDV::GCHandles.push_back(il2cpp_gchandle_new((Il2CppObject*)temScene1RuntimeMetaData, true));
	scenesManager->fields.ActiveScenes->fields._items->vector[scenesManager->fields.ActiveScenes->fields._size - 1] = temScene1ManagerScene;*/

	//app::ScenesManager_Register(scenesManager, temScene1Root, true, NULL);
	//app::GameObject_SetActiveRecursively(temScene1, true, NULL);
	//app::ScenesManager_EnableDisabledScene(scenesManager, temScene1ManagerScene, true, NULL);
	//temScene1ManagerScene->fields.KeepLoadedForCheckpoint = true;
	//temScene1ManagerScene->fields.PreventUnloading = true;
	app::SceneManager_MoveGameObjectToScene(temScene1, temUnityScene1, NULL);
	app::SceneRoot_StoreActiveObjects(temScene1Root, app::GameObject_get_transform(gameObject1, NULL), true, true, NULL);
	app::SceneRoot_InitActivationTask(temScene1Root, NULL);
	app::SceneRoot_RebuildObjectsToTimeSliceAndObservers(temScene1Root, NULL);
	app::List_1_SceneManagerScene__Add(scenesManager->fields.ActiveScenes, temScene1ManagerScene, (*app::List_1_SceneManagerScene__Add__MethodInfo));
	//app::GameObject_SetActiveRecursively(temScene1, true, NULL);
	//app::ScenesManager_Register(scenesManager, temScene1Root, true, NULL);
	temScene1ManagerScene->fields.KeepLoadedForCheckpoint = true;
	temScene1ManagerScene->fields.PreventUnloading = true;

	app::ScenesManager_PreventUnloading(scenesManager, temScene1MetaData, false, NULL);
	app::ScenesManager_PreventUnloading_1(scenesManager, temScene1RuntimeMetaData, false, NULL);
	app::RuntimeSceneMetaData_InitializedIsInsideCaches(temScene1RuntimeMetaData, NULL);
	app::ScenesManager_Register(scenesManager, temScene1Root, false, NULL);
	app::ScenesManager_ResetDistanceCaches(scenesManager, NULL);
	app::SceneManager_SetActiveScene(temUnityScene1, NULL);

	app::ScenesManagerBehaviourUtility_UpdateNearbyScenesUtilityList(TemSceneHelper::BehaviourUtility, NULL);
	app::ScenesManagerBehaviourUtility_UpdateActiveScenesUtilityList(TemSceneHelper::BehaviourUtility, NULL);
	app::ScenesManagerBehaviourUtility_UpdateSceneUtility(TemSceneHelper::BehaviourUtility, NULL);

	//app::ScenesManager_GenerateGuidToRuntimeSceneMetaDataDictionaryAndQuadTree(scenesManager, true, NULL);
	app::QuadTree_AddObjectRecursively(scenesManager->fields.m_scenesQuadTree, scenesManager->fields.m_scenesQuadTree->fields.RootNode, (app::IRectProvider*)temScene1RuntimeMetaData, temScene1RuntimeMetaData->fields.LinearId, NULL);

	//app::AreaMapUI* mapUI = (*app::AreaMapUI__TypeInfo)->static_fields->Instance;
	//app::AreaMapDebugNavigation_UpdateSceneBoundsMarker(mapUI->fields._DebugNavigation_k__BackingField, temScene1RuntimeMetaData, NULL);
	//app::SceneInspector__updateWorldBounds((*app::SceneInspector__TypeInfo)->static_fields->Instance, NULL);
	//app::SceneInspector_DrawScene((*app::SceneInspector__TypeInfo)->static_fields->Instance, temScene1MetaData, NULL);
}