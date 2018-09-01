#include "..\..\include\ari\Device.hpp"
#include <SDL2/SDL.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "io/SdlWindow.hpp"

namespace ari
{
	Device::Device(): m_pWindow(nullptr)
	{
		Logger = spdlog::stdout_color_mt("main");
	}

	Device::~Device()
	{
		delete m_pWindow;
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
		m_pWindow = new SdlWindow();
		m_pWindow->Init(params);

		return false;
	}

	bool Device::Run()
	{
		return m_pWindow->Run();
	}

} // ari