#pragma once
#include <cstdint>
#include "IoEnums.hpp"
#include "bx/filepath.h"
#include "bx/spscqueue.h"
#include "../en/EventSubscriber.hpp"

#define ENTRY_IMPLEMENT_EVENT(_class, _type) \
			_class(WindowHandle _handle) : Event(_type, _handle) {}

extern bx::AllocatorI* g_allocator;

namespace ari
{
	struct Event
	{
		enum Enum
		{
			Axis,
			Char,
			Exit,
			Gamepad,
			Key,
			Mouse,
			Size,
			Window,
			Suspend,
			DropFile,
		};

		Event(Enum _type)
			: m_type(_type)
		{
			m_handle.idx = UINT16_MAX;
		}

		Event(Enum _type, WindowHandle _handle)
			: m_type(_type)
			, m_handle(_handle)
		{
		}

		Event::Enum m_type;
		WindowHandle m_handle;
	};

	struct AxisEvent : public Event
	{
		ENTRY_IMPLEMENT_EVENT(AxisEvent, Event::Axis);

		GamepadAxis::Enum m_axis;
		int32_t m_value;
		GamepadHandle m_gamepad;
	};

	struct CharEvent : public Event
	{
		ENTRY_IMPLEMENT_EVENT(CharEvent, Event::Char);

		uint8_t m_len;
		uint8_t m_char[4];
	};

	struct GamepadEvent : public Event
	{
		ENTRY_IMPLEMENT_EVENT(GamepadEvent, Event::Gamepad);

		GamepadHandle m_gamepad;
		bool m_connected;
	};

	struct KeyEvent : public Event
	{
		ENTRY_IMPLEMENT_EVENT(KeyEvent, Event::Key);

		Key::Enum m_key;
		uint8_t m_modifiers;
		bool m_down;
	};

	struct MouseEvent : public Event
	{
		ENTRY_IMPLEMENT_EVENT(MouseEvent, Event::Mouse);

		int32_t m_mx;
		int32_t m_my;
		int32_t m_mz;
		MouseButton::Enum m_button;
		bool m_down;
		bool m_move;
	};

	struct SizeEvent : public Event
	{
		ENTRY_IMPLEMENT_EVENT(SizeEvent, Event::Size);

		uint32_t m_width;
		uint32_t m_height;
	};

	struct WindowEvent : public Event
	{
		ENTRY_IMPLEMENT_EVENT(WindowEvent, Event::Window);

		void* m_nwh;
	};

	struct SuspendEvent : public Event
	{
		ENTRY_IMPLEMENT_EVENT(SuspendEvent, Event::Suspend);

		Suspend::Enum m_state;
	};

	struct DropFileEvent : public Event
	{
		ENTRY_IMPLEMENT_EVENT(DropFileEvent, Event::DropFile);

		bx::FilePath m_filePath;
	};

	const Event* poll();
	const Event* poll(WindowHandle _handle);
	void release(const Event* _event);

	class EventQueue
	{
	public:
		EventQueue()
			: m_queue(g_allocator)
		{
		}

		~EventQueue()
		{
			for (const Event* ev = poll(); NULL != ev; ev = poll() )
			{
				release(ev);
			}
		}

		void postAxisEvent(WindowHandle _handle, GamepadHandle _gamepad, GamepadAxis::Enum _axis, int32_t _value)
		{
			AxisEvent* ev = BX_NEW(g_allocator, AxisEvent)(_handle);
			ev->m_gamepad = _gamepad;
			ev->m_axis    = _axis;
			ev->m_value   = _value;
			m_queue.push(ev);
		}

		void postCharEvent(WindowHandle _handle, uint8_t _len, const uint8_t _char[4])
		{
			CharEvent* ev = BX_NEW(g_allocator, CharEvent)(_handle);
			ev->m_len = _len;
			bx::memCopy(ev->m_char, _char, 4);
			m_queue.push(ev);
		}

		void postExitEvent()
		{
			Event* ev = BX_NEW(g_allocator, Event)(Event::Exit);
			m_queue.push(ev);
		}

		void postGamepadEvent(WindowHandle _handle, GamepadHandle _gamepad, bool _connected)
		{
			GamepadEvent* ev = BX_NEW(g_allocator, GamepadEvent)(_handle);
			ev->m_gamepad   = _gamepad;
			ev->m_connected = _connected;
			m_queue.push(ev);
		}

		void postKeyEvent(WindowHandle _handle, Key::Enum _key, uint8_t _modifiers, bool _down)
		{
			KeyEvent* ev = BX_NEW(g_allocator, KeyEvent)(_handle);
			ev->m_key       = _key;
			ev->m_modifiers = _modifiers;
			ev->m_down      = _down;
			m_queue.push(ev);
		}

		void postMouseEvent(WindowHandle _handle, int32_t _mx, int32_t _my, int32_t _mz)
		{
			MouseEvent* ev = BX_NEW(g_allocator, MouseEvent)(_handle);
			ev->m_mx     = _mx;
			ev->m_my     = _my;
			ev->m_mz     = _mz;
			ev->m_button = MouseButton::None;
			ev->m_down   = false;
			ev->m_move   = true;
			m_queue.push(ev);
		}

		void postMouseEvent(WindowHandle _handle, int32_t _mx, int32_t _my, int32_t _mz, MouseButton::Enum _button, bool _down)
		{
			MouseEvent* ev = BX_NEW(g_allocator, MouseEvent)(_handle);
			ev->m_mx     = _mx;
			ev->m_my     = _my;
			ev->m_mz     = _mz;
			ev->m_button = _button;
			ev->m_down   = _down;
			ev->m_move   = false;
			m_queue.push(ev);
		}

		void postSizeEvent(WindowHandle _handle, uint32_t _width, uint32_t _height)
		{
			SizeEvent* ev = BX_NEW(g_allocator, SizeEvent)(_handle);
			ev->m_width  = _width;
			ev->m_height = _height;
			m_queue.push(ev);
		}

		void postWindowEvent(WindowHandle _handle, void* _nwh = NULL)
		{
			WindowEvent* ev = BX_NEW(g_allocator, WindowEvent)(_handle);
			ev->m_nwh = _nwh;
			m_queue.push(ev);
		}

		void postSuspendEvent(WindowHandle _handle, Suspend::Enum _state)
		{
			SuspendEvent* ev = BX_NEW(g_allocator, SuspendEvent)(_handle);
			ev->m_state = _state;
			m_queue.push(ev);
		}

		void postDropFileEvent(WindowHandle _handle, const bx::FilePath& _filePath)
		{
			DropFileEvent* ev = BX_NEW(g_allocator, DropFileEvent)(_handle);
			ev->m_filePath = _filePath;
			m_queue.push(ev);
		}

		const Event* poll()
		{
			return m_queue.pop();
		}

		const Event* poll(WindowHandle _handle)
		{
			if (isValid(_handle) )
			{
				Event* ev = m_queue.peek();
				if (NULL == ev
				||  ev->m_handle.idx != _handle.idx)
				{
					return NULL;
				}
			}

			return poll();
		}

		void release(const Event* _event) const
		{
			BX_DELETE(g_allocator, const_cast<Event*>(_event) );
		}

	private:
		bx::SpScUnboundedQueueT<Event> m_queue;
	};

} // ari
