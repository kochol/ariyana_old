#pragma once
#include "Node.hpp"

namespace ari
{
	class ARI_API Component: public Node
	{
	public:

		//! Constructor
		Component();

		//! Destructor
		virtual ~Component() = default;

		bool IsFromNode3D;
		
	}; // Component

} // ari
