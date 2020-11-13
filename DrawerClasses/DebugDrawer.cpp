#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include "Adresses.h"
#include "detours.h"

#include "StringUtils.h"

#include "ManagerDef.h"
#include "GraphDrawer.h"

#include "DebugDrawer.h"

app::GameObject* DebugDrawer::masterDebug = nullptr;
bool DebugDrawer::toggleDebugObjects = true;
bool DebugDrawer::HasCreatedResources = false;
std::vector<app::GameObject*> DebugDrawer::debugObjects = std::vector<app::GameObject*>();

DebugDrawer::DebugDrawer()
{
}

void DebugDrawer::Initialize()
{
	app::String* raceBodyName = string_new("RaceBase");
	DebugDrawer::masterDebug = (app::GameObject*)il2cpp_object_new((Il2CppClass*)app::GameObject__TypeInfo);
	app::GameObject__ctor(DebugDrawer::masterDebug, raceBodyName, NULL);
	TransformSetPosition(DebugDrawer::masterDebug, tem::Vector3(0, 0, 0));
}

void DebugDrawer::ToggleDebugObjects()
{
	app::GameObject_SetMoonHiddenToHierarchy(DebugDrawer::masterDebug, DebugDrawer::toggleDebugObjects, NULL);

	for (auto& debug : DebugDrawer::debugObjects)
	{
		app::GameObject_SetMoonHiddenToHierarchy(debug, DebugDrawer::toggleDebugObjects, NULL);
	}
}

void DebugDrawer::CleanUp()
{
	for (auto& object : debugObjects)
	{
		if (object != nullptr)
		{
			app::Object_1_Destroy_1((app::Object_1*)object, NULL);
			object = nullptr;
		}
	}

	debugObjects.clear();

	if (HasCreatedResources == true)
	{
		if (debugTexture != nullptr && debugTexture->fields._._.m_CachedPtr != nullptr)
			app::Object_1_Destroy_1((app::Object_1*)debugTexture, NULL);
		debugTexture = nullptr;
		if ((unsigned long long)&debugMaterial > 0x10000 && debugMaterial != nullptr && debugMaterial->fields._.m_CachedPtr != nullptr)
			app::Object_1_Destroy_1((app::Object_1*)debugMaterial, NULL);
		debugMaterial = nullptr;
	}

	app::Object_1_Destroy_1((app::Object_1*)DebugDrawer::masterDebug, NULL);
	DebugDrawer::masterDebug = nullptr;
}

void DebugDrawer::SetupTexture(app::Color color, tem::Vector3 position) 
{
	app::String* debugParentName = string_new("DebugCollider");
	app::GameObject* debugParent = (app::GameObject*)il2cpp_object_new((Il2CppClass*)app::GameObject__TypeInfo);
	app::GameObject__ctor(debugParent, debugParentName, NULL);

	debugMaterial = CreateNewMaterial("Hidden/UberShader/4B897D76B847170D884884FBA5CEBC13");// CreateNewMaterial("Hidden/UberShader/4B897D76B847170D884884FBA5CEBC13");// "Hidden/UberShader/4B897D76B847170D884884FBA5CEBC13");// "Hidden/UberShader/E48C37CFA39B1500F0D8A6A5D0B46307");
	debugTexture = (app::Texture2D*)il2cpp_object_new((Il2CppClass*)app::Texture2D__TypeInfo);
	HasCreatedResources = true;
	app::Texture2D__ctor_3(debugTexture, 1, 1, app::TextureFormat__Enum::TextureFormat__Enum_RGBA32, false, false, NULL);
	app::Texture_set_wrapMode((app::Texture*)debugTexture, app::TextureWrapMode__Enum::TextureWrapMode__Enum_Repeat, NULL);
	app::Texture_set_filterMode((app::Texture*)debugTexture, app::FilterMode__Enum::FilterMode__Enum_Point, NULL);

	app::Color colorMod = color;
	colorMod.a = 0.5;
	FillPixels(debugTexture, 1, 1, colorMod);
	app::Texture2D_Apply_1(debugTexture, true, NULL);

	FillPixels(debugTexture, 1, 1, colorMod);
	app::Texture2D_Apply_1(debugTexture, true, NULL);

	app::String* TextureName = string_new("_MainTex");
	app::String* TextureName1 = string_new("_Color");

	app::Material_SetColor(debugMaterial, TextureName1, GraphColors::Grey, NULL);
	app::Material_SetTexture(debugMaterial, TextureName, (app::Texture*)debugTexture, NULL);
	app::Material_set_mainTexture(debugMaterial, (app::Texture*)debugTexture, NULL);

	app::String* debugName = string_new("Race Checkpoint");
	app::GameObject* debugObject = app::GameObject_CreatePrimitive(app::PrimitiveType__Enum_Cube, NULL);
	app::Object_1_set_name((app::Object_1*)debugObject, debugName, NULL);

	app::BoxCollider* boxCollider = (app::BoxCollider*)GetComponentByType(debugObject, "UnityEngine", "BoxCollider");
	app::Object_1_Destroy_1((app::Object_1*)boxCollider, NULL);
	app::Collider_set_isTrigger((app::Collider*)boxCollider, true, NULL);

	app::MeshRenderer* meshRenderer = (app::MeshRenderer*)GetComponentByType(debugObject, "UnityEngine", "MeshRenderer");

	app::Renderer_SetMaterial((app::Renderer*)meshRenderer, debugMaterial, NULL);
	app::Renderer_set_sortingOrder((app::Renderer*)meshRenderer, 30842, NULL);
	app::Renderer_set_renderingLayerMask((app::Renderer*)meshRenderer, 4102, NULL); //xxx0 nothing, xxx1 transparent, xxx2 full color, xxx3 full color shades everything inside
	app::Renderer_set_moonOffsetZ((app::Renderer*)meshRenderer, 0.0f, NULL);
	app::Material_set_renderQueue(debugMaterial, 2000, NULL);

	TransformSetParent(debugParent, DebugDrawer::masterDebug);
	TransformSetScale(debugObject, tem::Vector3(3, 15, 1));
	TransformSetParent(debugObject, debugParent);
	//TransformSetRotation(debugObject, tem::Vector3(-90, 0, 0));
	TransformSetPosition(debugParent, position); //tem::Vector3(0, 15 / 2, 0) + 
	TransformSetLocalPosition(debugObject, tem::Vector3(3/2 * -1, 15 / 2, 0));

	DebugDrawer::debugObjects.push_back(debugParent);
	DebugDrawer::ToggleDebugObjects();
}

