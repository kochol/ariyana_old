#include "WindowWin32.hpp"

#if BX_PLATFORM_WINDOWS

#include "bgfx/platform.h"
#include <map>
#include "bx/bx.h"
#include <bx/math.h>

#include <windowsx.h>
#include <Xinput.h>

#ifndef XINPUT_GAMEPAD_GUIDE
#	define XINPUT_GAMEPAD_GUIDE 0x400
#endif // XINPUT_GAMEPAD_GUIDE

#ifndef XINPUT_DLL_A
#	define XINPUT_DLL_A "Xinput.dll"
#endif // XINPUT_DLL_A

static std::map<uintptr_t, ari::WindowWin32*> s_windows;

ari::WindowWin32* GetWindowByHwnd(HWND _hwnd)
{
	auto it = s_windows.find((uintptr_t)_hwnd);
	if (it == s_windows.end())
		return nullptr;

	return it->second;
}

LRESULT CALLBACK wndProc(HWND _hwnd, UINT _id, WPARAM _wparam, LPARAM _lparam)
{
	ari::WindowWin32* win = GetWindowByHwnd(_hwnd);
	if (!win)
	{
		return DefWindowProc(_hwnd, _id, _wparam, _lparam);
	}

	return win->Process(_hwnd, _id, _wparam, _lparam);
}

namespace ari
{
	enum
	{
		WM_USER_WINDOW_DESTROY = WM_USER
	};

	struct TranslateKeyModifiers
	{
		int m_vk;
		Modifier::Enum m_modifier;
	};

	static const TranslateKeyModifiers s_translateKeyModifiers[8] =
	{
		{ VK_LMENU,    Modifier::LeftAlt    },
		{ VK_RMENU,    Modifier::RightAlt   },
		{ VK_LCONTROL, Modifier::LeftCtrl   },
		{ VK_RCONTROL, Modifier::RightCtrl  },
		{ VK_LSHIFT,   Modifier::LeftShift  },
		{ VK_RSHIFT,   Modifier::RightShift },
		{ VK_LWIN,     Modifier::LeftMeta   },
		{ VK_RWIN,     Modifier::RightMeta  },
	};

	static uint8_t translateKeyModifiers()
	{
		uint8_t modifiers = 0;
		for (uint32_t ii = 0; ii < BX_COUNTOF(s_translateKeyModifiers); ++ii)
		{
			const TranslateKeyModifiers& tkm = s_translateKeyModifiers[ii];
			modifiers |= 0 > GetKeyState(tkm.m_vk) ? tkm.m_modifier : Modifier::None;
		}
		return modifiers;
	}

	static uint8_t s_translateKey[256];

	static Key::Enum translateKey(WPARAM _wparam)
	{
		return (Key::Enum)s_translateKey[_wparam & 0xff];
	}

