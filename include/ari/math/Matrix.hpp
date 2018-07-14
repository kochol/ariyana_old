#pragma once

#include "../aridef.hpp"

namespace ari
{
	struct Matrix
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
		};

		//! Constructor: Identity the matrix.
		Matrix() :
			_11(1.0f), _12(0.0f), _13(0.0f), _14(0.0f),
			_21(0.0f), _22(1.0f), _23(0.0f), _24(0.0f),
			_31(0.0f), _32(0.0f), _33(1.0f), _34(0.0f),
			_41(0.0f), _42(0.0f), _43(0.0f), _44(1.0f)
		{ }
		
	}; // Matrix

} // ari
