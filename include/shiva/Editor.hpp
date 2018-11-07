#pragma once
#include "shivadef.hpp"
#include "ari/en/World.hpp"
#include "ari/en/gui/GuiSystem.hpp"
#include "windows/ProjectBrowser.hpp"

namespace shiva
{
	class Project;

	class SHIVA_API Editor
	{
	public:

		Editor();

		~Editor();
		
		void Init();

		void Update(float elasped);

		void LoadProject(Project* project);

	protected:

		ari::World		m_EditorWorld;
		ari::GuiSystem	m_GuiSystem;
		ProjectBrowser	m_ProjectBrowser;
		Project		*	m_pCurrentProject = nullptr;

	}; // Editor

	extern SHIVA_API Editor* g_pEditor;

} // shiva
