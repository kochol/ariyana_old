#pragma once
#include "../System.hpp"
#include "../EventSubscriber.hpp"

namespace bgfx
{
	struct VertexDecl;
	struct ProgramHandle;
}

namespace ari
{
	class BoxShape;

	class ARI_API RenderSystem: public System,
		public EventSubscriber<events::OnComponentAssigned<BoxShape>>,
		public EventSubscriber<events::OnFrameData>
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

		void Update(World* p_world, UpdateState state) override;
		void Configure(World* p_world) override;
		void Unconfigure(World* p_world) override;
		Type GetSystemType() override
		{
			return Type::RenderSystem;
		}
		bool NeedUpdateOnState(UpdateState state) override;

		void Receive(World* world, const events::OnComponentAssigned<BoxShape>& event) override;
		void Receive(World* world, const events::OnFrameData& event) override;

		bgfx::VertexDecl* GetVertexDecl(VertexType vertex_type) const;

		bgfx::ProgramHandle* GetProgram() const { return m_Program; }
		
	protected:

		bgfx::VertexDecl	*	m_pVertexDeclArray;
		bgfx::ProgramHandle	*	m_Program;
		FrameData			*	m_pFrameDataCurrent,
							*	m_pFrameDataNext;
	};
	
} // ari
