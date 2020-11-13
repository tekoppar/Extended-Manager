#pragma once

//ATTACK ANIMATIONS????
/*Type* type4 = GetType("Moon", "AnimationPlayer");
Object_1__Array* arrA5 = Object_1_FindObjectsOfTypeAll(type4, NULL);

std::vector<MoonAnimation*> allAnimationPlayer;
std::vector<std::string> allAnimationPlayerNames;
for (int i = 0; i < arrA5->max_length; i++)
{
	if (arrA5->vector[i] != nullptr)
	{
		AnimationPlayer* tempMoon = (AnimationPlayer*)arrA5->vector[i];

		if (tempMoon != nullptr && tempMoon->fields.Animation != nullptr)
		{
			String* aniName = MoonAnimation_get_Name(tempMoon->fields.Animation, NULL);
			std::string aniNameS = convert_csstring(aniName);
			allAnimationPlayerNames.push_back(aniNameS);
			allAnimationPlayer.push_back(tempMoon->fields.Animation);
		}
	}
}*/
//ATTACK ANIMATIONS????

//LOTS OF BLEND ANIMATIONS?????
/*Type* type5 = GetType("Moon", "BlendAnimation");
Object_1__Array* arrA6 = Object_1_FindObjectsOfTypeAll(type5, NULL);

std::vector<MoonAnimation*> allBlendAnimation;
std::vector<std::string> allBlendAnimationNames;
if (arrA6 != nullptr)
{
	for (int i = 0; i < arrA6->max_length; i++)
	{
		if (arrA6->vector[i] != nullptr)
		{
			BlendAnimation* tempMoon = (BlendAnimation*)arrA6->vector[i];

			if (tempMoon != nullptr && tempMoon->fields.Inputs != nullptr)
			{
				for (int i2 = 0; i2 < tempMoon->fields.Inputs->max_length; i2++) {
					BlendAnimation_Input* tempVar = tempMoon->fields.Inputs->vector[i2];
					if (tempVar != nullptr) {
						MoonAnimation* moonimation = tempVar->fields.Animation;

						if (moonimation != nullptr) {
							String* aniName = MoonAnimation_get_Name(moonimation, NULL);
							std::string aniNameS = convert_csstring(aniName);
							allBlendAnimationNames.push_back(aniNameS);
							allBlendAnimation.push_back(moonimation);
						}
					}
				}
			}
		}
	}
}*/
//LOTS OF BLEND ANIMATIONS?????

//LOTS OF BLEND ClipAnimation?????
/*Type* type6 = GetType("Moon", "ClipAnimation");
Object_1__Array* arrA7 = Object_1_FindObjectsOfTypeAll(type6, NULL);

std::vector<MoonAnimation*> allClipAnimation;
std::vector<std::string> allClipAnimationNames;
for (int i = 0; i < arrA7->max_length; i++)
{
	if (arrA7->vector[i] != nullptr)
	{
		ClipAnimation* tempMoon = (ClipAnimation*)arrA7->vector[i];
		MoonAnimation* moonimation  = new MoonAnimation();
		moonimation->fields = tempMoon->fields._;

		if (tempMoon != nullptr)
		{
			String* aniName = MoonAnimation_get_Name(moonimation, NULL);
			std::string aniNameS = convert_csstring(aniName);
			allClipAnimationNames.push_back(aniNameS);
			allClipAnimation.push_back(moonimation);
		}
	}
}
//LOTS OF BLEND ClipAnimation?????

Type* type3 = GetType("Moon", "MoonAnimation");
Object_1__Array* arrA = Object_1_FindObjectsOfTypeAll(type3, NULL);
std::vector<std::string> all1ClipAnimationNames;
for (int i = 0; i < arrA->max_length; i++)
{
	if (arrA->vector[i] != NULL && arrA->vector[i] != nullptr)
	{
		MoonAnimation* tempANI = (MoonAnimation*)arrA->vector[i];
		if (tempANI != nullptr) {
			String* aniName = MoonAnimation_get_Name(tempANI, NULL);
			std::string aniNameS = convert_csstring(aniName);
			all1ClipAnimationNames.push_back(aniNameS);
		}
	}
}*/






