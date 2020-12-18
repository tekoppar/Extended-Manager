#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <filesystem>

#include "StringUtils.h"
#include "ManagerDef.h"
#include "UberStateManager.h"

#include "SeinVisualEditor.h"

void VisualSettingsUpdated::ResetBooleans()
{
	this->HasUpdatedBow = false;
	this->HasUpdatedGlide = false;
	this->HasUpdatedGoldenSein = false;
	this->HasUpdatedHammer = false;
	this->HasUpdatedOri = false;
	this->HasUpdatedSword = false;
	this->HasUpdatedTorch = false;
	this->HasUpdatedGrenade = false;
}

/*app::Type* transformType = GetType("UnityEngine", "Renderer");
		std::vector<std::string> componentsNames;
		app::Component_1__Array* components = app::GameObject_GetComponentsInChildren_1(uberPoolGroup->fields.m_poolObjects->fields._items->vector[0]->fields.Target, transformType, true, NULL);
		for (int i = 0; i < components->max_length; i++)
		{
			if (components->vector[i] != nullptr)
			{
				app::GameObject* gamyobj = app::Component_1_get_gameObject(components->vector[i], NULL);
				app::String* oName = app::Object_1_get_name((app::Object_1*)gamyobj, NULL);
				componentsNames.push_back(il2cppi_to_string(oName));
			}
		}*/

VisualSettingsUpdated SeinVisualEditor::VisualSettingsUpdated;
VisualSettings SeinVisualEditor::DefaultVisualSettings;
VisualSettings SeinVisualEditor::VisualSettings;
std::unordered_map<std::string, tem::Vector4> SeinVisualEditor::DefaultVisualColors = std::unordered_map<std::string, tem::Vector4>();
app::GameObject* SeinVisualEditor::OriHat = nullptr;
bool SeinVisualEditor::ManagerLoaded = false;

void SeinVisualEditor::SetAllVisuals()
{
	if (SeinVisualEditor::VisualSettingsUpdated.HasUpdatedOri == false)
		SeinVisualEditor::VisualSettings.OriVisualSettings.SetOriVisuals(SeinVisualEditor::VisualSettings.OriVisualSettings);

	if (SeinVisualEditor::VisualSettingsUpdated.HasUpdatedTorch == false)
		SeinVisualEditor::VisualSettings.TorchVisualSettings.SetTorchVisuals(SeinVisualEditor::VisualSettings.TorchVisualSettings);

	if (SeinVisualEditor::VisualSettingsUpdated.HasUpdatedGlide == false)
		SeinVisualEditor::VisualSettings.GlideVisualSettings.SetGlideVisuals(SeinVisualEditor::VisualSettings.GlideVisualSettings);

	if (SeinVisualEditor::VisualSettingsUpdated.HasUpdatedBow == false)
		SeinVisualEditor::VisualSettings.BowVisualSettings.SetBowVisuals(SeinVisualEditor::VisualSettings.BowVisualSettings);

	if (SeinVisualEditor::VisualSettingsUpdated.HasUpdatedGoldenSein == false)
		SeinVisualEditor::VisualSettings.GoldenSeinVisualSettings.SetGoldenSeinVisuals(SeinVisualEditor::VisualSettings.GoldenSeinVisualSettings);

	if (SeinVisualEditor::VisualSettingsUpdated.HasUpdatedHammer == false)
		SeinVisualEditor::VisualSettings.HammerVisualSettings.SetHammerVisuals(SeinVisualEditor::VisualSettings.HammerVisualSettings);

	if (SeinVisualEditor::VisualSettingsUpdated.HasUpdatedSword == false)
		SeinVisualEditor::VisualSettings.SwordVisualSettings.SetSwordVisuals(SeinVisualEditor::VisualSettings.SwordVisualSettings);

	if (SeinVisualEditor::VisualSettingsUpdated.HasUpdatedGrenade == false)
		SeinVisualEditor::VisualSettings.GrenadeVisualSettings.SetGrenadeVisuals(SeinVisualEditor::VisualSettings.GrenadeVisualSettings);
}

