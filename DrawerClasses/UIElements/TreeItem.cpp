#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <filesystem>

#include "StringUtils.h"
#include "ManagerDef.h"
#include "Global.h"
#include "UIEvents.h"
#include "Gizmo.h"
#include "Tem.h"
#include "CreateUI.h"
#include "SceneHierarchy.h"
#include "SceneList.h"

#include "TreeItem.h"

namespace tem {
	void tem::TreeItem::Update()
	{
	}
	void tem::TreeItem::Cleanup()
	{
	}

	TreeItem::TreeItem()
	{
		TreeItemObjects;
		TreeItemComponentObjects;
		TreeItemChildrenObjects;
		this->HierarchyObject = nullptr;
	}

	TreeItem::TreeItem(std::string treeName)
	{
		TreeItemObjects = DrawUI::CreateTreeItem(treeName);
		TreeItemComponentObjects = DrawUI::CreateTreeItem("Components");
		TreeItemChildrenObjects = DrawUI::CreateTreeItem("Children");
		this->HierarchyObject = nullptr;

		TransformSetParent(TreeItemComponentObjects.TreeItemObject, TreeItemObjects.ChildrenTree);
		TransformSetParent(TreeItemChildrenObjects.TreeItemObject, TreeItemObjects.ChildrenTree);
		RectTransformSetSize(TreeItemObjects.TreeItemObject, tem::Vector2(14.0f, 200.0f));
		RectTransformSetSize(TreeItemObjects.ObjectButtonObject, tem::Vector2(14.0f, 186.0f));
		RectTransformSetSize(TreeItemObjects.FoldButtonObject, tem::Vector2(14.0f, 14.0f));
		RectTransformSetSize(TreeItemObjects.ChildrenTree, tem::Vector2(14.0f, 200.0f));

		RectTransformSetSize(TreeItemComponentObjects.TreeItemObject, tem::Vector2(14.0f, 200.0f));
		RectTransformSetSize(TreeItemComponentObjects.ObjectButtonObject, tem::Vector2(14.0f, 186.0f));
		RectTransformSetSize(TreeItemComponentObjects.FoldButtonObject, tem::Vector2(14.0f, 14.0f));
		RectTransformSetSize(TreeItemComponentObjects.ChildrenTree, tem::Vector2(14.0f, 200.0f));

		RectTransformSetSize(TreeItemChildrenObjects.TreeItemObject, tem::Vector2(14.0f, 200.0f));
		RectTransformSetSize(TreeItemChildrenObjects.ObjectButtonObject, tem::Vector2(14.0f, 186.0f));
		RectTransformSetSize(TreeItemChildrenObjects.FoldButtonObject, tem::Vector2(14.0f, 14.0f));
		RectTransformSetSize(TreeItemChildrenObjects.ChildrenTree, tem::Vector2(14.0f, 200.0f));

		/*TreeItemObject = DrawUI::TreeItem("TreeRoot");
		app::GameObject* treeItemHeader = DrawUI::HorizontalLayoutGroup("TreeItemHeader", app::TextAnchor__Enum::TextAnchor__Enum_UpperCenter);
		TreeItemObjectLayout = (app::VerticalLayoutGroup*)app::GameObject_GetComponent(treeItemHeader, typeVerticalLayoutGroup, NULL);
		FoldButtonObject = DrawUI::Button("X", 14, tem::Vector4(0.0f, 0.0f, 0.0f, 1.0f).ToColor());
		ObjectButtonObject = DrawUI::Button(treeName, 14, tem::Vector4(0.0f, 0.0f, 0.0f, 1.0f).ToColor());
		app::LayoutElement* tempLayout = (app::LayoutElement*)app::GameObject_GetComponent(FoldButtonObject, typeLayoutElement, NULL);
		app::LayoutElement_set_minHeight(tempLayout, 14.0f, NULL);
		app::LayoutElement_set_minWidth(tempLayout, 14.0f, NULL);
		tempLayout = (app::LayoutElement*)app::GameObject_GetComponent(ObjectButtonObject, typeLayoutElement, NULL);
		app::LayoutElement_set_minHeight(tempLayout, 14.0f, NULL);
		app::LayoutElement_set_minWidth(tempLayout, 200.0f, NULL);

		TransformSetParent(FoldButtonObject, treeItemHeader);
		TransformSetParent(ObjectButtonObject, treeItemHeader);

		RectTransformSetMinMax(treeItemHeader, tem::Vector2(0.0f, 1.0f), tem::Vector2(0.0f, 1.0f));
		RectTransformSetPivot(treeItemHeader, tem::Vector2(0.0f, 1.0f));

		ChildrenTree = DrawUI::VerticalLayoutGroup("TreeItemChildren", app::TextAnchor__Enum::TextAnchor__Enum_UpperLeft);
		TreeItemChildrenLayout = (app::VerticalLayoutGroup*)app::GameObject_GetComponent(ChildrenTree, typeVerticalLayoutGroup, NULL);
		app::RectOffset_set_left(TreeItemChildrenLayout->fields._._.m_Padding, 12.0f, NULL);

		TransformSetParent(treeItemHeader, TreeItemObject);
		TransformSetParent(ComponentsTree, TreeItemObject);
		TransformSetParent(ChildrenTree, TreeItemObject);

		RectTransformSetMinMax(ComponentsTree, tem::Vector2(0.0f, 1.0f), tem::Vector2(0.0f, 1.0f));
		RectTransformSetPivot(ComponentsTree, tem::Vector2(0.0f, 1.0f));

		RectTransformSetMinMax(ChildrenTree, tem::Vector2(0.0f, 1.0f), tem::Vector2(0.0f, 1.0f));
		RectTransformSetPivot(ChildrenTree, tem::Vector2(0.0f, 1.0f));

		FoldButton = (app::Button*)app::GameObject_GetComponent(FoldButtonObject, typeButton, NULL);
		ObjectButton = (app::Button*)app::GameObject_GetComponent(ObjectButtonObject, typeButton, NULL);
		app::GameObject_set_active(ChildrenTree, false, NULL);*/
	}

