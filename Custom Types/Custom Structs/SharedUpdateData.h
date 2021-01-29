#pragma once

namespace tem {
	class SharedUpdateData
	{
	public:
		tem::Vector3 OriPos;
		float AttractionDistance;
		float DeltaTime;
		bool IsMagnetEquipped;
		bool HasUltraMagnet; 

		SharedUpdateData()
		{
			OriPos = tem::Vector3();
			AttractionDistance = 0.0f;
			DeltaTime = 0.0f;
			IsMagnetEquipped = false;
			HasUltraMagnet = false;
		}

		SharedUpdateData(tem::Vector3 oriPos, float attractionDistance, float deltaTime, bool isMagnetEquipped, bool hasUltraMagnet)
		{
			OriPos = oriPos;
			AttractionDistance = attractionDistance;
			DeltaTime = deltaTime;
			IsMagnetEquipped = isMagnetEquipped;
			HasUltraMagnet = hasUltraMagnet;
		}

		SharedUpdateData(app::DropPickup_SharedUpdateData* value)
		{
			OriPos = value->OriPos;
			AttractionDistance = value->AttractionDistance;
			DeltaTime = value->DeltaTime;
			IsMagnetEquipped = value->IsMagnetEquipped;
			HasUltraMagnet = value->HasUltraMagnet;
		}

		app::DropPickup_SharedUpdateData ToMoon()
		{
			app::DropPickup_SharedUpdateData value = app::DropPickup_SharedUpdateData();
			value.OriPos = OriPos.ToMoon();
			value.AttractionDistance = AttractionDistance;
			value.DeltaTime = DeltaTime;
			value.IsMagnetEquipped = IsMagnetEquipped;
			value.HasUltraMagnet = HasUltraMagnet;

			return value;
		}

		std::string ToString()
		{
			return OriPos.ToString() + ", " + std::to_string(this->AttractionDistance) + ", " + std::to_string(this->DeltaTime) + ", " + std::to_string(this->IsMagnetEquipped) + ", " + std::to_string(this->HasUltraMagnet);
		}
	};
}