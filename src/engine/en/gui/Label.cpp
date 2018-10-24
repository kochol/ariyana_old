#include "../../../../include/ari/en/gui/Label.hpp"
#include "../../../../include/ari/en/gui/Dock.hpp"

namespace ari
{
	Label::Label(): Text(nullptr)
	{
	}

	bool Label::BeginRender()
	{
		ImGui::Text(Text);
		return true;
	}

} // ari
