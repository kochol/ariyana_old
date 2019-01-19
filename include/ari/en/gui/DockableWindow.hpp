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
	class PlatformWindow;

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

		void SetTitle(const char* _pTitle) const;
		void SetAlone(bool _alone) const;
		void SetClosable(bool _closable) const;
		void SetFillingSpace(bool _fill) const;

		void GetLastPosition(float& _x, float& _y) const;
		void GetLastSize(float& _width, float& _height) const;

		/**
		* This is a callback for when we want to draw the Guis good to get the window size here.
		*/
		DelegateNoParam<void> OnGui;

		/**
		 * This callback is for when platform window change or assigned.
		 * Good for setting the event listeners.
		 */
		DelegateNoParam<void> OnWindowChanged;

		/**
		 * @note: only call this function on OnGui callback 
		 */
		PlatformWindow* GetPlatformWindow() const;

	protected:

		GuiSystem			*	m_pGuiSystem;
		ImWindow::ImwWindow	*	m_pWindow;
		PlatformWindow		*	m_pPlatformWindow;

	};

} // ari
