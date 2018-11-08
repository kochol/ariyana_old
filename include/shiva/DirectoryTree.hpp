#pragma once
#include "shivadef.hpp"
#include <string>
#include "bx/file.h"
#include <vector>

namespace shiva
{
	struct FileInfo
	{
		std::string Name;
	};

	class SHIVA_API DirectoryTree
	{
	public:

		std::string Name;
		bx::FilePath Path;
		std::vector<FileInfo> FileList;
		std::vector<DirectoryTree> Directories;

		void Update();

	};

} // shiva
