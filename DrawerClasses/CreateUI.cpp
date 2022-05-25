#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <filesystem>

#include "ManagerDef.h"
#include "Vector4.h"
#include "GraphDrawer.h"

#include "CreateUI.h"

void TreeItemStruct::ExpandTree()
{
	app::GameObject_set_active(ChildrenTree, IsFolded, NULL);
	IsFolded = !IsFolded;
}

void DropdownHorizontal::ExpandDropdown()
{
	app::GameObject_set_active(DropdownChildren, IsFolded, NULL);
	IsFolded = !IsFolded;
}

std::vector<TemButton*> DrawUI::AllTemButtons = std::vector<TemButton*>();
std::vector<app::Texture2D*> DrawUI::AllTexture2D;
std::vector<std::string> DrawUI::AllTexture2DNames;

int DrawUI::FindTextureIndex(std::string name)
{
	for (int i = 0; i < AllTexture2DNames.size(); i++)
	{
		if (AllTexture2DNames[i] == name)
			return i;
	}

	return -1;
}

app::GameObject* DrawUI::EventSystem(const std::string& name)
{
	app::Type* type = GetType("UnityEngine.EventSystems", "EventSystem");
	app::Type* typeInput = GetType("UnityEngine.EventSystems", "StandaloneInputModule");
	app::GameObject* gameObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
	app::String* gameObjectname = string_new(name.data());
	app::GameObject__ctor(gameObject, gameObjectname, NULL);
	app::EventSystem* newObject = (app::EventSystem*)app::GameObject_AddComponent((app::GameObject*)gameObject, type, NULL);
	app::StandaloneInputModule* newObjectInput = (app::StandaloneInputModule*)app::GameObject_AddComponent((app::GameObject*)gameObject, typeInput, NULL);

	return gameObject;
}

app::GameObject* DrawUI::Image(const std::string& name, app::Material* material)
{
	app::Type* type = GetType("UnityEngine.UI", "Image");
	app::GameObject* gameObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
	app::String* gameObjectname = string_new(name.data());
	app::GameObject__ctor(gameObject, gameObjectname, NULL);
	app::Image* newObject = (app::Image*)app::GameObject_AddComponent((app::GameObject*)gameObject, type, NULL);
	app::Image_set_material(newObject, material, NULL);

	return gameObject;
}

app::GameObject* DrawUI::Selectable(const std::string& name)
{
	app::Type* selectableType = GetType("UnityEngine.UI", "Selectable");
	app::Type* imageType = GetType("UnityEngine.UI", "Image");
	app::Type* typeLayoutElement = GetType("UnityEngine.UI", "LayoutElement");
	app::GameObject* gameObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
	app::String* gameObjectname = string_new(name.data());
	app::GameObject__ctor(gameObject, gameObjectname, NULL);

	app::Image* imageObject = (app::Image*)app::GameObject_AddComponent((app::GameObject*)gameObject, imageType, NULL);
	app::Selectable* newObject = (app::Selectable*)app::GameObject_AddComponent((app::GameObject*)gameObject, selectableType, NULL);
	app::ColorBlock colors = app::ColorBlock();
	colors.m_ColorMultiplier = 1.2f;
	colors.m_FadeDuration = 0.1f;
	colors.m_DisabledColor = tem::Vector4(0.7f, 0.7f, 0.7f, 1.0f).ToColor();
	colors.m_HighlightedColor = tem::Vector4(0.8f, 0.8f, 0.8f, 1.0f).ToColor();
	colors.m_NormalColor = tem::Vector4(0.4f, 0.4f, 0.4f, 1.0f).ToColor();
	colors.m_PressedColor = tem::Vector4(1.0f, 1.0f, 1.0f, 1.0f).ToColor();
	app::Selectable_set_interactable(newObject, true, NULL);
	app::Selectable_set_colors(newObject, colors, NULL);
	app::Selectable__ctor(newObject, NULL);
	app::Selectable_set_colors(newObject, colors, NULL);
	//app::Selectable_set_image(newObject, imageObject, NULL);
	app::Selectable_set_targetGraphic(newObject, (app::Graphic*)imageObject, NULL);

	app::LayoutElement* newLayoutElement = (app::LayoutElement*)app::GameObject_AddComponent((app::GameObject*)gameObject, typeLayoutElement, NULL);
	app::LayoutElement_set_minHeight(newLayoutElement, 32, NULL);
	app::LayoutElement_set_minWidth(newLayoutElement, 32, NULL);

	return gameObject;
}

app::Texture2D* DrawUI::LoadImageFromPath(std::string path, int width, int height)
{
	std::string textureTemp = "";
	if (path != "" && std::filesystem::exists(path) == true && std::filesystem::is_regular_file(path) == true)
		textureTemp = sutil::readFile(path);
	else if (path != "" && std::filesystem::exists(ManagerPath + path) == true && std::filesystem::is_regular_file(ManagerPath + path) == true)
		textureTemp = sutil::readFile(ManagerPath + path);

	app::Type* byteArrType = GetTypeFromClass((Il2CppClass*)(*app::Byte__Array__TypeInfo));
	app::Byte__Array* byteArr = (app::Byte__Array*)app::Array_CreateInstance_1(byteArrType, static_cast<int32_t>(textureTemp.size()), NULL);

	for (int i = 0; i < textureTemp.size(); i++)
	{
		byteArr->vector[i] = textureTemp[i];
	}

	app::Texture2D* texture = (app::Texture2D*)il2cpp_object_new((Il2CppClass*)(*app::Texture2D__TypeInfo));
	
#ifdef _WOTW_PATCH_THREE
	app::Texture2D__ctor_3(texture, width, height, app::TextureFormat__Enum::TextureFormat__Enum_RGBA32, false, false, NULL);
	app::Texture_set_wrapMode((app::Texture*)texture, app::TextureWrapMode__Enum::TextureWrapMode__Enum_Repeat, NULL);
	app::Texture_set_filterMode((app::Texture*)texture, app::FilterMode__Enum::FilterMode__Enum_Point, NULL);
#endif
#ifdef _WOTW_PATCH_TWO
	app::Texture2D__ctor_3(texture, width, height, app::TextureFormat__Enum::RGBA32, false, false, NULL);
	app::Texture_set_wrapMode((app::Texture*)texture, app::TextureWrapMode__Enum::Repeat, NULL);
	app::Texture_set_filterMode((app::Texture*)texture, app::FilterMode__Enum::Point, NULL);
#endif

	app::ImageConversion_LoadImage_1((app::Texture2D*)texture, byteArr, NULL);
	app::Texture2D_ApplyImpl((app::Texture2D*)texture, true, true, NULL);

	return texture;
}

