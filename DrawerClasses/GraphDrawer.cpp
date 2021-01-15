#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include "Adresses.h"
#include "detours.h"

#include "StringUtils.h"

#include "CreateUI.h"
#include "ManagerDef.h"
#include "tem.h"

#include "GraphDrawer.h"

Graph graphDrawer = Graph();
Graph* Graph::Instance;

std::vector<GraphLabel*> AllGraphLabels;
std::vector<GraphLabel*> AllDefaultGraphLabels;

app::Color GraphColors::Red;
app::Color GraphColors::Green;
app::Color GraphColors::Black;
app::Color GraphColors::Black2;
app::Color GraphColors::Grey;
app::Color GraphColors::Blue;
app::Color GraphColors::Pink;
app::Color GraphColors::Orange;
app::Color GraphColors::DarkGray;
app::Color GraphColors::Transparent;
app::Color GraphColors::Middle;

void GraphColors::Initialize()
{
	{
		GraphColors::Red.a = 1.0f;
		GraphColors::Red.b = GraphColors::Red.g = 0.0f;
		GraphColors::Red.r = 1.0f;

		GraphColors::Pink.a = GraphColors::Pink.b = 1.0f;
		GraphColors::Pink.g = 0.0f;
		GraphColors::Pink.r = 1.0f;

		GraphColors::Orange.a = 1.0f;
		GraphColors::Orange.b = 0.0f;
		GraphColors::Orange.g = 0.5f;
		GraphColors::Orange.r = 1.0f;

		GraphColors::Green.a = 1.0f;
		GraphColors::Green.b = 0.0f;
		GraphColors::Green.g = 1.0f;
		GraphColors::Green.r = 0.0f;

		GraphColors::Blue.a = GraphColors::Blue.b = 1.0f;
		GraphColors::Blue.g = GraphColors::Blue.r = 0.0f;

		GraphColors::Black.a = 0.6f;
		GraphColors::Black.b = GraphColors::Black.g = GraphColors::Black.r = 0.0f;
		GraphColors::Black2.a = 0.9f;
		GraphColors::Black2.b = Black2.g = Black2.r = 0.16f;
		GraphColors::Grey.a = GraphColors::Grey.b = GraphColors::Grey.g = GraphColors::Grey.r = 1.0f;
		GraphColors::DarkGray.a = 1.0f;
		GraphColors::DarkGray.b = GraphColors::DarkGray.g = GraphColors::DarkGray.r = 0.8f;
		GraphColors::Transparent.a = GraphColors::Transparent.b = GraphColors::Transparent.g = GraphColors::Transparent.r = 0.0f;
		GraphColors::Middle.r = GraphColors::Middle.g = GraphColors::Middle.b = GraphColors::Middle.a = 0.5;
	}
}

app::Color GraphColors::RandomColor(float value, float alpha)
{
	app::Color color = app::Color();

	color.r = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / value));
	color.g = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / value));
	color.b = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / value));
	color.a = alpha == 0.0f ? 1.0f : static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / alpha));

	return color;
}

Graph::Graph()
{

}

void Graph::FindNextWidth(int& width)
{
	int a = width % 512;

	while (((width / 2) % 512) != 0)
	{
		width -= a;

		if (width != 0)
		{
			width += 512;
			a = width % 512;
		}
	}
}

void Graph::Initialize(int width)
{
	int newWidth = width;
	FindNextWidth(newWidth);

	if (IsInitialized == false)
	{
		SetupTextures(newWidth, CurrentGraphHeight);
	}
	AllFloatData = std::vector<FloatData>();
	(*app::DebugMenu__TypeInfo)->static_fields->ShouldKeepImGUIEnabled = true;

	if (graphColorTexture != nullptr)
	{
		if (CurrentGraphWidth < newWidth)
		{
			app::Texture2D_Resize(graphColorTexture, newWidth, CurrentGraphHeight, NULL);
			app::Texture2D_Resize(lightMap, newWidth, CurrentGraphHeight, NULL);
		}

		ClearGraph(graphColorTexture, GraphColors::Transparent, newWidth);
		ClearGraph(lightMap, GraphColors::Black2, newWidth);
		DrawGraphLinesX(lightMap, GraphColors::Grey);
		DrawGraphLinesY(lightMap, GraphColors::Grey);
	}

	IsInitialized = true;
}

void Graph::Destroy()
{
}

void Graph::Update()
{
	if (horizontalScrollbar != nullptr && verticalScrollbar != nullptr && canvasGraphData != nullptr)
	{
		float valueX = app::Scrollbar_get_value(horizontalScrollbar, NULL);
		float valueY = app::Scrollbar_get_value(verticalScrollbar, NULL) - 0.5f;
		app::Vector2 size = RectTransformGetSizeDelta(canvasGraphData);
		tem::Vector3 scale = TransformGetScale(canvasGraphData);
		TransformSetLocalPosition(canvasGraphData, tem::Vector3(((valueX * size.x) * scale.X) * -1, (valueY * size.y) * scale.Y, 0.0f));
	}
}

