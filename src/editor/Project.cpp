#include "..\..\include\shiva\Project.hpp"
#include "ari/Engine.hpp"
#include <ari/JsonCast.h>
#include <iostream>
#include <fstream>

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

	void Project::Load()
	{
	}

} // shiva
