project ("ariengine")
	kind "SharedLib"

	includedirs {
		path.join(BGFX_DIR, "include"),
		path.join(BX_DIR,   "include"),
		path.join(BIMG_DIR, "include"),
	}

	links {
		"bx",
		"bgfx"
	}

	files {
		"../include/ari/**.hpp",
		"../src/engine/**.cpp",
	}

	defines {
		"ARI_EXPORT",
	}
