#include "../../../include/ari/Plugin.hpp"
#include "../../../include/ari/Engine.hpp"
#include "BimgLoader.hpp"

namespace ari
{
	class BimgPlugin : public Plugin
	{
	public:

		BimgPlugin(const uint32_t& _handel, const std::string& _fileName)
			: Plugin(_handel, _fileName)
		{
			m_eType = Type::TextureLoader;
		}

		void* Create() override
		{
			BimgLoader* p = new BimgLoader();
			return reinterpret_cast<void*>(p);
		}

	};
} // ari

extern "C"
{
	ARI_PLUGIN_API ari::Plugin* RegisterPlugin(ari::Engine* pEngine, const uint32_t& _handel,
		const std::string& _fileName)
	{
		ari::BimgPlugin* p = new ari::BimgPlugin(_handel, _fileName);
		pEngine->texture_manager.AddLoader(reinterpret_cast<ari::ResourceLoader*>(p->Create()));
		return p;
	}
}