app::GameObject* DebugDrawer::CreateDebugObjectStatic(app::Color color, tem::Vector3 position)
{
	app::String* debugParentName = string_new("DebugCollider");
	app::GameObject* debugParent = (app::GameObject*)il2cpp_object_new((Il2CppClass*)app::GameObject__TypeInfo);
	app::GameObject__ctor(debugParent, debugParentName, NULL);

	app::Material* debugMaterial = CreateNewMaterial("Hidden/UberShader/4B897D76B847170D884884FBA5CEBC13");// CreateNewMaterial("Hidden/UberShader/4B897D76B847170D884884FBA5CEBC13");// "Hidden/UberShader/4B897D76B847170D884884FBA5CEBC13");// "Hidden/UberShader/E48C37CFA39B1500F0D8A6A5D0B46307");
	app::Texture2D* debugTexture = (app::Texture2D*)il2cpp_object_new((Il2CppClass*)app::Texture2D__TypeInfo);
	app::Texture2D__ctor_3(debugTexture, 1, 1, app::TextureFormat__Enum::TextureFormat__Enum_RGBA32, false, false, NULL);
	app::Texture_set_wrapMode((app::Texture*)debugTexture, app::TextureWrapMode__Enum::TextureWrapMode__Enum_Repeat, NULL);
	app::Texture_set_filterMode((app::Texture*)debugTexture, app::FilterMode__Enum::FilterMode__Enum_Point, NULL);

	app::Color colorMod = color;
	colorMod.a = 0.5;
	FillPixels(debugTexture, 1, 1, colorMod);
	app::Texture2D_Apply_1(debugTexture, true, NULL);

	app::String* TextureName = string_new("_MainTex");
	app::String* TextureName1 = string_new("_Color");

	app::Material_SetColor(debugMaterial, TextureName1, GraphColors::Grey, NULL);
	app::Material_SetTexture(debugMaterial, TextureName, (app::Texture*)debugTexture, NULL);
	app::Material_set_mainTexture(debugMaterial, (app::Texture*)debugTexture, NULL);

	app::String* debugName = string_new("Race Checkpoint");
	app::GameObject* debugObject = app::GameObject_CreatePrimitive(app::PrimitiveType__Enum::PrimitiveType__Enum_Cube, NULL);
	app::Object_1_set_name((app::Object_1*)debugObject, debugName, NULL);

	app::BoxCollider* boxCollider = (app::BoxCollider*)GetComponentByType(debugObject, "UnityEngine", "BoxCollider");
	app::Object_1_Destroy_1((app::Object_1*)boxCollider, NULL);

	app::MeshRenderer* meshRenderer = (app::MeshRenderer*)GetComponentByType(debugObject, "UnityEngine", "MeshRenderer");

	app::Renderer_SetMaterial((app::Renderer*)meshRenderer, debugMaterial, NULL);
	app::Renderer_set_sortingOrder((app::Renderer*)meshRenderer, 30842, NULL);
	app::Renderer_set_renderingLayerMask((app::Renderer*)meshRenderer, 4102, NULL); //xxx0 nothing, xxx1 transparent, xxx2 full color, xxx3 full color shades everything inside
	app::Renderer_set_moonOffsetZ((app::Renderer*)meshRenderer, 0.0f, NULL);
	app::Material_set_renderQueue(debugMaterial, 2000, NULL);

	TransformSetParent(debugParent, DebugDrawer::masterDebug);
	TransformSetScale(debugObject, tem::Vector3(3, 15, 1));
	TransformSetParent(debugObject, debugParent);
	//TransformSetRotation(debugObject, tem::Vector3(-90, 0, 0));
	TransformSetPosition(debugParent, position); //tem::Vector3(0, 15 / 2, 0) + 
	TransformSetLocalPosition(debugObject, tem::Vector3(3/2 * -1, 15 / 2, 0));
	
	DebugDrawer::debugObjects.push_back(debugParent);
	DebugDrawer::ToggleDebugObjects();

	return debugParent;
}

