#pragma once
#include "Gui.hpp"

namespace ari
{
	class ARI_API Popup: public Gui
	{
	public:

		bool BeginRender() override;

		void EndRender() override;

		void Show();

		void Hide();

		//! Name must be unique.
		char*	Name = nullptr;

	protected:

		bool m_bDoEndPopup = false;
		bool m_bOpenPopup = false;

	}; // Popup

} // ari
