#pragma once
#include "Gui.hpp"
#include "../../gfx/Texture.hpp"
#include "dear-imgui/imgui.h"

namespace ari
{
	class ARI_API Image: public Gui
	{
	public:
		bool BeginRender() override;

		std::shared_ptr<Texture>	ImageTxture;
		ImVec2						Size;

	}; // Image

} // ari
