#pragma once
#include "../Component.hpp"
#include "../../math/Rect.hpp"
#include <bgfx/bgfx.h>
#include "../../gfx/Texture.hpp"

namespace ari
{
	class ARI_API Viewport: public Component
	{
	public:

		RectI						Rect;
		bgfx::TextureFormat::Enum	TextureFormat = bgfx::TextureFormat::Count;
		bool						CreateDepth = false;
		bool						UseMSAA = false;

		// internal

		bgfx::FrameBufferHandle		m_frame_buffer_handle = BGFX_INVALID_HANDLE;
		RectI						m_last_rect;
		bgfx::ViewId				m_view_id = 0;
		Texture						m_texture,
									m_depth_texture;
	};

} // ari