void Graph::CleanUpStatic()
{
	(*app::DebugMenu__TypeInfo)->static_fields->ShouldKeepImGUIEnabled = false;

	Graph* temp = Graph::Instance;
	for (auto& graphLabel : AllDefaultGraphLabels)
	{
		app::Object_1_Destroy_1((app::Object_1*)graphLabel->button, NULL);
		graphLabel->button = nullptr;
		app::Object_1_Destroy_1((app::Object_1*)graphLabel, NULL);
	}
	AllDefaultGraphLabels.clear();

	for (auto& graphLabel : AllGraphLabels)
	{
		app::Object_1_Destroy_1((app::Object_1*)graphLabel->button, NULL);
		graphLabel->button = nullptr;
		app::Object_1_Destroy_1((app::Object_1*)graphLabel, NULL);
	}
	AllDefaultGraphLabels.clear();

	if (temp != nullptr)
	{
		app::Object_1_Destroy_1((app::Object_1*)temp->graphColorTexture, NULL);
		temp->graphColorTexture = nullptr;
		app::Object_1_Destroy_1((app::Object_1*)temp->lightMap, NULL);
		temp->lightMap = nullptr;

		app::Object_1_Destroy_1((app::Object_1*)temp->DataGraphColorMaterial, NULL);
		temp->DataGraphColorMaterial = nullptr;
		app::Object_1_Destroy_1((app::Object_1*)temp->RaceDataMaterial, NULL);
		temp->RaceDataMaterial = nullptr;
		app::Object_1_Destroy_1((app::Object_1*)temp->RaceDataBlackMaterial, NULL);
		temp->RaceDataBlackMaterial = nullptr;

		app::Object_1_Destroy_1((app::Object_1*)temp->canvasGraphBackground, NULL);
		temp->canvasGraphBackground = nullptr;
		app::Object_1_Destroy_1((app::Object_1*)temp->canvasGraphData, NULL);
		temp->canvasGraphData = nullptr;
		app::Object_1_Destroy_1((app::Object_1*)temp->labelLayout, NULL);
		temp->labelLayout = nullptr;
		app::Object_1_Destroy_1((app::Object_1*)temp->canvasVerticalLayout, NULL);
		temp->canvasVerticalLayout = nullptr;
		app::Object_1_Destroy_1((app::Object_1*)temp->newCanvas, NULL);
		temp->newCanvas = nullptr;
		app::Object_1_Destroy_1((app::Object_1*)temp->masterCanvas, NULL);
		temp->masterCanvas = nullptr;
	}

	temp = nullptr;
	Graph::Instance = nullptr;
}

void Graph::CloseGraph()
{
	ClearGraph(graphColorTexture, GraphColors::Transparent);
	(*app::DebugMenu__TypeInfo)->static_fields->ShouldKeepImGUIEnabled = false;

	if (masterCanvas != nullptr)
		app::GameObject_SetActiveRecursively(masterCanvas, false, NULL);

	for (auto& graphLabel : AllGraphLabels)
	{
		app::Object_1_Destroy_1((app::Object_1*)graphLabel->button, NULL);
		graphLabel->button = nullptr;
		app::Object_1_Destroy_1((app::Object_1*)graphLabel, NULL);
	}
	AllGraphLabels.clear();

	app::SeinController_set_IsSuspended(SeinCharacter->fields.Controller, false, NULL);
	app::CharacterPlatformMovement_set_IsSuspended(SeinCharacter->fields.PlatformBehaviour->fields.PlatformMovement, false, NULL);
}

void Graph::StartDrawing(int width)
{
	int newWidth = width;
	FindNextWidth(newWidth);
	(*app::DebugMenu__TypeInfo)->static_fields->ShouldKeepImGUIEnabled = true;

	if (newWidth == 0)
		newWidth = GraphWidth;

	if (masterCanvas == nullptr)
		SetupUI(newWidth, CurrentGraphHeight);
	else
		app::GameObject_SetActiveRecursively(masterCanvas, true, NULL);
}

void Graph::AddFloatData(std::vector<float> data, app::Color color, float yScale, float xScale, float inMin, float inMax)
{
	FloatData floatData = FloatData(data, color, yScale, xScale, inMin, inMax);
	AllFloatData.push_back(floatData);

	if (inMin == 0 && inMax == 0)
	{
		DrawFloats(data, color, yScale, xScale);
	}
	else
	{
		DrawFloatsMapRange(data, color, inMin, inMax, yScale, xScale);
	}
}

void Graph::DrawFloats(std::vector<float> data, app::Color color, float yScale, float xScale)
{
	if (graphColorTexture != nullptr)
	{
		std::size_t previousIndex = 0;
		float previousData = std::max<float>(0, std::min<float>(data[0], GraphWidth));
		float currentData = 0.0f;
		for (std::size_t i = 1; i < data.size(); i++)
		{
			currentData = std::max<float>(0, std::min<float>(data[i], GraphWidth));
			DrawLine(graphColorTexture, static_cast<int>(previousIndex), static_cast<int>(previousData * yScale) + 5, static_cast<int>(i) * static_cast<int>(xScale), static_cast<int>(currentData * yScale) + 5, color);
			previousData = currentData;
			previousIndex = i * static_cast<std::size_t>(xScale);
		}
		app::Texture2D_Apply_1(graphColorTexture, true, NULL);
	}
}

