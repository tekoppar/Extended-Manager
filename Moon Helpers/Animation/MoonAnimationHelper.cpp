#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include "StringUtils.h"
#include "ManagerDef.h"

#include "MoonAnimationHelper.h"

std::unordered_map<std::string, app::MoonAnimation*> AnimationHelper::AllAnimations;

void AnimationHelper::GetAnimations()
{
	app::Type* type3 = GetType("Moon", "MoonAnimation");
	app::Object_1__Array* arrA = app::Object_1_FindObjectsOfTypeAll(type3, NULL);

	for (int i = 0; i < arrA->max_length; i++)
	{
		if (arrA->vector[i] != NULL && arrA->vector[i] != nullptr)
		{
			app::MoonAnimation* tempANI = (app::MoonAnimation*)arrA->vector[i];

			if (tempANI != nullptr) {
				app::String* aniName = app::MoonAnimation_get_Name(tempANI, NULL);
				std::string aniNameS = sutil::convert_csstring(aniName);
				//app::MoonAnimation* copyAni = (app::MoonAnimation*)app::Object_1_Instantiate_2((app::Object_1*)tempANI, NULL);

				AllAnimations[aniNameS] = tempANI;
			}
		}
	}
}

app::MoonAnimation* AnimationHelper::GetAnimation(std::string name)
{
	app::Type* type3 = GetType("Moon", "MoonAnimation");
	app::Object_1__Array* arrA = app::Object_1_FindObjectsOfTypeAll(type3, NULL);

	for (int i = 0; i < arrA->max_length; i++)
	{
		if (arrA->vector[i] != NULL && arrA->vector[i] != nullptr)
		{
			app::MoonAnimation* tempANI = (app::MoonAnimation*)arrA->vector[i];
			if (tempANI != nullptr) {
				app::String* aniName = app::MoonAnimation_get_Name(tempANI, NULL);
				std::string aniNameS = sutil::convert_csstring(aniName);

				if (aniNameS == name)
					AllAnimations[aniNameS] = tempANI;
			}
		}
	}

	return AllAnimations[name];
}

app::MoonAnimation* AnimationHelper::GetAnimationByName(std::string name)
{
	if (AllAnimations.find(name) != AllAnimations.end())
		return AllAnimations[name];

	return nullptr;
}

void AnimationHelper::PlayAnimation(std::string name)
{
	app::MoonAnimation* animation = GetAnimationByName(name);

	if (animation == nullptr || animation->fields._._.m_CachedPtr == nullptr)
		animation = GetAnimation(name);

	if (animation != nullptr && animation->fields._._.m_CachedPtr != nullptr && animation->klass != nullptr)
	{
		app::SeinPlayAnimationController_PlayAnimation_1(MDV::SeinPlayAnimationController, animation, NULL);
	}
}