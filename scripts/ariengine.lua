project ("ariengine")
	kind "SharedLib"

	includedirs {
		path.join(BGFX_DIR, "include"),
		path.join(BX_DIR,   "include"),
		path.join(BIMG_DIR, "include"),
		path.join(ARIDEPS_DIR, "FiberTaskingLib/include"),
		path.join(ARIDEPS_DIR, "SDL2/include"),
		path.join(MODULE_DIR, "deps/spdlog/include")
	}

	links {
		"bx",
		"bgfx",
		"ftl",
		"SDL2"
	}

	files {
		"../include/ari/**.hpp",
		"../src/engine/**.cpp",
		"../deps/spdlog/include/**.h"
	}

	defines {
		"ARI_EXPORT",
	}

	configuration { "vs*", "x32" }
		libdirs { path.join(ARIDEPS_DIR, "libs/win32") }

	configuration { "vs*", "x64" }
	libdirs { path.join(ARIDEPS_DIR, "libs/win64") }
