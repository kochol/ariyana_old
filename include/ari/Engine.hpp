#pragma once
#include "aridef.hpp"
#include <memory>
#include "io/IoEnums.hpp"
#include "io/PlatformWindow.hpp"
#include "Program.hpp"
#include "PluginManager.hpp"
#include "gfx/TextureManager.hpp"

namespace bx
{
	class Thread;
	class Mutex;
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
	struct Event;

	struct InitParams
	{
		InitParams(): Height(600), Width(800), FullScreen(false)
		{}

		uint32_t Height,
				 Width;

		bool FullScreen;
		IProgram* Program;

	}; // InitParams

	class ARI_API Engine
	{
		friend class PlatformWindow;
		friend class GuiSystem;
	public:

		//! Constructor
		Engine();

		//! Destructor
		~Engine();

		static Engine& GetSingleton();

		//! Init the engine device
		bool Init(InitParams* params);

		bool Run();

		void LockUpdateThread();

		void UnlockUpdateThread();

		Event* Poll();

		void Release(const Event * _event);

		uint32_t GetCurrentFrameNumber() const { return m_frame_number; }

		std::shared_ptr<spdlog::logger> GetLogger() const { return  Logger; }

		InitParams* GetParams() const { return m_params; }

		void SetParams(InitParams* _params) { m_params = _params; }

		PlatformWindow* GetMainWindow() const { return m_pWindow; }

		PlatformWindow*	NewWindow(PlatformWindow::Type _type);

		uint16_t GetNewViewId();

		uint32_t GetMsaaFlags() const;

		float GetElapsedTime() const { return m_fElapsedTime; }

		float GetDeltaTime() const { return m_fDeltaTime; }

		PluginManager plugin_manager;
		TextureManager texture_manager;

	protected:

		static int InitBgfxInThread(bx::Thread* _thread, void* _userData);

		InitParams					*	m_params;
		std::shared_ptr<spdlog::logger> Logger;
		PlatformWindow				*	m_pWindow;
		uint32_t						m_debug, m_reset, m_frame_number;
		uint16_t						m_viewId = 0;
		int64_t							m_time_offset;
		bx::Thread					*	m_pGfxThread;
		bx::Mutex					*	m_pMutex = nullptr;
		int								m_iLockStatus = 0; //! 0 = No action, 1 = Lock, 2 = Unlock the update thread.
		ftl::TaskScheduler			*	m_pTaskMgr;
		MouseState						m_MouseState;
		bool							m_bRun;
		bool							m_bNeedReset;
		float							m_fElapsedTime = 0.0f,
										m_fDeltaTime = 0.0f;

	}; // Engine

	extern ARI_API Engine* g_pEngine;

}

