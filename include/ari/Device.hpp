#pragma once
#include "aridef.hpp"
#include <memory>

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

		//! Init the engine device
		bool Init(InitParams params);

		bool Run();

		std::shared_ptr<spdlog::logger> GetLogger() const { return  Logger; }

	private:

		std::shared_ptr<spdlog::logger> Logger;
		SdlWindow	*					m_pWindow;

	}; // Device
}
