#pragma once
#include "Gui.hpp"
#include "dear-imgui/imgui.h"

namespace ari
{
	class ARI_API Window: public Gui
	{
	public:
		Window(char* name);

		~Window() = default;

		void BeginRender() override;
		void EndRender() override;

		char	*	Name;
		bool		CloseButton,
					isOpen;
		ImVec2		Pos,
					Size;

	}; // Window

} // ari
