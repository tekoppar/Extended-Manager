#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <string>
#include <vector>

#include "StringUtils.h"
#include "ManagerDef.h"
#include "tem.h"
#include "MeshUtility.h"
#include "Global.h"
#include "GizmoEvents.h"
#include "TemSceneHelper.h"
#include "SceneList.h"
#include "CreateUI.h"
#include "UIEvents.h"

#include "Gizmo.h"

namespace tem {

	tem::Gizmo tem::Gizmo::Instance = tem::Gizmo();

	void tem::Gizmo::SetupGizmo()
	{
		CreateMoveGizmo();
	}

	void tem::Gizmo::CreateMoveGizmo()
	{
		GizmoHandle = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
		app::GameObject__ctor(GizmoHandle, string_new("GizmoHandle"), NULL);
		app::GameObject_set_layer(GizmoHandle, 11, NULL);


		app::Type* typeSelectable = GetType("UnityEngine.UI", "Selectable");
		app::Type* typeImage = GetType("UnityEngine.UI", "Image");
		app::Type* typeLayoutElement = GetType("UnityEngine.UI", "LayoutElement");

		app::GameObject* selectableObject = DrawUI::Selectable("Freeze");
		ToolbarSelectablesObjects.push_back(selectableObject);
		app::Texture2D* image = DrawUI::LoadImageFromPath(ManagerPath + "Icons\\toolicons\\Tex_freeze_t.png", 64, 64);
		ToolbarSelectable.push_back((app::Selectable*)app::GameObject_GetComponent(selectableObject, typeSelectable, NULL));
		DrawUI::SetImageInObject(selectableObject, image);
		tem::UIEvents::Instance->OnClickEvents[selectableObject] = this;
		tem::UIEvents::Instance->AddObjectToCanvas(selectableObject);

		selectableObject = DrawUI::Selectable("Unfreeze");
		ToolbarSelectablesObjects.push_back(selectableObject);
		image = DrawUI::LoadImageFromPath(ManagerPath + "Icons\\toolicons\\Tex_unfreeze_t.png", 64, 64);
		ToolbarSelectable.push_back((app::Selectable*)app::GameObject_GetComponent(selectableObject, typeSelectable, NULL));
		DrawUI::SetImageInObject(selectableObject, image);
		tem::UIEvents::Instance->OnClickEvents[selectableObject] = this;
		tem::UIEvents::Instance->AddObjectToCanvas(selectableObject);

		selectableObject = DrawUI::Selectable("Selection");
		ToolbarSelectablesObjects.push_back(selectableObject);
		image = DrawUI::LoadImageFromPath(ManagerPath + "Icons\\toolicons\\Tex_select_t.png", 64, 64);
		ToolbarSelectable.push_back((app::Selectable*)app::GameObject_GetComponent(selectableObject, typeSelectable, NULL));
		DrawUI::SetImageInObject(selectableObject, image);
		tem::UIEvents::Instance->OnClickEvents[selectableObject] = this;
		tem::UIEvents::Instance->AddObjectToCanvas(selectableObject);

		selectableObject = DrawUI::Selectable("MoveGizmo");
		ToolbarSelectablesObjects.push_back(selectableObject);
		image = DrawUI::LoadImageFromPath(ManagerPath + "Icons\\toolicons\\Tex_move_t.png", 64, 64);
		ToolbarSelectable.push_back((app::Selectable*)app::GameObject_GetComponent(selectableObject, typeSelectable, NULL));
		DrawUI::SetImageInObject(selectableObject, image);
		tem::UIEvents::Instance->OnClickEvents[selectableObject] = this;
		tem::UIEvents::Instance->AddObjectToCanvas(selectableObject);

		selectableObject = DrawUI::Selectable("RotateGizmo");
		ToolbarSelectablesObjects.push_back(selectableObject);
		image = DrawUI::LoadImageFromPath(ManagerPath + "Icons\\toolicons\\Tex_rotate_t.png", 64, 64);
		ToolbarSelectable.push_back((app::Selectable*)app::GameObject_GetComponent(selectableObject, typeSelectable, NULL));
		DrawUI::SetImageInObject(selectableObject, image);
		tem::UIEvents::Instance->OnClickEvents[selectableObject] = this;
		tem::UIEvents::Instance->AddObjectToCanvas(selectableObject);


		XAxisGizmo = MeshUtility::CreateMeshObjectFromFile(ManagerPath + "models\\gizmo_arrow.obj");
		YAxisGizmo = MeshUtility::CreateMeshObjectFromFile(ManagerPath + "models\\gizmo_arrow.obj");
		XYAxisGizmo = MeshUtility::CreateMeshObjectFromFile(ManagerPath + "models\\gizmo_handle_xy.obj");
		XAxisRotation = MeshUtility::CreateMeshObjectFromFile(ManagerPath + "models\\gizmo_ring_x.obj");
		YAxisRotation = MeshUtility::CreateMeshObjectFromFile(ManagerPath + "models\\gizmo_ring_y.obj");
		ZAxisRotation = MeshUtility::CreateMeshObjectFromFile(ManagerPath + "models\\gizmo_ring_z.obj");
		app::GameObject_set_layer(XAxisGizmo, 1, NULL);
		app::GameObject_set_layer(YAxisGizmo, 1, NULL);
		app::GameObject_set_layer(XYAxisGizmo, 1, NULL);
		app::GameObject_set_layer(XAxisRotation, 1, NULL);
		app::GameObject_set_layer(YAxisRotation, 1, NULL);
		app::GameObject_set_layer(ZAxisRotation, 1, NULL);

		TransformSetParent(XAxisGizmo, GizmoHandle);
		TransformSetLocalPosition(XAxisGizmo, tem::Vector3(0.0f, 0.0f, -3.0f));
		TransformSetEulerAngles(XAxisGizmo, tem::Vector3(90.0f, 180.0f, 90.0f));

		TransformSetParent(YAxisGizmo, GizmoHandle);
		TransformSetLocalPosition(YAxisGizmo, tem::Vector3(0.0f, 0.0f, -3.0f));
		TransformSetEulerAngles(YAxisGizmo, tem::Vector3(180.0f, 90.0f, 0.0f));

		TransformSetParent(XYAxisGizmo, GizmoHandle);
		TransformSetLocalPosition(XYAxisGizmo, tem::Vector3(0.0f, 0.0f, -3.0f));
		TransformSetEulerAngles(XYAxisGizmo, tem::Vector3(180.0f, 90.0f, 0.0f));

		TransformSetParent(XAxisRotation, GizmoHandle);
		TransformSetLocalPosition(XAxisRotation, tem::Vector3(0.0f, 0.0f, -3.0f));
		TransformSetEulerAngles(XAxisRotation, tem::Vector3(0.0f, 0.0f, 0.0f));

		TransformSetParent(YAxisRotation, GizmoHandle);
		TransformSetLocalPosition(YAxisRotation, tem::Vector3(0.0f, 0.0f, -3.0f));
		TransformSetEulerAngles(YAxisRotation, tem::Vector3(0.0f, 0.0f, 0.0f));

		TransformSetParent(ZAxisRotation, GizmoHandle);
		TransformSetLocalPosition(ZAxisRotation, tem::Vector3(0.0f, 0.0f, -3.0f));
		TransformSetEulerAngles(ZAxisRotation, tem::Vector3(0.0f, 0.0f, 0.0f));

		app::String* TextureName1 = string_new("_Color");
		app::String* EmiColor = string_new("_EmissivityColor");
		app::String* TextureMultiplyColor = string_new("_MultiplyLayerColor");
		app::MeshRenderer* tempMeshRenderer = (app::MeshRenderer*)GetComponentByType(XAxisGizmo, "UnityEngine", "MeshRenderer");
		app::Material* tempMat = app::Renderer_GetMaterial((app::Renderer*)tempMeshRenderer, NULL);
		app::Material_SetColor(tempMat, TextureName1, tem::Vector4(1.0f, 1.0f, 1.0f, 1.0f).ToColor(), NULL);
		app::Material_SetColor(tempMat, EmiColor, tem::Vector4(1.1f, 0.1f, 0.1f, 1.0f).ToColor(), NULL);
		app::Material_SetColor(tempMat, TextureMultiplyColor, (tem::Vector4(1.5f, 0.1f, 0.1f, 1.0f) * tem::Vector4(0.009f, 0.009f, 0.009f, 1.0f)).ToColor(), NULL);
		app::Material_set_renderQueue(tempMat, 2000, NULL);
		app::Renderer_set_renderingLayerMask((app::Renderer*)tempMeshRenderer, 1, NULL);// 263200, NULL);
		app::Renderer_set_sortingOrder((app::Renderer*)tempMeshRenderer, 26810, NULL);
		app::Renderer_set_moonOffsetZ((app::Renderer*)tempMeshRenderer, -0.004372681f, NULL);
		app::Renderer_set_customBounds((app::Renderer*)tempMeshRenderer, tem::Bounds(tem::Vector3(0.0f), tem::Vector3(24.0f, 1.0f, 60.0f)).ToMoon(), NULL);

		tempMeshRenderer = (app::MeshRenderer*)GetComponentByType(YAxisGizmo, "UnityEngine", "MeshRenderer");
		tempMat = app::Renderer_GetMaterial((app::Renderer*)tempMeshRenderer, NULL);
		app::Material_SetColor(tempMat, TextureName1, tem::Vector4(1.0f, 1.0f, 1.0f, 1.0f).ToColor(), NULL);
		app::Material_SetColor(tempMat, EmiColor, tem::Vector4(0.1f, 0.1f, 1.1f, 1.0f).ToColor(), NULL);
		app::Material_SetColor(tempMat, TextureMultiplyColor, (tem::Vector4(0.1f, 0.1f, 1.5f, 1.0f) * tem::Vector4(0.009f, 0.009f, 0.009f, 1.0f)).ToColor(), NULL);
		app::Material_set_renderQueue(tempMat, 2000, NULL);
		app::Renderer_set_renderingLayerMask((app::Renderer*)tempMeshRenderer, 263200, NULL);// 263200, NULL);
		app::Renderer_set_sortingOrder((app::Renderer*)tempMeshRenderer, 1, NULL);
		app::Renderer_set_moonOffsetZ((app::Renderer*)tempMeshRenderer, -0.004372681f, NULL);
		app::Renderer_set_customBounds((app::Renderer*)tempMeshRenderer, tem::Bounds(tem::Vector3(0.0f), tem::Vector3(1.0f, 24.0f, 60.0f)).ToMoon(), NULL);

		tempMeshRenderer = (app::MeshRenderer*)GetComponentByType(XYAxisGizmo, "UnityEngine", "MeshRenderer");
		tempMat = app::Renderer_GetMaterial((app::Renderer*)tempMeshRenderer, NULL);
		app::Material_SetColor(tempMat, TextureName1, tem::Vector4(0.96862f, 0.7921f, 0.09411f, 1.0f).ToColor(), NULL);
		app::Material_SetColor(tempMat, EmiColor, tem::Vector4(0.96862f, 0.7921f, 0.09411f, 1.0f).ToColor(), NULL);
		app::Material_SetColor(tempMat, TextureMultiplyColor, (tem::Vector4(0.96862f, 0.7921f, 0.09411f, 1.0f) * tem::Vector4(0.009f, 0.009f, 0.009f, 1.0f)).ToColor(), NULL);
		app::Material_set_renderQueue(tempMat, 2000, NULL);
		app::Renderer_set_renderingLayerMask((app::Renderer*)tempMeshRenderer, 263200, NULL);// 263200, NULL);
		app::Renderer_set_sortingOrder((app::Renderer*)tempMeshRenderer, 1, NULL);
		app::Renderer_set_moonOffsetZ((app::Renderer*)tempMeshRenderer, -0.004372681f, NULL);
		app::Renderer_set_customBounds((app::Renderer*)tempMeshRenderer, tem::Bounds(tem::Vector3(0.0f), tem::Vector3(1.0f, 24.0f, 60.0f)).ToMoon(), NULL);

		tempMeshRenderer = (app::MeshRenderer*)GetComponentByType(XAxisRotation, "UnityEngine", "MeshRenderer");
		tempMat = app::Renderer_GetMaterial((app::Renderer*)tempMeshRenderer, NULL);
		app::Material_SetColor(tempMat, TextureName1, tem::Vector4(1.0f, 1.0f, 1.0f, 1.0f).ToColor(), NULL);
		app::Material_SetColor(tempMat, EmiColor, tem::Vector4(1.1f, 0.1f, 0.1f, 1.0f).ToColor(), NULL);
		app::Material_SetColor(tempMat, TextureMultiplyColor, (tem::Vector4(1.5f, 0.1f, 0.1f, 1.0f) * tem::Vector4(0.009f, 0.009f, 0.009f, 1.0f)).ToColor(), NULL);
		app::Material_set_renderQueue(tempMat, 2000, NULL);
		app::Renderer_set_renderingLayerMask((app::Renderer*)tempMeshRenderer, 263200, NULL);// 263200, NULL);
		app::Renderer_set_sortingOrder((app::Renderer*)tempMeshRenderer, 1, NULL);
		app::Renderer_set_moonOffsetZ((app::Renderer*)tempMeshRenderer, -0.004372681f, NULL);
		app::Renderer_set_customBounds((app::Renderer*)tempMeshRenderer, tem::Bounds(tem::Vector3(0.0f), tem::Vector3(1.0f, 24.0f, 60.0f)).ToMoon(), NULL);

		tempMeshRenderer = (app::MeshRenderer*)GetComponentByType(YAxisRotation, "UnityEngine", "MeshRenderer");
		tempMat = app::Renderer_GetMaterial((app::Renderer*)tempMeshRenderer, NULL);
		app::Material_SetColor(tempMat, TextureName1, tem::Vector4(1.0f, 1.0f, 1.0f, 1.0f).ToColor(), NULL);
		app::Material_SetColor(tempMat, EmiColor, tem::Vector4(0.1f, 1.1f, 0.1f, 1.0f).ToColor(), NULL);
		app::Material_SetColor(tempMat, TextureMultiplyColor, (tem::Vector4(0.1f, 1.5f, 0.1f, 1.0f) * tem::Vector4(0.009f, 0.009f, 0.009f, 1.0f)).ToColor(), NULL);
		app::Material_set_renderQueue(tempMat, 2000, NULL);
		app::Renderer_set_renderingLayerMask((app::Renderer*)tempMeshRenderer, 263200, NULL);// 263200, NULL);
		app::Renderer_set_sortingOrder((app::Renderer*)tempMeshRenderer, 1, NULL);
		app::Renderer_set_moonOffsetZ((app::Renderer*)tempMeshRenderer, -0.004372681f, NULL);
		app::Renderer_set_customBounds((app::Renderer*)tempMeshRenderer, tem::Bounds(tem::Vector3(0.0f), tem::Vector3(1.0f, 24.0f, 60.0f)).ToMoon(), NULL);

		tempMeshRenderer = (app::MeshRenderer*)GetComponentByType(ZAxisRotation, "UnityEngine", "MeshRenderer");
		tempMat = app::Renderer_GetMaterial((app::Renderer*)tempMeshRenderer, NULL);
		app::Material_SetColor(tempMat, TextureName1, tem::Vector4(1.0f, 1.0f, 1.0f, 1.0f).ToColor(), NULL);
		app::Material_SetColor(tempMat, EmiColor, tem::Vector4(0.1f, 0.1f, 1.1f, 1.0f).ToColor(), NULL);
		app::Material_SetColor(tempMat, TextureMultiplyColor, (tem::Vector4(0.1f, 0.1f, 1.5f, 1.0f) * tem::Vector4(0.009f, 0.009f, 0.009f, 1.0f)).ToColor(), NULL);
		app::Material_set_renderQueue(tempMat, 2000, NULL);
		app::Renderer_set_renderingLayerMask((app::Renderer*)tempMeshRenderer, 263200, NULL);// 263200, NULL);
		app::Renderer_set_sortingOrder((app::Renderer*)tempMeshRenderer, 1, NULL);
		app::Renderer_set_moonOffsetZ((app::Renderer*)tempMeshRenderer, -0.004372681f, NULL);
		app::Renderer_set_customBounds((app::Renderer*)tempMeshRenderer, tem::Bounds(tem::Vector3(0.0f), tem::Vector3(1.0f, 24.0f, 60.0f)).ToMoon(), NULL);

		auto Il2ClassBoxCollider = GetClass("UnityEngine", "BoxCollider");
		app::Type* BoxColliderType = GetTypeFromClass(Il2ClassBoxCollider);
		XCollider = (app::BoxCollider*)app::GameObject_AddComponent(XAxisGizmo, BoxColliderType, NULL);
		YCollider = (app::BoxCollider*)app::GameObject_AddComponent(YAxisGizmo, BoxColliderType, NULL);
		XYCollider = (app::BoxCollider*)app::GameObject_AddComponent(XYAxisGizmo, BoxColliderType, NULL);

		app::MeshFilter* tempMeshFilter = (app::MeshFilter*)GetComponentByType(YAxisGizmo, "UnityEngine", "MeshFilter");
		app::Mesh* tempMesh = app::MeshFilter_get_sharedMesh(tempMeshFilter, NULL);
		app::Bounds bound = app::Mesh_get_bounds(tempMesh, NULL);
		app::BoxCollider_set_size(XCollider, (tem::Vector3(bound.m_Extents) * 1.5).ToMoon(), NULL);
		app::BoxCollider_set_center(XCollider, bound.m_Center, NULL);

		app::BoxCollider_set_size(YCollider, (tem::Vector3(bound.m_Extents) * 1.5).ToMoon(), NULL);
		app::BoxCollider_set_center(YCollider, bound.m_Center, NULL);

		tempMeshFilter = (app::MeshFilter*)GetComponentByType(XYAxisGizmo, "UnityEngine", "MeshFilter");
		tempMesh = app::MeshFilter_get_sharedMesh(tempMeshFilter, NULL);
		bound = app::Mesh_get_bounds(tempMesh, NULL);

		app::BoxCollider_set_size(XYCollider, (tem::Vector3(bound.m_Extents) * 1.5).ToMoon(), NULL);
		app::BoxCollider_set_center(XYCollider, bound.m_Center, NULL);


		auto Il2ClassMeshCollider = GetClass("UnityEngine", "MeshCollider");
		app::Type* MeshColliderType = GetTypeFromClass(Il2ClassMeshCollider);
		tempMeshFilter = (app::MeshFilter*)GetComponentByType(XAxisRotation, "UnityEngine", "MeshFilter");
		tempMesh = app::MeshFilter_get_sharedMesh(tempMeshFilter, NULL);
		XRotationCollider = (app::MeshCollider*)app::GameObject_AddComponent(XAxisRotation, MeshColliderType, NULL);
		app::MeshCollider_set_sharedMesh(XRotationCollider, tempMesh, NULL);
		tempMeshFilter = (app::MeshFilter*)GetComponentByType(YAxisRotation, "UnityEngine", "MeshFilter");
		tempMesh = app::MeshFilter_get_sharedMesh(tempMeshFilter, NULL);
		YRotationCollider = (app::MeshCollider*)app::GameObject_AddComponent(YAxisRotation, MeshColliderType, NULL);
		app::MeshCollider_set_sharedMesh(YRotationCollider, tempMesh, NULL);
		tempMeshFilter = (app::MeshFilter*)GetComponentByType(ZAxisRotation, "UnityEngine", "MeshFilter");
		tempMesh = app::MeshFilter_get_sharedMesh(tempMeshFilter, NULL);
		ZRotationCollider = (app::MeshCollider*)app::GameObject_AddComponent(ZAxisRotation, MeshColliderType, NULL);
		app::MeshCollider_set_sharedMesh(ZRotationCollider, tempMesh, NULL);

		app::DebugRendererSettings* debug = (*app::DebugRendererSettings__TypeInfo)->static_fields->s_instance;
		app::List_1_UnityEngine_Collider__Add(debug->fields.m_cachedDamageColliders, (app::Collider*)XCollider, (*app::List_1_UnityEngine_Collider__Add__MethodInfo));
		app::List_1_UnityEngine_Collider__Add(debug->fields.m_cachedDamageColliders, (app::Collider*)YCollider, (*app::List_1_UnityEngine_Collider__Add__MethodInfo));
		app::List_1_UnityEngine_Collider__Add(debug->fields.m_cachedDamageColliders, (app::Collider*)XYCollider, (*app::List_1_UnityEngine_Collider__Add__MethodInfo));

		XAxisInstanceId = app::Object_1_GetInstanceID((app::Object_1*)XCollider, NULL);
		YAxisInstanceId = app::Object_1_GetInstanceID((app::Object_1*)YCollider, NULL);
		XYAxisInstanceId = app::Object_1_GetInstanceID((app::Object_1*)XYCollider, NULL);
		XRotationInstanceId = app::Object_1_GetInstanceID((app::Object_1*)XRotationCollider, NULL);
		YRotationInstanceId = app::Object_1_GetInstanceID((app::Object_1*)YRotationCollider, NULL);
		ZRotationInstanceId = app::Object_1_GetInstanceID((app::Object_1*)ZRotationCollider, NULL);
		INITIALIZED = true;

		app::GameObject_set_active(XAxisGizmo, false, NULL);
		app::GameObject_set_active(YAxisGizmo, false, NULL);
		app::GameObject_set_active(XYAxisGizmo, false, NULL);
		app::GameObject_set_active(XAxisRotation, false, NULL);
		app::GameObject_set_active(YAxisRotation, false, NULL);
		app::GameObject_set_active(ZAxisRotation, false, NULL);

		tem::UIEvents::Instance->AddObjectToCanvas(GizmoHandle);
	}

