#pragma once
#include "bx/filepath.h"
#include <string>

namespace shiva
{
	class Project
	{
		Project();

	public:

		~Project();

		static Project* New(bx::FilePath projectPath);

		const std::string& GetProjectPath() const;

		void SetProjectPath(const std::string& path);

	private:

		bx::FilePath	m_ProjectPath;

	}; // Project

} // shiva

#include <Meta.h>

namespace meta {

	template <>
	inline auto registerMembers<shiva::Project>()
	{
		return members(
			member("path", &shiva::Project::GetProjectPath, &shiva::Project::SetProjectPath)
		);
	}

} // end of namespace meta