#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <future>
#include <unordered_map>
#include <math.h>

#include "StringUtils.h"
#include "ManagerDef.h"
#include "UIEvents.h"
#include "Gizmo.h"
#include "Tem.h"
#include "json.hpp"
#include "CreateUI.h"
#include "SceneList.h"

#include "CollisionCreator.h"

namespace tem {

	tem::CollisionCreator tem::CollisionCreator::Instance;

	void tem::CollisionCreator::Update()
	{
	}

	void tem::CollisionCreator::Cleanup()
	{
		for (auto& collision : AllCollisions)
		{
			for (app::SphereCollider* collider : collision.AllColliders)
			{
				app::Object_1_Destroy_1((app::Object_1*)collider, NULL);
			}
			collision.AllColliders.clear();
			collision.Positions.clear();

			app::Object_1_Destroy_1((app::Object_1*)collision.Collider, NULL);
			collision.Collider = nullptr;
			app::Object_1_Destroy_1((app::Object_1*)collision.meshPreviewMat, NULL);
			collision.meshPreviewMat = nullptr;
			app::Object_1_Destroy_1((app::Object_1*)collision.meshFilterPreview, NULL);
			collision.meshFilterPreview = nullptr;
			app::Object_1_Destroy_1((app::Object_1*)collision.meshRenderer, NULL);
			collision.meshRenderer = nullptr;
			app::Object_1_Destroy_1((app::Object_1*)collision.mesh, NULL);
			collision.mesh = nullptr;
			app::Object_1_Destroy_1((app::Object_1*)collision.colliderPreview, NULL);
			collision.colliderPreview = nullptr;
		}
		AllCollisions.clear();

		app::Object_1_Destroy_1((app::Object_1*)MasterCollisionObject, NULL);
		SelectedObject = nullptr;
		MasterCollisionObject = nullptr;
	}

