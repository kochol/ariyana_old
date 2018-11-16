#pragma once
#include "../ResourceManager.hpp"
#include "Texture.hpp"

namespace ari
{
	class ARI_API TextureManager: public ResourceManager<Texture>
	{
	public:
		~TextureManager() override;

	protected:

		bool LoadResource(Texture** ppOut, uint32_t handle, 
			const std::string& filename, void* extraParams) override;

	};

} // ari
