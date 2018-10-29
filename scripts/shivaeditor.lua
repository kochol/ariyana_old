project ("shivaeditor")
	kind "SharedLib"

	includedirs {
		path.join(BX_DIR,   "include"),
		path.join(BGFX_DIR, "3rdparty"),
		path.join(MODULE_DIR, "deps/MetaStuff/include"),	
		path.join(MODULE_DIR, "deps/MetaStuff/example/nlohmann_json"),					
		"../include",
	}

	links {
		"bx",
		"ariengine",
	}

	files {
		"../include/shiva/**.hpp",
		"../src/editor/**.cpp",
		"../src/editor/**.hpp",
	}

	defines {
		"SHIVA_EXPORT",
		"ASSETS_DIR=\"" .. ASSETS_DIR .. "\"",
	}

	configuration { "vs*" }
		buildoptions { "/EHsc" }

project ("Shiva")
	kind "ConsoleApp"

	includedirs {
		path.join(BX_DIR,   "include"),
		path.join(BGFX_DIR, "3rdparty"),
		"../include"
	}

	links {
		"bx",
		"ariengine",
		"shivaeditor",
	}

	files {
		"../src/shiva/**.cpp",
		"../src/shiva/**.hpp",
	}

	configuration { "vs*" }
		buildoptions { "/EHsc" }
	