#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <filesystem>

#include "StringUtils.h"
#include "ManagerDef.h"
#include "UberStateManager.h"
#include "SeinVisualEditor.h"
#include "Tem.h"

#include "OriVisual.h"

void OriVisualSettings::SetOriVisuals(OriVisualSettings oriSettings)
{
	std::string textureTemp = "";
	if (oriSettings.TexturePath != "NONE" && std::filesystem::exists(oriSettings.TexturePath) == true && std::filesystem::is_regular_file(oriSettings.TexturePath) == true)
		textureTemp = sutil::readFile(oriSettings.TexturePath);
	else if (oriSettings.TexturePath != "NONE" && std::filesystem::exists(ManagerPath + oriSettings.TexturePath) == true && std::filesystem::is_regular_file(ManagerPath + oriSettings.TexturePath) == true)
		textureTemp = sutil::readFile(ManagerPath + oriSettings.TexturePath);

	app::String* TextureName = string_new("_MainTex");
	app::String* TextureName1 = string_new("_Color");
	app::String* EmiColor = string_new("_EmissivityColor");
	app::Type* skinnedMeshRendererType = GetType("UnityEngine", "SkinnedMeshRenderer");
	app::Type* byteArrType = GetTypeFromClass((Il2CppClass*)(*app::Byte__Array__TypeInfo));
	app::GameObject* gamyobj = app::Component_1_get_gameObject((app::Component_1*)MDV::MoonSein, NULL);

	std::vector<std::string> scenePath = { "ori3D", "mirrorHolder", "rigHolder", "oriRig", "Model_GRP", "body_MDL" };
	std::vector<std::string> sceneFacePath = { "ori3D", "mirrorHolder", "rigHolder", "oriRig", "Model_GRP", "faceBody_MDL" };
	app::GameObject* oriModel = GetComponentByPath(gamyobj, scenePath);
	app::GameObject* oriFaceModel = GetComponentByPath(gamyobj, sceneFacePath);
	app::Component_1__Array* componentsRenderers = app::GameObject_GetComponentsInChildren_1(oriModel, skinnedMeshRendererType, true, NULL);
	app::Component_1__Array* componentsFaceRenderers = app::GameObject_GetComponentsInChildren_1(oriFaceModel, skinnedMeshRendererType, true, NULL);
	if (componentsRenderers->vector[0] != nullptr && componentsFaceRenderers->vector[0] != nullptr)
	{
		app::SkinnedMeshRenderer* meshRenderer = (app::SkinnedMeshRenderer*)componentsRenderers->vector[0];
		app::Material* meshMat = app::Renderer_GetMaterial((app::Renderer*)meshRenderer, NULL);

		app::SkinnedMeshRenderer* meshFaceRenderer = (app::SkinnedMeshRenderer*)componentsFaceRenderers->vector[0];
		app::Material* meshFaceMat = app::Renderer_GetMaterial((app::Renderer*)meshFaceRenderer, NULL);

		app::Byte__Array* byteArr = (app::Byte__Array*)app::Array_CreateInstance_1(byteArrType, textureTemp.size(), NULL);

		app::Texture2D* debugTexture = nullptr;
		if (textureTemp != "")
		{
			for (int i = 0; i < textureTemp.size(); i++)
			{
				byteArr->vector[i] = textureTemp[i];
			}

			app::Texture* oriTexture = app::Material_get_mainTexture(meshMat, NULL);
			//int width = app::Texture_get_width(oriTexture, NULL);
			//int height = app::Texture_get_height(oriTexture, NULL);

			//debugTexture = (app::Texture2D*)il2cpp_object_new((Il2CppClass*)(*app::Texture2D__TypeInfo));
			//app::Texture2D__ctor_3(debugTexture, width, height, app::TextureFormat__Enum::TextureFormat__Enum_RGBA32, false, false, NULL);
			//app::String* newTextureName = string_new("CustomOriColor");
			//app::Object_1_SetName((app::Object_1*)debugTexture, newTextureName, NULL);
			//app::Texture_set_wrapMode((app::Texture*)debugTexture, app::TextureWrapMode__Enum::TextureWrapMode__Enum_Repeat, NULL);
			//app::Texture_set_filterMode((app::Texture*)debugTexture, app::FilterMode__Enum::FilterMode__Enum_Point, NULL);
			//app::Texture2D_LoadRawTextureData_1(debugTexture, byteArr, NULL);

			if (oriTexture != nullptr)
			{
				app::Texture2D* texture2D = (app::Texture2D*)oriTexture;
				int width = app::Texture_get_width(oriTexture, NULL);
				int height = app::Texture_get_height(oriTexture, NULL);
				int mipcount = app::Texture2D_get_mipmapCount(texture2D, NULL);
				app::FilterMode__Enum filter = app::Texture_get_filterMode(oriTexture, NULL);
				app::TextureWrapMode__Enum wrap = app::Texture_get_wrapMode(oriTexture, NULL);
				app::TextureFormat__Enum format = app::Texture2D_get_format(texture2D, NULL);
				app::ImageConversion_LoadImage_1((app::Texture2D*)oriTexture, byteArr, NULL);
				app::Texture2D_ApplyImpl((app::Texture2D*)oriTexture, true, true, NULL);
				//OriVisualEditor::OriTexture = *debugTexture;
				//OriVisualEditor::DefaultOriVisualSettings.OriTexture = app::Material_GetTexture(meshMat, TextureName, NULL);
				app::Material_SetTexture(meshMat, TextureName, (app::Texture*)oriTexture, NULL);
				app::Material_set_mainTexture(meshMat, (app::Texture*)oriTexture, NULL);

				//OriVisualEditor::DefaultOriVisualSettings.OriFaceTexture = app::Material_GetTexture(meshFaceMat, TextureName, NULL);
				app::Material_SetTexture(meshFaceMat, TextureName, (app::Texture*)oriTexture, NULL);
				app::Material_set_mainTexture(meshFaceMat, (app::Texture*)oriTexture, NULL);
			}
		}

		SeinVisualEditor::DefaultVisualSettings.OriVisualSettings.Ori = app::Material_GetColor(meshMat, TextureName1, NULL);
		app::Material_SetColor(meshMat, TextureName1, oriSettings.Ori.ToColor(), NULL);
		app::Material_SetColor(meshFaceMat, TextureName1, oriSettings.Ori.ToColor(), NULL);

		//app::Renderer_SetMaterial((app::Renderer*)meshRenderer, meshMat, NULL);
		//app::Renderer_SetMaterial((app::Renderer*)meshFaceRenderer, meshFaceMat, NULL);
	}

	std::vector<std::string> sceneEmiPath = { "ori3D", "mirrorHolder", "rigHolder", "oriRig", "Model_GRP", "body_emissivity_MDL" };
	app::GameObject* oriEmiModel = GetComponentByPath(gamyobj, sceneEmiPath);
	app::Component_1__Array* componentsEmiRenderers = app::GameObject_GetComponentsInChildren_1(oriEmiModel, skinnedMeshRendererType, true, NULL);
	if (componentsEmiRenderers->vector[0] != nullptr)
	{
		app::SkinnedMeshRenderer* meshEmiRenderer = (app::SkinnedMeshRenderer*)componentsEmiRenderers->vector[0];
		app::Material* meshEmiMat = app::Renderer_GetMaterial((app::Renderer*)meshEmiRenderer, NULL);
		SeinVisualEditor::DefaultVisualSettings.OriVisualSettings.OriGlow = app::Material_GetColor(meshEmiMat, EmiColor, NULL);
		app::Material_SetColor(meshEmiMat, EmiColor, oriSettings.OriGlow.ToColor(), NULL);
		//app::Renderer_SetMaterial((app::Renderer*)meshEmiRenderer, meshEmiMat, NULL);
		app::GameObject_SetMoonHiddenToHierarchy(oriEmiModel, oriSettings.HideGlow, NULL);
	}

	std::vector<std::string> sceneTrail = { "ori3D", "mirrorHolder", "rigHolder", "oriRig", "trails", "trail" };
	SeinVisualEditor::SetMeshRendererColor(gamyobj, sceneTrail, oriSettings.OriTrail);

	SeinVisualEditor::VisualSettings.OriVisualSettings = oriSettings;
	SeinVisualEditor::VisualSettingsUpdated.HasUpdatedOri = true;
}