#pragma once
#include "../aridef.hpp"
#include "../math/Matrix.hpp"
#include <tinystl/vector.h>

namespace ari
{
	class Node3D;
	class Camera;

	class ARI_API FrameData
	{
	public:
		FrameData(): FrameNumber(0)
		{}

		tinystl::vector<Node3D*> Nodes;
		tinystl::vector<Matrix> WorldMatrices;
		uint32_t FrameNumber;
		Camera* Camera;
		
	}; // FrameData

} // ari