	void tem::Gizmo::Cleanup()
	{
		AllRegisteredObjects.clear();
		app::Object_1_Destroy_1((app::Object_1*)XCollider, NULL);
		app::Object_1_Destroy_1((app::Object_1*)XAxisGizmo, NULL);
		app::Object_1_Destroy_1((app::Object_1*)YCollider, NULL);
		app::Object_1_Destroy_1((app::Object_1*)YAxisGizmo, NULL);
		app::Object_1_Destroy_1((app::Object_1*)XYCollider, NULL);
		app::Object_1_Destroy_1((app::Object_1*)XYAxisGizmo, NULL);

		app::Object_1_Destroy_1((app::Object_1*)XRotationCollider, NULL);
		app::Object_1_Destroy_1((app::Object_1*)XAxisRotation, NULL);
		app::Object_1_Destroy_1((app::Object_1*)YRotationCollider, NULL);
		app::Object_1_Destroy_1((app::Object_1*)YAxisRotation, NULL);
		app::Object_1_Destroy_1((app::Object_1*)ZRotationCollider, NULL);
		app::Object_1_Destroy_1((app::Object_1*)ZAxisRotation, NULL);

		app::Object_1_Destroy_1((app::Object_1*)GizmoHandle, NULL);
		XCollider = nullptr;
		XAxisGizmo = nullptr;
		YCollider = nullptr;
		YAxisGizmo = nullptr;
		XYCollider = nullptr;
		XYAxisGizmo = nullptr;
		GizmoHandle = nullptr;
	}

