#include "../../../include/ari/io/PlatformWindow.hpp"
#include "../../../include/ari/Engine.hpp"
#include "../../../include/ari/io/Input.hpp"

namespace ari
{
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
