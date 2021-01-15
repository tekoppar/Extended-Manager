#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <string>
#include <vector>
#include <filesystem>

#include "StringUtils.h"
#include "tem.h"
#include "ManagerDef.h"

#include "MeshUtility.h"

namespace tem {
	struct Vertex {
		float x;
		float y;
		float z;

		app::Vector3 ToMoon()
		{
			app::Vector3* moon = (app::Vector3*)il2cpp_object_new((Il2CppClass*)(*app::Vector3__TypeInfo));
			moon->x = x;
			moon->y = y;
			moon->z = z;

			return *moon;
		}
	};

	struct Normal {
		float x;
		float y;
		float z;

		app::Vector3 ToMoon()
		{
			app::Vector3* moon = (app::Vector3*)il2cpp_object_new((Il2CppClass*)(*app::Vector3__TypeInfo));
			moon->x = x;
			moon->y = y;
			moon->z = z;

			return *moon;
		}
	};

	struct UV {
		float x;
		float y;
		float z;

		app::Vector2 ToMoon()
		{
			app::Vector2* moon = (app::Vector2*)il2cpp_object_new((Il2CppClass*)(*app::Vector2__TypeInfo));
			moon->x = x;
			moon->y = y;

			return *moon;
		}
	};

	struct Face {
		int v1;
		int v2;
		int v3;
		int t1;
		int t2;
		int t3;
		int n1;
		int n2;
		int n3;
	};
}

enum class ObjectLineType {
	Vertices = 0,
	TextureCoordinates = 1,
	VertexNormal = 2,
	Segment = 3,
	Face = 4,
	Empty = 5
};