	void tem::Gizmo::Update()
	{
		if (INITIALIZED == true)
		{
			DoOncePerFrame = false;
			FrameDelay++;
			bool isLeftMouse = app::Input_GetMouseButtonDown(0, NULL);
			bool isLeftMouseHeld = app::Input_GetMouseButton(0, NULL);
			bool isMiddleMouseHeld = app::Input_GetKey(app::KeyCode__Enum::KeyCode__Enum_Mouse2, NULL);
			tem::Vector3 mousePosition = app::Input_get_mousePosition(NULL);
			tem::Vector3 mouseDelta = PreviouisMousePosition - mousePosition;

			if (app::CharacterPlatformMovement_get_IsSuspended(MDV::MoonSein->fields.PlatformBehaviour->fields.PlatformMovement, NULL) != FreezeOri)
				SetFreeze(FreezeOri);

			if (isLeftMouseHeld || isMiddleMouseHeld)
			{
				tem::Vector3 position = app::MoonInput_get_mousePosition(NULL);
				tem::Vector3 cameraPosition = TransformGetPosition(app::Component_1_get_gameObject((app::Component_1*)MDV::MoonCamera, NULL));
				app::Ray ray = app::Camera_ScreenPointToRay_2(MDV::MoonCamera, position.ToMoon(), NULL);// tem::Vector3(position.X, position.Y, std::fabs(cameraPosition.Z)).ToMoon(), NULL);
				app::RaycastHit hit = app::RaycastHit();
				bool hitSomething = app::Physics_Raycast_14(ray, &hit, 500, NULL);
				tem::Vector3 newAxisPos = app::Camera_ScreenToWorldPoint_1(MDV::MoonCamera, tem::Vector3(position.X, position.Y, std::fabs(cameraPosition.Z)).ToMoon(), NULL);

				if (true == false && isMiddleMouseHeld == true && (mouseDelta.X > 0.1f || mouseDelta.Y > 0.1f))
				{
					tem::Vector2 cameraPosition = app::ScenesManager_get_CurrentCameraTargetPosition(TemSceneHelper::SceneManager, NULL);
					cameraPosition += mouseDelta;
					app::ScenesManager_set_CurrentCameraTargetPosition(TemSceneHelper::SceneManager, cameraPosition.ToVector2(), NULL);
				}

				tem::Vector3 oldPos = TransformGetPosition(GizmoHandle);

				tem::Vector3 oldRot;
				if (MDV::SelectedObject != nullptr)
					oldRot = TransformGetEulerAngles(MDV::SelectedObject);

				if (XAxisInstanceId == hit.m_Collider && Selected == tem::AxisType::NONE)
				{
					Selected = tem::AxisType::X;
					GizmoMode = GizmoMode::Move;
				}
				else if (YAxisInstanceId == hit.m_Collider && Selected == tem::AxisType::NONE)
				{
					Selected = tem::AxisType::Y;
					GizmoMode = GizmoMode::Move;
				}
				else if (XYAxisInstanceId == hit.m_Collider && Selected == tem::AxisType::NONE)
				{
					Selected = tem::AxisType::XY;
					GizmoMode = GizmoMode::Move;
				}
				else if (XRotationInstanceId == hit.m_Collider && Selected == tem::AxisType::NONE)
				{
					Selected = tem::AxisType::X;
					GizmoMode = GizmoMode::Rotate;
				}
				else if (YRotationInstanceId == hit.m_Collider && Selected == tem::AxisType::NONE)
				{
					Selected = tem::AxisType::Y;
					GizmoMode = GizmoMode::Rotate;
				}
				else if (ZRotationInstanceId == hit.m_Collider && Selected == tem::AxisType::NONE)
				{
					Selected = tem::AxisType::Z;
					GizmoMode = GizmoMode::Rotate;
				}

				switch (GizmoMode)
				{
					case GizmoMode::Move:
					{
						switch (Selected)
						{
							case tem::AxisType::X: oldPos.X = newAxisPos.X; break;
							case tem::AxisType::Y: oldPos.Y = newAxisPos.Y; break;
							case tem::AxisType::Z: oldPos.Z = newAxisPos.Z; break;
							case tem::AxisType::XY: oldPos.X = newAxisPos.X; oldPos.Y = newAxisPos.Y; break;
						}
					}
					break;
				}

				if (Selected != tem::AxisType::NONE)
				{
					TransformSetPosition(GizmoHandle, oldPos);

					for (auto& gizmo : AllRegisteredObjects)
					{
						if (gizmo != nullptr)
						{
							if (isLeftMouse == true)
								gizmo->GizmoClicked();

							if (isLeftMouseHeld == true || Gizmo::IsDragging == true)
							{
								gizmo->GizmoMoved(oldPos, Selected);
							}
						}
					}

					if (MDV::SelectedObject != nullptr)
					{
						if (GizmoMode == GizmoMode::Move)
						{
							TransformSetPosition(MDV::SelectedObject, tem::Vector3(oldPos.X, oldPos.Y, TransformGetPosition(MDV::SelectedObject).z));
							
							if (tem::SceneList::ActiveHiearchy != nullptr)
								tem::SceneList::ActiveHiearchy->Object.FieldPropertyHasChanged(MDV::SelectedObject, "Transform", "position", oldPos.ToString());
						}
					}

					Gizmo::IsDragging = true;
				}
			}
			else
			{
				for (auto& gizmo : AllRegisteredObjects)
				{
					if (gizmo != nullptr)
						gizmo->GizmoDone();
				}
				Gizmo::IsDragging = false;
				Selected = tem::AxisType::NONE;
			}

			PreviouisMousePosition = mousePosition;
		}
	}

