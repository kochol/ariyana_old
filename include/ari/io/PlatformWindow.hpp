#pragma once
#include "../aridef.hpp"
#include <cstdint>
#include "IoEvents.hpp"

namespace ari
{
	class ARI_API PlatformWindow
	{
		friend class Engine;

	public:

		enum class Type
		{
			Main,
			Child
		};

		PlatformWindow(Type _type): m_Type(_type) {}
		virtual ~PlatformWindow() {}

		virtual bool Init(int _posx, int _posy, int _width, int _height, uint32_t _flags, 
			const char* _title) = 0;

		virtual bool Run() = 0;

		virtual void SetMousePos(int _x, int _y) = 0;

		virtual void SetTitle(char* _title) = 0;

		virtual void SetFlags(uint32_t _flags, bool _addFlags = false) = 0;

		virtual void SetPos(int _x, int _y) = 0;

		virtual void SetSize(int _width, int _height) = 0;

		virtual void SetMouseLock(bool _lock) = 0;

		virtual void ToggleFrame() = 0;

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

	}; // Window

} // ari
