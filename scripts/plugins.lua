project ("plugin_bimg")
	kind "SharedLib"

	includedirs {
		path.join(BX_DIR,   "include"),
		path.join(BIMG_DIR, "include"),
		path.join(BGFX_DIR,   "include"),
	}

	links {
		"bx",
		"bimg",
		"bgfx",
		"ariengine",
	}

	files {
		"../src/plugins/bimg/**.cpp",
		"../src/plugins/bimg/**.hpp",
	}

	defines {
		"ARI_PLUGIN_EXPORT",
		"ASSETS_DIR=\"" .. ASSETS_DIR .. "\"",
	}

	configuration { "vs*" }
		buildoptions { "/EHsc" }
