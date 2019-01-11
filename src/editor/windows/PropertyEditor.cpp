#include "../../../include/shiva/windows/PropertyEditor.hpp"

namespace shiva
{
	void PropertyEditor::Init(ari::World * p_world)
	{
		DockWindow::Init(p_world);

		m_pWindow->SetTitle("Property Editor");
		m_pWindow->Dock(ari::DockableWindow::Oriention::Right, 0.2f);
	}
} // shiva
