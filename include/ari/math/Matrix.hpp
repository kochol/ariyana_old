#pragma once

#include "../aridef.hpp"
#include "bx/macros.h"
#include "bx/float4x4_t.h"
#include "Vector.hpp"

namespace ari
{
	BX_ALIGN_DECL_16(struct) Matrix
	{
		union
		{
			float v[16];
			struct
			{
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
			bx::float4x4_t f;
		};

		//! Constructor: Identity the matrix.
		Matrix() :
			_11(1.0f), _12(0.0f), _13(0.0f), _14(0.0f),
			_21(0.0f), _22(1.0f), _23(0.0f), _24(0.0f),
			_31(0.0f), _32(0.0f), _33(1.0f), _34(0.0f),
			_41(0.0f), _42(0.0f), _43(0.0f), _44(1.0f)
		{ }

		//! make identity matrix
		void Identity();		
		
		//! Multiply of two matrices.
		Matrix operator *(const Matrix &m) const;

		//! Multiply of two matrices.
		void operator *=(const Matrix &m);

		//! Set position and rotation
		void SetPositionRotation(const Vector3& position,
			const Vector3& rotation);

		//! Optimized function to set position, rotation and scale at once.
		void SetTransform(const Vector3& position,
			const Vector3& rotation,
			const Vector3& scale);

	}; // Matrix

} // ari
