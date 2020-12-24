#pragma once

class GoldenSeinViualSettings
{
public:
	tem::Vector4 SeinBodyColor = tem::Vector4(1.603774f, 0.866793f, 0.204254f, 1.521569f);
	tem::Vector4 SeinBodyEmissiveColor = tem::Vector4(0.000000f, 0.000000f, 0.000000f, 0.000000f);
	tem::Vector4 SeinParticleColor = tem::Vector4(1.905660f, 1.068100f, 0.422481f, 0.596078f);
	tem::Vector4 SeinRadialLightColor = tem::Vector4(1.471698f, 0.695338f, 0.000000f, 1.309804f);
	tem::Vector4 SeinTrailColor = tem::Vector4();
	tem::Vector4 SeinTrailMeshColor = tem::Vector4();

	void SetGoldenSeinVisuals(GoldenSeinViualSettings seinSettings);
};