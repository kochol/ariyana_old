#include "../../../../include/ari/en/gui/DockableWindow.hpp"
#include "ImwWindow.h"
#include "../../../../include/ari/en/gui/GuiSystem.hpp"
#include "ImwWindowManager.h"
#include "Imw/ImwWindowManagerAri.hpp"

namespace ari
{
	class AriImwWindow: public ImWindow::ImwWindow
	{
	public:
		AriImwWindow(DockableWindow* _pDock): m_pDockable(_pDock)
		{
		}

		void OnGui() override
		{
			SetAlone(m_pDockable->Alone);
			SetClosable(m_pDockable->Closable);

			for (auto c : m_pDockable->m_vChilds)
				m_pDockable->m_pGuiSystem->RenderGui(c);
		}

	protected:

		DockableWindow	*	m_pDockable;
	};

	DockableWindow::DockableWindow(GuiSystem * _pGuiSystem): m_pGuiSystem(_pGuiSystem)
	{
		// Check window manager Init
		ImWindow::ImwWindowManager* p_window_manager = ImWindow::ImwWindowManager::GetInstance();
		if (!p_window_manager)
		{
			p_window_manager = new ImwWindowManagerAri();
			p_window_manager->Init();
		}

		m_pWindow = new AriImwWindow(this);
		Dock();
	}

	DockableWindow::~DockableWindow()
	{
		// TODO: Add some function to delete it.
		// The ImwWill delete it later on shutdown
		// delete m_pWindow;
	}

	bool DockableWindow::BeginRender()
	{
		return false;
	}

	void DockableWindow::Dock(Oriention _oriention, float _raito) const
	{
		ImWindow::ImwWindowManager* p_window_manager = ImWindow::ImwWindowManager::GetInstance();
		p_window_manager->Dock(m_pWindow, ImWindow::EDockOrientation(_oriention), _raito);
	}

	void DockableWindow::DockWith(DockableWindow * _pOtherDock, Oriention _oriention, float _raito) const
	{
		ImWindow::ImwWindowManager* p_window_manager = ImWindow::ImwWindowManager::GetInstance();
		p_window_manager->DockWith(m_pWindow, _pOtherDock->m_pWindow, 
			ImWindow::EDockOrientation(_oriention), _raito);
	}

	void DockableWindow::SetTitle(const char * _pTitle)
	{
		m_pWindow->SetTitle(_pTitle);
	}

} // ari
