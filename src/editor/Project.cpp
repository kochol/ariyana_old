#include "..\..\include\shiva\Project.hpp"

namespace shiva
{
	Project::Project()
	{
	}

	Project::~Project()
	{
	}

	Project * Project::New(bx::FilePath projectPath)
	{


		return nullptr;
	}

	const std::string& Project::GetProjectPath() const
	{
		return m_ProjectPath.get();
	}

	void Project::SetProjectPath(const std::string & path)
	{
		m_ProjectPath.set(path.c_str());
	}

} // shiva
