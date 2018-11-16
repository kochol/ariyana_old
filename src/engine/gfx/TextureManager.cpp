#include "..\..\..\include\ari\gfx\TextureManager.hpp"
#include "../../../include/ari/ResourceLoader.hpp"

namespace ari
{
	TextureManager::~TextureManager()
	{
	}

	bool TextureManager::LoadResource(Texture ** ppOut, uint32_t handle, const std::string& filename, 
		void * extraParams)
	{
		bx::FilePath path = filename.c_str();
		std::string ext = path.getExt().getPtr();
		for (auto loader: m_vLoaders)
		{
			if (loader->IsALoadableFileExtension(ext))
			{
				bx::FileReader r;
				bx::Error err;
				if (r.open(path, &err))
				{
					*ppOut = reinterpret_cast<Texture*>(loader->LoadResource
						(&r, handle, filename, extraParams));
					if (*ppOut)
						return true;
				}
			}
		}
		return false;
	}

} // ari