void MeshUtility::LoadMeshFromFile(std::string filepath, app::Mesh* mesh, app::Transform* transform)
{
	std::string textureTemp = "";
	if (std::filesystem::exists(filepath) == false && std::filesystem::is_regular_file(filepath) == false)
		return;

	std::vector<tem::Face> faceIndexes;
	std::vector<tem::Vertex> vertices;
	std::vector<tem::Normal> normals;
	std::vector<tem::UV> uvs;
	std::vector<std::string> fileLines = sutil::ReadFileByLine(filepath);

	ObjectLineType objType = ObjectLineType::Vertices;
	for (int i = 0; i < fileLines.size(); i++)
	{
		std::string stringContent = fileLines[i];
		int index = -1;

		if (sutil::StringStartsWith(stringContent, "v  ") == true)
			objType = ObjectLineType::Vertices;
		else if (sutil::StringStartsWith(stringContent, "vn ") == true)
			objType = ObjectLineType::VertexNormal;
		else if (sutil::StringStartsWith(stringContent, "vt ") == true)
			objType = ObjectLineType::TextureCoordinates;
		else if (sutil::StringStartsWith(stringContent, "s ") == true)
			objType = ObjectLineType::Segment;
		else if (sutil::StringStartsWith(stringContent, "f ") == true)
			objType = ObjectLineType::Face;
		else
			objType = ObjectLineType::Empty;

		switch (objType)
		{
			case ObjectLineType::Vertices:
			{
				std::vector<std::string> xyz;
				tem::Vertex vertex;

				stringContent.erase(0, 3);
				xyz = sutil::SplitTem(stringContent, " ");

				vertex.x = std::stof(xyz[0]);
				//invert the float Y for unreal
				vertex.y = -1 * std::stof(xyz[1]);
				vertex.z = std::stof(xyz[2]);
				vertices.push_back(vertex);
			}
			break;

			case ObjectLineType::Face:
			{
				std::vector<std::string> xyz;
				int loopIndex = -1;

				stringContent.erase(0, 2);
				xyz = sutil::SplitTem(stringContent, " ");
				auto indexes1 = sutil::SplitTem(xyz[0], "/");
				auto indexes2 = sutil::SplitTem(xyz[1], "/");
				auto indexes3 = sutil::SplitTem(xyz[2], "/");

				tem::Face face;
				face.v1 = std::stoi(indexes1[0]) - 1;
				face.v2 = std::stoi(indexes2[0]) - 1;
				face.v3 = std::stoi(indexes3[0]) - 1;

				face.t1 = std::stoi(indexes1[1]) - 1;
				face.t2 = std::stoi(indexes2[1]) - 1;
				face.t3 = std::stoi(indexes3[1]) - 1;

				face.n1 = std::stoi(indexes1[2]) - 1;
				face.n2 = std::stoi(indexes2[2]) - 1;
				face.n3 = std::stoi(indexes3[2]) - 1;

				faceIndexes.push_back(face);
			}
			break;

			case ObjectLineType::TextureCoordinates:
			{
				std::vector<std::string> xyz;
				tem::UV UV;

				stringContent.erase(0, 3);
				xyz = sutil::SplitTem(stringContent, " ");
				UV.x = std::stof(xyz[0]);
				UV.y = std::stof(xyz[1]);
				UV.z = std::stof(xyz[2]);
				//UV.Y = ((UV.Y - 0) * (0 - 1)) / (1 - 0) + 1;
				//UV.X = ((UV.X - 0) * (0 - 1)) / (1 - 0) + 1;
				uvs.push_back(UV);
			}
			break;

			case ObjectLineType::VertexNormal:
			{
				std::vector<std::string> xyz;
				tem::Normal normal;

				stringContent.erase(0, 3);
				xyz = sutil::SplitTem(stringContent, " ");
				normal.x = std::stof(xyz[0]);
				//normals.X = ((normals.X - -1) * (-1 - 1)) / (1 - -1) + 1;
				normal.y = -1 * std::stof(xyz[1]);
				//normals.Y = ((normals.Y - -1) * (-1 - 1)) / (1 - -1) + 1;
				normal.z = std::stof(xyz[2]);
				//we don't invert the Z value for unreal
				//normals.Z = ((normals.Z - -1) * (-1 - 1)) / (1 - -1) + 1;
				normals.push_back(normal);
			}
			break;
		}
	}

	app::Type* vec3ArrType = GetTypeFromClass((Il2CppClass*)(*app::Vector3__TypeInfo));
	app::Vector3__Array* verticesArr = (app::Vector3__Array*)app::Array_CreateInstance_1(vec3ArrType, static_cast<int>(vertices.size()), NULL);
	app::Type* normalsArrType = GetTypeFromClass((Il2CppClass*)(*app::Vector3__TypeInfo));
	app::Vector3__Array* normalsArr = (app::Vector3__Array*)app::Array_CreateInstance_1(normalsArrType, static_cast<int>(normals.size()), NULL);
	app::Type* int32Arr = GetTypeFromClass((Il2CppClass*)(*app::Int32__TypeInfo));
	app::Int32__Array* trianglesArr = (app::Int32__Array*)app::Array_CreateInstance_1(int32Arr, static_cast<int>(faceIndexes.size() * 3), NULL);
	app::Type* vector2ArrType = GetTypeFromClass((Il2CppClass*)(*app::Vector2__TypeInfo));
	app::Vector2__Array* uvArr = (app::Vector2__Array*)app::Array_CreateInstance_1(vector2ArrType, static_cast<int>(uvs.size()), NULL);

	for (int i = 0; i < vertices.size(); i++)
	{
		verticesArr->vector[i] = app::Transform_InverseTransformPoint(transform, vertices[i].ToMoon(), NULL);
	}
	int tri = 0;
	for (int i = 0; i < faceIndexes.size(); i++)
	{
		trianglesArr->vector[tri] = faceIndexes[i].v1;
		trianglesArr->vector[tri+1] = faceIndexes[i].v2;
		trianglesArr->vector[tri+2] = faceIndexes[i].v3;
		tri += 3;
	}
	for (int i = 0; i < uvs.size(); i++)
	{
		uvArr->vector[i] = uvs[i].ToMoon();
	}
	for (int i = 0; i < normals.size(); i++)
	{
		normalsArr->vector[i] = normals[i].ToMoon();
	}

	app::Mesh_Clear_1(mesh, NULL);
	app::Mesh_set_vertices(mesh, verticesArr, NULL);
	app::Mesh_set_uv(mesh, uvArr, NULL);
	app::Mesh_RecalculateNormals(mesh, NULL);
	app::Mesh_set_triangles(mesh, trianglesArr, NULL);
	app::Mesh_RecalculateBounds(mesh, NULL);
}

