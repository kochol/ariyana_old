#include "..\..\..\include\shiva\windows\ProjectBrowser.hpp"
#include "ari/en/gui/Window.hpp"
#include "ari/en/World.hpp"
#include "ari/en/gui/TextBox.hpp"
#include "bx/string.h"
#include "bx/filepath.h"
#include "shiva/Project.hpp"
#include "ari/en/gui/Popup.hpp"
#include "shiva/Editor.hpp"
#include "ari/en/gui/DockableWindow.hpp"
#include "shiva/EditorSettings.hpp"

void testOnClick()
{
	printf("new project button clicked\n");
}

namespace shiva
{
	ProjectBrowser::ProjectBrowser(): m_pEntity(nullptr), m_pNewProjectName(nullptr),
	                                  m_pNewProjectPath(nullptr), m_pOpenProjectPath(nullptr),
									  m_pOpenProjectBtn(nullptr),
	                                  m_pNewProjectBtn(nullptr), m_pMessageBox(nullptr), m_pMbLabel(nullptr),
	                                  m_pMbOkBtn(nullptr)
	{
	}

	ProjectBrowser::~ProjectBrowser()
	{
		Shutdown();
	}

	void ProjectBrowser::Init(ari::World* p_world)
	{
		m_pEntity = new ari::Entity;
		p_world->AddEntity(m_pEntity);

		// Init Project browser window.
		m_pWindow = new ari::DockableWindow(g_pEditor->GetGuiSystem());
		m_pWindow->SetTitle("Project Browser");
		m_pEntity->AddChild(m_pWindow);
		m_pNewProjectName = new ari::TextBox(32);
		m_pNewProjectName->Label = "Project name";
		m_pNewProjectName->SetText("New project");
		m_pWindow->AddChild(m_pNewProjectName);
		m_pNewProjectPath = new ari::TextBox(512);
		m_pNewProjectPath->Label = "Project path";
		m_pNewProjectPath->SetText(bx::FilePath(bx::Dir::Home).get());
		m_pWindow->AddChild(m_pNewProjectPath);
		m_pNewProjectBtn = new ari::Button();
		m_pNewProjectBtn->Label = "New project";
		m_pNewProjectBtn->OnClick.Bind(this, &ProjectBrowser::OnNewProjectClick);
		m_pWindow->AddChild(m_pNewProjectBtn);

		// Init open project textbox
		m_pOpenProjectPath = new ari::TextBox(512);
		m_pOpenProjectPath->Label = "Project path to open";
		m_pOpenProjectPath->Separator = true;
		m_pOpenProjectPath->SetText(EditorSettings::Get().LastProjectPath.c_str());
		m_pWindow->AddChild(m_pOpenProjectPath);
		m_pOpenProjectBtn = new ari::Button();
		m_pOpenProjectBtn->Label = "Open project";
		m_pOpenProjectBtn->OnClick.Bind(this, &ProjectBrowser::OnOpenProjectClick);
		m_pWindow->AddChild(m_pOpenProjectBtn);

		// Init message window
		m_pMessageBox = new ari::Popup;
		m_pMessageBox->Name = "MessageBox";
		ari::Window* p_window = new ari::Window;
		p_window->Name = "M";
		p_window->Pos.x = -1000;
		p_window->Flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoInputs | 
			ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar;
		m_pEntity->AddChild(p_window);
		p_window->AddChild(m_pMessageBox);
		m_pMbLabel = new ari::Label;
		m_pMessageBox->AddChild(m_pMbLabel);
		m_pMbOkBtn = new ari::Button;
		m_pMbOkBtn->Label = "OK";
		m_pMbOkBtn->OnClick.Bind(this, &ProjectBrowser::OnClickMbOk);
		m_pMessageBox->AddChild(m_pMbOkBtn);
	}

	void ProjectBrowser::Shutdown()
	{
		if (m_pEntity)
		{
			m_pEntity->Destroy();
			m_pEntity = nullptr;
			m_pWindow = nullptr;
			m_pNewProjectName = nullptr;
			m_pNewProjectPath = nullptr;
			m_pNewProjectBtn = nullptr;
			m_pOpenProjectPath = nullptr;
			m_pOpenProjectBtn = nullptr;
			m_pMessageBox = nullptr;
			m_pMbLabel = nullptr;
			m_pMbOkBtn = nullptr;			
		}
	}

	void ProjectBrowser::OnNewProjectClick()
	{
		bx::Error err;
		Project* p = Project::New(bx::FilePath(m_pNewProjectPath->Text), m_pNewProjectName->Text, &err);
		if (p)
		{
			ProjectOpened(p);
		}
		else
		{
			m_pMbLabel->Text = err.getMessage().getPtr();
			m_pMessageBox->Show();
		}
	}

	void ProjectBrowser::OnOpenProjectClick()
	{
		bx::Error err;
		Project* p = Project::Load(bx::FilePath(m_pOpenProjectPath->Text), &err);
		if (p)
		{
			ProjectOpened(p);
		}
		else
		{
			m_pMbLabel->Text = err.getMessage().getPtr();
			m_pMessageBox->Show();
		}
	}

	void ProjectBrowser::OnClickMbOk()
	{
		m_pMessageBox->Hide();
	}

	void ProjectBrowser::ProjectOpened(Project* project)
	{
		g_pEditor->LoadProject(project);
		Shutdown();
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
