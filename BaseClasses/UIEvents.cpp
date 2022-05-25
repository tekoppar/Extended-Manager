#include "pch-il2cpp.h"

#include "il2cpp-appdata.h"
#include "helpers.h"

#include <filesystem>

#include "Adresses.h"
#include "detours.h"
#include "ManagerDef.h"
#include "GraphDrawer.h"
#include "CreateUI.h"
#include "SceneList.h"
#include "TreeItem.h"

#include "UIEvents.h"

namespace tem
{

	tOnPointerClick Real_OnPointerClick;

	void __fastcall My_OnPointerClick(void* __this, int edx)
	{
		/*for (auto& event : tem::UIEvents::Instance->OnClickEvents)
		{
			event->OnEvent(tem::EventType::OnClick, __this);
		}*/

		Real_OnPointerClick(__this);
	}

	tem::UIEvents* tem::UIEvents::Instance;
	bool tem::UIEvents::IsOverUIElement = false;

	tem::UIEvents::UIEvents()
	{
		(*app::DebugMenu__TypeInfo)->static_fields->ShouldKeepImGUIEnabled = true;
		Real_OnPointerClick = tOnPointerClick(Assembly_BaseAddr + 0x01F2BD90); // patch 1.3 0x1F2B430);

		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)Real_OnPointerClick, My_OnPointerClick);
		LONG lError = DetourTransactionCommit();

		if (lError == NO_ERROR)
			sutil::Append("C:\\moon\\manager_error.log", "Read thread detours hooked.\r\n");
		else if (lError == ERROR_INVALID_DATA)
			sutil::Append("C:\\moon\\manager_error.log", "Target function was changed by third party between steps of the transaction.\r\n");
		else if (lError == ERROR_INVALID_OPERATION)
			sutil::Append("C:\\moon\\manager_error.log", "No pending transaction exists.\r\n");
		else
			sutil::Append("C:\\moon\\manager_error.log", "Unkown error:" + std::to_string(lError) + ".\r\n");

		MDV::AllObjectsToCallUpdate.push_back(this);

		CanvasObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
		app::GameObject__ctor(CanvasObject, string_new("EditorCanvas"), NULL);
		app::GameObject_set_layer(CanvasObject, 11, NULL);

		app::Type* CanvasRendererType = GetType("UnityEngine", "CanvasRenderer");
		app::CanvasRenderer* canvasRenderer = (app::CanvasRenderer*)app::GameObject_AddComponent((app::GameObject*)CanvasObject, CanvasRendererType, NULL);

		app::GameObject* newCanvas = CreateNewCanvas();
		app::CanvasScaler* scaler = (app::CanvasScaler*)GetComponentByTypeInChildren(newCanvas, "UnityEngine.UI", "CanvasScaler");
#ifdef _WOTW_PATCH_THREE
		app::CanvasScaler_set_uiScaleMode(scaler, app::CanvasScaler_ScaleMode__Enum::CanvasScaler_ScaleMode__Enum_ScaleWithScreenSize, NULL);
#endif
#ifdef _WOTW_PATCH_TWO
		app::CanvasScaler_set_uiScaleMode(scaler, app::CanvasScaler_ScaleMode__Enum::ScaleWithScreenSize, NULL);
#endif
		app::CanvasScaler_set_referenceResolution(scaler, tem::Vector3::ToVector2(1920, 1080), NULL);
		app::GameObject_set_layer(newCanvas, 11, NULL);

		app::GameObject* eventSystem = DrawUI::EventSystem("EventSystem");
		EventSystem = (app::EventSystem*)GetComponentByType(eventSystem, "UnityEngine.EventSystems", "EventSystem");
#ifdef _WOTW_PATCH_THREE
		EditorToolbar = DrawUI::HorizontalLayoutGroup("HorizontalToolbar", app::TextAnchor__Enum::TextAnchor__Enum_UpperLeft);
#endif
#ifdef _WOTW_PATCH_TWO
		EditorToolbar = DrawUI::HorizontalLayoutGroup("HorizontalToolbar", app::TextAnchor__Enum::UpperLeft);
