project ("ariengine")
	kind "SharedLib"

	includedirs {
		path.join(BGFX_DIR, "include"),
		path.join(BX_DIR,   "include"),
		path.join(BIMG_DIR, "include"),
		path.join(ARIDEPS_DIR, "FiberTaskingLib/include"),
		path.join(ARIDEPS_DIR, "FiberTaskingLib/third_party/boost_context/include"),		
		path.join(ARIDEPS_DIR, "SDL2/include"),
		path.join(MODULE_DIR, "deps/spdlog/include")
	}

	links {
		"bx",
		"bimg",
		"bgfx",
		"SDL2"
	}

	files {
		"../include/ari/**.hpp",
		"../src/engine/**.cpp",
		"../src/engine/**.hpp",
		"../deps/spdlog/include/**.h"
	}

	defines {
		"ARI_EXPORT",
	}


	configuration {"Debug"}
		links { "ftlDebug", "boost_contextDebug" }

	configuration { "Release" }
		links { "ftl", "boost_context" }

	configuration { "vs*", "x32" }
		libdirs { path.join(ARIDEPS_DIR, "libs/win32") }

	configuration { "vs*", "x64" }
		libdirs { path.join(ARIDEPS_DIR, "libs/win64") }

	configuration { "vs*" }
		buildoptions { "/EHsc" }

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