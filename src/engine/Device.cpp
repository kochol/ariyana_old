#include "..\..\include\ari\Device.hpp"
#include <SDL2/SDL.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace ari
{
	Device::Device()
	{
		Logger = spdlog::stdout_color_mt("main");
	}

	Device::~Device()
	{
	}

	bool Device::Init(InitParams params)
	{
		// Init the SDL
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
		{
			Logger->error("Can't Initialize SDL2.");
			return false;
		}

		// Create a SDL window

		return false;
	}

} // ari