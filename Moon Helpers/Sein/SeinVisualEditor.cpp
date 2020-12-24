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
VisualSettings SeinVisualEditor::DefaultVisualSetting;
VisualSettings SeinVisualEditor::VisualSetting;
std::unordered_map<std::string, tem::Vector4> SeinVisualEditor::DefaultVisualColors = std::unordered_map<std::string, tem::Vector4>();
app::GameObject* SeinVisualEditor::OriHat = nullptr;
bool SeinVisualEditor::ManagerLoaded = false;

void SeinVisualEditor::SetAllVisuals()
{
	if (SeinVisualEditor::VisualSettingsUpdated.HasUpdatedOri == false)
		SeinVisualEditor::VisualSetting.OriVisualSetting.SetOriVisuals(SeinVisualEditor::VisualSetting.OriVisualSetting);

	if (SeinVisualEditor::VisualSettingsUpdated.HasUpdatedTorch == false)
		SeinVisualEditor::VisualSetting.TorchVisualSetting.SetTorchVisuals(SeinVisualEditor::VisualSetting.TorchVisualSetting);

	if (SeinVisualEditor::VisualSettingsUpdated.HasUpdatedGlide == false)
		SeinVisualEditor::VisualSetting.GlideVisualSetting.SetGlideVisuals(SeinVisualEditor::VisualSetting.GlideVisualSetting);

	if (SeinVisualEditor::VisualSettingsUpdated.HasUpdatedBow == false)
		SeinVisualEditor::VisualSetting.BowVisualSetting.SetBowVisuals(SeinVisualEditor::VisualSetting.BowVisualSetting);

	if (SeinVisualEditor::VisualSettingsUpdated.HasUpdatedGoldenSein == false)
		SeinVisualEditor::VisualSetting.GoldenSeinVisualSetting.SetGoldenSeinVisuals(SeinVisualEditor::VisualSetting.GoldenSeinVisualSetting);

	if (SeinVisualEditor::VisualSettingsUpdated.HasUpdatedHammer == false)
		SeinVisualEditor::VisualSetting.HammerVisualSetting.SetHammerVisuals(SeinVisualEditor::VisualSetting.HammerVisualSetting);

	if (SeinVisualEditor::VisualSettingsUpdated.HasUpdatedSword == false)
		SeinVisualEditor::VisualSetting.SwordVisualSetting.SetSwordVisuals(SeinVisualEditor::VisualSetting.SwordVisualSetting);

	if (SeinVisualEditor::VisualSettingsUpdated.HasUpdatedGrenade == false)
		SeinVisualEditor::VisualSetting.GrenadeVisualSetting.SetGrenadeVisuals(SeinVisualEditor::VisualSetting.GrenadeVisualSetting);

	/*std::string lines = "";
	for (auto line : SeinVisualEditor::DefaultVisualColors)
	{
		lines += line.first + ": " + line.second.ToString() + "\r\n";
	}
	sutil::Write(ManagerPath + "\\defaultValues.txt", lines);*/
}

void SeinVisualEditor::ResetAllVisuals()
{
	VisualSetting = VisualSettings();
	VisualSetting.OriVisualSetting.TexturePath = ManagerPath + "\\inputImages\\Ori_Diff_Cinematics_02.png";
	SeinVisualEditor::SetAllVisuals();
}

