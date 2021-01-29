#pragma once

#include "GraphDrawer.h"
#include "TemSceneHelper.h"
#include "Tem.h"

namespace tem {
	class ObjectCreator
	{
	public:
		static app::Scene temUnityScene1;
		static app::GameObject* temScene1;
		static app::SceneMetaData* temScene1MetaData;
		static app::RuntimeSceneMetaData* temScene1RuntimeMetaData;
		static app::SceneRoot* temScene1Root;
		static app::SceneManagerScene* temScene1ManagerScene;
		static app::SceneSettingsComponent* SceneCopySettings;

		static app::GameObject* CreateClone(app::GameObject* object);

		void CreateScene(std::string name, tem::Vector3 position, tem::Vector2 size, tem::Rect loadingRect);
		void CreateObject(std::string Namespace, std::string Class)
		{
			auto Il2Class = GetClass(Namespace, Class);
			app::Type* type = GetTypeFromClass((Il2CppClass*)Il2Class);

			app::GameObject* gameObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
			app::GameObject__ctor(gameObject, string_new("NewGameObject3"), NULL);
			MDV::GCHandles.push_back(il2cpp_gchandle_new((Il2CppObject*)gameObject, true));
			app::Object_1_DontDestroyOnLoad((app::Object_1*)gameObject, NULL);
			TransformSetPosition(gameObject, tem::Vector3(-1319.66f, -4643.13f, 0.0f).ToMoon());

			/*switch (sutil::hash(Class.c_str()))
			{
			}*/
		}
	};
}