void DrawUI::SetImageInObject(app::GameObject* object, app::Texture2D* texture)
{
	app::Type* type = GetType("UnityEngine.UI", "Image");
	app::Image* image = (app::Image*)app::GameObject_GetComponent(object, type, NULL);
	app::Material* newImageMat = CreateNewMaterial("UI/Default");

	if (image != nullptr)
	{
		app::String* TextureName1 = string_new("_Color");
		app::Color colorWhite = app::Color();
		colorWhite.r = colorWhite.g = colorWhite.b = colorWhite.a = 1.0f;

		app::String* TextureName = string_new("_MainTex");
		app::Material_SetColor(newImageMat, TextureName1, colorWhite, NULL);
		app::Material_SetTexture(newImageMat, TextureName, (app::Texture*)texture, NULL);
		app::Material_set_mainTexture(newImageMat, (app::Texture*)texture, NULL);
		app::Image_set_material(image, newImageMat, NULL);
	}
}

app::GameObject* DrawUI::Button(const std::string& name)
{
	app::Type* type = GetType("UnityEngine.UI", "Button");
	app::Type* typeImage = GetType("UnityEngine.UI", "Image");
	app::Type* typeLayoutElement = GetType("UnityEngine.UI", "LayoutElement");
	app::GameObject* gameObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
	app::String* gameObjectname = string_new(name.data());
	app::GameObject__ctor(gameObject, gameObjectname, NULL);
	app::Image* newObjectImage = (app::Image*)app::GameObject_AddComponent((app::GameObject*)gameObject, typeImage, NULL);
	app::Button* newObject = (app::Button*)app::GameObject_AddComponent((app::GameObject*)gameObject, type, NULL);
	app::LayoutElement* newLayoutElement = (app::LayoutElement*)app::GameObject_AddComponent((app::GameObject*)gameObject, typeLayoutElement, NULL);
	app::LayoutElement_set_minHeight(newLayoutElement, 32, NULL);
	app::LayoutElement_set_minWidth(newLayoutElement, 32, NULL);

	return gameObject;
}

app::GameObject* DrawUI::Button(const std::string& text, int fontSize, app::Color color)
{
	app::Type* type = GetType("UnityEngine.UI", "Button");
	app::Type* typeImage = GetType("UnityEngine.UI", "Image");
	//app::Type* typeLayoutElement = GetType("UnityEngine.UI", "LayoutElement");

	app::GameObject* gameObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
	app::GameObject__ctor(gameObject, string_new(text.data()), NULL);
	app::Image* newObjectImage = (app::Image*)app::GameObject_AddComponent(gameObject, typeImage, NULL);
	app::Button* newObject = (app::Button*)app::GameObject_AddComponent(gameObject, type, NULL);
	//app::LayoutElement* newLayoutElement = (app::LayoutElement*)app::GameObject_AddComponent(gameObject, typeLayoutElement, NULL);
	app::GameObject* textObject = DrawUI::Text("ButtonText", text, static_cast<int>(fontSize * 0.75), color);

	//app::LayoutElement_set_minHeight(newLayoutElement, (float)fontSize + 16, NULL);
	//app::LayoutElement_set_minWidth(newLayoutElement, (float)fontSize * text.size(), NULL);
	TransformSetParent(textObject, gameObject);

	return gameObject;
}

