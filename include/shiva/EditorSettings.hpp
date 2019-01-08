#pragma once
#include <Meta.h>

namespace shiva
{
	class EditorSettings
	{
	public:

		std::string			LastProjectPath;

		static EditorSettings& Get();
		static void Save();
		static void Load();
	};

} // shiva

namespace meta {

	template <>
	inline auto registerMembers<shiva::EditorSettings>()
	{
		return members(
			member("last_project_path", &shiva::EditorSettings::LastProjectPath)
		);
	}

} // end of namespace meta