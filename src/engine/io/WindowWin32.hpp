#pragma once
#include <bx/platform.h>

#if BX_PLATFORM_WINDOWS

#include "../../../include/ari/io/PlatformWindow.hpp"
#include <Windows.h>

namespace ari
{
	class WindowWin32: public PlatformWindow
	{
	public:
		WindowWin32(Type _type);
		~WindowWin32() override;

		bool Init(int _posx, int _posy, int _width, int _height, uint32_t _flags,
			const char* _title) override;

		bool Run() override;
		void Show(bool _show) override;

		void SetMousePos(int _x, int _y) override;

		void SetTitle(const char* _title) override;
	
		void SetFlags(uint32_t _flags, bool _addFlags) override;

		void GetPos(int& _x, int& _y) override;
		void SetPos(int _x, int _y) override;

		void SetSize(int _width, int _height) override;

		void SetMouseLock(bool _lock) override;

		void ToggleFrame() override;

		bool IsWindowMaximized() override;
		void SetWindowMaximized(bool _maximize) override;
		bool IsWindowMinimized() override;
		void SetWindowMinimized(bool _minimize) override;

		void* GetHandle() override;

		LRESULT Process(HWND _hwnd, UINT _id, WPARAM _wparam, LPARAM _lparam);

	protected:

		void Adjust(uint32_t _width, uint32_t _height, bool _windowFrame);
		void Clear();

	protected:

		HWND		m_hwnd;
		uint32_t	m_flags;
		RECT		m_rect;
		DWORD		m_style;
		bool		m_frame		= true;
		bool		m_init		= false;
		bool		m_exit		= false;
		bool		m_mouseLock = false;
		int			m_mx		= 0,
					m_my		= 0,
					m_mz		= 0;
	};
} // ari

#endif
