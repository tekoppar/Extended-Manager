#pragma once

namespace tem {
	class AnimatorStateInfo
	{
	public:
		int Name; // 0x00
		int Path; // 0x04
		int FullPath; // 0x08
		float NormalizedTime; // 0x0C
		float Length; // 0x10
		float Speed; // 0x14
		float SpeedMultiplier; // 0x18
		int Tag; // 0x1C
		int Loop; // 0x20

		AnimatorStateInfo()
		{
			Name = 0;
			Path = 0;
			FullPath = 0;
			NormalizedTime = 0.0f;
			Length = 0.0f;
			Speed = 0.0f;
			SpeedMultiplier = 0.0f;
			Tag = 0;
			Loop = 0;
		}

		AnimatorStateInfo(int name, int path, int fullPath, float normalizedTime, float length, float speed, float speedMultiplier, int tag, int loop)
		{
			Name = name;
			Path = path;
			FullPath = fullPath;
			NormalizedTime = normalizedTime;
			Length = length;
			Speed = speed;
			SpeedMultiplier = speedMultiplier;
			Tag = tag;
			Loop = loop;
		}

		AnimatorStateInfo(app::AnimatorStateInfo* value)
		{
			Name = value->m_Name;
			Path = value->m_Path;
			FullPath = value->m_FullPath;
			NormalizedTime = value->m_NormalizedTime;
			Length = value->m_Length;
			Speed = value->m_Speed;
			SpeedMultiplier = value->m_SpeedMultiplier;
			Tag = value->m_Tag;
			Loop = value->m_Loop;
		}

		app::AnimatorStateInfo ToMoon()
		{
			app::AnimatorStateInfo value = app::AnimatorStateInfo();
			value.m_Name = Name;
			value.m_Path = Path;
			value.m_FullPath = FullPath;
			value.m_NormalizedTime = NormalizedTime;
			value.m_Length = Length;
			value.m_Speed = Speed;
			value.m_SpeedMultiplier = SpeedMultiplier;
			value.m_Tag = Tag;
			value.m_Loop = Loop;

			return value;
		}

		std::string ToString()
		{
			return std::to_string(this->Name) + ", " + std::to_string(this->Path) + ", " + std::to_string(this->FullPath) + ", " + std::to_string(this->NormalizedTime) + ", " +
				std::to_string(this->Length) + ", " + std::to_string(this->Speed) + ", " + std::to_string(this->SpeedMultiplier) + ", " + std::to_string(this->Path) + ", " + std::to_string(this->Loop);
		}
	};
}