#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <string>
#include <vector>

#include "StringUtils.h"
#include "SeinCharacterHelper.h"
#include "ManagerDef.h"
#include "SeinVisualEditor.h"

app::ScenesManager* sceneManager;
std::string ManagerPath = "";
TemUser MDV::User = TemUser();
std::vector<Global*> MDV::AllObjectsToCallUpdate = std::vector<Global*>();
app::GameController* MDV::MoonGameController = nullptr;
app::GameplayCamera* MDV::SeinGameplayCamera = nullptr;
app::GameWorld* MDV::MoonGameWorld = nullptr;
app::SeinCharacter* MDV::MoonSein = nullptr;
app::SeinPlayAnimationController* MDV::SeinPlayAnimationController = nullptr;
app::AreaMapUI* MDV::AreaMapUI = nullptr;
std::vector<std::string> MDV::MessageToWrite = std::vector<std::string>();
app::GameObject* MDV::SelectedObject = nullptr;
bool MDV::CanCallMethods = false;

void MDV::ValidatePointers()
{
	app::GameStateMachine* stateMachine = (*app::GameStateMachine__TypeInfo)->static_fields->m_instance;

	if (MoonSein == nullptr || MoonSein != nullptr && MoonSein->fields._._._._.m_CachedPtr == nullptr)
	{
		MoonSein = app::Characters_get_Sein(NULL);
		SeinVisualEditor::VisualSettingsUpdated.ResetBooleans();
		SeinVisualEditor::SetHolidayOri();
	}

	if (SeinPlayAnimationController == nullptr)
		SeinPlayAnimationController = MoonSein->fields.Controller->fields.m_playAnimationController;

	if (SeinPlayAnimationController->fields.Sein == nullptr || SeinPlayAnimationController->fields.Sein->fields._._._._.m_CachedPtr == nullptr)
		SeinPlayAnimationController->fields.Sein = MoonSein;

	if (AreaMapUI == nullptr || AreaMapUI->fields._._._._.m_CachedPtr == nullptr)
		AreaMapUI = (*app::AreaMapUI__TypeInfo)->static_fields->Instance;

	//update visuals
	if (SeinVisualEditor::ManagerLoaded == true && MoonGameController != nullptr && stateMachine->fields._CurrentState_k__BackingField == app::GameStateMachine_State__Enum::GameStateMachine_State__Enum_Game && MoonSein != nullptr)
	{
		SeinVisualEditor::SetAllVisuals();
	}
}

app::GameObject* GetSceneByName(std::string sceneToFind)
{
	app::GameObject* foundScene = nullptr;
	if (sceneManager != nullptr)
	{
		for (int i = 0; i < sceneManager->fields.ActiveScenes->fields._size; i++)
		{
			app::SceneManagerScene* managerScene = sceneManager->fields.ActiveScenes->fields._items->vector[i];

			if (managerScene != nullptr)
			{
				app::SceneRoot* rootScene = managerScene->fields.SceneRoot;
				app::RuntimeSceneMetaData* metaData = managerScene->fields.MetaData;
				std::string sceneName = sutil::convert_csstring(metaData->fields.Scene);

				if (sceneName == sceneToFind)
				{
					if (rootScene != nullptr)
					{
						foundScene = app::Component_1_get_gameObject((app::Component_1*)rootScene, NULL);
						break;
					}
				}
			}
		}
	}

	return foundScene;
}

app::MoonGuid* GetSceneMoonGuidAll(std::string sceneToFind)
{
	app::GameObject* foundScene = nullptr;
	if (sceneManager != nullptr)
	{
		for (int i = 0; i < sceneManager->fields.AllScenes->fields._size; i++)
		{
			app::RuntimeSceneMetaData* metaDataTop = sceneManager->fields.AllScenes->fields._items->vector[i];
			std::string sceneNameTop = sutil::convert_csstring(metaDataTop->fields.Scene);
			if (sceneNameTop == sceneToFind)
			{
				app::SceneManagerScene* managerScene = app::ScenesManager_GetFromCurrentScenes(sceneManager, metaDataTop, NULL);

				if (managerScene == nullptr)
					managerScene = app::ScenesManager_GetSceneManagerScene(sceneManager, string_new(sceneToFind.data()), NULL);

				if (managerScene != nullptr)
				{
					app::SceneRoot* rootScene = managerScene->fields.SceneRoot;
					app::RuntimeSceneMetaData* metaData = managerScene->fields.MetaData;
					std::string sceneName = sutil::convert_csstring(metaData->fields.Scene);

					if (sceneName == sceneToFind)
					{
						return metaData->fields.SceneMoonGuid;
					}
				}
			}
		}
	}

	return nullptr;
}

