#include "../../../../include/ari/en/3d/SceneSystem.hpp"
#include "../../../../include/ari/en/World.hpp"
#include "../../../../include/ari/en/Entity.hpp"
#include "../../../../include/ari/en/3d/Camera.hpp"
#include <bx/math.h>
#include "../../../../include/ari/Engine.hpp"
#include "../../../../include/ari/en/2d/Viewport.hpp"
#include <spdlog/logger.h>
#include "bgfx/bgfx.h"

namespace ari
{
	SceneSystem::SceneSystem(): m_pActiveCamera(nullptr), m_FrameDatasUnused(nullptr), m_FrameDatasTransforms(nullptr),
	                            m_FrameDatasVisible(nullptr)
	{
	}

	SceneSystem::~SceneSystem()
	{
	}

	void SceneSystem::Update(World* p_world, UpdateState state)
	{
		if (state == UpdateState::SceneManagerState)
		{
			if (m_FrameDatasTransforms)
			{
				events::OnFrameData frame_data = { m_FrameDatasTransforms };
				p_world->emit(frame_data);
			}
			m_FrameDatasTransforms = new FrameData;
			m_FrameDatasTransforms->FrameNumber = g_pEngine->GetCurrentFrameNumber();
			m_FrameDatasTransforms->Camera = m_pActiveCamera;
			// Get all entities and calc transforms
			const auto& entities = p_world->GetAllEntities();
			for (auto e : entities)
			{
				CalcTransform(e, nullptr);
			}

			if (m_pActiveCamera)
			{
				bx::mtxLookAt(m_pActiveCamera->_view.v, m_pActiveCamera->Position.ToVec3(),
					m_pActiveCamera->Target.ToVec3(), m_pActiveCamera->Up.ToVec3());

				RectI rect;
				Viewport* p = m_pActiveCamera->GetChild<Viewport>();
				if (p)
					rect = p->Rect;
				else
				{
					g_pEngine->GetMainWindow()->GetSize(rect.width, rect.height);
				}
				bx::mtxProj(m_pActiveCamera->_proj.v, 60.0f, float(rect.width) / float(rect.height), 1.0f, 1000.0f, 
					bgfx::getCaps()->homogeneousDepth);
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
		BX_UNUSED(world, event);
	}

	void SceneSystem::Receive(World * world, const events::OnEntityDestroyed & event)
	{
		BX_UNUSED(world, event);
	}

	void SceneSystem::Receive(World * world, const events::OnComponentAssigned<Camera>& event)
	{
		BX_UNUSED(world);
		if (!m_pActiveCamera)
		{
			m_pActiveCamera = event.component;
			m_pActiveCamera->_isActive = true;
		}
	}

	void SceneSystem::Receive(World * world, const events::OnComponentRemoved<Camera>& event)
	{
		BX_UNUSED(world);
		if (m_pActiveCamera == event.component)
		{
			m_pActiveCamera = nullptr;
		}
	}

	void SceneSystem::Receive(World* world, const events::OnComponentAssigned<BoxShape>& event)
	{
		BX_UNUSED(world, event);
	}

	void SceneSystem::Receive(World* world, const events::OnComponentRemoved<BoxShape>& event)
	{
		BX_UNUSED(world, event);
	}

	void SceneSystem::CalcTransform(Node* node, Matrix* parentMat)
	{
		if (node->GetType() == Node::Type::Component)
		{
			Component* c = reinterpret_cast<Component*>(node);
			if (c->_isFromNode3D)
			{
				Node3D* n = reinterpret_cast<Node3D*>(node);
				Matrix m;
				m.SetTransform(n->Position, n->Rotation, n->Scale);
				if (parentMat)
					n->_finalMat = m * (*parentMat);
				else
					n->_finalMat = m;
				parentMat = &n->_finalMat;

				if (n->_isRenderable)
				{
					// Add it to frame data
					m_FrameDatasTransforms->Nodes.push_back(n);
					m_FrameDatasTransforms->WorldMatrices.push_back(n->_finalMat);
				}
			}
		}
		for (auto child: node->GetChildren())
		{
			CalcTransform(child, parentMat);
		}
	} // CalcTransform
	
} // ari
