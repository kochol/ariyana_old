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
	class Viewport;
	class Project;
	class PropertyEditor;

	class SHIVA_API EditorWindowManager
	{
	public:

		EditorWindowManager();

		~EditorWindowManager();

		void Init(ari::World* pWorld);

		void Shutdown();

	protected:

		ari::Entity			*	m_pEntity			= nullptr;
		AssetBrowser		*	m_pAssetBrowser		= nullptr;
		Viewport			*	m_pViewport			= nullptr;
		PropertyEditor		*	m_pPropertyEditor	= nullptr;

	}; // EditorWindowManager

} // shiva
