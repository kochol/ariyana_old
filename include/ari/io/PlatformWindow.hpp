#pragma once
#include "../aridef.hpp"
#include <cstdint>
#include "IoEvents.hpp"
#include "../Delegate.hpp"
#include "tinystl/vector.h"

namespace ari
{
	class ARI_API PlatformWindow
	{
		friend class Engine;

	public:

		enum class Type
		{
			Main,
			Child,
			Popup
		};

		PlatformWindow(Type _type): m_Type(_type) {}
		virtual ~PlatformWindow() {}

		virtual bool Init(int _posx, int _posy, int _width, int _height, uint32_t _flags, 
			const char* _title) = 0;

		virtual bool Run() = 0;

		virtual void Show(bool _show) = 0;

		virtual void SetMousePos(int _x, int _y) = 0;

		virtual void SetTitle(const char* _title) = 0;

		virtual void SetFlags(uint32_t _flags, bool _addFlags = false) = 0;

		virtual void GetPos(int& _x, int& _y) = 0;
		virtual void SetPos(int _x, int _y) = 0;

		virtual void GetSize(int& _width, int& _height);
		virtual void SetSize(int _width, int _height) = 0;

		virtual void SetAlpha(unsigned char _alpha) = 0;

		virtual void SetMouseLock(bool _lock) = 0;

		virtual void ToggleFrame() = 0;

		virtual bool IsWindowMaximized() = 0;
		virtual void SetWindowMaximized(bool _maximize) = 0;
		virtual bool IsWindowMinimized() = 0;
		virtual void SetWindowMinimized(bool _minimize) = 0;

		virtual void* GetHandle() = 0;

		void AddOnKeyDelegate(DelegateTwoParam<void, Key::Enum, bool>* _pDelegate);
		void RemoveOnKeyDelegate(DelegateTwoParam<void, Key::Enum, bool>* _pDelegate);

		void AddOnCharDelegate(DelegateTwoParam<void, uint8_t, uint8_t*>* _pDelegate);
		void RemoveOnCharDelegate(DelegateTwoParam<void, uint8_t, uint8_t*>* _pDelegate);

		void AddOnMouseButtonDelegate(DelegateTwoParam<void, MouseButton::Enum, bool>* _pDelegate);
		void RemoveOnMouseButtonDelegate(DelegateTwoParam<void, MouseButton::Enum, bool>* _pDelegate);

		void AddOnMouseMoveDelegate(DelegateTwoParam<void, int, int>* _pDelegate);
		void RemoveOnMouseMoveDelegate(DelegateTwoParam<void, int, int>* _pDelegate);

		void AddOnMouseWheelDelegate(DelegateOneParam<void, int>* _pDelegate);
		void RemoveOnMouseWheelDelegate(DelegateOneParam<void, int>* _pDelegate);

		void AddOnSizeDelegate(DelegateTwoParam<void, int, int>* _pDelegate);
		void RemoveOnSizeDelegate(DelegateTwoParam<void, int, int>* _pDelegate);

		bool ProcessEvents(uint32_t& _width, uint32_t& _height, uint32_t& _debug, uint32_t& _reset,
			MouseState* _mouse);

	protected:

		Type		m_Type;
		uint32_t	m_width;
		uint32_t	m_height;
		uint32_t	m_oldWidth;
		uint32_t	m_oldHeight;
		uint32_t	m_frameWidth;
		uint32_t	m_frameHeight;
		float		m_aspectRatio;
		EventQueue	m_eventQueue;
		tinystl::vector<DelegateTwoParam<void, Key::Enum, bool>*>
					m_vOnKeys;
		tinystl::vector<DelegateTwoParam<void, uint8_t, uint8_t*>*>
					m_vOnChar;
		tinystl::vector<DelegateTwoParam<void, MouseButton::Enum, bool>*>
					m_vOnMouseButtons;
		tinystl::vector<DelegateTwoParam<void, int, int>*>
					m_vOnMouseMove;
		tinystl::vector<DelegateOneParam<void, int>*>
					m_vOnMouseWheel;
		tinystl::vector<DelegateTwoParam<void, int, int>*>
					m_vOnSize;

	}; // Window

} // ari
