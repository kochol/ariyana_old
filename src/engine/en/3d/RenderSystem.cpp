#include "../../../../include/ari/en/3d/RenderSystem.hpp"
#include "../../../../include/ari/en/3d/BoxShape.hpp"
#include "../../../../include/ari/en/World.hpp"
#include <bgfx/bgfx.h>
#include "../../gfx/ShadersCode.hpp"
#include <brtshaderc.h>
#include "bx/filepath.h"
#include "tinystl/string.h"

namespace ari
{
	char* g_AssetDir = ASSETS_DIR;

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

		// compile vertex shader, with default arguments.
		tinystl::string shaderFile = g_AssetDir;
		shaderFile.append("/shaders/basic/vs_basic.sc");
		const bgfx::Memory* memVsh = shaderc::compileShader(shaderc::ST_VERTEX, shaderFile.c_str());
		bgfx::ShaderHandle vsh = bgfx::createShader(memVsh);

		// compile fragment shader, with specific arguments for defines, varying def file, shader profile.
		shaderFile = g_AssetDir;
		shaderFile.append("/shaders/basic/fs_basic.sc");
		const bgfx::Memory* memFsh = shaderc::compileShader(shaderc::ST_FRAGMENT, shaderFile.c_str());
		bgfx::ShaderHandle fsh = bgfx::createShader(memFsh);

		// build program using shaders
		m_Program = new bgfx::ProgramHandle();
		*m_Program = bgfx::createProgram(vsh, fsh, true);
	}

	RenderSystem::~RenderSystem()
	{
		delete[] m_pVertexDeclArray;
		BoxShape::Shutdown();
		bgfx::destroy(*m_Program);
		delete m_Program;
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
