#pragma once

#include "Node3D.hpp"
#include "../../math/Matrix.hpp"

namespace ari
{
	class ARI_API Camera: public Node3D
	{
	public:

		//! Constructor
		Camera() : _isActive(false), Up(0.0f, 1.0f, 0.0f) { }

		//! Destructor
		virtual ~Camera() = default;

		Vector3 Target,
			Up,
			Right;
		Matrix _view,
			_proj;
		bool _isActive;
		
	}; // Camera
	
} // ari
