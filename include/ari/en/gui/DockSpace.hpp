#pragma once
#include "Gui.hpp"

namespace ari
{
	class ARI_API DockSpace: public Gui
	{
	public:

		bool BeginRender() override;
		void EndRender() override;

	}; // DockSpace

} // ari
