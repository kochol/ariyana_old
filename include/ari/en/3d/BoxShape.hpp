#pragma once
#include "Node3D.hpp"

namespace bgfx
{
	struct VertexBufferHandle;
	struct IndexBufferHandle;
	struct ProgramHandle;
}

namespace ari
{
	class RenderSystem;

	class ARI_API BoxShape: public Node3D
	{
	public:

		// Constructor
		BoxShape() { _isRenderable = true; }

		//! Destructor
		virtual ~BoxShape() = default;

		//! Render
		virtual void Render(const Matrix& matrix, bgfx::Encoder* encoder, uint16_t _view_id) override;

		static void Init(RenderSystem* render_system);
		static void Shutdown();

		static bgfx::VertexBufferHandle m_sVBPos;
		static bgfx::VertexBufferHandle m_sVBColor;
		static bgfx::IndexBufferHandle	m_sIB;
		static bgfx::ProgramHandle		m_sProgram;

	}; // BoxShape
}
