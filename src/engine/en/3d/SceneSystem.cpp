#include "../../../../include/ari/en/3d/SceneSystem.hpp"
#include "../../../../include/ari/en/World.hpp"
#include "../../../../include/ari/en/3d/Camera.hpp"
#include "../../../../deps/bgfx/src/renderer_mtl.h"

namespace ari
{
	SceneSystem::SceneSystem(): m_pActiveCamera(nullptr)
	{
	}

	SceneSystem::~SceneSystem()
	{
	}

	void SceneSystem::Update(World* p_world, float tick)
	{
		// Get all entities
		const auto& entities = p_world->GetAllEntities();

		if (m_pActiveCamera)
		{
			bx::mtxLookAt(m_pActiveCamera->_view.v, m_pActiveCamera->Position.v,
				m_pActiveCamera->Target.v, m_pActiveCamera->Up.v);
		}
	}

	void SceneSystem::Configure(World * p_world)
	{
		p_world->subscribe<events::OnEntityCreated>(this);
		p_world->subscribe<events::OnEntityDestroyed>(this);
		p_world->subscribe<events::OnComponentAssigned<Camera>>(this);
		p_world->subscribe<events::OnComponentRemoved<Camera>>(this);
		p_world->subscribe<events::OnComponentAssigned<BoxShape>>(this);
		p_world->subscribe<events::OnComponentRemoved<BoxShape>>(this);
	}

	void SceneSystem::Unconfigure(World * p_world)
	{
		p_world->unsubscribeAll(this);
	}

	void SceneSystem::Receive(World * world, const events::OnEntityCreated & event)
	{
	}

	void SceneSystem::Receive(World * world, const events::OnEntityDestroyed & event)
	{
	}

	void SceneSystem::Receive(World * world, const events::OnComponentAssigned<Camera>& event)
	{
		if (!m_pActiveCamera)
		{
			m_pActiveCamera = event.component;
			m_pActiveCamera->_isActive = true;
		}
	}

	void SceneSystem::Receive(World * world, const events::OnComponentRemoved<Camera>& event)
	{
		if (m_pActiveCamera == event.component)
		{
			m_pActiveCamera = nullptr;
		}
	}

	void SceneSystem::Receive(World* world, const events::OnComponentAssigned<BoxShape>& event)
	{
	}

	void SceneSystem::Receive(World* world, const events::OnComponentRemoved<BoxShape>& event)
	{
	}
} // ari
