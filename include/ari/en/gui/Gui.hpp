#pragma once
#include "../Component.hpp"

namespace ari
{
	class ARI_API Gui: public Component
	{
	public:

		// Constructor
		Gui() { _isFromGui = true; }

		virtual ~Gui() = default;

		virtual void BeginRender() { }

		virtual void EndRender() { }

	};
} // ari
