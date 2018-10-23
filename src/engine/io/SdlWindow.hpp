#pragma once
#include "../../../include/ari/Engine.hpp"
#include "../../../include/ari/io/IoEvents.hpp"
#include "bx/handlealloc.h"
#include "bx/mutex.h"
#include <SDL2/SDL.h>

namespace ari
{
	struct GamepadSDL
	{
		GamepadSDL();

		void create(const SDL_JoyDeviceEvent& _jev);

		void create(const SDL_ControllerDeviceEvent& _cev);

		void update(EventQueue& _eventQueue, WindowHandle _handle, GamepadHandle _gamepad, 
			GamepadAxis::Enum _axis, int32_t _value);

		void destroy();

		bool filter(GamepadAxis::Enum _axis, int32_t* _value);
		int32_t m_value[GamepadAxis::Count];
		int32_t m_deadzone[GamepadAxis::Count];

		SDL_Joystick*       m_joystick;
		SDL_GameController* m_controller;
		//		SDL_Haptic*         m_haptic;
		SDL_JoystickID      m_jid;
	};

	class SdlWindow
	{
		friend class Engine;

	public:

		bool Init(InitParams& params);

		void setWindowSize(WindowHandle _handle, uint32_t _width, uint32_t _height, bool _force);

		bool Run();

		static void setMouseLock(WindowHandle _handle, bool _lock);

		bool processEvents(uint32_t& _width, uint32_t& _height, uint32_t& _debug, uint32_t& _reset,
			MouseState* _mouse);

	protected:


		WindowHandle findHandle(uint32_t _windowId);

		WindowHandle findHandle(SDL_Window * _window);

		GamepadHandle findGamepad(int _jid);

		bx::HandleAllocT<ARI_CONFIG_MAX_WINDOW> m_windowAlloc;
		SDL_Window* m_window[ARI_CONFIG_MAX_WINDOW];
		uint32_t m_flags[ARI_CONFIG_MAX_WINDOW];
		bx::HandleAllocT<ENTRY_CONFIG_MAX_GAMEPADS> m_gamepadAlloc;
		GamepadSDL m_gamepad[ENTRY_CONFIG_MAX_GAMEPADS];
		InitParams m_params;
		bx::Mutex m_lock;
		int m_mx, m_my, m_mz;
		EventQueue	m_eventQueue;
		WindowHandle defaultWindow;

	}; // SdlWindow

} // ari
