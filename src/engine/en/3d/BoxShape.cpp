#include "bgfx/bgfx.h"
#include "../../../../include/ari/en/3d/BoxShape.hpp"
#include "../../../../include/ari/en/3d/RenderSystem.hpp"
#include "../../../../include/ari/gfx/Vertices.hpp"

namespace ari
{
	bgfx::VertexBufferHandle BoxShape::m_sVBPos BGFX_INVALID_HANDLE;
	bgfx::VertexBufferHandle BoxShape::m_sVBColor BGFX_INVALID_HANDLE;
	bgfx::IndexBufferHandle	BoxShape::m_sIB BGFX_INVALID_HANDLE;

	static PosVertex s_cubePosVertices[] =
	{
		{ -1.0f,  1.0f,  1.0f },
		{ 1.0f,  1.0f,  1.0f },
		{ -1.0f, -1.0f,  1.0f },
		{ 1.0f, -1.0f,  1.0f },
		{ -1.0f,  1.0f, -1.0f },
		{ 1.0f,  1.0f, -1.0f },
		{ -1.0f, -1.0f, -1.0f },
		{ 1.0f, -1.0f, -1.0f },
	};

	static ColorVertex s_cubeColorVertices[] =
	{
		{ 0xff000000 },
		{ 0xff0000ff },
		{ 0xff00ff00 },
		{ 0xff00ffff },
		{ 0xffff0000 },
		{ 0xffff00ff },
		{ 0xffffff00 },
		{ 0xffffffff },
	};

	static const uint16_t s_cubeTriList[] =
	{
		0, 1, 2, // 0
		1, 3, 2,
		4, 6, 5, // 2
		5, 6, 7,
		0, 2, 4, // 4
		4, 2, 6,
		1, 5, 3, // 6
		5, 7, 3,
		0, 4, 1, // 8
		4, 5, 1,
		2, 3, 6, // 10
		6, 3, 7,
	};

	void BoxShape::Init(RenderSystem * render_system)
	{
		if (!bgfx::isValid(m_sVBPos))
		{
			// Create static vertex buffer.
			m_sVBPos = bgfx::createVertexBuffer(
				// Static data can be passed with bgfx::makeRef
				bgfx::makeRef(s_cubePosVertices, sizeof(s_cubePosVertices))
				, *render_system->GetVertexDecl(RenderSystem::VertexType::Pos)
			);

			m_sVBColor = bgfx::createVertexBuffer(
				// Static data can be passed with bgfx::makeRef
				bgfx::makeRef(s_cubeColorVertices, sizeof(s_cubeColorVertices))
				, *render_system->GetVertexDecl(RenderSystem::VertexType::Color)
			);

			// Create static index buffer.
			m_sIB = bgfx::createIndexBuffer(
				// Static data can be passed with bgfx::makeRef
				bgfx::makeRef(s_cubeTriList, sizeof(s_cubeTriList))
			);
		}
	}

	void BoxShape::Shutdown()
	{
		if (bgfx::isValid(m_sVBPos))
			bgfx::destroy(m_sVBPos);
		if (bgfx::isValid(m_sVBColor))
			bgfx::destroy(m_sVBColor);
		if (bgfx::isValid(m_sIB))
			bgfx::destroy(m_sIB);
	}
}
