#pragma once
#include "shivadef.hpp"
#include "ari/en/World.hpp"
#include "ari/en/gui/GuiSystem.hpp"
#include "ari/en/3d/RenderSystem.hpp"
#include "ari/en/3d/SceneSystem.hpp"
#include "windows/ProjectBrowser.hpp"
#include "windows/EditorWindowManager.hpp"

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

		Project* GetCurrentProject() const { return m_pCurrentProject; }

		ari::GuiSystem* GetGuiSystem() { return &m_GuiSystem; }

	protected:

		ari::World			m_EditorWorld;
		ari::GuiSystem		m_GuiSystem;
		ari::RenderSystem	m_RenderSystem;
		ari::SceneSystem	m_SceneSystem;
		ProjectBrowser		m_ProjectBrowser;
		EditorWindowManager	m_EditorWindow;
		Project			*	m_pCurrentProject = nullptr;

	}; // Editor

	extern SHIVA_API Editor* g_pEditor;

} // shiva
