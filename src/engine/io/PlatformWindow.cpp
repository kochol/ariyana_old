#include "../../../include/ari/io/PlatformWindow.hpp"
#include "../../../include/ari/Engine.hpp"
#include "../../../include/ari/io/Input.hpp"

namespace ari
{
	void PlatformWindow::GetSize(int& _width, int& _height)
	{
		_width = m_width;
		_height = m_height;
	}

	void PlatformWindow::AddOnKeyDelegate(DelegateTwoParam<void, Key::Enum, bool>* _pDelegate)
	{
		m_vOnKeys.push_back(_pDelegate);
	}

	void PlatformWindow::RemoveOnKeyDelegate(DelegateTwoParam<void, Key::Enum, bool>* _pDelegate)
	{
		for (auto it = m_vOnKeys.begin(); it != m_vOnKeys.end(); it++)
			if (*it == _pDelegate)
			{
				m_vOnKeys.erase(it);
				return;
			}
	}

	void PlatformWindow::AddOnCharDelegate(DelegateTwoParam<void, uint8_t, uint8_t*>* _pDelegate)
	{
		m_vOnChar.push_back(_pDelegate);
	}

	void PlatformWindow::RemoveOnCharDelegate(DelegateTwoParam<void, uint8_t, uint8_t*>* _pDelegate)
	{
		for (auto it = m_vOnChar.begin(); it != m_vOnChar.end(); it++)
			if (*it == _pDelegate)
			{
				m_vOnChar.erase(it);
				return;
			}
	}

	void PlatformWindow::AddOnMouseButtonDelegate(DelegateTwoParam<void, MouseButton::Enum, bool>* _pDelegate)
	{
		m_vOnMouseButtons.push_back(_pDelegate);
	}

	void PlatformWindow::RemoveOnMouseButtonDelegate(DelegateTwoParam<void, MouseButton::Enum, bool>* _pDelegate)
	{
		for (auto it = m_vOnMouseButtons.begin(); it != m_vOnMouseButtons.end(); it++)
			if (*it == _pDelegate)
			{
				m_vOnMouseButtons.erase(it);
				return;
			}
	}

	void PlatformWindow::AddOnMouseMoveDelegate(DelegateTwoParam<void, int, int>* _pDelegate)
	{
		m_vOnMouseMove.push_back(_pDelegate);
	}

	void PlatformWindow::RemoveOnMouseMoveDelegate(DelegateTwoParam<void, int, int>* _pDelegate)
	{
		for (auto it = m_vOnMouseMove.begin(); it != m_vOnMouseMove.end(); it++)
			if (*it == _pDelegate)
			{
				m_vOnMouseMove.erase(it);
				return;
			}
	}

	void PlatformWindow::AddOnMouseWheelDelegate(DelegateOneParam<void, int>* _pDelegate)
	{
		m_vOnMouseWheel.push_back(_pDelegate);
	}

	void PlatformWindow::RemoveOnMouseWheelDelegate(DelegateOneParam<void, int>* _pDelegate)
	{
		for (auto it = m_vOnMouseWheel.begin(); it != m_vOnMouseWheel.end(); it++)
			if (*it == _pDelegate)
			{
				m_vOnMouseWheel.erase(it);
				return;
			}
	}

	void PlatformWindow::AddOnSizeDelegate(DelegateTwoParam<void, int, int>* _pDelegate)
	{
		m_vOnSize.push_back(_pDelegate);
	}

	void PlatformWindow::RemoveOnSizeDelegate(DelegateTwoParam<void, int, int>* _pDelegate)
	{
		for (auto it = m_vOnSize.begin(); it != m_vOnSize.end(); it++)
			if (*it == _pDelegate)
			{
				m_vOnSize.erase(it);
				return;
			}
	}

	bool PlatformWindow::ProcessEvents(uint32_t & _width, uint32_t & _height, uint32_t & _debug, uint32_t & _reset, MouseState * _mouse)
	{
		g_pEngine->m_debug = _debug;
		g_pEngine->m_reset = _reset;

		const bool mouseLock = inputIsMouseLocked();

		const Event* ev;
		do
		{
			struct SE { const Event* m_ev; SE() : m_ev(poll()) {} ~SE() { if (NULL != m_ev) { release(m_ev); } } } scopeEvent;
			ev = scopeEvent.m_ev;

			if (NULL != ev)
			{
				switch (ev->m_type)
				{
				case Event::Axis:
				{
					const AxisEvent* axis = static_cast<const AxisEvent*>(ev);
					inputSetGamepadAxis(axis->m_gamepad, axis->m_axis, axis->m_value);
				}
				break;

				case Event::Char:
				{
					const CharEvent* chev = static_cast<const CharEvent*>(ev);
					inputChar(chev->m_len, chev->m_char);
				}
				break;

				case Event::Exit:
					return false;

				case Event::Gamepad:
				{
					//						const GamepadEvent* gev = static_cast<const GamepadEvent*>(ev);
					//						DBG("gamepad %d, %d", gev->m_gamepad.idx, gev->m_connected);
				}
				break;

				case Event::Mouse:
				{
					const MouseEvent* mouse = static_cast<const MouseEvent*>(ev);

					inputSetMousePos(mouse->m_mx, mouse->m_my, mouse->m_mz);
					if (!mouse->m_move)
					{
						inputSetMouseButtonState(mouse->m_button, mouse->m_down);
					}

					if (NULL != _mouse
						&& !mouseLock)
					{
						_mouse->m_mx = mouse->m_mx;
						_mouse->m_my = mouse->m_my;
						_mouse->m_mz = mouse->m_mz;
						if (!mouse->m_move)
						{
							_mouse->m_buttons[mouse->m_button] = mouse->m_down;
						}
					}
				}
				break;

				case Event::Key:
				{
					const KeyEvent* key = static_cast<const KeyEvent*>(ev);

					inputSetKeyState(key->m_key, key->m_modifiers, key->m_down);
				}
				break;

				case Event::Size:
				{
					const SizeEvent* size = static_cast<const SizeEvent*>(ev);

					_width = size->m_width;
					_height = size->m_height;
					_reset = !g_pEngine->m_reset; // force reset
				}
				break;

				case Event::Window:
					break;

				case Event::Suspend:
					break;

				case Event::DropFile:
				{
					//					const DropFileEvent* drop = static_cast<const DropFileEvent*>(ev);
										//DBG("%s", drop->m_filePath.get());
				}
				break;

				default:
					break;
				}
			}

			inputProcess();

		} while (NULL != ev);

		if (m_Type == Type::Main
			&& _reset != g_pEngine->m_reset)
		{
			_reset = g_pEngine->m_reset;
			g_pEngine->m_bNeedReset = true;
			inputSetMouseResolution(uint16_t(_width), uint16_t(_height));
		}

		_debug = g_pEngine->m_debug;

		g_pEngine->m_params->Width = _width;
		g_pEngine->m_params->Height = _height;


		return true; // s_exit
	}
} // ari
