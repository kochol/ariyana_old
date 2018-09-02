#pragma once
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

namespace ari
{
	class SdlWindow;

	struct InitParams
	{
		InitParams(): Height(600), Width(800), FullScreen(false)
		{}

		uint32_t Height,
				 Width;

		bool FullScreen;

	}; // InitParams

	class ARI_API Device
	{
	public:

		//! Constructor
		Device();

		//! Destructor
		~Device();

		static Device& GetSingleton();

		//! Init the engine device
		bool Init(InitParams params);

		bool Run();

		std::shared_ptr<spdlog::logger> GetLogger() const { return  Logger; }

	protected:

		static int InitBgfxInThread(bx::Thread* _thread, void* _userData);

		std::shared_ptr<spdlog::logger> Logger;
		SdlWindow	*					m_pWindow;
		InitParams						m_params;
		uint32_t		m_debug, m_reset;
		bx::Thread	*	m_pGfxThread;

	}; // Device
}

