#include "../../../include/shiva/windows/EditorWindow.hpp"
#include "ari/en/Entity.hpp"
#include "ari/en/World.hpp"
#include "ari/en/gui/Window.hpp"
#include "ari/en/gui/DockSpace.hpp"
#include "shiva/windows/AssetBrowser.hpp"
#include "ari/Engine.hpp"

namespace shiva
{
	EditorWindow::EditorWindow() = default;

	EditorWindow::~EditorWindow()
	{
		ShutDown();
		delete m_pAssetBrowser;
	}

	void EditorWindow::Init(ari::World* pWorld)
	{
		m_pEntity = new ari::Entity;
		pWorld->AddEntity(m_pEntity);
		m_pWindow = new ari::Window;
		m_pWindow->Name = "MainEditorWindow";
		m_pWindow->Flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoCollapse;
		auto p = ari::g_pEngine->GetParams();
		m_pWindow->Size.x = p->Width;
		m_pWindow->Size.y = p->Height;
		m_pEntity->AddChild(m_pWindow);
		m_pDockSpace = new ari::DockSpace;
		m_pWindow->AddChild(m_pDockSpace);

		// Init Asset Browser
		if (!m_pAssetBrowser)
			m_pAssetBrowser = new AssetBrowser;
		m_pAssetBrowser->Init(m_pDockSpace);

	} // Init

	void EditorWindow::ShutDown()
	{
		if (m_pEntity)
			m_pEntity->Destroy();
		m_pEntity = nullptr;
		m_pWindow = nullptr;
		m_pDockSpace = nullptr;
		m_pAssetBrowser->ShutDown();

	} // ShutDown

} // shiva