bool IsSceneLoadedByName(std::string sceneToFind)
{
	app::MoonGuid* guid = GetSceneMoonGuidAll(sceneToFind);
	return app::ScenesManager_SceneIsLoaded(sceneManager, guid, NULL);
}

app::GameObject* GetSceneByNameAll(std::string sceneToFind)
{
	app::GameObject* foundScene = nullptr;
	if (sceneManager != nullptr)
	{
		for (int i = 0; i < sceneManager->fields.AllScenes->fields._size; i++)
		{
			app::RuntimeSceneMetaData* metaDataTop = sceneManager->fields.AllScenes->fields._items->vector[i];
			std::string sceneNameTop = sutil::convert_csstring(metaDataTop->fields.Scene);
			if (sceneNameTop == sceneToFind)
			{
				app::SceneManagerScene* managerScene = app::ScenesManager_GetFromCurrentScenes(sceneManager, metaDataTop, NULL);

				if (managerScene == nullptr)
					managerScene = app::ScenesManager_GetSceneManagerScene(sceneManager, string_new(sceneToFind.data()), NULL);

				if (managerScene != nullptr)
				{
					app::SceneRoot* rootScene = managerScene->fields.SceneRoot;
					app::RuntimeSceneMetaData* metaData = managerScene->fields.MetaData;
					std::string sceneName = sutil::convert_csstring(metaData->fields.Scene);

					if (sceneName == sceneToFind)
					{
						if (rootScene != nullptr)
						{
							foundScene = app::Component_1_get_gameObject((app::Component_1*)rootScene, NULL);
							break;
						}
					}
				}
			}
		}
	}

	return foundScene;
}

app::GameObject* PreloadSceneByName(std::string sceneToPreload)
{
	app::GameObject* foundScene = nullptr;
	if (sceneManager != nullptr)
	{
		for (int i = 0; i < sceneManager->fields.AllScenes->fields._size; i++)
		{
			app::RuntimeSceneMetaData* metaDataTop = sceneManager->fields.AllScenes->fields._items->vector[i];
			std::string sceneNameTop = sutil::convert_csstring(metaDataTop->fields.Scene);
			app::SceneManagerScene* managerScene = app::ScenesManager_GetFromCurrentScenes(sceneManager, metaDataTop, NULL);

			if (managerScene == nullptr && sceneNameTop == sceneToPreload)
			{
				app::ScenesManager_PreloadScene(sceneManager, metaDataTop, NULL);
			}
		}
	}

	return foundScene;
}

app::GameObject* EnableSceneByName(std::string sceneToPreload)
{
	app::GameObject* foundScene = nullptr;
	if (sceneManager != nullptr)
	{
		for (int i = 0; i < sceneManager->fields.AllScenes->fields._size; i++)
		{
			app::RuntimeSceneMetaData* metaDataTop = sceneManager->fields.AllScenes->fields._items->vector[i];
			std::string sceneNameTop = sutil::convert_csstring(metaDataTop->fields.Scene);
			app::SceneManagerScene* managerScene = app::ScenesManager_GetFromCurrentScenes(sceneManager, metaDataTop, NULL);

			if (managerScene == nullptr && sceneNameTop == sceneToPreload)
			{
				app::SceneManagerScene_EnableScene(managerScene, true, NULL);
			}
		}
	}

	return foundScene;
}

