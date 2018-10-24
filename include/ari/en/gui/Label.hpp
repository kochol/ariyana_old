#pragma once
#include "Gui.hpp"

namespace ari
{
	class ARI_API Label : public Gui
	{
	public:

		//! Constructor
		Label();

		~Label() = default;

		bool BeginRender() override;

		char	*	Text;
	};
	
}
