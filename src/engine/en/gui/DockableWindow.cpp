#include "../../../../include/ari/en/gui/DockableWindow.hpp"
#include "ImwWindow.h"
#include "../../../../include/ari/en/gui/GuiSystem.hpp"
#include "ImwWindowManager.h"
#include "Imw/ImwWindowManagerAri.hpp"
#include "imw/ImwPlatformWindowAri.hpp"

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
			auto p_window_manager = ImWindow::ImwWindowManager::GetInstance();
			const auto win = reinterpret_cast<ImwPlatformWindowAri*>
				(p_window_manager->GetCurrentPlatformWindow())->GetPlatformWindow();

			if (win != m_pDockable->m_pPlatformWindow && m_pDockable->OnWindowChanged.IsBound())
			{
				m_pDockable->m_pPlatformWindow = win;
				m_pDockable->OnWindowChanged.Execute();
			}
			m_pDockable->m_pPlatformWindow = win;

			if (m_pDockable->OnGui.IsBound())
				m_pDockable->OnGui.Execute();

			for (auto c : m_pDockable->m_vChilds)
				m_pDockable->m_pGuiSystem->RenderGui(c);
		}

	protected:

		DockableWindow	*	m_pDockable;
	};

	DockableWindow::DockableWindow(GuiSystem * _pGuiSystem): m_pGuiSystem(_pGuiSystem), m_pPlatformWindow(nullptr)
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
		ImWindow::ImwWindowManager* p_window_manager = ImWindow::ImwWindowManager::GetInstance();
		p_window_manager->DestroyWindow(m_pWindow);
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

	void DockableWindow::SetTitle(const char * _pTitle) const
	{
		m_pWindow->SetTitle(_pTitle);
	}

	void DockableWindow::SetAlone(bool _alone) const
	{
		m_pWindow->SetAlone(_alone);
	}

	void DockableWindow::SetClosable(bool _closable) const
	{
		m_pWindow->SetClosable(_closable);
	}

	void DockableWindow::SetFillingSpace(bool _fill) const
	{
		m_pWindow->SetFillingSpace(_fill);
	}

	void DockableWindow::GetLastPosition(float & _x, float & _y) const
	{
		auto p = m_pWindow->GetLastPosition();
		_x = p.x;
		_y = p.y;
	}

	void DockableWindow::GetLastSize(float & _width, float & _height) const
	{
		auto s = m_pWindow->GetLastSize();
		_width = s.x;
		_height = s.y;
	}

	PlatformWindow * DockableWindow::GetPlatformWindow() const
	{
		return m_pPlatformWindow;
	}

} // ari
