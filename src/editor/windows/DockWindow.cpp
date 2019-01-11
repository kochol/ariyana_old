#include "shiva/windows/DockWindow.hpp"
#include "ari/en/World.hpp"
#include "shiva/Editor.hpp"

namespace shiva
{
	void DockWindow::Init(ari::World* p_world)
	{
		m_pEntity = new ari::Entity;
		p_world->AddEntity(m_pEntity);
		m_pWindow = new ari::DockableWindow(g_pEditor->GetGuiSystem());
		m_pEntity->AddChild(m_pWindow);
	}

	void DockWindow::Shutdown()
	{
		if (m_pEntity)
		{
			m_pEntity->Destroy();
			m_pWindow = nullptr;
		}
	}

} // shiva
