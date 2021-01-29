#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <future>
#include <unordered_map>

#include "StringUtils.h"
#include "ManagerDef.h"
#include "Tem.h"
#include "ObjectCreator.h"
#include "TemSceneHelper.h"

#include "SceneData.h"

namespace tem 
{
	SceneData::SceneData()
	{
		this->Name = "";
		this->Position = tem::Vector3();
		this->Size = tem::Vector2();
		this->LoadingZone = tem::Rect();
	}

	SceneData::SceneData(std::string name, tem::Vector3 position, tem::Vector2 size, tem::Rect loadingZone)
	{
		this->Name = name;
		this->Position = position;
		this->Size = size;
		this->LoadingZone = loadingZone;
	}

	void SceneData::LoadScene()
	{
		tem::ObjectCreator creator;
		creator.CreateScene(Name, Position, Size, LoadingZone);
	}
}