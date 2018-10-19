#include "..\..\..\..\include\ari\en\gui\Window.hpp"
namespace ari
{
	Window::Window(char * name): Name(name), CloseButton(false), isOpen(true)
	{
	}

	void Window::BeginRender()
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
			ImGui::Begin(Name
				, &isOpen
				, 0
			);
		else
			ImGui::Begin(Name
				, nullptr
				, 0
			);
	}

	void Window::EndRender()
	{
		ImGui::End();
	}

} // ari