	void tem::CollisionCreator::AddCollisionToolbar()
	{
		MasterCollisionObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
		app::GameObject__ctor(MasterCollisionObject, string_new("CustomCollisionLayer"), NULL);

		tem::SceneList::SpecialSceneHierarchyMap["Collision"] = (std::uintptr_t)MasterCollisionObject;
		tem::SceneList::SpecialSceneHierarchyIndexMap[750] = (std::uintptr_t)MasterCollisionObject;
		tem::SceneList::ConstructSceneHierarchy({ 999, 750 }, 1);

		DropdownHorizontal = DrawUI::CreateDropdownHorizontal("HorizontalToolbar", ManagerPath + "Icons\\toolicons\\Tex_drawing_t.png");
		tem::UIEvents::Instance->OnClickEvents[DropdownHorizontal.FoldSelectableObject] = this;

		app::Type* typeSelectable = GetType("UnityEngine.UI", "Selectable");
		app::Type* typeImage = GetType("UnityEngine.UI", "Image");
		app::Type* typeLayoutElement = GetType("UnityEngine.UI", "LayoutElement");

		app::GameObject* selectableObject = DrawUI::Selectable("Selection");
		ToolbarSelectablesObjects.push_back(selectableObject);
		app::Texture2D* image0 = DrawUI::LoadImageFromPath(ManagerPath + "Icons\\toolicons\\Tex_select_t.png", 64, 64);
		ToolbarSelectables.push_back((app::Selectable*)app::GameObject_GetComponent(selectableObject, typeSelectable, NULL));
		DrawUI::SetImageInObject(selectableObject, image0);
		tem::UIEvents::Instance->OnClickEvents[selectableObject] = this;

		selectableObject = DrawUI::Selectable("MoveCollision");
		ToolbarSelectablesObjects.push_back(selectableObject);
		app::Texture2D* image1 = DrawUI::LoadImageFromPath(ManagerPath + "Icons\\toolicons\\Tex_move_t.png", 64, 64);
		ToolbarSelectables.push_back((app::Selectable*)app::GameObject_GetComponent(selectableObject, typeSelectable, NULL));
		DrawUI::SetImageInObject(selectableObject, image1);
		tem::UIEvents::Instance->OnClickEvents[selectableObject] = this;

		selectableObject = DrawUI::Selectable("EditCollision");
		ToolbarSelectablesObjects.push_back(selectableObject);
		app::Texture2D* image2 = DrawUI::LoadImageFromPath(ManagerPath + "Icons\\toolicons\\Tex_pencil_t.png", 64, 64);
		ToolbarSelectables.push_back((app::Selectable*)app::GameObject_GetComponent(selectableObject, typeSelectable, NULL));
		DrawUI::SetImageInObject(selectableObject, image2);
		tem::UIEvents::Instance->OnClickEvents[selectableObject] = this;

		selectableObject = DrawUI::Selectable("AddCollision");
		ToolbarSelectablesObjects.push_back(selectableObject);
		app::Texture2D* image3 = DrawUI::LoadImageFromPath(ManagerPath + "Icons\\toolicons\\Tex_hammer_t.png", 64, 64);
		ToolbarSelectables.push_back((app::Selectable*)app::GameObject_GetComponent(selectableObject, typeSelectable, NULL));
		DrawUI::SetImageInObject(selectableObject, image3);
		tem::UIEvents::Instance->OnClickEvents[selectableObject] = this;

		selectableObject = DrawUI::Selectable("SplitCollision");
		ToolbarSelectablesObjects.push_back(selectableObject);
		app::Texture2D* image4 = DrawUI::LoadImageFromPath(ManagerPath + "Icons\\toolicons\\Tex_split_t.png", 64, 64);
		ToolbarSelectables.push_back((app::Selectable*)app::GameObject_GetComponent(selectableObject, typeSelectable, NULL));
		DrawUI::SetImageInObject(selectableObject, image4);
		tem::UIEvents::Instance->OnClickEvents[selectableObject] = this;

		selectableObject = DrawUI::Selectable("FlipFaceDirectionUp");
		ToolbarSelectablesObjects.push_back(selectableObject);
		app::Texture2D* image5 = DrawUI::LoadImageFromPath(ManagerPath + "Icons\\toolicons\\Tex_flipup_t.png", 64, 64);
		ToolbarSelectables.push_back((app::Selectable*)app::GameObject_GetComponent(selectableObject, typeSelectable, NULL));
		DrawUI::SetImageInObject(selectableObject, image5);
		tem::UIEvents::Instance->OnClickEvents[selectableObject] = this;

		selectableObject = DrawUI::Selectable("FlipFaceDirectionDown");
		ToolbarSelectablesObjects.push_back(selectableObject);
		app::Texture2D* image6 = DrawUI::LoadImageFromPath(ManagerPath + "Icons\\toolicons\\Tex_flipdown_t.png", 64, 64);
		ToolbarSelectables.push_back((app::Selectable*)app::GameObject_GetComponent(selectableObject, typeSelectable, NULL));
		DrawUI::SetImageInObject(selectableObject, image6);
		tem::UIEvents::Instance->OnClickEvents[selectableObject] = this;

		selectableObject = DrawUI::Selectable("AddCollisionHandle");
		ToolbarSelectablesObjects.push_back(selectableObject);
		app::Texture2D* image7 = DrawUI::LoadImageFromPath(ManagerPath + "Icons\\toolicons\\Tex_add_handle_t.png", 64, 64);
		ToolbarSelectables.push_back((app::Selectable*)app::GameObject_GetComponent(selectableObject, typeSelectable, NULL));
		DrawUI::SetImageInObject(selectableObject, image7);
		tem::UIEvents::Instance->OnClickEvents[selectableObject] = this;

		for (app::Selectable* selectable : ToolbarSelectables)
		{
			TransformSetParent(app::Component_1_get_gameObject((app::Component_1*)selectable, NULL), DropdownHorizontal.DropdownChildren);
		}

		RectTransformSetPivot(DropdownHorizontal.DropdownObject, tem::Vector2(0.0f, 0.0f));
		TransformSetLocalPosition(DropdownHorizontal.DropdownObject, tem::Vector3(0.0f, 0.0f, 0.0f));// tem::Vector3(TransformGetPosition(newCanvas)));
		RectTransformSetSize(DropdownHorizontal.DropdownObject, tem::Vector2(100, 32));
		TransformSetLocalPosition(DropdownHorizontal.DropdownObject, tem::Vector3(0.0f, 0.0f, 0.0f));

		tem::UIEvents::Instance->AddObjectToCanvas(DropdownHorizontal.DropdownObject);

		app::GameObject_set_active(ToolbarSelectablesObjects[5], false, NULL);
		app::GameObject_set_active(ToolbarSelectablesObjects[6], true, NULL);
	}

