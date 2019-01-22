#pragma once

#include <bx/math.h>
#include "arimath.hpp"

namespace ari
{
	struct Vector3
	{
		Vector3(): x(0.0f), y(0.0f), z(0.0f) { }

		Vector3(const float _x, const float _y, const float _z): x(_x), y(_y), z(_z) { }

		void Set(const float _x, const float _y, const float _z)
		{
			x = _x;
			y = _y;
			z = _z;
		}

		Vector3 operator-(const Vector3& v) const
		{
			return { x - v.x, y - v.y, z - v.z };
		}

		void Cross(const Vector3& _v1, const Vector3& _v2)
		{
			x = _v1.y*_v2.z - _v1.z*_v2.y;
			y = _v1.z*_v2.x - _v1.x*_v2.z;
			z = _v1.x*_v2.y - _v1.y*_v2.x;
		}

		//! Returns the vector length
		float GetLength() const
		{
			return sqrtf(x*x + y * y + z * z);
		}

		void Normalize()
		{
			float length = GetLength();
			length = fEpsilon > length ? fEpsilon : length;
			x /= length;
			y /= length;
			z /= length;
		}

		bx::Vec3 ToVec3() const
		{
			return {
				x,
				y,
				z
			};
		}

		union
		{
			float v[3];
			struct {
				float x,
					y,
					z;
			};
		};
	}; // Vector3

} // ari
