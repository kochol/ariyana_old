#pragma once
#include "../aridef.hpp"
#include "../Resource.hpp"
#include "bgfx/bgfx.h"
#include "bimg/bimg.h"

namespace ari
{
	struct TextureParams
	{
		uint32_t Flags = BGFX_TEXTURE_NONE;
		bgfx::TextureInfo* Info = nullptr;
		bimg::Orientation::Enum* Orientation = nullptr;
	};

	class ARI_API Texture: public Resource
	{
	public:

		Texture(const uint32_t& _handel, const std::string& _fileName);

		~Texture() override;

		bgfx::TextureHandle Handle = BGFX_INVALID_HANDLE;

	};

} // ari
