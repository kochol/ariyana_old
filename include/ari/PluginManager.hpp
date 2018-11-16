#pragma once
#include "ResourceManager.hpp"
#include "Plugin.hpp"
#include "aridef.hpp"

namespace ari
{
	class ARI_API PluginManager: public ResourceManager<Plugin>
	{
	protected:

		bool LoadResource(Plugin** ppOut, uint32_t handle, 
			const std::string& filename, void* extraParams) override;

	};

} // ari
