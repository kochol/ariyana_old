#include "..\..\..\..\include\ari\en\gui\Dock.hpp"
#include "../../../../deps/imguiDock/imgui_dock.h"

namespace ari
{
	Dock::Dock(): isOpened(true), Label(nullptr), _root(false)
	{
	}

	bool Dock::BeginRender()
	{
		return ImGui::BeginDock(Label, &isOpened);
	}

	void Dock::EndRender()
	{
		ImGui::EndDock();
	}

} // ari
