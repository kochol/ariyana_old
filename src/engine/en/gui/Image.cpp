#include "../../../../include/ari/en/gui/Image.hpp"
#include "../../../../deps/bgfx/examples/common/imgui/imgui.h"

namespace ari
{
	bool Image::BeginRender()
	{
		ImGui::Image(ImageTexture->Handle, Size);

		if (OnHovered.IsBound() && ImGui::IsItemHovered())
			OnHovered.Execute();

		return false;
	}

} // ari