void Graph::DrawFloatsMapRange(std::vector<float> data, app::Color color, float inMin, float inMax, float yScale, float xScale)
{
	if (graphColorTexture != nullptr)
	{
		std::size_t previousIndex = 0;
		float previousData = std::max<float>(1, std::min<float>(data[0], GraphWidth));
		float currentData = 0.0f;
		previousData = MapRange(previousData, inMin, inMax, 16, GraphHeight - 16);
		for (std::size_t i = 1; i < data.size(); i++)
		{
			currentData = std::max<float>(1, std::min<float>(data[i], GraphWidth));
			currentData = MapRange(currentData, inMin, inMax, 16, GraphHeight - 16);
			DrawLine(graphColorTexture, static_cast<int>(previousIndex), static_cast<int>(previousData * yScale), static_cast<int>(i) * static_cast<int>(xScale), static_cast<int>(currentData * yScale), color);
			previousData = currentData;
			previousIndex = i * static_cast<std::size_t>(xScale);
		}
		app::Texture2D_Apply_1(graphColorTexture, true, NULL);
	}
}

void Graph::ClearGraph(app::Texture2D* texture, app::Color color, int width)
{
	if (width == 0)
		width = GraphWidth;

	FillPixels(texture, width, GraphHeight, color);
	app::Texture2D_Apply_1(texture, true, NULL);
}

void Graph::DrawGraphLinesX(app::Texture2D* texture, app::Color color)
{
	std::size_t graphLineSpacing = static_cast<std::size_t>(std::floor(GraphWidth / 64));
	for (std::size_t i = 1; i < graphLineSpacing; i++)
	{
		DrawLine(texture, static_cast<int>(i * 64), 0, static_cast<int>(i * 64), GraphHeight, color);
	}
	app::Texture2D_Apply_1(texture, true, NULL);
}

void Graph::DrawGraphLinesY(app::Texture2D* texture, app::Color color)
{
	std::size_t graphLineSpacing = static_cast<std::size_t>(std::floor(GraphHeight / 64));
	for (std::size_t i = 1; i < graphLineSpacing; i++)
	{
		DrawLine(texture, 0, static_cast<int>(i) * 64, GraphWidth, static_cast<int>(i) * 64, color);
	}
	app::Texture2D_Apply_1(texture, true, NULL);
}

void Graph::AddGraphLabel(const std::string& text, int fontSize, app::Color color, int index)
{
	GraphLabel* graphLabelEvent = new GraphLabel();
	auto class1 = GetClass<>("UnityEngine", "MonoBehaviour");
	graphLabelEvent->app::MonoBehaviour::klass = (app::MonoBehaviour__Class*)class1;

	app::Object__ctor((app::Object*)graphLabelEvent, NULL);
	app::Component__ctor((app::Component*)graphLabelEvent, NULL);
	app::MonoBehaviour__ctor((app::MonoBehaviour*)graphLabelEvent, NULL);
	app::String* bloo = string_new("GraphLabel");
	app::GameObject__ctor((app::GameObject*)graphLabelEvent, bloo, NULL);
	graphLabelEvent->Awake(text, fontSize, color);
	graphLabelEvent->onClickMethod = &DrawGraphLinesButton;
	graphLabelEvent->intValue = index;

	TransformSetParent((app::GameObject*)graphLabelEvent, labelLayout);
	AllGraphLabels.push_back(graphLabelEvent);
}

void Graph::ReDrawGraphLines(int index)
{
	app::Color tempColor;
	for (auto& floatData : AllFloatData)
	{
		tempColor = floatData.Color;
		tempColor.a = 0.5;
		if (floatData.InMin == 0 && floatData.InMax == 0)
		{
			DrawFloats(floatData.Data, tempColor, floatData.yScale, floatData.xScale);
		}
		else
		{
			DrawFloatsMapRange(floatData.Data, tempColor, floatData.InMin, floatData.InMax, floatData.yScale, floatData.xScale);
		}
	}

	if (AllFloatData[index].InMin == 0 && AllFloatData[index].InMax == 0)
	{
		DrawFloats(AllFloatData[index].Data, AllFloatData[index].Color, AllFloatData[index].yScale, AllFloatData[index].xScale);
	}
	else
	{
		DrawFloatsMapRange(AllFloatData[index].Data, AllFloatData[index].Color, AllFloatData[index].InMin, AllFloatData[index].InMax, AllFloatData[index].yScale, AllFloatData[index].xScale);
	}
}

