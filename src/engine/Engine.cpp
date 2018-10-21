#include "..\..\include\ari\Engine.hpp"
#include "..\..\include\ari\Program.hpp"
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "io/SdlWindow.hpp"
#include <bgfx/bgfx.h>
#include <bx/thread.h>
#include <ftl/task_scheduler.h>
#include <bx/timer.h>

extern bx::AllocatorI* g_allocator;

namespace ari
{
	Engine* g_pEngine = nullptr;

	Engine::Engine() : m_pWindow(nullptr), m_debug(0), m_reset(0), 
		m_frame_number(0), m_time_offset(0), m_pGfxThread(nullptr)
	{
		Logger = spdlog::stdout_color_mt("main");
		Logger->set_level(spdlog::level::trace);
		g_pEngine = this;
		m_pTaskMgr = new ftl::TaskScheduler();
	}

	Engine::~Engine()
	{
		delete m_pWindow;
		g_pEngine = nullptr;
		delete m_pTaskMgr;
		m_pGfxThread->shutdown();
		delete m_pGfxThread;
	}

	Engine & Engine::GetSingleton()
	{
		return *g_pEngine;
	}

	bool Engine::Init(InitParams params)
	{
		// Create a SDL window
		m_pWindow = new SdlWindow();
		if (!m_pWindow->Init(params))
		{
			Logger->error("Can't create SDL window");
			return false;
		}

		m_params = params;
		m_debug = BGFX_DEBUG_TEXT;
		m_reset = BGFX_RESET_VSYNC;

		m_pGfxThread = new bx::Thread();
		m_pGfxThread->init(Engine::InitBgfxInThread, this);

		return true;
	}

	bool Engine::Run()
	{
		return m_pWindow->Run();
	}

	int Engine::InitBgfxInThread(bx::Thread * _thread, void * _userData)
	{
		// Init bgfx
		bgfx::Init init;
		init.resolution.width = g_pEngine->m_params.Width;
		init.resolution.height = g_pEngine->m_params.Height;
		init.resolution.reset = g_pEngine->m_reset;
		bgfx::init(init);

		// Enable debug text.
		bgfx::setDebug(g_pEngine->m_debug);

		// Set view 0 clear state.
		bgfx::setViewClear(0
			, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
			, 0x00000000
			, 1.0f
			, 0
		);

		if (g_pEngine->m_params.Program)
			g_pEngine->m_params.Program->Init();
		
		g_pEngine->m_time_offset = bx::getHPCounter();

		while (true)
		{
			// Set view 0 default viewport.
			bgfx::setViewRect(0, 0, 0, uint16_t(800), uint16_t(600));

			// This dummy draw call is here to make sure that view 0 is cleared
			// if no other draw calls are submitted to view 0.
			bgfx::touch(0);

			float time = (float)((bx::getHPCounter() - g_pEngine->m_time_offset) / double(bx::getHPFrequency()));

			if (g_pEngine->m_params.Program)
				g_pEngine->m_params.Program->Update(g_pEngine->m_frame_number, time);

			bgfx::frame();
			g_pEngine->m_frame_number++;
		}
		return 0;
	}

} // ari