#pragma once
class AnimationHelper
{
public:
	static std::unordered_map<std::string, app::MoonAnimation*> AllAnimations;

	static void GetAnimations();
	static app::MoonAnimation* GetAnimation(std::string name);
	static app::MoonAnimation* GetAnimationByName(std::string name);
	static void PlayAnimation(std::string name);
};

