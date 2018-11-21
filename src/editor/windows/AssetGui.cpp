#include "AssetGui.hpp"
#include "../../../deps/bgfx/examples/common/imgui/imgui.h"
#include "ari/Engine.hpp"

namespace shiva
{
	AssetGui::AssetGui()
	{
	}

	AssetGui::~AssetGui()
	{
	}

	bool AssetGui::BeginRender()
	{
		ImGui::BeginGroup();
		ImGui::Image(Image->Handle, ImVec2(64, 64));
		ImGui::TextWrapped(FileName.c_str());
		ImGui::EndGroup();
		if (ImGui::IsItemHovered())
		{
			if (OnDblClick.IsBound())
				if (ImGui::IsMouseDoubleClicked(0))
					OnDblClick.Execute(this);
			if (OnRightClick.IsBound())
				if (ImGui::IsMouseClicked(1))
					OnRightClick.Execute(this);
		}
		return false;
	}

} // shiva
