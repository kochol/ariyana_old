#pragma once
#include "Gui.hpp"
#include "../../Delegate.hpp"

namespace ari
{
	class ARI_API Button: public Gui
	{
	public:

		bool BeginRender() override;

		DelegateNoParam<void> OnClick;

		char* Label;
	};
} // ari
