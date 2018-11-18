#include "../../../include/shiva/windows/AssetBrowser.hpp"
#include "ari/en/gui/Dock.hpp"
#include "ari/en/gui/Button.hpp"
#include "ari/en/gui/DockSpace.hpp"
#include "ari/en/World.hpp"
#include "AssetGui.hpp"

namespace shiva
{
	AssetBrowser::~AssetBrowser()
	{
		ShutDown();
	}

	void AssetBrowser::Init(ari::DockSpace * pDockSpace)
	{
		m_pDock = new ari::Dock;
		m_pDock->Label = "Asset browser";
		pDockSpace->AddChild(m_pDock);
		m_pButton = new ari::Button;
		m_pButton->Label = "TEST   Dock";
		m_pDock->AddChild(m_pButton);
		m_pDock->AddChild(new AssetGui);
	}

	void AssetBrowser::ShutDown()
	{
		m_pDock = nullptr;
		m_pButton = nullptr;
	}

} // shiva
