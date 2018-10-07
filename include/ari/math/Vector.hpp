#pragma once

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
