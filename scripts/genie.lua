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
	-- startproject "example-00-helloworld"

MODULE_DIR = path.getabsolute("../")
BGFX_DIR   = path.getabsolute("../deps/bgfx")
BX_DIR     = os.getenv("BX_DIR")
BIMG_DIR   = os.getenv("BIMG_DIR")

local BGFX_BUILD_DIR = path.join(MODULE_DIR, ".build")
local BGFX_THIRD_PARTY_DIR = path.join(BGFX_DIR, "3rdparty")
if not BX_DIR then
	BX_DIR = path.getabsolute(path.join(BGFX_DIR, "../bx"))
end

if not BIMG_DIR then
	BIMG_DIR = path.getabsolute(path.join(BGFX_DIR, "../bimg"))
end

if not os.isdir(BX_DIR) or not os.isdir(BIMG_DIR) then

	if not os.isdir(BX_DIR) then
		print("bx not found at " .. BX_DIR)
	end

	if not os.isdir(BIMG_DIR) then
		print("bimg not found at " .. BIMG_DIR)
	end

	print("For more info see: https://bkaradzic.github.io/bgfx/build.html")
	os.exit()
end

dofile (path.join(BX_DIR, "scripts/toolchain.lua"))
if not toolchain(BGFX_BUILD_DIR, BGFX_THIRD_PARTY_DIR) then
	return -- no action specified
end

function copyLib()
end

dofile("ariengine.lua")

dofile(path.join(BGFX_DIR, "scripts/bgfx.lua"))

group "deps"
bgfxProject("", "StaticLib", {})

dofile(path.join(BX_DIR,   "scripts/bx.lua"))
dofile(path.join(BIMG_DIR, "scripts/bimg.lua"))
dofile(path.join(BIMG_DIR, "scripts/bimg_decode.lua"))
