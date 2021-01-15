#pragma once

class MeshUtility
{
public:
	static void LoadMeshFromFile(std::string filepath, app::Mesh* mesh, app::Transform* transform);
	static app::GameObject* CreateMeshObjectFromFile(std::string filepath);
};
