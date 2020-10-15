#pragma once

#include "il2cpp-appdata.h"
#include "helpers.h"

#include "ManagerDef.h"

#ifndef _CREATEUI_H
#define _CREATEUI_H

namespace DrawUI {
	app::GameObject* EventSystem(const std::string& name);
	app::GameObject* Image(const std::string& name, app::Material* material);
	app::GameObject* Button(const std::string& name);
	app::Button* Button(app::GameObject* object, const std::string& text, int fontSize, app::Color color);
	app::GameObject* VerticalLayoutGroup(const std::string& name, app::TextAnchor__Enum textAnchor = app::TextAnchor__Enum::TextAnchor__Enum_UpperLeft);
	app::GameObject* HorizontalLayoutGroup(const std::string& name, app::TextAnchor__Enum textAnchor = app::TextAnchor__Enum::TextAnchor__Enum_UpperLeft);
	app::GameObject* Text(const std::string& name, const std::string& text, int fontSize, app::Color color);

	app::GameObject* EventSystem(const std::string& name)
	{
		app::Type* type = GetType("UnityEngine.EventSystems", "EventSystem");
		app::Type* typeInput = GetType("UnityEngine.EventSystems", "StandaloneInputModule");
		app::GameObject* gameObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)app::GameObject__TypeInfo);
		app::String* gameObjectname = string_new(name.data());
		app::GameObject__ctor(gameObject, gameObjectname, NULL);
		app::EventSystem* newObject = (app::EventSystem*)app::GameObject_AddComponent((app::GameObject*)gameObject, type, NULL);
		app::StandaloneInputModule* newObjectInput = (app::StandaloneInputModule*)app::GameObject_AddComponent((app::GameObject*)gameObject, typeInput, NULL);

		return gameObject;
	}

	app::GameObject* Image(const std::string& name, app::Material* material)
	{
		app::Type* type = GetType("UnityEngine.UI", "Image");
		app::GameObject* gameObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)app::GameObject__TypeInfo);
		app::String* gameObjectname = string_new(name.data());
		app::GameObject__ctor(gameObject, gameObjectname, NULL);
		app::Image* newObject = (app::Image*)app::GameObject_AddComponent((app::GameObject*)gameObject, type, NULL);
		app::Image_set_material(newObject, material, NULL);

		return gameObject;
	}

	app::GameObject* Button(const std::string& name)
	{
		app::Type* type = GetType("UnityEngine.UI", "Button");
		app::Type* typeImage = GetType("UnityEngine.UI", "Image");
		app::GameObject* gameObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)app::GameObject__TypeInfo);
		app::String* gameObjectname = string_new(name.data());
		app::GameObject__ctor(gameObject, gameObjectname, NULL);
		app::Image* newObjectImage = (app::Image*)app::GameObject_AddComponent((app::GameObject*)gameObject, typeImage, NULL);
		app::Button* newObject = (app::Button*)app::GameObject_AddComponent((app::GameObject*)gameObject, type, NULL);

		return gameObject;
	}

	app::Button* Button(app::GameObject* object, const std::string& text, int fontSize, app::Color color)
	{
		app::Type* type = GetType("UnityEngine.UI", "Button");
		app::Type* typeImage = GetType("UnityEngine.UI", "Image");
		app::Type* typeText = GetType("UnityEngine.UI", "Text");
		app::Type* typeLayoutElement = GetType("UnityEngine.UI", "LayoutElement");
		app::Button* newObject = (app::Button*)app::GameObject_AddComponent((app::GameObject*)object, type, NULL);
		app::Image* newObjectImage = (app::Image*)app::GameObject_AddComponent((app::GameObject*)object, typeImage, NULL);
		app::LayoutElement* newLayoutElement = (app::LayoutElement*)app::GameObject_AddComponent((app::GameObject*)object, typeLayoutElement, NULL);
		app::GameObject* textObject = DrawUI::Text("ButtonText", text, fontSize, color);
		//app::Text* textObject = (app::Text*)app::GameObject_AddComponent((app::GameObject*)object, typeText, NULL);

		app::LayoutElement_set_minHeight(newLayoutElement, (float)fontSize + 2, NULL);
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

	app::GameObject* VerticalLayoutGroup(const std::string& name, app::TextAnchor__Enum textAnchor)
	{
		app::Type* type = GetType("UnityEngine.UI", "VerticalLayoutGroup");
		app::Type* typeContentSizeFitter = GetType("UnityEngine.UI", "ContentSizeFitter");
		app::GameObject* gameObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)app::GameObject__TypeInfo);
		app::String* gameObjectname = string_new(name.data());
		app::GameObject__ctor(gameObject, gameObjectname, NULL);
		app::VerticalLayoutGroup* newObject = (app::VerticalLayoutGroup*)app::GameObject_AddComponent((app::GameObject*)gameObject, type, NULL);
		app::HorizontalOrVerticalLayoutGroup_set_childControlWidth((app::HorizontalOrVerticalLayoutGroup*)newObject, true, NULL);
		app::HorizontalOrVerticalLayoutGroup_set_childControlHeight((app::HorizontalOrVerticalLayoutGroup*)newObject, true, NULL);
		app::HorizontalOrVerticalLayoutGroup_set_childForceExpandWidth((app::HorizontalOrVerticalLayoutGroup*)newObject, false, NULL);
		app::HorizontalOrVerticalLayoutGroup_set_childForceExpandHeight((app::HorizontalOrVerticalLayoutGroup*)newObject, false, NULL);

		app::ContentSizeFitter* newContentSizeFitter = (app::ContentSizeFitter*)app::GameObject_AddComponent((app::GameObject*)gameObject, typeContentSizeFitter, NULL);
		app::ContentSizeFitter_set_horizontalFit(newContentSizeFitter, app::ContentSizeFitter_FitMode__Enum::ContentSizeFitter_FitMode__Enum_PreferredSize, NULL);
		app::ContentSizeFitter_set_verticalFit(newContentSizeFitter, app::ContentSizeFitter_FitMode__Enum::ContentSizeFitter_FitMode__Enum_PreferredSize, NULL);

		app::LayoutGroup_set_childAlignment((app::LayoutGroup*)newObject, textAnchor, NULL);

		return gameObject;
	}

	app::GameObject* HorizontalLayoutGroup(const std::string& name, app::TextAnchor__Enum textAnchor)
	{
		app::Type* type = GetType("UnityEngine.UI", "HorizontalLayoutGroup");
		app::Type* typeContentSizeFitter = GetType("UnityEngine.UI", "ContentSizeFitter");
		app::GameObject* gameObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)app::GameObject__TypeInfo);
		app::String* gameObjectname = string_new(name.data());
		app::GameObject__ctor(gameObject, gameObjectname, NULL);
		app::HorizontalLayoutGroup* newObject = (app::HorizontalLayoutGroup*)app::GameObject_AddComponent((app::GameObject*)gameObject, type, NULL);
		app::HorizontalOrVerticalLayoutGroup_set_childControlHeight((app::HorizontalOrVerticalLayoutGroup*)newObject, true, NULL);
		app::HorizontalOrVerticalLayoutGroup_set_childForceExpandWidth((app::HorizontalOrVerticalLayoutGroup*)newObject, false, NULL);
		app::HorizontalOrVerticalLayoutGroup_set_childForceExpandHeight((app::HorizontalOrVerticalLayoutGroup*)newObject, false, NULL);
		
		app::ContentSizeFitter* newContentSizeFitter = (app::ContentSizeFitter*)app::GameObject_AddComponent((app::GameObject*)gameObject, typeContentSizeFitter, NULL);
		app::ContentSizeFitter_set_horizontalFit(newContentSizeFitter, app::ContentSizeFitter_FitMode__Enum::ContentSizeFitter_FitMode__Enum_PreferredSize, NULL);
		app::ContentSizeFitter_set_verticalFit(newContentSizeFitter, app::ContentSizeFitter_FitMode__Enum::ContentSizeFitter_FitMode__Enum_PreferredSize, NULL);

		app::LayoutGroup_set_childAlignment((app::LayoutGroup*)newObject, textAnchor, NULL);

		return gameObject;
	}

	app::GameObject* RectMask2D(const std::string& name, float minWidth = 10, float minHeight = 10, float preferedWidth = 100, float preferedHeight = 100)
	{
		app::Type* type = GetType("UnityEngine.UI", "RectMask2D");
		app::Type* typeLayoutElement = GetType("UnityEngine.UI", "LayoutElement");
		app::GameObject* gameObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)app::GameObject__TypeInfo);
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

	app::GameObject* Text(const std::string& name, const std::string& text, int fontSize, app::Color color)
	{
		app::Type* type = GetType("UnityEngine.UI", "Text");
		app::Type* typeLayoutElement = GetType("UnityEngine.UI", "LayoutElement");
		app::Type* typeContentSizeFitter = GetType("UnityEngine.UI", "ContentSizeFitter");
		app::GameObject* gameObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)app::GameObject__TypeInfo);
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

		app::LayoutElement* newLayoutElement = (app::LayoutElement*)app::GameObject_AddComponent(gameObject, typeLayoutElement, NULL);
		app::ContentSizeFitter* newContentSizeFitter = (app::ContentSizeFitter*)app::GameObject_AddComponent(gameObject, typeContentSizeFitter, NULL);

		app::LayoutElement_set_minHeight(newLayoutElement, (float)fontSize + 3, NULL);
		app::LayoutElement_set_minWidth(newLayoutElement, ((float)fontSize * text.size() + 3) * 0.6, NULL);
		app::ContentSizeFitter_set_horizontalFit(newContentSizeFitter, app::ContentSizeFitter_FitMode__Enum::ContentSizeFitter_FitMode__Enum_MinSize, NULL);
		app::ContentSizeFitter_set_verticalFit(newContentSizeFitter, app::ContentSizeFitter_FitMode__Enum::ContentSizeFitter_FitMode__Enum_MinSize, NULL);

		return gameObject;
	}
}

#endif