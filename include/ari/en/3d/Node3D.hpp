#pragma once

#include "../Component.hpp"
#include "../../math/Vector.hpp"
#include "../../math/Matrix.hpp"

namespace ari
{
	class ARI_API Node3D: public Component
	{
	public:

		//! Constructor
		Node3D() : Scale(1.0f, 1.0f, 1.0f), _isRenderable(false) { _isFromNode3D = true; }

		//! Destructor
		virtual ~Node3D() = default;

		//! Render
		virtual void Render(const Matrix& matrix) { }

		Vector3 Position,
			Rotation,
			Scale;

		Matrix _finalMat;
		bool _isRenderable;

	}; // Node3D
	
} // ari