void Graph::SetupTextures(int width, int height)
{
	if (width == 0)
		width = GraphWidth;

	CurrentGraphHeight = height;
	CurrentGraphWidth = width;

	RaceDataMaterial = CreateNewMaterial("UI/Default");// CreateNewMaterial("Hidden/UberShader/4B897D76B847170D884884FBA5CEBC13");// "Hidden/UberShader/4B897D76B847170D884884FBA5CEBC13");// "Hidden/UberShader/E48C37CFA39B1500F0D8A6A5D0B46307");
	RaceDataBlackMaterial = CreateNewMaterial("UI/Default");// "Unlit/Transparent" "Hidden/UberShader/105297F2E11B21A8CBB22D0A6B734A5C" "Hidden/UberShader/4B897D76B847170D884884FBA5CEBC13");// "Hidden/UberShader/E48C37CFA39B1500F0D8A6A5D0B46307");
	//Material_CopyPropertiesFromMaterial(RaceDataBlackMaterial, DataGraphColorMaterial, NULL);

	app::String* UNITY_UI_ALPHACLIPName = string_new("UNITY_UI_ALPHACLIP");
	app::String* UNITY_UI_CLIP_RECTName = string_new("UNITY_UI_CLIP_RECT");
	app::String* srcBlendName = string_new("_SrcBlend");
	app::String* dstBlendName = string_new("_DstBlend");
	app::String* zWriteName = string_new("_ZWrite");
	app::String* _ALPHATEST_ONName = string_new("_ALPHATEST_ON");
	app::String* _ALPHABLEND_ONName = string_new("_ALPHABLEND_ON");
	app::String* _ALPHAPREMULTIPLY_ONName = string_new("_ALPHAPREMULTIPLY_ON");

	app::Material_EnableKeyword_1(RaceDataMaterial, UNITY_UI_ALPHACLIPName, NULL);
	app::Material_EnableKeyword_1(RaceDataMaterial, UNITY_UI_CLIP_RECTName, NULL);
	app::Material_EnableKeyword_1(RaceDataBlackMaterial, UNITY_UI_ALPHACLIPName, NULL);
	app::Material_EnableKeyword_1(RaceDataBlackMaterial, UNITY_UI_CLIP_RECTName, NULL);

	graphColorTexture = (app::Texture2D*)il2cpp_object_new((Il2CppClass*)(*app::Texture2D__TypeInfo));
	app::Texture2D__ctor_3(graphColorTexture, width, GraphHeight, app::TextureFormat__Enum::TextureFormat__Enum_RGBA32, false, false, NULL);
	app::Texture_set_wrapMode((app::Texture*)graphColorTexture, app::TextureWrapMode__Enum::TextureWrapMode__Enum_Repeat, NULL);
	app::Texture_set_filterMode((app::Texture*)graphColorTexture, app::FilterMode__Enum::FilterMode__Enum_Point, NULL);

	//app::Material_SetInt(RaceDataMaterial, srcBlendName, (int)app::BlendMode__Enum::BlendMode__Enum_One, NULL);
	//app::Material_SetInt(RaceDataMaterial, dstBlendName, (int)app::BlendMode__Enum::BlendMode__Enum_OneMinusSrcAlpha, NULL);
	//app::Material_SetInt(RaceDataMaterial, zWriteName, 0, NULL);
	//app::Material_DisableKeyword_1(RaceDataMaterial, _ALPHATEST_ONName, NULL);
	//app::Material_DisableKeyword_1(RaceDataMaterial, _ALPHABLEND_ONName, NULL);
	//app::Material_EnableKeyword_1(RaceDataMaterial, _ALPHAPREMULTIPLY_ONName, NULL);
	//app::Material_set_renderQueue(RaceDataMaterial, 3000, NULL);

	ClearGraph(graphColorTexture, GraphColors::Transparent, width);

	lightMap = (app::Texture2D*)il2cpp_object_new((Il2CppClass*)(*app::Texture2D__TypeInfo));
	app::Texture2D__ctor_3(lightMap, GraphWidth, GraphHeight, app::TextureFormat__Enum::TextureFormat__Enum_RGBA32, true, true, NULL);
	app::Texture_set_wrapMode((app::Texture*)graphColorTexture, app::TextureWrapMode__Enum::TextureWrapMode__Enum_Repeat, NULL);
	app::Texture_set_filterMode((app::Texture*)graphColorTexture, app::FilterMode__Enum::FilterMode__Enum_Point, NULL);

	//app::Material_SetInt(RaceDataBlackMaterial, srcBlendName, (int)app::BlendMode__Enum::BlendMode__Enum_One, NULL);
	//app::Material_SetInt(RaceDataBlackMaterial, dstBlendName, (int)app::BlendMode__Enum::BlendMode__Enum_OneMinusSrcAlpha, NULL);
	//app::Material_SetInt(RaceDataBlackMaterial, zWriteName, 0, NULL);
	//app::Material_DisableKeyword_1(RaceDataBlackMaterial, _ALPHATEST_ONName, NULL);
	//app::Material_DisableKeyword_1(RaceDataBlackMaterial, _ALPHABLEND_ONName, NULL);
	//app::Material_EnableKeyword_1(RaceDataBlackMaterial, _ALPHAPREMULTIPLY_ONName, NULL);
	//app::Material_set_renderQueue(RaceDataBlackMaterial, 3000, NULL);

	ClearGraph(lightMap, GraphColors::Black2);
	DrawGraphLinesX(lightMap, GraphColors::Grey);
	DrawGraphLinesY(lightMap, GraphColors::Grey);

	app::String* TextureName = string_new("_MainTex");
	app::String* TextureName1 = string_new("_Color");

	app::Material_SetColor(RaceDataMaterial, TextureName1, GraphColors::Grey, NULL);
	app::Material_SetTexture(RaceDataMaterial, TextureName, (app::Texture*)graphColorTexture, NULL);
	app::Material_set_mainTexture(RaceDataMaterial, (app::Texture*)graphColorTexture, NULL);

	//Material_SetColor(RaceDataBlackMaterial, TextureName1, GraphColors::Black2, NULL);

	app::Material_SetColor(RaceDataBlackMaterial, TextureName1, GraphColors::Black2, NULL);
	app::Material_SetTexture(RaceDataBlackMaterial, TextureName, (app::Texture*)lightMap, NULL);
	app::Material_set_mainTexture(RaceDataBlackMaterial, (app::Texture*)lightMap, NULL);
}

