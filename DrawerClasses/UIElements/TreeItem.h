#pragma once

#ifndef _TREEITEM_H
#define _TREEITEM_H

#include "Global.h"
#include "CreateUI.h"

namespace tem {
	class SceneHierarchy;
	class TreeItem : public Global, public OnEvents
	{
	public:
		TreeItemStruct TreeItemObjects;
		TreeItemStruct TreeItemComponentObjects;
		TreeItemStruct TreeItemChildrenObjects;
		/*app::GameObject* FoldButtonObject = nullptr;
		app::GameObject* ObjectButtonObject = nullptr;
		app::GameObject* ComponentsTree = nullptr;
		app::GameObject* ChildrenTree = nullptr;
		app::GameObject* TreeItemObject = nullptr;
		app::VerticalLayoutGroup* TreeItemObjectLayout = nullptr;
		app::VerticalLayoutGroup* TreeItemComponentLayout = nullptr;
		app::VerticalLayoutGroup* TreeItemChildrenLayout = nullptr;
		app::Button* FoldButton = nullptr;
		app::Button* ObjectButton = nullptr;*/
		tem::SceneHierarchy* HierarchyObject = nullptr;

		TreeItem();
		TreeItem(std::string treeName);

		virtual void Update() override;
		virtual void Cleanup() override;
		virtual void tem::OnEvents::OnEvent(tem::EventType type, void* ptr);
	};
}

#endif