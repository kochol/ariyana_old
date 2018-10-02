#include "SdlWindow.hpp"

#include <SDL2/SDL.h>
#include <string>
#include <spdlog/logger.h>

BX_PRAGMA_DIAGNOSTIC_PUSH()
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG("-Wextern-c-compat")
#include <SDL2/SDL_syswm.h>
BX_PRAGMA_DIAGNOSTIC_POP()

#include <bgfx/platform.h>

struct Msg
{
	Msg()
		: m_x(0)
		, m_y(0)
		, m_width(0)
		, m_height(0)
		, m_flags(0)
		, m_flagsEnabled(false)
	{
	}

	int32_t  m_x;
	int32_t  m_y;
	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_flags;
	std::string m_title;
	bool m_flagsEnabled;
};

namespace ari
{
	inline bool sdlSetWindow(SDL_Window* _window)
	{
		SDL_SysWMinfo wmi;
		SDL_VERSION(&wmi.version);
		if (!SDL_GetWindowWMInfo(_window, &wmi))
		{
			return false;
		}

		bgfx::PlatformData pd;
#	if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
		pd.ndt = wmi.info.x11.display;
		pd.nwh = (void*)(uintptr_t)wmi.info.x11.window;
#	elif BX_PLATFORM_OSX
		pd.ndt = NULL;
		pd.nwh = wmi.info.cocoa.window;
#	elif BX_PLATFORM_WINDOWS
		pd.ndt = NULL;
		pd.nwh = wmi.info.win.window;
#	elif BX_PLATFORM_STEAMLINK
		pd.ndt = wmi.info.vivante.display;
		pd.nwh = wmi.info.vivante.window;
#	endif // BX_PLATFORM_
		pd.context = NULL;
		pd.backBuffer = NULL;
		pd.backBufferDS = NULL;
		bgfx::setPlatformData(pd);

		return true;
	}

	static WindowHandle getWindowHandle(const SDL_UserEvent& _uev)
	{
		union { void* p; WindowHandle h; } cast;
		cast.p = _uev.data1;
		return cast.h;
	}

	static uint32_t s_userEventStart;

	enum SDL_USER_WINDOW
	{
		SDL_USER_WINDOW_CREATE,
		SDL_USER_WINDOW_DESTROY,
		SDL_USER_WINDOW_SET_TITLE,
		SDL_USER_WINDOW_SET_FLAGS,
		SDL_USER_WINDOW_SET_POS,
		SDL_USER_WINDOW_SET_SIZE,
		SDL_USER_WINDOW_TOGGLE_FRAME,
		SDL_USER_WINDOW_TOGGLE_FULL_SCREEN,
		SDL_USER_WINDOW_MOUSE_LOCK,
	};

	bool SdlWindow::Init(InitParams & params)
	{
		// Init the SDL
		if (SDL_Init(0 | SDL_INIT_GAMECONTROLLER) < 0)
		{
			Device::GetSingleton().GetLogger()->error("Can't Initialize SDL2.");
			return false;
		}

		m_mx = m_my = 0;
		m_params = params;

		m_windowAlloc.alloc();
		m_window[0] = SDL_CreateWindow("Ariyana"
			, SDL_WINDOWPOS_UNDEFINED
			, SDL_WINDOWPOS_UNDEFINED
			, params.Width
			, params.Height
			, SDL_WINDOW_SHOWN
			| SDL_WINDOW_RESIZABLE
		);

		m_flags[0] = 0
			| ENTRY_WINDOW_FLAG_ASPECT_RATIO
			| ENTRY_WINDOW_FLAG_FRAME
			;

		s_userEventStart = SDL_RegisterEvents(7);

		sdlSetWindow(m_window[0]);
		// Calling this function before bgfx init makes bgfx single threaded.
//		bgfx::renderFrame();

		// Force window resolution...
		WindowHandle defaultWindow = { 0 };
		setWindowSize(defaultWindow, params.Width, params.Height, true);

		SDL_EventState(SDL_DROPFILE, SDL_ENABLE);

		return true;

	} // Init