app::GameObject* GetComponentByScenePath(std::string sceneName, std::vector<std::string> scenePath)
{
	app::GameObject* currentObject = GetSceneByName(sceneName);
	app::String* activeObjectName = nullptr;

	if (currentObject == nullptr)
		currentObject = GetSceneByNameAll(sceneName);

	app::Type* transformType = GetType("UnityEngine", "Transform");

	if (currentObject != nullptr)
	{
		for (auto& string : scenePath)
		{
			activeObjectName = string_new(string.c_str());
			app::Component_1__Array* components = app::GameObject_GetComponentsInChildren_1(currentObject, transformType, true, NULL);

			if (components != nullptr)
			{
				for (int i = 0; i < components->max_length; i++)
				{
					if (components->vector[i] != nullptr)
					{
						app::GameObject* gamyobj = app::Component_1_get_gameObject(components->vector[i], NULL);
						app::String* oName = app::Object_1_get_name((app::Object_1*)gamyobj, NULL);

						bool same = app::String_Equals_1(activeObjectName, oName, NULL);
						if (same)
						{
							currentObject = gamyobj;
							break;
						}
					}
				}
			}
		}
	}

	return currentObject;
}

app::GameObject* GetComponentByPath(app::GameObject* object, std::vector<std::string> scenePath)
{
	app::GameObject* currentObject = object;
	app::Type* transformType = GetType("UnityEngine", "Transform");
	app::String* activeObjectName = nullptr;

	if (currentObject != nullptr)
	{
		for (auto& string : scenePath)
		{
			activeObjectName = string_new(string.c_str());
			app::Component_1__Array* components = app::GameObject_GetComponentsInChildren_1(currentObject, transformType, true, NULL);

			if (components != nullptr)
			{
				for (int i = 0; i < components->max_length; i++)
				{
					if (components->vector[i] != nullptr)
					{
						app::GameObject* gamyobj = app::Component_1_get_gameObject(components->vector[i], NULL);
						app::String* oName = app::Object_1_get_name((app::Object_1*)gamyobj, NULL);
						bool same = app::String_Equals_1(activeObjectName, oName, NULL);

						if (same && currentObject != gamyobj)
						{
							currentObject = gamyobj;
							break;
						}
					}
				}
			}
		}
	}

	return currentObject;
}

std::vector<app::GameObject*> GetComponentsByName(app::GameObject* object, std::string componentName)
{
	std::vector<app::GameObject*> foundComponents;
	app::Type* transformType = GetType("UnityEngine", "Transform");
	app::String* activeObjectName = string_new(componentName.c_str());;

	if (object != nullptr)
	{
			app::Component_1__Array* components = app::GameObject_GetComponentsInChildren_1(object, transformType, true, NULL);

			if (components != nullptr)
			{
				for (int i = 0; i < components->max_length; i++)
				{
					if (components->vector[i] != nullptr)
					{
						app::GameObject* gamyobj = app::Component_1_get_gameObject(components->vector[i], NULL);
						app::String* oName = app::Object_1_get_name((app::Object_1*)gamyobj, NULL);
						bool same = app::String_Equals_1(activeObjectName, oName, NULL);

						if (same && object != gamyobj)
						{
							foundComponents.push_back(gamyobj);
						}
					}
				}
		}
	}

	return foundComponents;
}

app::GameObject* GetComponentByName(app::GameObject* object, std::string componentName)
{
	app::GameObject* foundComponent = nullptr;
	app::Type* transformType = GetType("UnityEngine", "Transform");
	app::String* activeObjectName = string_new(componentName.c_str());;

	if (object != nullptr)
	{
		app::Component_1__Array* components = app::GameObject_GetComponentsInChildren_1(object, transformType, true, NULL);

		if (components != nullptr)
		{
			for (int i = 0; i < components->max_length; i++)
			{
				if (components->vector[i] != nullptr)
				{
					app::GameObject* gamyobj = app::Component_1_get_gameObject(components->vector[i], NULL);
					app::String* oName = app::Object_1_get_name((app::Object_1*)gamyobj, NULL);
					bool same = app::String_Equals_1(activeObjectName, oName, NULL);

					if (same && object != gamyobj)
					{
						return gamyobj;

					}
				}
			}
		}
	}

	return foundComponent;
}

