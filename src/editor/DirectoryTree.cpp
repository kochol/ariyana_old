#include "..\..\include\shiva\DirectoryTree.hpp"
#include "dirent.h"

namespace shiva
{
	void DirectoryTree::Update()
	{
		if (Name.length() == 0)
		{
			const char* slash = bx::strRFind(Path.get(), '/');
			slash++;
			Name = slash;
		}

		// clear the childs.
		Directories.clear();
		FileList.clear();

		// get file list.
		DIR* dir = opendir(Path.get());
		dirent* next;
		do
		{
			next = readdir(dir);
			if (next)
			{
				if (next->d_name[0] == '.')
					continue;

				if (next->d_type == DT_DIR)
				{
					DirectoryTree child;
					child.Path = Path;
					child.Path.join(next->d_name);
					Directories.push_back(child);
					Directories[Directories.size() - 1].Update();
				}
				else if (next->d_type == DT_REG)
				{
					FileList.push_back({ next->d_name });
				}
				else
				{
					printf("Unknown file type.\n");
				}
			}
		}
		while (next);
	}

} // shiva