	WindowWin32::WindowWin32(Type _type): PlatformWindow(_type)
	{
		if (_type == Type::Main)
		{
			bx::memSet(s_translateKey, 0, sizeof(s_translateKey));
			s_translateKey[VK_ESCAPE] = Key::Esc;
			s_translateKey[VK_RETURN] = Key::Return;
			s_translateKey[VK_TAB] = Key::Tab;
			s_translateKey[VK_BACK] = Key::Backspace;
			s_translateKey[VK_SPACE] = Key::Space;
			s_translateKey[VK_UP] = Key::Up;
			s_translateKey[VK_DOWN] = Key::Down;
			s_translateKey[VK_LEFT] = Key::Left;
			s_translateKey[VK_RIGHT] = Key::Right;
			s_translateKey[VK_INSERT] = Key::Insert;
			s_translateKey[VK_DELETE] = Key::Delete;
			s_translateKey[VK_HOME] = Key::Home;
			s_translateKey[VK_END] = Key::End;
			s_translateKey[VK_PRIOR] = Key::PageUp;
			s_translateKey[VK_NEXT] = Key::PageDown;
			s_translateKey[VK_SNAPSHOT] = Key::Print;
			s_translateKey[VK_OEM_PLUS] = Key::Plus;
			s_translateKey[VK_OEM_MINUS] = Key::Minus;
			s_translateKey[VK_OEM_4] = Key::LeftBracket;
			s_translateKey[VK_OEM_6] = Key::RightBracket;
			s_translateKey[VK_OEM_1] = Key::Semicolon;
			s_translateKey[VK_OEM_7] = Key::Quote;
			s_translateKey[VK_OEM_COMMA] = Key::Comma;
			s_translateKey[VK_OEM_PERIOD] = Key::Period;
			s_translateKey[VK_DECIMAL] = Key::Period;
			s_translateKey[VK_OEM_2] = Key::Slash;
			s_translateKey[VK_OEM_5] = Key::Backslash;
			s_translateKey[VK_OEM_3] = Key::Tilde;
			s_translateKey[VK_F1] = Key::F1;
			s_translateKey[VK_F2] = Key::F2;
			s_translateKey[VK_F3] = Key::F3;
			s_translateKey[VK_F4] = Key::F4;
			s_translateKey[VK_F5] = Key::F5;
			s_translateKey[VK_F6] = Key::F6;
			s_translateKey[VK_F7] = Key::F7;
			s_translateKey[VK_F8] = Key::F8;
			s_translateKey[VK_F9] = Key::F9;
			s_translateKey[VK_F10] = Key::F10;
			s_translateKey[VK_F11] = Key::F11;
			s_translateKey[VK_F12] = Key::F12;
			s_translateKey[VK_NUMPAD0] = Key::NumPad0;
			s_translateKey[VK_NUMPAD1] = Key::NumPad1;
			s_translateKey[VK_NUMPAD2] = Key::NumPad2;
			s_translateKey[VK_NUMPAD3] = Key::NumPad3;
			s_translateKey[VK_NUMPAD4] = Key::NumPad4;
			s_translateKey[VK_NUMPAD5] = Key::NumPad5;
			s_translateKey[VK_NUMPAD6] = Key::NumPad6;
			s_translateKey[VK_NUMPAD7] = Key::NumPad7;
			s_translateKey[VK_NUMPAD8] = Key::NumPad8;
			s_translateKey[VK_NUMPAD9] = Key::NumPad9;
			s_translateKey[uint8_t('0')] = Key::Key0;
			s_translateKey[uint8_t('1')] = Key::Key1;
			s_translateKey[uint8_t('2')] = Key::Key2;
			s_translateKey[uint8_t('3')] = Key::Key3;
			s_translateKey[uint8_t('4')] = Key::Key4;
			s_translateKey[uint8_t('5')] = Key::Key5;
			s_translateKey[uint8_t('6')] = Key::Key6;
			s_translateKey[uint8_t('7')] = Key::Key7;
			s_translateKey[uint8_t('8')] = Key::Key8;
			s_translateKey[uint8_t('9')] = Key::Key9;
			s_translateKey[uint8_t('A')] = Key::KeyA;
			s_translateKey[uint8_t('B')] = Key::KeyB;
			s_translateKey[uint8_t('C')] = Key::KeyC;
			s_translateKey[uint8_t('D')] = Key::KeyD;
			s_translateKey[uint8_t('E')] = Key::KeyE;
			s_translateKey[uint8_t('F')] = Key::KeyF;
			s_translateKey[uint8_t('G')] = Key::KeyG;
			s_translateKey[uint8_t('H')] = Key::KeyH;
			s_translateKey[uint8_t('I')] = Key::KeyI;
			s_translateKey[uint8_t('J')] = Key::KeyJ;
			s_translateKey[uint8_t('K')] = Key::KeyK;
			s_translateKey[uint8_t('L')] = Key::KeyL;
			s_translateKey[uint8_t('M')] = Key::KeyM;
			s_translateKey[uint8_t('N')] = Key::KeyN;
			s_translateKey[uint8_t('O')] = Key::KeyO;
			s_translateKey[uint8_t('P')] = Key::KeyP;
			s_translateKey[uint8_t('Q')] = Key::KeyQ;
			s_translateKey[uint8_t('R')] = Key::KeyR;
			s_translateKey[uint8_t('S')] = Key::KeyS;
			s_translateKey[uint8_t('T')] = Key::KeyT;
			s_translateKey[uint8_t('U')] = Key::KeyU;
			s_translateKey[uint8_t('V')] = Key::KeyV;
			s_translateKey[uint8_t('W')] = Key::KeyW;
			s_translateKey[uint8_t('X')] = Key::KeyX;
			s_translateKey[uint8_t('Y')] = Key::KeyY;
			s_translateKey[uint8_t('Z')] = Key::KeyZ;
		}
	}