	void tem::CollisionCreator::SetupRenderer(tem::Collision& collision)
	{
#ifdef _WOTW_PATCH_THREE
		collision.colliderPreview = app::GameObject_CreatePrimitive(app::PrimitiveType__Enum_Cube, NULL);
#endif
#ifdef _WOTW_PATCH_TWO
		collision.colliderPreview = app::GameObject_CreatePrimitive(app::PrimitiveType__Enum::Cube, NULL);
#endif
		app::Object_1_set_name((app::Object_1*)collision.colliderPreview, string_new("CollisionMesh"), NULL);

		app::BoxCollider* boxCollider = (app::BoxCollider*)GetComponentByType(collision.colliderPreview, "UnityEngine", "BoxCollider");
		app::Object_1_Destroy_1((app::Object_1*)boxCollider, NULL);

		auto Il2ClassMeshCollider = GetClass("UnityEngine", "MeshCollider");
		app::Type* MeshColliderType = GetTypeFromClass(Il2ClassMeshCollider);
		collision.Collider = (app::MeshCollider*)app::GameObject_AddComponent(collision.colliderPreview, MeshColliderType, NULL);
		app::Collider__ctor((app::Collider*)collision.Collider, NULL);
		app::Collider_set_enabled((app::Collider*)collision.Collider, true, NULL);

		app::Texture2D* collisionTexture = (app::Texture2D*)il2cpp_object_new((Il2CppClass*)(*app::Texture2D__TypeInfo));

#ifdef _WOTW_PATCH_THREE
		app::Texture2D__ctor_3(collisionTexture, 32, 32, app::TextureFormat__Enum::TextureFormat__Enum_RGBA32, false, false, NULL);
		app::Texture_set_wrapMode((app::Texture*)collisionTexture, app::TextureWrapMode__Enum::TextureWrapMode__Enum_Repeat, NULL);
		app::Texture_set_filterMode((app::Texture*)collisionTexture, app::FilterMode__Enum::FilterMode__Enum_Point, NULL);
#endif
#ifdef _WOTW_PATCH_TWO
		app::Texture2D__ctor_3(collisionTexture, 32, 32, app::TextureFormat__Enum::RGBA32, false, false, NULL);
		app::Texture_set_wrapMode((app::Texture*)collisionTexture, app::TextureWrapMode__Enum::Repeat, NULL);
		app::Texture_set_filterMode((app::Texture*)collisionTexture, app::FilterMode__Enum::Point, NULL);
#endif
		FillPixels(collisionTexture, 32, 32, tem::Vector4(1.0f, 0.0f, 0.0f, 1.0f).ToColor());

		app::Material* debugMaterial = CreateNewMaterial(); //calls app::Material__ctor() using the material found app::Shader_Find(standardMatS, NULL); // "Hidden/UberShader/4B897D76B847170D884884FBA5CEBC13");// CreateNewMaterial("Hidden/UberShader/4B897D76B847170D884884FBA5CEBC13");// "Hidden/UberShader/4B897D76B847170D884884FBA5CEBC13");// "Hidden/UberShader/E48C37CFA39B1500F0D8A6A5D0B46307");
		app::String* TextureName1 = string_new("_Color");
		app::String* wireColor = string_new("_WireColor");

		collision.meshRenderer = (app::MeshRenderer*)GetComponentByType(collision.colliderPreview, "UnityEngine", "MeshRenderer");
		app::Material_SetColor(debugMaterial, TextureName1, tem::Vector4(1.0f, 1.0f, 1.0f, 1.0f).ToColor(), NULL);
		app::Material_SetColor(debugMaterial, wireColor, tem::Vector4(0.0f, 1.0f, 0.0f, 1.0f).ToColor(), NULL);

		app::Renderer_SetMaterial((app::Renderer*)collision.meshRenderer, debugMaterial, NULL);
		app::Renderer_set_sortingOrder((app::Renderer*)collision.meshRenderer, 26810, NULL);
		app::Renderer_set_renderingLayerMask((app::Renderer*)collision.meshRenderer, 263200, NULL); //xxx0 nothing, xxx1 transparent, xxx2 full color, xxx3 full color shades everything inside
		app::Material_set_renderQueue(debugMaterial, 2000, NULL);

		collision.meshFilterPreview = (app::MeshFilter*)GetComponentByType(collision.colliderPreview, "UnityEngine", "MeshFilter");

		Gizmo::Instance.AllRegisteredObjects.push_back(static_cast<GizmoEvents*>(this));

		tem::Vector3 oriPos = TransformGetPosition(app::Component_1_get_gameObject((app::Component_1*)MDV::MoonSein, NULL));
		TransformSetPosition(collision.colliderPreview, oriPos);
		TransformSetLocalPosition(collision.colliderPreview, tem::Vector3(0.0f));
		TransformSetPosition(collision.colliderPreview, oriPos);
		TransformSetParent(collision.colliderPreview, MasterCollisionObject);
	}

