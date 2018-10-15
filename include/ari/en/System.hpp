#pragma once
#include "../aridef.hpp"

namespace ari
{
	class World;

	class ARI_API System
	{
	public:

		enum class Type
		{
			GameplaySystem,
			SceneSystem,
			RenderSystem
		};

		enum class UpdateState
		{
			GameplayState,
			SceneManagerState,
			MainThreadState
		};

		//! Constructor
		System() = default;

		//! Destructor
		virtual ~System() = default;

		//! Update the system
		virtual void Update(World* p_world, UpdateState state) = 0;

		//! Configure the system after adding it to the world
		virtual void Configure(World* p_world) = 0;

		//! Unconfigure the system before removing it from the world
		virtual void Unconfigure(World* p_world) = 0;

		//! Returns the system type
		virtual Type GetSystemType() = 0;

		//! Ask the system if needs update on different states
		virtual bool NeedUpdateOnState(UpdateState state) = 0;

	}; // System
	
} // ari
