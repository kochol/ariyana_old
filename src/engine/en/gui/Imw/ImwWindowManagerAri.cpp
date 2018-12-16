#include "ImwWindowManagerAri.hpp"
#include <bx/platform.h>
#include "bgfx/bgfx.h"
#include "ImwPlatformWindowAri.hpp"

#if BX_PLATFORM_WINDOWS
#include <Windows.h>
#endif

namespace ari
{
	bool ImwWindowManagerAri::CanCreateMultipleWindow()
	{
		const bgfx::Caps* caps = bgfx::getCaps();
		return 0 != (caps->supported & BGFX_CAPS_SWAP_CHAIN);
	}

	ImWindow::ImwPlatformWindow* ImwWindowManagerAri::CreatePlatformWindow(ImWindow::EPlatformWindowType eType,
		ImWindow::ImwPlatformWindow* pParent)
	{
		ImwPlatformWindowAri* pWindow = new ImwPlatformWindowAri(eType, CanCreateMultipleWindow());
		if (pWindow->Init(pParent))
		{
			return pWindow;
		}
		delete pWindow;
		return nullptr;
	}

	ImVec2 ImwWindowManagerAri::GetCursorPos()
	{
#if BX_PLATFORM_WINDOWS
		POINT pt = { 0, 0 };
		::GetCursorPos(&pt);
		return { float(pt.x), float(pt.y) };
#endif

		return { 0.0f, 0.0f };
	}

	bool ImwWindowManagerAri::IsLeftClickDown()
	{
#if BX_PLATFORM_WINDOWS
		return GetAsyncKeyState(VK_LBUTTON) & 0x8000;
#endif

		return false;
	}

} // ari
