#pragma once
#include "aridef.hpp"
#include <vector>
#include "bx/readerwriter.h"
#include "bx/file.h"

namespace ari
{	
	class Resource;

	class ARI_API ResourceLoader
	{
	public:

		//! Constructor
		ResourceLoader() : m_bSwapEndian(false)
		{}

		//! Destructor
		virtual ~ResourceLoader() = default;

		//! returns true if the file maybe is able to be loaded by this Loader
		//! based on the file extension (e.g. ".mesh")
		virtual bool IsALoadableFileExtension(std::string _extention);

		//! Loads a resource from a FileSystem and return its pointer.
		/*!
			\param strFilename The resource file name to load.
			\return Returns the created resource pointer. Note resource may not loaded yet.
			\sa kge::io::FileSystemManager, Resource::IsLoaded
		 */
		virtual Resource* LoadResource(bx::FileReaderI* pStream) = 0;

	protected:

		std::vector<std::string>	        m_aFileExtension;		//!< The file extension list that this loader is capable to load
		bool								m_bSwapEndian;			//!< Swap the loaded data or not

	};
	
} // ari
