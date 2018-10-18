#include "../../../../include/ari/en/gui/GuiSystem.hpp"
#include "../../../../deps/bgfx/examples/common/imgui/imgui.h"

namespace ari
{
	GuiSystem::GuiSystem(): m_bIsDockCreated(false)
	{
	}

	GuiSystem::~GuiSystem()
	{
		if (m_bIsDockCreated)
			ImGui::ShutdownDockContext();
	}

	void GuiSystem::Update(World * p_world, UpdateState state)
	{
		if (state == UpdateState::MainThreadState)
		{
			
		}
	}

	void GuiSystem::Configure(World * p_world)
	{
		imguiCreate();
	}

	void GuiSystem::Unconfigure(World * p_world)
	{
		imguiDestroy();
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
		if (!m_bIsDockCreated)
		{
			ImGui::InitDockContext();
			m_bIsDockCreated = true;
		}
	}

} // ari
