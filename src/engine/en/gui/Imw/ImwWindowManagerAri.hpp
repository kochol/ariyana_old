#pragma once
#include "ImwWindowManager.h"

namespace ari
{
	class ImwWindowManagerAri: public ImWindow::ImwWindowManager
	{
	protected:
		bool CanCreateMultipleWindow() override;

		ImWindow::ImwPlatformWindow* CreatePlatformWindow(ImWindow::EPlatformWindowType eType,
			ImWindow::ImwPlatformWindow* pParent) override;

		ImVec2 GetCursorPos() override;

		bool IsLeftClickDown() override;
	};

} // ari
