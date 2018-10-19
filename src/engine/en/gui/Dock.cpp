#include "..\..\..\..\include\ari\en\gui\Dock.hpp"
namespace ari
{
	Dock::Dock(): isOpened(true), Label(nullptr), _root(false)
	{
	}

	void Dock::BeginRender()
	{
		ImGui::BeginDock(Label, &isOpened);
		if (_root)
		{
			ImGui::RootDock(Pos, Size);
		}
	}

	void Dock::EndRender()
	{
		if (isOpened)
			ImGui::EndDock();
	}

} // ari
