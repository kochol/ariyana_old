#include "../../../../include/ari/en/gui/CheckBox.hpp"
#include "../../../../include/ari/en/gui/Dock.hpp"

namespace ari
{
	CheckBox::CheckBox(): Checked(false), Label("")
	{
	}

	bool CheckBox::BeginRender()
	{
		ImGui::Checkbox(Label, &Checked);
		return true;
	}
}
