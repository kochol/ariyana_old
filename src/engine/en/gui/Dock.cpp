#include "..\..\..\..\include\ari\en\gui\Dock.hpp"
namespace ari
{
	Dock::Dock(): isOpened(false), Label(nullptr), _root(false)
	{
	}

	void Dock::BeginRender()
	{
		if (_root)
			ImGui::RootDock(Pos, Size);

		ImGui::BeginDock(Label, &isOpened);
	}

	void Dock::EndRender()
	{
		ImGui::EndDock();
	}
} // ari
