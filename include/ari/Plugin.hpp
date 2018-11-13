#pragma once
#include "Resource.hpp"

namespace ari
{
	class Plugin: public Resource
	{
	public:

		enum class Type
		{
			TextureLoader,
			MeshLoader,

			Unknown
		};

		Plugin(const uint32_t& _handel, const std::string& _fileName)
			: Resource(_handel, _fileName)
		{
		}

		virtual ~Plugin() = default;

		virtual void* Create() = 0;

	protected:

		Type	m_eType = Type::Unknown;

	}; // Plugin

} // ari