void Graph::SetupUI(int width, int height)
{
	if (width == 0)
		width = GraphWidth;

	if (height == 0)
		height = GraphHeight;

	if (masterCanvas == nullptr)
	{
		app::String* testingCanvasName = string_new("RaceGraph");
		app::Type* CanvasRendererType = GetType("UnityEngine", "CanvasRenderer");
		app::Type* textType = GetType("UnityEngine.UI", "Text");
		app::Type* imageType = GetType("UnityEngine.UI", "Image");
		app::Type* buttonType = GetType("UnityEngine.UI", "Button");

		masterCanvas = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
		app::GameObject__ctor(masterCanvas, testingCanvasName, NULL);

		app::CanvasRenderer* canvasRenderer = (app::CanvasRenderer*)app::GameObject_AddComponent((app::GameObject*)masterCanvas, CanvasRendererType, NULL);

		newCanvas = CreateNewCanvas();
		app::CanvasScaler* scaler = (app::CanvasScaler*)GetComponentByTypeInChildren(newCanvas, "UnityEngine.UI", "CanvasScaler");
		app::CanvasScaler_set_uiScaleMode(scaler, app::CanvasScaler_ScaleMode__Enum::CanvasScaler_ScaleMode__Enum_ScaleWithScreenSize, NULL);
		app::CanvasScaler_set_referenceResolution(scaler, tem::Vector3::ToVector2(1920, 1080), NULL);
		//app::CanvasScaler_set_uiScaleMode(scaler, app::CanvasScaler_ScaleMode__Enum::CanvasScaler_ScaleMode__Enum_ConstantPixelSize, NULL);
		//app::CanvasScaler_set_scaleFactor(scaler, 0.75f, NULL);

		app::GameObject* eventSystem = DrawUI::EventSystem("EventSystem");

		app::GameObject* rectMask2D = DrawUI::RectMask2D("CanvasMask", GraphWidth, GraphHeight, GraphWidth, GraphHeight);

		canvasGraphBackground = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
		app::String* canvasBackgroundImageName = string_new("CanvasBackgroundImage");
		app::GameObject__ctor(canvasGraphBackground, canvasBackgroundImageName, NULL);
		app::Image* canvasBackgroundImage = (app::Image*)app::GameObject_AddComponent((app::GameObject*)canvasGraphBackground, imageType, NULL);
		app::Image_set_material(canvasBackgroundImage, RaceDataBlackMaterial, NULL);

		canvasGraphData = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
		app::String* canvasImageName = string_new("CanvasDataImage");
		app::GameObject__ctor(canvasGraphData, canvasImageName, NULL);
		app::Image* canvasImage = (app::Image*)app::GameObject_AddComponent((app::GameObject*)canvasGraphData, imageType, NULL);
		app::Image_set_material(canvasImage, RaceDataMaterial, NULL);

		//graphHorizontalLayout = DrawUI::HorizontalLayoutGroup("LabelLayout", app::TextAnchor__Enum::TextAnchor__Enum_UpperRight);
		canvasVerticalLayout = DrawUI::VerticalLayoutGroup("canvasVerticalLayout", app::TextAnchor__Enum::TextAnchor__Enum_UpperCenter);
		labelLayout = DrawUI::HorizontalLayoutGroup("LabelLayout", app::TextAnchor__Enum::TextAnchor__Enum_MiddleCenter);

		GraphLabel* zoomInButton = new GraphLabel();
		auto class1 = GetClass<>("UnityEngine", "MonoBehaviour");
		zoomInButton->app::MonoBehaviour::klass = (app::MonoBehaviour__Class*)class1;
		AllDefaultGraphLabels.push_back(zoomInButton);

		app::Object__ctor((app::Object*)zoomInButton, NULL);
		app::Component__ctor((app::Component*)zoomInButton, NULL);
		app::MonoBehaviour__ctor((app::MonoBehaviour*)zoomInButton, NULL);
		app::String* bloo = string_new("GraphZoomIn");
		app::GameObject__ctor((app::GameObject*)zoomInButton, bloo, NULL);
		zoomInButton->Awake("+", 24, GraphColors::Grey);
		zoomInButton->floatValue = 0.25;
		zoomInButton->onClickMethod = &ZoomGraphButton;
		TransformSetParent((app::GameObject*)zoomInButton, labelLayout);

		GraphLabel* zoomOutButton = new GraphLabel();
		zoomOutButton->app::MonoBehaviour::klass = (app::MonoBehaviour__Class*)class1;
		AllDefaultGraphLabels.push_back(zoomOutButton);

		app::Object__ctor((app::Object*)zoomOutButton, NULL);
		app::Component__ctor((app::Component*)zoomOutButton, NULL);
		app::MonoBehaviour__ctor((app::MonoBehaviour*)zoomOutButton, NULL);
		bloo = string_new("GraphZoomOut");
		app::GameObject__ctor((app::GameObject*)zoomOutButton, bloo, NULL);
		zoomOutButton->Awake("-", 24, GraphColors::Grey);
		zoomOutButton->floatValue = -0.25;
		zoomOutButton->onClickMethod = &ZoomGraphButton;
		TransformSetParent((app::GameObject*)zoomOutButton, labelLayout);

		GraphLabel* closeButton = new GraphLabel();
		closeButton->app::MonoBehaviour::klass = (app::MonoBehaviour__Class*)class1;
		AllDefaultGraphLabels.push_back(closeButton);

		app::Object__ctor((app::Object*)closeButton, NULL);
		app::Component__ctor((app::Component*)closeButton, NULL);
		app::MonoBehaviour__ctor((app::MonoBehaviour*)closeButton, NULL);
		bloo = string_new("Close");
		app::GameObject__ctor((app::GameObject*)closeButton, bloo, NULL);
		closeButton->Awake("Close", 24, GraphColors::Grey);
		closeButton->floatValue = -0.25;
		closeButton->onClickMethod = &CleanUpGraphButton;
		TransformSetParent((app::GameObject*)closeButton, labelLayout);

		app::GameObject* scrollbarObject = DrawUI::Scrollbar(canvasGraphData, "scrollbar", GraphColors::DarkGray, GraphColors::Grey);
		horizontalScrollbar = (app::Scrollbar*)GetComponentByType(scrollbarObject, "UnityEngine.UI", "Scrollbar");

		app::GameObject* scrollbarObjectVertical = DrawUI::Scrollbar(canvasGraphData, "scrollbar", GraphColors::DarkGray, GraphColors::Grey, false);
		verticalScrollbar = (app::Scrollbar*)GetComponentByType(scrollbarObjectVertical, "UnityEngine.UI", "Scrollbar");
		app::Scrollbar_set_value(verticalScrollbar, 0.5f, NULL);

		//app::GameObject* dropdown = DrawUI::Dropdown("Test");

		TransformSetPosition(masterCanvas, tem::Vector3(0.0f, 0.0f, 0.0f));

		//TransformSetParent(canvasText, newCanvas);
		//TransformSetParent(graphHorizontalLayout, newCanvas);
		TransformSetParent(canvasVerticalLayout, newCanvas);
		TransformSetParent(scrollbarObjectVertical, canvasVerticalLayout);
		TransformSetParent(rectMask2D, canvasVerticalLayout);
		TransformSetParent(scrollbarObject, canvasVerticalLayout);
		//TransformSetParent(dropdown, canvasVerticalLayout);
		TransformSetParent(canvasGraphBackground, rectMask2D);
		TransformSetParent(canvasGraphData, rectMask2D);
		TransformSetParent(labelLayout, canvasVerticalLayout);
		TransformSetParent(newCanvas, masterCanvas);
		TransformSetParent(eventSystem, masterCanvas);
		//TransformSetParent((GameObject*)graphLabelEvent, newCanvas);

		//TransformSetPosition(canvasText, tem::Vector3(0, 0, 0.0f));
		//RectTransformSetSize(canvasText, tem::Vector3(200.0f, 400.0f, 0));

		float newGraphWidth = (float)GraphWidth / 2.0f;
		float newGraphHeight = (float)GraphHeight / 2.0f;

		RectTransformSetMinMax(newCanvas, tem::Vector2(0, 0), tem::Vector2(0, 0));
		RectTransformSetPivot(newCanvas, tem::Vector2(0.5f, 0.5f));

		//RectTransformSetWidthHeight(rectMask2D, newGraphWidth, newGraphHeight);
		RectTransformSetPivot(rectMask2D, tem::Vector2(0, 0));
		RectTransformSetMinMax(rectMask2D, tem::Vector2(0.5f, 0.5f), tem::Vector2(0.5f, 0.5f));
		//TransformSetPosition(rectMask2D, tem::Vector3(TransformGetPosition(newCanvas)));
		RectTransformSetSize(rectMask2D, tem::Vector2(GraphWidth, GraphHeight));
		TransformSetLocalPosition(rectMask2D, tem::Vector3(0, 0, 0)); //TransformSetLocalPosition(rectMask2D, tem::Vector3(newGraphWidth * -1, 0, 0));
		//TransformSetLocalPosition(rectMask2D, tem::Vector3(newGraphWidth * - 1, newGraphHeight * -1, 0));
		TransformSetScale(rectMask2D, tem::Vector3(1, 1, 1));

		RectTransformSetPivot(canvasGraphBackground, tem::Vector2(0.0f, 0.0f));
		RectTransformSetMinMax(canvasGraphBackground, tem::Vector2(0.5f, 0.5f), tem::Vector2(0.5f, 0.5f));
		//TransformSetPosition(canvasGraphBackground, tem::Vector3(0, 0, 0.0f));
		RectTransformSetSize(canvasGraphBackground, tem::Vector2(GraphWidth, GraphHeight));
		TransformSetLocalPosition(canvasGraphBackground, tem::Vector3(0.0f, 0.0f, 0.0f));
		//TransformSetLocalPosition(canvasGraphBackground, tem::Vector3(newGraphWidth / 2, newGraphHeight / 2, 0));
		TransformSetScale(canvasGraphBackground, tem::Vector3(1, 1, 1));

		RectTransformSetPivot(canvasGraphData, tem::Vector2(0.0f, 0.0f));
		RectTransformSetMinMax(canvasGraphData, tem::Vector2(0.5f, 0.5f), tem::Vector2(0.5f, 0.5f));
		//TransformSetPosition(canvasGraphData, tem::Vector3(0, 0, 0.0f));// tem::Vector3(newGraphWidth / 2, newGraphHeight / 2, 0));
		RectTransformSetSize(canvasGraphData, tem::Vector2(width, GraphHeight));
		TransformSetLocalPosition(canvasGraphData, tem::Vector3(0.0f, 0.0f, 0.0f));
		//TransformSetLocalPosition(canvasGraphData, tem::Vector3(newGraphWidth / 2, newGraphHeight / 2, 0));
		//TransformSetLocalPosition(canvasGraphData, tem::Vector3(newGraphWidth / 2, newGraphHeight / 2, 0));
		TransformSetScale(canvasGraphData, tem::Vector3(1, 1, 1));

		//TransformSetPosition(labelLayout, tem::Vector3(0, 0, 0.0f));
		RectTransformSetSize(labelLayout, tem::Vector2(900.0f, 32.0f));
		TransformSetLocalPosition(labelLayout, tem::Vector3(0.0f, 250.0f, 0.0f));
		TransformSetScale(labelLayout, tem::Vector3(1, 1, 1));

		//TransformSetLocalPosition(graphHorizontalLayout, tem::Vector3(0, 0, 0.0f));

		//RectTransformSetMinMax(canvasVerticalLayout, tem::Vector3(0.5, 1, 0), tem::Vector3(0.5, 1, 0));
		RectTransformSetPivot(canvasVerticalLayout, tem::Vector2(0.5f, -0.5f));
		//TransformSetPosition(canvasVerticalLayout, tem::Vector3(0, 0, 0.0f));
		//RectTransformSetAnchoredPosition(canvasVerticalLayout, tem::Vector3(0, 0, 0));
		TransformSetLocalPosition(canvasVerticalLayout, tem::Vector3(0.0f, 0.0f, 0.0f));// tem::Vector3(TransformGetPosition(newCanvas)));
		RectTransformSetSize(canvasVerticalLayout, tem::Vector2(GraphWidth, GraphHeight + 400));
		TransformSetLocalPosition(canvasVerticalLayout, tem::Vector3(0.0f, 0.0f, 0.0f));

		app::Transform* dataTransform = app::GameObject_get_transform(canvasGraphData, NULL);

		//app::Scrollbar* scrollRect = (app::Scrollbar*)app::GameObject_AddComponent((app::GameObject*)canvasGraphData, scrollType, NULL);
		//TransformSetPosition(canvasGraphData, tem::Vector3(0.0f, 0.0f, 0.0f));

		RectTransformSetPivot(canvasGraphData, tem::Vector2(0.0f, 0.0f));
		RectTransformSetSize(canvasGraphData, tem::Vector2(width, GraphHeight));
		//RectTransformSetMinMax(canvasGraphData, tem::Vector3(0.0, 0.0, 0), tem::Vector3(0.0f, 0.0f, 0));
		TransformSetLocalPosition(canvasGraphData, tem::Vector3(0.0f, 0.0f, 0.0f));
		app::RectTransform_set_anchoredPosition((app::RectTransform*)dataTransform, ToVector2(0.0f, 0.0f), NULL);
		app::RectTransform_set_sizeDelta((app::RectTransform*)dataTransform, ToVector2(static_cast<float>(width), static_cast<float>(GraphHeight)), NULL);

		/*auto rectcc = GetClass<>("UnityEngine", "Rect");
		app::Rect* rect = (app::Rect*)il2cpp_object_new((Il2CppClass*)rectcc);
		app::RectTransform_get_rect_Injected((app::RectTransform*)dataTransform, rect, NULL);
		rect->m_Width = 100;//rect->m_Height = 0;*/

		app::GameObject_SetActiveRecursively(masterCanvas, true, NULL);
		app::GameObject_SetMoonReadyToHierarchy(masterCanvas, true, NULL);
	}
}