app::GameObject* GetComponentByNameContainsType(app::GameObject* object, std::string componentName, app::Type* type)
{
	app::GameObject* foundComponent = nullptr;
	app::Type* transformType = GetType("UnityEngine", "Transform");
	app::String* activeObjectName = string_new(componentName.c_str());;

	if (object != nullptr)
	{
		app::Component_1__Array* components = app::GameObject_GetComponentsInChildren_1(object, transformType, true, NULL);

		if (components != nullptr)
		{
			for (int i = 0; i < components->max_length; i++)
			{
				if (components->vector[i] != nullptr)
				{
					app::GameObject* gamyobj = app::Component_1_get_gameObject(components->vector[i], NULL);
					app::String* oName = app::Object_1_get_name((app::Object_1*)gamyobj, NULL);
					bool same = app::String_Equals_1(activeObjectName, oName, NULL);
					app::Component_1* typeComponent = app::GameObject_GetComponent(gamyobj, type, NULL);

					if (same && object != gamyobj && typeComponent != nullptr)
					{
						return gamyobj;
					}
				}
			}
		}
	}

	return foundComponent;
}

void DrawLine(app::Texture2D* tex, int x0, int y0, int x1, int y1, app::Color color)
{
	int dy = (int)(y1 - y0);
	int dx = (int)(x1 - x0);
	int stepx, stepy;

	if (dy < 0) { dy = -dy; stepy = -1; }
	else { stepy = 1; }
	if (dx < 0) { dx = -dx; stepx = -1; }
	else { stepx = 1; }
	dy <<= 1;
	dx <<= 1;

	float fraction = 0;

	app::Texture2D_SetPixel(tex, x0, y0, color, NULL);
	if (dx > dy) {
		fraction = (float)dy - (dx >> 1);
		while (std::abs(x0 - x1) > 1) {
			if (fraction >= 0) {
				y0 += stepy;
				fraction -= dx;
			}
			x0 += stepx;
			fraction += dy;
			app::Texture2D_SetPixel(tex, x0, y0, color, NULL);
		}
	}
	else {
		fraction = (float)dx - (dy >> 1);
		while (std::abs(y0 - y1) > 1) {
			if (fraction >= 0) {
				x0 += stepx;
				fraction -= dy;
			}
			y0 += stepy;
			fraction += dx;
			app::Texture2D_SetPixel(tex, x0, y0, color, NULL);
		}
	}
}

app::Component_1* GetComponentByTypeInChildren(app::GameObject* object, std::string Namespace, std::string Name)
{
	app::Type* componentType = GetType(Namespace, Name);
	app::Component_1* component = app::GameObject_GetComponentInChildren(object, componentType, true, NULL);

	return component;
}

std::vector<app::Component_1*> GetComponentsByTypeInChildren(app::GameObject* object, std::string Namespace, std::string Name)
{
	app::Type* componentType = GetType(Namespace, Name);
	app::Component_1__Array* components = app::GameObject_GetComponentsInChildren_1(object, componentType, true, NULL);

	std::vector<app::Component_1*> foundComponents;
	for (int i = 0; i < components->max_length; i++)
	{
		if (components->vector[i] != nullptr)
		{
			foundComponents.push_back(components->vector[i]);
		}
	}

	return foundComponents;
}

app::Component_1* GetComponentByType(app::GameObject* object, std::string Namespace, std::string Name)
{
	app::Type* componentType = GetType(Namespace, Name);
	app::Component_1* component = app::GameObject_GetComponent(object, componentType, NULL);

	return component;
}

