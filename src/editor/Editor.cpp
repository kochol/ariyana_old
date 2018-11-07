#include "..\..\include\shiva\Editor.hpp"
#include "shiva/Project.hpp"

namespace shiva
{
	Editor* g_pEditor = nullptr;

	Editor::Editor()
	{
		g_pEditor = this;
	}

	Editor::~Editor()
	{
		g_pEditor = nullptr;
	}

	void Editor::Init()
	{
		m_EditorWorld.AddSystem(&m_GuiSystem);
		m_ProjectBrowser.Init(&m_EditorWorld);
	}

	void Editor::Update(float elasped)
	{
		m_EditorWorld.Update(elasped);
	}

	void Editor::LoadProject(Project* project)
	{
		delete m_pCurrentProject;
		m_pCurrentProject = project;
	}

} // shiva
