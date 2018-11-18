#include "../../../../include/ari/en/gui/Image.hpp"
#include "../../../../deps/bgfx/examples/common/imgui/imgui.h"

namespace ari
{
	bool Image::BeginRender()
	{
		ImGui::Image(ImageTxture->Handle, Size);
		return false;
	}

} // ari
