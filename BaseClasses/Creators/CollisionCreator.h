#pragma once

#ifndef _COLLISIONCREATOR_H
#define _COLLISIONCREATOR_H

#include "Global.h"
#include "UIEvents.h"
#include "GizmoEvents.h"
#include "Tem.h"
#include "Collision.h"
#include "json.hpp"

namespace tem {
	enum class CollisionToolType {
		None = -1,
		Selection = 0,
		Drawing = 1,
		NewCollision = 2,
		Moving = 3
	};

	enum class CollisionEditActionType {
		UIHover = -1,
		None = 0,
		DrawingCollision = 1,
		MovingCollision = 2
	};

	class CollisionCreator : public Global, public GizmoEvents, public OnEvents
	{
	public:
		static tem::CollisionCreator Instance;

		CollisionEditActionType ActiveActionType = CollisionEditActionType::None;
		CollisionToolType ActiveTool = CollisionToolType::Selection;
		app::SphereCollider* SelectedObject = nullptr;
		int ActiveCollision = -1;
		std::vector<tem::Collision> AllCollisions = std::vector<tem::Collision>();
		app::GameObject* HorizontalToolbar = nullptr;
		std::vector<app::GameObject*> ToolbarButtonsObjects;
		std::vector<app::Button*> ToolbarButtons;
		bool HitCollisionHandle = false;
		app::GameObject* MasterCollisionObject = nullptr;

		CollisionCreator()
		{
			this->SelectedObject = nullptr;
			this->ActiveCollision = -1;
			this->AllCollisions = std::vector<tem::Collision>();
			this->ActiveActionType = CollisionEditActionType::None;
			this->ActiveTool = CollisionToolType::Selection;
			MasterCollisionObject = nullptr;
		}

		void SetupRenderer(tem::Collision& collision);
		virtual void Update() override;
		virtual void Cleanup() override;
		void LoadCollision(tem::CollisionCreator newCollision);
		void AddCollisionToolbar();

		virtual void GizmoEvents::GizmoMoved(tem::Vector3 position, tem::AxisType axis) override;
		virtual void GizmoEvents::GizmoClicked() override;
		virtual void GizmoEvents::GizmoDone() override;

		virtual void tem::OnEvents::OnEvent(tem::EventType type, void* ptr);
	};

	void to_json(nlohmann::json& j, const tem::CollisionCreator& p);
	void from_json(const nlohmann::json& j, tem::CollisionCreator& p);
}

#endif