#pragma once
#include "../../../include/ari/Device.hpp"
#include "bx/handlealloc.h"
#include "bx/mutex.h"

struct SDL_Window;

namespace ari
{
	struct WindowHandle { uint16_t idx; };
	inline bool isValid(WindowHandle _handle) { return UINT16_MAX != _handle.idx; }

	class SdlWindow
	{
	public:

		bool Init(InitParams& params);

		void setWindowSize(WindowHandle _handle, uint32_t _width, uint32_t _height, bool _force);

		bool Run();

	protected:


		WindowHandle findHandle(uint32_t _windowId);

		WindowHandle findHandle(SDL_Window * _window);

		bx::HandleAllocT<ARI_CONFIG_MAX_WINDOW> m_windowAlloc;
		SDL_Window* m_window[ARI_CONFIG_MAX_WINDOW];
		uint32_t m_flags[ARI_CONFIG_MAX_WINDOW];
		InitParams m_params;
		bx::Mutex m_lock;
		int m_mx, m_my;

	}; // SdlWindow

} // ari
