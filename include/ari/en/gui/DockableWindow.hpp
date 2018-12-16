#pragma once
#include "Gui.hpp"

namespace ImWindow
{
	class ImwWindow;
}

namespace ari
{
	class GuiSystem;

	class ARI_API DockableWindow: public Gui
	{
		friend class AriImwWindow;

	public:
		enum class Oriention
		{
			Center,
			Top,
			Left,
			Right,
			Botton
		};

		DockableWindow(GuiSystem* _pGuiSystem);
		~DockableWindow() override;

		bool BeginRender() override;

		void Dock(Oriention _oriention = Oriention::Center,	float _raito = 0.5f) const;

		void DockWith(DockableWindow* _pOtherDock, Oriention _oriention = Oriention::Center, 
			float _raito = 0.5f) const;

		char				*	Tiltle = nullptr;
		bool					Alone = false;
		bool					Closable = true;

	protected:

		GuiSystem			*	m_pGuiSystem;
		ImWindow::ImwWindow	*	m_pWindow;

	};

} // ari
