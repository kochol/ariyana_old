#include "../../../../include/ari/en/gui/Label.hpp"
#include "../../../../include/ari/en/gui/Dock.hpp"

namespace ari
{
	Label::Label(): Text(nullptr)
	{
	}

	void Label::BeginRender()
	{
		ImGui::Text(Text);
	}

} // ari
