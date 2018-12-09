#include "ImwPlatformWindowAri.hpp"

namespace ari
{
	ImwPlatformWindowAri::ImwPlatformWindowAri(ImWindow::EPlatformWindowType eType, bool bCreateContext):
		ImwPlatformWindow(eType, bCreateContext)
	{
	}

	ImwPlatformWindowAri::~ImwPlatformWindowAri()
	{
	}

	bool ImwPlatformWindowAri::Init(ImwPlatformWindow* pParent)
	{
	}

	ImVec2 ImwPlatformWindowAri::GetPosition() const
	{
	}

	ImVec2 ImwPlatformWindowAri::GetSize() const
	{
	}

	ImVec2 ImwPlatformWindowAri::GetNormalPosition() const
	{
	}

	ImVec2 ImwPlatformWindowAri::GetNormalSize() const
	{
	}

	bool ImwPlatformWindowAri::IsWindowMaximized() const
	{
	}

	bool ImwPlatformWindowAri::IsWindowMinimized() const
	{
	}

	void ImwPlatformWindowAri::Show(bool bShow)
	{
	}

	void ImwPlatformWindowAri::SetSize(int iWidth, int iHeight)
	{
	}

	void ImwPlatformWindowAri::SetPosition(int iX, int iY)
	{
	}

	void ImwPlatformWindowAri::SetWindowMaximized(bool bMaximized)
	{
	}

	void ImwPlatformWindowAri::SetWindowMinimized(bool bMinimized)
	{
	}

	void ImwPlatformWindowAri::SetTitle(const char* pTtile)
	{
	}

	void ImwPlatformWindowAri::PreUpdate()
	{
	}

	void ImwPlatformWindowAri::PreRender()
	{
	}

	void ImwPlatformWindowAri::OnOverlay()
	{
	}

	void ImwPlatformWindowAri::RenderDrawLists(ImDrawData* pDrawData)
	{
	}
} // ari
