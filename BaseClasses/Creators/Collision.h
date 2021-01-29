#pragma once

#ifndef _COLLISION_H
#define _COLLISION_H

#include "Tem.h"
#include "json.hpp"

namespace tem {
	class Collision
	{
	public:
		std::vector<app::SphereCollider*> AllColliders = std::vector<app::SphereCollider*>();
		std::vector<tem::Vector3> Positions = std::vector<tem::Vector3>();
		bool FaceDirection = false;
		app::Mesh* mesh = nullptr;
		app::MeshCollider* Collider = nullptr;
		app::GameObject* colliderPreview = nullptr;
		app::MeshFilter* meshFilterPreview = nullptr;
		app::MeshRenderer* meshRenderer = nullptr;
		app::Material* meshPreviewMat = nullptr;

		Collision()
		{
			AllColliders = std::vector<app::SphereCollider*>();
			Positions = std::vector<tem::Vector3>();
			mesh = nullptr;
			Collider = nullptr;
			colliderPreview = nullptr;
			meshFilterPreview = nullptr;
			meshRenderer = nullptr;
			meshPreviewMat = nullptr;
			FaceDirection = false;
		}

		Collision(std::vector<app::SphereCollider*> collisions, std::vector<tem::Vector3> positions)
		{
			AllColliders = collisions;
			Positions = positions;
			mesh = nullptr;
			Collider = nullptr;
			colliderPreview = nullptr;
			meshFilterPreview = nullptr;
			meshRenderer = nullptr;
			meshPreviewMat = nullptr;
			FaceDirection = false;
		}

		bool ShouldDrawCollision();
		void AddPosition(tem::Vector3 position);
		void ClonePositionIndex(int index);
		void DrawCollision();
		void AddSphereHandle(tem::Vector3 position, int index);
		void UpdateSphereHandles();
	};

	void to_json(nlohmann::json& j, const tem::Collision& p);
	void from_json(const nlohmann::json& j, tem::Collision& p);
}

#endif