#include "../../../include/shiva/windows/Viewport.hpp"
#include "../../../deps/bgfx/examples/common/imgui/imgui.h"

namespace shiva
{
	ari::DockableWindow* pp;

	void OnGui()
	{
		// TODO: Set viewport size here
		float x, y, w, h;
		pp->GetLastPosition(x, y);
		pp->GetLastSize(w, h);
		printf("%f x, %f y, %f w, %f h\n", x, y, h, w);
		ImVec2 oSize = ImGui::GetContentRegionAvail();
		printf("w %f, h %f\n", oSize.x, oSize.y);
		ImGui::Selectable("I'm a selectable\nwho fills the whole space", true, 0, oSize);
	}

	void Viewport::Init(ari::World * p_world)
	{
		DockWindow::Init(p_world);

		pp = m_pWindow;

		m_pWindow->SetTitle("Viewport");
		m_pWindow->SetAlone(true);
		m_pWindow->Dock();
		m_pWindow->SetFillingSpace(true);
		m_pWindow->OnGui.Bind(&OnGui);

	} // Init

} // shiva
