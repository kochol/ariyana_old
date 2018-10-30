#include "..\..\include\shiva\Project.hpp"
#include "ari/Engine.hpp"
#include <ari/JsonCast.h>
#include <iostream>
#include <fstream>
#include "bx/file.h"

namespace shiva
{
	Project::Project()
	{
	}

	Project::~Project()
	{
	}

	Project * Project::New(bx::FilePath projectPath, std::string name)
	{
		projectPath.join(name.c_str());

		// 1st Create the folders
		if (!bx::makeAll(projectPath))
		{
			//ari::g_pEngine->GetLogger()->
			return nullptr;
		}

		Project* p = new Project();
		p->m_ProjectName = name;
		projectPath.join(name.append(".shiva").c_str());
		p->m_ProjectPath = projectPath;
		p->Save();

		return p;
	}

	void Project::Save()
	{
		json root;
		to_json(root, *this);
		std::ofstream out(m_ProjectPath.get());
		
		out << std::setw(4) << root << std::endl;
	}

	Project * Project::Load(bx::FilePath path)
	{
		bx::FileReader file;
		bx::Error err;
		if (!file.open(path, &err))
		{
			return nullptr;
		}
		const int32_t size = static_cast<int32_t>(file.seek(0, bx::Whence::End));
		file.seek(0, bx::Whence::Begin);
		char* data = new char[size + 1];
		file.read(data, size, &err);
		data[size] = 0;
		json root = json::parse(data);
		Project* p = new Project();
		from_json(root, *p);
		p->m_ProjectPath = path;
		return p;
	}

} // shiva