	void tem::CollisionCreator::GizmoClicked()
	{
		this->IsUsingGizmo = true;
	}

	void tem::CollisionCreator::GizmoDone()
	{
		this->IsUsingGizmo = false;
	}

	void tem::CollisionCreator::GizmoMoved(tem::Vector3 position, tem::AxisType axis)
	{
		this->IsUsingGizmo = true;
		if (SelectedObject != nullptr && ActiveCollision != -1 && (ActiveTool == tem::CollisionToolType::Selection || ActiveTool == tem::CollisionToolType::Moving || ActiveTool == tem::CollisionToolType::Drawing))
		{
			app::GameObject* temp = app::Component_1_get_gameObject((app::Component_1*)SelectedObject, NULL);
			std::string name = il2cppi_to_string(app::Object_1_get_name((app::Object_1*)temp, NULL));
			sutil::ReplaceS(name, "HandleCollision", "");
			int index = std::stoi(name);

			switch (axis)
			{
				case tem::AxisType::X: AllCollisions[ActiveCollision].Positions[index].X = position.X; break;
				case tem::AxisType::Y: AllCollisions[ActiveCollision].Positions[index].Y = position.Y; break;
				case tem::AxisType::Z: AllCollisions[ActiveCollision].Positions[index].Z = position.Z; break;
				case tem::AxisType::XY: AllCollisions[ActiveCollision].Positions[index].X = position.X; AllCollisions[ActiveCollision].Positions[index].Y = position.Y; break;
			}
			tem::Vector3 handlePos = AllCollisions[ActiveCollision].Positions[index];
			handlePos.Z = -0.7f;
			app::SphereCollider_set_center(AllCollisions[ActiveCollision].AllColliders[index], handlePos.ToMoon(), NULL);

			AllCollisions[ActiveCollision].DrawCollision();
		}
	}

	void tem::CollisionCreator::LoadCollision(tem::CollisionCreator newCollision)
	{
		for (auto& collision : AllCollisions)
		{
			for (app::SphereCollider* collider : collision.AllColliders)
			{
				app::Object_1_Destroy_1((app::Object_1*)collider, NULL);
			}
			collision.AllColliders.clear();
			collision.Positions.clear();
		}

		if ((*app::DebugRenderer__TypeInfo)->static_fields->s_enabled == false)
			(*app::DebugRenderer__TypeInfo)->static_fields->s_enabled = true;

		AllCollisions = newCollision.AllCollisions;

		if (MasterCollisionObject == nullptr)
			AddCollisionToolbar();

		for (auto& collision : AllCollisions)
		{
			SetupRenderer(collision);
			for (int i = 0; i < collision.Positions.size(); i++)
			{
				collision.AddSphereHandle(collision.Positions[i], i);
			}
			collision.DrawCollision();
		}
	}

