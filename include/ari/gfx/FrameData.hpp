#pragma once
#include "../aridef.hpp"
#include "../math/Matrix.hpp"
#include "../en/3d/Node3D.hpp"

namespace ari
{
	class ARI_API FrameData
	{
	public:
		FrameData(): FrameNumber(0)
		{}

		tinystl::vector<Node3D*> Nodes;
		tinystl::vector<Matrix> WorldMatrices;
		uint32_t FrameNumber;
		
	}; // FrameData

} // ari
