#pragma once

class GlideVisualSettings
{
public:
	tem::Vector4 FeatherColor;
	tem::Vector4 FeatherEmissiveColor;
	tem::Vector4 FeatherUpwindColor;
	tem::Vector4 FeatherflapColor;
	tem::Vector4 FeatherflapEmissiveColor;

	void SetGlideVisuals(GlideVisualSettings glideSettings);
};