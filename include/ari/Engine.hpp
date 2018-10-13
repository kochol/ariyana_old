﻿#pragma once
#include "aridef.hpp"
#include <memory>

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
	class IProgram;

	struct InitParams
	{
		InitParams(): Height(600), Width(800), FullScreen(false), Program(nullptr)
		{}

		uint32_t Height,
				 Width;

		bool FullScreen;
		IProgram* Program;

	}; // InitParams

	class ARI_API Engine
	{
	public:

		//! Constructor
		Engine();

		//! Destructor
		~Engine();

		static Engine& GetSingleton();

		//! Init the engine device
		bool Init(InitParams params);

		bool Run();

		uint32_t GetCurrentFrameNumber() const { return m_frame_number; }

		std::shared_ptr<spdlog::logger> GetLogger() const { return  Logger; }

	protected:

		static int InitBgfxInThread(bx::Thread* _thread, void* _userData);

		std::shared_ptr<spdlog::logger> Logger;
		SdlWindow	*					m_pWindow;
		InitParams						m_params;
		uint32_t						m_debug, m_reset, m_frame_number;
		int64_t							m_time_offset;
		bx::Thread					*	m_pGfxThread;
		ftl::TaskScheduler			*	m_pTaskMgr;

	}; // Engine

	extern ARI_API Engine* g_pEngine;

}

