#pragma once
#include "shiva/shivadef.hpp"
#include "ari/en/Entity.hpp"
#include "ari/en/gui/Gui.hpp"
#include "ari/en/gui/Button.hpp"
#include "ari/en/gui/Label.hpp"

namespace ari
{
	class Window;
	class World;
	class TextBox;
	class Popup;

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
		ari::TextBox	*	m_pNewProjectPath;
		ari::Button		*	m_pNewProjectBtn;
		ari::Popup		*	m_pMessageBox;
		ari::Label			m_MbLabel;
		ari::Button			m_MbOkBtn;

		void OnNewProjectClick();
		void OnClickMbOk();

	}; // ProjectBrowser

} // shiva
