#include "../../../../include/ari/en/gui/GuiSystem.hpp"
#include "../../../../include/ari/en/World.hpp"
#include "../../../../include/ari/en/Entity.hpp"
#include "../../../../include/ari/en/Component.hpp"
#include "../../../../deps/bgfx/examples/common/imgui/imgui.h"
#include "../../../../include/ari/en/gui/Gui.hpp"
#include "bx/macros.h"
#include "../../../../include/ari/Engine.hpp"
#include "../../../../deps/imguiDock/imgui_dock.h"

namespace ari
{
	GuiSystem::GuiSystem(): m_bIsDockCreated(false)
	{
	}

	GuiSystem::~GuiSystem()
	{
		if (m_bIsDockCreated)
			ImGui::ShutdownDock();
	}

	void GuiSystem::Update(World * p_world, UpdateState state)
	{
		if (state == UpdateState::MainThreadState)
		{
			imguiBeginFrame(g_pEngine->m_MouseState.m_mx
				, g_pEngine->m_MouseState.m_my
				, (g_pEngine->m_MouseState.m_buttons[MouseButton::Left] ? IMGUI_MBUT_LEFT : 0)
				| (g_pEngine->m_MouseState.m_buttons[MouseButton::Right] ? IMGUI_MBUT_RIGHT : 0)
				| (g_pEngine->m_MouseState.m_buttons[MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
				, g_pEngine->m_MouseState.m_mz
				, uint16_t(g_pEngine->m_params->Width)
				, uint16_t(g_pEngine->m_params->Height)
			);

			for (auto e: p_world->GetAllEntities())
			{
				RenderGui(e);
			}
			imguiEndFrame();

		}
	}

	void GuiSystem::Configure(World * p_world)
	{
		imguiCreate();
		p_world->subscribe<events::OnComponentAssigned<Dock>>(this);
	}

	void GuiSystem::Unconfigure(World * p_world)
	{
		imguiDestroy();
		p_world->unsubscribeAll(this);
	}

	System::Type GuiSystem::GetSystemType()
	{
		return Type::RenderSystem;
	}

	bool GuiSystem::NeedUpdateOnState(UpdateState state)
	{
		return state == UpdateState::MainThreadState;
	}

	void GuiSystem::Receive(World * world, const events::OnComponentAssigned<Dock>& event)
	{
		BX_UNUSED(world, event);
		if (!m_bIsDockCreated)
		{
			ImGui::InitDock();
			m_bIsDockCreated = true;
		}
	}

	void GuiSystem::RenderGui(Node * node)
	{
		Gui* gui = nullptr;
		bool renderChilds = true;
		if (node->GetType() == Node::Type::Component)
		{
			Component* cmp = reinterpret_cast<Component*>(node);
			if (cmp->_isFromGui)
			{
				gui = reinterpret_cast<Gui*>(cmp);

				if (!gui->Visible)
					return;

				if (gui->SameLine)
					ImGui::SameLine();

				renderChilds = gui->BeginRender();
			}
		}
		if (renderChilds)
			for (auto child : node->GetChildren())
			{
				RenderGui(child);
			}
		if (gui)
			gui->EndRender();
	}

} // ari
