#pragma once
#include "../../../include/ari/ResourceLoader.hpp"

namespace ari
{
	class BimgLoader: public ResourceLoader
	{
	public:
		BimgLoader() = default;

		~BimgLoader() override = default;

		Resource* LoadResource(bx::FileReaderI* pStream) override;

	}; // BimgLoader

} // ari
