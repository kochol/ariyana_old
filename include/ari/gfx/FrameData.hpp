#pragma once
#include "../aridef.hpp"
#include "../math/Matrix.hpp"
#include "../en/3d/Node3D.hpp"

namespace ari
{
	class ARI_API FrameData
	{
	public:
		FrameData(): RenderNode(nullptr), FrameNumber(0)
		{}

		Node3D * RenderNode;
		Matrix World;
		uint32_t FrameNumber;
		
	}; // FrameData

} // ari