app::GameObject* CreateNewCanvas()
{
	app::GameObject* canvasObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
	app::String* canvasObjectName = string_new("Canvas");
	app::GameObject__ctor(canvasObject, canvasObjectName, NULL);
	app::Transform* canvasObjectTransform = app::GameObject_get_transform(canvasObject, NULL);

	il2cpp_runtime_class_init((Il2CppClass*)(*app::Canvas__TypeInfo));
	auto CanvasScalerC = GetClass<>("UnityEngine.UI", "CanvasScaler");
	il2cpp_runtime_class_init((Il2CppClass*)CanvasScalerC);
	auto GraphicRaycasterC = GetClass<>("UnityEngine.UI", "GraphicRaycaster");
	il2cpp_runtime_class_init((Il2CppClass*)GraphicRaycasterC);

	app::Type* canvasT = GetType("UnityEngine", "Canvas");
	app::Type* CanvasScalerT = GetType("UnityEngine.UI", "CanvasScaler");
	app::Type* GraphicRaycasterT = GetType("UnityEngine.UI", "GraphicRaycaster");
	app::Canvas* Canvas = (app::Canvas*)app::GameObject_AddComponent(canvasObject, canvasT, NULL);

	//change render mode to screenspace overlay
	uintptr_t m_CachedPtr = (uintptr_t)Canvas->fields._._._.m_CachedPtr;
	m_CachedPtr = m_CachedPtr + 0x40; //offset 0x40 to m_rendermode
	int* m_rendermode = (int*)m_CachedPtr;
	int newRenderMode = 0;
	*m_rendermode = newRenderMode;

	app::Camera* camera = app::GameplayCamera_get_Camera(MDV::SeinGameplayCamera, NULL);
	app::Canvas_set_worldCamera(Canvas, camera, NULL);

	app::CanvasScaler* scaler = (app::CanvasScaler*)app::GameObject_AddComponent(canvasObject, CanvasScalerT, NULL);
	app::GraphicRaycaster* caster = (app::GraphicRaycaster*)app::GameObject_AddComponent(canvasObject, GraphicRaycasterT, NULL);

	return canvasObject;
}

void FillPixels(app::Texture2D* tex, int x, int y, app::Color color)
{
	for (int iX = 0; iX < x; iX++)
	{
		for (int iY = 0; iY < y; iY++)
		{
			app::Texture2D_SetPixel(tex, iX, iY, color, NULL);
		}
	}
}

void TransformSetScale(app::GameObject* object, tem::Vector3 scale)
{
	app::Type* transformType = GetType("UnityEngine", "Transform");

	if (transformType->klass->_0.name != "Transform" && transformType->klass->_0.name != "RectTransform")
	{
		transformType = GetTypeFromClass((Il2CppClass*)(*app::Transform__TypeInfo));
	}
		app::Transform* objectTransform = (app::Transform*)app::GameObject_GetComponent(object, transformType, NULL);
		app::Vector3* scaleLocal = (app::Vector3*)il2cpp_object_new((Il2CppClass*)(*app::Vector3__TypeInfo));
		scaleLocal->x = scale.X;
		scaleLocal->y = scale.Y;
		scaleLocal->z = scale.Z;
		app::Transform_set_localScale(objectTransform, *scaleLocal, NULL);
}

tem::Vector3 TransformGetScale(app::GameObject* object)
{
	app::Type* transformType = GetType("UnityEngine", "Transform");

	if (transformType->klass->_0.name != "Transform" && transformType->klass->_0.name != "RectTransform")
	{
		transformType = GetTypeFromClass((Il2CppClass*)(*app::Transform__TypeInfo));
	}
	app::Transform* objectTransform = (app::Transform*)app::GameObject_GetComponent(object, transformType, NULL);
	app::Vector3 scaleLocal = app::Transform_get_localScale(objectTransform, NULL);
	return tem::Vector3(scaleLocal.x, scaleLocal.y, scaleLocal.z);
}

void TransformSetPosition(app::GameObject* object, tem::Vector3 position)
{
	app::Type* transformType = GetType("UnityEngine", "Transform");

	if (transformType->klass->_0.name != "Transform" && transformType->klass->_0.name != "RectTransform")
	{
		transformType = GetTypeFromClass((Il2CppClass*)(*app::Transform__TypeInfo));
	}
	app::Transform* objectTransform = (app::Transform*)app::GameObject_GetComponent(object, transformType, NULL);
	app::Vector3* positionWorld = (app::Vector3*)il2cpp_object_new((Il2CppClass*)(*app::Vector3__TypeInfo));
	positionWorld->x = position.X;
	positionWorld->y = position.Y;
	positionWorld->z = position.Z;
	app::Transform_set_position(objectTransform, *positionWorld, NULL);
}