app::Button* DrawUI::Button(app::GameObject* object, const std::string& text, int fontSize, app::Color color)
{
	app::Type* type = GetType("UnityEngine.UI", "Button");
	app::Type* typeImage = GetType("UnityEngine.UI", "Image");
	app::Type* typeText = GetType("UnityEngine.UI", "Text");
	app::Type* typeLayoutElement = GetType("UnityEngine.UI", "LayoutElement");
	app::String* TextureName = string_new("_MainTex");
	app::String* TextureName1 = string_new("_Color");

	app::Button* newObject = (app::Button*)app::GameObject_AddComponent((app::GameObject*)object, type, NULL);
	app::Image* newObjectImage = (app::Image*)app::GameObject_AddComponent((app::GameObject*)object, typeImage, NULL);
	app::LayoutElement* newLayoutElement = (app::LayoutElement*)app::GameObject_AddComponent((app::GameObject*)object, typeLayoutElement, NULL);
	app::GameObject* textObject = DrawUI::Text("ButtonText", text, static_cast<int>(fontSize * 0.75), color);
	//app::Text* textObject = (app::Text*)app::GameObject_AddComponent((app::GameObject*)object, typeText, NULL);

	app::Material* imageMat = app::Image_get_material(newObjectImage, NULL);
	int textureIndex = FindTextureIndex("messageBackgroundB");
	app::Texture2D* sliderDot = AllTexture2D[textureIndex];

	app::Color colorWhite = app::Color();
	colorWhite.r = colorWhite.g = colorWhite.b = colorWhite.a = 1.0f;
	app::Material_SetColor(imageMat, TextureName1, colorWhite, NULL);

	if (textureIndex != -1)
	{
		app::Material_SetTexture(imageMat, TextureName, (app::Texture*)sliderDot, NULL);
		app::Material_set_mainTexture(imageMat, (app::Texture*)sliderDot, NULL);
	}

	app::LayoutElement_set_minHeight(newLayoutElement, (float)fontSize + 16, NULL);
	app::LayoutElement_set_minWidth(newLayoutElement, (float)fontSize * text.size(), NULL);

	/*app::String* textText = string_new(text.data());
	app::String* font = string_new("Arial.ttf");
	app::Type* fontType = GetType("UnityEngine", "Font");
	app::Font* newFont = (app::Font*)app::Resources_GetBuiltinResource(fontType, font, NULL);
	app::Text_set_font(textObject, newFont, NULL);
	app::Text_set_fontSize(textObject, fontSize, NULL);
	app::Text_set_text(textObject, textText, NULL);
	app::Graphic_set_color((app::Graphic*)textObject, color, NULL);*/
	TransformSetParent(textObject, object);

	return newObject;
}

app::GameObject* DrawUI::TreeItem(const std::string& name, app::TextAnchor__Enum textAnchor)
{
	app::Type* type = GetType("UnityEngine.UI", "VerticalLayoutGroup");
	app::Type* typeContentSizeFitter = GetType("UnityEngine.UI", "ContentSizeFitter");
	app::GameObject* gameObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
	app::String* gameObjectname = string_new(name.data());
	app::GameObject__ctor(gameObject, gameObjectname, NULL);
	app::VerticalLayoutGroup* newObject = (app::VerticalLayoutGroup*)app::GameObject_AddComponent((app::GameObject*)gameObject, type, NULL);
	app::HorizontalOrVerticalLayoutGroup_set_childControlWidth((app::HorizontalOrVerticalLayoutGroup*)newObject, true, NULL);
	app::HorizontalOrVerticalLayoutGroup_set_childControlHeight((app::HorizontalOrVerticalLayoutGroup*)newObject, true, NULL);
	app::HorizontalOrVerticalLayoutGroup_set_childForceExpandWidth((app::HorizontalOrVerticalLayoutGroup*)newObject, false, NULL);
	app::HorizontalOrVerticalLayoutGroup_set_childForceExpandHeight((app::HorizontalOrVerticalLayoutGroup*)newObject, false, NULL);

	app::ContentSizeFitter* newContentSizeFitter = (app::ContentSizeFitter*)app::GameObject_AddComponent((app::GameObject*)gameObject, typeContentSizeFitter, NULL);
#ifdef _WOTW_PATCH_THREE
	app::ContentSizeFitter_set_horizontalFit(newContentSizeFitter, app::ContentSizeFitter_FitMode__Enum::ContentSizeFitter_FitMode__Enum_PreferredSize, NULL);
	app::ContentSizeFitter_set_verticalFit(newContentSizeFitter, app::ContentSizeFitter_FitMode__Enum::ContentSizeFitter_FitMode__Enum_PreferredSize, NULL);
#endif
#ifdef _WOTW_PATCH_TWO
	app::ContentSizeFitter_set_horizontalFit(newContentSizeFitter, app::ContentSizeFitter_FitMode__Enum::PreferredSize, NULL);
	app::ContentSizeFitter_set_verticalFit(newContentSizeFitter, app::ContentSizeFitter_FitMode__Enum::PreferredSize, NULL);
#endif

	app::LayoutGroup_set_childAlignment((app::LayoutGroup*)newObject, textAnchor, NULL);

	return gameObject;
}

app::GameObject* DrawUI::VerticalLayoutGroup(const std::string& name, app::TextAnchor__Enum textAnchor)
{
	app::Type* type = GetType("UnityEngine.UI", "VerticalLayoutGroup");
	app::Type* typeContentSizeFitter = GetType("UnityEngine.UI", "ContentSizeFitter");
	app::GameObject* gameObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
	app::String* gameObjectname = string_new(name.data());
	app::GameObject__ctor(gameObject, gameObjectname, NULL);
	app::VerticalLayoutGroup* newObject = (app::VerticalLayoutGroup*)app::GameObject_AddComponent((app::GameObject*)gameObject, type, NULL);
	app::HorizontalOrVerticalLayoutGroup_set_childControlWidth((app::HorizontalOrVerticalLayoutGroup*)newObject, true, NULL);
	app::HorizontalOrVerticalLayoutGroup_set_childControlHeight((app::HorizontalOrVerticalLayoutGroup*)newObject, true, NULL);
	app::HorizontalOrVerticalLayoutGroup_set_childForceExpandWidth((app::HorizontalOrVerticalLayoutGroup*)newObject, false, NULL);
	app::HorizontalOrVerticalLayoutGroup_set_childForceExpandHeight((app::HorizontalOrVerticalLayoutGroup*)newObject, false, NULL);

	app::ContentSizeFitter* newContentSizeFitter = (app::ContentSizeFitter*)app::GameObject_AddComponent((app::GameObject*)gameObject, typeContentSizeFitter, NULL);
#ifdef _WOTW_PATCH_THREE
	app::ContentSizeFitter_set_horizontalFit(newContentSizeFitter, app::ContentSizeFitter_FitMode__Enum::ContentSizeFitter_FitMode__Enum_PreferredSize, NULL);
	app::ContentSizeFitter_set_verticalFit(newContentSizeFitter, app::ContentSizeFitter_FitMode__Enum::ContentSizeFitter_FitMode__Enum_PreferredSize, NULL);
#endif
#ifdef _WOTW_PATCH_TWO
	app::ContentSizeFitter_set_horizontalFit(newContentSizeFitter, app::ContentSizeFitter_FitMode__Enum::PreferredSize, NULL);
	app::ContentSizeFitter_set_verticalFit(newContentSizeFitter, app::ContentSizeFitter_FitMode__Enum::PreferredSize, NULL);
#endif

	app::LayoutGroup_set_childAlignment((app::LayoutGroup*)newObject, textAnchor, NULL);

	return gameObject;
}

