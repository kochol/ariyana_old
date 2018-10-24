#pragma once
#include "shivadef.hpp"
#include "ari/en/World.hpp"
#include "ari/en/gui/GuiSystem.hpp"
#include "windows/ProjectBrowser.hpp"

namespace shiva
{
	class SHIVA_API Editor
	{
	public:
		
		void Init();

		void Update(float elasped);

	protected:

		ari::World		m_EditorWorld;
		ari::GuiSystem	m_GuiSystem;
		ProjectBrowser	m_ProjectBrowser;

	}; // Editor

} // shiva
