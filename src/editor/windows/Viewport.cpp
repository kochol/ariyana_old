#include "../../../include/shiva/windows/Viewport.hpp"
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

	void Viewport::OnHovered()
	{
		// Rotate camera by right click
		if (ImGui::IsMouseDragging(1))
		{
			const auto d = ImGui::GetMouseDragDelta(1);
			m_pCamera->RotateByMouse(int(d.x), int(d.y), 0.3f * ari::g_pEngine->GetDeltaTime());
			ImGui::ResetMouseDragDelta(1);

			const float speed = 0.3f * ari::g_pEngine->GetDeltaTime();
			if (ImGui::IsKeyDown(ari::Key::KeyW))
				m_pCamera->MoveBF(speed);
			if (ImGui::IsKeyDown(ari::Key::KeyS))
				m_pCamera->MoveBF(-speed);
			if (ImGui::IsKeyDown(ari::Key::KeyA))
				m_pCamera->MoveLR(-speed);
			if (ImGui::IsKeyDown(ari::Key::KeyD))
				m_pCamera->MoveLR(speed);
		}
		if (ImGui::IsMouseDragging(2))
		{
			const auto d = ImGui::GetMouseDragDelta(2);
			m_pCamera->MoveUD(d.y * -0.3f * ari::g_pEngine->GetDeltaTime());
			m_pCamera->MoveLR(d.x * 0.5f * ari::g_pEngine->GetDeltaTime());
			ImGui::ResetMouseDragDelta(2);
		}
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
		m_pView->ImageTexture = std::shared_ptr<ari::Texture>(&m_pViewport->m_texture);
		m_pView->Size.x = m_pView->Size.y = 300;
		m_pView->OnHovered.Bind(this, &Viewport::OnHovered);
		m_pWindow->AddChild(m_pView);

	} // Init

} // shiva