app::GameObject* DrawUI::HorizontalLayoutGroup(const std::string& name, app::TextAnchor__Enum textAnchor)
{
	app::Type* type = GetType("UnityEngine.UI", "HorizontalLayoutGroup");
	//app::Type* typeContentSizeFitter = GetType("UnityEngine.UI", "ContentSizeFitter");
	app::GameObject* gameObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
	app::String* gameObjectname = string_new(name.data());
	app::GameObject__ctor(gameObject, gameObjectname, NULL);
	app::HorizontalLayoutGroup* newObject = (app::HorizontalLayoutGroup*)app::GameObject_AddComponent((app::GameObject*)gameObject, type, NULL);
	app::HorizontalOrVerticalLayoutGroup_set_childControlHeight((app::HorizontalOrVerticalLayoutGroup*)newObject, true, NULL);
	app::HorizontalOrVerticalLayoutGroup_set_childForceExpandWidth((app::HorizontalOrVerticalLayoutGroup*)newObject, false, NULL);
	app::HorizontalOrVerticalLayoutGroup_set_childForceExpandHeight((app::HorizontalOrVerticalLayoutGroup*)newObject, false, NULL);

	//app::ContentSizeFitter* newContentSizeFitter = (app::ContentSizeFitter*)app::GameObject_AddComponent((app::GameObject*)gameObject, typeContentSizeFitter, NULL);
	//app::ContentSizeFitter_set_horizontalFit(newContentSizeFitter, app::ContentSizeFitter_FitMode__Enum::ContentSizeFitter_FitMode__Enum_PreferredSize, NULL);
	//app::ContentSizeFitter_set_verticalFit(newContentSizeFitter, app::ContentSizeFitter_FitMode__Enum::ContentSizeFitter_FitMode__Enum_PreferredSize, NULL);

	app::LayoutGroup_set_childAlignment((app::LayoutGroup*)newObject, textAnchor, NULL);

	return gameObject;
}

app::GameObject* DrawUI::RectMask2D(const std::string& name, float minWidth, float minHeight, float preferedWidth, float preferedHeight)
{
	app::Type* type = GetType("UnityEngine.UI", "RectMask2D");
	app::Type* typeLayoutElement = GetType("UnityEngine.UI", "LayoutElement");
	app::GameObject* gameObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
	app::String* gameObjectname = string_new(name.data());
	app::GameObject__ctor(gameObject, gameObjectname, NULL);
	app::RectMask2D* newObject = (app::RectMask2D*)app::GameObject_AddComponent((app::GameObject*)gameObject, type, NULL);

	app::LayoutElement* newLayoutElement = (app::LayoutElement*)app::GameObject_AddComponent(gameObject, typeLayoutElement, NULL);
	app::LayoutElement_set_minHeight(newLayoutElement, minHeight, NULL);
	app::LayoutElement_set_minWidth(newLayoutElement, minWidth, NULL);
	app::LayoutElement_set_preferredWidth(newLayoutElement, preferedWidth, NULL);
	app::LayoutElement_set_preferredHeight(newLayoutElement, preferedHeight, NULL);

	return gameObject;
}

app::GameObject* DrawUI::Text(const std::string& name, const std::string& text, int fontSize, app::Color color)
{
	app::Type* type = GetType("UnityEngine.UI", "Text");
	//app::Type* typeLayoutElement = GetType("UnityEngine.UI", "LayoutElement");
	//app::Type* typeContentSizeFitter = GetType("UnityEngine.UI", "ContentSizeFitter");
	app::GameObject* gameObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
	app::String* gameObjectname = string_new(name.data());
	app::GameObject__ctor(gameObject, gameObjectname, NULL);
	app::Text* newObject = (app::Text*)app::GameObject_AddComponent((app::GameObject*)gameObject, type, NULL);

	app::String* textText = string_new(text.data());
	app::String* font = string_new("Arial.ttf");
	app::Type* fontType = GetType("UnityEngine", "Font");
	app::Font* newFont = (app::Font*)app::Resources_GetBuiltinResource(fontType, font, NULL);
	app::Text_set_font(newObject, newFont, NULL);
	app::Text_set_fontSize(newObject, fontSize, NULL);
	app::Text_set_text(newObject, textText, NULL);
	app::Graphic_set_color((app::Graphic*)newObject, color, NULL);

	//app::LayoutElement* newLayoutElement = (app::LayoutElement*)app::GameObject_AddComponent(gameObject, typeLayoutElement, NULL);
	//app::ContentSizeFitter* newContentSizeFitter = (app::ContentSizeFitter*)app::GameObject_AddComponent(gameObject, typeContentSizeFitter, NULL);

	//app::LayoutElement_set_minHeight(newLayoutElement, static_cast<float>(fontSize) + 3.0f, NULL);
	//app::LayoutElement_set_minWidth(newLayoutElement, (static_cast<float>(fontSize) * static_cast<float>(text.size()) + 3.0f) * 0.6f, NULL);
	//app::ContentSizeFitter_set_horizontalFit(newContentSizeFitter, app::ContentSizeFitter_FitMode__Enum::ContentSizeFitter_FitMode__Enum_MinSize, NULL);
	//app::ContentSizeFitter_set_verticalFit(newContentSizeFitter, app::ContentSizeFitter_FitMode__Enum::ContentSizeFitter_FitMode__Enum_MinSize, NULL);

	return gameObject;
}

