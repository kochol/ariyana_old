#pragma once
#include "../System.hpp"
#include "../EventSubscriber.hpp"

namespace ari
{
	class Node;
	class Dock;

	class ARI_API GuiSystem: public System,
		public EventSubscriber<events::OnComponentAssigned<Dock>>
	{
		friend class AriImwWindow;

	public:

		GuiSystem();
		virtual ~GuiSystem();

		void Update(World* p_world, UpdateState state) override;
		void Configure(World* p_world) override;
		void Unconfigure(World* p_world) override;
		Type GetSystemType() override;
		bool NeedUpdateOnState(UpdateState state) override;

		void Receive(World* world, const events::OnComponentAssigned<Dock>& event) override;
		
	protected:
		bool	m_bIsDockCreated;

		void RenderGui(Node* node);
	};
}
