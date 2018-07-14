#pragma once

#include "Node3D.hpp"
#include "../../math/Matrix.hpp"

namespace ari
{
	class ARI_API Camera: public Node3D
	{
	public:

		//! Constructor
		Camera();

		//! Destructor
		~Camera();

		Vector3 Target,
			Up,
			Right;
		Matrix _view,
			_proj;
		
	}; // Camera
	
} // ari
