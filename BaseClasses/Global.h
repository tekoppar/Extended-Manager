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

	enum class KeyCode {
		LMOUSE = 0x01,
		RMOUSE = 0x02,
		SPACEBAR = 0x20,
		A = 0x41,
		B = 0x42,
		C = 0x43,
		D = 0x44,
		E = 0x45,
		F = 0x46,
		G = 0x47,
		H = 0x48,
		I = 0x49,
		J = 0x4A,
		K = 0x4B,
		L = 0x4C,
		M = 0x4D,
		N = 0x4E,
		O = 0x4F,
		P = 0x50,
		Q = 0x51,
		R = 0x52,
		S = 0x53,
		T = 0x54,
		U = 0x55,
		V = 0x56,
		W = 0x57,
		X = 0x58,
		Y = 0x59,
		Z = 0x5A,
		LSHIFT = 0xA0
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