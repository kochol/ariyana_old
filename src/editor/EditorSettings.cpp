#include "..\..\include\shiva\EditorSettings.hpp"
#include <ari/JsonCast.h>
#include <iostream>
#include <fstream>
#include "bx/file.h"

namespace shiva
{
	EditorSettings & EditorSettings::Get()
	{
		static EditorSettings settings;
		return settings;
	}

	void EditorSettings::Save()
	{
		json root;
		to_json(root, Get());
		std::ofstream out("editor_settings.json");
		
		out << std::setw(4) << root << std::endl;

	} // Save

	void EditorSettings::Load()
	{
		bx::FileReader file;
		bx::Error err;
		if (!file.open("editor_settings.json", &err))
		{

			return;
		}
		const int32_t size = static_cast<int32_t>(file.seek(0, bx::Whence::End));
		file.seek(0, bx::Whence::Begin);
		char* data = new char[size + 1];
		file.read(data, size, &err);
		data[size] = 0;

		json root = json::parse(data);
		delete[] data;
		from_json(root, Get());

	} // Load


} // shiva
