#include "../../../../include/ari/en/3d/SceneSystem.hpp"
#include "../../../../include/ari/en/World.hpp"
#include "../../../../include/ari/en/Entity.hpp"
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

	void SceneSystem::Update(World* p_world, UpdateState state)
	{
		if (state == UpdateState::SceneManagerState)
		{
			// Get all entities and calc transforms
			const auto& entities = p_world->GetAllEntities();
			for (auto e : entities)
			{
				CalcTransform(e, nullptr);
			}

			if (m_pActiveCamera)
			{
				bx::mtxLookAt(m_pActiveCamera->_view.v, m_pActiveCamera->Position.v,
					m_pActiveCamera->Target.v, m_pActiveCamera->Up.v);
				bx::mtxProj(m_pActiveCamera->_proj.v, 0.5f, 640.0f / 480.0f, 1.0f, 1000.0f, false);
			}
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

	bool SceneSystem::NeedUpdateOnState(UpdateState state)
	{
		switch (state)
		{
		case UpdateState::GameplayState:
		case UpdateState::SceneManagerState:
			return true;
		default:
			return false;
		}
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

	void SceneSystem::CalcTransform(Node* node, Matrix* parentMat)
	{
		if (node->GetType() == Node::Type::Component)
		{
			Component* c = static_cast<Component*>(node);
			if (c->IsFromNode3D)
			{
				Node3D* n = static_cast<Node3D*>(node);
				Matrix m;
				m.SetTransform(n->Position, n->Rotation, n->Scale);
				if (parentMat)
					n->_finalMat = (*parentMat) * m;
				else
					n->_finalMat = m;
				parentMat = &n->_finalMat;
			}
		}
		for (auto child: node->GetChildren())
		{
			CalcTransform(child, parentMat);
		}
	}
} // ari
