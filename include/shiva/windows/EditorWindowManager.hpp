#pragma once
#include "shiva/shivadef.hpp"

namespace ari 
{
	class World;
	class Entity;
	class DockSpace;
	class Window;
}

namespace shiva
{
	class AssetBrowser;
	class Project;

	class SHIVA_API EditorWindowManager
	{
	public:

		EditorWindowManager();

		~EditorWindowManager();

		void Init(ari::World* pWorld);

		void ShutDown();

	protected:

		ari::Entity			*	m_pEntity = nullptr;
		AssetBrowser		*	m_pAssetBrowser = nullptr;
				
	}; // EditorWindowManager

} // shiva
