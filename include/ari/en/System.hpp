#pragma once
#include "../aridef.hpp"

namespace ari
{
	class World;

	class ARI_API System
	{
	public:

		//! Constructor
		System() = default;

		//! Destructor
		virtual ~System() = default;

		//! Update the system
		virtual void Update(float tick) = 0;

		//! Configure the system after adding it to the world
		virtual void Configure(World* p_world) = 0;

		//! Unconfigure the system before removing it from the world
		virtual void Unconfigure(World* p_world) = 0;

	}; // System
	
} // ari
