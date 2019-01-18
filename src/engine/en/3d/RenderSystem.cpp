#include "../../../../include/ari/en/3d/RenderSystem.hpp"
#include "../../../../include/ari/en/3d/BoxShape.hpp"
#include "../../../../include/ari/en/3d/Camera.hpp"
#include "../../../../include/ari/en/2d/Viewport.hpp"
#include "../../../../include/ari/en/World.hpp"
#include "../../../../include/ari/gfx/FrameData.hpp"
#include <bgfx/bgfx.h>
#include <brtshaderc.h>
#include "tinystl/string.h"
#include "../../../../include/ari/Engine.hpp"

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
			m_view_id = 0;
			m_pFrameDataCurrent = m_pFrameDataNext;
			if (m_pFrameDataCurrent)
				// Set the camera
				if (m_pFrameDataCurrent->Camera)
				{
					// Set viewport
					Viewport* pViewport = m_pFrameDataCurrent->Camera->GetChild<Viewport>();
					if (pViewport)
					{
						m_view_id = pViewport->m_view_id;

						// Check if we need create a frame buffer or not.
						if (pViewport->TextureFormat != bgfx::TextureFormat::Count
							&& (!bgfx::isValid(pViewport->m_frame_buffer_handle)
								|| pViewport->Rect != pViewport->m_last_rect))
						{
							pViewport->m_last_rect = pViewport->Rect;
							uint32_t msaa = g_pEngine->GetMsaaFlags();
							if (!pViewport->UseMSAA)
								msaa = 0;

							if (bgfx::isValid(pViewport->m_frame_buffer_handle))
							{
								bgfx::destroy(pViewport->m_frame_buffer_handle);
							}
							else
							{
								pViewport->m_view_id = g_pEngine->GetNewViewId();
								m_view_id = pViewport->m_view_id;
							}

							bgfx::TextureHandle th[2];

							th[0] = bgfx::createTexture2D(
								pViewport->Rect.width - pViewport->Rect.x,
								pViewport->Rect.height - pViewport->Rect.y,
								false,
								1,
								pViewport->TextureFormat,
								(uint64_t(msaa + 1) << BGFX_TEXTURE_RT_MSAA_SHIFT) | BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP
							);

							pViewport->m_texture.Handle = th[0];

							// Create depth buffer
							if (pViewport->CreateDepth)
							{
								const uint64_t textureFlags = BGFX_TEXTURE_RT_WRITE_ONLY | (uint64_t(msaa + 1) << BGFX_TEXTURE_RT_MSAA_SHIFT);

								bgfx::TextureFormat::Enum depthFormat =
									bgfx::isTextureValid(0, false, 1, bgfx::TextureFormat::D16, textureFlags) ? bgfx::TextureFormat::D16
									: bgfx::isTextureValid(0, false, 1, bgfx::TextureFormat::D24S8, textureFlags) ? bgfx::TextureFormat::D24S8
									: bgfx::TextureFormat::D32
									;

								th[1] = bgfx::createTexture2D(
									pViewport->Rect.width - pViewport->Rect.x,
									pViewport->Rect.height - pViewport->Rect.y,
									false,
									1,
									depthFormat,
									textureFlags
								);

								pViewport->m_depth_texture.Handle = th[1];
							}

							// Create frame buffer
							pViewport->m_frame_buffer_handle = bgfx::createFrameBuffer(
								pViewport->CreateDepth ? 2 : 1,
								th,
								true
							);
						}

						if (bgfx::isValid(pViewport->m_frame_buffer_handle))
						{
							bgfx::setViewFrameBuffer(pViewport->m_view_id, pViewport->m_frame_buffer_handle);
							bgfx::setViewClear(pViewport->m_view_id, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
								0x303030ff, 1.0f, 0);
						}

						bgfx::setViewRect(pViewport->m_view_id, pViewport->Rect.x, pViewport->Rect.y,
							pViewport->Rect.width, pViewport->Rect.height);

					}
					bgfx::setViewTransform(m_view_id, m_pFrameDataCurrent->Camera->_view.v,
						m_pFrameDataCurrent->Camera->_proj.v);
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
					m_pFrameDataCurrent->Nodes[i]->Render(m_pFrameDataCurrent->WorldMatrices[i], encoder, m_view_id);
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
