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

if string.find(_ACTION, "vs") then
	if os.isdir(path.join(MODULE_DIR, ".build/win32_" .. _ACTION .. "/bin")) == false then
		os.mkdir(path.join(MODULE_DIR, ".build/win32_" .. _ACTION .. "/bin"))
	end
	if os.isdir(path.join(MODULE_DIR, ".build/win64_" .. _ACTION .. "/bin")) == false then
		os.mkdir(path.join(MODULE_DIR, ".build/win64_" .. _ACTION .. "/bin"))
	end
	print(os.copyfile(path.join(ARIDEPS_DIR, "libs/win32/SDL2.dll"), path.join(MODULE_DIR, ".build/win32_" .. _ACTION .. "/bin/SDL2.dll")))
	print(os.copyfile(path.join(ARIDEPS_DIR, "libs/win64/SDL2.dll"), path.join(MODULE_DIR, ".build/win64_" .. _ACTION .. "/bin/SDL2.dll")))	
end