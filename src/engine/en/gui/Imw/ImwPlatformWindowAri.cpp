#include "ImwPlatformWindowAri.hpp"
#include "../../../../../include/ari/Engine.hpp"

namespace ari
{
	ImwPlatformWindowAri::ImwPlatformWindowAri(ImWindow::EPlatformWindowType eType, bool bCreateContext):
		ImwPlatformWindow(eType, bCreateContext)
	{
		m_pWindow = g_pEngine->NewWindow(PlatformWindow::Type::Child);
	}

	ImwPlatformWindowAri::~ImwPlatformWindowAri()
	{
		delete m_pWindow;
	}

	bool ImwPlatformWindowAri::Init(ImwPlatformWindow* pParent)
	{
		return m_pWindow->Init(0, 0, 800, 600, 0, "Test");
	}

	ImVec2 ImwPlatformWindowAri::GetPosition() const
	{
		int x, y;
		m_pWindow->GetPos(x, y);

		return {x, y};
	}

	ImVec2 ImwPlatformWindowAri::GetSize() const
	{
		int w, h;
		m_pWindow->GetSize(w, h);

		return {w, h};
	}

	bool ImwPlatformWindowAri::IsWindowMaximized() const
	{
		return m_pWindow->IsWindowMaximized();
	}

	bool ImwPlatformWindowAri::IsWindowMinimized() const
	{
		return m_pWindow->IsWindowMinimized();
	}

	void ImwPlatformWindowAri::Show(bool bShow)
	{
		m_pWindow->Show(bShow);
	}

	void ImwPlatformWindowAri::SetSize(int iWidth, int iHeight)
	{
		m_pWindow->SetSize(iWidth, iHeight);
	}

	void ImwPlatformWindowAri::SetPosition(int iX, int iY)
	{
		m_pWindow->SetPos(iX, iY);
	}

	void ImwPlatformWindowAri::SetWindowMaximized(bool bMaximized)
	{
		m_pWindow->SetWindowMaximized(bMaximized);
	}

	void ImwPlatformWindowAri::SetWindowMinimized(bool bMinimized)
	{
		m_pWindow->SetWindowMinimized(bMinimized);
	}

	void ImwPlatformWindowAri::SetTitle(const char* pTtile)
	{
		m_pWindow->SetTitle(pTtile);
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
