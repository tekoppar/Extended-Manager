#pragma once

class Global
{
public:
	virtual void Update() = 0;
	virtual void Cleanup() = 0;
};

namespace tem {
	enum class EventType {
		OnClick = 0,
		LeftMouseDown = 1,
		RightMouseDown = 2,
		MiddleMouseDown = 3,
		LeftMouseUp = 4,
		RightMouseUp = 5,
		MiddleMouseUp = 6,
		MouseMove = 7,
		MouseEnter = 8,
		MouseLeave = 9,
		KeyPressedDelete = 10,
		PointerEvent = 11
	};

	struct RegisterEvent {
		std::vector<uint8_t> Events = std::vector<uint8_t>(10, 0);
	};

	class OnEvents
	{
	public:
		//RegisterEvent Events;

		virtual void OnEvent(EventType type, void* ptr) = 0;
	};
}