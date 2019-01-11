#pragma once
#include "DockWindow.hpp"

namespace shiva
{
	class SHIVA_API Viewport : public DockWindow
	{
	public:

		void Init(ari::World* p_world) override;

	};

} // shiva
