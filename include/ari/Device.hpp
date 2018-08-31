#pragma once
#include "aridef.hpp"
#include <memory>

namespace spdlog
{
	class logger;
}

namespace ari
{
	struct InitParams
	{
		int Height,
			Width;

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

		std::shared_ptr<spdlog::logger> GetLogger() const { return  Logger; }

	private:

		std::shared_ptr<spdlog::logger> Logger;

	}; // Device
}
