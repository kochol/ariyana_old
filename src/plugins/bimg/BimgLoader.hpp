#pragma once
#include "../../../include/ari/ResourceLoader.hpp"

namespace ari
{
	class BimgLoader: public ResourceLoader
	{
	public:
		BimgLoader();

		~BimgLoader() override = default;

		Resource* LoadResource(bx::FileReaderI* pStream, uint32_t _handle, 
			const std::string& _filename, void* _extraParams) override;

	}; // BimgLoader

} // ari