app::GameObject* DrawUI::Scrollbar(app::GameObject* rectHandle, const std::string& name, app::Color color, app::Color colorHandle, bool horizontal)
{
	app::Type* scrollType = GetType("UnityEngine.UI", "Scrollbar");
	app::Type* type = GetType("UnityEngine.UI", "Image");
	app::Type* typeLayoutElement = GetType("UnityEngine.UI", "LayoutElement");
	app::Type* rectTransformType = GetType("UnityEngine", "RectTransform");
	app::Material* scrollbarMaterial = CreateNewMaterial("UI/Default");
	app::Material* scrollbarHandleMaterial = CreateNewMaterial("UI/Default");
	app::String* TextureName = string_new("_MainTex");
	app::String* TextureName1 = string_new("_Color");

	app::GameObject* gameObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
	app::String* gameObjectname = string_new(name.data());
	app::GameObject__ctor(gameObject, gameObjectname, NULL);

	/*app::Texture2D* scrollbarTexture = (app::Texture2D*)il2cpp_object_new((Il2CppClass*)app::Texture2D__TypeInfo);
	app::Texture2D__ctor_3(scrollbarTexture, 1024, 8.0f, app::TextureFormat__Enum::TextureFormat__Enum_RGBA32, false, false, NULL);
	app::Texture_set_wrapMode((app::Texture*)scrollbarTexture, app::TextureWrapMode__Enum::TextureWrapMode__Enum_Repeat, NULL);
	app::Texture_set_filterMode((app::Texture*)scrollbarTexture, app::FilterMode__Enum::FilterMode__Enum_Point, NULL);*/

	app::Image* scrollbarImage = (app::Image*)app::GameObject_AddComponent((app::GameObject*)gameObject, type, NULL);
	app::Image_set_material(scrollbarImage, scrollbarMaterial, NULL);

	int textureIndex = FindTextureIndex("sliderBackground");
	app::Texture2D* sliderBackground = AllTexture2D[textureIndex];

	app::Material_SetColor(scrollbarMaterial, TextureName1, color, NULL);

	if (textureIndex != -1)
	{
		app::Material_SetTexture(scrollbarMaterial, TextureName, (app::Texture*)sliderBackground, NULL);
		app::Material_set_mainTexture(scrollbarMaterial, (app::Texture*)sliderBackground, NULL);
	}

	app::Scrollbar* scrollbar = (app::Scrollbar*)app::GameObject_AddComponent((app::GameObject*)gameObject, scrollType, NULL);
	app::LayoutElement* newLayoutElement = (app::LayoutElement*)app::GameObject_AddComponent(gameObject, typeLayoutElement, NULL);

	app::LayoutElement_set_minHeight(newLayoutElement, 32.0f, NULL);
	app::LayoutElement_set_minWidth(newLayoutElement, 256.0f + 128.0f, NULL);

	app::GameObject* slidingAreaObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
	app::String* slidingAreaObjectName = string_new("SlidingArea");
	app::GameObject__ctor(slidingAreaObject, slidingAreaObjectName, NULL);
	app::RectTransform* slidingRectTransform = (app::RectTransform*)app::GameObject_AddComponent(slidingAreaObject, rectTransformType, NULL);

	/*app::Texture2D* scrollbarHandleTexture = (app::Texture2D*)il2cpp_object_new((Il2CppClass*)app::Texture2D__TypeInfo);
	app::Texture2D__ctor_3(scrollbarHandleTexture, 12, 12, app::TextureFormat__Enum::TextureFormat__Enum_RGBA32, false, false, NULL);
	app::Texture_set_wrapMode((app::Texture*)scrollbarHandleTexture, app::TextureWrapMode__Enum::TextureWrapMode__Enum_Repeat, NULL);
	app::Texture_set_filterMode((app::Texture*)scrollbarHandleTexture, app::FilterMode__Enum::FilterMode__Enum_Point, NULL);*/

	app::GameObject* scrollbarImageOject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
	app::String* scrollbarImageName = string_new("ScrollbarHandle");
	app::GameObject__ctor(scrollbarImageOject, scrollbarImageName, NULL);
	app::Image* scrollbarHandleImage = (app::Image*)app::GameObject_AddComponent((app::GameObject*)scrollbarImageOject, type, NULL);
	app::Image_set_material(scrollbarHandleImage, scrollbarHandleMaterial, NULL);

	textureIndex = FindTextureIndex("sliderDot");
	app::Texture2D* sliderDot = AllTexture2D[textureIndex];

	app::Material_SetColor(scrollbarHandleMaterial, TextureName1, colorHandle, NULL);

	if (textureIndex != -1)
	{
		app::Material_SetTexture(scrollbarHandleMaterial, TextureName, (app::Texture*)sliderDot, NULL);
		app::Material_set_mainTexture(scrollbarHandleMaterial, (app::Texture*)sliderDot, NULL);
	}


	TransformSetParent(scrollbarImageOject, slidingAreaObject);
	TransformSetParent(slidingAreaObject, gameObject);

	app::Transform* scrollbarTransform = app::GameObject_get_transform(gameObject, NULL);
	app::Transform* rectHandleTransform = app::GameObject_get_transform(rectHandle, NULL);
	app::Transform* scrollbarImageTransform = app::GameObject_get_transform(scrollbarImageOject, NULL);

	RectTransformSetSize(gameObject, tem::Vector2(256.0f, 32.0f));
	RectTransformSetSize(slidingAreaObject, tem::Vector2(256.0f, 12.0f));
	app::RectTransform_set_sizeDelta((app::RectTransform*)scrollbarTransform, ToVector2(256.0f, 32), NULL);
	app::RectTransform_set_sizeDelta((app::RectTransform*)scrollbarImageTransform, ToVector2(12, 12), NULL);

	app::Scrollbar_set_handleRect(scrollbar, (app::RectTransform*)scrollbarImageTransform, NULL);
	app::Scrollbar_set_size(scrollbar, 0.01f, NULL);
	app::Scrollbar_set_value(scrollbar, 0.0f, NULL);
#ifdef _WOTW_PATCH_THREE
	app::Scrollbar_set_direction(scrollbar, app::Scrollbar_Direction__Enum::Scrollbar_Direction__Enum_LeftToRight, NULL);
#endif
#ifdef _WOTW_PATCH_TWO
	app::Scrollbar_set_direction(scrollbar, app::Scrollbar_Direction__Enum::LeftToRight, NULL);
#endif

	return gameObject;
}

