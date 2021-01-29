#pragma once

#ifndef _GIZMO_H
#define _GIZMO_H

#include "Global.h"
#include "UIEvents.h"
#include "GizmoEvents.h"
#include "Tem.h"

namespace tem {
	enum class GizmoEditMode {
		None = -1,
		DraggingGizmo = 0,
		DragginCollisionHandle = 1,
		PaintingCollision = 2,
		ObjectSelected = 3,
		TransformingCamera = 4
	};

	enum class GizmoMode {
		None = -1,
		Move = 0,
		Scale = 1,
		Rotate = 2,
		Selection = 3
	};

	class Gizmo : public Global, public OnEvents
	{
	public:
		static Gizmo Instance;
		std::vector<GizmoEvents*> AllRegisteredObjects = std::vector<GizmoEvents*>();

		virtual void Update() override;
		virtual void Cleanup() override;

		void SetGizmoPosition(tem::Vector3 position);
		void SetupGizmo();

		virtual void tem::OnEvents::OnEvent(tem::EventType type, void* ptr);

	private:

		GizmoMode GizmoMode = GizmoMode::Move;
		GizmoEditMode GizmoEditMode = GizmoEditMode::None;
		bool INITIALIZED = false;
		bool IsDragging = false;
		bool EditingEnabled = false;
		bool DoOncePerFrame = false;
		bool FreezeOri = false;
		tem::Vector3 PreviouisMousePosition = tem::Vector3();
		tem::Vector3 PreviousRotation = tem::Vector3();
		int FrameDelay = 0;
		app::GameObject* GizmoHandle = nullptr;
		app::GameObject* XAxisGizmo = nullptr;
		app::GameObject* YAxisGizmo = nullptr;
		app::GameObject* XYAxisGizmo = nullptr;
		app::GameObject* XAxisRotation = nullptr;
		app::GameObject* YAxisRotation = nullptr;
		app::GameObject* ZAxisRotation = nullptr;
		app::BoxCollider* XCollider = nullptr;
		app::BoxCollider* YCollider = nullptr;
		app::BoxCollider* XYCollider = nullptr;
		app::MeshCollider* XRotationCollider = nullptr;
		app::MeshCollider* YRotationCollider = nullptr;
		app::MeshCollider* ZRotationCollider = nullptr;
		tem::AxisType Selected = tem::AxisType::NONE;
		app::GameObject* SelectedGameObject = nullptr;
		std::vector<app::GameObject*> ToolbarSelectablesObjects;
		std::vector<app::Selectable*> ToolbarSelectable;
		int XAxisInstanceId = -1;
		int YAxisInstanceId = -1;
		int XYAxisInstanceId = -1;
		int XRotationInstanceId = -1;
		int YRotationInstanceId = -1;
		int ZRotationInstanceId = -1;

		void CreateMoveGizmo();
		void ToggleFreeze();
		void SetFreeze(bool value);
	};
}

#endif