	WindowHandle SdlWindow::findHandle(uint32_t _windowId)
	{
		SDL_Window* window = SDL_GetWindowFromID(_windowId);
		return findHandle(window);
	}

	WindowHandle SdlWindow::findHandle(SDL_Window* _window)
	{
		bx::MutexScope scope(m_lock);
		for (uint16_t ii = 0, num = m_windowAlloc.getNumHandles(); ii < num; ++ii)
		{
			uint16_t idx = m_windowAlloc.getHandleAt(ii);
			if (_window == m_window[idx])
			{
				WindowHandle handle = { idx };
				return handle;
			}
		}

		WindowHandle invalid = { UINT16_MAX };
		return invalid;
	}

	void SdlWindow::setWindowSize(WindowHandle _handle, uint32_t _width, uint32_t _height, bool _force = false)
	{
		if (_width != m_params.Width
			|| _height != m_params.Height
			|| _force)
		{
			m_params.Width  = _width;
			m_params.Height = _height;

			SDL_SetWindowSize(m_window[_handle.idx], _width, _height);
			//m_eventQueue.postSizeEvent(_handle, _width, _height);
		}
	} // setWindowSize

	bool SdlWindow::Run()
	{
		bool exit = false;
		SDL_Event event;
		bgfx::renderFrame();

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
//				m_eventQueue.postExitEvent();
				exit = true;
				break;

			case SDL_MOUSEMOTION:
			{
				const SDL_MouseMotionEvent& mev = event.motion;
				m_mx = mev.x;
				m_my = mev.y;

				WindowHandle handle = findHandle(mev.windowID);
				if (isValid(handle))
				{
//					m_eventQueue.postMouseEvent(handle, m_mx, m_my, m_mz);
				}
			}
			break;

//			case SDL_MOUSEBUTTONDOWN:
//			case SDL_MOUSEBUTTONUP:
//			{
//				//const SDL_MouseButtonEvent& mev = event.button;
//				//WindowHandle handle = findHandle(mev.windowID);
//				//if (isValid(handle))
//				//{
//				//	MouseButton::Enum button;
//				//	switch (mev.button)
//				//	{
//				//	default:
//				//	case SDL_BUTTON_LEFT:   button = MouseButton::Left;   break;
//				//	case SDL_BUTTON_MIDDLE: button = MouseButton::Middle; break;
//				//	case SDL_BUTTON_RIGHT:  button = MouseButton::Right;  break;
//				//	}
//
//					//m_eventQueue.postMouseEvent(handle
//					//	, mev.x
//					//	, mev.y
//					//	, m_mz
//					//	, button
//					//	, mev.type == SDL_MOUSEBUTTONDOWN
//					//);
//				}
//			}
//			break;
//
//			case SDL_MOUSEWHEEL:
//			{
//				const SDL_MouseWheelEvent& mev = event.wheel;
//				m_mz += mev.y;
//
//				WindowHandle handle = findHandle(mev.windowID);
//				if (isValid(handle))
//				{
//					//m_eventQueue.postMouseEvent(handle, m_mx, m_my, m_mz);
//				}
//			}
//			break;
//
//			case SDL_TEXTINPUT:
//			{
//				const SDL_TextInputEvent& tev = event.text;
//				WindowHandle handle = findHandle(tev.windowID);
//				if (isValid(handle))
//				{
//					//m_eventQueue.postCharEvent(handle, 1, (const uint8_t*)tev.text);
//				}
//			}
//			break;
//
//			case SDL_KEYDOWN:
//			{
//				const SDL_KeyboardEvent& kev = event.key;
//				WindowHandle handle = findHandle(kev.windowID);
//				if (isValid(handle))
//				{
//					uint8_t modifiers = translateKeyModifiers(kev.keysym.mod);
//					Key::Enum key = translateKey(kev.keysym.scancode);
//
//#if 0
//					DBG("SDL scancode %d, key %d, name %s, key name %s"
//						, kev.keysym.scancode
//						, key
//						, SDL_GetScancodeName(kev.keysym.scancode)
//						, SDL_GetKeyName(kev.keysym.scancode)
//					);
//#endif // 0
//
//					/// If you only press (e.g.) 'shift' and nothing else, then key == 'shift', modifier == 0.
//					/// Further along, pressing 'shift' + 'ctrl' would be: key == 'shift', modifier == 'ctrl.
//					if (0 == key && 0 == modifiers)
//					{
//						modifiers = translateKeyModifierPress(kev.keysym.scancode);
//					}
//
//					if (Key::Esc == key)
//					{
//						uint8_t pressedChar[4];
//						pressedChar[0] = 0x1b;
//						//m_eventQueue.postCharEvent(handle, 1, pressedChar);
//					}
//					else if (Key::Return == key)
//					{
//						uint8_t pressedChar[4];
//						pressedChar[0] = 0x0d;
//						//m_eventQueue.postCharEvent(handle, 1, pressedChar);
//					}
//					else if (Key::Backspace == key)
//					{
//						uint8_t pressedChar[4];
//						pressedChar[0] = 0x08;
//						//m_eventQueue.postCharEvent(handle, 1, pressedChar);
//					}
//
//					//m_eventQueue.postKeyEvent(handle, key, modifiers, kev.state == SDL_PRESSED);
//				}
//			}
//			break;
//
//			case SDL_KEYUP:
//			{
//				const SDL_KeyboardEvent& kev = event.key;
//				WindowHandle handle = findHandle(kev.windowID);
//				if (isValid(handle))
//				{
//					uint8_t modifiers = translateKeyModifiers(kev.keysym.mod);
//					Key::Enum key = translateKey(kev.keysym.scancode);
//					//m_eventQueue.postKeyEvent(handle, key, modifiers, kev.state == SDL_PRESSED);
//				}
//			}
//			break;

			case SDL_WINDOWEVENT:
			{
				const SDL_WindowEvent& wev = event.window;
				switch (wev.event)
				{
				case SDL_WINDOWEVENT_RESIZED:
				case SDL_WINDOWEVENT_SIZE_CHANGED:
				{
					WindowHandle handle = findHandle(wev.windowID);
					setWindowSize(handle, wev.data1, wev.data2);
				}
				break;

				case SDL_WINDOWEVENT_SHOWN:
				case SDL_WINDOWEVENT_HIDDEN:
				case SDL_WINDOWEVENT_EXPOSED:
				case SDL_WINDOWEVENT_MOVED:
				case SDL_WINDOWEVENT_MINIMIZED:
				case SDL_WINDOWEVENT_MAXIMIZED:
				case SDL_WINDOWEVENT_RESTORED:
				case SDL_WINDOWEVENT_ENTER:
				case SDL_WINDOWEVENT_LEAVE:
				case SDL_WINDOWEVENT_FOCUS_GAINED:
				case SDL_WINDOWEVENT_FOCUS_LOST:
					break;

				case SDL_WINDOWEVENT_CLOSE:
				{
					WindowHandle handle = findHandle(wev.windowID);
					if (0 == handle.idx)
					{
						//m_eventQueue.postExitEvent();
						exit = true;
					}
				}
				break;
				}
			}
			break;

			//case SDL_JOYAXISMOTION:
			//{
			//	const SDL_JoyAxisEvent& jev = event.jaxis;
			//	GamepadHandle handle = findGamepad(jev.which);
			//	if (isValid(handle))
			//	{
			//		GamepadAxis::Enum axis = translateGamepadAxis(jev.axis);
			//		m_gamepad[handle.idx].update(m_eventQueue, defaultWindow, handle, axis, jev.value);
			//	}
			//}
			//break;

			//case SDL_CONTROLLERAXISMOTION:
			//{
			//	const SDL_ControllerAxisEvent& aev = event.caxis;
			//	GamepadHandle handle = findGamepad(aev.which);
			//	if (isValid(handle))
			//	{
			//		GamepadAxis::Enum axis = translateGamepadAxis(aev.axis);
			//		m_gamepad[handle.idx].update(m_eventQueue, defaultWindow, handle, axis, aev.value);
			//	}
			//}
			//break;

			//case SDL_JOYBUTTONDOWN:
			//case SDL_JOYBUTTONUP:
			//{
			//	const SDL_JoyButtonEvent& bev = event.jbutton;
			//	GamepadHandle handle = findGamepad(bev.which);

			//	if (isValid(handle))
			//	{
			//		Key::Enum key = translateGamepad(bev.button);
			//		if (Key::Count != key)
			//		{
			//			m_eventQueue.postKeyEvent(defaultWindow, key, 0, event.type == SDL_JOYBUTTONDOWN);
			//		}
			//	}
			//}
			//break;

			//case SDL_CONTROLLERBUTTONDOWN:
			//case SDL_CONTROLLERBUTTONUP:
			//{
			//	const SDL_ControllerButtonEvent& bev = event.cbutton;
			//	GamepadHandle handle = findGamepad(bev.which);
			//	if (isValid(handle))
			//	{
			//		Key::Enum key = translateGamepad(bev.button);
			//		if (Key::Count != key)
			//		{
			//			m_eventQueue.postKeyEvent(defaultWindow, key, 0, event.type == SDL_CONTROLLERBUTTONDOWN);
			//		}
			//	}
			//}
			//break;

			//case SDL_JOYDEVICEADDED:
			//{
			//	GamepadHandle handle = { m_gamepadAlloc.alloc() };
			//	if (isValid(handle))
			//	{
			//		const SDL_JoyDeviceEvent& jev = event.jdevice;
			//		m_gamepad[handle.idx].create(jev);
			//		m_eventQueue.postGamepadEvent(defaultWindow, handle, true);
			//	}
			//}
			//break;

			//case SDL_JOYDEVICEREMOVED:
			//{
			//	const SDL_JoyDeviceEvent& jev = event.jdevice;
			//	GamepadHandle handle = findGamepad(jev.which);
			//	if (isValid(handle))
			//	{
			//		m_gamepad[handle.idx].destroy();
			//		m_gamepadAlloc.free(handle.idx);
			//		m_eventQueue.postGamepadEvent(defaultWindow, handle, false);
			//	}
			//}
			//break;

			//case SDL_CONTROLLERDEVICEADDED:
			//{
			//	GamepadHandle handle = { m_gamepadAlloc.alloc() };
			//	if (isValid(handle))
			//	{
			//		const SDL_ControllerDeviceEvent& cev = event.cdevice;
			//		m_gamepad[handle.idx].create(cev);
			//		m_eventQueue.postGamepadEvent(defaultWindow, handle, true);
			//	}
			//}
			//break;

			//case SDL_CONTROLLERDEVICEREMAPPED:
			//{

			//}
			//break;

			//case SDL_CONTROLLERDEVICEREMOVED:
			//{
			//	const SDL_ControllerDeviceEvent& cev = event.cdevice;
			//	GamepadHandle handle = findGamepad(cev.which);
			//	if (isValid(handle))
			//	{
			//		m_gamepad[handle.idx].destroy();
			//		m_gamepadAlloc.free(handle.idx);
			//		m_eventQueue.postGamepadEvent(defaultWindow, handle, false);
			//	}
			//}
			//break;

			//case SDL_DROPFILE:
			//{
			//	const SDL_DropEvent& dev = event.drop;
			//	WindowHandle handle = defaultWindow; //findHandle(dev.windowID);
			//	if (isValid(handle))
			//	{
			//		m_eventQueue.postDropFileEvent(handle, dev.file);
			//		SDL_free(dev.file);
			//	}
			//}
			//break;

			default:
			{
				const SDL_UserEvent& uev = event.user;
				switch (uev.type - s_userEventStart)
				{
				case SDL_USER_WINDOW_CREATE:
				{
					WindowHandle handle = getWindowHandle(uev);
					Msg* msg = (Msg*)uev.data2;

					m_window[handle.idx] = SDL_CreateWindow(msg->m_title.c_str()
						, msg->m_x
						, msg->m_y
						, msg->m_width
						, msg->m_height
						, SDL_WINDOW_SHOWN
						| SDL_WINDOW_RESIZABLE
					);

					m_flags[handle.idx] = msg->m_flags;

					//void* nwh = sdlNativeWindowHandle(m_window[handle.idx]);
					//if (NULL != nwh)
					//{
						//m_eventQueue.postSizeEvent(handle, msg->m_width, msg->m_height);
						//m_eventQueue.postWindowEvent(handle, nwh);
					//}

					delete msg;
				}
				break;

				case SDL_USER_WINDOW_DESTROY:
				{
					WindowHandle handle = getWindowHandle(uev);
					if (isValid(handle))
					{
						//m_eventQueue.postWindowEvent(handle);
						SDL_DestroyWindow(m_window[handle.idx]);
						m_window[handle.idx] = NULL;
					}
				}
				break;

				case SDL_USER_WINDOW_SET_TITLE:
				{
					WindowHandle handle = getWindowHandle(uev);
					Msg* msg = (Msg*)uev.data2;
					if (isValid(handle))
					{
						SDL_SetWindowTitle(m_window[handle.idx], msg->m_title.c_str());
					}
					delete msg;
				}
				break;

				case SDL_USER_WINDOW_SET_FLAGS:
				{
					WindowHandle handle = getWindowHandle(uev);
					Msg* msg = (Msg*)uev.data2;

					if (msg->m_flagsEnabled)
					{
						m_flags[handle.idx] |= msg->m_flags;
					}
					else
					{
						m_flags[handle.idx] &= ~msg->m_flags;
					}

					delete msg;
				}
				break;

				case SDL_USER_WINDOW_SET_POS:
				{
					WindowHandle handle = getWindowHandle(uev);
					Msg* msg = (Msg*)uev.data2;
					SDL_SetWindowPosition(m_window[handle.idx], msg->m_x, msg->m_y);
					delete msg;
				}
				break;

				case SDL_USER_WINDOW_SET_SIZE:
				{
					WindowHandle handle = getWindowHandle(uev);
					Msg* msg = (Msg*)uev.data2;
					if (isValid(handle))
					{
						setWindowSize(handle, msg->m_width, msg->m_height);
					}
					delete msg;
				}
				break;

				case SDL_USER_WINDOW_TOGGLE_FRAME:
				{
					WindowHandle handle = getWindowHandle(uev);
					if (isValid(handle))
					{
						m_flags[handle.idx] ^= ENTRY_WINDOW_FLAG_FRAME;
						SDL_SetWindowBordered(m_window[handle.idx], (SDL_bool)!!(m_flags[handle.idx] & ENTRY_WINDOW_FLAG_FRAME));
					}
				}
				break;

				case SDL_USER_WINDOW_TOGGLE_FULL_SCREEN:
				{
					WindowHandle handle = getWindowHandle(uev);
					m_params.FullScreen = !m_params.FullScreen;
					SDL_SetWindowFullscreen(m_window[handle.idx], m_params.FullScreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
				}
				break;

				case SDL_USER_WINDOW_MOUSE_LOCK:
				{
					SDL_SetRelativeMouseMode(!!uev.code ? SDL_TRUE : SDL_FALSE);
				}
				break;

				default:
					break;
				}
			}
			break;
			}
		}

		return !exit;

	} // Run

} // ari
