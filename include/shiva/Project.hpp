#pragma once
#include "bx/filepath.h"
#include <string>
#include <Meta.h>

namespace shiva
{
	class Project
	{
		friend auto meta::registerMembers<Project>();
	public:
		Project();

		~Project();

		static Project* New(bx::FilePath projectPath, std::string name);

		void Save();
		static Project* Load(bx::FilePath path);

	private:

		bx::FilePath	m_ProjectPath;
		std::string		m_ProjectName;

	}; // Project

} // shiva

namespace meta {

	template <>
	inline auto registerMembers<shiva::Project>()
	{
		return members(
			member("name", &shiva::Project::m_ProjectName)
		);
	}

} // end of namespace meta