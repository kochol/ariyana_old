#include "..\..\include\ari\Engine.hpp"
#include "..\..\include\ari\Program.hpp"
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "io/SdlWindow.hpp"
#include <bgfx/bgfx.h>
#include <bx/thread.h>
#include <ftl/task_scheduler.h>
#include <bx/timer.h>
#include "../../include/ari/io/Input.hpp"
#include "../../deps/bgfx/src/renderer.h"
#include "io/WindowWin32.hpp"

extern bx::AllocatorI* g_allocator;

namespace ari
{
	Engine* g_pEngine = nullptr;

	Engine::Engine() : m_pWindow(nullptr), m_debug(0), m_reset(0), 
		m_frame_number(0), m_time_offset(0), m_pGfxThread(nullptr),
		m_bRun(true), m_bNeedReset(false)
	{
		Logger = spdlog::stdout_color_mt("main");
		Logger->set_level(spdlog::level::trace);
		g_pEngine = this;
		m_pTaskMgr = new ftl::TaskScheduler();
	}

	Engine::~Engine()
	{
		m_bRun = false;
		m_params->Program.release();

		// 
		bgfx::renderFrame();
		m_pGfxThread->shutdown();
		delete m_pGfxThread;

		delete m_pWindow;
		g_pEngine = nullptr;
		delete m_pTaskMgr;
	}

	Engine & Engine::GetSingleton()
	{
		return *g_pEngine;
	}

	bool Engine::Init(std::shared_ptr<InitParams> params)
	{
		// Create a window
#if BX_PLATFORM_WINDOWS
		m_pWindow = new WindowWin32(PlatformWindow::Type::Main);
#else
		Logger->error("Windowing in this platform not supported yet.");
		return false;
#endif

		char* windowName = "Ariyana";
		if (params->Program)
			windowName = (char*)params->Program->GetProgramName().c_str();
		if (!m_pWindow->Init(0, 0, params->Width, params->Height, 0, windowName))
		{
			Logger->error("Can't create window");
			return false;
		}

		m_params = params;
		m_debug = BGFX_DEBUG_TEXT;
		m_reset = BGFX_RESET_VSYNC;

		inputInit();

		m_pGfxThread = new bx::Thread();
		m_pGfxThread->init(Engine::InitBgfxInThread, this);

		return true;
	}

	bool Engine::Run()
	{
	    m_bRun = m_pWindow->Run();
		uint32_t reset = m_reset;
		m_bRun &= m_pWindow->ProcessEvents(m_params->Width, m_params->Height, m_debug, reset, &m_MouseState);
		return m_bRun;
	}

	Event * Engine::Poll()
	{
		return const_cast<Event*>(m_pWindow->m_eventQueue.poll());
	}

	void Engine::Release(const Event * _event)
	{
		m_pWindow->m_eventQueue.release(_event);
	}

	int Engine::InitBgfxInThread(bx::Thread * _thread, void * _userData)
	{
		BX_UNUSED(_thread, _userData);

		// Init bgfx
		bgfx::Init init;
		init.resolution.width = g_pEngine->m_params->Width;
		init.resolution.height = g_pEngine->m_params->Height;
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

		if (g_pEngine->m_params->Program)
			g_pEngine->m_params->Program->Init();
		
		g_pEngine->m_time_offset = bx::getHPCounter();

		while (g_pEngine->m_bRun)
		{
			if (g_pEngine->m_bNeedReset)
			{
				bgfx::reset(g_pEngine->m_params->Width, g_pEngine->m_params->Height, g_pEngine->m_reset);
				g_pEngine->m_bNeedReset = false;
			}
			// Set view 0 default viewport.
			bgfx::setViewRect(0, 0, 0, uint16_t(g_pEngine->m_params->Width), uint16_t(g_pEngine->m_params->Height));

			// This dummy draw call is here to make sure that view 0 is cleared
			// if no other draw calls are submitted to view 0.
			bgfx::touch(0);

			float time = (float)((bx::getHPCounter() - g_pEngine->m_time_offset) / double(bx::getHPFrequency()));

			if (g_pEngine->m_params->Program)
				g_pEngine->m_params->Program->Update(g_pEngine->m_frame_number, time);

			bgfx::frame();
			g_pEngine->m_frame_number++;
		}
		if (g_pEngine->m_params->Program)
			return g_pEngine->m_params->Program->Shutdown();

		return 0;
	}

} // ari
