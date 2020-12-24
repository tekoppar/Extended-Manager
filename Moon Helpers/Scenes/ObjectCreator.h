#pragma once

class ObjectCreator
{
public:
	static app::Scene temUnityScene1;
	static app::GameObject* temScene1;
	static app::SceneMetaData* temScene1MetaData;
	static app::RuntimeSceneMetaData* temScene1RuntimeMetaData;
	static app::SceneRoot* temScene1Root;
	static app::SceneManagerScene* temScene1ManagerScene;


	void CreateObject(std::string Namespace, std::string Class)
	{
		auto Il2Class = GetClass(Namespace, Class);
		app::Type* type = GetTypeFromClass((Il2CppClass*)Il2Class);

		app::GameObject* gameObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
		app::GameObject__ctor(gameObject, string_new("NewGameObject"), NULL);
		MDV::GCHandles.push_back(il2cpp_gchandle_new((Il2CppObject*)gameObject, true));
		app::Object_1_DontDestroyOnLoad((app::Object_1*)gameObject, NULL);
		TransformSetPosition(gameObject, tem::Vector3(-791.86f, -4296.17f, 0.0f));

		switch (sutil::hash(Class.c_str()))
		{
		case sutil::hash("SceneManagerScene"):
		{
			temScene1 = gameObject;
			app::Transform* gameObjectT = app::GameObject_get_transform(temScene1, NULL);
			app::GameObject_SetActive(temScene1, false, NULL);
			app::MoonGuid* sceneGuid = app::GuidOwner_GenerateGUID(NULL);
			app::GameObject* gameObject1 = app::GameObject_CreatePrimitive(app::PrimitiveType__Enum_Cube, NULL);
			app::GameObject__ctor(gameObject1, string_new("CubeObject"), NULL);
			TransformSetParent(gameObject1, temScene1);

			auto Il2ClassSceneMetaData = GetClass("", "SceneMetaData");
			app::Type* typeSceneMetaData = GetTypeFromClass((Il2CppClass*)Il2ClassSceneMetaData);
			temScene1MetaData = (app::SceneMetaData*)app::ScriptableObject_CreateInstance(typeSceneMetaData, NULL);
			app::SceneMetaData__ctor(temScene1MetaData, NULL);
			temScene1MetaData->fields.SceneMoonGuid = sceneGuid;
			temScene1MetaData->fields.CanTimeSlice = true;

			auto Il2ClassRuntimeSceneMetaData = GetClass("", "RuntimeSceneMetaData");
			temScene1RuntimeMetaData = (app::RuntimeSceneMetaData*)il2cpp_object_new((Il2CppClass*)Il2ClassRuntimeSceneMetaData);
			app::RuntimeSceneMetaData__ctor_1(temScene1RuntimeMetaData, temScene1MetaData, NULL);
			temScene1RuntimeMetaData->fields.SceneMoonGuid = sceneGuid;
			temScene1RuntimeMetaData->fields.Scene = string_new("NewGameObject");
			temScene1RuntimeMetaData->fields.VisibleOnlyInPaddingDependantScene = temScene1MetaData;
			temScene1RuntimeMetaData->fields.CanTimeSlice = true;
			temScene1RuntimeMetaData->fields.DependantScene = true;

			app::ScenesManager* scenesManager = (*app::Scenes__TypeInfo)->static_fields->Manager;
			//temScene1MetaData->fields.LoadingCondition = temScene1RuntimeMetaData->fields.LoadingCondition = scenesManager->fields.ActiveScenes->fields._items->vector[0]->fields.MetaData->fields.LoadingCondition;
			app::List_1_UnityEngine_Rect_* sceneLoadingBounds = (app::List_1_UnityEngine_Rect_*)il2cpp_object_new((Il2CppClass*)(*app::List_1_UnityEngine_Rect___TypeInfo));
			app::Type* rectArrType = GetTypeFromClass((Il2CppClass*)(*app::Rect__Array__TypeInfo));
			app::Rect__Array* rectArr1 = (app::Rect__Array*)app::Array_CreateInstance_1(rectArrType, 10, NULL);
			sceneLoadingBounds->fields._items = rectArr1;
			app::List_1_UnityEngine_Rect__Insert(sceneLoadingBounds, 0, tem::Rect(-753.46f, -4333.48f, 23.91f, 19.93f).ToMoon(), NULL);
			temScene1MetaData->fields.SceneLoadingBoundaries = temScene1RuntimeMetaData->fields.SceneLoadingBoundaries = sceneLoadingBounds;

			app::List_1_UnityEngine_Rect_* sceneBounds = (app::List_1_UnityEngine_Rect_*)il2cpp_object_new((Il2CppClass*)(*app::List_1_UnityEngine_Rect___TypeInfo));
			app::Rect__Array* rectArr2 = (app::Rect__Array*)app::Array_CreateInstance_1(rectArrType, 10, NULL);
			sceneBounds->fields._items = rectArr2;
			app::List_1_UnityEngine_Rect__Insert(sceneBounds, 0, tem::Rect(-814.75f, -4318.35f, 62.32f, 30.27f).ToMoon(), NULL);
			temScene1MetaData->fields.SceneBoundaries = temScene1RuntimeMetaData->fields.SceneBoundaries = sceneBounds;

			app::List_1_UnityEngine_Rect_* scenePaddingBounds = (app::List_1_UnityEngine_Rect_*)il2cpp_object_new((Il2CppClass*)(*app::List_1_UnityEngine_Rect___TypeInfo));
			app::Rect__Array* rectArr3 = (app::Rect__Array*)app::Array_CreateInstance_1(rectArrType, 10, NULL);
			scenePaddingBounds->fields._items = rectArr3;
			app::List_1_UnityEngine_Rect__Insert(scenePaddingBounds, 0, tem::Rect(-819.84f, -4311.28f, 77.32f, 44.90f).ToMoon(), NULL);
			temScene1MetaData->fields.ScenePaddingBoundaries = temScene1RuntimeMetaData->fields.ScenePaddingBoundaries = scenePaddingBounds;

			temScene1RuntimeMetaData->fields.m_totalRect = tem::Rect(-824.19f, -4307.75f, 85.78f, 55.02f).ToMoon();

			app::Type* singleArrType = GetTypeFromClass((Il2CppClass*)(*app::Single__Array__TypeInfo));
			app::Single__Array* singleArr1 = (app::Single__Array*)app::Array_CreateInstance_1(singleArrType, 10, NULL);
			singleArr1->vector[0] = 1.0f;
			temScene1MetaData->fields.ScenePaddingWideScreenExpansion->fields._items = singleArr1;
			temScene1MetaData->fields.ScenePaddingWideScreenExpansion->fields._size = 1;
			temScene1RuntimeMetaData->fields.ScenePaddingWideScreenExpansion->fields._items = singleArr1;
			temScene1RuntimeMetaData->fields.ScenePaddingWideScreenExpansion->fields._size = 1;

			temScene1MetaData->fields.InitialValuesBlindForest = scenesManager->fields.ActiveScenes->fields._items->vector[0]->fields.SceneRoot->fields.MetaData->fields.InitialValuesBlindForest;
			temScene1MetaData->fields.InitialValuesWisp = scenesManager->fields.ActiveScenes->fields._items->vector[0]->fields.SceneRoot->fields.MetaData->fields.InitialValuesWisp;
			temScene1MetaData->fields.RootPosition = tem::Vector3(-773.8f, -4342.81f, 0.0f).ToMoon();
			temScene1MetaData->fields.DependantScene = true;
			//temScene1MetaData->fields.ReverseLoadingBoundaries = scenesManager->fields.ActiveScenes->fields._items->vector[0]->fields.SceneRoot->fields.MetaData->fields.ReverseLoadingBoundaries;

			TransformSetPosition(gameObject, tem::Vector3(-773.8f, -4342.81f, 0.0f).ToMoon());

			auto Il2ClassSceneRoot = GetClass("", "SceneRoot");
			app::Type* rootType = GetTypeFromClass(Il2ClassSceneRoot);
			temScene1Root = (app::SceneRoot*)app::GameObject_AddComponent(temScene1, rootType, NULL);
			app::Object_1_DontDestroyOnLoad((app::Object_1*)temScene1Root, NULL);
			MDV::GCHandles.push_back(il2cpp_gchandle_new((Il2CppObject*)temScene1Root, true));
			//app::SceneRoot* temScene1Root = (app::SceneRoot*)il2cpp_object_new((Il2CppClass*)(*app::SceneRoot__TypeInfo));
			//app::GameObject__ctor((app::GameObject*)temScene1Root, string_new("test123"), NULL);
			temScene1RuntimeMetaData->fields.MapPositionOverride = temScene1Root->fields.m_previousPosition = temScene1MetaData->fields.RootPosition;
			temScene1RuntimeMetaData->fields.PlaceholderPosition = tem::Vector3(temScene1RuntimeMetaData->fields.MapPositionOverride).ToVector2();

			app::Type* boolArrType = GetTypeFromClass((Il2CppClass*)(*app::Boolean__Array__TypeInfo));
			app::Boolean__Array* boolArr1 = (app::Boolean__Array*)app::Array_CreateInstance_1(boolArrType, 10, NULL);
			temScene1RuntimeMetaData->fields.m_cachedIsInsideSceneBounds = boolArr1;
			app::Boolean__Array* boolArr2 = (app::Boolean__Array*)app::Array_CreateInstance_1(boolArrType, 10, NULL);
			temScene1RuntimeMetaData->fields.m_cachedIsInsideScenePaddingBounds = boolArr2;
			app::Boolean__Array* boolArr3 = (app::Boolean__Array*)app::Array_CreateInstance_1(boolArrType, 10, NULL);
			temScene1RuntimeMetaData->fields.m_IsInsideSceneBoundsIsCached = boolArr3;
			app::Boolean__Array* boolArr4 = (app::Boolean__Array*)app::Array_CreateInstance_1(boolArrType, 10, NULL);
			temScene1RuntimeMetaData->fields.m_IsInsideScenePaddingBoundsIsCached = boolArr4;

			auto Il2ClassSceneSettingsComponent = GetClass("", "SceneSettingsComponent");
			app::Type* sceneSettingsComponentType = GetTypeFromClass(Il2ClassSceneSettingsComponent);
			app::SceneSettingsComponent* sceneSettingsComponent = (app::SceneSettingsComponent*)app::GameObject_AddComponent(temScene1, sceneSettingsComponentType, NULL);
			app::SceneSettingsComponent__ctor(sceneSettingsComponent, NULL);

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

			temUnityScene1 = app::SceneManager_CreateScene_1(string_new("NewGameObject"), NULL);

			app::SceneRoot__ctor(temScene1Root, NULL);
			app::SceneRoot_StoreActiveObjectsFor(temScene1Root, app::GameObject_get_transform(gameObject1, NULL), NULL);
			temScene1Root->fields.MetaData = temScene1MetaData;
			temScene1Root->fields.m_sceneSettings = sceneSettingsComponent;
			temScene1Root->fields.m_highPriorityEnabling = true;

			app::Type* componentArrType = GetTypeFromClass((Il2CppClass*)(*app::Component_1__Array__TypeInfo));
			app::Component_1__Array* componentArr = (app::Component_1__Array*)app::Array_CreateInstance_1(componentArrType, 10, NULL);
			temScene1Root->fields.m_frustumOptimizedObjects = componentArr;

			//app::ScenesManager_RegisterSceneByName(scenesManager, string_new("NewGameObject"), true, true, NULL);
			//app::ScenesManager_Register(scenesManager, temScene1Root, true, NULL);
			temScene1Root->fields._._._.m_cachedGameObject = temScene1;
			temScene1Root->fields._._._.m_cachedTransform = gameObjectT;

			app::List_1_UnityEngine_GameObject_* gameObjectsToEnable = (app::List_1_UnityEngine_GameObject_*)il2cpp_object_new((Il2CppClass*)(*app::List_1_UnityEngine_GameObject___TypeInfo));
			app::List_1_UnityEngine_GameObject___ctor(gameObjectsToEnable, 10, (*app::List_1_UnityEngine_GameObject___ctor__MethodInfo));
			temScene1Root->fields.m_objectsToTimeSliceEnable = gameObjectsToEnable;
			app::List_1_UnityEngine_GameObject__Add(temScene1Root->fields.m_objectsToTimeSliceEnable, gameObject, (*app::List_1_UnityEngine_GameObject__Add__MethodInfo));
			app::List_1_UnityEngine_GameObject__Add(temScene1Root->fields.m_objectsToTimeSliceEnable, gameObject1, (*app::List_1_UnityEngine_GameObject__Add__MethodInfo));
			temScene1Root->fields.m_objectsToTimesliceDisable = temScene1Root->fields.m_objectsToTimeSliceEnable;

			app::Component_1__Array* componentsToEnable = (app::Component_1__Array*)app::Array_CreateInstance_1(componentArrType, 10, NULL);
			temScene1Root->fields.m_sceneRootPostEnabledObservers = componentsToEnable;
			//temScene1Root->fields.m_sceneRootPostEnabledObservers->vector[0] = (app::Component_1*)temScene1Root;
			//temScene1Root->fields.m_sceneRootPostEnabledObservers->vector[1] = (app::Component_1*)sceneSettingsComponent;
			temScene1Root->fields.sceneRootPreDisableObservers = temScene1Root->fields.m_sceneRootPostEnabledObservers;

			//app::GameObject_SetActive(temScene1, true, NULL);
			app::ScenesManager_Register(scenesManager, temScene1Root, true, NULL);

			scenesManager->fields.AllScenes->fields._items->max_length *= 2;
			scenesManager->fields.AllScenes->fields._items->vector[scenesManager->fields.AllScenes->fields._size] = temScene1RuntimeMetaData;
			scenesManager->fields.m_linearScenesArray->max_length *= 2;
			app::Dictionary_2_MoonGuid_RuntimeSceneMetaData__set_Item(scenesManager->fields.m_guidToRuntimeSceneMetaDatas, sceneGuid, temScene1RuntimeMetaData, (*app::Dictionary_2_MoonGuid_RuntimeSceneMetaData__set_Item__MethodInfo));

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

			app::SceneManager_MoveGameObjectToScene(temScene1, temUnityScene1, NULL);

			temScene1ManagerScene = scenesManager->fields.ActiveScenes->fields._items->vector[scenesManager->fields.ActiveScenes->fields._size - 1];
			temScene1ManagerScene->fields.MetaData = temScene1RuntimeMetaData;
			temScene1ManagerScene->fields.SceneRoot = temScene1Root;
			app::SceneManagerScene_SetSceneRoot(temScene1ManagerScene, temScene1Root, NULL);
			app::Object_1_DontDestroyOnLoad((app::Object_1*)temScene1ManagerScene, NULL);
			MDV::GCHandles.push_back(il2cpp_gchandle_new((Il2CppObject*)temScene1ManagerScene, true));
			MDV::GCHandles.push_back(il2cpp_gchandle_new((Il2CppObject*)temScene1RuntimeMetaData, true));
			scenesManager->fields.ActiveScenes->fields._items->vector[scenesManager->fields.ActiveScenes->fields._size - 1] = temScene1ManagerScene;

			//app::ScenesManager_Register(scenesManager, temScene1Root, true, NULL);
			//app::GameObject_SetActiveRecursively(temScene1, true, NULL);
 			app::ScenesManager_EnableDisabledScene(scenesManager, temScene1ManagerScene, true, NULL);
			temScene1ManagerScene->fields.KeepLoadedForCheckpoint = true;
			temScene1ManagerScene->fields.PreventUnloading = true;
		}
		}
	}
};