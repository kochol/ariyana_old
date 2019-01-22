#pragma once

#include "Node3D.hpp"
#include "../../math/Matrix.hpp"

namespace ari
{
	class ARI_API Camera: public Node3D
	{
	public:

		//! Constructor
		Camera() : Up(0.0f, 1.0f, 0.0f), _isActive(false) { }

		//! Destructor
		virtual ~Camera() = default;

		Vector3 Target,
			Up,
			Right;
		Matrix _view,
			_proj;
		bool _isActive;

		//! Rotate the camera around an axis.
		void Rotate(float _angle, const Vector3& _axis);

		//! Rotate by mouse movement
		void RotateByMouse(int _x, int _y, float _speed);

		//! Move back & forward
		void MoveBF(const float& _speed);

		//! Move left & right
		void MoveLR(const float& _speed);

		//! Move up & down
		void MoveUD(const float& _speed);

	protected:

		float			m_fCurRotX  = 0.0f, // Current Rotation X
						m_fLastRotX = 0.0f;	// Last Rotation X

	}; // Camera
	
} // ari
