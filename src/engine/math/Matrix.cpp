#include "../../../include/ari/math/Matrix.hpp"
#include "bx/math.h"

namespace ari
{
	void Matrix::Identity()
	{
		bx::mtxIdentity(v);
	}

	Matrix Matrix::operator*(const Matrix& m) const
	{
		Matrix r;
		bx::float4x4_mul(&r.f, &f, &m.f);
		return r;
	}

	void Matrix::operator*=(const Matrix& m)
	{
		bx::float4x4_mul(&f, &f, &m.f);
	}

	void Matrix::SetPositionRotation(const Vector3& position, const Vector3& rotation)
	{
		bx::mtxRotateXYZ(v, rotation.x, rotation.y, rotation.z);
		_41 = position.x;
		_42 = position.y;
		_43 = position.z;
	}

	void Matrix::SetTransform(const Vector3& position, const Vector3& rotation, const Vector3& scale)
	{
		bx::mtxSRT(v, scale.x, scale.y, scale.z,
			rotation.x, rotation.y, rotation.z,
			position.x, position.y, position.z);
	}
} // ari
