#include "ImwPlatformWindowAri.hpp"
#include "../../../../../include/ari/Engine.hpp"
#include "../../../../../deps/bgfx/examples/common/imgui/imgui.h"

namespace ari
{
	ImwPlatformWindowAri::ImwPlatformWindowAri(ImWindow::EPlatformWindowType eType, bool bCreateContext):
		ImwPlatformWindow(eType, bCreateContext)
	{
		if (eType == ImWindow::E_PLATFORM_WINDOW_TYPE_MAIN)
			m_pWindow = g_pEngine->GetMainWindow();
		else
			m_pWindow = g_pEngine->NewWindow(PlatformWindow::Type::Child);
	}

	ImwPlatformWindowAri::~ImwPlatformWindowAri()
	{
		if (m_eType != ImWindow::E_PLATFORM_WINDOW_TYPE_MAIN)
			delete m_pWindow;
	}

	bool ImwPlatformWindowAri::Init(ImwPlatformWindow* pParent)
	{
		// Init frame buffers
		static bgfx::ViewId s_view_id = 0;
		if (m_eType == ImWindow::E_PLATFORM_WINDOW_TYPE_MAIN)
		{
			m_iViewId = 0;
			return true;
		}

		m_iViewId = ++s_view_id;
		bgfx::setViewName(m_iViewId, "ImWindow");

		m_hFrameBufferHandle = bgfx::createFrameBuffer(m_pWindow->GetHandle(), 800, 600);
		bgfx::setViewFrameBuffer(m_iViewId, m_hFrameBufferHandle);

		// Init key bindings
		ImGuiIO& io = GetContext()->IO;
		io.KeyMap[ImGuiKey_Tab] = (int)ari::Key::Tab;
		io.KeyMap[ImGuiKey_LeftArrow] = (int)ari::Key::Left;
		io.KeyMap[ImGuiKey_RightArrow] = (int)ari::Key::Right;
		io.KeyMap[ImGuiKey_UpArrow] = (int)ari::Key::Up;
		io.KeyMap[ImGuiKey_DownArrow] = (int)ari::Key::Down;
		io.KeyMap[ImGuiKey_PageUp] = (int)ari::Key::PageUp;
		io.KeyMap[ImGuiKey_PageDown] = (int)ari::Key::PageDown;
		io.KeyMap[ImGuiKey_Home] = (int)ari::Key::Home;
		io.KeyMap[ImGuiKey_End] = (int)ari::Key::End;
		io.KeyMap[ImGuiKey_Insert] = (int)ari::Key::Insert;
		io.KeyMap[ImGuiKey_Delete] = (int)ari::Key::Delete;
		io.KeyMap[ImGuiKey_Backspace] = (int)ari::Key::Backspace;
		io.KeyMap[ImGuiKey_Space] = (int)ari::Key::Space;
		io.KeyMap[ImGuiKey_Enter] = (int)ari::Key::Return;
		io.KeyMap[ImGuiKey_Escape] = (int)ari::Key::Esc;
		io.KeyMap[ImGuiKey_A] = (int)ari::Key::KeyA;
		io.KeyMap[ImGuiKey_C] = (int)ari::Key::KeyC;
		io.KeyMap[ImGuiKey_V] = (int)ari::Key::KeyV;
		io.KeyMap[ImGuiKey_X] = (int)ari::Key::KeyX;
		io.KeyMap[ImGuiKey_Y] = (int)ari::Key::KeyY;
		io.KeyMap[ImGuiKey_Z] = (int)ari::Key::KeyZ;

		// Setup on events.
		m_onKey.Bind(this, &ImwPlatformWindowAri::OnKey);
		m_pWindow->AddOnKeyDelegate(&m_onKey);
		m_onMouseBtn.Bind(this, &ImwPlatformWindowAri::OnMouseKey);
		m_pWindow->AddOnMouseButtonDelegate(&m_onMouseBtn);
		m_onMouseMove.Bind(this, &ImwPlatformWindowAri::OnMouseMove);
		m_pWindow->AddOnMouseMoveDelegate(&m_onMouseMove);
		m_onMouseWheel.Bind(this, &ImwPlatformWindowAri::OnMouseWheel);
		m_onSize.Bind(this, &ImwPlatformWindowAri::OnSize);
		m_pWindow->AddOnSizeDelegate(&m_onSize);

		return m_pWindow->Init(0, 0, 800, 600, 0, "Test");
	}

	ImVec2 ImwPlatformWindowAri::GetPosition() const
	{
		int x, y;
		m_pWindow->GetPos(x, y);

		return {float(x), float(y)};
	}

	ImVec2 ImwPlatformWindowAri::GetSize() const
	{
		int w, h;
		m_pWindow->GetSize(w, h);

		return { float(w), float(h)};
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
		m_pWindow->Run();

	}

	void ImwPlatformWindowAri::RenderDrawLists(ImDrawData* pDrawData)
	{
		if (m_iViewId != 0)
			bgfx::setViewFrameBuffer(m_iViewId, m_hFrameBufferHandle);
		imguiRender(m_iViewId, pDrawData);
	}

	void ImwPlatformWindowAri::OnKey(Key::Enum _key, bool _down)
	{
		GetContext()->IO.KeysDown[_key] = _down;
	}

	void ImwPlatformWindowAri::OnMouseKey(MouseButton::Enum _btn, bool _down)
	{
		switch (_btn)
		{
		case MouseButton::Left:
			GetContext()->IO.MouseDown[0] = _down;
			break;
		case MouseButton::Middle:
			GetContext()->IO.MouseDown[2] = _down;
			break;
		case MouseButton::Right:
			GetContext()->IO.MouseDown[1] = _down;
			break;
		default:
			break;
		}
	}

	void ImwPlatformWindowAri::OnMouseMove(int _x, int _y)
	{
		GetContext()->IO.MousePos.x = _x;
		GetContext()->IO.MousePos.y = _y;
	}

	void ImwPlatformWindowAri::OnMouseWheel(int _z)
	{
		GetContext()->IO.MouseWheel = _z;
	}

	void ImwPlatformWindowAri::OnSize(int _w, int _h)
	{
		if (bgfx::isValid(m_hFrameBufferHandle))
			bgfx::destroy(m_hFrameBufferHandle);

		GetContext()->IO.DisplaySize = ImVec2(float(_w), float(_h));

		m_hFrameBufferHandle = bgfx::createFrameBuffer(m_pWindow->GetHandle(), uint16_t(_w), uint16_t(_h));

		if (m_eType == ImWindow::E_PLATFORM_WINDOW_TYPE_MAIN)
		{
			bgfx::setViewFrameBuffer(m_iViewId, m_hFrameBufferHandle);
			bgfx::reset(_w, _h);
		}

	}

} // ari