#endif
		app::GameObject_set_layer(eventSystem, 11, NULL);
		app::GameObject_set_layer(EditorToolbar, 11, NULL);

		TransformSetParent(newCanvas, CanvasObject);
		TransformSetParent(eventSystem, CanvasObject);
		TransformSetParent(EditorToolbar, newCanvas);

		RectTransformSetMinMax(newCanvas, tem::Vector2(0.0f, 1.0f), tem::Vector2(0.0f, 1.0f));
		RectTransformSetPivot(newCanvas, tem::Vector2(0.5f, 0.5f));

		RectTransformSetMinMax(EditorToolbar, tem::Vector2(0.0f, 1.0f), tem::Vector2(0.0f, 1.0f));
		RectTransformSetPivot(EditorToolbar, tem::Vector2(0.0f, 1.0f));
		TransformSetPosition(EditorToolbar, tem::Vector3(0.0f, 0.0f, 0.0f));
		TransformSetLocalPosition(EditorToolbar, tem::Vector3(0.0f, 0.0f, 0.0f));// tem::Vector3(TransformGetPosition(newCanvas)));
		RectTransformSetSize(EditorToolbar, tem::Vector2(400, 32));

		app::GameObject_SetActiveRecursively(CanvasObject, true, NULL);
		app::GameObject_SetMoonReadyToHierarchy(CanvasObject, true, NULL);

		/*app::GameObject* PreviewCanvasObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
		app::GameObject__ctor(PreviewCanvasObject, string_new("PreviewCanvasObject"), NULL);

		app::GameObject* previewRawImageObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
		app::GameObject__ctor(previewRawImageObject, string_new("RawImage"), NULL);

		app::GameObject* previewCanvas = CreateNewCanvas();
		app::Canvas* previewCanvass = (app::Canvas*)GetComponentByTypeInChildren(previewCanvas, "UnityEngine", "Canvas");
		app::CanvasScaler* previewScaler = (app::CanvasScaler*)GetComponentByTypeInChildren(previewCanvas, "UnityEngine.UI", "CanvasScaler");
		app::CanvasScaler_set_uiScaleMode(previewScaler, app::CanvasScaler_ScaleMode__Enum::CanvasScaler_ScaleMode__Enum_ConstantPixelSize, NULL);
		//app::CanvasScaler_set_referenceResolution(previewScaler, tem::Vector3::ToVector2(1920, 1080), NULL);

		auto Il2ClassRawImage = GetClass("UnityEngine.UI", "RawImage");
		app::Type* rawImageType = GetTypeFromClass(Il2ClassRawImage);
		app::RawImage* previewRawImage = (app::RawImage*)app::GameObject_AddComponent(previewRawImageObject, rawImageType, NULL);
		app::RawImage__ctor(previewRawImage, NULL);

		app::RenderTexture* previewRenderTexture = (app::RenderTexture*)il2cpp_object_new((Il2CppClass*)(*app::RenderTexture__TypeInfo));
		app::RenderTexture__ctor_6(previewRenderTexture, 256, 256, 0, NULL);
		previewRawImage->fields.m_Texture = (app::Texture*)previewRenderTexture;
		app::RawImage_set_texture(previewRawImage, (app::Texture*)previewRenderTexture, NULL);

		app::GameObject* previewCameraObject = (app::GameObject*)il2cpp_object_new((Il2CppClass*)(*app::GameObject__TypeInfo));
		app::GameObject__ctor(previewCameraObject, string_new("Camera"), NULL);

		auto Il2ClassCamera = GetClass("UnityEngine", "Camera");
		app::Type* cameraType = GetTypeFromClass(Il2ClassCamera);
		app::Camera* previewCamera = (app::Camera*)app::GameObject_AddComponent(previewCameraObject, cameraType, NULL);
		app::Camera_set_targetTexture(previewCamera, previewRenderTexture, NULL);
		app::Camera_set_usePhysicalProperties(previewCamera, false, NULL);
		app::Camera_set_fieldOfView(previewCamera, 45, NULL);
		app::Camera_set_farClipPlane(previewCamera, 1000.0f, NULL);
		app::Camera_set_nearClipPlane(previewCamera, 0.3f, NULL);
		app::Camera_set_clearFlags(previewCamera, app::CameraClearFlags__Enum::CameraClearFlags__Enum_Depth, NULL);
		app::Camera_set_cullingMask(previewCamera, -1, NULL);
		app::Camera_set_depth(previewCamera, 50000000, NULL);
		app::Camera_set_rect(previewCamera, tem::Rect(0.0f, 0.0f, 0.25f, 0.25f).ToMoon(), NULL);
		app::Camera_set_pixelRect(previewCamera, tem::Rect(0.0f, 0.0f, 256.0f, 256.0f).ToMoon(), NULL);
		app::Camera__ctor(previewCamera, NULL);

		app::GameObject* rectMask2D = DrawUI::RectMask2D("CanvasMask", 256, 256, 256, 256);
		TransformSetParent(previewCanvas, PreviewCanvasObject);
		TransformSetParent(previewCameraObject, PreviewCanvasObject);
		TransformSetParent(previewRawImageObject, previewCanvas);

		RectTransformSetMinMax(previewCanvas, tem::Vector2(0.0f, 0.0f), tem::Vector2(0.0f, 0.0f));
		RectTransformSetPivot(previewCanvas, tem::Vector2(0.5f, 0.5f));
		RectTransformSetSize(previewCanvas, tem::Vector2(256, 256));

		uintptr_t m_CachedPtr = (uintptr_t)previewCanvass->fields._._._.m_CachedPtr;
		m_CachedPtr = m_CachedPtr + 0x40; //offset 0x40 to m_rendermode
		int* m_rendermode = (int*)m_CachedPtr;
		int newRenderMode = 1;
		*m_rendermode = newRenderMode;

		app::Canvas_set_sortingOrder(previewCanvass, 5000, NULL);
		app::Canvas_set_worldCamera(previewCanvass, previewCamera, NULL);

		app::RawImage_SetNativeSize(previewRawImage, NULL);*/
	}

	void tem::UIEvents::Cleanup()
	{
		this->OnClickEvents.clear();
		app::Object_1_Destroy_1((app::Object_1*)this->StandaloneInputModule, NULL);
		app::Object_1_Destroy_1((app::Object_1*)this->EditorToolbar, NULL);
		app::Object_1_Destroy_1((app::Object_1*)this->EventSystem, NULL);
		app::Object_1_Destroy_1((app::Object_1*)this->CanvasObject, NULL);
		this->StandaloneInputModule = nullptr;
		this->EditorToolbar = nullptr;
		this->EventSystem = nullptr;
		this->CanvasObject = nullptr;

		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(PVOID&)Real_OnPointerClick, My_OnPointerClick);
		DetourTransactionCommit();
	}

	void tem::UIEvents::Update()
	{
		bool isLeftMouseDown = app::Input_GetMouseButton(0, NULL);
		bool isRightMouseDown = app::Input_GetMouseButton(1, NULL);
#ifdef _WOTW_PATCH_THREE
		bool isDeletePressed = app::Input_GetKey(app::KeyCode__Enum::KeyCode__Enum_Delete, NULL);
#endif
#ifdef _WOTW_PATCH_TWO
		bool isDeletePressed = app::Input_GetKey(app::KeyCode__Enum::Delete, NULL);
#endif
		bool movedMouse = false;
		void* clickedObjectPtr = nullptr;
		app::GameObject* mouseEnterObject = nullptr;

		/*tem::Vector3 position = app::MoonInput_get_mousePosition(NULL);
		tem::Vector3 cameraPosition = TransformGetPosition(app::Component_1_get_gameObject((app::Component_1*)MDV::MoonCamera, NULL));
		app::Ray ray = app::Camera_ScreenPointToRay_2(MDV::MoonCamera, tem::Vector3(position.X, position.Y, std::fabs(cameraPosition.Z)).ToMoon(), NULL); //29.0f
		app::RaycastHit hit = app::RaycastHit();
		bool hitSomething = app::Physics_Raycast_14(ray, &hit, 500, NULL);*/

		if (EventSystem != nullptr)
		{
			if (StandaloneInputModule == nullptr)
				StandaloneInputModule = (app::StandaloneInputModule*)EventSystem->fields.m_CurrentInputModule;

			if (StandaloneInputModule != nullptr)
			{
				StandaloneInputModule->fields.m_ForceModuleActive = true;
				app::StandaloneInputModule_Process(StandaloneInputModule, NULL);

				if (StandaloneInputModule->fields.m_InputPointerEvent != nullptr)
				{
					clickedObjectPtr = (void*)StandaloneInputModule->fields.m_InputPointerEvent->fields.m_PointerPress;
					mouseEnterObject = StandaloneInputModule->fields.m_InputPointerEvent->fields._pointerEnter_k__BackingField;
					tem::Vector2 mouseMoveVector = tem::Vector2(StandaloneInputModule->fields.m_LastMousePosition) - tem::Vector2(StandaloneInputModule->fields.m_MousePosition);
					movedMouse = mouseMoveVector > 0.1f || mouseMoveVector < 0.1f;
				}

				if (StandaloneInputModule->fields.m_CurrentFocusedGameObject != nullptr)
				{
					if (CurrentHoveredObject != nullptr && CurrentHoveredObject != StandaloneInputModule->fields.m_CurrentFocusedGameObject)
					{
						if (tem::UIEvents::Instance->OnClickEvents.find(StandaloneInputModule->fields.m_CurrentFocusedGameObject) != tem::UIEvents::Instance->OnClickEvents.end())
							tem::UIEvents::Instance->OnClickEvents[StandaloneInputModule->fields.m_CurrentFocusedGameObject]->OnEvent(tem::EventType::MouseEnter, StandaloneInputModule->fields.m_CurrentFocusedGameObject);

						if (tem::PtrInRange(OldHoveredEvent) == true && tem::UIEvents::Instance->OnClickEvents[reinterpret_cast<void*>(OldHoveredEvent)] == nullptr)
							tem::UIEvents::Instance->OnClickEvents.erase(reinterpret_cast<void*>(OldHoveredEvent));

						if (tem::PtrInRange(OldHoveredEvent) == true && tem::UIEvents::Instance->OnClickEvents.find(reinterpret_cast<void*>(OldHoveredEvent)) != tem::UIEvents::Instance->OnClickEvents.end())
							tem::UIEvents::Instance->OnClickEvents[reinterpret_cast<void*>(OldHoveredEvent)]->OnEvent(tem::EventType::MouseLeave, CurrentHoveredObject);

						tem::OnEvents* event = tem::UIEvents::Instance->OnClickEvents[CurrentHoveredObject];
						OldHoveredEvent = (std::uintptr_t) & event;
						CurrentHoveredObject = StandaloneInputModule->fields.m_CurrentFocusedGameObject;
					}
					else if (CurrentHoveredObject == nullptr)
					{
						if (tem::UIEvents::Instance->OnClickEvents.find(StandaloneInputModule->fields.m_CurrentFocusedGameObject) != tem::UIEvents::Instance->OnClickEvents.end())
						{
							tem::UIEvents::Instance->OnClickEvents[StandaloneInputModule->fields.m_CurrentFocusedGameObject]->OnEvent(tem::EventType::MouseEnter, StandaloneInputModule->fields.m_CurrentFocusedGameObject);
							CurrentHoveredObject = StandaloneInputModule->fields.m_CurrentFocusedGameObject;
						}
					}
				}
				else
				{
					CurrentHoveredObject = nullptr;
					tem::UIEvents::IsOverUIElement = false;
				}
			}
		}

		if (clickedObjectPtr != nullptr && tem::UIEvents::Instance->OnClickEvents.find(clickedObjectPtr) != tem::UIEvents::Instance->OnClickEvents.end())
		{
			tem::OnEvents* event = tem::UIEvents::Instance->OnClickEvents[clickedObjectPtr];

			if (mouseEnterObject != nullptr && (mouseEnterObject->klass->_0.namespaze == "UnityEngine.EventSystems" || mouseEnterObject->klass->_0.namespaze == "UnityEngine.UI"))
				event->OnEvent(tem::EventType::MouseEnter, clickedObjectPtr);
			else
				event->OnEvent(tem::EventType::MouseLeave, clickedObjectPtr);

			if (MouseState.MouseLeftWasUp == true && isLeftMouseDown == true)
				event->OnEvent(tem::EventType::PointerEvent, clickedObjectPtr);
			else if (MouseState.MouseLeftWasUp == false && isLeftMouseDown == false)
				event->OnEvent(tem::EventType::LeftMouseUp, clickedObjectPtr);

			if (MouseState.MouseRightWasUp == true && isRightMouseDown == true)
				event->OnEvent(tem::EventType::PointerEvent, clickedObjectPtr);
			else if (MouseState.MouseRightWasUp == false && isRightMouseDown == false)
				event->OnEvent(tem::EventType::RightMouseUp, clickedObjectPtr);
		}

		for (auto& event : OnClickEvents)
		{
			if (isDeletePressed)
				event.second->OnEvent(tem::EventType::KeyPressedDelete, event.first);
			if (movedMouse)
				event.second->OnEvent(tem::EventType::MouseMove, event.first);

			if (MouseState.MouseLeftWasUp == true && isLeftMouseDown == true)
				event.second->OnEvent(tem::EventType::LeftMouseDown, event.first);
			else if (MouseState.MouseLeftWasUp == false && isLeftMouseDown == false)
				event.second->OnEvent(tem::EventType::LeftMouseUp, event.first);

			if (MouseState.MouseRightWasUp == true && isRightMouseDown == true)
				event.second->OnEvent(tem::EventType::RightMouseDown, event.first);
			else if (MouseState.MouseRightWasUp == false && isRightMouseDown == false)
				event.second->OnEvent(tem::EventType::RightMouseUp, event.first);
		}

		if (MouseState.MouseLeftWasUp == true && isLeftMouseDown == true)
			MouseState.MouseLeftWasUp = false;
		else if (MouseState.MouseLeftWasUp == false && isLeftMouseDown == false)
			MouseState.MouseLeftWasUp = true;

		if (MouseState.MouseRightWasUp == true && isRightMouseDown == true)
			MouseState.MouseRightWasUp = false;
		else if (MouseState.MouseRightWasUp == false && isRightMouseDown == false)
			MouseState.MouseRightWasUp = true;
	}

	void tem::UIEvents::AddObjectToCanvas(app::GameObject* object)
	{
		if (object != nullptr)
			TransformSetParent(object, EditorToolbar);
	}
}