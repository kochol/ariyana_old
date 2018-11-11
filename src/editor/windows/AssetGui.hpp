#pragma once
#include "ari/en/gui/Gui.hpp"

namespace shiva
{
	class AssetGui: public ari::Gui
	{
	public:
		~AssetGui() override;
		bool BeginRender() override;
	};

} // shiva
