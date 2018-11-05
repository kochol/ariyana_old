#include "..\..\..\..\include\ari\en\gui\Button.hpp"
#include "../../../../include/ari/en/gui/Dock.hpp"

namespace ari
{
	bool Button::BeginRender()
	{
		if (ImGui::Button(Label) && OnClick.IsBound())
		{
			OnClick.Execute();
		}
		return false;
	}

} // ari