	WindowWin32::~WindowWin32()
	{
		DestroyWindow(m_hwnd);
	}

	bool WindowWin32::Run()
	{
		// TODO: s_xinput.update(m_eventQueue);
		//WaitForInputIdle(GetCurrentProcess(), 16);

		MSG msg;
		msg.message = WM_NULL;
		while (0 != PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return !m_exit;
	}

	void WindowWin32::Show(bool _show)
	{
		ShowWindow(m_hwnd, _show? SW_SHOW: SW_HIDE);
	}

	void WindowWin32::SetMousePos(int _x, int _y)
	{
		POINT pt = { _x, _y };
		ClientToScreen(m_hwnd, &pt);
		SetCursorPos(pt.x, pt.y);
	}

	void WindowWin32::SetTitle(const char* _title)
	{
		SetWindowTextA(m_hwnd, _title);
	}

	void WindowWin32::SetFlags(uint32_t _flags, bool _addFlags)
	{
		if (_addFlags)
		{
			m_flags |= _flags;
		}
		else
		{
			m_flags &= ~_flags;
		}
	}

	void WindowWin32::GetPos(int & _x, int & _y)
	{
		RECT r;
		GetWindowRect(m_hwnd, &r);
		_x = r.left;
		_y = r.top;
	}

	void WindowWin32::SetPos(int _x, int _y)
	{
		SetWindowPos(m_hwnd, 0, _x, _y, 0, 0
			, SWP_NOACTIVATE
			| SWP_NOOWNERZORDER
			| SWP_NOSIZE
		);
	}

	void WindowWin32::SetSize(int _width, int _height)
	{
		Adjust(_width, _height, true);
	}

	void WindowWin32::SetMouseLock(bool _lock)
	{
		if (_lock)
		{
			m_mx = m_width / 2;
			m_my = m_height / 2;
			ShowCursor(false);
			SetMousePos(m_mx, m_my);
		}
		else
		{
			SetMousePos(m_mx, m_my);
			ShowCursor(true);
		}

		m_mouseLock = _lock;

	}

	void WindowWin32::ToggleFrame()
	{
		if (m_frame)
		{
			m_oldWidth = m_width;
			m_oldHeight = m_height;
		}
		Adjust(m_oldWidth, m_oldHeight, !m_frame);
	}

	bool WindowWin32::IsWindowMaximized()
	{
		return IsZoomed(m_hwnd) == TRUE;
	}

	void WindowWin32::SetWindowMaximized(bool _maximize)
	{
		if (_maximize)
			ShowWindow(m_hwnd, SW_MAXIMIZE);
		else
			ShowWindow(m_hwnd, SW_RESTORE);
	}

	bool WindowWin32::IsWindowMinimized()
	{
		return IsIconic(m_hwnd) == TRUE;
	}

	void WindowWin32::SetWindowMinimized(bool _minimize)
	{
		if (_minimize)
			ShowWindow(m_hwnd, SW_MINIMIZE);
		else if (IsIconic(m_hwnd))
			ShowWindow(m_hwnd, SW_RESTORE);
	}

	bool WindowWin32::Init(int _posx, int _posy, int _width, int _height, uint32_t _flags, const char * _title)
	{
		SetDllDirectoryA(".");

		// TODO: Init xinput
//		s_xinput.init();

		HINSTANCE instance = (HINSTANCE)GetModuleHandle(NULL);

		if (m_Type == Type::Main)
		{
			WNDCLASSEXA wnd;
			bx::memSet(&wnd, 0, sizeof(wnd));
			wnd.cbSize = sizeof(wnd);
			wnd.style = CS_HREDRAW | CS_VREDRAW;
			wnd.lpfnWndProc = wndProc;
			wnd.hInstance = instance;
			wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);
			wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
			wnd.lpszClassName = "Ariyana";
			wnd.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
			RegisterClassExA(&wnd);
		}

		m_hwnd = CreateWindowExA(
			WS_EX_ACCEPTFILES
			, "Ariyana"
			, _title
			, WS_OVERLAPPEDWINDOW | WS_VISIBLE
			, _posx
			, _posy
			, _width
			, _height
			, NULL
			, NULL
			, instance
			, this
		);
		s_windows[(uintptr_t)m_hwnd] = this;

		m_flags = 0
			| ENTRY_WINDOW_FLAG_ASPECT_RATIO
			| ENTRY_WINDOW_FLAG_FRAME
			;

		if (m_Type == Type::Main)
		{
			bgfx::PlatformData pd;
			bx::memSet(&pd, 0, sizeof(pd));
			pd.nwh = m_hwnd;
			bgfx::setPlatformData(pd);
		}

		if (m_Type == Type::Main)
			Adjust(_width, _height, true);
		Clear();

		m_width = _width;
		m_height = _height;
		m_oldWidth = _width;
		m_oldHeight = _height;
		m_init = true;
		m_eventQueue.postSizeEvent(m_width, m_height);

		MSG msg;
		msg.message = WM_NULL;
		return true;
	}

