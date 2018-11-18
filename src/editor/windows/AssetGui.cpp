#include "AssetGui.hpp"
#include "../../../deps/bgfx/examples/common/imgui/imgui.h"
#include "ari/Engine.hpp"

namespace shiva
{
	AssetGui::AssetGui()
	{
		std::string str = ASSETS_DIR;
		str += "/icons/filetypes/BMP.png";
		Image = ari::g_pEngine->texture_manager.Load(str, nullptr);
	}

	AssetGui::~AssetGui()
	{
	}

	bool AssetGui::BeginRender()
	{
		ImGui::Image(Image->Handle, ImVec2(20, 20));
		return false;
	}

} // shiva