// Setup for the race animation.

//std::vector<std::string> allObjectsNames;
//std::vector<std::string> allScenesNames;

/*for (int i = 0; i < sceneManager->fields.ActiveScenes->fields._size; i++)
{
	SceneManagerScene* managerScene = sceneManager->fields.ActiveScenes->fields._items->vector[i];

	if (managerScene != nullptr)
	{
		SceneRoot* rootScene = managerScene->fields.SceneRoot;
		RuntimeSceneMetaData* metaData = managerScene->fields.MetaData;
		std::string sceneName = convert_csstring(metaData->fields.Scene);

		if (sceneName == "inkwaterMarshRaceSetups")
		{
			if (rootScene != nullptr)
			{
				GameObject* gameObject = Component_1_get_gameObject((Component_1*)rootScene, NULL);
				std::vector<std::string> scenePath = {"raceData", "raceStop", "art", "guideStoneSetup", "raceMarkerEnd", "body"};
				GameObject* foundObject = GetComponentByScenePath("inkwaterMarshRaceSetups", scenePath);

				Type* type45 = GetType("UnityEngine", "Transform");
				Component_1__Array* components = GameObject_GetComponents(foundObject, type45, NULL);

				for (int i2 = 0; i2 < components->max_length; i2++)
				{
					GameObject* gamyobj = Component_1_get_gameObject(components->vector[i2], NULL);
					String* name = Object_1_get_name((Object_1*)gamyobj, NULL);
					std::string nameS = convert_csstring(name);
					allObjectsNames.push_back(nameS);
				}
			}
		}
	}
}*/

/*app::Type* meshType = GetType("Moon.Timeline", "MoonTimeline");
app::Object_1__Array* meshArr = app::Object_1_FindObjectsOfType(meshType, NULL);

std::vector<std::string> allMeshesNames;

std::vector<app::MoonTimeline*> boolSkippable;
std::vector<app::MoonTimeline*> functionSkippable;
for (int i = 0; i < meshArr->max_length; i++)
{
	if (meshArr->vector[i] != nullptr)
	{
		app::MoonTimeline* timeline = (app::MoonTimeline*)meshArr->vector[i];

		if (timeline != nullptr)
		{
			timeline->fields.IsSkippable = true;
			boolSkippable.push_back(timeline);

			if (timeline->fields.m_timelineContext)
			{
				app::TimelineContext_set_IsSkippable(timeline->fields.m_timelineContext, true, NULL);
				functionSkippable.push_back(timeline);
			}
		}
	}
}*/















/*PreloadSceneByName("questMapScene");

	SceneManagerScene* managerScene = sceneManager->fields.ActiveScenes->fields._items->vector[0];
	GameObject* gameObject = Component_1_get_gameObject((Component_1*)managerScene->fields.SceneRoot, NULL);
	Type* transformType = GetType("UnityEngine", "Transform");
	app::Component_1__Array* components = GameObject_GetComponentsInParent_1(gameObject, transformType, true, NULL);
	GameObject* gamyobj = Component_1_get_gameObject(components->vector[0], NULL);
	components = app::GameObject_GetComponentsInChildren_1(gamyobj, transformType, true, NULL);

	std::vector<std::string> allObjectsNames1;
	std::vector< GameObject*> allwfewefwe;
	for (int i2 = 0; i2 < components->max_length; i2++)
	{
		GameObject* gamyobj = Component_1_get_gameObject(components->vector[i2], NULL);
		String* name = Object_1_get_name((Object_1*)gamyobj, NULL);
		std::string nameS = convert_csstring(name);
			allObjectsNames1.push_back(nameS);
			allwfewefwe.push_back(gamyobj);
	}*/