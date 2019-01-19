#pragma once
#include "ImwPlatformWindow.h"
#include "../../../../../include/ari/io/PlatformWindow.hpp"
#include <bgfx/bgfx.h>

namespace ari
{
	class ImwPlatformWindowAri: public ImWindow::ImwPlatformWindow
	{
	public:
		ImwPlatformWindowAri(ImWindow::EPlatformWindowType eType, bool bCreateContext);
		~ImwPlatformWindowAri() override;

		bool Init(ImwPlatformWindow* pParent) override;

		ImVec2 GetPosition() const override;
		ImVec2 GetSize() const override;

		bool IsWindowMaximized() const override;
		bool IsWindowMinimized() const override;

		void Show(bool bShow) override;
		void SetSize(int iWidth, int iHeight) override;
		void SetPosition(int iX, int iY) override;
		void SetWindowMaximized(bool bMaximized) override;
		void SetWindowMinimized(bool bMinimized) override;
		void SetTitle(const char* pTtile) override;

		PlatformWindow* GetPlatformWindow() const { return m_pWindow; }

	protected:
		void PreUpdate() override;
		void RenderDrawLists(ImDrawData* pDrawData) override;

		void OnKey(Key::Enum _key, bool _down);
		void OnChar(uint8_t len, uint8_t* utf8);
		void OnMouseKey(MouseButton::Enum _btn, bool _down);
		void OnMouseMove(int _x, int _y);
		void OnMouseWheel(int _z);
		void OnSize(int _w, int _h);

		PlatformWindow	*					m_pWindow = nullptr;
		DelegateTwoParam<void, Key::Enum, bool>
											m_onKey;
		DelegateTwoParam<void, uint8_t, uint8_t*>
											m_onChar;
		DelegateTwoParam<void, MouseButton::Enum, bool>
											m_onMouseBtn;
		DelegateTwoParam<void, int, int>	m_onMouseMove,
											m_onSize;
		DelegateOneParam<void, int>			m_onMouseWheel;
		bgfx::ViewId						m_iViewId;
		bgfx::FrameBufferHandle				m_hFrameBufferHandle;
	};

} // ari
