#include "../../../../include/ari/en/3d/RenderSystem.hpp"
#include "../../../../include/ari/en/3d/BoxShape.hpp"
#include "../../../../include/ari/en/3d/Camera.hpp"
#include "../../../../include/ari/en/2d/Viewport.hpp"
#include "../../../../include/ari/en/World.hpp"
#include "../../../../include/ari/gfx/FrameData.hpp"
#include <bgfx/bgfx.h>
#include <brtshaderc.h>
#include "tinystl/string.h"

namespace ari
{
	char* g_AssetDir = ASSETS_DIR;

	RenderSystem::RenderSystem(): m_pVertexDeclArray(nullptr), m_Program(nullptr), m_pFrameDataCurrent(nullptr),
	                              m_pFrameDataNext(nullptr)
	{
	}

	RenderSystem::~RenderSystem()
	{
		delete[] m_pVertexDeclArray;
		BoxShape::Shutdown();
		bgfx::destroy(*m_Program);
		delete m_Program;
	}

	void RenderSystem::Update(World * p_world, UpdateState state)
	{
		if (state == UpdateState::MainThreadState)
		{
			m_pFrameDataCurrent = m_pFrameDataNext;
			if (m_pFrameDataCurrent)
				// Set the camera
				if (m_pFrameDataCurrent->Camera)
				{
					bgfx::setViewTransform(0, m_pFrameDataCurrent->Camera->_view.v,
						m_pFrameDataCurrent->Camera->_proj.v);

					// Set viewport
					Viewport* pViewport = m_pFrameDataCurrent->Camera->GetChild<Viewport>();
					if (pViewport)
					{
						bgfx::setViewRect(0, pViewport->Rect.x, pViewport->Rect.y, 
							pViewport->Rect.width, pViewport->Rect.height);
					}
				}
		}
		else if (state == UpdateState::GameplayState)
		{
			bgfx::Encoder* encoder = nullptr;
			if (p_world->GetUpdateType() == World::UpdateType::Async)
			{
				encoder = bgfx::begin();
			}
			if (m_pFrameDataCurrent)
			{
				for (size_t i = 0; i < m_pFrameDataCurrent->Nodes.size(); i++)
				{
					m_pFrameDataCurrent->Nodes[i]->Render(m_pFrameDataCurrent->WorldMatrices[i], encoder);
				}
				delete m_pFrameDataCurrent;
			}
			if (p_world->GetUpdateType() == World::UpdateType::Async)
			{
				bgfx::end(encoder);
			}
		}
	} // Update

	void RenderSystem::Configure(World * p_world)
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

		// compile vertex shader, with default arguments.
		tinystl::string shaderFile = g_AssetDir;
		shaderFile.append("/shaders/basic/vs_basic.glsl");
		const bgfx::Memory* memVsh = shaderc::compileShader(shaderc::ST_VERTEX, shaderFile.c_str());
		bgfx::ShaderHandle vsh = bgfx::createShader(memVsh);

		// compile fragment shader, with specific arguments for defines, varying def file, shader profile.
		shaderFile = g_AssetDir;
		shaderFile.append("/shaders/basic/fs_basic.glsl");
		const bgfx::Memory* memFsh = shaderc::compileShader(shaderc::ST_FRAGMENT, shaderFile.c_str());
		bgfx::ShaderHandle fsh = bgfx::createShader(memFsh);

		// build program using shaders
		m_Program = new bgfx::ProgramHandle();
		*m_Program = bgfx::createProgram(vsh, fsh, true);

		p_world->subscribe<events::OnComponentAssigned<BoxShape>>(this);
		p_world->subscribe<events::OnFrameData>(this);

	} // Configure

	void RenderSystem::Unconfigure(World * p_world)
	{
		p_world->unsubscribeAll(this);

	} // Unconfigure

	bool RenderSystem::NeedUpdateOnState(UpdateState state)
	{
		switch (state)
		{
		case UpdateState::GameplayState:
		case UpdateState::MainThreadState:
			return true;
		default:
			return false;
		}
	}

	void RenderSystem::Receive(World * world, const events::OnComponentAssigned<BoxShape>& event)
	{
		BX_UNUSED(world, event);
		BoxShape::Init(this);
	}

	void RenderSystem::Receive(World * world, const events::OnFrameData & event)
	{	
		BX_UNUSED(world);
		m_pFrameDataNext = event.frame_data;		
	}

	bgfx::VertexDecl * RenderSystem::GetVertexDecl(VertexType vertex_type) const
	{
		return &m_pVertexDeclArray[(int)vertex_type];
	}

} // ari
