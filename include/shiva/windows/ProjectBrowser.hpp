#pragma once
#include "shiva/shivadef.hpp"
#include "ari/en/Entity.hpp"

namespace ari
{
	class Window;
	class World;

} // ari

namespace shiva
{
	
	class SHIVA_API ProjectBrowser
	{
	public:
		ProjectBrowser();

		~ProjectBrowser();

		void Init(ari::World* p_world);
		
	protected:

		ari::Window		*	m_pWindow;
		ari::Entity			m_Entity;

	}; // ProjectBrowser

} // shiva
