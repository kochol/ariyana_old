#pragma once
#include "../System.hpp"
#include "../EventSubscriber.hpp"

namespace ari
{
	class Camera;

	class ARI_API SceneSystem: public System,
		public EventSubscriber<events::OnEntityCreated>,
		public EventSubscriber<events::OnEntityDestroyed>,
		public EventSubscriber<events::OnComponentAssigned<Camera>>,
		public EventSubscriber<events::OnComponentRemoved<Camera>>
	{
	public:

		//! Constructor
		SceneSystem();

		//! Destructor
		~SceneSystem();

		void Update(World* p_world, float tick) override;
		void Configure(World* p_world) override;
		void Unconfigure(World* p_world) override;

		void Receive(World* world, const events::OnEntityCreated& event) override;
		void Receive(World* world, const events::OnEntityDestroyed& event) override;
		void Receive(World* world, const events::OnComponentAssigned<Camera>& event) override;
		void Receive(World* world, const events::OnComponentRemoved<Camera>& event) override;

	protected:

		Camera * m_pActiveCamera;

	}; // SceneSystem
	
} // ari
