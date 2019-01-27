#include "../../include/shiva/Editor.hpp"
#include "shiva/Project.hpp"
#include "shiva/EditorSettings.hpp"

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
		// Load editor settings
		EditorSettings::Load();
		
		// Add Systems
		m_EditorWorld.AddSystem(&m_GuiSystem);
		m_EditorWorld.AddSystem(&m_RenderSystem);
		m_EditorWorld.AddSystem(&m_SceneSystem);
		//m_EditorWorld.SetUpdateType(ari::World::UpdateType::Sync);
		
		// Init project browser
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

		EditorSettings::Get().LastProjectPath = project->GetPath().get();
		EditorSettings::Save();

		m_EditorWindow.Init(&m_EditorWorld);
	}

} // shiva
