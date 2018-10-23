#pragma once
#include "shivadef.hpp"
#include "ari/en/World.hpp"
#include "ari/en/gui/GuiSystem.hpp"

namespace shiva
{
	class SHIVA_API Editor
	{
	public:
		
		void Init();

	protected:

		ari::World		m_EditorWorld;
		ari::GuiSystem	m_GuiSystem;

	}; // Editor

} // shiva
