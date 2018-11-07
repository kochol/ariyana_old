#include "../../../../include/ari/en/gui/Popup.hpp"
#include <dear-imgui/imgui.h>

namespace ari
{
	bool Popup::BeginRender()
	{
		if (m_bOpenPopup)
		{
			ImGui::OpenPopup(Name);
			m_bOpenPopup = false;
		}
		m_bDoEndPopup = ImGui::BeginPopup(Name);
		return m_bDoEndPopup;
	}

	void Popup::EndRender()
	{
		if (m_bDoEndPopup)
			ImGui::EndPopup();
	}

	void Popup::Show()
	{
		m_bOpenPopup = true;
	}

	void Popup::Hide()
	{
		ImGui::CloseCurrentPopup();
	}

} // ari
