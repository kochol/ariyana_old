#pragma once
#include "bx/bx.h"

namespace ari
{
	struct WindowHandle  { uint16_t idx; };
	inline bool isValid(WindowHandle _handle)  { return UINT16_MAX != _handle.idx; }

	struct GamepadHandle { uint16_t idx; };
	inline bool isValid(GamepadHandle _handle) { return UINT16_MAX != _handle.idx; }

	struct MouseButton
	{
		enum Enum
		{
			None,
			Left,
			Middle,
			Right,

			Count
		};
	};

	struct GamepadAxis
	{
		enum Enum
		{
			LeftX,
			LeftY,
			LeftZ,
			RightX,
			RightY,
			RightZ,

			Count
		};
	};

	struct Modifier
	{
		enum Enum
		{
			None       = 0,
			LeftAlt    = 0x01,
			RightAlt   = 0x02,
			LeftCtrl   = 0x04,
			RightCtrl  = 0x08,
			LeftShift  = 0x10,
			RightShift = 0x20,
			LeftMeta   = 0x40,
			RightMeta  = 0x80,
		};
	};

	struct Key
	{
		enum Enum
		{
			None = 0,
			Esc,
			Return,
			Tab,
			Space,
			Backspace,
			Up,
			Down,
			Left,
			Right,
			Insert,
			Delete,
			Home,
			End,
			PageUp,
			PageDown,
			Print,
			Plus,
			Minus,
			LeftBracket,
			RightBracket,
			Semicolon,
			Quote,
			Comma,
			Period,
			Slash,
			Backslash,
			Tilde,
			F1,
			F2,
			F3,
			F4,
			F5,
			F6,
			F7,
			F8,
			F9,
			F10,
			F11,
			F12,
			NumPad0,
			NumPad1,
			NumPad2,
			NumPad3,
			NumPad4,
			NumPad5,
			NumPad6,
			NumPad7,
			NumPad8,
			NumPad9,
			Key0,
			Key1,
			Key2,
			Key3,
			Key4,
			Key5,
			Key6,
			Key7,
			Key8,
			Key9,
			KeyA,
			KeyB,
			KeyC,
			KeyD,
			KeyE,
			KeyF,
			KeyG,
			KeyH,
			KeyI,
			KeyJ,
			KeyK,
			KeyL,
			KeyM,
			KeyN,
			KeyO,
			KeyP,
			KeyQ,
			KeyR,
			KeyS,
			KeyT,
			KeyU,
			KeyV,
			KeyW,
			KeyX,
			KeyY,
			KeyZ,

			GamepadA,
			GamepadB,
			GamepadX,
			GamepadY,
			GamepadThumbL,
			GamepadThumbR,
			GamepadShoulderL,
			GamepadShoulderR,
			GamepadUp,
			GamepadDown,
			GamepadLeft,
			GamepadRight,
			GamepadBack,
			GamepadStart,
			GamepadGuide,

			Count
		};
	};

	struct Suspend
	{
		enum Enum
		{
			WillSuspend,
			DidSuspend,
			WillResume,
			DidResume,

			Count
		};
	};

	const char* getName(Key::Enum _key);

	struct MouseState
	{
		MouseState()
			: m_mx(0)
			, m_my(0)
			, m_mz(0)
		{
			for (unsigned char & m_button : m_buttons)
			{
				m_button = MouseButton::None;
			}
		}

		int32_t m_mx;
		int32_t m_my;
		int32_t m_mz;
		uint8_t m_buttons[MouseButton::Count];
	};

	struct GamepadState
	{
		GamepadState()
		{
			bx::memSet(m_axis, 0, sizeof(m_axis) );
		}

		int32_t m_axis[GamepadAxis::Count];
	};

} // ari