app::GameObject* MeshUtility::CreateMeshObjectFromFile(std::string filepath)
{
	app::GameObject* gameObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
	app::GameObject__ctor(gameObject, string_new("MeshObject"), NULL);

	app::Texture2D* collisionTexture = (app::Texture2D*)il2cpp_object_new((Il2CppClass*)(*app::Texture2D__TypeInfo));
	app::Texture2D__ctor_3(collisionTexture, 32, 32, app::TextureFormat__Enum::TextureFormat__Enum_RGBA32, false, false, NULL);
	app::Texture_set_wrapMode((app::Texture*)collisionTexture, app::TextureWrapMode__Enum::TextureWrapMode__Enum_Repeat, NULL);
	app::Texture_set_filterMode((app::Texture*)collisionTexture, app::FilterMode__Enum::FilterMode__Enum_Point, NULL);

	FillPixels(collisionTexture, 32, 32, tem::Vector4(1.0f, 1.0f, 1.0f, 1.0f).ToColor());
	app::Texture2D_Apply_1(collisionTexture, true, NULL);

	app::Material* material = CreateNewMaterial("Hidden/UberShader/DF362EF066C0701751D3088D28729049"); //calls app::Material__ctor() using the material found app::Shader_Find(standardMatS, NULL); // "Hidden/UberShader/4B897D76B847170D884884FBA5CEBC13");// CreateNewMaterial("Hidden/UberShader/4B897D76B847170D884884FBA5CEBC13");// "Hidden/UberShader/4B897D76B847170D884884FBA5CEBC13");// "Hidden/UberShader/E48C37CFA39B1500F0D8A6A5D0B46307");

	auto Il2ClassMeshFilter = GetClass("UnityEngine", "MeshFilter");
	app::Type* MeshFilterType = GetTypeFromClass(Il2ClassMeshFilter);
	app::MeshFilter* MeshFilter = (app::MeshFilter*)app::GameObject_AddComponent(gameObject, MeshFilterType, NULL);
	app::Mesh* mesh = app::MeshFilter_get_mesh(MeshFilter, NULL);

	app::Transform* transform = app::GameObject_get_transform(gameObject, NULL);
	LoadMeshFromFile(filepath, mesh, transform);
	//app::MeshFilter_set_sharedMesh(MeshFilter, mesh, NULL);
	//app::MeshFilter_set_mesh(MeshFilter, mesh, NULL);

	auto Il2ClassMeshRenderer = GetClass("UnityEngine", "MeshRenderer");
	app::Type* MeshRendererType = GetTypeFromClass(Il2ClassMeshRenderer);
	app::MeshRenderer* MeshRenderer = (app::MeshRenderer*)app::GameObject_AddComponent(gameObject, MeshRendererType, NULL);

	app::String* TextureName = string_new("_MainTex");
	app::String* TextureName1 = string_new("_Color");
	app::String* EmiColor = string_new("_EmissivityColor");
	app::String* TextureMultiplyColor = string_new("_MultiplyLayerColor");
	app::String* TextureMultiply = string_new("_MultiplyLayerTexture");
	int32_t reflectionInt = app::Shader_PropertyToID(string_new("_ReflectionAmount"), NULL);

	app::Material_SetTexture(material, TextureName, (app::Texture*)collisionTexture, NULL);
	app::Material_SetTexture(material, TextureMultiply, (app::Texture*)collisionTexture, NULL);
	app::Material_set_mainTexture(material, (app::Texture*)collisionTexture, NULL);
	app::Material_SetColor(material, TextureName1, tem::Vector4(1.0f, 1.0f, 1.0f, 1.0f).ToColor(), NULL);
	app::Material_SetColor(material, EmiColor, tem::Vector4(1.0f, 1.0f, 1.0f, 1.0f).ToColor(), NULL);
	app::Material_SetColor(material, TextureMultiplyColor, (tem::Vector4(1.0f, 1.0f, 1.0f, 1.0f) * tem::Vector4(0.009f, 0.009f, 0.009f, 1.0f)).ToColor(), NULL);
	app::Material_SetFloat(material, reflectionInt, 0.0f, NULL);

	app::Renderer_SetMaterial((app::Renderer*)MeshRenderer, material, NULL);
	app::Renderer_set_sortingOrder((app::Renderer*)MeshRenderer, 26810, NULL);
	app::Renderer_set_renderingLayerMask((app::Renderer*)MeshRenderer, 263200, NULL); //xxx0 nothing, xxx1 transparent, xxx2 full color, xxx3 full color shades everything inside
	app::Material_set_renderQueue(material, 2000, NULL);
	app::Renderer_set_moonOffsetZ((app::Renderer*)MeshRenderer, 0.0002f, NULL);

	return gameObject;
}