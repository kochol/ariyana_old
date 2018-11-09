#pragma once
#include "Gui.hpp"
#include "dear-imgui/imgui.h"

namespace ari
{
	class ARI_API Dock: public Gui
	{
	public:

		Dock();

		~Dock() = default;

		bool BeginRender() override;

		void EndRender() override;

		bool	isOpened;
		char*	Label;

	}; // Dock

} // ari
