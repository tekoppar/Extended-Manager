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

#include "Collision.h"

namespace tem {

	void tem::Collision::DrawCollision()
	{
		if (Positions.size() < 2)
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

		tem::Vector3 pos1 = Positions[0];
		tem::Vector3 pos2 = Positions[0];
		pos2 += tem::Vector3(0.0f, 0.0f, 1.0f);
		tem::Vector3 pos3 = Positions[1];
		tem::Vector3 pos4 = Positions[1];
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

		if (FaceDirection == false)
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
		pos1 = pos3;
		pos2 = pos4;
		if (Positions.size() >= 3)
		{
			for (int i = 2; i < Positions.size(); i++)
			{
				pos3 = Positions[i];
				pos4 = Positions[i];
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

				if (FaceDirection == false)
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
			if (app::List_1_UnityEngine_Collider__Contains(debug->fields.m_cachedColliders, (app::Collider*)Collider, (*app::List_1_UnityEngine_Collider__Contains__MethodInfo)) == false)
				app::List_1_UnityEngine_Collider__Add(debug->fields.m_cachedColliders, (app::Collider*)Collider, (*app::List_1_UnityEngine_Collider__Add__MethodInfo));
			else
			{
				bool alreadyContains = true;
			}
		}
	}

	void tem::Collision::AddSphereHandle(tem::Vector3 position, int index)
	{
		auto Il2ClassSphereCollider = GetClass("UnityEngine", "SphereCollider");
		app::Type* SphereColliderType = GetTypeFromClass(Il2ClassSphereCollider);
		app::DebugRendererSettings* debug = (*app::DebugRendererSettings__TypeInfo)->static_fields->s_instance;

		app::GameObject* newHandle = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
		app::GameObject__ctor(newHandle, string_new(("HandleCollision" + std::to_string(index)).data()), NULL);

		app::SphereCollider* collider = (app::SphereCollider*)app::GameObject_AddComponent(newHandle, SphereColliderType, NULL);
		app::Collider__ctor((app::Collider*)collider, NULL);
		app::Collider_set_enabled((app::Collider*)collider, true, NULL);
		app::SphereCollider_set_radius(collider, 0.25f, NULL);
		position.Z = -0.7f;
		app::SphereCollider_set_center(collider, position.ToMoon(), NULL);
		AllColliders.insert(AllColliders.begin() + index, collider);
		TransformSetParent(newHandle, colliderPreview);

		app::List_1_UnityEngine_Collider__Add(debug->fields.m_cachedDamageColliders, (app::Collider*)collider, (*app::List_1_UnityEngine_Collider__Add__MethodInfo));
	}

	void tem::Collision::AddPosition(tem::Vector3 position)
	{
		if (tem::UIEvents::IsOverUIElement == false)
		{
			tem::Vector3 cameraPosition = TransformGetPosition(app::Component_1_get_gameObject((app::Component_1*)MDV::MoonCamera, NULL));
			app::Vector3 worldVec3 = app::Camera_ScreenToWorldPoint_1(MDV::MoonCamera, tem::Vector3(position.X, position.Y, std::fabs(cameraPosition.Z)).ToMoon(), NULL);
			tem::Vector3 worldTem = tem::Vector3(worldVec3);
			worldTem.Z = 0.0f;

			Positions.push_back(worldTem);
			AddSphereHandle(worldTem, Positions.size() - 1);
			DrawCollision();
		}
	}

	void tem::Collision::ClonePositionIndex(int index)
	{
		if (index < Positions.size())
		{
			Positions.insert(Positions.begin() + (index - 1), Positions[index]);
			AddSphereHandle(Positions[index], index - 1);
			DrawCollision();
			UpdateSphereHandles();
		}
	}

	bool tem::Collision::ShouldDrawCollision()
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

		tem::Vector3 cameraPosition = TransformGetPosition(app::Component_1_get_gameObject((app::Component_1*)MDV::MoonCamera, NULL));
		app::Vector3 worldVec3 = app::Camera_ScreenToWorldPoint_1(MDV::MoonCamera, tem::Vector3(position.X, position.Y, std::fabs(cameraPosition.Z)).ToMoon(), NULL);
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

	void tem::Collision::UpdateSphereHandles()
	{
		for (int i = 0; i < Positions.size(); i++)
		{
			app::GameObject* gameObject = app::Component_1_get_gameObject((app::Component_1*)AllColliders[i], NULL);
			TransformSetParent(gameObject, colliderPreview);
			app::Object_1_set_name((app::Object_1*)gameObject, string_new(("HandleCollision" + std::to_string(i)).data()), NULL);
			tem::Vector3 fixedPos = Positions[i];
			fixedPos.Z = -0.7f;
			app::SphereCollider_set_center(AllColliders[i], fixedPos.ToMoon(), NULL);

			app::DebugRendererSettings* debug = (*app::DebugRendererSettings__TypeInfo)->static_fields->s_instance;
			if (app::List_1_UnityEngine_Collider__Contains(debug->fields.m_cachedDamageColliders, (app::Collider*)AllColliders[i], (*app::List_1_UnityEngine_Collider__Contains__MethodInfo)) == false)
				app::List_1_UnityEngine_Collider__Add(debug->fields.m_cachedDamageColliders, (app::Collider*)AllColliders[i], (*app::List_1_UnityEngine_Collider__Add__MethodInfo));
		}
	}

	void to_json(nlohmann::json& j, const tem::Collision& p)
	{
		j = nlohmann::json{ {"FaceDirection", p.FaceDirection }, {"Positions", p.Positions } };
	}

	void from_json(const nlohmann::json& j, tem::Collision& p)
	{
		j.at("FaceDirection").get_to(p.FaceDirection);
		j.at("Positions").get_to(p.Positions);
	}
}