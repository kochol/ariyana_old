#pragma once

#include "../Component.hpp"
#include "../../math/Vector.hpp"

namespace ari
{
	class ARI_API Node3D: public Component
	{
	public:

		//! Constructor
		Node3D(): Scale(1.0f, 1.0f, 1.0f) { }

		//! Destructor
		virtual ~Node3D() = default;

		Vector3 Position,
			Rotation,
			Scale;

	}; // Node3D
	
} // ari
