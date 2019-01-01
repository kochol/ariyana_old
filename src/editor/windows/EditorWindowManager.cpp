#include "../../../include/shiva/windows/EditorWindowManager.hpp"
#include "ari/en/Entity.hpp"
#include "ari/en/World.hpp"
#include "ari/en/gui/Window.hpp"
#include "ari/en/gui/DockSpace.hpp"
#include "shiva/windows/AssetBrowser.hpp"
#include "ari/Engine.hpp"

namespace shiva
{
	EditorWindowManager::EditorWindowManager() = default;

	EditorWindowManager::~EditorWindowManager()
	{
		ShutDown();
		delete m_pAssetBrowser;
	}

	void EditorWindowManager::Init(ari::World* pWorld)
	{
		m_pEntity = new ari::Entity;
		pWorld->AddEntity(m_pEntity);

		// Init Asset Browser
		if (!m_pAssetBrowser)
			m_pAssetBrowser = new AssetBrowser;
		m_pAssetBrowser->Init(pWorld);

	} // Init

	void EditorWindowManager::ShutDown()
	{
		if (m_pEntity)
			m_pEntity->Destroy();
		m_pEntity = nullptr;
		m_pAssetBrowser->ShutDown();

	} // ShutDown

} // shiva
