project ("ariengine")
	kind "SharedLib"

	includedirs {
		path.join(BGFX_DIR, "include"),
		path.join(BGFX_DIR, "3rdparty"),
		path.join(BX_DIR,   "include"),
		path.join(BIMG_DIR, "include"),
		path.join(ARIDEPS_DIR, "FiberTaskingLib/include"),
		path.join(ARIDEPS_DIR, "FiberTaskingLib/third_party/boost_context/include"),		
		path.join(ARIDEPS_DIR, "SDL2/include"),
		path.join(MODULE_DIR, "deps/spdlog/include"),
		path.join(MODULE_DIR, "deps/brtshaderc/tools/brtshaderc"),	
		path.join(MODULE_DIR, "deps/MetaStuff/include"),	
		path.join(MODULE_DIR, "deps/MetaStuff/example/nlohmann_json"),					
	}

	links {
		"bx",
		"bimg",
		"bgfx",
		"SDL2",
		"brtshaderc"
	}

	files {
		"../include/ari/**.hpp",
		"../include/ari/**.inl",
		"../src/engine/**.cpp",
		"../src/engine/**.hpp",
		"../deps/spdlog/include/**.h",
		"../assets/shaders/**.glsl",
		"../deps/bgfx/3rdparty/dear-imgui/**.h",
		"../deps/bgfx/3rdparty/dear-imgui/**.inl",
		"../deps/bgfx/3rdparty/dear-imgui/**.cpp",
		"../deps/bgfx/examples/common/imgui/*.h",
		"../deps/bgfx/examples/common/imgui/*.cpp",				
	}

	defines {
		"ARI_EXPORT",
		"ASSETS_DIR=\"" .. ASSETS_DIR .. "\"",
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