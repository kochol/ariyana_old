#include "BimgLoader.hpp"
#include "bgfx/bgfx.h"
#include "bimg/bimg.h"
#include "bimg/decode.h"
#include "../../../include/ari/gfx/Texture.hpp"

namespace ari
{
	void* load(bx::FileReaderI* _reader, bx::AllocatorI* _allocator, uint32_t* _size)
	{
		uint32_t size = (uint32_t)bx::getSize(_reader);
		void* data = BX_ALLOC(_allocator, size);
		bx::read(_reader, data, size);
		bx::close(_reader);
		if (nullptr != _size)
		{
			*_size = size;
		}
		return data;
	}

	void unload(void* _ptr)
	{
		BX_FREE(getDefaultAllocator(), _ptr);
	}

	static void imageReleaseCb(void* _ptr, void* _userData)
	{
		BX_UNUSED(_ptr);
		bimg::ImageContainer* imageContainer = (bimg::ImageContainer*)_userData;
		bimg::imageFree(imageContainer);
	}

	BimgLoader::BimgLoader()
	{
		m_aFileExtension.push_back("png");
		m_aFileExtension.push_back("jpg");
		m_aFileExtension.push_back("bmp");
		m_aFileExtension.push_back("jpeg");
		m_aFileExtension.push_back("tga");
		m_aFileExtension.push_back("dds");

	}

	Resource * BimgLoader::LoadResource(bx::FileReaderI * pStream, uint32_t _handle, 
		const std::string& _filename, void* _extraParams)
	{
		bgfx::TextureHandle bgfx_handle = BGFX_INVALID_HANDLE;

		TextureParams temp_params;
		TextureParams* params;
		if (_extraParams)
			params = reinterpret_cast<TextureParams*>(_extraParams);
		else
			params = &temp_params;

		uint32_t size;
		void* data = load(pStream, getDefaultAllocator(), &size);
		if (nullptr != data)
		{
			bimg::ImageContainer* imageContainer = bimg::imageParse(getDefaultAllocator(), data, size);

			if (nullptr != imageContainer)
			{
				if (nullptr != params->Orientation)
				{
					*params->Orientation = imageContainer->m_orientation;
				}

				const bgfx::Memory* mem = bgfx::makeRef(
					imageContainer->m_data
					, imageContainer->m_size
					, imageReleaseCb
					, imageContainer
				);
				unload(data);

				if (imageContainer->m_cubeMap)
				{
					bgfx_handle = bgfx::createTextureCube(
						uint16_t(imageContainer->m_width)
						, 1 < imageContainer->m_numMips
						, imageContainer->m_numLayers
						, bgfx::TextureFormat::Enum(imageContainer->m_format)
						, params->Flags
						, mem
					);
				}
				else if (1 < imageContainer->m_depth)
				{
					bgfx_handle = bgfx::createTexture3D(
						uint16_t(imageContainer->m_width)
						, uint16_t(imageContainer->m_height)
						, uint16_t(imageContainer->m_depth)
						, 1 < imageContainer->m_numMips
						, bgfx::TextureFormat::Enum(imageContainer->m_format)
						, params->Flags
						, mem
					);
				}
				else if (bgfx::isTextureValid(0, false, imageContainer->m_numLayers, bgfx::TextureFormat::Enum(imageContainer->m_format), params->Flags))
				{
					bgfx_handle = bgfx::createTexture2D(
						uint16_t(imageContainer->m_width)
						, uint16_t(imageContainer->m_height)
						, 1 < imageContainer->m_numMips
						, imageContainer->m_numLayers
						, bgfx::TextureFormat::Enum(imageContainer->m_format)
						, params->Flags
						, mem
					);
				}

				if (NULL != params->Info)
				{
					bgfx::calcTextureSize(
						*params->Info
						, uint16_t(imageContainer->m_width)
						, uint16_t(imageContainer->m_height)
						, uint16_t(imageContainer->m_depth)
						, imageContainer->m_cubeMap
						, 1 < imageContainer->m_numMips
						, imageContainer->m_numLayers
						, bgfx::TextureFormat::Enum(imageContainer->m_format)
					);
				}				

				if (bgfx::isValid(bgfx_handle))
				{
					bgfx::setName(bgfx_handle, _filename.c_str());
					Texture* t = new Texture(_handle, _filename);
					t->Handle = bgfx_handle;
					return t;
				}
			}
		}

		return nullptr;
	}

} // ari
