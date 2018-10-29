#include "..\..\include\shiva\Editor.hpp"
#include "shiva/Project.hpp"

namespace shiva
{
	void Editor::Init()
	{
		m_EditorWorld.AddSystem(&m_GuiSystem);
		m_ProjectBrowser.Init(&m_EditorWorld);
		Project::New(bx::FilePath(bx::Dir::Temp), "test1");
	}

	void Editor::Update(float elasped)
	{
		m_EditorWorld.Update(elasped);
	}
} // shiva
