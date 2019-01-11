#include "../../../include/shiva/windows/Viewport.hpp"

namespace shiva
{
	void Viewport::Init(ari::World * p_world)
	{
		DockWindow::Init(p_world);

		m_pWindow->SetTitle("Viewport");
		//m_pWindow->SetAlone(true);
		m_pWindow->Dock();

	} // Init

} // shiva