app::Vector3 TransformGetPosition(app::GameObject* object)
{
	app::Type* transformType = GetType("UnityEngine", "Transform");

	if (transformType->klass->_0.name != "Transform" && transformType->klass->_0.name != "RectTransform")
	{
		transformType = GetTypeFromClass((Il2CppClass*)(*app::Transform__TypeInfo));
	}
	app::Transform* objectTransform = (app::Transform*)app::GameObject_GetComponent(object, transformType, NULL);
	return app::Transform_get_position(objectTransform, NULL);
}

void TransformSetLocalPosition(app::GameObject* object, tem::Vector3 position)
{
	app::Type* transformType = GetType("UnityEngine", "Transform");

	if (transformType->klass->_0.name != "Transform" && transformType->klass->_0.name != "RectTransform")
	{
		transformType = GetTypeFromClass((Il2CppClass*)(*app::Transform__TypeInfo));
	}
	app::Transform* objectTransform = (app::Transform*)app::GameObject_GetComponent(object, transformType, NULL);
	app::Vector3* positionLocal = (app::Vector3*)il2cpp_object_new((Il2CppClass*)(*app::Vector3__TypeInfo));
	positionLocal->x = position.X;
	positionLocal->y = position.Y;
	positionLocal->z = position.Z;
	app::Transform_set_localPosition(objectTransform, *positionLocal, NULL);
}

tem::Vector3 TransformGetLocalPosition(app::GameObject* object)
{
	app::Type* transformType = GetType("UnityEngine", "Transform");

	if (transformType->klass->_0.name != "Transform" && transformType->klass->_0.name != "RectTransform")
	{
		transformType = GetTypeFromClass((Il2CppClass*)(*app::Transform__TypeInfo));
	}
	app::Transform* objectTransform = (app::Transform*)app::GameObject_GetComponent(object, transformType, NULL);
	app::Vector3 localPosition = app::Transform_get_localPosition(objectTransform, NULL);
	return localPosition;
}

void TransformSetRotation(app::GameObject* object, tem::Vector3 rotation)
{
	app::Type* transformType = GetType("UnityEngine", "Transform");

	if (transformType->klass->_0.name != "Transform" && transformType->klass->_0.name != "RectTransform")
	{
		transformType = GetTypeFromClass((Il2CppClass*)(*app::Transform__TypeInfo));
	}

	app::Transform* objectTransform = (app::Transform*)app::GameObject_GetComponent(object, transformType, NULL);
	app::Vector3* rotationLocal = (app::Vector3*)il2cpp_object_new((Il2CppClass*)(*app::Vector3__TypeInfo));
	rotationLocal->x = rotation.X;
	rotationLocal->y = rotation.Y;
	rotationLocal->z = rotation.Z;
	app::Transform_Rotate(objectTransform, *rotationLocal, app::Space__Enum::Space__Enum_Self, NULL);
}

void TransformSetEulerAngles(app::GameObject* object, tem::Vector3 angles)
{
	app::Type* transformType = GetType("UnityEngine", "Transform");

	if (transformType->klass->_0.name != "Transform" && transformType->klass->_0.name != "RectTransform")
	{
		transformType = GetTypeFromClass((Il2CppClass*)(*app::Transform__TypeInfo));
	}

	app::Transform* objectTransform = (app::Transform*)app::GameObject_GetComponent(object, transformType, NULL);
	app::Vector3* rotationLocal = (app::Vector3*)il2cpp_object_new((Il2CppClass*)(*app::Vector3__TypeInfo));
	rotationLocal->x = angles.X;
	rotationLocal->y = angles.Y;
	rotationLocal->z = angles.Z;
	app::Transform_set_eulerAngles(objectTransform, *rotationLocal, NULL);
}

tem::Vector3 TransformGetRotation(app::GameObject* object)
{
	app::Type* transformType = GetType("UnityEngine", "Transform");

	if (transformType->klass->_0.name != "Transform" && transformType->klass->_0.name != "RectTransform")
	{
		transformType = GetTypeFromClass((Il2CppClass*)(*app::Transform__TypeInfo));
	}
	app::Transform* objectTransform = (app::Transform*)app::GameObject_GetComponent(object, transformType, NULL);
	app::Quaternion rotation = app::Transform_get_rotation(objectTransform, NULL);
	app::Quaternion__Boxed* quatBoxed = (app::Quaternion__Boxed*)il2cpp_object_new((Il2CppClass*)(*app::Quaternion__TypeInfo));
	quatBoxed->fields = rotation;
	tem::Vector3 rotationV3 = app::Quaternion_ToEulerAngles(quatBoxed, NULL);
	return rotationV3;
}

