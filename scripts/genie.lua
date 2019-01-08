newoption {
	trigger = "with-tests",
	description = "Enable building tests.",
}

solution "Ariyana"
	configurations {
		"Debug",
		"Release",
	}

	if _ACTION == "xcode4" then
		platforms {
			"Universal",
		}
	else
		platforms {
			"x32",
			"x64",
			"Native", -- for targets where bitness is not specified
		}
	end

	language "C++"
	startproject "Shiva"

MODULE_DIR  = path.getabsolute("../")
ASSETS_DIR  = "../../../assets"
ARIDEPS_DIR = path.getabsolute("../deps/arideps") 
BGFX_DIR    = path.getabsolute("../deps/bgfx")
BX_DIR      = path.getabsolute("../deps/bx")
BIMG_DIR    = path.getabsolute("../deps/bimg")

local BGFX_BUILD_DIR = path.join(MODULE_DIR, ".build")
local BGFX_THIRD_PARTY_DIR = path.join(BGFX_DIR, "3rdparty")

dofile (path.join(BX_DIR, "scripts/toolchain.lua"))
if not toolchain(BGFX_BUILD_DIR, BGFX_THIRD_PARTY_DIR) then
	return -- no action specified
end

function copyLib()
end

dofile("ariengine.lua")
dofile("shivaeditor.lua")

dofile(path.join(BGFX_DIR, "scripts/bgfx.lua"))

group "deps"
bgfxProject("", "SharedLib", {})

dofile(path.join(BX_DIR,   "scripts/bx.lua"))
dofile(path.join(BIMG_DIR, "scripts/bimg.lua"))
dofile(path.join(BIMG_DIR, "scripts/bimg_decode.lua"))
dofile(path.join(MODULE_DIR, "deps/brtshaderc/scripts/brtshaderc.lua"))

function testProject(...)
	for _, name in ipairs({...}) do
		project ("test-" .. name)
			uuid (os.uuid("test-" .. name))
			kind "ConsoleApp"

		files {
			path.join(MODULE_DIR, "tests", name, "**.cpp"),
			path.join(MODULE_DIR, "tests", name, "**.hpp"),
		}

		includedirs {
			path.join(MODULE_DIR,   "include"),
			path.join(BX_DIR,   "include"),	
			path.join(BIMG_DIR,   "include"),	
			path.join(BGFX_DIR, "3rdparty"),		
			path.join(BGFX_DIR, "include"),		
		}
	
		links {
			"ariengine",
		}	

	end
end

if _OPTIONS["with-tests"] then
	group "tests"

	testProject("00-init",
				"01-cubes",
				"02-gui")
end

group "plugins"
dofile("plugins.lua")
