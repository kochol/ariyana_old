#pragma once
#include "aridef.hpp"
#include <memory>
#include "io/IoEnums.hpp"
#include "Program.hpp"

namespace bx
{
	class Thread;
}
namespace spdlog
{
	class logger;
}
namespace ftl
{
	class TaskScheduler;
}

namespace ari
{
	class SdlWindow;
	struct Event;

	struct InitParams
	{
		InitParams(): Height(600), Width(800), FullScreen(false)
		{}

		uint32_t Height,
				 Width;

		bool FullScreen;
		std::unique_ptr<IProgram> Program;

	}; // InitParams

	class ARI_API Engine
	{
		friend class SdlWindow;
		friend class GuiSystem;
	public:

		//! Constructor
		Engine();

		//! Destructor
		~Engine();

		static Engine& GetSingleton();

		//! Init the engine device
		bool Init(std::shared_ptr<InitParams> params);

		bool Run();

		Event* Poll();

		void Release(const Event * _event);

		uint32_t GetCurrentFrameNumber() const { return m_frame_number; }

		std::shared_ptr<spdlog::logger> GetLogger() const { return  Logger; }

	protected:

		static int InitBgfxInThread(bx::Thread* _thread, void* _userData);

		std::shared_ptr<spdlog::logger> Logger;
		SdlWindow	*					m_pWindow;
		std::shared_ptr<InitParams>		m_params;
		uint32_t						m_debug, m_reset, m_frame_number;
		int64_t							m_time_offset;
		bx::Thread					*	m_pGfxThread;
		ftl::TaskScheduler			*	m_pTaskMgr;
		MouseState						m_MouseState;
		bool							m_bRun;
		bool							m_bNeedReset;

	}; // Engine

	extern ARI_API Engine* g_pEngine;

}

