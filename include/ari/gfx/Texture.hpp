#pragma once
#include "../aridef.hpp"
#include "../Resource.hpp"

namespace ari
{
	class ARI_API Texture: public Resource
	{
	public:

		Texture(const uint32_t& _handel, const std::string& _fileName);

		~Texture() override;

	};

} // ari