	void tem::Gizmo::SetGizmoPosition(tem::Vector3 position)
	{
		TransformSetPosition(GizmoHandle, tem::Vector3(position.X, position.Y, 0.0f));
	}

	void tem::Gizmo::OnEvent(tem::EventType type, void* ptr)
	{
		switch (type)
		{
			case tem::EventType::MouseMove:
			{
				for (auto& button : this->ToolbarSelectablesObjects)
				{
					if (DoOncePerFrame == false && ptr == button && GizmoMode == GizmoMode::Rotate && Selected != tem::AxisType::NONE)
					{
						DoOncePerFrame = true;
						tem::Vector3 position = app::MoonInput_get_mousePosition(NULL);
						tem::Vector3 cameraPosition = TransformGetPosition(app::Component_1_get_gameObject((app::Component_1*)MDV::MoonCamera, NULL));
						app::Ray ray = app::Camera_ScreenPointToRay_2(MDV::MoonCamera, tem::Vector3(position.X, position.Y, std::fabs(cameraPosition.Z)).ToMoon(), NULL);
						app::RaycastHit hit = app::RaycastHit();
						bool hitSomething = app::Physics_Raycast_14(ray, &hit, 500, NULL);
						tem::Vector3 newAxisPos = app::Camera_ScreenToWorldPoint_1(MDV::MoonCamera, tem::Vector3(position.X, position.Y, std::fabs(cameraPosition.Z)).ToMoon(), NULL);

						tem::Vector3 gizmoPos = TransformGetPosition(GizmoHandle);
						float signedAngle = tem::Angle(gizmoPos, newAxisPos);

						switch (Selected)
						{
							case tem::AxisType::X: PreviousRotation.X = signedAngle; break;
							case tem::AxisType::Y: PreviousRotation.Y = signedAngle; break;
							case tem::AxisType::Z: PreviousRotation.Z = signedAngle; break;
						}

						if (MDV::SelectedObject != nullptr)
						{
							TransformSetQuatRotation(MDV::SelectedObject, PreviousRotation);
							tem::SceneList::ActiveHiearchy->Object.FieldPropertyHasChanged(MDV::SelectedObject, "Transform", "eulerAngles", PreviousRotation.ToString());
						}
					}
				}
			}
			break;

			//case tem::EventType::MouseLeave: break;
			case tem::EventType::MouseEnter: tem::UIEvents::IsOverUIElement = true; break;

				//case tem::EventType::RightMouseDown:  break;

				//case tem::EventType::LeftMouseUp:  break;
			case tem::EventType::PointerEvent:
			{
				for (int i = 0; i < ToolbarSelectablesObjects.size(); i++)
				{
					if (ToolbarSelectablesObjects[i] == ptr)
					{
						app::GameObject_set_active(XAxisGizmo, false, NULL);
						app::GameObject_set_active(YAxisGizmo, false, NULL);
						app::GameObject_set_active(XYAxisGizmo, false, NULL);
						app::GameObject_set_active(XAxisRotation, false, NULL);
						app::GameObject_set_active(YAxisRotation, false, NULL);
						app::GameObject_set_active(ZAxisRotation, false, NULL);
						PreviousRotation = 0.0f;

						switch (i)
						{
							case 0:
							case 1:
							{
								ToggleFreeze();
							}
							break;

							case 2:
							{
								GizmoMode = tem::GizmoMode::Selection;
							}
							break;

							case 3:
							{
								GizmoMode = tem::GizmoMode::Move;
								app::GameObject_set_active(XAxisGizmo, true, NULL);
								app::GameObject_set_active(YAxisGizmo, true, NULL);
								app::GameObject_set_active(XYAxisGizmo, true, NULL);
							}
							break;

							case 4:
							{
								GizmoMode = tem::GizmoMode::Rotate;
								app::GameObject_set_active(XAxisRotation, true, NULL);
								app::GameObject_set_active(YAxisRotation, true, NULL);
								app::GameObject_set_active(ZAxisRotation, true, NULL);
							}
							break;
						}
					}

				}
			}
			break;
		}
	}

