#pragma once
#include "ari/en/gui/Gui.hpp"
#include "ari/gfx/Texture.hpp"
#include "ari/Delegate.hpp"

namespace shiva
{
	class AssetGui: public ari::Gui
	{
	public:
		AssetGui();
		~AssetGui() override;
		bool BeginRender() override;

		std::shared_ptr<ari::Texture>	Image;
		std::string						FileName,
										Path;
		bool							IsDirectory;
		ari::DelegateOneParam<void, AssetGui*>
										OnDblClick,
										OnRightClick;
	};

} // shiva