	void WindowWin32::Adjust(uint32_t _width, uint32_t _height, bool _windowFrame)
	{
		m_width = _width;
		m_height = _height;
		m_aspectRatio = float(_width) / float(_height);

		ShowWindow(m_hwnd, SW_SHOWNORMAL);
		RECT rect;
		RECT newrect = { 0, 0, (LONG)_width, (LONG)_height };
		DWORD style = WS_POPUP | WS_SYSMENU;

		if (m_frame)
		{
			GetWindowRect(m_hwnd, &m_rect);
			m_style = GetWindowLong(m_hwnd, GWL_STYLE);
		}

		if (_windowFrame)
		{
			rect = m_rect;
			style = m_style;
		}
		else
		{
			HMONITOR monitor = MonitorFromWindow(m_hwnd, MONITOR_DEFAULTTONEAREST);
			MONITORINFO mi;
			mi.cbSize = sizeof(mi);
			GetMonitorInfo(monitor, &mi);
			newrect = mi.rcMonitor;
			rect = mi.rcMonitor;
			m_aspectRatio = float(newrect.right - newrect.left) / float(newrect.bottom - newrect.top);
		}

		SetWindowLong(m_hwnd, GWL_STYLE, style);
		uint32_t prewidth = newrect.right - newrect.left;
		uint32_t preheight = newrect.bottom - newrect.top;
		AdjustWindowRect(&newrect, style, FALSE);
		m_frameWidth = (newrect.right - newrect.left) - prewidth;
		m_frameHeight = (newrect.bottom - newrect.top) - preheight;
		UpdateWindow(m_hwnd);

		if (rect.left == -32000
			|| rect.top == -32000)
		{
			rect.left = 0;
			rect.top = 0;
		}

		int32_t left = rect.left;
		int32_t top = rect.top;
		int32_t width = (newrect.right - newrect.left);
		int32_t height = (newrect.bottom - newrect.top);

		if (!_windowFrame)
		{
			float aspectRatio = 1.0f / m_aspectRatio;
			width = bx::uint32_max(_width / 4, width);
			height = uint32_t(float(width)*aspectRatio);

			left = newrect.left + (newrect.right - newrect.left - width) / 2;
			top = newrect.top + (newrect.bottom - newrect.top - height) / 2;
		}

		SetWindowPos(m_hwnd
			, HWND_TOP
			, left
			, top
			, width
			, height
			, SWP_SHOWWINDOW
		);

		ShowWindow(m_hwnd, SW_RESTORE);

		m_frame = _windowFrame;

	} // Adjust
	
