#pragma once
#include "Node3D.hpp"

namespace bgfx
{
	struct VertexBufferHandle;
	struct IndexBufferHandle;
}

namespace ari
{
	class RenderSystem;

	class ARI_API BoxShape: public Node3D
	{
	public:

		// Constructor
		BoxShape() = default;

		//! Destructor
		virtual ~BoxShape() = default;

		static void Init(RenderSystem* render_system);
		static void Shutdown();

		static bgfx::VertexBufferHandle m_sVBPos;
		static bgfx::VertexBufferHandle m_sVBColor;
		static bgfx::IndexBufferHandle	m_sIB;

	}; // BoxShape
}