void Graph::GetShader()
{
	std::vector<std::string> scenePath = { "raceData", "raceStop", "art", "guideStoneSetup", "raceMarkerEnd", "body" };
	app::GameObject* foundObject = GetComponentByScenePath("inkwaterMarshRaceSetups", scenePath);

	app::Type* type45 = GetType("UnityEngine", "MeshFilter");
	app::Component_1__Array* components = app::GameObject_GetComponentsInChildren_1(foundObject, type45, true, NULL);

	type45 = GetType("UnityEngine", "MeshRenderer");
	app::Component_1__Array* componentsRenderers = app::GameObject_GetComponentsInChildren_1(foundObject, type45, true, NULL);

	std::vector<std::string> objectNames;
	std::vector< app::MeshFilter*> meshFilters;
	for (int i = 0; i < components->max_length; i++)
	{
		app::GameObject* gamyobj = app::Component_1_get_gameObject(components->vector[i], NULL);
		app::String* name = app::Object_1_get_name((app::Object_1*)gamyobj, NULL);
		std::string nameS = sutil::convert_csstring(name);
		objectNames.push_back(nameS);
		meshFilters.push_back((app::MeshFilter*)components->vector[i]);
	}

	std::vector<app::MeshRenderer*> meshRenderers;
	for (int i = 0; i < componentsRenderers->max_length; i++)
	{
		app::GameObject* gamyobj = app::Component_1_get_gameObject(componentsRenderers->vector[i], NULL);
		app::String* name = app::Object_1_get_name((app::Object_1*)gamyobj, NULL);
		std::string nameS = sutil::convert_csstring(name);
		objectNames.push_back(nameS);
		meshRenderers.push_back((app::MeshRenderer*)componentsRenderers->vector[i]);
	}

	DataGraphColorMaterial = app::Renderer_GetMaterial((app::Renderer*)meshRenderers[0], NULL);
}

