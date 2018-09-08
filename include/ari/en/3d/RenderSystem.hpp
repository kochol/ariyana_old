#pragma once
#include "../System.hpp"
#include "../EventSubscriber.hpp"

namespace bgfx
{
	struct VertexDecl;
}

namespace ari
{
	class BoxShape;

	class ARI_API RenderSystem: public System,
		public EventSubscriber<events::OnComponentAssigned<BoxShape>>
	{
	public:

		enum class VertexType
		{
			Pos, 
			Color,
			Count
		};

		RenderSystem();
		~RenderSystem();

		void Update(World* p_world, float tick) override;
		void Configure(World* p_world) override;
		void Unconfigure(World* p_world) override;

		void Receive(World* world, const events::OnComponentAssigned<BoxShape>& event) override;

		bgfx::VertexDecl* GetVertexDecl(VertexType vertex_type) const;

	protected:

		bgfx::VertexDecl	*	m_pVertexDeclArray;
	};
	
} // ari