	void tem::Gizmo::ToggleFreeze()
	{
		if (FreezeOri == false)
		{
			app::GameObject_set_active(ToolbarSelectablesObjects[0], false, NULL);
			app::GameObject_set_active(ToolbarSelectablesObjects[1], true, NULL);
			app::SeinController_set_IsSuspended(MDV::MoonSein->fields.Controller, true, NULL);
			app::CharacterPlatformMovement_set_IsSuspended(MDV::MoonSein->fields.PlatformBehaviour->fields.PlatformMovement, true, NULL);
		}
		else
		{
			app::GameObject_set_active(ToolbarSelectablesObjects[0], true, NULL);
			app::GameObject_set_active(ToolbarSelectablesObjects[1], false, NULL);
			app::SeinController_set_IsSuspended(MDV::MoonSein->fields.Controller, false, NULL);
			app::CharacterPlatformMovement_set_IsSuspended(MDV::MoonSein->fields.PlatformBehaviour->fields.PlatformMovement, false, NULL);
		}
		FreezeOri = !FreezeOri;
	}

	void tem::Gizmo::SetFreeze(bool value)
	{
		app::GameObject_set_active(ToolbarSelectablesObjects[0], !value, NULL);
		app::GameObject_set_active(ToolbarSelectablesObjects[1], value, NULL);
		app::SeinController_set_IsSuspended(MDV::MoonSein->fields.Controller, value, NULL);
		app::CharacterPlatformMovement_set_IsSuspended(MDV::MoonSein->fields.PlatformBehaviour->fields.PlatformMovement, value, NULL);
	}
}