void Graph::ClickEvent(void* __this)
{
	for (int i = 0; i < AllGraphLabels.size(); i++)
	{
		GraphLabel* graphLabel = AllGraphLabels[i];
		if (graphLabel != nullptr && graphLabel->onClickMethod != nullptr && graphLabel->button == __this)
		{
			graphLabel->onClickMethod(graphLabel);
		}
	}

	for (int i = 0; i < AllDefaultGraphLabels.size(); i++)
	{
		GraphLabel* graphLabel = AllDefaultGraphLabels[i];
		if (graphLabel != nullptr && graphLabel->onClickMethod != nullptr && graphLabel->button == __this)
		{
			graphLabel->onClickMethod(graphLabel);
		}
	}
}

void Graph::Zoom(float zoomValue)
{
	tem::Vector3 newScale = TransformGetScale(canvasGraphData);
	//TransformSetScale(canvasGraphBackground, newScale.Y+zoomValue);
	//newScale.Y += zoomValue;
	newScale += zoomValue;
	TransformSetScale(canvasGraphData, newScale);
	TransformSetScale(canvasGraphBackground, newScale);
}

FloatData::FloatData(std::vector<float> data, app::Color color, float scaleY, float scaleX, float inMin, float inMax)
{
	Data = data;
	Color = color;
	yScale = scaleY;
	xScale = scaleX;
	InMin = inMin;
	InMax = inMax;
}

void GraphLabel::Awake(const std::string& text, int fontSize, app::Color color)
{
	app::Type* textType = GetType("UnityEngine.UI", "Text");

	app::GameObject_SetActive((app::GameObject*)this, true, NULL);
	button = DrawUI::Button((app::GameObject*)this, text, fontSize, color);
	textComponent = (app::Text*)app::GameObject_GetComponentInChildren_1((app::GameObject*)this, textType, NULL);
	//textComponent = (Text*)GameObject_GetComponent((GameObject*)this, textType, NULL);
	app::Button_ButtonClickedEvent* clickEvent = app::Button_get_onClick(button, NULL);
}

static void DrawGraphLinesButton(GraphLabel* __this)
{
	if (Graph::Instance != nullptr)
		Graph::Instance->ReDrawGraphLines(__this->intValue);
}

static void ZoomGraphButton(GraphLabel* __this)
{
	if (Graph::Instance != nullptr)
		Graph::Instance->Zoom(__this->floatValue);
}

static void CleanUpGraphButton(GraphLabel* __this)
{
	if (Graph::Instance != nullptr)
		Graph::Instance->CloseGraph();
}