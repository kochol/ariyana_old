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

		virtual bool BeginRender() { return true; }

		virtual void EndRender() { }

		bool SameLine = false;

		bool Visible = true;

	}; // Gui

} // ari