	void tem::CollisionCreator::OnEvent(tem::EventType type, void* ptr)
	{
		switch (type)
		{
			case tem::EventType::KeyPressedDelete:
			{
				if (SelectedObject != nullptr && ActiveCollision != -1)
				{
					std::size_t index = vector::find<app::SphereCollider*>(AllCollisions[ActiveCollision].AllColliders, SelectedObject);

					if (index != -1)
					{
						AllCollisions[ActiveCollision].Positions.erase(AllCollisions[ActiveCollision].Positions.begin() + index);
						app::Object_1_Destroy_1((app::Object_1*)AllCollisions[ActiveCollision].AllColliders[index], NULL);
						AllCollisions[ActiveCollision].AllColliders.erase(AllCollisions[ActiveCollision].AllColliders.begin() + index);

						int newIndex = 0;
						for (app::SphereCollider* collider : AllCollisions[ActiveCollision].AllColliders)
						{
							app::GameObject* gameObject = app::Component_1_get_gameObject((app::Component_1*)collider, NULL);
							app::Object_1_set_name((app::Object_1*)gameObject, string_new(("HandleCollision" + std::to_string(newIndex)).data()), NULL);
							newIndex++;
						}
					}
				}
			}
			break;

			case tem::EventType::MouseMove:
			{
				if (ActiveCollision != -1 && HitCollisionHandle == false && ActiveTool == tem::CollisionToolType::Drawing && tem::UIEvents::IsOverUIElement == false && ActiveActionType == tem::CollisionEditActionType::DrawingCollision && AllCollisions[ActiveCollision].ShouldDrawCollision() == true)
				{
					AllCollisions[ActiveCollision].AddPosition(app::MoonInput_get_mousePosition(NULL));
				}
			}
			break;

			case tem::EventType::MouseLeave:
			{
				if (DropdownHorizontal.FoldSelectableObject == ptr)
				{
					ActiveActionType = tem::CollisionEditActionType::None;
				}

				for (int i = 0; i < ToolbarSelectablesObjects.size(); i++)
				{
					if (ToolbarSelectablesObjects[i] == ptr)
					{
						ActiveActionType = tem::CollisionEditActionType::None;
					}
				}
			}
			break;

			case tem::EventType::MouseEnter:
			{
				if (DropdownHorizontal.FoldSelectableObject == ptr)
				{
					tem::UIEvents::IsOverUIElement = true;
					ActiveActionType = tem::CollisionEditActionType::UIHover;
				}

				for (int i = 0; i < ToolbarSelectablesObjects.size(); i++)
				{
					if (ToolbarSelectablesObjects[i] == ptr)
					{
						tem::UIEvents::IsOverUIElement = true;
						ActiveActionType = tem::CollisionEditActionType::UIHover;
					}
				}
			}
			break;

			case tem::EventType::RightMouseDown: SelectedObject = nullptr; ActiveTool = tem::CollisionToolType::Selection; if (ActiveActionType != tem::CollisionEditActionType::UIHover) ActiveActionType = tem::CollisionEditActionType::None; break;

			case tem::EventType::LeftMouseUp: if (ActiveActionType != tem::CollisionEditActionType::UIHover) ActiveActionType = tem::CollisionEditActionType::None;  break;
			case tem::EventType::LeftMouseDown:
			{
				if (ActiveActionType != tem::CollisionEditActionType::UIHover && tem::UIEvents::IsOverUIElement == false)
					ActiveActionType = tem::CollisionEditActionType::DrawingCollision;

				HitCollisionHandle = false;
				if (IsUsingGizmo == false && (ActiveTool == tem::CollisionToolType::Selection || ActiveTool == tem::CollisionToolType::Moving || ActiveTool == tem::CollisionToolType::Drawing))
				{
					tem::Vector3 position = app::MoonInput_get_mousePosition(NULL);

					if (MasterCollisionObject != nullptr)
					{
						tem::Vector3 cameraPosition = TransformGetPosition(app::Component_1_get_gameObject((app::Component_1*)MDV::MoonCamera, NULL));
						app::Ray ray = app::Camera_ScreenPointToRay_2(MDV::MoonCamera, tem::Vector3(position.X, position.Y, std::fabs(cameraPosition.Z)).ToMoon(), NULL); //29.0f
						app::RaycastHit hit = app::RaycastHit();
						bool hitSomething = app::Physics_Raycast_14(ray, &hit, 500, NULL);

						if (hitSomething == true)
							CheckIfHitHandle(hit.m_Collider);
						else
						{
							SelectedObject = nullptr;
							HitCollisionHandle = false;
						}
					}
					else
						AddCollisionToolbar();
				}
				else
				{
					SelectedObject = nullptr;
					HitCollisionHandle = false;
				}
			}
			break;
			case tem::EventType::PointerEvent:
			{

				if (DropdownHorizontal.FoldSelectableObject == ptr)
				{
					DropdownHorizontal.ExpandDropdown();
					if (DropdownHorizontal.IsFolded)
						ActiveTool = tem::CollisionToolType::None;
					else
						ActiveTool = tem::CollisionToolType::Selection;
				}

				for (int i = 0; i < ToolbarSelectablesObjects.size(); i++)
				{
					if (ToolbarSelectablesObjects[i] == ptr)
					{
						if ((*app::DebugRenderer__TypeInfo)->static_fields->s_enabled == false)
							(*app::DebugRenderer__TypeInfo)->static_fields->s_enabled = true;

						switch (i)
						{
							case 0: ActiveTool = tem::CollisionToolType::Selection; break;
							case 1: ActiveTool = tem::CollisionToolType::Moving; break;
							case 2: ActiveTool = tem::CollisionToolType::Drawing; break;
							case 3: ActiveTool = tem::CollisionToolType::NewCollision; AllCollisions.push_back(tem::Collision()); SetupRenderer(AllCollisions[AllCollisions.size() - 1]); ActiveCollision = AllCollisions.size() - 1; break;
							case 4:
							{
								if (ActiveCollision != -1 && SelectedObject != nullptr)
								{
									app::GameObject* temp = app::Component_1_get_gameObject((app::Component_1*)SelectedObject, NULL);
									std::string name = il2cppi_to_string(app::Object_1_get_name((app::Object_1*)temp, NULL));
									sutil::ReplaceS(name, "HandleCollision", "");
									int index = std::stoi(name);

									std::vector<tem::Vector3> splitPositions;
									std::vector<app::SphereCollider*> splitColliders;
									splitPositions.insert(splitPositions.begin(), (AllCollisions[ActiveCollision].Positions.begin()) + index, AllCollisions[ActiveCollision].Positions.end());
									splitColliders.insert(splitColliders.begin(), (AllCollisions[ActiveCollision].AllColliders.begin()) + index, AllCollisions[ActiveCollision].AllColliders.end());
									AllCollisions[ActiveCollision].Positions.erase((AllCollisions[ActiveCollision].Positions.begin()) + index, AllCollisions[ActiveCollision].Positions.end());
									AllCollisions[ActiveCollision].AllColliders.erase((AllCollisions[ActiveCollision].AllColliders.begin()) + index, AllCollisions[ActiveCollision].AllColliders.end());

									tem::Collision splitCollision = tem::Collision(splitColliders, splitPositions);
									AllCollisions.push_back(splitCollision);

									SetupRenderer(AllCollisions[AllCollisions.size() - 1]);
									AllCollisions[AllCollisions.size() - 1].UpdateSphereHandles();
									AllCollisions[AllCollisions.size() - 1].DrawCollision();
									AllCollisions[ActiveCollision].UpdateSphereHandles();
								}
							}
							break;

							case 5:
							case 6: ToggleFaceDirection(); break;
							case 7:
							{
								if (ActiveCollision != -1 && SelectedObject != nullptr)
								{
									app::GameObject* temp = app::Component_1_get_gameObject((app::Component_1*)SelectedObject, NULL);
									std::string name = il2cppi_to_string(app::Object_1_get_name((app::Object_1*)temp, NULL));
									sutil::ReplaceS(name, "HandleCollision", "");
									int index = std::stoi(name);

									if (index > 0)
										AllCollisions[ActiveCollision].ClonePositionIndex(index);
								}
							}
							break;
						}

						if (ActiveTool != tem::CollisionToolType::None && ActiveCollision != -1)
							AllCollisions[ActiveCollision].DrawCollision();
					}

				}

				if (ActiveActionType == tem::CollisionEditActionType::UIHover)
					return;

				HitCollisionHandle = false;
				if (IsUsingGizmo == false && (ActiveTool == tem::CollisionToolType::Selection || ActiveTool == tem::CollisionToolType::Moving || ActiveTool == tem::CollisionToolType::Drawing))
				{
					tem::Vector3 position = app::MoonInput_get_mousePosition(NULL);

					if (MasterCollisionObject != nullptr)
					{
						tem::Vector3 cameraPosition = TransformGetPosition(app::Component_1_get_gameObject((app::Component_1*)MDV::MoonCamera, NULL));
						app::Ray ray = app::Camera_ScreenPointToRay_2(MDV::MoonCamera, tem::Vector3(position.X, position.Y, std::fabs(cameraPosition.Z)).ToMoon(), NULL); //29.0f
						app::RaycastHit hit = app::RaycastHit();
						bool hitSomething = app::Physics_Raycast_14(ray, &hit, 500, NULL);

						if (hitSomething == true)
							CheckIfHitHandle(hit.m_Collider);
					}
					else
						AddCollisionToolbar();
				}
				else
				{
					SelectedObject = nullptr;
					HitCollisionHandle = false;
				}
			}
			break;
		}
	}

