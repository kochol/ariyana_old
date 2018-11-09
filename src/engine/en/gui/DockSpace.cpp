#include "../../../../include/ari/en/gui/DockSpace.hpp"
#include "../../../../deps/imguiDock/imgui_dock.h"

namespace ari
{
	bool DockSpace::BeginRender()
	{
		ImGui::BeginDockspace();
		return true;
	}

	void DockSpace::EndRender()
	{
		ImGui::EndDockspace();
	}

} // ari