	void WindowWin32::Clear()
	{
		RECT rect;
		GetWindowRect(m_hwnd, &rect);
		HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
		HDC hdc = GetDC(m_hwnd);
		SelectObject(hdc, brush);
		FillRect(hdc, &rect, brush);

	} // Clear

	static void mouseCapture(HWND _hwnd, bool _capture)
	{
		if (_capture)
		{
			SetCapture(_hwnd);
		}
		else
		{
			ReleaseCapture();
		}
	}

	LRESULT WindowWin32::Process(HWND _hwnd, UINT _id, WPARAM _wparam, LPARAM _lparam)
	{
		if (m_init)
		{
			switch (_id)
			{
			case WM_USER_WINDOW_DESTROY:
			{
				m_eventQueue.postWindowEvent();
				DestroyWindow(m_hwnd);
				m_hwnd = nullptr;

				m_exit = true;
				m_eventQueue.postExitEvent();
			}
			break;

			case WM_DESTROY:
				break;

			case WM_QUIT:
			case WM_CLOSE:
				PostMessage(m_hwnd, WM_USER_WINDOW_DESTROY, 0, 0);
				// Don't process message. Window will be destroyed later.
				return 0;

			case WM_SIZING:
			{
				if (ENTRY_WINDOW_FLAG_ASPECT_RATIO & m_flags)
				{
					RECT& rect = *(RECT*)_lparam;
					uint32_t width = rect.right - rect.left - m_frameWidth;
					uint32_t height = rect.bottom - rect.top - m_frameHeight;

					// Recalculate size according to aspect ratio
					switch (_wparam)
					{
					case WMSZ_LEFT:
					case WMSZ_RIGHT:
					{
						float aspectRatio = 1.0f / m_aspectRatio;
						width = bx::uint32_max(800 / 4, width);
						height = uint32_t(float(width)*aspectRatio);
					}
					break;

					default:
					{
						float aspectRatio = m_aspectRatio;
						height = bx::uint32_max(600 / 4, height);
						width = uint32_t(float(height)*aspectRatio);
					}
					break;
					}

					// Recalculate position using different anchor points
					switch (_wparam)
					{
					case WMSZ_TOPLEFT:
						rect.left = rect.right - width - m_frameWidth;
						rect.top = rect.bottom - height - m_frameHeight;
						break;

					case WMSZ_TOP:
					case WMSZ_TOPRIGHT:
						rect.right = rect.left + width + m_frameWidth;
						rect.top = rect.bottom - height - m_frameHeight;
						break;

					case WMSZ_LEFT:
					case WMSZ_BOTTOMLEFT:
						rect.left = rect.right - width - m_frameWidth;
						rect.bottom = rect.top + height + m_frameHeight;
						break;

					default:
						rect.right = rect.left + width + m_frameWidth;
						rect.bottom = rect.top + height + m_frameHeight;
						break;
					}

					m_eventQueue.postSizeEvent(width, height);
				}
			}
			return 0;

			case WM_SIZE:
			{
				uint32_t width = GET_X_LPARAM(_lparam);
				uint32_t height = GET_Y_LPARAM(_lparam);

				m_width = width;
				m_height = height;
				m_eventQueue.postSizeEvent(m_width, m_height);
			}
			break;

			case WM_SYSCOMMAND:
				switch (_wparam)
				{
				case SC_MINIMIZE:
				case SC_RESTORE:
				{
					HWND parent = GetWindow(_hwnd, GW_OWNER);
					if (NULL != parent)
					{
						PostMessage(parent, _id, _wparam, _lparam);
					}
				}
				}
				break;

			case WM_MOUSEMOVE:
			{
				int32_t mx = GET_X_LPARAM(_lparam);
				int32_t my = GET_Y_LPARAM(_lparam);

				if (m_mouseLock)
				{
					mx -= m_mx;
					my -= m_my;

					if (0 == mx
						&& 0 == my)
					{
						break;
					}

					SetMousePos(m_mx, m_my);
				}

				m_eventQueue.postMouseEvent(mx, my, m_mz);
			}
			break;

			case WM_MOUSEWHEEL:
			{
				POINT pt = { GET_X_LPARAM(_lparam), GET_Y_LPARAM(_lparam) };
				ScreenToClient(_hwnd, &pt);
				int32_t mx = pt.x;
				int32_t my = pt.y;
				m_mz += GET_WHEEL_DELTA_WPARAM(_wparam) / WHEEL_DELTA;
				m_eventQueue.postMouseEvent(mx, my, m_mz);
			}
			break;

			case WM_LBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_LBUTTONDBLCLK:
			{
				mouseCapture(_hwnd, _id == WM_LBUTTONDOWN);
				int32_t mx = GET_X_LPARAM(_lparam);
				int32_t my = GET_Y_LPARAM(_lparam);
				m_eventQueue.postMouseEvent(mx, my, m_mz, MouseButton::Left, _id == WM_LBUTTONDOWN);
			}
			break;

			case WM_MBUTTONDOWN:
			case WM_MBUTTONUP:
			case WM_MBUTTONDBLCLK:
			{
				mouseCapture(_hwnd, _id == WM_MBUTTONDOWN);
				int32_t mx = GET_X_LPARAM(_lparam);
				int32_t my = GET_Y_LPARAM(_lparam);
				m_eventQueue.postMouseEvent(mx, my, m_mz, MouseButton::Middle, _id == WM_MBUTTONDOWN);
			}
			break;

			case WM_RBUTTONDOWN:
			case WM_RBUTTONUP:
			case WM_RBUTTONDBLCLK:
			{
				mouseCapture(_hwnd, _id == WM_RBUTTONDOWN);
				int32_t mx = GET_X_LPARAM(_lparam);
				int32_t my = GET_Y_LPARAM(_lparam);
				m_eventQueue.postMouseEvent(mx, my, m_mz, MouseButton::Right, _id == WM_RBUTTONDOWN);
			}
			break;

			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:
			case WM_KEYUP:
			case WM_SYSKEYUP:
			{
				uint8_t modifiers = translateKeyModifiers();
				Key::Enum key = translateKey(_wparam);

				if (Key::Print == key
					&& 0x3 == ((uint32_t)(_lparam) >> 30))
				{
					// VK_SNAPSHOT doesn't generate keydown event. Fire on down event when previous
					// key state bit is set to 1 and transition state bit is set to 1.
					//
					// http://msdn.microsoft.com/en-us/library/windows/desktop/ms646280%28v=vs.85%29.aspx
					m_eventQueue.postKeyEvent(key, modifiers, true);
				}

				m_eventQueue.postKeyEvent(key, modifiers, _id == WM_KEYDOWN || _id == WM_SYSKEYDOWN);
			}
			break;

			case WM_CHAR:
			{
				uint8_t utf8[4] = {};
				uint8_t len = (uint8_t)WideCharToMultiByte(CP_UTF8
					, 0
					, (LPCWSTR)&_wparam
					, 1
					, (LPSTR)utf8
					, BX_COUNTOF(utf8)
					, NULL
					, NULL
				);
				if (0 != len)
				{
					m_eventQueue.postCharEvent(len, utf8);
				}
			}
			break;

			case WM_DROPFILES:
			{
				HDROP drop = (HDROP)_wparam;
				char tmp[bx::kMaxFilePath];
				uint32_t result = DragQueryFileA(drop, 0, tmp, sizeof(tmp));
				BX_UNUSED(result);
				m_eventQueue.postDropFileEvent(tmp);
			}
			break;

			default:
				break;
			}
		}

		return DefWindowProc(_hwnd, _id, _wparam, _lparam);
	}

} // ari

#endif
