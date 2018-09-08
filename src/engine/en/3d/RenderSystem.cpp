#include "..\..\..\..\include\ari\en\3d\RenderSystem.hpp"
#include "..\..\..\..\include\ari\en\3d\BoxShape.hpp"
#include "../../../../include/ari/en/World.hpp"
#include <bgfx/bgfx.h>

namespace ari
{
	RenderSystem::RenderSystem()
	{
		// Create vertex declarations
		m_pVertexDeclArray = new bgfx::VertexDecl[(int)VertexType::Count];
		m_pVertexDeclArray[(int)VertexType::Pos]
			.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.end();
		m_pVertexDeclArray[(int)VertexType::Color]
			.begin()
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
			.end();
	}

	RenderSystem::~RenderSystem()
	{
		delete[] m_pVertexDeclArray;
		BoxShape::Shutdown();
	}

	void RenderSystem::Update(World * p_world, float tick)
	{
	} // Update

	void RenderSystem::Configure(World * p_world)
	{
		p_world->subscribe<events::OnComponentAssigned<BoxShape>>(this);

	} // Configure

	void RenderSystem::Unconfigure(World * p_world)
	{
		p_world->unsubscribeAll(this);

	} // Unconfigure

	void RenderSystem::Receive(World * world, const events::OnComponentAssigned<BoxShape>& event)
	{
		BoxShape::Init(this);
	}

	bgfx::VertexDecl * RenderSystem::GetVertexDecl(VertexType vertex_type) const
	{
		return &m_pVertexDeclArray[(int)vertex_type];
	}

} // ari