app::GameObject* DrawUI::Dropdown(const std::string& name)
{
	app::Type* type = GetType("UnityEngine.UI", "Dropdown");
	app::Type* toggleType = GetType("UnityEngine.UI", "Toggle");
	app::Type* imageType = GetType("UnityEngine.UI", "Image");
	app::Type* typeLayoutElement = GetType("UnityEngine.UI", "LayoutElement");
	app::Material* imageMaterial = CreateNewMaterial("UI/Default");
	app::Material* itemBackgroundMaterial = CreateNewMaterial("UI/Default");
	app::Material* itemLabelMaterial = CreateNewMaterial("UI/Default");
	app::String* TextureName = string_new("_MainTex");
	app::String* TextureName1 = string_new("_Color");

	app::GameObject* gameObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
	app::String* gameObjectname = string_new(name.data());
	app::GameObject__ctor(gameObject, gameObjectname, NULL);

	app::Image* newImageObject = (app::Image*)app::GameObject_AddComponent((app::GameObject*)gameObject, imageType, NULL);
	app::Image_set_material(newImageObject, imageMaterial, NULL);

	int textureIndex = FindTextureIndex("window");
	app::Texture2D* window = AllTexture2D[textureIndex];

	if (textureIndex != -1)
	{
		app::Material_SetTexture(imageMaterial, TextureName, (app::Texture*)window, NULL);
		app::Material_set_mainTexture(imageMaterial, (app::Texture*)window, NULL);
	}

	app::Dropdown* dropdownObject = (app::Dropdown*)app::GameObject_AddComponent((app::GameObject*)gameObject, type, NULL);
	app::Dropdown__ctor(dropdownObject, NULL);

	//Setup dropdown template
	app::GameObject* templateObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
	app::String* templateObjectName = string_new("Template");
	app::GameObject__ctor(templateObject, templateObjectName, NULL);

	app::GameObject* templateItem = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
	app::String* templateItemName = string_new("Item");
	app::GameObject__ctor(templateItem, templateItemName, NULL);

	app::Dropdown* toggleTemplate = (app::Dropdown*)app::GameObject_AddComponent((app::GameObject*)templateItem, toggleType, NULL);

	app::GameObject* itemBackground = DrawUI::Image("Item Background", itemBackgroundMaterial);
	textureIndex = FindTextureIndex("textfield");
	app::Texture2D* arrowDown = AllTexture2D[textureIndex];

	if (textureIndex != -1)
	{
		app::Material_SetTexture(itemBackgroundMaterial, TextureName, (app::Texture*)arrowDown, NULL);
		app::Material_set_mainTexture(itemBackgroundMaterial, (app::Texture*)arrowDown, NULL);
	}

	app::GameObject* itemCheckmark = DrawUI::Image("Item Checkmark", itemLabelMaterial);
	textureIndex = FindTextureIndex("lockIcon");
	app::Texture2D* apply = AllTexture2D[textureIndex];

	if (textureIndex != -1)
	{
		app::Material_SetTexture(itemLabelMaterial, TextureName, (app::Texture*)apply, NULL);
		app::Material_set_mainTexture(itemLabelMaterial, (app::Texture*)apply, NULL);
	}

	app::GameObject* itemLabel = DrawUI::Text("Item Label", "Fuck Unity", 14, GraphColors::Grey);

	RectTransformSetSizeDelta(gameObject, 400, 64);

	TransformSetParent(itemBackground, templateItem);
	TransformSetParent(itemCheckmark, templateItem);
	TransformSetParent(itemLabel, templateItem);
	TransformSetParent(templateItem, templateObject);
	TransformSetParent(templateObject, gameObject);

	app::Transform* templateTransform = app::GameObject_get_transform((app::GameObject*)templateObject, NULL);
	dropdownObject->fields.m_Template = (app::RectTransform*)templateTransform;

	app::LayoutElement* newLayoutElement = (app::LayoutElement*)app::GameObject_AddComponent(gameObject, typeLayoutElement, NULL);
	app::LayoutElement_set_minHeight(newLayoutElement, 300, NULL);
	app::LayoutElement_set_minWidth(newLayoutElement, 32, NULL);

	app::Dropdown_set_template(dropdownObject, (app::RectTransform*)templateTransform, NULL);
	app::Dropdown_SetupTemplate(dropdownObject, NULL);
	app::Dropdown_CreateDropdownList(dropdownObject, templateObject, NULL);

	app::String* option1S = string_new("Test");
	app::String* option2S = string_new("Test2");
	app::String* option3S = string_new("Test3");

	//app::List_1_UnityEngine_UI_Dropdown_OptionData___TypeInfo;
	app::List_1_UnityEngine_UI_Dropdown_OptionData_ options = app::List_1_UnityEngine_UI_Dropdown_OptionData_();// = app::Dropdown_get_options(dropdownObject, NULL);
	options.fields._items = (*app::List_1_UnityEngine_UI_Dropdown_OptionData___TypeInfo)->static_fields->_emptyArray;

	app::Dropdown_OptionData* option1 = (app::Dropdown_OptionData*)il2cpp_object_new((Il2CppClass*)(*app::Dropdown_OptionData__TypeInfo));
	app::Dropdown_OptionData__ctor_1(option1, option1S, NULL);
	app::Dropdown_OptionData* option2 = (app::Dropdown_OptionData*)il2cpp_object_new((Il2CppClass*)(*app::Dropdown_OptionData__TypeInfo));
	app::Dropdown_OptionData__ctor_1(option2, option2S, NULL);
	app::Dropdown_OptionData* option3 = (app::Dropdown_OptionData*)il2cpp_object_new((Il2CppClass*)(*app::Dropdown_OptionData__TypeInfo));
	app::Dropdown_OptionData__ctor_1(option3, option3S, NULL);

	options.fields._items->vector[0] = option1;
	options.fields._items->vector[1] = option2;
	options.fields._items->vector[2] = option3;
	app::Dropdown_set_options(dropdownObject, &options, NULL);

	return gameObject;
}

