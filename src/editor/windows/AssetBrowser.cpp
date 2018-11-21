#include "../../../include/shiva/windows/AssetBrowser.hpp"
#include "ari/en/gui/Dock.hpp"
#include "ari/en/gui/Button.hpp"
#include "ari/en/gui/DockSpace.hpp"
#include "ari/en/World.hpp"
#include "AssetGui.hpp"
#include "shiva/Editor.hpp"
#include "shiva/Project.hpp"
#include "ari/Engine.hpp"

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
		UpdateAssets(g_pEditor->GetCurrentProject()->GetTree());
	}

	void AssetBrowser::ShutDown()
	{
		m_pDock->Destroy();
		m_pDock = nullptr;
	}

	void AssetBrowser::UpdateAssets(const DirectoryTree & _tree)
	{
		size_t c = 0;
		std::string strFile = ASSETS_DIR;
		strFile += "/icons/filetypes/DEFAULT.png";
		std::string strFolder = ASSETS_DIR;
		strFolder += "/icons/filetypes/BMP.png";
		for (size_t i = 0; i < _tree.Directories.size(); ++i)
		{
			if (m_vAssets.size() <= c)
			{
				AssetGui* p_gui = new AssetGui;
				p_gui->Image = ari::g_pEngine->texture_manager.Load(strFolder, nullptr);
				p_gui->FileName = _tree.Directories[i].Name;
				if (c % 2 == 1)
					p_gui->SameLine = true;
				m_pDock->AddChild(p_gui);
				m_vAssets.push_back(p_gui);
			}
			else
			{
				m_vAssets[c]->Image = ari::g_pEngine->texture_manager.Load(strFolder, nullptr);
				m_vAssets[c]->FileName = _tree.Directories[i].Name;
				m_vAssets[c]->Visible = true;
			}
			c++;
		}
		for (size_t i = 0; i < _tree.FileList.size(); ++i)
		{
			if (m_vAssets.size() <= c)
			{
				AssetGui* p_gui = new AssetGui;
				p_gui->Image = ari::g_pEngine->texture_manager.Load(strFile, nullptr);
				p_gui->FileName = _tree.FileList[i].Name;
				if (c % 2 == 1)
					p_gui->SameLine = true;
				m_pDock->AddChild(p_gui);
				m_vAssets.push_back(p_gui);
			}
			else
			{
				m_vAssets[c]->Image = ari::g_pEngine->texture_manager.Load(strFile, nullptr);
				m_vAssets[c]->FileName = _tree.FileList[i].Name;
				m_vAssets[c]->Visible = true;
			}
			c++;
		}
		for (size_t i = c; i < m_vAssets.size(); i++)
		{
			m_vAssets[i]->Visible = false;
		}
	}

} // shiva
