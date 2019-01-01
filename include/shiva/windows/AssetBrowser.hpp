#pragma once
#include "shiva/shivadef.hpp"
#include "shiva/DirectoryTree.hpp"
#include "../../../src/editor/windows/AssetGui.hpp"
#include "ari/en/gui/DockableWindow.hpp"
#include "DockWindow.hpp"

namespace ari {
	class Button;
	class Dock;
	class DockSpace;
}

namespace shiva
{
	class AssetGui;

	class SHIVA_API AssetBrowser : public DockWindow
	{
	public:

		~AssetBrowser();

		void Init(ari::World* p_world);

		void ShutDown();

	private:

		void UpdateAssets(const DirectoryTree& _tree);
		static DirectoryTree* FindPathTree(DirectoryTree* _tree, const std::string& _path);
		void OnDblClick(AssetGui* _sender);
		void OnRightClick(AssetGui* _sender);

		ari::DockableWindow	*	m_pDock = nullptr;		
		std::vector<AssetGui*>	m_vAssets;

	}; // AssetBrowser

} // shiva
