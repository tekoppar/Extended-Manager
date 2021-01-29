#pragma once

#include "Vector3.h"
#include "Rect.h"
#include "Quaternion.h"
#include "AreaMapManager.h"
#include "TemUser.h"
#include "tem.h"
#include "TemLogger.h"
#include "Global.h"

#ifndef _MANAGERDEF_H
#define _MANAGERDEF_H

extern std::string ManagerPath;
extern app::ScenesManager* sceneManager;
extern AreaMapManager areaMapManager;

class MDV : public Global {
public:
	static TemUser User;

	static std::vector<Global*> AllObjectsToCallUpdate;
	static std::vector<std::string> MessageToWrite;
	static app::GameController* MoonGameController;
	static app::GameplayCamera* SeinGameplayCamera;
	static app::Camera* MoonCamera;
	static app::GameWorld* MoonGameWorld;
	static app::SeinCharacter* MoonSein;
	static app::SeinPlayAnimationController* SeinPlayAnimationController;
	static app::AreaMapUI* AreaMapUI;
	static app::GameObject* SelectedObject;
	static app::GameObject* PreviewObject;
	static bool CanCallMethods;
	static std::vector<uint8_t> GCHandles;

	static void ValidatePointers();
};

app::String* string_new(const char* str);

app::GameObject* GetSceneByName(std::string sceneToFind);
app::GameObject* GetSceneByNameAll(std::string sceneToFind);
bool IsSceneLoadedByName(std::string sceneToFind);
app::GameObject* PreloadSceneByName(std::string sceneToPreload);
app::GameObject* EnableSceneByName(std::string sceneToPreload);

app::GameObject* GetComponentByScenePath(std::string sceneName, std::vector<std::string> scenePath);
app::GameObject* GetComponentByPath(app::GameObject* object, std::vector<std::string> scenePath);
std::vector<app::GameObject*> GetComponentsByName(app::GameObject* object, std::string scenePath);
app::GameObject* GetComponentByName(app::GameObject* object, std::string componentName);
app::GameObject* GetComponentByNameContainsType(app::GameObject* object, std::string componentName, app::Type* type);
std::vector<app::GameObject*> GetChildrenByName(app::GameObject* parent, std::string name);

//template<typename Return = app::Object*>
//Return* GetObjectByType(std::string Namespace, std::string Name);

void DrawLine(app::Texture2D* tex, int x0, int y0, int x1, int y1, app::Color color);

app::Component_1* GetComponentByTypeInChildren(app::GameObject* object, std::string Namespace, std::string name);
std::vector<app::Component_1*> GetComponentsByTypeInChildren(app::GameObject* object, std::string Namespace, std::string Name);
app::Component_1* GetComponentByType(app::GameObject* object, std::string Namespace, std::string Name);

app::GameObject* CreateNewCanvas();

void FillPixels(app::Texture2D* tex, int x, int y, app::Color color);

void TransformSetScale(app::GameObject* object, tem::Vector3 scale);
tem::Vector3 TransformGetScale(app::GameObject* object);
void TransformSetPosition(app::GameObject* object, tem::Vector3 position);
app::Vector3 TransformGetPosition(app::GameObject* object);
void TransformSetLocalPosition(app::GameObject* object, tem::Vector3 position);
tem::Vector3 TransformGetLocalPosition(app::GameObject* object);
void TransformSetRotation(app::GameObject* object, tem::Vector3 rotation);
void TransformSetEulerAngles(app::GameObject* object, tem::Vector3 angles);
tem::Vector3 TransformGetEulerAngles(app::GameObject* object);
tem::Vector3 TransformGetRotation(app::GameObject* object);
void TransformSetQuatRotation(app::GameObject* object, tem::Vector3 eulersAngles);
void TransformSetParent(app::GameObject* object, app::GameObject* parent, bool setAsLastSibling = false);
app::GameObject* TransformGetParent(app::GameObject* object);
void TransformSetParentFromObject(app::GameObject* object, app::GameObject* child);
int TransformGetObjectIndex(app::GameObject* object);
void RectTransformSetSize(app::GameObject* object, tem::Vector2 size);
void RectTransformSetAnchoredPosition(app::GameObject* object, tem::Vector2 anchor);
void RectTransformSetMinMax(app::GameObject* object, tem::Vector2 min, tem::Vector2 max);
app::Vector2 RectTransformGetMax(app::GameObject* object);
app::Vector2 RectTransformGetMin(app::GameObject* object);
void RectTransformSetPivot(app::GameObject* object, tem::Vector2 pivot);
app::Vector2 RectTransformGetPivot(app::GameObject* object);
void RectTransformSetWidthHeight(app::GameObject* object, float width, float height);
void RectTransformSetSizeDelta(app::GameObject* object, float width, float height);
app::Vector2 RectTransformGetSizeDelta(app::GameObject* object);

//"Hidden/UberShader/D26F57B95BEC7C085767DAC7B567E5F4" shader that works, cant handle black colors and always looks transparent
//Hidden/ColliderPreviewShader good for colors, but no black and always looks transparent
//Hidden/UberShader/105297F2E11B21A8CBB22D0A6B734A5C can have grayscale but near impossible to have colors
app::Material* CreateNewMaterial(std::string shader = "Hidden/UberShader/105297F2E11B21A8CBB22D0A6B734A5C");
void MeshRendererSetColor(app::GameObject* object, app::Color color);

app::Vector2 ToVector2(const float x, const float y);

void FlipMeshNormals(app::Mesh* mesh);

#endif