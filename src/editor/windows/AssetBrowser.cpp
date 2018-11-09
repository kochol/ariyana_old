#include "../../../include/shiva/windows/AssetBrowser.hpp"
#include "ari/en/gui/Dock.hpp"
#include "ari/en/gui/Button.hpp"
#include "ari/en/gui/DockSpace.hpp"
#include "ari/en/World.hpp"

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
		ari::Dock* d = new ari::Dock;
		d->Label = "Test window";
		pDockSpace->AddChild(d);
		ari::Button* b = new ari::Button;
		b->Label = "TTT FFFF";
		d->AddChild(b);
		d = new ari::Dock;
		d->Label = "Test window2";
		pDockSpace->AddChild(d);
		b = new ari::Button;
		b->Label = "TTT FFFF 22222";
		d->AddChild(b);
		d = new ari::Dock;
		d->Label = "Test window 333";
		pDockSpace->AddChild(d);
		b = new ari::Button;
		b->Label = "TTT FFFF 3333";
		d->AddChild(b);
	}

	void AssetBrowser::ShutDown()
	{
		m_pDock = nullptr;
		m_pButton = nullptr;
	}

} // shiva
