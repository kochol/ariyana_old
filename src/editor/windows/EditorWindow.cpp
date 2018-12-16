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

		// Init Asset Browser
		if (!m_pAssetBrowser)
			m_pAssetBrowser = new AssetBrowser;
		m_pAssetBrowser->Init(m_pEntity);

	} // Init

	void EditorWindow::ShutDown()
	{
		if (m_pEntity)
			m_pEntity->Destroy();
		m_pEntity = nullptr;
		m_pAssetBrowser->ShutDown();

	} // ShutDown

} // shiva
