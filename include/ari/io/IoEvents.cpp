#include "IoEvents.hpp"
#include "../Engine.hpp"

namespace ari
{
	const Event * poll()
	{
		return g_pEngine->Poll();
	}

	const Event * poll(WindowHandle _handle)
	{
		BX_UNUSED(_handle);
		return nullptr;
	}

	void release(const Event * _event)
	{
		g_pEngine->Release(_event);
	}
}
