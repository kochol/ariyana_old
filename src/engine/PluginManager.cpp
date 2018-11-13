#include "..\..\include\ari\PluginManager.hpp"
#include <bx/macros.h>
#include "../../include/ari/Engine.hpp"

#if BX_PLATFORM_WINDOWS

#include <Windows.h>

#else

#include <dlfcn.h>

#endif

namespace ari
{
	bool PluginManager::LoadResource(Plugin ** ppOut, uint32_t handle, const std::string filename, void * extraParams)
	{
		// RegisterPlugin function pointer
		typedef Plugin*(*RegisterPlugin) (Engine*, const uint32_t&, const std::string&);

		bool bLoadFailed = false;
		RegisterPlugin pFn = NULL;


#if BX_PLATFORM_WINDOWS
		// Load .dll files under windows OS
		std::string strPluginName = filename;
		strPluginName += ".dll";

		// Load dll and check for success
		HMODULE hMod = LoadLibrary(strPluginName.c_str());

		if (hMod)
		{
			pFn = (RegisterPlugin)GetProcAddress(hMod, "RegisterPlugin");
			if (!pFn)
			{
				//io::Logger::Error("RegisterPlugin function dose not find in %s plugin.", strPluginName.c_str());
				return false;
			}
		}
		else
		{
//			io::Logger::Error("can't load the %s plugin. (file not found) %d", strPluginName.c_str(), GetLastError());
			return false;
		}

#else

		std::string strPluginName;
		strPluginName = "lib";
		strPluginName += filename;
		strPluginName += ".so";

		void* handle = dlopen(strPluginName.c_str(), RTLD_LAZY);

		char* error;

		if (!handle)
		{
			//io::Logger::Error("can't load the %s plugin. (%s)", strPluginName.c_str(), dlerror());
			return false;
		}
		// Clear any exiting error
		dlerror();

		// Load the RegisterPlugin function
		pFn = (RegisterPlugin)dlsym(handle, "RegisterPlugin");
		if ((error = (char*)dlerror()) != NULL || !pFn)
		{
			//io::Logger::Error("RegisterPlugin function dose not find in %s plugin.\n%s", strPluginName.c_str(), error);
			return false;
		}

#endif

		// Call the RegisterPlugin function
		*ppOut = (*pFn)(g_pEngine, handle, filename);
		//io::Logger::SuccessKGE("Plugin %s loaded successfully.", strPluginName.c_str());

		return true;
	}

} // ari
