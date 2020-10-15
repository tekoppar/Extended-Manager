#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include "Adresses.h"
#include "detours.h"

#include "StringUtils.h"

#include "ManagerDef.h"
#include "GraphDrawer.h"

#include "DebugDrawer.h"

void DebugDrawer::CleanUp()
{
	for (auto& object : debugObjects)
	{
		app::Object_1_Destroy_1((app::Object_1*)object, NULL);
	}

	debugObjects.clear();

	debugTexture = nullptr;
	debugMaterial = nullptr;
}

void DebugDrawer::SetupTexture(app::Color color, tem::Vector3 position) 
{
	app::String* debugParentName = string_new("DebugCollider");
	app::GameObject* debugParent = (app::GameObject*)il2cpp_object_new((Il2CppClass*)app::GameObject__TypeInfo);
	app::GameObject__ctor(debugParent, debugParentName, NULL);

	debugMaterial = CreateNewMaterial("Hidden/UberShader/4B897D76B847170D884884FBA5CEBC13");// CreateNewMaterial("Hidden/UberShader/4B897D76B847170D884884FBA5CEBC13");// "Hidden/UberShader/4B897D76B847170D884884FBA5CEBC13");// "Hidden/UberShader/E48C37CFA39B1500F0D8A6A5D0B46307");
	debugTexture = (app::Texture2D*)il2cpp_object_new((Il2CppClass*)app::Texture2D__TypeInfo);
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

	app::Material_SetColor(debugMaterial, TextureName1, graphColors.Grey, NULL);
	app::Material_SetTexture(debugMaterial, TextureName, (app::Texture*)debugTexture, NULL);
	app::Material_set_mainTexture(debugMaterial, (app::Texture*)debugTexture, NULL);

	app::String* debugName = string_new("Race Checkpoint");
	app::GameObject* debugObject = app::GameObject_CreatePrimitive(app::PrimitiveType__Enum_Cube, NULL);
	app::Object_1_set_name((app::Object_1*)debugObject, debugName, NULL);

	app::BoxCollider* boxCollider = (app::BoxCollider*)GetComponentByType(debugObject, "UnityEngine", "BoxCollider");
	app::Object_1_Destroy_1((app::Object_1*)boxCollider, NULL);
	app::MeshRenderer* meshRenderer = (app::MeshRenderer*)GetComponentByType(debugObject, "UnityEngine", "MeshRenderer");

	app::Renderer_SetMaterial((app::Renderer*)meshRenderer, debugMaterial, NULL);
	app::Renderer_set_sortingOrder((app::Renderer*)meshRenderer, 32767, NULL);
	app::Material_set_renderQueue(debugMaterial, 0, NULL);

	TransformSetScale(debugObject, tem::Vector3(3, 15, 1));
	TransformSetParent(debugObject, debugParent);
	//TransformSetRotation(debugObject, tem::Vector3(-90, 0, 0));
	TransformSetPosition(debugParent, tem::Vector3(0, 15 / 2, 0) + position);

	debugObjects.push_back(debugObject);
}

app::GameObject* DebugDrawer::CreateDebugObject(app::Color color, tem::Vector3 position)
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

	app::Material_SetColor(debugMaterial, TextureName1, graphColors.Grey, NULL);
	app::Material_SetTexture(debugMaterial, TextureName, (app::Texture*)debugTexture, NULL);
	app::Material_set_mainTexture(debugMaterial, (app::Texture*)debugTexture, NULL);

	app::String* debugName = string_new("Race Checkpoint");
	app::GameObject* debugObject = app::GameObject_CreatePrimitive(app::PrimitiveType__Enum::PrimitiveType__Enum_Cube, NULL);
	app::Object_1_set_name((app::Object_1*)debugObject, debugName, NULL);

	app::BoxCollider* boxCollider = (app::BoxCollider*)GetComponentByType(debugObject, "UnityEngine", "BoxCollider");
	app::Object_1_Destroy_1((app::Object_1*)boxCollider, NULL);
	app::MeshRenderer* meshRenderer = (app::MeshRenderer*)GetComponentByType(debugObject, "UnityEngine", "MeshRenderer");

	app::Renderer_SetMaterial((app::Renderer*)meshRenderer, debugMaterial, NULL);
	app::Renderer_set_sortingOrder((app::Renderer*)meshRenderer, 32767, NULL);
	app::Material_set_renderQueue(debugMaterial, 0, NULL);

	TransformSetScale(debugObject, tem::Vector3(3, 15, 1));
	TransformSetParent(debugObject, debugParent);
	//TransformSetRotation(debugObject, tem::Vector3(-90, 0, 0));
	TransformSetPosition(debugParent, tem::Vector3(0, 15 / 2, 0) + position);

	return debugParent;
}