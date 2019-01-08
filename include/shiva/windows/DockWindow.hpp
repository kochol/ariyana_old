#pragma once
#include "shiva/shivadef.hpp"
#include "ari/en/gui/DockableWindow.hpp"
#include "ari/en/Entity.hpp"

namespace shiva
{
	/*!
	 * DockWindow is the base class for other windows in editor.
	 */
	class SHIVA_API DockWindow
	{
	public:

		virtual ~DockWindow() = default;

		ari::DockableWindow* GetDock() const { return m_pWindow; }

		virtual void Init(ari::World* p_world) = 0;

	protected:

		ari::Entity			*	m_pEntity = nullptr;
		ari::DockableWindow	*	m_pWindow = nullptr;

	};

} // shiva
