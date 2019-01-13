#pragma once
#include "Gui.hpp"
#include "../../Delegate.hpp"

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

		void SetTitle(const char* _pTitle);
		void SetAlone(bool _alone);
		void SetClosable(bool _closable);
		void SetFillingSpace(bool _fill);

		void GetLastPosition(float& _x, float& _y);
		void GetLastSize(float& _width, float& _height);

		/**
		* This is a callback for when we want to draw the Guis good to get the window size here.
		*/
		DelegateNoParam<void> OnGui;

	protected:

		GuiSystem			*	m_pGuiSystem;
		ImWindow::ImwWindow	*	m_pWindow;

	};

} // ari
