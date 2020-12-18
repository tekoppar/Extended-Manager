#pragma once

class GoldenSeinViualSettings
{
public:
	tem::Vector4 SeinBodyColor;
	tem::Vector4 SeinBodyEmissiveColor;
	tem::Vector4 SeinParticleColor;
	tem::Vector4 SeinRadialLightColor;
	tem::Vector4 SeinTrailColor;
	tem::Vector4 SeinTrailMeshColor;

	void SetGoldenSeinVisuals(GoldenSeinViualSettings seinSettings);
};