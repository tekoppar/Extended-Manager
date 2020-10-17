#pragma once

#include "../HelperClasses.h"
#include "AreaMapManager.h"

#ifndef _MANAGERDEF_H
#define _MANAGERDEF_H

extern app::ScenesManager* sceneManager;
extern AreaMapManager areaMapManager;

app::String* string_new(const char* str);

app::GameObject* GetSceneByName(std::string sceneToFind);

app::GameObject* GetSceneByNameAll(std::string sceneToFind);

bool IsSceneLoadedByName(std::string sceneToFind);

app::GameObject* PreloadSceneByName(std::string sceneToPreload);

app::GameObject* EnableSceneByName(std::string sceneToPreload);

app::GameObject* GetComponentByScenePath(std::string sceneName, std::vector<std::string> scenePath);

//template<typename Return = app::Object*>
//Return* GetObjectByType(std::string Namespace, std::string Name);

void DrawLine(app::Texture2D* tex, int x0, int y0, int x1, int y1, app::Color color);

app::Component_1* GetComponentByTypeInChildren(app::GameObject* object, std::string Namespace, std::string name);

app::Component_1* GetComponentByType(app::GameObject* object, std::string Namespace, std::string Name);

app::GameObject* CreateNewCanvas();

void FillPixels(app::Texture2D* tex, int x, int y, app::Color color);

void TransformSetScale(app::GameObject* object, tem::Vector3 scale);

tem::Vector3 TransformGetScale(app::GameObject* object);

void TransformSetPosition(app::GameObject* object, tem::Vector3 position);

app::Vector3 TransformGetPosition(app::GameObject* object);

void TransformSetLocalPosition(app::GameObject* object, tem::Vector3 position);

void TransformSetRotation(app::GameObject* object, tem::Vector3 rotation);

void TransformSetParent(app::GameObject* object, app::GameObject* parent);

app::GameObject* TransformGetParent(app::GameObject* object);

void TransformSetParentFromObject(app::GameObject* object, app::GameObject* child);

void RectTransformSetSize(app::GameObject* object, tem::Vector3 size);

void RectTransformSetAnchoredPosition(app::GameObject* object, tem::Vector3 anchor);

void RectTransformSetMinMax(app::GameObject* object, tem::Vector3 min, tem::Vector3 max);

app::Vector2 RectTransformGetMax(app::GameObject* object);

app::Vector2 RectTransformGetMin(app::GameObject* object);

void RectTransformSetPivot(app::GameObject* object, tem::Vector3 pivot);

app::Vector2 RectTransformGetPivot(app::GameObject* object);

void RectTransformSetWidthHeight(app::GameObject* object, float width, float height);

//"Hidden/UberShader/D26F57B95BEC7C085767DAC7B567E5F4" shader that works, cant handle black colors and always looks transparent
//Hidden/ColliderPreviewShader good for colors, but no black and always looks transparent
//Hidden/UberShader/105297F2E11B21A8CBB22D0A6B734A5C can have grayscale but near impossible to have colors
app::Material* CreateNewMaterial(std::string shader = "Hidden/UberShader/105297F2E11B21A8CBB22D0A6B734A5C");

void MeshRendererSetColor(app::GameObject* object, app::Color color);

#endif