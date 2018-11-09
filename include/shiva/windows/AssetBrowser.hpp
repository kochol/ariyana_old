#pragma once
#include "shiva/shivadef.hpp"

namespace ari {
	class Button;
	class Dock;
	class DockSpace;
}

namespace shiva
{
	class SHIVA_API AssetBrowser
	{
	public:

		~AssetBrowser();

		void Init(ari::DockSpace * pDockSpace);

		void ShutDown();

	private:

		ari::Dock	*	m_pDock = nullptr;
		ari::Button	*	m_pButton = nullptr;

	}; // AssetBrowser

} // shiva