	/*void tem::TreeItem::UpdateParentPtrs()
	{
		tem::TreeItem::Instance.HierarchyObject->Object.TreeItemObject = &tem::TreeItem::Instance;
		for (int i = 0; i < tem::TreeItem::Instance.TreeItemChildren.size(); i++)
		{
			tem::TreeItem::Instance.TreeItemChildren[i].ParentTree = &tem::TreeItem::Instance;
			TransformSetParent(tem::TreeItem::Instance.TreeItemChildren[i].TreeItemObject, tem::TreeItem::Instance.ChildrenTree);
			UpdateParentPtrsP(&tem::TreeItem::Instance.TreeItemChildren[i]);
		}
	}

	void tem::TreeItem::UpdateParentPtrsP(tem::TreeItem* active)
	{
		active->HierarchyObject->Object.TreeItemObject = active;
		for (int i = 0; i < active->TreeItemChildren.size(); i++)
		{
			active->TreeItemChildren[i].ParentTree = active;
			TransformSetParent(active->TreeItemChildren[i].TreeItemObject, active->ChildrenTree);
			UpdateParentPtrsP(&active->TreeItemChildren[i]);
		}
	}*/

	void tem::TreeItem::OnEvent(tem::EventType type, void* ptr)
	{
		switch (type)
		{
			case tem::EventType::LeftMouseDown:
			{
				if (this->TreeItemObjects.FoldButtonObject == ptr && this->TreeItemObjects.ChildrenTree != nullptr)
				{
					this->TreeItemObjects.ExpandTree();
				}
				else if (this->TreeItemComponentObjects.FoldButtonObject == ptr && this->TreeItemComponentObjects.ChildrenTree != nullptr)
				{
					this->TreeItemComponentObjects.ExpandTree();
				}
				else if (this->TreeItemChildrenObjects.FoldButtonObject == ptr && this->TreeItemChildrenObjects.ChildrenTree != nullptr)
				{
					this->TreeItemChildrenObjects.ExpandTree();

					if (this->TreeItemChildrenObjects.IsFolded == false && this->HierarchyObject != nullptr && this->HierarchyObject->Object.SceneIndexHierarchy.size() > 1)
					{
						tem::SceneList::ConstructSceneHierarchy(this->HierarchyObject->Object.SceneIndexHierarchy, 1);
					}
				}
				else if ((this->TreeItemObjects.ObjectButton == ptr || this->TreeItemComponentObjects.ObjectButton == ptr || this->TreeItemChildrenObjects.ObjectButton == ptr) && this->HierarchyObject != nullptr)
				{
					tem::SceneList::ActiveHiearchy = this->HierarchyObject;

					if (this->HierarchyObject->Object.SceneIndexHierarchy.size() > 1)
						MDV::SelectedObject = tem::SceneList::GetGameObjectFromHierarchyIndex(this->HierarchyObject->Object.SceneIndexHierarchy);
				}
			}
			break;

			case tem::EventType::MouseMove:break;
			case tem::EventType::MouseLeave: break;
			case tem::EventType::MouseEnter: break;
			case tem::EventType::RightMouseDown: break;
			case tem::EventType::LeftMouseUp: break;
		}
	}
}