void SeinVisualEditor::LoadJsonFile(std::string& path)
{
	std::string contents = sutil::ReadFile(path);
	nlohmann::json j = nlohmann::json::parse(contents);
	nlohmann::json jj = j.at("VisualSettings");
	nlohmann::json jj1 = j.at("ActiveVisualSetting");

	VisualSettings.OriVisualSettings.HideGlow = jj1["OriVisualSettings"]["HideGlow"].get<bool>();
	VisualSettings.OriVisualSettings.Ori = jj1["OriVisualSettings"]["Ori"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.OriVisualSettings.OriGlow = jj1["OriVisualSettings"]["OriGlow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.OriVisualSettings.OriTrail = jj1["OriVisualSettings"]["OriTrail"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.OriVisualSettings.TexturePath = jj1["OriVisualSettings"]["TexturePath"].get<std::string>();

	VisualSettings.GoldenSeinVisualSettings.SeinBodyColor = jj1["GoldenSeinVisualSettings"]["SeinBody"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GoldenSeinVisualSettings.SeinBodyEmissiveColor = jj1["GoldenSeinVisualSettings"]["SeinBodyEmissive"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GoldenSeinVisualSettings.SeinParticleColor = jj1["GoldenSeinVisualSettings"]["SeinParticle"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GoldenSeinVisualSettings.SeinRadialLightColor = jj1["GoldenSeinVisualSettings"]["SeinRadialLight"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GoldenSeinVisualSettings.SeinTrailColor = jj1["GoldenSeinVisualSettings"]["SeinTrail"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GoldenSeinVisualSettings.SeinTrailMeshColor = jj1["GoldenSeinVisualSettings"]["SeinTrailMesh"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSettings.SwordVisualSettings.SwordColor = jj1["SwordVisualSettings"]["Sword"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordEmissiveColor = jj1["SwordVisualSettings"]["SwordEmissive"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordHitEffectColor = jj1["SwordVisualSettings"]["SwordHitEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordHitEffectEmissiveColor = jj1["SwordVisualSettings"]["SwordHitEffectEmissive"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSettings.SwordVisualSettings.SwordAttackAirPoke.BlowingSand = jj1["SwordVisualSettings"]["SwordAttackAirPoke"]["BlowingSand"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordAttackAirPoke.Glow = jj1["SwordVisualSettings"]["SwordAttackAirPoke"]["Glow"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSettings.SwordVisualSettings.SwordAttackDownAir.EnergyEffect = jj1["SwordVisualSettings"]["SwordAttackDownAir"]["EnergyEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordAttackDownAir.FireSprite = jj1["SwordVisualSettings"]["SwordAttackDownAir"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordAttackDownAir.SnowPattern = jj1["SwordVisualSettings"]["SwordAttackDownAir"]["SnowPattern"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordAttackDownAir.VignetteMaskC = jj1["SwordVisualSettings"]["SwordAttackDownAir"]["VignetteMaskC"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSettings.SwordVisualSettings.SwordAttackGroundA.EnergyEffect = jj1["SwordVisualSettings"]["SwordAttackGroundA"]["EnergyEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordAttackGroundA.FireSprite = jj1["SwordVisualSettings"]["SwordAttackGroundA"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordAttackGroundA.SnowPattern = jj1["SwordVisualSettings"]["SwordAttackGroundA"]["SnowPattern"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordAttackGroundA.VignetteMaskC = jj1["SwordVisualSettings"]["SwordAttackGroundA"]["VignetteMaskC"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSettings.SwordVisualSettings.SwordAttackGroundB.EnergyEffect = jj1["SwordVisualSettings"]["SwordAttackGroundB"]["EnergyEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordAttackGroundB.FireSprite = jj1["SwordVisualSettings"]["SwordAttackGroundB"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordAttackGroundB.SnowPattern = jj1["SwordVisualSettings"]["SwordAttackGroundB"]["SnowPattern"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordAttackGroundB.VignetteMaskC = jj1["SwordVisualSettings"]["SwordAttackGroundB"]["VignetteMaskC"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSettings.SwordVisualSettings.SwordAttackGroundC.BlowingSand = jj1["SwordVisualSettings"]["SwordAttackGroundC"]["BlowingSand"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordAttackGroundC.SnowPattern = jj1["SwordVisualSettings"]["SwordAttackGroundC"]["SnowPattern"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordAttackGroundC.SnowPattern2 = jj1["SwordVisualSettings"]["SwordAttackGroundC"]["SnowPattern2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordAttackGroundC.VignetteMaskC = jj1["SwordVisualSettings"]["SwordAttackGroundC"]["VignetteMaskC"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSettings.SwordVisualSettings.SwordAttackUp.EnergyEffect = jj1["SwordVisualSettings"]["SwordAttackUp"]["EnergyEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordAttackUp.FireSprite = jj1["SwordVisualSettings"]["SwordAttackUp"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordAttackUp.SnowPattern = jj1["SwordVisualSettings"]["SwordAttackUp"]["SnowPattern"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordAttackUp.VignetteMaskC = jj1["SwordVisualSettings"]["SwordAttackUp"]["VignetteMaskC"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSettings.SwordVisualSettings.SwordBlock.AcidParticles = jj1["SwordVisualSettings"]["SwordBlock"]["AcidParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordBlock.CharacterGlow = jj1["SwordVisualSettings"]["SwordBlock"]["CharacterGlow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordBlock.Circle = jj1["SwordVisualSettings"]["SwordBlock"]["Circle"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordBlock.CircleGlowC = jj1["SwordVisualSettings"]["SwordBlock"]["CircleGlowC"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordBlock.Distortion = jj1["SwordVisualSettings"]["SwordBlock"]["Distortion"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordBlock.FxBox = jj1["SwordVisualSettings"]["SwordBlock"]["FxBox"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordBlock.Glow = jj1["SwordVisualSettings"]["SwordBlock"]["Glow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordBlock.LavaFountainA = jj1["SwordVisualSettings"]["SwordBlock"]["LavaFountainA"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordBlock.NoiseCaustic = jj1["SwordVisualSettings"]["SwordBlock"]["NoiseCaustic"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordBlock.SingleSnowParticleA = jj1["SwordVisualSettings"]["SwordBlock"]["SingleSnowParticleA"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordBlock.SnowPattern = jj1["SwordVisualSettings"]["SwordBlock"]["SnowPattern"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordBlock.SnowPattern2 = jj1["SwordVisualSettings"]["SwordBlock"]["SnowPattern2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordBlock.StarSpike = jj1["SwordVisualSettings"]["SwordBlock"]["StarSpike"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSettings.SwordVisualSettings.SwordDamageBlue.BurningCoreParticles = jj1["SwordVisualSettings"]["SwordDamageBlue"]["BurningCoreParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordDamageBlue.BurnMarks = jj1["SwordVisualSettings"]["SwordDamageBlue"]["BurnMarks"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordDamageBlue.DebrisParticles = jj1["SwordVisualSettings"]["SwordDamageBlue"]["DebrisParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordDamageBlue.Distortion = jj1["SwordVisualSettings"]["SwordDamageBlue"]["Distortion"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordDamageBlue.ImpactCenter = jj1["SwordVisualSettings"]["SwordDamageBlue"]["ImpactCenter"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordDamageBlue.ImpactSparklesA = jj1["SwordVisualSettings"]["SwordDamageBlue"]["ImpactSparklesA"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordDamageBlue.SmokeParticles = jj1["SwordVisualSettings"]["SwordDamageBlue"]["SmokeParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordDamageBlue.SparkStartParticles = jj1["SwordVisualSettings"]["SwordDamageBlue"]["SparkStartParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordDamageBlue.VignetteMaskC = jj1["SwordVisualSettings"]["SwordDamageBlue"]["VignetteMaskC"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSettings.SwordVisualSettings.SwordHit.DebrisParticles = jj1["SwordVisualSettings"]["SwordHit"]["DebrisParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordHit.DebrisParticlesFallBig = jj1["SwordVisualSettings"]["SwordHit"]["DebrisParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordHit.DistortionNew = jj1["SwordVisualSettings"]["SwordHit"]["DebrisParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordHit.DropGlowB = jj1["SwordVisualSettings"]["SwordHit"]["DebrisParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordHit.FxBox = jj1["SwordVisualSettings"]["SwordHit"]["DebrisParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordHit.GlowUnmask = jj1["SwordVisualSettings"]["SwordHit"]["DebrisParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordHit.LensCrossStart = jj1["SwordVisualSettings"]["SwordHit"]["DebrisParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordHit.LensFlare20b = jj1["SwordVisualSettings"]["SwordHit"]["DebrisParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordHit.LensFlare9 = jj1["SwordVisualSettings"]["SwordHit"]["DebrisParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordHit.LensRadialSpike = jj1["SwordVisualSettings"]["SwordHit"]["DebrisParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordHit.LightCircleShape = jj1["SwordVisualSettings"]["SwordHit"]["DebrisParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordHit.LightGlow = jj1["SwordVisualSettings"]["SwordHit"]["DebrisParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordHit.RadialBurned2 = jj1["SwordVisualSettings"]["SwordHit"]["DebrisParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordHit.RadialLightRays = jj1["SwordVisualSettings"]["SwordHit"]["DebrisParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordHit.RadialMaskB = jj1["SwordVisualSettings"]["SwordHit"]["DebrisParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordHit.SparksLong = jj1["SwordVisualSettings"]["SwordHit"]["DebrisParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordHit.SplashEdge = jj1["SwordVisualSettings"]["SwordHit"]["DebrisParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordHit.SplashEdge2 = jj1["SwordVisualSettings"]["SwordHit"]["DebrisParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordHit.StarSpike2 = jj1["SwordVisualSettings"]["SwordHit"]["DebrisParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.SwordVisualSettings.SwordHit.VignetteMaskC = jj1["SwordVisualSettings"]["SwordHit"]["DebrisParticles"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSettings.HammerVisualSettings.HammerColor = jj1["HammerVisualSettings"]["Hammer"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerEmissiveColor = jj1["HammerVisualSettings"]["HammerEmissive"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerHitEffectColor = jj1["HammerVisualSettings"]["HammerHitEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerHitEffectEmissiveColor = jj1["HammerVisualSettings"]["HammerHitEffectEmissive"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSettings.HammerVisualSettings.HammerAttackAir1.EnergyEffect = jj1["HammerVisualSettings"]["HammerAttackAir1"]["EnergyEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackAir1.FireSprite = jj1["HammerVisualSettings"]["HammerAttackAir1"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackAir1.LinearGradientMask = jj1["HammerVisualSettings"]["HammerAttackAir1"]["LinearGradientMask"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackAir1.SpriteSnowPettern2 = jj1["HammerVisualSettings"]["HammerAttackAir1"]["SpriteSnowPettern2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackAir1.VignetteMaskC = jj1["HammerVisualSettings"]["HammerAttackAir1"]["VignetteMaskC"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSettings.HammerVisualSettings.HammerAttackAir2.EnergyEffect = jj1["HammerVisualSettings"]["HammerAttackAir2"]["EnergyEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackAir2.FireSprite = jj1["HammerVisualSettings"]["HammerAttackAir2"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackAir2.LinearGradientMask = jj1["HammerVisualSettings"]["HammerAttackAir2"]["LinearGradientMask"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackAir2.SpriteSnowPettern2 = jj1["HammerVisualSettings"]["HammerAttackAir2"]["SpriteSnowPettern2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackAir2.VignetteMaskC = jj1["HammerVisualSettings"]["HammerAttackAir2"]["VignetteMaskC"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSettings.HammerVisualSettings.HammerAttackAir3.EnergyEffect = jj1["HammerVisualSettings"]["HammerAttackAir3"]["EnergyEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackAir3.FireSprite = jj1["HammerVisualSettings"]["HammerAttackAir3"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackAir3.LinearGradientMask = jj1["HammerVisualSettings"]["HammerAttackAir3"]["LinearGradientMask"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackAir3.SpriteSnowPettern2 = jj1["HammerVisualSettings"]["HammerAttackAir3"]["SpriteSnowPettern2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackAir3.VignetteMaskC = jj1["HammerVisualSettings"]["HammerAttackAir3"]["VignetteMaskC"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSettings.HammerVisualSettings.HammerAttackAirUpSwipe.EnergyEffect = jj1["HammerVisualSettings"]["HammerAttackAirUpSwipe"]["EnergyEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackAirUpSwipe.FireSprite = jj1["HammerVisualSettings"]["HammerAttackAirUpSwipe"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackAirUpSwipe.LinearGradientMask = jj1["HammerVisualSettings"]["HammerAttackAirUpSwipe"]["LinearGradientMask"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackAirUpSwipe.SpriteSnowPettern2 = jj1["HammerVisualSettings"]["HammerAttackAirUpSwipe"]["SpriteSnowPettern2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackAirUpSwipe.VignetteMaskC = jj1["HammerVisualSettings"]["HammerAttackAirUpSwipe"]["VignetteMaskC"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSettings.HammerVisualSettings.HammerAttackGround.EnergyEffect = jj1["HammerVisualSettings"]["HammerAttackGround1"]["EnergyEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackGround.FireSprite = jj1["HammerVisualSettings"]["HammerAttackGround1"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackGround.LinearGradientMask = jj1["HammerVisualSettings"]["HammerAttackGround1"]["LinearGradientMask"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackGround.SpriteSnowPettern2 = jj1["HammerVisualSettings"]["HammerAttackGround1"]["SpriteSnowPettern2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackGround.VignetteMaskC = jj1["HammerVisualSettings"]["HammerAttackGround1"]["VignetteMaskC"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSettings.HammerVisualSettings.HammerAttackGround2.EnergyEffect = jj1["HammerVisualSettings"]["HammerAttackGround2"]["EnergyEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackGround2.FireSprite = jj1["HammerVisualSettings"]["HammerAttackGround2"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackGround2.LinearGradientMask = jj1["HammerVisualSettings"]["HammerAttackGround2"]["LinearGradientMask"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackGround2.SpriteSnowPettern2 = jj1["HammerVisualSettings"]["HammerAttackGround2"]["SpriteSnowPettern2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackGround2.VignetteMaskC = jj1["HammerVisualSettings"]["HammerAttackGround2"]["VignetteMaskC"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSettings.HammerVisualSettings.HammerAttackGroundDown.EnergyEffect = jj1["HammerVisualSettings"]["HammerAttackGroundDown"]["EnergyEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackGroundDown.FireSprite = jj1["HammerVisualSettings"]["HammerAttackGroundDown"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackGroundDown.LinearGradientMask = jj1["HammerVisualSettings"]["HammerAttackGroundDown"]["LinearGradientMask"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackGroundDown.SpriteSnowPettern2 = jj1["HammerVisualSettings"]["HammerAttackGroundDown"]["SpriteSnowPettern2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackGroundDown.VignetteMaskC = jj1["HammerVisualSettings"]["HammerAttackGroundDown"]["VignetteMaskC"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSettings.HammerVisualSettings.HammerAttackGroundUpSwipe.EnergyEffect = jj1["HammerVisualSettings"]["HammerAttackGroundUpSwipe"]["EnergyEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackGroundUpSwipe.FireSprite = jj1["HammerVisualSettings"]["HammerAttackGroundUpSwipe"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackGroundUpSwipe.LinearGradientMask = jj1["HammerVisualSettings"]["HammerAttackGroundUpSwipe"]["LinearGradientMask"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackGroundUpSwipe.SpriteSnowPettern2 = jj1["HammerVisualSettings"]["HammerAttackGroundUpSwipe"]["SpriteSnowPettern2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackGroundUpSwipe.VignetteMaskC = jj1["HammerVisualSettings"]["HammerAttackGroundUpSwipe"]["VignetteMaskC"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSettings.HammerVisualSettings.HammerAttackStomp.GiftLeafTransformationLightRing = jj1["HammerVisualSettings"]["HammerAttackStomp"]["GiftLeafTransformationLightRing"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.HammerVisualSettings.HammerAttackStomp.Glow = jj1["HammerVisualSettings"]["HammerAttackStomp"]["GiftLeafTransformationLightRing"].get<tem::Vector4>();
	VisualSettings.HammerVisualSettings.HammerAttackStomp.Glow1 = jj1["HammerVisualSettings"]["HammerAttackStomp"]["GiftLeafTransformationLightRing"].get<tem::Vector4>();
	VisualSettings.HammerVisualSettings.HammerAttackStomp.SingleSnowParticleA = jj1["HammerVisualSettings"]["HammerAttackStomp"]["GiftLeafTransformationLightRing"].get<tem::Vector4>();
	VisualSettings.HammerVisualSettings.HammerAttackStomp.Smoke = jj1["HammerVisualSettings"]["HammerAttackStomp"]["GiftLeafTransformationLightRing"].get<tem::Vector4>();

	VisualSettings.HammerVisualSettings.HammerBlock.AcidParticles = jj1["HammerVisualSettings"]["HammerBlock"]["AcidParticles"].get<tem::Vector4>();
	VisualSettings.HammerVisualSettings.HammerBlock.CharacterGlow = jj1["HammerVisualSettings"]["HammerBlock"]["CharacterGlow"].get<tem::Vector4>();
	VisualSettings.HammerVisualSettings.HammerBlock.Circle = jj1["HammerVisualSettings"]["HammerBlock"]["Circle"].get<tem::Vector4>();
	VisualSettings.HammerVisualSettings.HammerBlock.Glow = jj1["HammerVisualSettings"]["HammerBlock"]["Glow"].get<tem::Vector4>();
	VisualSettings.HammerVisualSettings.HammerBlock.LavaFountainA = jj1["HammerVisualSettings"]["HammerBlock"]["LavaFountainA"].get<tem::Vector4>();
	VisualSettings.HammerVisualSettings.HammerBlock.SingleSnowParticleA = jj1["HammerVisualSettings"]["HammerBlock"]["SingleSnowParticleA"].get<tem::Vector4>();

	VisualSettings.HammerVisualSettings.HammerHit.DistortionNew = jj1["HammerVisualSettings"]["HammerHit"]["DistortionNew"].get<tem::Vector4>();
	VisualSettings.HammerVisualSettings.HammerHit.FxBox = jj1["HammerVisualSettings"]["HammerHit"]["FxBox"].get<tem::Vector4>();
	VisualSettings.HammerVisualSettings.HammerHit.Glow = jj1["HammerVisualSettings"]["HammerHit"]["Glow"].get<tem::Vector4>();

	VisualSettings.HammerVisualSettings.HammerStompPreparation.FireSprite3Flip = jj1["HammerVisualSettings"]["HammerStompPreparation"]["FireSprite3Flip"].get<tem::Vector4>();
	VisualSettings.HammerVisualSettings.HammerStompPreparation.VignetteMaskC = jj1["HammerVisualSettings"]["HammerStompPreparation"]["VignetteMaskC"].get<tem::Vector4>();

	nlohmann::json jBowVisuals = jj1.at("BowVisualSettings");
	VisualSettings.BowVisualSettings.BowShaftColor = jBowVisuals["BowShaft"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.BowVisualSettings.BowShaftEmissiveColor = jBowVisuals["BowShaftEmissive"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.BowVisualSettings.BowStringColor = jBowVisuals["BowString"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.BowVisualSettings.BowStringEmissiveColor = jBowVisuals["BowStringEmissive"].get<tem::Vector4>() * 0.003921568627451f;

	nlohmann::json jArrowVisuals = jBowVisuals.at("ArrowVisualSettings");
	VisualSettings.BowVisualSettings.ArrowVisualSettings.ArrowEffectColor = jArrowVisuals["ArrowEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.BowVisualSettings.ArrowVisualSettings.ArrowEffectEmissiveColor = jArrowVisuals["ArrowEffectEmissive"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.BowVisualSettings.ArrowVisualSettings.ArrowSpearColor = jArrowVisuals["ArrowSpear"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.BowVisualSettings.ArrowVisualSettings.ArrowSpearEmissiveColor = jArrowVisuals["ArrowSpearEmissive"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.BowVisualSettings.ArrowVisualSettings.TipImpactColor = jArrowVisuals["TipImpact"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.BowVisualSettings.ArrowVisualSettings.TipImpactEmissiveColor = jArrowVisuals["TipImpactEmissive"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.BowVisualSettings.ArrowVisualSettings.TipParticleColor = jArrowVisuals["TipParticle"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.BowVisualSettings.ArrowVisualSettings.TipParticleEmissiveColor = jArrowVisuals["TipParticleEmissive"].get<tem::Vector4>() * 0.003921568627451f;

	nlohmann::json jGlideVisuals = jj1.at("GlideVisualSettings");
	VisualSettings.GlideVisualSettings.FeatherColor = jGlideVisuals["Feather"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GlideVisualSettings.FeatherEmissiveColor = jGlideVisuals["FeatherEmissive"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GlideVisualSettings.FeatherflapColor = jGlideVisuals["Featherflap"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GlideVisualSettings.FeatherflapEmissiveColor = jGlideVisuals["FeatherflapEmissive"].get<tem::Vector4>() * 0.003921568627451f;
	//VisualSettings.GlideVisualSettings.FeatherUpwindColor = jGlideVisuals["FeatherUpwind"].get<tem::Vector4>();

	nlohmann::json jTorchVisuals = jj1.at("TorchVisualSettings");
	VisualSettings.TorchVisualSettings.HideGlow = jTorchVisuals["HideGlow"].get<bool>();
	VisualSettings.TorchVisualSettings.TorchColor = jTorchVisuals["Torch"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchFloatingSparkColor = jTorchVisuals["TorchFloatingSpark"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchLightEffect = jTorchVisuals["TorchLightEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchRunningColor = jTorchVisuals["TorchRunning"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchSpark = jTorchVisuals["TorchSpark"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchTrailMeshColor = jTorchVisuals["TorchTrailMesh"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchTrailMeshEnable = jTorchVisuals["TorchTrailMeshEnable"].get<bool>();

	TorchAttack airAttack1;
	VisualSettings.TorchVisualSettings.TorchAirAttacks.push_back(airAttack1);
	TorchAttack airAttack2;
	VisualSettings.TorchVisualSettings.TorchAirAttacks.push_back(airAttack2);
	TorchAttack airAttack3;
	VisualSettings.TorchVisualSettings.TorchAirAttacks.push_back(airAttack3);

	VisualSettings.TorchVisualSettings.TorchAirAttacks[0].FireSprite = jTorchVisuals["TorchAirAttacks1"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchAirAttacks[0].TrailZigZag = jTorchVisuals["TorchAirAttacks1"]["TrailZigZag"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchAirAttacks[1].FireSprite = jTorchVisuals["TorchAirAttacks2"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchAirAttacks[1].TrailZigZag = jTorchVisuals["TorchAirAttacks2"]["TrailZigZag"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchAirAttacks[2].FireSprite = jTorchVisuals["TorchAirAttacks3"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchAirAttacks[2].TrailZigZag = jTorchVisuals["TorchAirAttacks3"]["TrailZigZag"].get<tem::Vector4>() * 0.003921568627451f;

	TorchAttack groundAttack1;
	VisualSettings.TorchVisualSettings.TorchGroundAttacks.push_back(groundAttack1);
	TorchAttack groundAttack2;
	VisualSettings.TorchVisualSettings.TorchGroundAttacks.push_back(groundAttack2);
	TorchAttack groundAttack3;
	VisualSettings.TorchVisualSettings.TorchGroundAttacks.push_back(groundAttack3);

	VisualSettings.TorchVisualSettings.TorchGroundAttacks[0].FireSprite = jTorchVisuals["TorchGroundAttacks1"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchGroundAttacks[0].TrailZigZag = jTorchVisuals["TorchGroundAttacks1"]["TrailZigZag"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchGroundAttacks[1].FireSprite = jTorchVisuals["TorchGroundAttacks2"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchGroundAttacks[1].TrailZigZag = jTorchVisuals["TorchGroundAttacks2"]["TrailZigZag"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchGroundAttacks[2].FireSprite = jTorchVisuals["TorchGroundAttacks3"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchGroundAttacks[2].TrailZigZag = jTorchVisuals["TorchGroundAttacks3"]["TrailZigZag"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSettings.TorchVisualSettings.TorchBreak.AcidParticles = jTorchVisuals["TorchBreak"]["AcidParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchBreak.CharacterGlow = jTorchVisuals["TorchBreak"]["CharacterGlow"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSettings.TorchVisualSettings.TorchHit.FireEffect = jTorchVisuals["TorchHit"]["FireEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchHit.FireEffect2 = jTorchVisuals["TorchHit"]["FireEffect2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchHit.FlameFireC = jTorchVisuals["TorchHit"]["FlameFireC"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchHit.FlameGlow = jTorchVisuals["TorchHit"]["FlameGlow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchHit.FsBox = jTorchVisuals["TorchHit"]["FsBox"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchHit.Glow = jTorchVisuals["TorchHit"]["Glow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchHit.GlowUnmask = jTorchVisuals["TorchHit"]["GlowUnmask"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchHit.RadialBurned = jTorchVisuals["TorchHit"]["RadialBurned"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchHit.RadialBurned2 = jTorchVisuals["TorchHit"]["RadialBurned2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchHit.SpriteSnowPattern = jTorchVisuals["TorchHit"]["SpriteSnowPattern"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSettings.TorchVisualSettings.TorchHitSmall.FireEffect = jTorchVisuals["TorchHitSmall"]["FireEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchHitSmall.FireEffect2 = jTorchVisuals["TorchHitSmall"]["FireEffect2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchHitSmall.FlameFireC = jTorchVisuals["TorchHitSmall"]["FlameFireC"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchHitSmall.FlameGlow = jTorchVisuals["TorchHitSmall"]["FlameGlow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchHitSmall.FsBox = jTorchVisuals["TorchHitSmall"]["FsBox"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchHitSmall.Glow = jTorchVisuals["TorchHitSmall"]["Glow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchHitSmall.GlowUnmask = jTorchVisuals["TorchHitSmall"]["GlowUnmask"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchHitSmall.RadialBurned = jTorchVisuals["TorchHitSmall"]["RadialBurned"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchHitSmall.RadialBurned2 = jTorchVisuals["TorchHitSmall"]["RadialBurned2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.TorchVisualSettings.TorchHitSmall.SpriteSnowPattern = jTorchVisuals["TorchHitSmall"]["SpriteSnowPattern"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSettings.GrenadeVisualSettings.Grenade.FireEffect = jj1["GrenadeVisualSettings"]["Grenade"]["FireEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.Grenade.FireSprite = jj1["GrenadeVisualSettings"]["Grenade"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.Grenade.Flame1 = jj1["GrenadeVisualSettings"]["Grenade"]["Flame1"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.Grenade.Flame2 = jj1["GrenadeVisualSettings"]["Grenade"]["Flame2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.Grenade.Flame3 = jj1["GrenadeVisualSettings"]["Grenade"]["Flame3"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.Grenade.LightCircle = jj1["GrenadeVisualSettings"]["Grenade"]["LightCircle"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.Grenade.MainTrail = jj1["GrenadeVisualSettings"]["Grenade"]["MainTrail"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.Grenade.ProtectiveLight = jj1["GrenadeVisualSettings"]["Grenade"]["ProtectiveLight"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.Grenade.Smoke = jj1["GrenadeVisualSettings"]["Grenade"]["Smoke"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.Grenade.SnowPattern1 = jj1["GrenadeVisualSettings"]["Grenade"]["SnowPattern1"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.Grenade.SnowPattern2 = jj1["GrenadeVisualSettings"]["Grenade"]["SnowPattern2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.Grenade.SnowPattern3 = jj1["GrenadeVisualSettings"]["Grenade"]["SnowPattern3"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.Grenade.TrailZigZag = jj1["GrenadeVisualSettings"]["Grenade"]["TrailZigZag"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSettings.GrenadeVisualSettings.Charged.FireEffect = jj1["GrenadeVisualSettings"]["Charged"]["FireEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.Charged.FireSprite = jj1["GrenadeVisualSettings"]["Charged"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.Charged.Flame1 = jj1["GrenadeVisualSettings"]["Charged"]["Flame1"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.Charged.Flame2 = jj1["GrenadeVisualSettings"]["Charged"]["Flame2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.Charged.Flame3 = jj1["GrenadeVisualSettings"]["Charged"]["Flame3"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.Charged.LightCircle = jj1["GrenadeVisualSettings"]["Charged"]["LightCircle"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.Charged.MainTrail = jj1["GrenadeVisualSettings"]["Charged"]["MainTrail"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.Charged.ProtectiveLight = jj1["GrenadeVisualSettings"]["Charged"]["ProtectiveLight"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.Charged.Smoke = jj1["GrenadeVisualSettings"]["Charged"]["Smoke"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.Charged.SnowPattern1 = jj1["GrenadeVisualSettings"]["Charged"]["SnowPattern1"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.Charged.SnowPattern2 = jj1["GrenadeVisualSettings"]["Charged"]["SnowPattern2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.Charged.SnowPattern3 = jj1["GrenadeVisualSettings"]["Charged"]["SnowPattern3"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.Charged.TrailZigZag = jj1["GrenadeVisualSettings"]["Charged"]["TrailZigZag"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSettings.GrenadeVisualSettings.GrenadeAiming.OuterGlow = jj1["GrenadeVisualSettings"]["GrenadeAiming"]["OuterGlow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeAiming.Sparkle = jj1["GrenadeVisualSettings"]["GrenadeAiming"]["Sparkle"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeAiming.Sprite1 = jj1["GrenadeVisualSettings"]["GrenadeAiming"]["Sprite1"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeAiming.Sprite2 = jj1["GrenadeVisualSettings"]["GrenadeAiming"]["Sprite2"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSettings.GrenadeVisualSettings.GrenadeCharging.ArcaneOrb = jj1["GrenadeVisualSettings"]["GrenadeCharging"]["ArcaneOrb"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeCharging.ChargingJump = jj1["GrenadeVisualSettings"]["GrenadeCharging"]["ChargingJump"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeCharging.EnergySplash = jj1["GrenadeVisualSettings"]["GrenadeCharging"]["EnergySplash"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeCharging.SnowPattern = jj1["GrenadeVisualSettings"]["GrenadeCharging"]["SnowPattern"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeCharging.VignetteMask1 = jj1["GrenadeVisualSettings"]["GrenadeCharging"]["VignetteMask1"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeCharging.VignetteMask2 = jj1["GrenadeVisualSettings"]["GrenadeCharging"]["VignetteMask2"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSettings.GrenadeVisualSettings.GrenadeExplosion.Distortion = jj1["GrenadeVisualSettings"]["GrenadeExplosion"]["Distortion"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosion.FireEffect = jj1["GrenadeVisualSettings"]["GrenadeExplosion"]["FireEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosion.ForceField = jj1["GrenadeVisualSettings"]["GrenadeExplosion"]["ForceField"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosion.FX = jj1["GrenadeVisualSettings"]["GrenadeExplosion"]["FX"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosion.LightCircle = jj1["GrenadeVisualSettings"]["GrenadeExplosion"]["LightCircle"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosion.LightGlow = jj1["GrenadeVisualSettings"]["GrenadeExplosion"]["LightGlow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosion.RadialBurned = jj1["GrenadeVisualSettings"]["GrenadeExplosion"]["RadialBurned"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosion.RadialBurned2 = jj1["GrenadeVisualSettings"]["GrenadeExplosion"]["RadialBurned2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosion.RadialCrack = jj1["GrenadeVisualSettings"]["GrenadeExplosion"]["RadialCrack"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosion.RadialIrisImpact = jj1["GrenadeVisualSettings"]["GrenadeExplosion"]["RadialIrisImpact"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosion.Smoke = jj1["GrenadeVisualSettings"]["GrenadeExplosion"]["Smoke"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosion.SnowPattern = jj1["GrenadeVisualSettings"]["GrenadeExplosion"]["SnowPattern"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosion.SpriteSheetFire = jj1["GrenadeVisualSettings"]["GrenadeExplosion"]["SpriteSheetFire"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosion.StarSpike = jj1["GrenadeVisualSettings"]["GrenadeExplosion"]["StarSpike"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSettings.GrenadeVisualSettings.GrenadeExplosionCharged.Distortion = jj1["GrenadeVisualSettings"]["GrenadeExplosionCharged"]["Distortion"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosionCharged.FireEffect = jj1["GrenadeVisualSettings"]["GrenadeExplosionCharged"]["FireEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosionCharged.ForceField = jj1["GrenadeVisualSettings"]["GrenadeExplosionCharged"]["ForceField"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosionCharged.FX = jj1["GrenadeVisualSettings"]["GrenadeExplosionCharged"]["FX"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosionCharged.LightCircle = jj1["GrenadeVisualSettings"]["GrenadeExplosionCharged"]["LightCircle"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosionCharged.LightGlow = jj1["GrenadeVisualSettings"]["GrenadeExplosionCharged"]["LightGlow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosionCharged.RadialBurned = jj1["GrenadeVisualSettings"]["GrenadeExplosionCharged"]["RadialBurned"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosionCharged.RadialBurned2 = jj1["GrenadeVisualSettings"]["GrenadeExplosionCharged"]["RadialBurned2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosionCharged.RadialCrack = jj1["GrenadeVisualSettings"]["GrenadeExplosionCharged"]["RadialCrack"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosionCharged.RadialIrisImpact = jj1["GrenadeVisualSettings"]["GrenadeExplosionCharged"]["RadialIrisImpact"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosionCharged.Smoke = jj1["GrenadeVisualSettings"]["GrenadeExplosionCharged"]["Smoke"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosionCharged.SnowPattern = jj1["GrenadeVisualSettings"]["GrenadeExplosionCharged"]["SnowPattern"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosionCharged.SpriteSheetFire = jj1["GrenadeVisualSettings"]["GrenadeExplosionCharged"]["SpriteSheetFire"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosionCharged.StarSpike = jj1["GrenadeVisualSettings"]["GrenadeExplosionCharged"]["StarSpike"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSettings.GrenadeVisualSettings.GrenadeExplosionFractured.ArrowDistortion = jj1["GrenadeVisualSettings"]["GrenadeExplosionFractured"]["ArrowDistortion"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosionFractured.ArrowGlow = jj1["GrenadeVisualSettings"]["GrenadeExplosionFractured"]["ArrowGlow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosionFractured.ArrowSingleParticle = jj1["GrenadeVisualSettings"]["GrenadeExplosionFractured"]["ArrowSingleParticle"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosionFractured.ArrowSmoke = jj1["GrenadeVisualSettings"]["GrenadeExplosionFractured"]["ArrowSmoke"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosionFractured.ArrowVignette = jj1["GrenadeVisualSettings"]["GrenadeExplosionFractured"]["ArrowVignette"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosionFractured.Burst = jj1["GrenadeVisualSettings"]["GrenadeExplosionFractured"]["Burst"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosionFractured.BurstPreGlow = jj1["GrenadeVisualSettings"]["GrenadeExplosionFractured"]["BurstPreGlow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosionFractured.Distortion = jj1["GrenadeVisualSettings"]["GrenadeExplosionFractured"]["Distortion"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeExplosionFractured.SnowPattern = jj1["GrenadeVisualSettings"]["GrenadeExplosionFractured"]["SnowPattern"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSettings.GrenadeVisualSettings.GrenadeFractured.OriSparkle = jj1["GrenadeVisualSettings"]["GrenadeFractured"]["OriSparkle"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeFractured.OuterGlow = jj1["GrenadeVisualSettings"]["GrenadeFractured"]["OuterGlow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeFractured.ParticleDropGlow = jj1["GrenadeVisualSettings"]["GrenadeFractured"]["ParticleDropGlow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeFractured.ParticleImpactGlow = jj1["GrenadeVisualSettings"]["GrenadeFractured"]["ParticleImpactGlow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeFractured.SharedCircleGlow = jj1["GrenadeVisualSettings"]["GrenadeFractured"]["SharedCircleGlow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeFractured.SingleSnowParticle = jj1["GrenadeVisualSettings"]["GrenadeFractured"]["SingleSnowParticle"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeFractured.Sprite = jj1["GrenadeVisualSettings"]["GrenadeFractured"]["Sprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSettings.GrenadeVisualSettings.GrenadeFractured.Trail = jj1["GrenadeVisualSettings"]["GrenadeFractured"]["Trail"].get<tem::Vector4>() * 0.003921568627451f;
}

void SeinVisualEditor::Cleanup()
{
	if (MDV::MoonSein != nullptr)
	{
		app::String* TextureName = string_new("_MainTex");
		app::String* TextureName1 = string_new("_Color");
		app::String* EmiColor = string_new("_EmissivityColor");
		app::Type* meshRendererType = GetType("UnityEngine", "MeshRenderer");
		app::Type* skinnedMeshRendererType = GetType("UnityEngine", "SkinnedMeshRenderer");
		app::Type* particleRendererType = GetType("UnityEngine", "ParticleSystemRenderer");
		app::Type* byteArrType = GetTypeFromClass((Il2CppClass*)(*app::Byte__Array__TypeInfo));
		app::GameObject* gamyobj = app::Component_1_get_gameObject((app::Component_1*)MDV::MoonSein, NULL);

		std::vector<std::string> scenePath = { "ori3D", "mirrorHolder", "rigHolder", "oriRig", "Model_GRP", "body_MDL" };
		std::vector<std::string> sceneFacePath = { "ori3D", "mirrorHolder", "rigHolder", "oriRig", "Model_GRP", "faceBody_MDL" };
		app::GameObject* seinModel = GetComponentByPath(gamyobj, scenePath);
		app::GameObject* seinFaceModel = GetComponentByPath(gamyobj, sceneFacePath);
		app::Component_1__Array* componentsRenderers = app::GameObject_GetComponentsInChildren_1(seinModel, skinnedMeshRendererType, true, NULL);
		app::Component_1__Array* componentsFaceRenderers = app::GameObject_GetComponentsInChildren_1(seinFaceModel, skinnedMeshRendererType, true, NULL);

		app::SkinnedMeshRenderer* meshRenderer = (app::SkinnedMeshRenderer*)componentsRenderers->vector[0];
		app::Material* meshMat = app::Renderer_GetMaterial((app::Renderer*)meshRenderer, NULL);

		app::SkinnedMeshRenderer* meshFaceRenderer = (app::SkinnedMeshRenderer*)componentsFaceRenderers->vector[0];
		app::Material* meshFaceMat = app::Renderer_GetMaterial((app::Renderer*)meshFaceRenderer, NULL);

		//app::Material_SetTexture(meshMat, TextureName, (app::Texture*)SeinVisualEditor::DefaultSeinVisualSettings.SeinTexture, NULL);
		//app::Material_set_mainTexture(meshMat, (app::Texture*)SeinVisualEditor::DefaultSeinVisualSettings.SeinTexture, NULL);

		//app::Material_SetTexture(meshFaceMat, TextureName, (app::Texture*)SeinVisualEditor::DefaultSeinVisualSettings.SeinFaceTexture, NULL);
		//app::Material_set_mainTexture(meshFaceMat, (app::Texture*)SeinVisualEditor::DefaultSeinVisualSettings.SeinFaceTexture, NULL);
	}
}

void SeinVisualEditor::SetSkinnedMeshRendererColorByName(app::GameObject* parent, std::string componentName, tem::Vector4 color, tem::Vector4 emissive, int setActive)
{
	app::Type* skinnedMeshRendererType = GetType("UnityEngine", "SkinnedMeshRenderer");

	if (parent != nullptr)
	{
		app::GameObject* sceneGameObject = GetComponentByName(parent, componentName);

		if (sceneGameObject != nullptr)
		{
			app::Component_1__Array* componentsSkinnedMeshRenderer = app::GameObject_GetComponentsInChildren_1(sceneGameObject, skinnedMeshRendererType, true, NULL);
			if (componentsSkinnedMeshRenderer->vector[0] != nullptr)
			{
				app::String* TextureName1 = string_new("_Color");
				app::String* EmiColor = string_new("_EmissivityColor");
				app::SkinnedMeshRenderer* meshRenderer = (app::SkinnedMeshRenderer*)componentsSkinnedMeshRenderer->vector[0];

				if (meshRenderer != nullptr)
				{
					app::Material* meshMat = app::Renderer_GetMaterial((app::Renderer*)meshRenderer, NULL);

					if (meshMat != nullptr)
					{
						app::Color defaultcolor = app::Material_GetColor(meshMat, TextureName1, NULL);
						if (SeinVisualEditor::DefaultVisualColors.find(componentName) == SeinVisualEditor::DefaultVisualColors.end())
							SeinVisualEditor::DefaultVisualColors[componentName] = defaultcolor;

						app::Material_SetColor(meshMat, TextureName1, color.ToColor(), NULL);
						app::Material_SetColor(meshMat, EmiColor, emissive.ToColor(), NULL);
					}
				}
			}
		}
	}
}

void SeinVisualEditor::SetSkinnedMeshRendererColor(app::GameObject* parent, std::string componentName, tem::Vector4 color, tem::Vector4 emissive, int setActive)
{
	app::Type* skinnedMeshRendererType = GetType("UnityEngine", "SkinnedMeshRenderer");

	if (parent != nullptr)
	{
		app::Component_1__Array* componentsSkinnedMeshRenderer = app::GameObject_GetComponentsInChildren_1(parent, skinnedMeshRendererType, true, NULL);
		if (componentsSkinnedMeshRenderer->vector[0] != nullptr)
		{
			app::String* TextureName1 = string_new("_Color");
			app::String* EmiColor = string_new("_EmissivityColor");
			app::SkinnedMeshRenderer* meshRenderer = (app::SkinnedMeshRenderer*)componentsSkinnedMeshRenderer->vector[0];

			if (meshRenderer != nullptr)
			{
				app::Material* meshMat = app::Renderer_GetMaterial((app::Renderer*)meshRenderer, NULL);

				if (meshMat != nullptr)
				{
					app::Color defaultcolor = app::Material_GetColor(meshMat, TextureName1, NULL);
					if (SeinVisualEditor::DefaultVisualColors.find(componentName) == SeinVisualEditor::DefaultVisualColors.end())
						SeinVisualEditor::DefaultVisualColors[componentName] = defaultcolor;

					app::Material_SetColor(meshMat, TextureName1, color.ToColor(), NULL);
					app::Material_SetColor(meshMat, EmiColor, emissive.ToColor(), NULL);
				}
			}
		}
	}
}


void SeinVisualEditor::SetSkinnedMeshRendererColor(app::SkinnedMeshRenderer* skinnedMesh, std::string componentName, tem::Vector4 color, tem::Vector4 emissive, int setActive)
{
	if (skinnedMesh != nullptr)
	{
		app::String* TextureName1 = string_new("_Color");
		app::String* EmiColor = string_new("_EmissivityColor");
		app::Material* meshMat = app::Renderer_GetMaterial((app::Renderer*)skinnedMesh, NULL);

		if (meshMat != nullptr)
		{
			app::Color defaultcolor = app::Material_GetColor(meshMat, TextureName1, NULL);
			if (SeinVisualEditor::DefaultVisualColors.find(componentName) == SeinVisualEditor::DefaultVisualColors.end())
				SeinVisualEditor::DefaultVisualColors[componentName] = defaultcolor;

			app::Material_SetColor(meshMat, TextureName1, color.ToColor(), NULL);
			app::Material_SetColor(meshMat, EmiColor, emissive.ToColor(), NULL);
		}
	}
}

void SeinVisualEditor::SetMeshRendererColorByName(app::GameObject* parent, std::string componentName, tem::Vector4 color, tem::Vector4 emissive, int setActive)
{
	app::Type* meshRendererType = GetType("UnityEngine", "MeshRenderer");

	if (parent != nullptr)
	{
		app::GameObject* sceneGameObject = GetComponentByNameContainsType(parent, componentName, meshRendererType);

		if (sceneGameObject != nullptr)
		{
			app::Component_1__Array* componentsMeshRenderer = app::GameObject_GetComponentsInChildren_1(sceneGameObject, meshRendererType, true, NULL);
			if (componentsMeshRenderer->vector[0] != nullptr)
			{
				app::String* TextureName1 = string_new("_Color");
				app::String* EmiColor = string_new("_EmissivityColor");
				app::MeshRenderer* meshRenderer = (app::MeshRenderer*)componentsMeshRenderer->vector[0];

				if (meshRenderer != nullptr)
				{
					app::Material* meshMat = app::Renderer_GetMaterial((app::Renderer*)meshRenderer, NULL);

					if (meshMat != nullptr)
					{
						app::Color defaultcolor = app::Material_GetColor(meshMat, TextureName1, NULL);
						if (SeinVisualEditor::DefaultVisualColors.find(componentName) == SeinVisualEditor::DefaultVisualColors.end())
							SeinVisualEditor::DefaultVisualColors[componentName] = defaultcolor;

						app::Material_SetColor(meshMat, TextureName1, color.ToColor(), NULL);
						app::Material_SetColor(meshMat, EmiColor, emissive.ToColor(), NULL);
					}
				}
			}
		}
	}
}

void SeinVisualEditor::SetMeshRendererColor(app::GameObject* parent, std::vector<std::string>& scenePath, tem::Vector4 color, int setActive)
{
	app::String* TextureName1 = string_new("_Color");
	app::String* EmiColor = string_new("_EmissivityColor");
	app::Type* meshRendererType = GetType("UnityEngine", "MeshRenderer");

	if (parent != nullptr)
	{
		app::GameObject* sceneGameObject = GetComponentByPath(parent, scenePath);
		app::Component_1__Array* componentsMeshRenderer = app::GameObject_GetComponentsInChildren_1(sceneGameObject, meshRendererType, true, NULL);
		if (componentsMeshRenderer->vector[0] != nullptr)
		{
			if (setActive > -1)
				app::GameObject_set_active(sceneGameObject, (setActive == 0 ? false : true), NULL);

			app::MeshRenderer* meshRenderer = (app::MeshRenderer*)componentsMeshRenderer->vector[0];

			if (meshRenderer != nullptr)
			{
				app::Material* meshMat = app::Renderer_GetMaterial((app::Renderer*)meshRenderer, NULL);

				if (meshMat != nullptr)
				{
					app::Color defaultcolor = app::Material_GetColor(meshMat, TextureName1, NULL);
					if (SeinVisualEditor::DefaultVisualColors.find(scenePath[scenePath.size() - 1]) == SeinVisualEditor::DefaultVisualColors.end())
						SeinVisualEditor::DefaultVisualColors[scenePath[scenePath.size() - 1]] = defaultcolor;

					app::Material_SetColor(meshMat, TextureName1, color.ToColor(), NULL);
					app::Material_SetColor(meshMat, EmiColor, color.ToColor(), NULL);
					//app::Renderer_SetMaterial((app::Renderer*)meshRenderer, meshMat, NULL);
				}
			}
		}
	}
}

void SeinVisualEditor::SetMeshRenderersColor(app::GameObject* parent, std::string componentName, tem::Vector4 color, tem::Vector4 emissive, int setActive)
{
	app::String* TextureName1 = string_new("_Color");
	app::String* EmiColor = string_new("_EmissivityColor");
	app::Type* meshRendererType = GetType("UnityEngine", "MeshRenderer");

	if (parent != nullptr)
	{
		std::vector<app::GameObject*> sceneGameObject = GetComponentsByName(parent, componentName);
		for (app::GameObject* component : sceneGameObject)
		{
			app::Component_1__Array* componentsMeshRenderer = app::GameObject_GetComponentsInChildren_1(component, meshRendererType, true, NULL);
			if (componentsMeshRenderer->vector[0] != nullptr)
			{
				if (setActive > -1)
					app::GameObject_set_active(component, (setActive == 0 ? false : true), NULL);

				app::MeshRenderer* particleRenderer = (app::MeshRenderer*)componentsMeshRenderer->vector[0];

				if (particleRenderer != nullptr)
				{
					app::Material* meshMat = app::Renderer_GetMaterial((app::Renderer*)particleRenderer, NULL);

					if (meshMat != nullptr)
					{
						app::Color defaultcolor = app::Material_GetColor(meshMat, TextureName1, NULL);
						if (SeinVisualEditor::DefaultVisualColors.find(componentName) == SeinVisualEditor::DefaultVisualColors.end())
							SeinVisualEditor::DefaultVisualColors[componentName] = defaultcolor;

						app::Material_SetColor(meshMat, TextureName1, color.ToColor(), NULL);
						app::Material_SetColor(meshMat, EmiColor, emissive.ToColor(), NULL);
						//app::Renderer_SetMaterial((app::Renderer*)particleRenderer, meshMat, NULL);
					}
				}
			}
		}
	}
}

void SeinVisualEditor::SetParticleRendererColorByName(app::GameObject* parent, std::string componentName, tem::Vector4 color, tem::Vector4 emissive, int setActive)
{
	app::Type* particleRendererType = GetType("UnityEngine", "ParticleSystemRenderer");

	if (parent != nullptr)
	{
		app::GameObject* sceneGameObject = GetComponentByName(parent, componentName);

		if (sceneGameObject != nullptr)
		{
			app::Component_1__Array* componentsParticleRenderer = app::GameObject_GetComponentsInChildren_1(sceneGameObject, particleRendererType, true, NULL);
			if (componentsParticleRenderer->vector[0] != nullptr)
			{
				app::String* TextureName1 = string_new("_Color");
				app::String* EmiColor = string_new("_EmissivityColor");
				app::ParticleSystemRenderer* particleRenderer = (app::ParticleSystemRenderer*)componentsParticleRenderer->vector[0];

				if (particleRenderer != nullptr)
				{
					app::Material* meshMat = app::Renderer_GetMaterial((app::Renderer*)particleRenderer, NULL);

					if (meshMat != nullptr)
					{
						app::Color defaultcolor = app::Material_GetColor(meshMat, TextureName1, NULL);
						if (SeinVisualEditor::DefaultVisualColors.find(componentName) == SeinVisualEditor::DefaultVisualColors.end())
							SeinVisualEditor::DefaultVisualColors[componentName] = defaultcolor;

						app::Material_SetColor(meshMat, TextureName1, color.ToColor(), NULL);
						app::Material_SetColor(meshMat, EmiColor, emissive.ToColor(), NULL);
					}
				}
			}
		}
	}
}

void SeinVisualEditor::SetParticleRendererColor(app::GameObject* parent, std::vector<std::string>& scenePath, tem::Vector4 color, int setActive)
{
	app::String* TextureName1 = string_new("_Color");
	app::String* EmiColor = string_new("_EmissivityColor");
	app::Type* particleRendererType = GetType("UnityEngine", "ParticleSystemRenderer");

	if (parent != nullptr)
	{
		app::GameObject* sceneGameObject = GetComponentByPath(parent, scenePath);
		app::Component_1__Array* componentsParticleRenderer = app::GameObject_GetComponentsInChildren_1(sceneGameObject, particleRendererType, true, NULL);
		if (componentsParticleRenderer->vector[0] != nullptr)
		{
			if (setActive > -1)
				app::GameObject_set_active(sceneGameObject, (setActive == 0 ? false : true), NULL);

			app::ParticleSystemRenderer* particleRenderer = (app::ParticleSystemRenderer*)componentsParticleRenderer->vector[0];

			if (particleRenderer != nullptr)
			{
				app::Material* meshMat = app::Renderer_GetMaterial((app::Renderer*)particleRenderer, NULL);

				if (meshMat != nullptr)
				{
					app::Color defaultcolor = app::Material_GetColor(meshMat, TextureName1, NULL);
					if (SeinVisualEditor::DefaultVisualColors.find(scenePath[scenePath.size() - 1]) == SeinVisualEditor::DefaultVisualColors.end())
						SeinVisualEditor::DefaultVisualColors[scenePath[scenePath.size() - 1]] = defaultcolor;

					app::Material_SetColor(meshMat, TextureName1, color.ToColor(), NULL);
					app::Material_SetColor(meshMat, EmiColor, color.ToColor(), NULL);
					//app::Renderer_SetMaterial((app::Renderer*)particleRenderer, meshMat, NULL);
				}
			}
		}
	}
}

void SeinVisualEditor::SetParticleRenderersColor(app::GameObject* parent, std::string componentName, tem::Vector4 color, tem::Vector4 emissive, int setActive)
{
	app::String* TextureName1 = string_new("_Color");
	app::String* EmiColor = string_new("_EmissivityColor");
	app::Type* particleRendererType = GetType("UnityEngine", "ParticleSystemRenderer");

	if (parent != nullptr)
	{
		std::vector<app::GameObject*> sceneGameObject = GetComponentsByName(parent, componentName);
		for (app::GameObject* component : sceneGameObject)
		{
			app::Component_1__Array* componentsParticleRenderer = app::GameObject_GetComponentsInChildren_1(component, particleRendererType, true, NULL);
			if (componentsParticleRenderer->vector[0] != nullptr)
			{
				if (setActive > -1)
					app::GameObject_set_active(component, (setActive == 0 ? false : true), NULL);

				app::ParticleSystemRenderer* particleRenderer = (app::ParticleSystemRenderer*)componentsParticleRenderer->vector[0];

				if (particleRenderer != nullptr)
				{
					app::Material* meshMat = app::Renderer_GetMaterial((app::Renderer*)particleRenderer, NULL);

					if (meshMat != nullptr)
					{
						app::Color defaultcolor = app::Material_GetColor(meshMat, TextureName1, NULL);
						if (SeinVisualEditor::DefaultVisualColors.find(componentName) == SeinVisualEditor::DefaultVisualColors.end())
							SeinVisualEditor::DefaultVisualColors[componentName] = defaultcolor;

						app::Material_SetColor(meshMat, TextureName1, color.ToColor(), NULL);
						app::Material_SetColor(meshMat, EmiColor, emissive.ToColor(), NULL);
						//app::Renderer_SetMaterial((app::Renderer*)particleRenderer, meshMat, NULL);
					}
				}
			}
		}
	}
}

std::unordered_map<std::string, app::UberPoolGroup*> SeinVisualEditor::GetUberGroups(std::vector<std::string> groupNames)
{
	std::unordered_map<std::string, app::UberPoolGroup*> ubergroups;
	app::UberPoolManager* uberPool = (*app::UberPoolManager__TypeInfo)->static_fields->Instance;

	if (uberPool != nullptr && ubergroups.empty() == true)
	{
		for (int i = 0; i < uberPool->fields.m_groups->fields._size; i++)
		{
			if (uberPool->fields.m_groups->fields._items->vector[i] != nullptr)
			{
				app::UberPoolGroup* pool = uberPool->fields.m_groups->fields._items->vector[i];

				if (pool != nullptr)
				{
					std::string name = sutil::convert_csstring(pool->fields.m_poolName);
					for (std::string groupName : groupNames)
					{
						if (groupName == name)
							ubergroups[name] = pool;
					}
				}
			}
		}
	}

	return ubergroups;
}

void SeinVisualEditor::SetHolidayOri()
{
	if (OriHat != nullptr)
		app::Object_1_Destroy_1((app::Object_1*)OriHat, NULL);

	app::String* debugParentName = string_new("SantaHat");
	app::Texture2D* debugTexture = (app::Texture2D*)il2cpp_object_new((Il2CppClass*)(*app::Texture2D__TypeInfo));
	app::Texture2D__ctor_3(debugTexture, 256, 256, app::TextureFormat__Enum::TextureFormat__Enum_RGBA32, false, false, NULL);
	app::Texture_set_wrapMode((app::Texture*)debugTexture, app::TextureWrapMode__Enum::TextureWrapMode__Enum_Repeat, NULL);
	app::Texture_set_filterMode((app::Texture*)debugTexture, app::FilterMode__Enum::FilterMode__Enum_Point, NULL);

	SeinVisualEditor::OriHat = app::GameObject_CreatePrimitive(app::PrimitiveType__Enum_Cube, NULL);
	app::Object_1_set_name((app::Object_1*)OriHat, debugParentName, NULL);

	app::MeshRenderer* meshRenderer = (app::MeshRenderer*)GetComponentByType(OriHat, "UnityEngine", "MeshRenderer");

	std::string textureTemp = sutil::readFile(ManagerPath + "InputImages\\OriHat.png");
	app::Type* byteArrType = GetTypeFromClass((Il2CppClass*)(*app::Byte__Array__TypeInfo));
	app::Byte__Array* byteArr = (app::Byte__Array*)app::Array_CreateInstance_1(byteArrType, textureTemp.size(), NULL);

	if (textureTemp != "")
	{
		for (int i = 0; i < textureTemp.size(); i++)
		{
			byteArr->vector[i] = textureTemp[i];
		}

		app::String* debugParentName = string_new("DebugCollider");
		app::GameObject* debugParent = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
		app::GameObject__ctor(debugParent, debugParentName, NULL);

		app::ImageConversion_LoadImage_1((app::Texture2D*)debugTexture, byteArr, NULL);
		app::Texture2D_ApplyImpl((app::Texture2D*)debugTexture, true, true, NULL);

		app::GameObject* gamyobj = app::Component_1_get_gameObject((app::Component_1*)MDV::MoonSein, NULL);
		app::Material* debugMaterial = CreateNewMaterial("Hidden/UberShader/DF362EF066C0701751D3088D28729049");// "Hidden/UberShader/4B897D76B847170D884884FBA5CEBC13");// CreateNewMaterial("Hidden/UberShader/4B897D76B847170D884884FBA5CEBC13");// "Hidden/UberShader/4B897D76B847170D884884FBA5CEBC13");// "Hidden/UberShader/E48C37CFA39B1500F0D8A6A5D0B46307");
		std::vector<std::string> scenePath = { "ori3D", "mirrorHolder", "rigHolder", "oriRig", "Model_GRP", "body_MDL" };
		app::GameObject* oriModel = GetComponentByPath(gamyobj, scenePath);
		app::Type* skinnedMeshRendererType = GetType("UnityEngine", "SkinnedMeshRenderer");
		app::Component_1__Array* componentsRenderers = app::GameObject_GetComponentsInChildren_1(oriModel, skinnedMeshRendererType, true, NULL);
		//app::Material* oriMat = app::Renderer_GetMaterial((app::Renderer*)componentsRenderers->vector[0], NULL);
		//app::Material_CreateWithMaterial(debugMaterial, oriMat, NULL);

		app::BoxCollider* boxCollider = (app::BoxCollider*)GetComponentByType(OriHat, "UnityEngine", "BoxCollider");
		app::Object_1_Destroy_1((app::Object_1*)boxCollider, NULL);

		app::String* TextureName = string_new("_MainTex");
		app::String* TextureName1 = string_new("_Color");
		app::String* EmiColor = string_new("_EmissivityColor");
		app::String* TextureMultiplyColor = string_new("_MultiplyLayerColor");
		app::String* TextureMultiply = string_new("_MultiplyLayerTexture");
		app::String* UNITY_UI_ALPHACLIPName = string_new("UNITY_UI_ALPHACLIP");
		app::String* UNITY_UI_CLIP_RECTName = string_new("UNITY_UI_CLIP_RECT");
		//app::Material_EnableKeyword_1(debugMaterial, UNITY_UI_ALPHACLIPName, NULL);
		//app::Material_EnableKeyword_1(debugMaterial, UNITY_UI_CLIP_RECTName, NULL);
		int32_t reflectionInt = app::Shader_PropertyToID(string_new("_ReflectionAmount"), NULL);

		app::Material_SetTexture(debugMaterial, TextureName, (app::Texture*)debugTexture, NULL);
		app::Material_SetTexture(debugMaterial, TextureMultiply, (app::Texture*)debugTexture, NULL);
		app::Material_set_mainTexture(debugMaterial, (app::Texture*)debugTexture, NULL);
		app::Material_SetColor(debugMaterial, TextureName1, tem::Vector4(0.0f, 0.0f, 0.0f, 1.0f).ToColor(), NULL);
		app::Material_SetColor(debugMaterial, EmiColor, tem::Vector4(0.0f, 0.0f, 0.0f, 1.0f).ToColor(), NULL);
		app::Material_SetColor(debugMaterial, TextureMultiplyColor, tem::Vector4(0.009f, 0.009f, 0.009f, 1.0f).ToColor(), NULL);
		app::Material_SetFloat(debugMaterial, reflectionInt, 0.0f, NULL);

		app::Renderer_SetMaterial((app::Renderer*)meshRenderer, debugMaterial, NULL);
		app::Renderer_set_sortingOrder((app::Renderer*)meshRenderer, 26810, NULL);
		app::Renderer_set_renderingLayerMask((app::Renderer*)meshRenderer, 263200, NULL); //xxx0 nothing, xxx1 transparent, xxx2 full color, xxx3 full color shades everything inside
		app::Material_set_renderQueue(debugMaterial, 2000, NULL);
		app::Renderer_set_moonOffsetZ((app::Renderer*)meshRenderer, 0.00002f, NULL);

		app::GameObject* oriHeadSkeleton = GetComponentByName(gamyobj, "jaw_SKN");
		TransformSetParent(OriHat, debugParent);
		TransformSetParent(debugParent, oriHeadSkeleton);
		TransformSetLocalPosition(debugParent, tem::Vector3(0, 0, 0));
		TransformSetLocalPosition(OriHat, tem::Vector3(0.03f, 0.5f, -0.06f));
		TransformSetEulerAngles(OriHat, tem::Vector3(180, 220, 2.5));
		TransformSetScale(OriHat, tem::Vector3(1.0f, 1.0f, 0.0f));
		MDV::SelectedObject = OriHat;
	}
}