/*void TemButton::IOnClick()
{
	this->onClickMethod();
}*/

DropdownHorizontal DrawUI::CreateDropdownHorizontal(const std::string& name, const std::string& imagePath)
{
	DropdownHorizontal dropdownHorizontal = DropdownHorizontal();
	app::Type* typeSelectable = GetType("UnityEngine.UI", "Selectable");
	app::Type* typeVerticalLayoutGroup = GetType("UnityEngine.UI", "VerticalLayoutGroup");
	app::Type* typeHorizontalLayoutGroup = GetType("UnityEngine.UI", "HorizontalLayoutGroup");
	app::Type* typeLayoutElement = GetType("UnityEngine.UI", "LayoutElement");
	app::Type* typeContentSizeFitter = GetType("UnityEngine.UI", "ContentSizeFitter");

	dropdownHorizontal.DropdownObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
	app::String* gameObjectname = string_new(name.data());
	app::GameObject__ctor(dropdownHorizontal.DropdownObject, gameObjectname, NULL);
	app::VerticalLayoutGroup* newObject = (app::VerticalLayoutGroup*)app::GameObject_AddComponent((app::GameObject*)dropdownHorizontal.DropdownObject, typeVerticalLayoutGroup, NULL);
	app::HorizontalOrVerticalLayoutGroup_set_childControlWidth((app::HorizontalOrVerticalLayoutGroup*)newObject, true, NULL);
	app::HorizontalOrVerticalLayoutGroup_set_childControlHeight((app::HorizontalOrVerticalLayoutGroup*)newObject, true, NULL);
	app::HorizontalOrVerticalLayoutGroup_set_childForceExpandWidth((app::HorizontalOrVerticalLayoutGroup*)newObject, false, NULL);
	app::HorizontalOrVerticalLayoutGroup_set_childForceExpandHeight((app::HorizontalOrVerticalLayoutGroup*)newObject, false, NULL);

	app::ContentSizeFitter* newContentSizeFitter = (app::ContentSizeFitter*)app::GameObject_AddComponent((app::GameObject*)dropdownHorizontal.DropdownObject, typeContentSizeFitter, NULL);
#ifdef _WOTW_PATCH_THREE
	app::ContentSizeFitter_set_horizontalFit(newContentSizeFitter, app::ContentSizeFitter_FitMode__Enum::ContentSizeFitter_FitMode__Enum_PreferredSize, NULL);
	app::ContentSizeFitter_set_verticalFit(newContentSizeFitter, app::ContentSizeFitter_FitMode__Enum::ContentSizeFitter_FitMode__Enum_PreferredSize, NULL);

	app::LayoutGroup_set_childAlignment((app::LayoutGroup*)newObject, app::TextAnchor__Enum::TextAnchor__Enum_UpperLeft, NULL);
#endif
#ifdef _WOTW_PATCH_TWO
	app::ContentSizeFitter_set_horizontalFit(newContentSizeFitter, app::ContentSizeFitter_FitMode__Enum::PreferredSize, NULL);
	app::ContentSizeFitter_set_verticalFit(newContentSizeFitter, app::ContentSizeFitter_FitMode__Enum::PreferredSize, NULL);

	app::LayoutGroup_set_childAlignment((app::LayoutGroup*)newObject, app::TextAnchor__Enum::UpperLeft, NULL);
#endif

	dropdownHorizontal.FoldSelectableObject = DrawUI::Selectable("FoldSelectable");
	app::Texture2D* image = DrawUI::LoadImageFromPath(imagePath, 64, 64);
	DrawUI::SetImageInObject(dropdownHorizontal.FoldSelectableObject, image);

	TransformSetParent(dropdownHorizontal.FoldSelectableObject, dropdownHorizontal.DropdownObject);
	RectTransformSetMinMax(dropdownHorizontal.DropdownObject, tem::Vector2(0.0f, 1.0f), tem::Vector2(0.0f, 1.0f));
	RectTransformSetPivot(dropdownHorizontal.DropdownObject, tem::Vector2(0.0f, 1.0f));

#ifdef _WOTW_PATCH_THREE
	dropdownHorizontal.DropdownChildren = DrawUI::HorizontalLayoutGroup("DropdownChildren", app::TextAnchor__Enum::TextAnchor__Enum_UpperLeft);
#endif
#ifdef _WOTW_PATCH_TWO
	dropdownHorizontal.DropdownChildren = DrawUI::HorizontalLayoutGroup("DropdownChildren", app::TextAnchor__Enum::UpperLeft);
#endif
	dropdownHorizontal.DropdownChildrenLayout = (app::HorizontalLayoutGroup*)app::GameObject_GetComponent(dropdownHorizontal.DropdownChildren, typeHorizontalLayoutGroup, NULL);

	TransformSetParent(dropdownHorizontal.DropdownChildren, dropdownHorizontal.DropdownObject);

	dropdownHorizontal.FoldSelectable = (app::Selectable*)app::GameObject_GetComponent(dropdownHorizontal.FoldSelectableObject, typeSelectable, NULL);
	app::GameObject_set_active(dropdownHorizontal.DropdownChildren, false, NULL);

	return dropdownHorizontal;
}

