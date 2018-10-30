#include "..\..\include\shiva\Editor.hpp"
#include "shiva/Project.hpp"

namespace shiva
{
	void Editor::Init()
	{
		m_EditorWorld.AddSystem(&m_GuiSystem);
		m_ProjectBrowser.Init(&m_EditorWorld);
	}

	void Editor::Update(float elasped)
	{
		m_EditorWorld.Update(elasped);
	}

} // shiva