void TransformSetParent(app::GameObject* object, app::GameObject* parent)
{
	app::Transform* objectTransform = app::GameObject_get_transform((app::GameObject*)object, NULL);

	app::Transform* parentTransform = nullptr;
	if (parent != NULL)
		parentTransform = app::GameObject_get_transform((app::GameObject*)parent, NULL);

	app::Transform_SetParent((app::Transform*)objectTransform, (parent == NULL ? NULL : parentTransform), NULL);
}

app::GameObject* TransformGetParent(app::GameObject* object)
{
	app::Transform* objectTransform = app::GameObject_get_transform((app::GameObject*)object, NULL);
	app::Transform* parentTransform = app::Transform_GetParent((app::Transform*)objectTransform, NULL);
	return app::Component_1_get_gameObject((app::Component_1*)parentTransform, NULL);
}

void TransformSetParentFromObject(app::GameObject* object, app::GameObject* child)
{
	app::Transform* objectTransform = app::GameObject_get_transform((app::GameObject*)object, NULL);
	app::Transform* childTransform = app::GameObject_get_transform((app::GameObject*)child, NULL);
	app::Transform* parentTransform = app::Transform_GetParent(childTransform, NULL);
	app::Transform_SetParent((app::Transform*)objectTransform, parentTransform, NULL);
}

void RectTransformSetSize(app::GameObject* object, tem::Vector3 size)
{
	app::Transform* objectTransform = app::GameObject_get_transform((app::GameObject*)object, NULL);
	app::Vector2* sizeDelta = (app::Vector2*)il2cpp_object_new((Il2CppClass*)(*app::Vector2__TypeInfo));
	sizeDelta->x = size.X;
	sizeDelta->y = size.Y;
	app::RectTransform_set_sizeDelta((app::RectTransform*)objectTransform, *sizeDelta, NULL);
}

void RectTransformSetAnchoredPosition(app::GameObject* object, tem::Vector3 anchor)
{
	app::Transform* objectTransform = app::GameObject_get_transform((app::GameObject*)object, NULL);
	app::Vector2* anchorSize = (app::Vector2*)il2cpp_object_new((Il2CppClass*)(*app::Vector2__TypeInfo));
	anchorSize->x = anchor.X;
	anchorSize->y = anchor.Y;
	app::RectTransform_set_anchoredPosition((app::RectTransform*)objectTransform, *anchorSize, NULL);
}

void RectTransformSetMinMax(app::GameObject* object, tem::Vector3 min, tem::Vector3 max)
{
	app::Transform* objectTransform = app::GameObject_get_transform((app::GameObject*)object, NULL);
	app::Vector2* anchorMin = (app::Vector2*)il2cpp_object_new((Il2CppClass*)(*app::Vector2__TypeInfo));
	app::Vector2* anchorMax = (app::Vector2*)il2cpp_object_new((Il2CppClass*)(*app::Vector2__TypeInfo));
	anchorMin->x = min.X;
	anchorMin->y = min.Y;
	anchorMax->x = max.X;
	anchorMax->y = max.Y;
	app::RectTransform_set_anchorMax((app::RectTransform*)objectTransform, *anchorMax, NULL);
	app::RectTransform_set_anchorMin((app::RectTransform*)objectTransform, *anchorMin, NULL);
}

app::Vector2 RectTransformGetMax(app::GameObject* object)
{
	app::Transform* objectTransform = app::GameObject_get_transform((app::GameObject*)object, NULL);
	return app::RectTransform_get_anchorMax((app::RectTransform*)objectTransform, NULL);
}

app::Vector2 RectTransformGetMin(app::GameObject* object)
{
	app::Transform* objectTransform = app::GameObject_get_transform((app::GameObject*)object, NULL);
	return app::RectTransform_get_anchorMin((app::RectTransform*)objectTransform, NULL);
}

