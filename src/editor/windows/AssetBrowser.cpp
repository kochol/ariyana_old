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

	void AssetBrowser::Init(ari::World* p_world)
	{
		m_pDock = new ari::DockableWindow(g_pEditor->GetGuiSystem());
		m_pDock->SetTitle("Asset browser");
		m_pDock->Dock(ari::DockableWindow::Oriention::Left);
		p_world->GetAllEntities()[0]->AddChild(m_pDock);
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
		strFolder += "/icons/filetypes/folder.png";
		if (!_tree.IsRoot)
		{
			std::string strUp = ASSETS_DIR;
			strUp += "/icons/filetypes/folder_up.png";
			m_vAssets[0]->Image = ari::g_pEngine->texture_manager.Load(strUp, nullptr);
			m_vAssets[0]->Path = _tree.Path.get();
			m_vAssets[0]->Path = m_vAssets[0]->Path.substr(0, m_vAssets[0]->Path.rfind('/'));
			m_vAssets[0]->FileName = "..";
			m_vAssets[0]->IsDirectory = true;
			c++;
		}
		for (size_t i = 0; i < _tree.Directories.size(); ++i)
		{
			if (m_vAssets.size() <= c)
			{
				AssetGui* p_gui = new AssetGui;
				p_gui->Image = ari::g_pEngine->texture_manager.Load(strFolder, nullptr);
				p_gui->FileName = _tree.Directories[i].Name;
				p_gui->Path = _tree.Directories[i].Path.get();
				p_gui->IsDirectory = true;
				p_gui->OnDblClick.Bind(this, &AssetBrowser::OnDblClick);
				p_gui->OnRightClick.Bind(this, &AssetBrowser::OnRightClick);
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
				m_vAssets[c]->Path = _tree.Directories[i].Path.get();
				m_vAssets[c]->IsDirectory = true;
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
				p_gui->Path = _tree.Path.get();
				p_gui->IsDirectory = false;
				p_gui->OnDblClick.Bind(this, &AssetBrowser::OnDblClick);
				p_gui->OnRightClick.Bind(this, &AssetBrowser::OnRightClick);
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
				m_vAssets[c]->Path = _tree.Path.get();
				m_vAssets[c]->IsDirectory = false;
			}
			c++;
		}
		for (size_t i = c; i < m_vAssets.size(); i++)
		{
			m_vAssets[i]->Visible = false;
		}
	}

	DirectoryTree* AssetBrowser::FindPathTree(DirectoryTree* _tree, const std::string& _path)
	{
		if (_tree->Path.get() == _path)
			return _tree;
		for (size_t i = 0; i < _tree->Directories.size(); i++)
		{
			const auto r = FindPathTree(&_tree->Directories[i], _path);
			if (r)
				return r;
		}
		return nullptr;
	}

	void AssetBrowser::OnDblClick(AssetGui* _sender)
	{
		if (_sender->IsDirectory)
		{
			DirectoryTree tree = g_pEditor->GetCurrentProject()->GetTree();
			auto r = FindPathTree(&tree, _sender->Path);
			if (r)
				UpdateAssets(*r);
			else
				printf("Can't find the directory %s.", _sender->Path.c_str());
		}
	}

	void AssetBrowser::OnRightClick(AssetGui* _sender)
	{
	}

} // shiva
