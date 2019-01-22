#pragma once
#include "Gui.hpp"
#include "../../gfx/Texture.hpp"
#include "dear-imgui/imgui.h"
#include "../../Delegate.hpp"

namespace ari
{
	class ARI_API Image: public Gui
	{
	public:
		bool BeginRender() override;

		std::shared_ptr<Texture>	ImageTexture;
		ImVec2						Size;
		DelegateNoParam<void>		OnHovered;

	}; // Image

} // ari
