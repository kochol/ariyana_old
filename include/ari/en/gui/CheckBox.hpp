#pragma once
#include "Gui.hpp"

namespace ari
{
	class ARI_API CheckBox: public Gui
	{
	public:
		
		CheckBox();

		~CheckBox() = default;

		bool BeginRender() override;

		bool		Checked;
		char	*	Label;
	};
	
} // ari
