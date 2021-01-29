#pragma once

#ifndef _SCENEDATA_H
#define _SCENEDATA_H

namespace tem
{
	class SceneData
	{
	public:
		std::string Name = "";
		tem::Vector3 Position;
		tem::Vector2 Size;
		tem::Rect LoadingZone;

		SceneData();
		SceneData(std::string name, tem::Vector3 position, tem::Vector2 size, tem::Rect loadingZone);

		void LoadScene();
	};
}
#endif