app::GameObject* DebugDrawer::CreateDebugObject(app::Color color, tem::Vector3 position, tem::Vector3 scale)
{
	app::String* debugParentName = string_new("DebugCollider");
	app::GameObject* debugParent = (app::GameObject*)il2cpp_object_new((Il2CppClass*)app::GameObject__TypeInfo);
	app::GameObject__ctor(debugParent, debugParentName, NULL);

	app::Material* debugMaterial = CreateNewMaterial("Hidden/UberShader/4B897D76B847170D884884FBA5CEBC13");// CreateNewMaterial("Hidden/UberShader/4B897D76B847170D884884FBA5CEBC13");// "Hidden/UberShader/4B897D76B847170D884884FBA5CEBC13");// "Hidden/UberShader/E48C37CFA39B1500F0D8A6A5D0B46307");
	app::Texture2D* debugTexture = (app::Texture2D*)il2cpp_object_new((Il2CppClass*)app::Texture2D__TypeInfo);
	app::Texture2D__ctor_3(debugTexture, 1, 1, app::TextureFormat__Enum::TextureFormat__Enum_RGBA32, false, false, NULL);
	app::Texture_set_wrapMode((app::Texture*)debugTexture, app::TextureWrapMode__Enum::TextureWrapMode__Enum_Repeat, NULL);
	app::Texture_set_filterMode((app::Texture*)debugTexture, app::FilterMode__Enum::FilterMode__Enum_Point, NULL);

	app::Color colorMod = color;
	colorMod.a = 0.5;
	FillPixels(debugTexture, 1, 1, colorMod);
	app::Texture2D_Apply_1(debugTexture, true, NULL);

	app::String* TextureName = string_new("_MainTex");
	app::String* TextureName1 = string_new("_Color");

	app::Material_SetColor(debugMaterial, TextureName1, GraphColors::Grey, NULL);
	app::Material_SetTexture(debugMaterial, TextureName, (app::Texture*)debugTexture, NULL);
	app::Material_set_mainTexture(debugMaterial, (app::Texture*)debugTexture, NULL);

	app::String* debugName = string_new("Race Checkpoint");
	app::GameObject* debugObject = app::GameObject_CreatePrimitive(app::PrimitiveType__Enum::PrimitiveType__Enum_Cube, NULL);
	app::Object_1_set_name((app::Object_1*)debugObject, debugName, NULL);

	app::BoxCollider* boxCollider = (app::BoxCollider*)GetComponentByType(debugObject, "UnityEngine", "BoxCollider");
	app::Object_1_Destroy_1((app::Object_1*)boxCollider, NULL);
	
	app::MeshRenderer* meshRenderer = (app::MeshRenderer*)GetComponentByType(debugObject, "UnityEngine", "MeshRenderer");

	app::Renderer_SetMaterial((app::Renderer*)meshRenderer, debugMaterial, NULL);
	app::Renderer_set_sortingOrder((app::Renderer*)meshRenderer, 30842, NULL);
	app::Renderer_set_renderingLayerMask((app::Renderer*)meshRenderer, 4102, NULL); //xxx0 nothing, xxx1 transparent, xxx2 full color, xxx3 full color shades everything inside
	app::Renderer_set_moonOffsetZ((app::Renderer*)meshRenderer, 0.0f, NULL);
	app::Material_set_renderQueue(debugMaterial, 2000, NULL);

	TransformSetParent(debugParent, DebugDrawer::masterDebug);
	TransformSetScale(debugObject, tem::Vector3(1, 1, 1));
	TransformSetParent(debugObject, debugParent);
	//TransformSetRotation(debugObject, tem::Vector3(-90, 0, 0));
	TransformSetPosition(debugParent, position); //tem::Vector3(0, 15 / 2, 0) + 
	TransformSetLocalPosition(debugObject, tem::Vector3(scale.X / 2 * -1, scale.Y / 2, 0));
	
	DebugDrawer::debugObjects.push_back(debugParent);
	DebugDrawer::ToggleDebugObjects();

	return debugParent;
}

