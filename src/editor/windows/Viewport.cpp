#include "../../../include/shiva/windows/Viewport.hpp"
#include "../../../deps/bgfx/examples/common/imgui/imgui.h"
#include "ari/en/2d/Viewport.hpp"
#include "ari/en/3d/Camera.hpp"
#include "ari/en/3d/BoxShape.hpp"
#include "ari/en/World.hpp"
#include "ari/en/gui/Image.hpp"
#include "ari/Engine.hpp"

namespace shiva
{
	void Viewport::OnGui()
	{
		float w, h;
		m_pWindow->GetLastSize(w, h);
		m_pView->Size.x = w;
		m_pView->Size.y = h;
		m_pViewport->Rect.Set(0, 0, int(w), int(h));
	}

	void Viewport::Init(ari::World * p_world)
	{
		DockWindow::Init(p_world);

		m_pWindow->SetTitle("Viewport");
		m_pWindow->SetAlone(true);
		m_pWindow->Dock();
		m_pWindow->SetFillingSpace(true);
		m_pWindow->OnGui.Bind(this, &Viewport::OnGui);

		// Init Camera & Viewport
		m_pCamera = new ari::Camera();
		m_pCamera->Position.Set(4.0f, 4.0f, 4.0f);
		m_pEntity->AddChild(m_pCamera);
		m_pViewport = new ari::Viewport;
		m_pViewport->Rect.Set(0, 0, 300, 300);
		m_pViewport->CreateDepth = true;
		m_pViewport->TextureFormat = bgfx::TextureFormat::BGRA8;
		m_pViewport->UseMSAA = true;
		m_pCamera->AddChild(m_pViewport);
		// Add a box for test.
		m_pEntity->AddChild(new ari::BoxShape);

		// Add image
		m_pView = new ari::Image;
		m_pView->ImageTxture = std::shared_ptr<ari::Texture>(&m_pViewport->m_texture);
		m_pView->Size.x = m_pView->Size.y = 300;
		m_pWindow->AddChild(m_pView);

	} // Init

} // shiva
