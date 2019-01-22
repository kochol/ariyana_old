#include "../../../../include/ari/en/3d/Camera.hpp"

namespace ari
{
	void Camera::Rotate(float _angle, const Vector3 & _axis)
	{
		Vector3 vLook;				// Looking point.

		const Vector3 vDir = Target - Position; // Looking direction.

		const float cost = bx::cos(_angle);
		const float sint = bx::sin(_angle);

		// Find the new x position for the new rotated point
		vLook.x = (cost + (1 - cost) * _axis.x * _axis.x)				* vDir.x;
		vLook.x += ((1 - cost) * _axis.x * _axis.y - _axis.z * sint)	* vDir.y;
		vLook.x += ((1 - cost) * _axis.x * _axis.z + _axis.y * sint)	* vDir.z;

		// Find the new y position for the new rotated point
		vLook.y = ((1 - cost) * _axis.x * _axis.y + _axis.z * sint)		* vDir.x;
		vLook.y += (cost + (1 - cost) * _axis.y * _axis.y)				* vDir.y;
		vLook.y += ((1 - cost) * _axis.y * _axis.z - _axis.x * sint)	* vDir.z;

		// Find the new z position for the new rotated point
		vLook.z = ((1 - cost) * _axis.x * _axis.z - _axis.y * sint)		* vDir.x;
		vLook.z += ((1 - cost) * _axis.y * _axis.z + _axis.x * sint)	* vDir.y;
		vLook.z += (cost + (1 - cost) * _axis.z * _axis.z)				* vDir.z;


		// Now we just add the newly rotated vector to our position to set
		// our new rotated view of our camera.
		Target.x = Position.x + vLook.x;
		Target.y = Position.y + vLook.y;
		Target.z = Position.z + vLook.z;

	} // Rotate

	void Camera::RotateByMouse(int _x, int _y, float _speed)
	{
		if ((_x == 0) && (_y == 0))
			return;

		_x *= -1;
		_y *= -1;
		float angleY = 0.0f; 
		float angleZ = 0.0f;

		angleY = float(_x) * _speed;
		angleZ = float(_y) * _speed;

		m_fLastRotX = m_fCurRotX;

		m_fCurRotX += angleZ;

		// calculate the correct up
		Vector3 view = Target - Position;
		view.Normalize();
		Vector3 right;
		right.Cross(Up, view);
		right.Normalize();
		Up.Cross(view, right);

		Vector3 vAxis;
		vAxis.Cross(view, Up);
		vAxis.Normalize();

		if (m_fCurRotX > 1.0f)
		{
			m_fCurRotX = 1.0f;
			if (m_fLastRotX < 1.0f)
			{
				Rotate(1.0f - m_fLastRotX, vAxis);
			} // if (LastRotX != 1.0f)

		} // if (m_fCurRotX > 1.0f)
		else if (m_fCurRotX < -1.0f)
		{
			m_fCurRotX = -1.0f;
			if (m_fLastRotX > -1.0f)
			{
				Rotate(-1.0f - m_fLastRotX, vAxis);
			} // if (m_fLastRotX < -1.0f)

		} // if (m_fCurRotX < -1.0f)
		else
		{
			Rotate(angleZ, vAxis);
		}
		Rotate(-angleY, Vector3(0.0f, 1.0f, 0.0f));
	}

}
