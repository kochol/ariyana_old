#include "../../../../include/ari/en/gui/CheckBox.hpp"
#include "../../../../include/ari/en/gui/Dock.hpp"

namespace ari
{
	CheckBox::CheckBox(): Checked(false), Label("")
	{
	}

	void CheckBox::BeginRender()
	{
		ImGui::Checkbox(Label, &Checked);
	}
}
