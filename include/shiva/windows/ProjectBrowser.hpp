#pragma once
#include "shiva/shivadef.hpp"
#include "ari/en/Entity.hpp"
#include "ari/en/gui/Gui.hpp"

namespace ari
{
	class Window;
	class World;
	class TextBox;

} // ari

namespace shiva
{
	/*!
	 * Custom GUI component to show a project in the list.
	 */
	class ProjectGui: public ari::Gui
	{
	public:
		bool BeginRender() override;
		void EndRender() override;

	}; // ProjectGui

	class SHIVA_API ProjectBrowser
	{
	public:
		ProjectBrowser();

		~ProjectBrowser();

		void Init(ari::World* p_world);
		
	protected:

		ari::Window		*	m_pWindow;
		ari::Entity			m_Entity;
		ari::TextBox	*	m_pNewProjectName;

	}; // ProjectBrowser

} // shiva
