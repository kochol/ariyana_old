#pragma once
#include "Node.hpp"

namespace ari
{
	class ARI_API Component: public Node
	{
		//! Constructor
		Component();

		//! Destructor
		virtual ~Component() = default;
		
	}; // Component

} // ari
