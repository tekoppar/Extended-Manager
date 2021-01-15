#pragma once

#ifndef _UIEVENTS_H
#define _UIEVENTS_H

#include "Global.h"

namespace tem {
	struct MouseEvents {
		bool MouseLeftWasUp = false;
		bool MouseRightWasUp = false;
	};

	class UIEvents : public Global
	{
	public:
		static UIEvents* Instance;
		static bool IsOverUIElement;
		
		std::unordered_map<void*, tem::OnEvents*> OnClickEvents;
		app::GameObject* CanvasObject = nullptr;
		MouseEvents MouseState;

		void AddObjectToCanvas(app::GameObject* object);

		UIEvents();

		virtual void Cleanup() override;
		virtual void Update() override;
	private:
		app::GameObject* EditorToolbar = nullptr;
		app::EventSystem* EventSystem = nullptr;
		app::StandaloneInputModule* StandaloneInputModule = nullptr;
		app::GameObject* CurrentHoveredObject = nullptr;
		std::uintptr_t OldHoveredEvent = 0x0;
	};

	typedef void(__thiscall* tOnPointerClick)(void* __this);
}

#endif