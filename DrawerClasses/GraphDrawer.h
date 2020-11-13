#pragma once

#ifndef _GRAPHDRAWER_H
#define _GRAPHDRAWER_H

class GraphColors {
public:
	static app::Color Red;
	static app::Color Green;
	static app::Color Black;
	static app::Color Black2;
	static app::Color Grey;
	static app::Color Blue;
	static app::Color Pink;
	static app::Color Orange;
	static app::Color DarkGray;
	static app::Color Transparent;
	static app::Color Middle;

	static void Initialize();
	static app::Color RandomColor(float value = 1.0f, float alpha = 0.0f);
};
extern GraphColors graphColors;

class FloatData {
public:
	std::vector<float> Data;
	app::Color Color = GraphColors::Pink;
	float yScale = 8;
	float xScale = 1;
	float InMin = 0;
	float InMax = 0;

	FloatData(std::vector<float> data, app::Color color = GraphColors::Pink, float scaleY = 8, float scaleX = 1, float inMin = 0, float inMax = 0);
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
	app::GameObject* graphHorizontalLayout = nullptr;

	app::Scrollbar* horizontalScrollbar = nullptr;
	app::Scrollbar* verticalScrollbar = nullptr;

	app::Texture2D* graphColorTexture = nullptr;
	app::Texture2D* lightMap = nullptr;

	std::vector<FloatData> AllFloatData;

	app::SeinCharacter* SeinCharacter = nullptr;

	bool IsInitialized = false;

	int CurrentGraphWidth = 1024;
	int CurrentGraphHeight = 256;

	Graph();
	void Destroy();
	void Initialize(int width = 0);
	static void CleanUpStatic();
	void CloseGraph();
	void Update();
	void StartDrawing(int width = 0);
	static void FindNextWidth(int& width);
	void AddFloatData(std::vector<float> data, app::Color color, float yScale = 8, float xScale = 1, float inMin = 0, float inMax = 0);
	void DrawFloats(std::vector<float> data, app::Color color, float yScale = 8, float xScale = 1);
	void DrawFloatsMapRange(std::vector<float> data, app::Color color, float inMin, float inMax, float yScale = 8, float xScale = 1);
	void ClearGraph(app::Texture2D* texture, app::Color color, int width = 0);
	void DrawGraphLinesX(app::Texture2D* texture, app::Color color);
	void DrawGraphLinesY(app::Texture2D* texture, app::Color color);
	void AddGraphLabel(const std::string& text, int fontSize, app::Color color, int index = 0);
	void ReDrawGraphLines(int index = 0);
	void SetupTextures(int width = 0, int height = 0);
	void SetupUI(int width = 0, int height = 0);
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

	void Awake(const std::string& text = "Example", int fontSize = 16, app::Color color = GraphColors::Pink);
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