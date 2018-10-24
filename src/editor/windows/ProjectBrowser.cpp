#include "..\..\..\include\shiva\windows\ProjectBrowser.hpp"
#include "ari/en/gui/Window.hpp"
#include "ari/en/World.hpp"

namespace shiva
{
	ProjectBrowser::ProjectBrowser(): m_pWindow(nullptr)
	{
	}

	ProjectBrowser::~ProjectBrowser()
	{
		if (m_pWindow)
			delete m_pWindow;
	}

	void ProjectBrowser::Init(ari::World* p_world)
	{
		p_world->AddEntity(&m_Entity);
		m_pWindow = new ari::Window();
		m_pWindow->Name = "Project Browser";
		m_pWindow->Size.x = 800;
		m_pWindow->Size.y = 600;
		m_Entity.AddChild(m_pWindow);
	}

} // shiva