TreeItemStruct DrawUI::CreateTreeItem(const std::string& name)
{
	TreeItemStruct treeStruct = TreeItemStruct();
	app::Type* typeButton = GetType("UnityEngine.UI", "Button");
	app::Type* typeVerticalLayoutGroup = GetType("UnityEngine.UI", "VerticalLayoutGroup");
	app::Type* typeLayoutElement = GetType("UnityEngine.UI", "LayoutElement");

	treeStruct.TreeItemObject = DrawUI::TreeItem("TreeRoot");
#ifdef _WOTW_PATCH_THREE
	app::GameObject* treeItemHeader = DrawUI::HorizontalLayoutGroup("TreeItemHeader", app::TextAnchor__Enum::TextAnchor__Enum_UpperCenter);
#endif
#ifdef _WOTW_PATCH_TWO
	app::GameObject* treeItemHeader = DrawUI::HorizontalLayoutGroup("TreeItemHeader", app::TextAnchor__Enum::UpperCenter);
#endif
	treeStruct.TreeItemObjectLayout = (app::VerticalLayoutGroup*)app::GameObject_GetComponent(treeItemHeader, typeVerticalLayoutGroup, NULL);
	treeStruct.FoldButtonObject = DrawUI::Button("X", 14, tem::Vector4(0.0f, 0.0f, 0.0f, 1.0f).ToColor());
	treeStruct.ObjectButtonObject = DrawUI::Button(name, 14, tem::Vector4(0.0f, 0.0f, 0.0f, 1.0f).ToColor());
	//app::LayoutElement* tempLayout = (app::LayoutElement*)app::GameObject_GetComponent(treeStruct.FoldButtonObject, typeLayoutElement, NULL);
	//app::LayoutElement_set_minHeight(tempLayout, 14.0f, NULL);
	//app::LayoutElement_set_minWidth(tempLayout, 14.0f, NULL);
	//tempLayout = (app::LayoutElement*)app::GameObject_GetComponent(treeStruct.ObjectButtonObject, typeLayoutElement, NULL);
	//app::LayoutElement_set_minHeight(tempLayout, 14.0f, NULL);
	//app::LayoutElement_set_minWidth(tempLayout, 200.0f, NULL);

	TransformSetParent(treeStruct.FoldButtonObject, treeItemHeader);
	TransformSetParent(treeStruct.ObjectButtonObject, treeItemHeader);

	RectTransformSetMinMax(treeItemHeader, tem::Vector2(0.0f, 1.0f), tem::Vector2(0.0f, 1.0f));
	RectTransformSetPivot(treeItemHeader, tem::Vector2(0.0f, 1.0f));

#ifdef _WOTW_PATCH_THREE
	treeStruct.ChildrenTree = DrawUI::VerticalLayoutGroup("TreeItemChildren", app::TextAnchor__Enum::TextAnchor__Enum_UpperLeft);
#endif
#ifdef _WOTW_PATCH_TWO
	treeStruct.ChildrenTree = DrawUI::VerticalLayoutGroup("TreeItemChildren", app::TextAnchor__Enum::UpperLeft);
#endif
	treeStruct.TreeItemChildrenLayout = (app::VerticalLayoutGroup*)app::GameObject_GetComponent(treeStruct.ChildrenTree, typeVerticalLayoutGroup, NULL);
	app::RectOffset_set_left(treeStruct.TreeItemChildrenLayout->fields._._.m_Padding, 12.0, NULL);

	TransformSetParent(treeItemHeader, treeStruct.TreeItemObject);
	TransformSetParent(treeStruct.ChildrenTree, treeStruct.TreeItemObject);

	RectTransformSetMinMax(treeStruct.ChildrenTree, tem::Vector2(0.0f, 1.0f), tem::Vector2(0.0f, 1.0f));
	RectTransformSetPivot(treeStruct.ChildrenTree, tem::Vector2(0.0f, 1.0f));

	treeStruct.FoldButton = (app::Button*)app::GameObject_GetComponent(treeStruct.FoldButtonObject, typeButton, NULL);
	treeStruct.ObjectButton = (app::Button*)app::GameObject_GetComponent(treeStruct.ObjectButtonObject, typeButton, NULL);
	app::GameObject_set_active(treeStruct.ChildrenTree, false, NULL);

	return treeStruct;
}