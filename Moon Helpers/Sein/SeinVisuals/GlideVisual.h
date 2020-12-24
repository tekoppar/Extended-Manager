#pragma once

class GlideVisualSettings
{
public:
	tem::Vector4 FeatherColor = tem::Vector4(1.000000f, 1.000000f, 1.000000f, 1.000000f);
	tem::Vector4 FeatherEmissiveColor = tem::Vector4(0.000000f, 0.000000f, 0.000000f, 1.000000f);
	tem::Vector4 FeatherUpwindColor = tem::Vector4();
	tem::Vector4 FeatherflapColor = tem::Vector4(1.000000f, 1.000000f, 1.000000f, 1.000000f);
	tem::Vector4 FeatherflapEmissiveColor = tem::Vector4(0.000000f, 0.000000f, 0.000000f, 1.000000f);

	void SetGlideVisuals(GlideVisualSettings glideSettings);
};