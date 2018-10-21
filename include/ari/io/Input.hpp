#pragma once
#include "IoEnums.hpp"
#include "../aridef.hpp"

namespace ari
{
	typedef void(*InputBindingFn)(const void* _userData);

	struct ARI_API InputBinding
	{
		void set(Key::Enum _key, uint8_t _modifiers, uint8_t _flags, InputBindingFn _fn, const void* _userData = NULL)
		{
			m_key = _key;
			m_modifiers = _modifiers;
			m_flags = _flags;
			m_fn = _fn;
			m_userData = _userData;
		}

		void end()
		{
			m_key = Key::None;
			m_modifiers = Modifier::None;
			m_flags = 0;
			m_fn = NULL;
			m_userData = NULL;
		}

		Key::Enum m_key;
		uint8_t m_modifiers;
		uint8_t m_flags;
		InputBindingFn m_fn;
		const void* m_userData;
	};

#define INPUT_BINDING_END { Key::None, Modifier::None, 0, NULL, NULL }

	///
	void inputInit();

	///
	void inputShutdown();

	///
	void inputAddBindings(const char* _name, const InputBinding* _bindings);

	///
	void inputRemoveBindings(const char* _name);

	///
	void inputProcess();

	///
	void inputSetKeyState(Key::Enum  _key, uint8_t _modifiers, bool _down);

	///
	bool inputGetKeyState(Key::Enum _key, uint8_t* _modifiers = NULL);

	///
	uint8_t inputGetModifiersState();

	/// Adds single UTF-8 encoded character into input buffer.
	void inputChar(uint8_t _len, const uint8_t _char[4]);

	/// Returns single UTF-8 encoded character from input buffer.
	const uint8_t* inputGetChar();

	/// Flush internal input buffer.
	void inputCharFlush();

	///
	void inputSetMouseResolution(uint16_t _width, uint16_t _height);

	///
	void inputSetMousePos(int32_t _mx, int32_t _my, int32_t _mz);

	///
	void inputSetMouseButtonState(MouseButton::Enum _button, uint8_t _state);

	///
	void inputSetMouseLock(bool _lock);

	///
	void inputGetMouse(float _mouse[3]);

	///
	bool inputIsMouseLocked();

	///
	void inputSetGamepadAxis(GamepadHandle _handle, GamepadAxis::Enum _axis, int32_t _value);

	///
	int32_t inputGetGamepadAxis(GamepadHandle _handle, GamepadAxis::Enum _axis);

}