	void tem::CollisionCreator::ToggleFaceDirection()
	{
		if (ActiveCollision != -1)
		{
			if (AllCollisions[ActiveCollision].FaceDirection)
			{
				app::GameObject_set_active(ToolbarSelectablesObjects[5], false, NULL);
				app::GameObject_set_active(ToolbarSelectablesObjects[6], true, NULL);
			}
			else
			{
				app::GameObject_set_active(ToolbarSelectablesObjects[5], true, NULL);
				app::GameObject_set_active(ToolbarSelectablesObjects[6], false, NULL);
			}

			AllCollisions[ActiveCollision].FaceDirection = !AllCollisions[ActiveCollision].FaceDirection;
		}
	}

	void tem::CollisionCreator::SetFaceDirection(bool direction)
	{
		if (ActiveCollision != -1)
		{
			app::GameObject_set_active(ToolbarSelectablesObjects[5], !direction, NULL);
			app::GameObject_set_active(ToolbarSelectablesObjects[6], direction, NULL);
		}
	}

	void tem::CollisionCreator::CheckIfHitHandle(int hitInstanceID)
	{
		for (int i = 0; i < AllCollisions.size(); i++)
		{
			for (int i2 = 0; i2 < AllCollisions[i].AllColliders.size(); i2++)
			{
				if (tem::PtrInRange(AllCollisions[i].AllColliders[i2]) == true)
				{
					int instanceId = app::Object_1_GetInstanceID((app::Object_1*)AllCollisions[i].AllColliders[i2], NULL);

					if (instanceId == hitInstanceID)
					{
						SelectedObject = AllCollisions[i].AllColliders[i2];
						HitCollisionHandle = true;
						ActiveCollision = i;
						SetFaceDirection(AllCollisions[i].FaceDirection);

						app::GameObject* temp = app::Component_1_get_gameObject((app::Component_1*)SelectedObject, NULL);
						std::string name = il2cppi_to_string(app::Object_1_get_name((app::Object_1*)temp, NULL));
						sutil::ReplaceS(name, "HandleCollision", "");
						int index = std::stoi(name);

						Gizmo::Instance.SetGizmoPosition(AllCollisions[i].Positions[index]);

						AllCollisions[ActiveCollision].DrawCollision();
						AllCollisions[ActiveCollision].UpdateSphereHandles();

						MDV::SelectedObject = nullptr;
						if (MDV::PreviewObject != nullptr)
						{
							app::MeshRenderer* meshRenderer = (app::MeshRenderer*)GetComponentByType(MDV::PreviewObject, "UnityEngine", "MeshRenderer");
							app::Renderer_SetMaterial((app::Renderer*)meshRenderer, NULL, NULL);
							app::Object_1_Destroy_1((app::Object_1*)MDV::PreviewObject, NULL);
							MDV::PreviewObject = nullptr;
						}
					}
				}
			}
		}
	}

	void to_json(nlohmann::json& j, const tem::CollisionCreator& p)
	{
		j = nlohmann::json{ {"ActiveActionType", std::to_string(static_cast<int>(p.ActiveActionType)) }, {"AllCollisions", p.AllCollisions} };
	}

	void from_json(const nlohmann::json& j, tem::CollisionCreator& p)
	{
		if (j.find("AllCollisions") != j.end())
			j.at("AllCollisions").get_to(p.AllCollisions);
		else
			p.AllCollisions = std::vector<tem::Collision>();

		std::string actionType = j.at("ActiveActionType");
		p.ActiveActionType = static_cast<tem::CollisionEditActionType>(std::stoi(actionType));
	}
}