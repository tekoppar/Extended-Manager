#pragma once

#ifndef _CREATEUI_H
#define _CREATEUI_H

class TreeItemStruct {
public:
	app::GameObject* FoldButtonObject = nullptr;
	app::GameObject* ObjectButtonObject = nullptr;
	app::GameObject* ChildrenTree = nullptr;
	app::GameObject* TreeItemObject = nullptr;
	app::VerticalLayoutGroup* TreeItemObjectLayout = nullptr;
	app::VerticalLayoutGroup* TreeItemChildrenLayout = nullptr;
	app::Button* FoldButton = nullptr;
	app::Button* ObjectButton = nullptr;
	bool IsFolded = true;

	void ExpandTree();
};

class DropdownHorizontal
{
public:
	app::GameObject* DropdownObject = nullptr;
	app::GameObject* DropdownChildren = nullptr;
	app::HorizontalLayoutGroup* DropdownChildrenLayout = nullptr;
	app::GameObject* FoldSelectableObject = nullptr;
	app::Selectable* FoldSelectable = nullptr;
	bool IsFolded = true;

	void ExpandDropdown();
};

class TemButton;

class DrawUI {
public:
	static std::vector<app::Texture2D*> AllTexture2D;
	static std::vector<std::string> AllTexture2DNames;
	static std::vector<TemButton*> AllTemButtons;

	static int FindTextureIndex(std::string name);
	static app::GameObject* EventSystem(const std::string& name);
	static app::GameObject* Image(const std::string& name, app::Material* material);
	static app::GameObject* Selectable(const std::string& name);
	static app::GameObject* Button(const std::string& text, int fontSize, app::Color color);
	static app::GameObject* Button(const std::string& name);
	static app::Button* Button(app::GameObject* object, const std::string& text, int fontSize, app::Color color);
	static app::GameObject* TreeItem(const std::string& name, app::TextAnchor__Enum textAnchor = app::TextAnchor__Enum::TextAnchor__Enum_UpperLeft);
	static app::GameObject* VerticalLayoutGroup(const std::string& name, app::TextAnchor__Enum textAnchor = app::TextAnchor__Enum::TextAnchor__Enum_UpperLeft);
	static app::GameObject* HorizontalLayoutGroup(const std::string& name, app::TextAnchor__Enum textAnchor = app::TextAnchor__Enum::TextAnchor__Enum_UpperLeft);
	static DropdownHorizontal CreateDropdownHorizontal(const std::string& name, const std::string& imagePath);
	static app::GameObject* RectMask2D(const std::string& name, float minWidth = 10, float minHeight = 10, float preferedWidth = 100, float preferedHeight = 100);
	static app::GameObject* Text(const std::string& name, const std::string& text, int fontSize, app::Color color);
	static app::GameObject* Scrollbar(app::GameObject* rectHandle, const std::string& name, app::Color color, app::Color colorHandle, bool horizontal = true);
	static app::GameObject* Dropdown(const std::string& name);
	static TreeItemStruct CreateTreeItem(const std::string& name);
	static void SetImageInObject(app::GameObject* object, app::Texture2D* texture);
	static app::Texture2D* LoadImageFromPath(std::string path, int width, int height);
};

class TemButton : public app::Button,  public app::Selectable,  app::IPointerClickHandler, app::ISubmitHandler
{
public:
	/*public IOnclick,public app::Object_1,public app::Component, app::IEventSystemHandler
	void (*onClickMethod)();
	virtual void IOnClick() override;

	app::Button* UnityButton = nullptr;
	app::GameObject* UnityGameObject = nullptr;
	app::Button_ButtonClickedEvent* UnityClickEvent = nullptr;

	TemButton()
	{
		app::Type* type = GetType("UnityEngine.UI", "Button");
		std::uintptr_t ptr = (std::uintptr_t)type->fields._impl.value;
		ptr = ptr - 0x20;
		app::Button button = *reinterpret_cast<app::Button*>(this);
		button.klass = (app::Button__Class*)(Il2CppClass*)(ptr);
		//std::string buttonName = "ButtonObject";
		//app::GameObject__ctor(this, CreateString(buttonName), NULL),
		app::Button__ctor(&button, NULL);
		//std::string buttonName = "Button";
		//UnityGameObject = DrawUI::Button(buttonName);
		//app::Type* buttonType = GetType("UnityEngine.UI", "Button");
		//UnityButton = (app::Button*)app::GameObject_GetComponent(UnityGameObject, buttonType, NULL);
		UnityClickEvent = app::Button_get_onClick(&button, NULL);
		DrawUI::AllTemButtons.push_back(this);
	}*/
};

#endif

