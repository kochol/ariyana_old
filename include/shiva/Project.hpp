#pragma once
#include "bx/filepath.h"
#include <string>
#include <Meta.h>
#include <bx/error.h>
#include "DirectoryTree.hpp"

BX_ERROR_RESULT(SH_ERROR_NOT_EMPTY_DIRECTPRY, BX_MAKEFOURCC('s', 'h', 0, 0));

namespace shiva
{
	class Project
	{
		friend auto meta::registerMembers<Project>();
	public:
		Project();

		~Project();

		static Project* New(bx::FilePath projectPath, std::string name, bx::Error* err);

		void Save();
		static Project* Load(bx::FilePath path, bx::Error* err);

		void UpdateProjectTree();

	private:

		bx::FilePath	m_ProjectPath;
		std::string		m_ProjectName;
		DirectoryTree	m_Tree;

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