void SeinVisualEditor::LoadJsonFile(std::string& path)
{
	std::string contents = sutil::ReadFile(path);
	nlohmann::json j = nlohmann::json::parse(contents);
	nlohmann::json jj = j.at("VisualSettings");
	nlohmann::json jj1 = j.at("ActiveVisualSetting");

	VisualSetting.OriVisualSetting.HideGlow = jj1["OriVisualSettings"]["HideGlow"].get<bool>();
	VisualSetting.OriVisualSetting.Ori = jj1["OriVisualSettings"]["Ori"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.OriVisualSetting.OriGlow = jj1["OriVisualSettings"]["OriGlow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.OriVisualSetting.OriTrail = jj1["OriVisualSettings"]["OriTrail"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.OriVisualSetting.TexturePath = jj1["OriVisualSettings"]["TexturePath"].get<std::string>();

	VisualSetting.OriVisualSetting.HatVisualSettings.Hat= jj1["OriVisualSettings"]["HatVisualSettings"]["Hat"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.OriVisualSetting.HatVisualSettings.HatEmissive = jj1["OriVisualSettings"]["HatVisualSettings"]["HatEmissive"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.OriVisualSetting.HatVisualSettings.TexturePath = jj1["OriVisualSettings"]["HatVisualSettings"]["TexturePath"].get<std::string>();

	VisualSetting.GoldenSeinVisualSetting.SeinBodyColor = jj1["GoldenSeinVisualSettings"]["SeinBody"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GoldenSeinVisualSetting.SeinBodyEmissiveColor = jj1["GoldenSeinVisualSettings"]["SeinBodyEmissive"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GoldenSeinVisualSetting.SeinParticleColor = jj1["GoldenSeinVisualSettings"]["SeinParticle"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GoldenSeinVisualSetting.SeinRadialLightColor = jj1["GoldenSeinVisualSettings"]["SeinRadialLight"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GoldenSeinVisualSetting.SeinTrailColor = jj1["GoldenSeinVisualSettings"]["SeinTrail"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GoldenSeinVisualSetting.SeinTrailMeshColor = jj1["GoldenSeinVisualSettings"]["SeinTrailMesh"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.SwordVisualSetting.SwordColor = jj1["SwordVisualSettings"]["Sword"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordEmissiveColor = jj1["SwordVisualSettings"]["SwordEmissive"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordHitEffectColor = jj1["SwordVisualSettings"]["SwordHitEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordHitEffectEmissiveColor = jj1["SwordVisualSettings"]["SwordHitEffectEmissive"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.SwordVisualSetting.SwordAttackAirPoke.BlowingSand = jj1["SwordVisualSettings"]["SwordAttackAirPoke"]["BlowingSand"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordAttackAirPoke.Glow = jj1["SwordVisualSettings"]["SwordAttackAirPoke"]["Glow"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.SwordVisualSetting.SwordAttackDownAir.EnergyEffect = jj1["SwordVisualSettings"]["SwordAttackDownAir"]["EnergyEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordAttackDownAir.FireSprite = jj1["SwordVisualSettings"]["SwordAttackDownAir"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordAttackDownAir.SnowPattern = jj1["SwordVisualSettings"]["SwordAttackDownAir"]["SnowPattern"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordAttackDownAir.VignetteMaskC = jj1["SwordVisualSettings"]["SwordAttackDownAir"]["VignetteMaskC"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.SwordVisualSetting.SwordAttackGroundA.EnergyEffect = jj1["SwordVisualSettings"]["SwordAttackGroundA"]["EnergyEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordAttackGroundA.FireSprite = jj1["SwordVisualSettings"]["SwordAttackGroundA"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordAttackGroundA.SnowPattern = jj1["SwordVisualSettings"]["SwordAttackGroundA"]["SnowPattern"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordAttackGroundA.VignetteMaskC = jj1["SwordVisualSettings"]["SwordAttackGroundA"]["VignetteMaskC"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.SwordVisualSetting.SwordAttackGroundB.EnergyEffect = jj1["SwordVisualSettings"]["SwordAttackGroundB"]["EnergyEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordAttackGroundB.FireSprite = jj1["SwordVisualSettings"]["SwordAttackGroundB"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordAttackGroundB.SnowPattern = jj1["SwordVisualSettings"]["SwordAttackGroundB"]["SnowPattern"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordAttackGroundB.VignetteMaskC = jj1["SwordVisualSettings"]["SwordAttackGroundB"]["VignetteMaskC"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.SwordVisualSetting.SwordAttackGroundC.BlowingSand = jj1["SwordVisualSettings"]["SwordAttackGroundC"]["BlowingSand"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordAttackGroundC.SnowPattern = jj1["SwordVisualSettings"]["SwordAttackGroundC"]["SnowPattern"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordAttackGroundC.SnowPattern2 = jj1["SwordVisualSettings"]["SwordAttackGroundC"]["SnowPattern2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordAttackGroundC.VignetteMaskC = jj1["SwordVisualSettings"]["SwordAttackGroundC"]["VignetteMaskC"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.SwordVisualSetting.SwordAttackUp.EnergyEffect = jj1["SwordVisualSettings"]["SwordAttackUp"]["EnergyEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordAttackUp.FireSprite = jj1["SwordVisualSettings"]["SwordAttackUp"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordAttackUp.SnowPattern = jj1["SwordVisualSettings"]["SwordAttackUp"]["SnowPattern"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordAttackUp.VignetteMaskC = jj1["SwordVisualSettings"]["SwordAttackUp"]["VignetteMaskC"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.SwordVisualSetting.SwordBlock.AcidParticles = jj1["SwordVisualSettings"]["SwordBlock"]["AcidParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordBlock.CharacterGlow = jj1["SwordVisualSettings"]["SwordBlock"]["CharacterGlow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordBlock.Circle = jj1["SwordVisualSettings"]["SwordBlock"]["Circle"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordBlock.CircleGlowC = jj1["SwordVisualSettings"]["SwordBlock"]["CircleGlowC"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordBlock.Distortion = jj1["SwordVisualSettings"]["SwordBlock"]["Distortion"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordBlock.FxBox = jj1["SwordVisualSettings"]["SwordBlock"]["FxBox"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordBlock.Glow = jj1["SwordVisualSettings"]["SwordBlock"]["Glow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordBlock.LavaFountainA = jj1["SwordVisualSettings"]["SwordBlock"]["LavaFountainA"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordBlock.NoiseCaustic = jj1["SwordVisualSettings"]["SwordBlock"]["NoiseCaustic"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordBlock.SingleSnowParticleA = jj1["SwordVisualSettings"]["SwordBlock"]["SingleSnowParticleA"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordBlock.SnowPattern = jj1["SwordVisualSettings"]["SwordBlock"]["SnowPattern"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordBlock.SnowPattern2 = jj1["SwordVisualSettings"]["SwordBlock"]["SnowPattern2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordBlock.StarSpike = jj1["SwordVisualSettings"]["SwordBlock"]["StarSpike"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.SwordVisualSetting.SwordDamageBlue.BurningCoreParticles = jj1["SwordVisualSettings"]["SwordDamageBlue"]["BurningCoreParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordDamageBlue.BurnMarks = jj1["SwordVisualSettings"]["SwordDamageBlue"]["BurnMarks"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordDamageBlue.DebrisParticles = jj1["SwordVisualSettings"]["SwordDamageBlue"]["DebrisParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordDamageBlue.Distortion = jj1["SwordVisualSettings"]["SwordDamageBlue"]["Distortion"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordDamageBlue.ImpactCenter = jj1["SwordVisualSettings"]["SwordDamageBlue"]["ImpactCenter"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordDamageBlue.ImpactSparklesA = jj1["SwordVisualSettings"]["SwordDamageBlue"]["ImpactSparklesA"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordDamageBlue.SmokeParticles = jj1["SwordVisualSettings"]["SwordDamageBlue"]["SmokeParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordDamageBlue.SparkStartParticles = jj1["SwordVisualSettings"]["SwordDamageBlue"]["SparkStartParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordDamageBlue.VignetteMaskC = jj1["SwordVisualSettings"]["SwordDamageBlue"]["VignetteMaskC"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.SwordVisualSetting.SwordHit.DebrisParticles = jj1["SwordVisualSettings"]["SwordHit"]["DebrisParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordHit.DebrisParticlesFallBig = jj1["SwordVisualSettings"]["SwordHit"]["DebrisParticlesFallBig"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordHit.DistortionNew = jj1["SwordVisualSettings"]["SwordHit"]["DistortionNew"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordHit.DropGlowB = jj1["SwordVisualSettings"]["SwordHit"]["DropGlowB"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordHit.FxBox = jj1["SwordVisualSettings"]["SwordHit"]["FxBox"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordHit.GlowUnmask = jj1["SwordVisualSettings"]["SwordHit"]["GlowUnmask"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordHit.LensCrossStart = jj1["SwordVisualSettings"]["SwordHit"]["LensCrossStart"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordHit.LensFlare20b = jj1["SwordVisualSettings"]["SwordHit"]["LensFlare20b"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordHit.LensFlare9 = jj1["SwordVisualSettings"]["SwordHit"]["LensFlare9"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordHit.LensRadialSpike = jj1["SwordVisualSettings"]["SwordHit"]["LensRadialSpike"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordHit.LightCircleShape = jj1["SwordVisualSettings"]["SwordHit"]["LightCircleShape"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordHit.LightGlow = jj1["SwordVisualSettings"]["SwordHit"]["LightGlow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordHit.RadialBurned2 = jj1["SwordVisualSettings"]["SwordHit"]["RadialBurned2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordHit.RadialLightRays = jj1["SwordVisualSettings"]["SwordHit"]["RadialLightRays"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordHit.RadialMaskB = jj1["SwordVisualSettings"]["SwordHit"]["RadialMaskB"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordHit.SparksLong = jj1["SwordVisualSettings"]["SwordHit"]["SparksLong"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordHit.SplashEdge = jj1["SwordVisualSettings"]["SwordHit"]["SplashEdge"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordHit.SplashEdge2 = jj1["SwordVisualSettings"]["SwordHit"]["SplashEdge2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordHit.StarSpike2 = jj1["SwordVisualSettings"]["SwordHit"]["StarSpike2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.SwordVisualSetting.SwordHit.VignetteMaskC = jj1["SwordVisualSettings"]["SwordHit"]["VignetteMaskC"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.HammerVisualSetting.HammerColor = jj1["HammerVisualSettings"]["Hammer"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerEmissiveColor = jj1["HammerVisualSettings"]["HammerEmissive"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerHitEffectColor = jj1["HammerVisualSettings"]["HammerHitEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerHitEffectEmissiveColor = jj1["HammerVisualSettings"]["HammerHitEffectEmissive"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.HammerVisualSetting.HammerAttackAir1.EnergyEffect = jj1["HammerVisualSettings"]["HammerAttackAir1"]["EnergyEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackAir1.FireSprite = jj1["HammerVisualSettings"]["HammerAttackAir1"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackAir1.LinearGradientMask = jj1["HammerVisualSettings"]["HammerAttackAir1"]["LinearGradientMask"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackAir1.SpriteSnowPettern2 = jj1["HammerVisualSettings"]["HammerAttackAir1"]["SpriteSnowPettern2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackAir1.VignetteMaskC = jj1["HammerVisualSettings"]["HammerAttackAir1"]["VignetteMaskC"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.HammerVisualSetting.HammerAttackAir2.EnergyEffect = jj1["HammerVisualSettings"]["HammerAttackAir2"]["EnergyEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackAir2.FireSprite = jj1["HammerVisualSettings"]["HammerAttackAir2"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackAir2.LinearGradientMask = jj1["HammerVisualSettings"]["HammerAttackAir2"]["LinearGradientMask"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackAir2.SpriteSnowPettern2 = jj1["HammerVisualSettings"]["HammerAttackAir2"]["SpriteSnowPettern2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackAir2.VignetteMaskC = jj1["HammerVisualSettings"]["HammerAttackAir2"]["VignetteMaskC"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.HammerVisualSetting.HammerAttackAir3.EnergyEffect = jj1["HammerVisualSettings"]["HammerAttackAir3"]["EnergyEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackAir3.FireSprite = jj1["HammerVisualSettings"]["HammerAttackAir3"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackAir3.LinearGradientMask = jj1["HammerVisualSettings"]["HammerAttackAir3"]["LinearGradientMask"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackAir3.SpriteSnowPettern2 = jj1["HammerVisualSettings"]["HammerAttackAir3"]["SpriteSnowPettern2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackAir3.VignetteMaskC = jj1["HammerVisualSettings"]["HammerAttackAir3"]["VignetteMaskC"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.HammerVisualSetting.HammerAttackAirUpSwipe.EnergyEffect = jj1["HammerVisualSettings"]["HammerAttackAirUpSwipe"]["EnergyEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackAirUpSwipe.FireSprite = jj1["HammerVisualSettings"]["HammerAttackAirUpSwipe"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackAirUpSwipe.LinearGradientMask = jj1["HammerVisualSettings"]["HammerAttackAirUpSwipe"]["LinearGradientMask"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackAirUpSwipe.SpriteSnowPettern2 = jj1["HammerVisualSettings"]["HammerAttackAirUpSwipe"]["SpriteSnowPettern2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackAirUpSwipe.VignetteMaskC = jj1["HammerVisualSettings"]["HammerAttackAirUpSwipe"]["VignetteMaskC"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.HammerVisualSetting.HammerAttackGround.EnergyEffect = jj1["HammerVisualSettings"]["HammerAttackGround1"]["EnergyEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackGround.FireSprite = jj1["HammerVisualSettings"]["HammerAttackGround1"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackGround.LinearGradientMask = jj1["HammerVisualSettings"]["HammerAttackGround1"]["LinearGradientMask"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackGround.SpriteSnowPettern2 = jj1["HammerVisualSettings"]["HammerAttackGround1"]["SpriteSnowPettern2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackGround.VignetteMaskC = jj1["HammerVisualSettings"]["HammerAttackGround1"]["VignetteMaskC"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.HammerVisualSetting.HammerAttackGround2.EnergyEffect = jj1["HammerVisualSettings"]["HammerAttackGround2"]["EnergyEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackGround2.FireSprite = jj1["HammerVisualSettings"]["HammerAttackGround2"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackGround2.LinearGradientMask = jj1["HammerVisualSettings"]["HammerAttackGround2"]["LinearGradientMask"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackGround2.SpriteSnowPettern2 = jj1["HammerVisualSettings"]["HammerAttackGround2"]["SpriteSnowPettern2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackGround2.VignetteMaskC = jj1["HammerVisualSettings"]["HammerAttackGround2"]["VignetteMaskC"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.HammerVisualSetting.HammerAttackGroundDown.EnergyEffect = jj1["HammerVisualSettings"]["HammerAttackGroundDown"]["EnergyEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackGroundDown.FireSprite = jj1["HammerVisualSettings"]["HammerAttackGroundDown"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackGroundDown.LinearGradientMask = jj1["HammerVisualSettings"]["HammerAttackGroundDown"]["LinearGradientMask"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackGroundDown.SpriteSnowPettern2 = jj1["HammerVisualSettings"]["HammerAttackGroundDown"]["SpriteSnowPettern2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackGroundDown.VignetteMaskC = jj1["HammerVisualSettings"]["HammerAttackGroundDown"]["VignetteMaskC"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.HammerVisualSetting.HammerAttackGroundUpSwipe.EnergyEffect = jj1["HammerVisualSettings"]["HammerAttackGroundUpSwipe"]["EnergyEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackGroundUpSwipe.FireSprite = jj1["HammerVisualSettings"]["HammerAttackGroundUpSwipe"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackGroundUpSwipe.LinearGradientMask = jj1["HammerVisualSettings"]["HammerAttackGroundUpSwipe"]["LinearGradientMask"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackGroundUpSwipe.SpriteSnowPettern2 = jj1["HammerVisualSettings"]["HammerAttackGroundUpSwipe"]["SpriteSnowPettern2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackGroundUpSwipe.VignetteMaskC = jj1["HammerVisualSettings"]["HammerAttackGroundUpSwipe"]["VignetteMaskC"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.HammerVisualSetting.HammerAttackStomp.GiftLeafTransformationLightRing = jj1["HammerVisualSettings"]["HammerAttackStomp"]["GiftLeafTransformationLightRing"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackStomp.Glow = jj1["HammerVisualSettings"]["HammerAttackStomp"]["Glow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackStomp.Glow1 = jj1["HammerVisualSettings"]["HammerAttackStomp"]["Glow1"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackStomp.SingleSnowParticleA = jj1["HammerVisualSettings"]["HammerAttackStomp"]["SingleSnowParticleA"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackStomp.Smoke = jj1["HammerVisualSettings"]["HammerAttackStomp"]["Smoke"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerAttackStomp.DebrisParticles = jj1["HammerVisualSettings"]["HammerAttackStomp"]["DebrisParticles"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.HammerVisualSetting.HammerShockwave.AtlantisRockFarBackgroundAg = jj1["HammerVisualSettings"]["HammerShockwave"]["AtlantisRockFarBackgroundAg"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerShockwave.BulletGlow = jj1["HammerVisualSettings"]["HammerShockwave"]["BulletGlow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerShockwave.FxBox = jj1["HammerVisualSettings"]["HammerShockwave"]["FxBox"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerShockwave.RadialMaskB = jj1["HammerVisualSettings"]["HammerShockwave"]["RadialMaskB"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerShockwave.SharedSmokeA = jj1["HammerVisualSettings"]["HammerShockwave"]["SharedSmokeA"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerShockwave.Sparks = jj1["HammerVisualSettings"]["HammerShockwave"]["Sparks"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerShockwave.SplashEdge2localOrient = jj1["HammerVisualSettings"]["HammerShockwave"]["SplashEdge2localOrient"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerShockwave.SpritesheetSpikes = jj1["HammerVisualSettings"]["HammerShockwave"]["SpritesheetSpikes"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.HammerVisualSetting.HammerBlock.AcidParticles = jj1["HammerVisualSettings"]["HammerBlock"]["AcidParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerBlock.CharacterGlow = jj1["HammerVisualSettings"]["HammerBlock"]["CharacterGlow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerBlock.Circle = jj1["HammerVisualSettings"]["HammerBlock"]["Circle"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerBlock.Glow = jj1["HammerVisualSettings"]["HammerBlock"]["Glow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerBlock.LavaFountainA = jj1["HammerVisualSettings"]["HammerBlock"]["LavaFountainA"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerBlock.SingleSnowParticleA = jj1["HammerVisualSettings"]["HammerBlock"]["SingleSnowParticleA"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.HammerVisualSetting.HammerHit.DistortionNew = jj1["HammerVisualSettings"]["HammerHit"]["DistortionNew"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerHit.FxBox = jj1["HammerVisualSettings"]["HammerHit"]["FxBox"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerHit.Glow = jj1["HammerVisualSettings"]["HammerHit"]["Glow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerHit.DebrisParticles = jj1["HammerVisualSettings"]["HammerHit"]["DebrisParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerHit.DebrisParticles1 = jj1["HammerVisualSettings"]["HammerHit"]["DebrisParticles1"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerHit.DebrisParticles2 = jj1["HammerVisualSettings"]["HammerHit"]["DebrisParticles2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerHit.DebrisParticles3 = jj1["HammerVisualSettings"]["HammerHit"]["DebrisParticles3"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerHit.DebrisParticlesFallBig = jj1["HammerVisualSettings"]["HammerHit"]["DebrisParticlesFallBig"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerHit.KuroNestEggCrackD = jj1["HammerVisualSettings"]["HammerHit"]["KuroNestEggCrackD"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerHit.LensFlare20b = jj1["HammerVisualSettings"]["HammerHit"]["LensFlare20b"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerHit.LensFlare3 = jj1["HammerVisualSettings"]["HammerHit"]["LensFlare3"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerHit.LensFlare9 = jj1["HammerVisualSettings"]["HammerHit"]["LensFlare9"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerHit.LensRadialSpike = jj1["HammerVisualSettings"]["HammerHit"]["LensRadialSpike"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerHit.RadialBurned2 = jj1["HammerVisualSettings"]["HammerHit"]["RadialBurned2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerHit.RadialIrisImpact = jj1["HammerVisualSettings"]["HammerHit"]["RadialIrisImpact"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerHit.RadialLightRays = jj1["HammerVisualSettings"]["HammerHit"]["RadialLightRays"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerHit.RadialMaskB = jj1["HammerVisualSettings"]["HammerHit"]["RadialMaskB"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerHit.SpikeHitLarge1 = jj1["HammerVisualSettings"]["HammerHit"]["SpikeHitLarge1"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerHit.SpikeHitLarge2 = jj1["HammerVisualSettings"]["HammerHit"]["SpikeHitLarge2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerHit.ParticleShape = jj1["HammerVisualSettings"]["HammerHit"]["ParticleShape"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerHit.StarSpike2 = jj1["HammerVisualSettings"]["HammerHit"]["StarSpike2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerHit.VignetteMaskC = jj1["HammerVisualSettings"]["HammerHit"]["VignetteMaskC"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.HammerVisualSetting.HammerStompPreparation.FireSprite3Flip = jj1["HammerVisualSettings"]["HammerStompPreparation"]["FireSprite3Flip"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.HammerVisualSetting.HammerStompPreparation.VignetteMaskC = jj1["HammerVisualSettings"]["HammerStompPreparation"]["VignetteMaskC"].get<tem::Vector4>() * 0.003921568627451f;

	nlohmann::json jBowVisuals = jj1.at("BowVisualSettings");
	VisualSetting.BowVisualSetting.BowShaftColor = jBowVisuals["BowShaft"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.BowVisualSetting.BowShaftEmissiveColor = jBowVisuals["BowShaftEmissive"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.BowVisualSetting.BowStringColor = jBowVisuals["BowString"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.BowVisualSetting.BowStringEmissiveColor = jBowVisuals["BowStringEmissive"].get<tem::Vector4>() * 0.003921568627451f;

	nlohmann::json jArrowVisuals = jBowVisuals.at("ArrowVisualSettings");
	VisualSetting.BowVisualSetting.ArrowVisualSettings.ArrowEffectColor = jArrowVisuals["ArrowEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.BowVisualSetting.ArrowVisualSettings.ArrowEffectEmissiveColor = jArrowVisuals["ArrowEffectEmissive"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.BowVisualSetting.ArrowVisualSettings.ArrowSpearColor = jArrowVisuals["ArrowSpear"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.BowVisualSetting.ArrowVisualSettings.ArrowSpearEmissiveColor = jArrowVisuals["ArrowSpearEmissive"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.BowVisualSetting.ArrowVisualSettings.TipImpactColor = jArrowVisuals["TipImpact"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.BowVisualSetting.ArrowVisualSettings.TipImpactEmissiveColor = jArrowVisuals["TipImpactEmissive"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.BowVisualSetting.ArrowVisualSettings.TipParticleColor = jArrowVisuals["TipParticle"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.BowVisualSetting.ArrowVisualSettings.TipParticleEmissiveColor = jArrowVisuals["TipParticleEmissive"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.BowVisualSetting.ArrowVisualSettings.ArrowTrail = jArrowVisuals["ArrowTrail"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.BowVisualSetting.ArrowVisualSettings.ArrowTrailEmissive = jArrowVisuals["ArrowTrailEmissive"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.BowVisualSetting.ArrowHitVisualSettings.DistortionNew = jj1["BowVisualSettings"]["ArrowHitVisualSettings"]["DistortionNew"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.BowVisualSetting.ArrowHitVisualSettings.FxBox = jj1["BowVisualSettings"]["ArrowHitVisualSettings"]["FxBox"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.BowVisualSetting.ArrowHitVisualSettings.BloodSplat = jj1["BowVisualSettings"]["ArrowHitVisualSettings"]["BloodSplat"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.BowVisualSetting.ArrowHitVisualSettings.DebrisParticles = jj1["BowVisualSettings"]["ArrowHitVisualSettings"]["DebrisParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.BowVisualSetting.ArrowHitVisualSettings.DebrisParticlesFallBig = jj1["BowVisualSettings"]["ArrowHitVisualSettings"]["DebrisParticlesFallBig"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.BowVisualSetting.ArrowHitVisualSettings.GlowUnmask = jj1["BowVisualSettings"]["ArrowHitVisualSettings"]["GlowUnmask"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.BowVisualSetting.ArrowHitVisualSettings.VignetteMaskC = jj1["BowVisualSettings"]["ArrowHitVisualSettings"]["VignetteMaskC"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.BowVisualSetting.ArrowHitVisualSettings.BlowingUpForceField = jj1["BowVisualSettings"]["ArrowHitVisualSettings"]["BlowingUpForceField"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.BowVisualSetting.ArrowHitVisualSettings.LensFlare20b = jj1["BowVisualSettings"]["ArrowHitVisualSettings"]["LensFlare20b"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.BowVisualSetting.ArrowHitVisualSettings.LensFlare9 = jj1["BowVisualSettings"]["ArrowHitVisualSettings"]["LensFlare9"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.BowVisualSetting.ArrowHitVisualSettings.RadialBurned = jj1["BowVisualSettings"]["ArrowHitVisualSettings"]["RadialBurned"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.BowVisualSetting.ArrowHitVisualSettings.RadialBurned2 = jj1["BowVisualSettings"]["ArrowHitVisualSettings"]["RadialBurned2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.BowVisualSetting.ArrowHitVisualSettings.RadialIrisImpact = jj1["BowVisualSettings"]["ArrowHitVisualSettings"]["RadialIrisImpact"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.BowVisualSetting.ArrowHitVisualSettings.StarSpike2 = jj1["BowVisualSettings"]["ArrowHitVisualSettings"]["StarSpike2"].get<tem::Vector4>() * 0.003921568627451f;

	nlohmann::json jGlideVisuals = jj1.at("GlideVisualSettings");
	VisualSetting.GlideVisualSetting.FeatherColor = jGlideVisuals["Feather"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GlideVisualSetting.FeatherEmissiveColor = jGlideVisuals["FeatherEmissive"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GlideVisualSetting.FeatherflapColor = jGlideVisuals["Featherflap"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GlideVisualSetting.FeatherflapEmissiveColor = jGlideVisuals["FeatherflapEmissive"].get<tem::Vector4>() * 0.003921568627451f;
	//VisualSetting.GlideVisualSetting.FeatherUpwindColor = jGlideVisuals["FeatherUpwind"].get<tem::Vector4>();

	nlohmann::json jTorchVisuals = jj1.at("TorchVisualSettings");
	VisualSetting.TorchVisualSetting.HideGlow = jTorchVisuals["HideGlow"].get<bool>();
	VisualSetting.TorchVisualSetting.TorchColor = jTorchVisuals["Torch"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchFloatingSparkColor = jTorchVisuals["TorchFloatingSpark"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchLightEffect = jTorchVisuals["TorchLightEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchRunningColor = jTorchVisuals["TorchRunning"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchSpark = jTorchVisuals["TorchSpark"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchTrailMeshColor = jTorchVisuals["TorchTrailMesh"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchTrailMeshEnable = jTorchVisuals["TorchTrailMeshEnable"].get<bool>();

	TorchAttack airAttack1;
	VisualSetting.TorchVisualSetting.TorchAirAttacks.push_back(airAttack1);
	TorchAttack airAttack2;
	VisualSetting.TorchVisualSetting.TorchAirAttacks.push_back(airAttack2);
	TorchAttack airAttack3;
	VisualSetting.TorchVisualSetting.TorchAirAttacks.push_back(airAttack3);

	VisualSetting.TorchVisualSetting.TorchAirAttacks[0].FireSprite = jTorchVisuals["TorchAirAttacks1"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchAirAttacks[0].TrailZigZag = jTorchVisuals["TorchAirAttacks1"]["TrailZigZag"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchAirAttacks[1].FireSprite = jTorchVisuals["TorchAirAttacks2"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchAirAttacks[1].TrailZigZag = jTorchVisuals["TorchAirAttacks2"]["TrailZigZag"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchAirAttacks[2].FireSprite = jTorchVisuals["TorchAirAttacks3"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchAirAttacks[2].TrailZigZag = jTorchVisuals["TorchAirAttacks3"]["TrailZigZag"].get<tem::Vector4>() * 0.003921568627451f;

	TorchAttack groundAttack1;
	VisualSetting.TorchVisualSetting.TorchGroundAttacks.push_back(groundAttack1);
	TorchAttack groundAttack2;
	VisualSetting.TorchVisualSetting.TorchGroundAttacks.push_back(groundAttack2);
	TorchAttack groundAttack3;
	VisualSetting.TorchVisualSetting.TorchGroundAttacks.push_back(groundAttack3);

	VisualSetting.TorchVisualSetting.TorchGroundAttacks[0].FireSprite = jTorchVisuals["TorchGroundAttacks1"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchGroundAttacks[0].TrailZigZag = jTorchVisuals["TorchGroundAttacks1"]["TrailZigZag"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchGroundAttacks[1].FireSprite = jTorchVisuals["TorchGroundAttacks2"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchGroundAttacks[1].TrailZigZag = jTorchVisuals["TorchGroundAttacks2"]["TrailZigZag"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchGroundAttacks[2].FireSprite = jTorchVisuals["TorchGroundAttacks3"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchGroundAttacks[2].TrailZigZag = jTorchVisuals["TorchGroundAttacks3"]["TrailZigZag"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.TorchVisualSetting.TorchBreak.AcidParticles = jTorchVisuals["TorchBreak"]["AcidParticles"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchBreak.CharacterGlow = jTorchVisuals["TorchBreak"]["CharacterGlow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchBreak.Smoke = jTorchVisuals["TorchBreak"]["Smoke"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.TorchVisualSetting.TorchHit.FireEffect = jTorchVisuals["TorchHit"]["FireEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchHit.FireEffect2 = jTorchVisuals["TorchHit"]["FireEffect2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchHit.FlameFireC = jTorchVisuals["TorchHit"]["FlameFireC"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchHit.FlameGlow = jTorchVisuals["TorchHit"]["FlameGlow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchHit.FsBox = jTorchVisuals["TorchHit"]["FsBox"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchHit.Glow = jTorchVisuals["TorchHit"]["Glow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchHit.GlowUnmask = jTorchVisuals["TorchHit"]["GlowUnmask"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchHit.RadialBurned = jTorchVisuals["TorchHit"]["RadialBurned"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchHit.RadialBurned2 = jTorchVisuals["TorchHit"]["RadialBurned2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchHit.SpriteSnowPattern = jTorchVisuals["TorchHit"]["SpriteSnowPattern"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.TorchVisualSetting.TorchHitSmall.FireEffect = jTorchVisuals["TorchHitSmall"]["FireEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchHitSmall.FireEffect2 = jTorchVisuals["TorchHitSmall"]["FireEffect2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchHitSmall.FlameFireC = jTorchVisuals["TorchHitSmall"]["FlameFireC"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchHitSmall.FlameGlow = jTorchVisuals["TorchHitSmall"]["FlameGlow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchHitSmall.FsBox = jTorchVisuals["TorchHitSmall"]["FsBox"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchHitSmall.Glow = jTorchVisuals["TorchHitSmall"]["Glow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchHitSmall.GlowUnmask = jTorchVisuals["TorchHitSmall"]["GlowUnmask"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchHitSmall.RadialBurned = jTorchVisuals["TorchHitSmall"]["RadialBurned"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchHitSmall.RadialBurned2 = jTorchVisuals["TorchHitSmall"]["RadialBurned2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.TorchVisualSetting.TorchHitSmall.SpriteSnowPattern = jTorchVisuals["TorchHitSmall"]["SpriteSnowPattern"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.GrenadeVisualSetting.Grenade.FireEffect = jj1["GrenadeVisualSettings"]["Grenade"]["FireEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.Grenade.FireSprite = jj1["GrenadeVisualSettings"]["Grenade"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.Grenade.Flame1 = jj1["GrenadeVisualSettings"]["Grenade"]["Flame1"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.Grenade.Flame2 = jj1["GrenadeVisualSettings"]["Grenade"]["Flame2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.Grenade.Flame3 = jj1["GrenadeVisualSettings"]["Grenade"]["Flame3"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.Grenade.LightCircle = jj1["GrenadeVisualSettings"]["Grenade"]["LightCircle"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.Grenade.MainTrail = jj1["GrenadeVisualSettings"]["Grenade"]["MainTrail"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.Grenade.ProtectiveLight = jj1["GrenadeVisualSettings"]["Grenade"]["ProtectiveLight"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.Grenade.Smoke = jj1["GrenadeVisualSettings"]["Grenade"]["Smoke"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.Grenade.SnowPattern1 = jj1["GrenadeVisualSettings"]["Grenade"]["SnowPattern1"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.Grenade.SnowPattern2 = jj1["GrenadeVisualSettings"]["Grenade"]["SnowPattern2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.Grenade.SnowPattern3 = jj1["GrenadeVisualSettings"]["Grenade"]["SnowPattern3"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.Grenade.TrailZigZag = jj1["GrenadeVisualSettings"]["Grenade"]["TrailZigZag"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.GrenadeVisualSetting.Charged.FireEffect = jj1["GrenadeVisualSettings"]["Charged"]["FireEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.Charged.FireSprite = jj1["GrenadeVisualSettings"]["Charged"]["FireSprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.Charged.Flame1 = jj1["GrenadeVisualSettings"]["Charged"]["Flame1"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.Charged.Flame2 = jj1["GrenadeVisualSettings"]["Charged"]["Flame2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.Charged.Flame3 = jj1["GrenadeVisualSettings"]["Charged"]["Flame3"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.Charged.LightCircle = jj1["GrenadeVisualSettings"]["Charged"]["LightCircle"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.Charged.MainTrail = jj1["GrenadeVisualSettings"]["Charged"]["MainTrail"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.Charged.ProtectiveLight = jj1["GrenadeVisualSettings"]["Charged"]["ProtectiveLight"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.Charged.Smoke = jj1["GrenadeVisualSettings"]["Charged"]["Smoke"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.Charged.SnowPattern1 = jj1["GrenadeVisualSettings"]["Charged"]["SnowPattern1"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.Charged.SnowPattern2 = jj1["GrenadeVisualSettings"]["Charged"]["SnowPattern2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.Charged.SnowPattern3 = jj1["GrenadeVisualSettings"]["Charged"]["SnowPattern3"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.Charged.TrailZigZag = jj1["GrenadeVisualSettings"]["Charged"]["TrailZigZag"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.GrenadeVisualSetting.GrenadeAiming.OuterGlow = jj1["GrenadeVisualSettings"]["GrenadeAiming"]["OuterGlow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeAiming.Sparkle = jj1["GrenadeVisualSettings"]["GrenadeAiming"]["Sparkle"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeAiming.Sprite1 = jj1["GrenadeVisualSettings"]["GrenadeAiming"]["Sprite1"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeAiming.Sprite2 = jj1["GrenadeVisualSettings"]["GrenadeAiming"]["Sprite2"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.GrenadeVisualSetting.GrenadeCharging.ArcaneOrb = jj1["GrenadeVisualSettings"]["GrenadeCharging"]["ArcaneOrb"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeCharging.ChargingJump = jj1["GrenadeVisualSettings"]["GrenadeCharging"]["ChargingJump"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeCharging.EnergySplash = jj1["GrenadeVisualSettings"]["GrenadeCharging"]["EnergySplash"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeCharging.SnowPattern = jj1["GrenadeVisualSettings"]["GrenadeCharging"]["SnowPattern"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeCharging.VignetteMask1 = jj1["GrenadeVisualSettings"]["GrenadeCharging"]["VignetteMask1"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeCharging.VignetteMask2 = jj1["GrenadeVisualSettings"]["GrenadeCharging"]["VignetteMask2"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.GrenadeVisualSetting.GrenadeExplosion.Distortion = jj1["GrenadeVisualSettings"]["GrenadeExplosion"]["Distortion"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosion.FireEffect = jj1["GrenadeVisualSettings"]["GrenadeExplosion"]["FireEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosion.ForceField = jj1["GrenadeVisualSettings"]["GrenadeExplosion"]["ForceField"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosion.FX = jj1["GrenadeVisualSettings"]["GrenadeExplosion"]["FX"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosion.LightCircle = jj1["GrenadeVisualSettings"]["GrenadeExplosion"]["LightCircle"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosion.LightGlow = jj1["GrenadeVisualSettings"]["GrenadeExplosion"]["LightGlow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosion.RadialBurned = jj1["GrenadeVisualSettings"]["GrenadeExplosion"]["RadialBurned"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosion.RadialBurned2 = jj1["GrenadeVisualSettings"]["GrenadeExplosion"]["RadialBurned2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosion.RadialCrack = jj1["GrenadeVisualSettings"]["GrenadeExplosion"]["RadialCrack"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosion.RadialIrisImpact = jj1["GrenadeVisualSettings"]["GrenadeExplosion"]["RadialIrisImpact"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosion.Smoke = jj1["GrenadeVisualSettings"]["GrenadeExplosion"]["Smoke"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosion.SnowPattern = jj1["GrenadeVisualSettings"]["GrenadeExplosion"]["SnowPattern"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosion.SpriteSheetFire = jj1["GrenadeVisualSettings"]["GrenadeExplosion"]["SpriteSheetFire"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosion.StarSpike = jj1["GrenadeVisualSettings"]["GrenadeExplosion"]["StarSpike"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.GrenadeVisualSetting.GrenadeExplosionCharged.Distortion = jj1["GrenadeVisualSettings"]["GrenadeExplosionCharged"]["Distortion"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosionCharged.FireEffect = jj1["GrenadeVisualSettings"]["GrenadeExplosionCharged"]["FireEffect"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosionCharged.ForceField = jj1["GrenadeVisualSettings"]["GrenadeExplosionCharged"]["ForceField"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosionCharged.FX = jj1["GrenadeVisualSettings"]["GrenadeExplosionCharged"]["FX"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosionCharged.LightCircle = jj1["GrenadeVisualSettings"]["GrenadeExplosionCharged"]["LightCircle"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosionCharged.LightGlow = jj1["GrenadeVisualSettings"]["GrenadeExplosionCharged"]["LightGlow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosionCharged.RadialBurned = jj1["GrenadeVisualSettings"]["GrenadeExplosionCharged"]["RadialBurned"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosionCharged.RadialBurned2 = jj1["GrenadeVisualSettings"]["GrenadeExplosionCharged"]["RadialBurned2"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosionCharged.RadialCrack = jj1["GrenadeVisualSettings"]["GrenadeExplosionCharged"]["RadialCrack"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosionCharged.RadialIrisImpact = jj1["GrenadeVisualSettings"]["GrenadeExplosionCharged"]["RadialIrisImpact"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosionCharged.Smoke = jj1["GrenadeVisualSettings"]["GrenadeExplosionCharged"]["Smoke"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosionCharged.SnowPattern = jj1["GrenadeVisualSettings"]["GrenadeExplosionCharged"]["SnowPattern"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosionCharged.SpriteSheetFire = jj1["GrenadeVisualSettings"]["GrenadeExplosionCharged"]["SpriteSheetFire"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosionCharged.StarSpike = jj1["GrenadeVisualSettings"]["GrenadeExplosionCharged"]["StarSpike"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.GrenadeVisualSetting.GrenadeExplosionFractured.ArrowDistortion = jj1["GrenadeVisualSettings"]["GrenadeExplosionFractured"]["ArrowDistortion"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosionFractured.ArrowGlow = jj1["GrenadeVisualSettings"]["GrenadeExplosionFractured"]["ArrowGlow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosionFractured.ArrowSingleParticle = jj1["GrenadeVisualSettings"]["GrenadeExplosionFractured"]["ArrowSingleParticle"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosionFractured.ArrowSmoke = jj1["GrenadeVisualSettings"]["GrenadeExplosionFractured"]["ArrowSmoke"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosionFractured.ArrowVignette = jj1["GrenadeVisualSettings"]["GrenadeExplosionFractured"]["ArrowVignette"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosionFractured.Burst = jj1["GrenadeVisualSettings"]["GrenadeExplosionFractured"]["Burst"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosionFractured.BurstPreGlow = jj1["GrenadeVisualSettings"]["GrenadeExplosionFractured"]["BurstPreGlow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosionFractured.Distortion = jj1["GrenadeVisualSettings"]["GrenadeExplosionFractured"]["Distortion"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeExplosionFractured.SnowPattern = jj1["GrenadeVisualSettings"]["GrenadeExplosionFractured"]["SnowPattern"].get<tem::Vector4>() * 0.003921568627451f;

	VisualSetting.GrenadeVisualSetting.GrenadeFractured.OriSparkle = jj1["GrenadeVisualSettings"]["GrenadeFractured"]["OriSparkle"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeFractured.OuterGlow = jj1["GrenadeVisualSettings"]["GrenadeFractured"]["OuterGlow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeFractured.ParticleDropGlow = jj1["GrenadeVisualSettings"]["GrenadeFractured"]["ParticleDropGlow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeFractured.ParticleImpactGlow = jj1["GrenadeVisualSettings"]["GrenadeFractured"]["ParticleImpactGlow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeFractured.SharedCircleGlow = jj1["GrenadeVisualSettings"]["GrenadeFractured"]["SharedCircleGlow"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeFractured.SingleSnowParticle = jj1["GrenadeVisualSettings"]["GrenadeFractured"]["SingleSnowParticle"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeFractured.Sprite = jj1["GrenadeVisualSettings"]["GrenadeFractured"]["Sprite"].get<tem::Vector4>() * 0.003921568627451f;
	VisualSetting.GrenadeVisualSetting.GrenadeFractured.Trail = jj1["GrenadeVisualSettings"]["GrenadeFractured"]["Trail"].get<tem::Vector4>() * 0.003921568627451f;
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

void SeinVisualEditor::SetSkinnedMeshRendererColorByName(app::GameObject* parent, std::string componentName, tem::Vector4 color, tem::Vector4 emissive, std::string masterName, int setActive)
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
						if (SeinVisualEditor::DefaultVisualColors.find(masterName + componentName) == SeinVisualEditor::DefaultVisualColors.end())
							SeinVisualEditor::DefaultVisualColors[masterName + componentName] = defaultcolor;

						app::Color defaultcolorEmi = app::Material_GetColor(meshMat, EmiColor, NULL);
						if (SeinVisualEditor::DefaultVisualColors.find(masterName + componentName + "Emi") == SeinVisualEditor::DefaultVisualColors.end())
							SeinVisualEditor::DefaultVisualColors[masterName + componentName + "Emi"] = defaultcolorEmi;

						app::Material_SetColor(meshMat, TextureName1, color.ToColor(), NULL);
						app::Material_SetColor(meshMat, EmiColor, emissive.ToColor(), NULL);
					}
				}
			}
		}
	}
}

void SeinVisualEditor::SetSkinnedMeshRendererColor(app::GameObject* parent, std::string componentName, tem::Vector4 color, tem::Vector4 emissive, std::string masterName, int setActive)
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
					if (SeinVisualEditor::DefaultVisualColors.find(masterName + componentName) == SeinVisualEditor::DefaultVisualColors.end())
						SeinVisualEditor::DefaultVisualColors[masterName + componentName] = defaultcolor;

					app::Color defaultcolorEmi = app::Material_GetColor(meshMat, EmiColor, NULL);
					if (SeinVisualEditor::DefaultVisualColors.find(masterName + componentName + "Emi") == SeinVisualEditor::DefaultVisualColors.end())
						SeinVisualEditor::DefaultVisualColors[masterName + componentName + "Emi"] = defaultcolorEmi;

					app::Material_SetColor(meshMat, TextureName1, color.ToColor(), NULL);
					app::Material_SetColor(meshMat, EmiColor, emissive.ToColor(), NULL);
				}
			}
		}
	}
}


void SeinVisualEditor::SetSkinnedMeshRendererColor(app::SkinnedMeshRenderer* skinnedMesh, std::string componentName, tem::Vector4 color, tem::Vector4 emissive, std::string masterName, int setActive)
{
	if (skinnedMesh != nullptr)
	{
		app::String* TextureName1 = string_new("_Color");
		app::String* EmiColor = string_new("_EmissivityColor");
		app::Material* meshMat = app::Renderer_GetMaterial((app::Renderer*)skinnedMesh, NULL);

		if (meshMat != nullptr)
		{
			app::Color defaultcolor = app::Material_GetColor(meshMat, TextureName1, NULL);
			if (SeinVisualEditor::DefaultVisualColors.find(masterName + componentName) == SeinVisualEditor::DefaultVisualColors.end())
				SeinVisualEditor::DefaultVisualColors[masterName + componentName] = defaultcolor;

			app::Color defaultcolorEmi = app::Material_GetColor(meshMat, EmiColor, NULL);
			if (SeinVisualEditor::DefaultVisualColors.find(masterName + componentName + "Emi") == SeinVisualEditor::DefaultVisualColors.end())
				SeinVisualEditor::DefaultVisualColors[masterName + componentName + "Emi"] = defaultcolorEmi;

			app::Material_SetColor(meshMat, TextureName1, color.ToColor(), NULL);
			app::Material_SetColor(meshMat, EmiColor, emissive.ToColor(), NULL);
		}
	}
}

void SeinVisualEditor::SetMeshRendererColorByName(app::GameObject* parent, std::string componentName, tem::Vector4 color, tem::Vector4 emissive, std::string masterName, int setActive)
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
						if (SeinVisualEditor::DefaultVisualColors.find(masterName + componentName) == SeinVisualEditor::DefaultVisualColors.end())
							SeinVisualEditor::DefaultVisualColors[masterName + componentName] = defaultcolor;

						app::Color defaultcolorEmi = app::Material_GetColor(meshMat, EmiColor, NULL);
						if (SeinVisualEditor::DefaultVisualColors.find(masterName + componentName + "Emi") == SeinVisualEditor::DefaultVisualColors.end())
							SeinVisualEditor::DefaultVisualColors[masterName + componentName + "Emi"] = defaultcolorEmi;

						app::Material_SetColor(meshMat, TextureName1, color.ToColor(), NULL);
						app::Material_SetColor(meshMat, EmiColor, emissive.ToColor(), NULL);
					}
				}
			}
		}
	}
}

void SeinVisualEditor::SetMeshRendererColor(app::GameObject* parent, std::vector<std::string>& scenePath, tem::Vector4 color, std::string masterName, int setActive)
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
					if (SeinVisualEditor::DefaultVisualColors.find(masterName + scenePath[scenePath.size() - 1]) == SeinVisualEditor::DefaultVisualColors.end())
						SeinVisualEditor::DefaultVisualColors[masterName + scenePath[scenePath.size() - 1]] = defaultcolor;

					app::Color defaultcolorEmi = app::Material_GetColor(meshMat, EmiColor, NULL);
					if (SeinVisualEditor::DefaultVisualColors.find(masterName + scenePath[scenePath.size() - 1] + "Emi") == SeinVisualEditor::DefaultVisualColors.end())
						SeinVisualEditor::DefaultVisualColors[masterName + scenePath[scenePath.size() - 1] + "Emi"] = defaultcolorEmi;

					app::Material_SetColor(meshMat, TextureName1, color.ToColor(), NULL);
					app::Material_SetColor(meshMat, EmiColor, color.ToColor(), NULL);
					//app::Renderer_SetMaterial((app::Renderer*)meshRenderer, meshMat, NULL);
				}
			}
		}
	}
}

void SeinVisualEditor::SetMeshRenderersColor(app::GameObject* parent, std::string componentName, tem::Vector4 color, tem::Vector4 emissive, std::string masterName, int setActive)
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
						if (SeinVisualEditor::DefaultVisualColors.find(masterName + componentName) == SeinVisualEditor::DefaultVisualColors.end())
							SeinVisualEditor::DefaultVisualColors[masterName + componentName] = defaultcolor;

						app::Color defaultcolorEmi = app::Material_GetColor(meshMat, EmiColor, NULL);
						if (SeinVisualEditor::DefaultVisualColors.find(masterName + componentName + "Emi") == SeinVisualEditor::DefaultVisualColors.end())
							SeinVisualEditor::DefaultVisualColors[masterName + componentName + "Emi"] = defaultcolorEmi;

						app::Material_SetColor(meshMat, TextureName1, color.ToColor(), NULL);
						app::Material_SetColor(meshMat, EmiColor, emissive.ToColor(), NULL);
						//app::Renderer_SetMaterial((app::Renderer*)particleRenderer, meshMat, NULL);
					}
				}
			}
		}
	}
}

void SeinVisualEditor::SetParticleRendererColorByName(app::GameObject* parent, std::string componentName, tem::Vector4 color, tem::Vector4 emissive, std::string masterName, int setActive)
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
						if (SeinVisualEditor::DefaultVisualColors.find(masterName + componentName) == SeinVisualEditor::DefaultVisualColors.end())
							SeinVisualEditor::DefaultVisualColors[masterName + componentName] = defaultcolor;

						app::Color defaultcolorEmi = app::Material_GetColor(meshMat, EmiColor, NULL);
						if (SeinVisualEditor::DefaultVisualColors.find(masterName + componentName + "Emi") == SeinVisualEditor::DefaultVisualColors.end())
							SeinVisualEditor::DefaultVisualColors[masterName + componentName + "Emi"] = defaultcolorEmi;

						app::Material_SetColor(meshMat, TextureName1, color.ToColor(), NULL);
						app::Material_SetColor(meshMat, EmiColor, emissive.ToColor(), NULL);
					}
				}
			}
		}
	}
}

void SeinVisualEditor::SetParticleRendererColor(app::GameObject* parent, std::vector<std::string>& scenePath, tem::Vector4 color, std::string masterName, int setActive)
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
					if (SeinVisualEditor::DefaultVisualColors.find(masterName + scenePath[scenePath.size() - 1]) == SeinVisualEditor::DefaultVisualColors.end())
						SeinVisualEditor::DefaultVisualColors[masterName + scenePath[scenePath.size() - 1]] = defaultcolor;

					app::Color defaultcolorEmi = app::Material_GetColor(meshMat, EmiColor, NULL);
					if (SeinVisualEditor::DefaultVisualColors.find(masterName + scenePath[scenePath.size() - 1] + "Emi") == SeinVisualEditor::DefaultVisualColors.end())
						SeinVisualEditor::DefaultVisualColors[masterName + scenePath[scenePath.size() - 1] + "Emi"] = defaultcolorEmi;

					app::Material_SetColor(meshMat, TextureName1, color.ToColor(), NULL);
					app::Material_SetColor(meshMat, EmiColor, color.ToColor(), NULL);
					//app::Renderer_SetMaterial((app::Renderer*)particleRenderer, meshMat, NULL);
				}
			}
		}
	}
}

void SeinVisualEditor::SetParticleRenderersColor(app::GameObject* parent, std::string componentName, tem::Vector4 color, tem::Vector4 emissive, std::string masterName, int setActive)
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
						if (SeinVisualEditor::DefaultVisualColors.find(masterName + componentName) == SeinVisualEditor::DefaultVisualColors.end())
							SeinVisualEditor::DefaultVisualColors[masterName + componentName] = defaultcolor;

						app::Color defaultcolorEmi = app::Material_GetColor(meshMat, EmiColor, NULL);
						if (SeinVisualEditor::DefaultVisualColors.find(masterName + componentName + "Emi") == SeinVisualEditor::DefaultVisualColors.end())
							SeinVisualEditor::DefaultVisualColors[masterName + componentName + "Emi"] = defaultcolorEmi;

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