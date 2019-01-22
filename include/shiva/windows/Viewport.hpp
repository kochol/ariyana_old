#pragma once
#include "DockWindow.hpp"

namespace ari
{
	class Camera;
	class Viewport;
	class Image;
}

namespace shiva
{
	class SHIVA_API Viewport : public DockWindow
	{
	public:

		void Init(ari::World* p_world) override;

	protected:

		ari::Camera			*	m_pCamera			= nullptr;
		ari::Viewport		*	m_pViewport			= nullptr;
		ari::Image			*	m_pView				= nullptr;
		ari::PlatformWindow	*	m_pPlatformWindow	= nullptr;
		ari::DelegateTwoParam<void, int, int>
								m_OnMouseMove;

		void OnGui();
		void OnHovered();

	};

} // shiva
