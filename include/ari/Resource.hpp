#pragma once
#include <string>
#include "aridef.hpp"

namespace ari
{	
	class ARI_API Resource
	{
		template <class T>
		friend class ResourceManager;

	public:

		Resource(const uint32_t& _handel, const std::string& _fileName): 
			m_iHandle(_handel), m_sFileName(_fileName) { }

		virtual ~Resource() = default;

		uint32_t GetHandel() const { return m_iHandle; }

		std::string GetFileName() const { return m_sFileName; }

	protected:

		uint32_t	m_iHandle;
		std::string m_sFileName;
	};

} // ari
