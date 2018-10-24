#include "../../../../include/ari/en/gui/Window.hpp"

namespace ari
{
	Window::Window(): Name(nullptr), CloseButton(false), isOpen(true)
	{
	}

	bool Window::BeginRender()
	{
		ImGui::SetNextWindowPos(
			Pos
			, ImGuiCond_FirstUseEver
		);
		ImGui::SetNextWindowSize(
			Size
			, ImGuiCond_FirstUseEver
		);
		if (CloseButton)
			return ImGui::Begin(Name
				, &isOpen
				, 0
			);
		else
			return ImGui::Begin(Name
				, nullptr
				, 0
			);
	}

	void Window::EndRender()
	{
		ImGui::End();
	}

} // ari
