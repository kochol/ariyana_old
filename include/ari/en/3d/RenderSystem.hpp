#pragma once
#include "../System.hpp"
#include "../EventSubscriber.hpp"

namespace ari
{
	class ARI_API RenderSystem: public System
	{
	public:
		RenderSystem() = default;
		~RenderSystem() = default;

		void Update(World* p_world, float tick) override;
		void Configure(World* p_world) override;
		void Unconfigure(World* p_world) override;
	};
	
} // ari