void RectTransformSetPivot(app::GameObject* object, tem::Vector3 pivot)
{
	app::Transform* objectTransform = app::GameObject_get_transform((app::GameObject*)object, NULL);
	app::Vector2* newPivot = (app::Vector2*)il2cpp_object_new((Il2CppClass*)(*app::Vector2__TypeInfo));
	newPivot->x = pivot.X;
	newPivot->y = pivot.Y;
	app::RectTransform_set_pivot((app::RectTransform*)objectTransform, *newPivot, NULL);
}

app::Vector2 RectTransformGetPivot(app::GameObject* object)
{
	app::Transform* objectTransform = app::GameObject_get_transform((app::GameObject*)object, NULL);
	return app::RectTransform_get_pivot((app::RectTransform*)objectTransform, NULL);
}

void RectTransformSetWidthHeight(app::GameObject* object, float width, float height)
{
	app::Transform* objectTransform = app::GameObject_get_transform((app::GameObject*)object, NULL);
	app::RectTransform_SetSizeWithCurrentAnchors((app::RectTransform*)objectTransform, app::RectTransform_Axis__Enum::RectTransform_Axis__Enum_Vertical, height, NULL);
	app::RectTransform_SetSizeWithCurrentAnchors((app::RectTransform*)objectTransform, app::RectTransform_Axis__Enum::RectTransform_Axis__Enum_Horizontal, width, NULL);
	app::Rect rect = app::RectTransform_get_rect((app::RectTransform*)objectTransform, NULL);
	app::Rect* rectP = &rect;
	rectP->m_Height = height;
	rectP->m_Width = width;
}

void RectTransformSetSizeDelta(app::GameObject* object, float width, float height)
{
	app::Transform* objectTransform = app::GameObject_get_transform((app::GameObject*)object, NULL);
	app::RectTransform_set_sizeDelta((app::RectTransform*)objectTransform, ToVector2(width, height), NULL);
}

app::Vector2 RectTransformGetSizeDelta(app::GameObject* object)
{
	app::Transform* objectTransform = app::GameObject_get_transform((app::GameObject*)object, NULL);
	return app::RectTransform_get_sizeDelta((app::RectTransform*)objectTransform, NULL);
}

//"Hidden/UberShader/D26F57B95BEC7C085767DAC7B567E5F4" shader that works, cant handle black colors and always looks transparent
//Hidden/ColliderPreviewShader good for colors, but no black and always looks transparent
//Hidden/UberShader/105297F2E11B21A8CBB22D0A6B734A5C can have grayscale but near impossible to have colors
app::Material* CreateNewMaterial(std::string shader)
{
	app::String* standardMatS = string_new(shader.data());
	app::Shader* standardShader = app::Shader_Find(standardMatS, NULL);
	app::Material* newMaterial = (app::Material*)il2cpp_object_new((Il2CppClass*)(*app::Material__TypeInfo));
	app::Material__ctor(newMaterial, standardShader, NULL);
	app::Color newColor = app::Color();
	newColor.a = 0.0f, newColor.b = 1.0f, newColor.g = 1.0f, newColor.r = 1.0f;
	app::Material_set_color(newMaterial, newColor, NULL);

	return newMaterial;
}

void MeshRendererSetColor(app::GameObject* object, app::Color color)
{
	app::Type* type = GetType("UnityEngine", "MeshRenderer");
	app::MeshRenderer* meshRenderer = (app::MeshRenderer*)app::GameObject_GetComponent(object, type, NULL);

	if (meshRenderer == nullptr)
		meshRenderer = (app::MeshRenderer*)app::GameObject_GetComponentInChildren(object, type, true, NULL);

	if (meshRenderer != nullptr)
	{
		app::Material* material = app::Renderer_GetMaterial((app::Renderer*)meshRenderer, NULL);

		if (material != nullptr)
			app::Material_set_color(material, color, NULL);
	}
}

app::Vector2 ToVector2(const float x, const float y)
{
	auto vector2Class = GetClass<>("UnityEngine", "Vector2");
	app::Vector2* vector2 = (app::Vector2*)il2cpp_object_new((Il2CppClass*)vector2Class);
	vector2->x = x;
	vector2->y = y;
	return *vector2;
}