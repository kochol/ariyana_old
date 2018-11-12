#include "..\..\include\ari\ResourceLoader.hpp"

namespace ari
{
	bool ResourceLoader::IsALoadableFileExtension(std::string _extention)
	{
		for (const auto & ext : m_aFileExtension)
		{
			if (_extention.find_last_of(ext) > 0)
				return true;
		}

		return false;
	}
} // ari
