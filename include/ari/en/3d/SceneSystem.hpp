#pragma once
#include "../System.hpp"
#include "../EventSubscriber.hpp"
#include "../../gfx/FrameData.hpp"

namespace ari
{
	class Camera;
	class BoxShape;
	class Node;

	class ARI_API SceneSystem: public System,
		public EventSubscriber<events::OnEntityCreated>,
		public EventSubscriber<events::OnEntityDestroyed>,
		public EventSubscriber<events::OnComponentAssigned<Camera>>,
		public EventSubscriber<events::OnComponentRemoved<Camera>>,
		public EventSubscriber<events::OnComponentAssigned<BoxShape>>,
		public EventSubscriber<events::OnComponentRemoved<BoxShape>>
	{
	public:

		//! Constructor
		SceneSystem();

		//! Destructor
		~SceneSystem();

		void Update(World* p_world, UpdateState state) override;
		void Configure(World* p_world) override;
		void Unconfigure(World* p_world) override;
		Type GetSystemType() override
		{
			return Type::SceneSystem;
		}
		bool NeedUpdateOnState(UpdateState state) override;

		void Receive(World* world, const events::OnEntityCreated& event) override;
		void Receive(World* world, const events::OnEntityDestroyed& event) override;
		void Receive(World* world, const events::OnComponentAssigned<Camera>& event) override;
		void Receive(World* world, const events::OnComponentRemoved<Camera>& event) override;
		void Receive(World* world, const events::OnComponentAssigned<BoxShape>& event) override;
		void Receive(World* world, const events::OnComponentRemoved<BoxShape>& event) override;

	protected:

		Camera * m_pActiveCamera;
		FrameData	*	m_FrameDatasUnused,			// This is the unused frame data pointers
					*	m_FrameDatasTransforms,		// This is the transform calculated nodes
					*	m_FrameDatasVisible;		// This is the visible nodes that must be rendered.

		void CalcTransform(Node* node, Matrix* parentMat);

	}; // SceneSystem
	
} // ari
