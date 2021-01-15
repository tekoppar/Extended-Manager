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
		for (app::SphereCollider* collider : AllColliders)
		{
			app::Object_1_Destroy_1((app::Object_1*)collider, NULL);
		}
		AllColliders.clear();
		Positions.clear();

		app::Object_1_Destroy_1((app::Object_1*)Collider, NULL);
		Collider = nullptr;
		app::Object_1_Destroy_1((app::Object_1*)meshPreviewMat, NULL);
		meshPreviewMat = nullptr;
		app::Object_1_Destroy_1((app::Object_1*)meshFilterPreview, NULL);
		meshFilterPreview = nullptr;
		app::Object_1_Destroy_1((app::Object_1*)meshRenderer, NULL);
		meshRenderer = nullptr;
		app::Object_1_Destroy_1((app::Object_1*)mesh, NULL);
		mesh = nullptr;
		app::Object_1_Destroy_1((app::Object_1*)SelectedObject, NULL);
		SelectedObject = nullptr;
		app::Object_1_Destroy_1((app::Object_1*)colliderPreview, NULL);
		colliderPreview = nullptr;
	}

	bool tem::CollisionCreator::ShouldDrawCollision()
	{
		tem::Vector3 position = app::MoonInput_get_mousePosition(NULL);

		if (Positions.size() == 0)
			return true;
		else if (Positions.size() < 3)
		{
			if (Positions.size() >= 1 && tem::Vector3::Distance(Positions[Positions.size() - 1], position) > 1.0f)
				return true;
			else
				return false;
		}

		app::Vector3 worldVec3 = app::Camera_ScreenToWorldPoint_1(MDV::MoonCamera, tem::Vector3(position.X, position.Y, 29.0f).ToMoon(), NULL);
		tem::Vector3 worldTem = tem::Vector3(worldVec3);

		float signedAngle = app::Vector3_SignedAngle(worldVec3, Positions[Positions.size() - 1].ToMoon(), tem::Vector3::Up.ToMoon(), NULL);
		float angleDiff = 0.0f;

		if (Positions.size() >= 3)
			angleDiff = tem::AngleDiff(Positions[Positions.size() - 2], Positions[Positions.size() - 1], worldTem);

		float distance = tem::Vector3::Distance(worldTem, Positions[Positions.size() - 1]);
		distance = tem::MapRange(distance, 0.0f, 3.0f, 0.0f, 1.0f);
		angleDiff = tem::MapRange(angleDiff, 0.0f, 90.0f, 0.0f, 1.0f);
		return distance > 0.25f && distance + angleDiff > 0.7f;
	}

	void tem::CollisionCreator::AddCollisionToolbar()
	{
		HorizontalToolbar = DrawUI::HorizontalLayoutGroup("HorizontalToolbar", app::TextAnchor__Enum::TextAnchor__Enum_UpperLeft);

		app::Type* typeButton = GetType("UnityEngine.UI", "Button");
		app::Type* typeImage = GetType("UnityEngine.UI", "Image");
		app::Type* typeLayoutElement = GetType("UnityEngine.UI", "LayoutElement");

		app::GameObject* buttonObject = DrawUI::Button("Selection");
		ToolbarButtonsObjects.push_back(buttonObject);
		app::Texture2D* image = DrawUI::LoadImageFromPath(ManagerPath + "Icons\\toolicons\\Tex_select_t.png", 64, 64);
		ToolbarButtons.push_back((app::Button*)app::GameObject_GetComponent(buttonObject, typeButton, NULL));
		DrawUI::SetImageInObject(buttonObject, image);
		app::Button_ButtonClickedEvent* clickEvent = app::Button_get_onClick((app::Button*)&ToolbarButtons[ToolbarButtons.size() - 1], NULL);
		tem::UIEvents::Instance->OnClickEvents[buttonObject] = this;

		buttonObject = DrawUI::Button("MoveCollision");
		ToolbarButtonsObjects.push_back(buttonObject);
		app::Texture2D* image2 = DrawUI::LoadImageFromPath(ManagerPath + "Icons\\toolicons\\Tex_move_t.png", 64, 64);
		ToolbarButtons.push_back((app::Button*)app::GameObject_GetComponent(buttonObject, typeButton, NULL));
		DrawUI::SetImageInObject(buttonObject, image2);
		app::Button_ButtonClickedEvent* clickEvent2 = app::Button_get_onClick((app::Button*)&ToolbarButtons[ToolbarButtons.size() - 1], NULL);
		tem::UIEvents::Instance->OnClickEvents[buttonObject] = this;

		buttonObject = DrawUI::Button("EditCollision");
		ToolbarButtonsObjects.push_back(buttonObject);
		app::Texture2D* image3 = DrawUI::LoadImageFromPath(ManagerPath + "Icons\\toolicons\\Tex_pencil_t.png", 64, 64);
		ToolbarButtons.push_back((app::Button*)app::GameObject_GetComponent(buttonObject, typeButton, NULL));
		DrawUI::SetImageInObject(buttonObject, image3);
		app::Button_ButtonClickedEvent* clickEvent3 = app::Button_get_onClick((app::Button*)&ToolbarButtons[ToolbarButtons.size() - 1], NULL);
		tem::UIEvents::Instance->OnClickEvents[buttonObject] = this;

		buttonObject = DrawUI::Button("AddCollision");
		ToolbarButtonsObjects.push_back(buttonObject);
		app::Texture2D* image4 = DrawUI::LoadImageFromPath(ManagerPath + "Icons\\toolicons\\Tex_hammer_t.png", 64, 64);
		ToolbarButtons.push_back((app::Button*)app::GameObject_GetComponent(buttonObject, typeButton, NULL));
		DrawUI::SetImageInObject(buttonObject, image4);
		app::Button_ButtonClickedEvent* clickEvent4 = app::Button_get_onClick((app::Button*)&ToolbarButtons[ToolbarButtons.size() - 1], NULL);
		tem::UIEvents::Instance->OnClickEvents[buttonObject] = this;

		for (app::Button* button : ToolbarButtons)
		{
			TransformSetParent(app::Component_1_get_gameObject((app::Component_1*)button, NULL), HorizontalToolbar);
		}

		RectTransformSetPivot(HorizontalToolbar, tem::Vector2(0.0f, 0.0f));
		TransformSetLocalPosition(HorizontalToolbar, tem::Vector3(0.0f, 0.0f, 0.0f));// tem::Vector3(TransformGetPosition(newCanvas)));
		RectTransformSetSize(HorizontalToolbar, tem::Vector2(100, 32));
		TransformSetLocalPosition(HorizontalToolbar, tem::Vector3(0.0f, 0.0f, 0.0f));

		tem::UIEvents::Instance->AddObjectToCanvas(HorizontalToolbar);
	}

	void tem::CollisionCreator::SetupRenderer()
	{
		colliderPreview = app::GameObject_CreatePrimitive(app::PrimitiveType__Enum_Cube, NULL);
		app::Object_1_set_name((app::Object_1*)colliderPreview, string_new("CollisionMesh"), NULL);

		app::BoxCollider* boxCollider = (app::BoxCollider*)GetComponentByType(colliderPreview, "UnityEngine", "BoxCollider");
		app::Object_1_Destroy_1((app::Object_1*)boxCollider, NULL);

		auto Il2ClassMeshCollider = GetClass("UnityEngine", "MeshCollider");
		app::Type* MeshColliderType = GetTypeFromClass(Il2ClassMeshCollider);
		Collider = (app::MeshCollider*)app::GameObject_AddComponent(colliderPreview, MeshColliderType, NULL);
		app::Collider__ctor((app::Collider*)Collider, NULL);
		app::Collider_set_enabled((app::Collider*)Collider, true, NULL);

		app::Texture2D* collisionTexture = (app::Texture2D*)il2cpp_object_new((Il2CppClass*)(*app::Texture2D__TypeInfo));
		app::Texture2D__ctor_3(collisionTexture, 32, 32, app::TextureFormat__Enum::TextureFormat__Enum_RGBA32, false, false, NULL);
		app::Texture_set_wrapMode((app::Texture*)collisionTexture, app::TextureWrapMode__Enum::TextureWrapMode__Enum_Repeat, NULL);
		app::Texture_set_filterMode((app::Texture*)collisionTexture, app::FilterMode__Enum::FilterMode__Enum_Point, NULL);
		FillPixels(collisionTexture, 32, 32, tem::Vector4(1.0f, 0.0f, 0.0f, 1.0f).ToColor());

		app::Material* debugMaterial = CreateNewMaterial(); //calls app::Material__ctor() using the material found app::Shader_Find(standardMatS, NULL); // "Hidden/UberShader/4B897D76B847170D884884FBA5CEBC13");// CreateNewMaterial("Hidden/UberShader/4B897D76B847170D884884FBA5CEBC13");// "Hidden/UberShader/4B897D76B847170D884884FBA5CEBC13");// "Hidden/UberShader/E48C37CFA39B1500F0D8A6A5D0B46307");
		app::String* TextureName1 = string_new("_Color");
		app::String* wireColor = string_new("_WireColor");

		meshRenderer = (app::MeshRenderer*)GetComponentByType(colliderPreview, "UnityEngine", "MeshRenderer");
		app::Material_SetColor(debugMaterial, TextureName1, tem::Vector4(1.0f, 1.0f, 1.0f, 1.0f).ToColor(), NULL);
		app::Material_SetColor(debugMaterial, wireColor, tem::Vector4(0.0f, 1.0f, 0.0f, 1.0f).ToColor(), NULL);

		app::Renderer_SetMaterial((app::Renderer*)meshRenderer, debugMaterial, NULL);
		app::Renderer_set_sortingOrder((app::Renderer*)meshRenderer, 26810, NULL);
		app::Renderer_set_renderingLayerMask((app::Renderer*)meshRenderer, 263200, NULL); //xxx0 nothing, xxx1 transparent, xxx2 full color, xxx3 full color shades everything inside
		app::Material_set_renderQueue(debugMaterial, 2000, NULL);

		meshFilterPreview = (app::MeshFilter*)GetComponentByType(colliderPreview, "UnityEngine", "MeshFilter");

		Gizmo::Instance.AllRegisteredObjects.push_back(static_cast<GizmoEvents*>(this));

		tem::Vector3 oirPos = TransformGetPosition(app::Component_1_get_gameObject((app::Component_1*)MDV::MoonSein, NULL));
		TransformSetPosition(colliderPreview, oirPos);
		TransformSetLocalPosition(colliderPreview, tem::Vector3(0.0f));
		TransformSetPosition(colliderPreview, oirPos);

		tem::SceneList::SpecialSceneHierarchyMap["Collision"] = (std::uintptr_t)colliderPreview;
		tem::SceneList::SpecialSceneHierarchyIndexMap[750] = (std::uintptr_t)colliderPreview;
		tem::SceneList::ConstructSceneHierarchy({ 999, 750 }, 1);
	}

	void tem::CollisionCreator::AddPosition(tem::Vector3 position)
	{
		if (this->colliderPreview == nullptr)
			this->SetupRenderer();

		if (tem::UIEvents::IsOverUIElement == false)
		{
			app::Vector3 worldVec3 = app::Camera_ScreenToWorldPoint_1(MDV::MoonCamera, tem::Vector3(position.X, position.Y, 29.0f).ToMoon(), NULL);
			tem::Vector3 worldTem = tem::Vector3(worldVec3);
			worldTem.Z = 0.0f;

			this->Positions.push_back(worldTem);
			AddSphereHandle(worldTem);
			DrawCollision();
		}
	}

	void tem::CollisionCreator::DrawCollision()
	{
		if (this->Positions.size() < 2)
			return;

		app::List_1_UnityEngine_Vector3_* listVec3 = (app::List_1_UnityEngine_Vector3_*)il2cpp_object_new((Il2CppClass*)(*app::List_1_UnityEngine_Vector3___TypeInfo));
		app::Type* vec3ArrType = GetTypeFromClass((Il2CppClass*)(*app::Vector3__TypeInfo));
		app::Vector3__Array* vec3 = (app::Vector3__Array*)app::Array_CreateInstance_1(vec3ArrType, static_cast<int>(Positions.size()), NULL);
		listVec3->fields._items = vec3;
		app::List_1_UnityEngine_Vector3___ctor_2(listVec3, static_cast<int>(Positions.size()), (*app::List_1_UnityEngine_Vector3___ctor_1__MethodInfo));

		app::List_1_System_Int32_* faces = (app::List_1_System_Int32_*)il2cpp_object_new((Il2CppClass*)(*app::List_1_System_Int32___TypeInfo));
		app::List_1_System_Int32___ctor(faces, static_cast<int>(Positions.size() * 2), (*app::List_1_System_Int32___ctor__MethodInfo));

		app::Transform* transform = app::GameObject_get_transform(colliderPreview, NULL);
		Collider->fields._._.m_cachedGameObject = colliderPreview;
		Collider->fields._._.m_cachedTransform = transform;
		Collider->fields._._.m_gameObjectCached = true;
		Collider->fields._._.m_transformCached = true;
		std::vector<tem::Vector3> uvVertexs;


		tem::Vector3 pos1 = this->Positions[0];
		tem::Vector3 pos2 = this->Positions[0];
		pos2 += tem::Vector3(0.0f, 0.0f, 1.0f);
		tem::Vector3 pos3 = this->Positions[1];
		tem::Vector3 pos4 = this->Positions[1];
		pos4 += tem::Vector3(0.0f, 0.0f, 1.0f);

		app::Vector3__Array* verticesArr = (app::Vector3__Array*)app::Array_CreateInstance_1(vec3ArrType, static_cast<int>(Positions.size() * 2), NULL);
		app::Type* int32Arr = GetTypeFromClass((Il2CppClass*)(*app::Int32__TypeInfo));
		app::Int32__Array* trianglesArr = (app::Int32__Array*)app::Array_CreateInstance_1(int32Arr, static_cast<int>(Positions.size() * 6), NULL);

		tem::Vector3 localPos = tem::Vector3(app::Transform_InverseTransformPoint(transform, pos1.ToMoon(), NULL));
		tem::Vector3 localPos2 = tem::Vector3(app::Transform_InverseTransformPoint(transform, pos2.ToMoon(), NULL));
		tem::Vector3 localPos3 = tem::Vector3(app::Transform_InverseTransformPoint(transform, pos3.ToMoon(), NULL));
		tem::Vector3 localPos4 = tem::Vector3(app::Transform_InverseTransformPoint(transform, pos4.ToMoon(), NULL));

		verticesArr->vector[0] = localPos.ToMoon();
		verticesArr->vector[1] = localPos2.ToMoon();
		verticesArr->vector[2] = localPos3.ToMoon();
		verticesArr->vector[3] = localPos4.ToMoon();

		int leftTop = 0, leftBot = 1, rightTop = 2, rightBot = 3;

		if (this->Positions[0].X < this->Positions[1].X)
		{
			trianglesArr->vector[0] = leftTop;
			trianglesArr->vector[1] = leftBot;
			trianglesArr->vector[2] = rightTop;

			trianglesArr->vector[3] = rightBot;
			trianglesArr->vector[4] = leftBot;
			trianglesArr->vector[5] = rightTop;
		}
		else
		{
			trianglesArr->vector[2] = leftTop;
			trianglesArr->vector[1] = leftBot;
			trianglesArr->vector[0] = rightTop;

			trianglesArr->vector[5] = rightBot;
			trianglesArr->vector[4] = leftBot;
			trianglesArr->vector[3] = rightTop;
		}

		leftTop += 2;
		leftBot += 2;
		rightTop += 2;
		rightBot += 2;

		int triangleArrIndex = 5;
		int verticesArrIndex = 3;
		if (Positions.size() >= 3)
		{
			for (int i = 2; i < this->Positions.size(); i++)
			{
				pos3 = this->Positions[i];
				pos4 = this->Positions[i];
				pos4 += tem::Vector3(0.0f, 0.0f, 1.0f);

				localPos3 = tem::Vector3(app::Transform_InverseTransformPoint(transform, pos3.ToMoon(), NULL));
				localPos4 = tem::Vector3(app::Transform_InverseTransformPoint(transform, pos4.ToMoon(), NULL));

				/*uvVertexs.push_back(localPos);
				uvVertexs.push_back(localPos2);
				uvVertexs.push_back(localPos3);
				uvVertexs.push_back(localPos2);
				uvVertexs.push_back(localPos3);
				uvVertexs.push_back(localPos4);*/

				verticesArrIndex++;
				verticesArr->vector[verticesArrIndex] = localPos3.ToMoon();
				verticesArrIndex++;
				verticesArr->vector[verticesArrIndex] = localPos4.ToMoon();

				if (pos1.X < pos3.X)
				{
					triangleArrIndex++;
					trianglesArr->vector[triangleArrIndex] = leftTop;
					triangleArrIndex++;
					trianglesArr->vector[triangleArrIndex] = leftBot;
					triangleArrIndex++;
					trianglesArr->vector[triangleArrIndex] = rightTop;

					triangleArrIndex++;
					trianglesArr->vector[triangleArrIndex] = rightBot;
					triangleArrIndex++;
					trianglesArr->vector[triangleArrIndex] = leftBot;
					triangleArrIndex++;
					trianglesArr->vector[triangleArrIndex] = rightTop;
				}
				else
				{
					triangleArrIndex++;
					trianglesArr->vector[triangleArrIndex] = rightTop;
					triangleArrIndex++;
					trianglesArr->vector[triangleArrIndex] = leftBot;
					triangleArrIndex++;
					trianglesArr->vector[triangleArrIndex] = leftTop;

					triangleArrIndex++;
					trianglesArr->vector[triangleArrIndex] = rightTop;
					triangleArrIndex++;
					trianglesArr->vector[triangleArrIndex] = leftBot;
					triangleArrIndex++;
					trianglesArr->vector[triangleArrIndex] = rightBot;
				}

				pos1 = pos3;
				pos2 = pos4;
				leftTop += 2;
				leftBot += 2;
				rightTop += 2;
				rightBot += 2;
			}
		}

		app::Mesh* tempMesh = app::MeshFilter_get_mesh(meshFilterPreview, NULL);
		if (Positions.size() == 2)
		{
			app::Mesh_MarkDynamicImpl(tempMesh, NULL);
		}

		std::vector<tem::Vector2> uvVectors = UvCalculator::CalculateUVs(uvVertexs, 1.0f);
		app::Type* vector2ArrType = GetTypeFromClass((Il2CppClass*)(*app::Vector2__TypeInfo));
		app::Vector2__Array* uvArr = (app::Vector2__Array*)app::Array_CreateInstance_1(vector2ArrType, static_cast<int>(uvVectors.size()), NULL);

		for (int i = 0; i < uvVectors.size(); i++)
		{
			uvArr->vector[i] = uvVectors[i].ToMoon();
		}

		app::Mesh_Clear_1(tempMesh, NULL);
		app::Mesh_set_vertices(tempMesh, verticesArr, NULL);
		app::Mesh_set_uv(tempMesh, uvArr, NULL);
		app::Mesh_RecalculateNormals(tempMesh, NULL);
		app::Mesh_set_triangles(tempMesh, trianglesArr, NULL);

		app::MeshCollider_set_sharedMesh(Collider, tempMesh, NULL);
		app::DebugRendererSettings* debug = (*app::DebugRendererSettings__TypeInfo)->static_fields->s_instance;

		if (debug != nullptr)
		{
			app::List_1_UnityEngine_Collider__Add(debug->fields.m_cachedColliders, (app::Collider*)Collider, (*app::List_1_UnityEngine_Collider__Add__MethodInfo));
		}
	}

	void tem::CollisionCreator::AddSphereHandle(tem::Vector3 position)
	{
		auto Il2ClassSphereCollider = GetClass("UnityEngine", "SphereCollider");
		app::Type* SphereColliderType = GetTypeFromClass(Il2ClassSphereCollider);
		app::DebugRendererSettings* debug = (*app::DebugRendererSettings__TypeInfo)->static_fields->s_instance;

		app::GameObject* newHandle = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
		app::GameObject__ctor(newHandle, string_new(("HandleCollision" + std::to_string((Positions.size() - 1))).data()), NULL);

		app::SphereCollider* collider = (app::SphereCollider*)app::GameObject_AddComponent(newHandle, SphereColliderType, NULL);
		app::Collider__ctor((app::Collider*)collider, NULL);
		app::Collider_set_enabled((app::Collider*)collider, true, NULL);
		app::SphereCollider_set_radius(collider, 0.25f, NULL);
		position.Z = -0.7f;
		app::SphereCollider_set_center(collider, position.ToMoon(), NULL);
		AllColliders.push_back(collider);

		app::List_1_UnityEngine_Collider__Add(debug->fields.m_cachedDamageColliders, (app::Collider*)collider, (*app::List_1_UnityEngine_Collider__Add__MethodInfo));

		TransformSetParent(newHandle, colliderPreview);
	}

	void tem::CollisionCreator::GizmoClicked()
	{
		this->IsUsingGizmo = true;
		this->ActiveActionType = tem::CollisionEditActionType::None;
		this->ActiveTool = tem::CollisionToolType::Selection;
	}

	void tem::CollisionCreator::GizmoDone()
	{
		this->IsUsingGizmo = false;
	}

	void tem::CollisionCreator::GizmoMoved(tem::Vector3 position, tem::AxisType axis)
	{
		this->IsUsingGizmo = true;
		this->ActiveTool = tem::CollisionToolType::Selection;
		this->ActiveActionType = tem::CollisionEditActionType::None;

		if (SelectedObject != nullptr)
		{
			app::GameObject* temp = app::Component_1_get_gameObject((app::Component_1*)SelectedObject, NULL);
			std::string name = il2cppi_to_string(app::Object_1_get_name((app::Object_1*)temp, NULL));
			sutil::ReplaceS(name, "HandleCollision", "");
			int index = std::stoi(name);

			switch (axis)
			{
				case tem::AxisType::X: Positions[index].X = position.X; break;
				case tem::AxisType::Y: Positions[index].Y = position.Y; break;
				case tem::AxisType::Z: Positions[index].Z = position.Z; break;
				case tem::AxisType::XY: Positions[index].X = position.X; Positions[index].Y = position.Y; break;
			}
			tem::Vector3 handlePos = Positions[index];
			handlePos.Z = -0.7f;
			app::SphereCollider_set_center(AllColliders[index], handlePos.ToMoon(), NULL);

			DrawCollision();
		}
	}

	void tem::CollisionCreator::LoadCollision(tem::CollisionCreator newCollision)
	{
		for (app::SphereCollider* collider : AllColliders)
		{
			app::Object_1_Destroy_1((app::Object_1*)collider, NULL);
		}

		AllColliders.clear();
		Positions.clear();
		Positions = newCollision.Positions;

		if (colliderPreview == nullptr)
			SetupRenderer();

		for (tem::Vector3& pos : Positions)
		{
			AddSphereHandle(pos);
		}

		DrawCollision();
	}

	void tem::CollisionCreator::OnEvent(tem::EventType type, void* ptr)
	{
		switch (type)
		{
			case tem::EventType::KeyPressedDelete:
			{
				if (SelectedObject != nullptr)
				{
					std::size_t index = vector::find<app::SphereCollider*>(AllColliders, SelectedObject);

					if (index != -1)
					{
						Positions.erase(Positions.begin() + index);
						app::Object_1_Destroy_1((app::Object_1*)AllColliders[index], NULL);
						AllColliders.erase(AllColliders.begin() + index);

						int newIndex = 0;
						for (app::SphereCollider* collider : AllColliders)
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
				if (HitCollisionHandle == false && ActiveTool == tem::CollisionToolType::Drawing && tem::UIEvents::IsOverUIElement == false && ActiveActionType == tem::CollisionEditActionType::DrawingCollision && ShouldDrawCollision() == true)
				{
					AddPosition(app::MoonInput_get_mousePosition(NULL));
				}
				/*else if (SelectedObject != nullptr && ActiveTool == tem::CollisionToolType::Moving)
				{
					tem::Vector3 mousePos = app::MoonInput_get_mousePosition(NULL);
					app::Vector3 worldVec3 = app::Camera_ScreenToWorldPoint_1(MDV::MoonCamera, tem::Vector3(mousePos.X, mousePos.Y, 29.0f).ToMoon(), NULL);
					tem::Vector3 worldTem = tem::Vector3(worldVec3);
					worldTem.Z = 0.0f;
					app::GameObject* temp = app::Component_1_get_gameObject((app::Component_1*)SelectedObject, NULL);
					TransformSetPosition(temp, worldTem);
					std::string name = il2cppi_to_string(app::Object_1_get_name((app::Object_1*)temp, NULL));
					sutil::ReplaceS(name, "HandleCollision", "");
					int index = std::stoi(name);
					this->Positions[index] = worldTem;
					DrawCollision();
				}*/
			}
			break;

			case tem::EventType::MouseLeave: 
			{
				for (int i = 0; i < ToolbarButtonsObjects.size(); i++)
				{
					if (ToolbarButtonsObjects[i] == ptr)
					{
						ActiveActionType = tem::CollisionEditActionType::None;
					}
				}
			}
			break;

			case tem::EventType::MouseEnter:
			{
				for (int i = 0; i < ToolbarButtonsObjects.size(); i++)
				{
					if (ToolbarButtonsObjects[i] == ptr)
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
				if (IsUsingGizmo == false)
				{
					tem::Vector3 position = app::MoonInput_get_mousePosition(NULL);

					if (colliderPreview != nullptr && Collider != nullptr)
					{
						app::Ray ray = app::Camera_ScreenPointToRay_2(MDV::MoonCamera, tem::Vector3(position.X, position.Y, tem::Vector3(TransformGetPosition(app::Component_1_get_gameObject((app::Component_1*)MDV::MoonCamera, NULL))).Z).ToMoon(), NULL); //29.0f
						app::RaycastHit hit = app::RaycastHit();
						bool hitSomething = app::Physics_Raycast_14(ray, &hit, 500, NULL);

						if (hitSomething == true)
						{
							for (app::SphereCollider* collider : AllColliders)
							{
								int instanceId = app::Object_1_GetInstanceID((app::Object_1*)collider, NULL);

								if (instanceId == hit.m_Collider)
								{
									SelectedObject = collider;
									HitCollisionHandle = true;

									app::GameObject* temp = app::Component_1_get_gameObject((app::Component_1*)SelectedObject, NULL);
									std::string name = il2cppi_to_string(app::Object_1_get_name((app::Object_1*)temp, NULL));
									sutil::ReplaceS(name, "HandleCollision", "");
									int index = std::stoi(name);

									Gizmo::Instance.SetGizmoPosition(this->Positions[index]);

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
						else
						{
							SelectedObject = nullptr;
							HitCollisionHandle = false;
						}
					}
					else
						SetupRenderer();
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
				for (int i = 0; i < ToolbarButtonsObjects.size(); i++)
				{
					if (ToolbarButtonsObjects[i] == ptr)
					{
						(*app::DebugRenderer__TypeInfo)->static_fields->s_enabled = true;

						switch (i)
						{
							case 0: ActiveTool = tem::CollisionToolType::Selection; break;
							case 1: ActiveTool = tem::CollisionToolType::Moving; break;
							case 2: ActiveTool = tem::CollisionToolType::Drawing; break;
							case 3: ActiveTool = tem::CollisionToolType::NewCollision; break;
						}

						if (ActiveTool != tem::CollisionToolType::None)
							DrawCollision();
					}

				}

				if (ActiveActionType == tem::CollisionEditActionType::UIHover)
					return;

				HitCollisionHandle = false;
				if (IsUsingGizmo == false)
				{
					tem::Vector3 position = app::MoonInput_get_mousePosition(NULL);

					if (colliderPreview != nullptr && Collider != nullptr)
					{
						app::Ray ray = app::Camera_ScreenPointToRay_2(MDV::MoonCamera, tem::Vector3(position.X, position.Y, 29.0f).ToMoon(), NULL);
						app::RaycastHit hit = app::RaycastHit();
						bool hitSomething = app::Physics_Raycast_14(ray, &hit, 500, NULL);

						if (hitSomething == true)
						{
							for (app::SphereCollider* collider : AllColliders)
							{
								int instanceId = app::Object_1_GetInstanceID((app::Object_1*)collider, NULL);

								if (instanceId == hit.m_Collider)
								{
									SelectedObject = collider;
									HitCollisionHandle = true;

									app::GameObject* temp = app::Component_1_get_gameObject((app::Component_1*)SelectedObject, NULL);
									std::string name = il2cppi_to_string(app::Object_1_get_name((app::Object_1*)temp, NULL));
									sutil::ReplaceS(name, "HandleCollision", "");
									int index = std::stoi(name);

									Gizmo::Instance.SetGizmoPosition(this->Positions[index]);

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
					else
						SetupRenderer();
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

	void to_json(nlohmann::json& j, const tem::CollisionCreator& p)
	{
		j = nlohmann::json{ {"ActiveActionType", std::to_string(static_cast<int>(p.ActiveActionType)) }, {"Positions", p.Positions} };
	}

	void from_json(const nlohmann::json& j, tem::CollisionCreator& p)
	{
		j.at("Positions").get_to(p.Positions);
		std::string actionType = j.at("ActiveActionType");
		p.ActiveActionType = static_cast<tem::CollisionEditActionType>(std::stoi(actionType));
	}
}