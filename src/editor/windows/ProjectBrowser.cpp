#include "..\..\..\include\shiva\windows\ProjectBrowser.hpp"
#include "ari/en/gui/Window.hpp"
#include "ari/en/World.hpp"
#include "ari/en/gui/TextBox.hpp"
#include "bx/string.h"

namespace shiva
{
	ProjectBrowser::ProjectBrowser(): m_pWindow(nullptr)
	{
	}

	ProjectBrowser::~ProjectBrowser()
	{
		delete m_pWindow;
		delete m_pNewProjectName;
	}

	void ProjectBrowser::Init(ari::World* p_world)
	{
		p_world->AddEntity(&m_Entity);
		m_pWindow = new ari::Window();
		m_pWindow->Name = "Project Browser";
		m_pWindow->Size.x = 800;
		m_pWindow->Size.y = 600;
		m_pWindow->Flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
		m_Entity.AddChild(m_pWindow);
		//ProjectGui* pPG = new ProjectGui();
		//ProjectGui* pPG2 = new ProjectGui();
		//m_pWindow->AddChild(pPG);
		//m_pWindow->AddChild(pPG2);
		m_pNewProjectName = new ari::TextBox(32);
		m_pNewProjectName->Label = "Project name";
		bx::strCopy(m_pNewProjectName->Text, sizeof(m_pNewProjectName->Text), "Test");
		m_pWindow->AddChild(m_pNewProjectName);
	}

	bool ProjectGui::BeginRender()
	{
		ImGui::BeginGroup();
		{
			ImGui::BeginGroup();
			ImGui::Button("AAA");
			ImGui::SameLine();
			ImGui::Button("BBB");
			ImGui::SameLine();
			ImGui::BeginGroup();
			ImGui::Button("CCC");
			ImGui::Button("DDD");
			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::Button("EEE");
			ImGui::EndGroup();
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("First group hovered");
		}
		// Capture the group size and create widgets using the same size
		ImVec2 size = ImGui::GetItemRectSize();
		const float values[5] = { 0.5f, 0.20f, 0.80f, 0.60f, 0.25f };
		ImGui::PlotHistogram("##values", values, IM_ARRAYSIZE(values), 0, NULL, 0.0f, 1.0f, size);

		ImGui::Button("ACTION", ImVec2((size.x - ImGui::GetStyle().ItemSpacing.x)*0.5f, size.y));
		ImGui::SameLine();
		ImGui::Button("REACTION", ImVec2((size.x - ImGui::GetStyle().ItemSpacing.x)*0.5f, size.y));
		ImGui::EndGroup();

		return false;
	}

	void ProjectGui::EndRender()
	{
	}

} // shiva