app::GameObject* DebugDrawer::CreateDebugObjectDetached(app::Color color, tem::Vector3 position, tem::Vector3 scale)
{
	app::String* debugParentName = string_new("DebugCollider");
	app::GameObject* debugParent = (app::GameObject*)il2cpp_object_new((Il2CppClass*)app::GameObject__TypeInfo);
	app::GameObject__ctor(debugParent, debugParentName, NULL);

	app::Material* debugMaterial = CreateNewMaterial("Hidden/ColliderPreviewShader");// "Hidden/UberShader/4B897D76B847170D884884FBA5CEBC13");// CreateNewMaterial("Hidden/UberShader/4B897D76B847170D884884FBA5CEBC13");// "Hidden/UberShader/4B897D76B847170D884884FBA5CEBC13");// "Hidden/UberShader/E48C37CFA39B1500F0D8A6A5D0B46307");
	app::Texture2D* debugTexture = (app::Texture2D*)il2cpp_object_new((Il2CppClass*)app::Texture2D__TypeInfo);
	app::Texture2D__ctor_3(debugTexture, 1, 1, app::TextureFormat__Enum::TextureFormat__Enum_RGBA32, false, false, NULL);
	app::Texture_set_wrapMode((app::Texture*)debugTexture, app::TextureWrapMode__Enum::TextureWrapMode__Enum_Repeat, NULL);
	app::Texture_set_filterMode((app::Texture*)debugTexture, app::FilterMode__Enum::FilterMode__Enum_Point, NULL);

	app::Color colorMod = color;
	colorMod.a = 0.25f;
	FillPixels(debugTexture, 1, 1, colorMod);
	app::Texture2D_Apply_1(debugTexture, true, NULL);

	app::String* TextureName = string_new("_MainTex");
	app::String* TextureName1 = string_new("_Color");

	app::Material_SetColor(debugMaterial, TextureName1, color, NULL);
	app::Material_SetTexture(debugMaterial, TextureName, (app::Texture*)debugTexture, NULL);
	app::Material_set_mainTexture(debugMaterial, (app::Texture*)debugTexture, NULL);

	app::String* debugName = string_new("Race Checkpoint");
	app::GameObject* debugObject = app::GameObject_CreatePrimitive(app::PrimitiveType__Enum::PrimitiveType__Enum_Cube, NULL);
	app::Object_1_set_name((app::Object_1*)debugObject, debugName, NULL);

	app::BoxCollider* boxCollider = (app::BoxCollider*)GetComponentByType(debugObject, "UnityEngine", "BoxCollider");
	app::Object_1_Destroy_1((app::Object_1*)boxCollider, NULL);

	app::MeshRenderer* meshRenderer = (app::MeshRenderer*)GetComponentByType(debugObject, "UnityEngine", "MeshRenderer");

	app::Renderer_SetMaterial((app::Renderer*)meshRenderer, debugMaterial, NULL);
	app::Renderer_set_sortingOrder((app::Renderer*)meshRenderer, 30842, NULL);
	app::Renderer_set_renderingLayerMask((app::Renderer*)meshRenderer, 4102, NULL); //xxx0 nothing, xxx1 transparent, xxx2 full color, xxx3 full color shades everything inside
	app::Renderer_set_moonOffsetZ((app::Renderer*)meshRenderer, 0.0f, NULL);
	app::Material_set_renderQueue(debugMaterial, 2000, NULL);

	TransformSetScale(debugObject, tem::Vector3(1,1,1));
	TransformSetParent(debugObject, debugParent);
	//TransformSetRotation(debugObject, tem::Vector3(-90, 0, 0));
	TransformSetPosition(debugParent, position); //tem::Vector3(0, 15 / 2, 0) + 
	TransformSetLocalPosition(debugObject, tem::Vector3(scale.X / 2 * -1, scale.Y / 2, 0));

	DebugDrawer::debugObjects.push_back(debugParent);

	return debugParent;
}