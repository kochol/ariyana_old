#include "..\..\..\include\ari\gfx\Texture.hpp"

namespace ari
{
	Texture::Texture(const uint32_t & _handel, const std::string & _fileName)
		: Resource(_handel, _fileName)
	{
	}

	Texture::~Texture()
	{
	}


} // ari
