#pragma once

#ifndef _GRAPHDRAWER_H
#define _GRAPHDRAWER_H

#include "../HelperClasses.h"

class GraphColors {
public:
	app::Color Red;
	app::Color Green;
	app::Color Black;
	app::Color Black2;
	app::Color Grey;
	app::Color Blue;
	app::Color Pink;
	app::Color Orange;
	app::Color DarkGray;
	app::Color Transparent;

	GraphColors()
	{
		Red.a = 1.0f;
		Red.b = 0.0f;
		Red.g = 0.0f;
		Red.r = 1.0f;

		Pink.a = 1.0f;
		Pink.b = 1.0f;
		Pink.g = 0.0f;
		Pink.r = 1.0f;

		Orange.a = 1.0f;
		Orange.b = 0.0f;
		Orange.g = 0.5f;
		Orange.r = 1.0f;

		Green.a = 1.0f;
		Green.b = 0.0f;
		Green.g = 1.0f;
		Green.r = 0.0f;

		Blue.a = 1.0f;
		Blue.b = 1.0f;
		Blue.g = 0.0f;
		Blue.r = 0.0f;

		Black.a = 0.6f;
		Black.b = 0.0f;
		Black.g = 0.0f;
		Black.r = 0.0f;

		Black2.a = 0.9f;
		Black2.b = 0.16f;
		Black2.g = 0.16f;
		Black2.r = 0.16f;

		Grey.a = 1.0f;
		Grey.b = 1.0f;
		Grey.g = 1.0f;
		Grey.r = 1.0f;

		DarkGray.a = 1.0f;
		DarkGray.b = 0.8f;
		DarkGray.g = 0.8f;
		DarkGray.r = 0.8f;

		Transparent.a = 0.0f;
		Transparent.b = 0.0f;
		Transparent.g = 0.0f;
		Transparent.r = 0.0f;
	}
};
extern GraphColors graphColors;

class FloatData {
public:
	std::vector<float> Data;
	app::Color Color = graphColors.Pink;
	float yScale = 8;
	float xScale = 1;
	float InMin = 0;
	float InMax = 0;

	FloatData(std::vector<float> data, app::Color color = graphColors.Pink, float scaleY = 8, float scaleX = 1, float inMin = 0, float inMax = 0);
};

class Graph 
{
public:
	static Graph* Instance;

	app::Material* DataGraphColorMaterial = nullptr;
	app::Material* RaceDataMaterial = nullptr;
	app::Material* RaceDataBlackMaterial = nullptr;

	app::GameObject* masterCanvas = nullptr;
	app::GameObject* newCanvas = nullptr;
	app::GameObject* canvasGraphBackground = nullptr;
	app::GameObject* canvasGraphData = nullptr;
	app::GameObject* labelLayout = nullptr;
	app::GameObject* canvasVerticalLayout = nullptr;

	app::Texture2D* graphColorTexture = nullptr;
	app::Texture2D* lightMap = nullptr;

	std::vector<FloatData> AllFloatData;

	Graph();
	void Destroy();
	void Initialize();
	static void CleanUpStatic();
	void CloseGraph();
	void StartDrawing();
	void AddFloatData(std::vector<float> data, app::Color color, float yScale = 8, float xScale = 1, float inMin = 0, float inMax = 0);
	void DrawFloats(std::vector<float> data, app::Color color, float yScale = 8, float xScale = 1);
	void DrawFloatsMapRange(std::vector<float> data, app::Color color, float inMin, float inMax, float yScale = 8, float xScale = 1);
	void ClearGraph(app::Texture2D* texture, app::Color color);
	void DrawGraphLinesX(app::Texture2D* texture, app::Color color);
	void DrawGraphLinesY(app::Texture2D* texture, app::Color color);
	void AddGraphLabel(const std::string& text, int fontSize, app::Color color, int index = 0);
	void ReDrawGraphLines(int index = 0);
	void SetupTextures();
	void SetupUI();
	void GetShader();
	void ClickEvent(void* __this);
	void Zoom(float zoomValue);
};
extern Graph graphDrawer;

class IOnclick
{
public:
	virtual ~IOnclick();

	void IOnClick();
};

class GraphLabel : public app::MonoBehaviour, public app::Behaviour, public app::Component, public app::Object, app::IPointerClickHandler, app::ISubmitHandler, app::IEventSystemHandler {
public:
	void (*onClickMethod)(GraphLabel* __this);

	int intValue = 0;
	float floatValue = 0.0f;

	app::Button* button = nullptr;
	app::Text* textComponent = nullptr;

	void Awake(const std::string& text = "Example", int fontSize = 16, app::Color color = graphColors.Pink);
};

static void DrawGraphLinesButton(GraphLabel* __this);
static void ZoomGraphButton(GraphLabel* __this);
static void CleanUpGraphButton(GraphLabel* __this);

static const int GraphWidth = 1024;
static const int GraphHeight = 256;

static const float MapRange(float x, float in_min, float in_max, float out_min, float out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#endif