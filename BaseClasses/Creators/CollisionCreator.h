#pragma once

#ifndef _COLLISIONCREATOR_H
#define _COLLISIONCREATOR_H

#include "Global.h"
#include "UIEvents.h"
#include "GizmoEvents.h"
#include "Tem.h"
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
		std::vector<app::SphereCollider*> AllColliders = std::vector<app::SphereCollider*>();
		std::vector<tem::Vector3> Positions = std::vector<tem::Vector3>();
		app::Mesh* mesh = nullptr;
		app::MeshCollider* Collider = nullptr;
		app::GameObject* colliderPreview = nullptr;
		app::MeshFilter* meshFilterPreview = nullptr;
		app::MeshRenderer* meshRenderer = nullptr;
		app::Material* meshPreviewMat = nullptr;
		app::GameObject* HorizontalToolbar = nullptr;
		std::vector<app::GameObject*> ToolbarButtonsObjects;
		std::vector<app::Button*> ToolbarButtons;
		bool HitCollisionHandle = false;

		CollisionCreator()
		{
			this->SelectedObject = nullptr;
			this->AllColliders = std::vector<app::SphereCollider*>();
			this->Positions = std::vector<tem::Vector3>();
			this->mesh = nullptr;
			this->Collider = nullptr;
			this->colliderPreview = nullptr;
			this->meshFilterPreview = nullptr;
			this->meshRenderer = nullptr;
			this->meshPreviewMat = nullptr;
			this->ActiveActionType = CollisionEditActionType::None;
			this->ActiveTool = CollisionToolType::Selection;
		}

		void SetupRenderer();
		virtual void Update() override;
		virtual void Cleanup() override;
		bool ShouldDrawCollision();
		void AddPosition(tem::Vector3 position);
		void DrawCollision();
		void AddSphereHandle(tem::Vector3 position);
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