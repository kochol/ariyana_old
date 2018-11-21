#pragma once
#include "shiva/shivadef.hpp"
#include "shiva/DirectoryTree.hpp"
#include "../../../src/editor/windows/AssetGui.hpp"

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

		void UpdateAssets(const DirectoryTree& _tree);

		ari::Dock			*	m_pDock = nullptr;		
		std::vector<AssetGui*>	m_vAssets;

	}; // AssetBrowser

} // shiva
