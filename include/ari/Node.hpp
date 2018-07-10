#pragma once

#include "aridef.hpp"
#include "tinystl/vector.h"
#include <memory>

namespace ari
{
	class ARI_API Node: public std::enable_shared_from_this<Node>
	{
	public:

		enum class Type
		{
			Entity = 0,
			Component,

			Unknown

		};

		//! Constructor
		Node();

		//! Destructor
		virtual ~Node();

		//! Adds a node as child.
		virtual void AddChild(std::shared_ptr<Node> child);

		/*! Removes a child from this node.
		\param child The pointer to the child.
		*/
		virtual void RemoveChild(std::shared_ptr<Node> child);

		//! Removes all children of this node.
		void RemoveChildren();

		//! Returns the node parent.
		virtual std::shared_ptr<Node> GetParent() { return m_pParent; }

		//! Sets the node parent.
		virtual void SetParent(std::shared_ptr<Node> parent);

		//! Returns the node type.
		Node::Type GetType() const { return m_eNodeType; }

	protected:

		std::shared_ptr<Node> m_pParent;
		tinystl::vector<std::shared_ptr<Node>> m_vChilds;
		Node::Type m_eNodeType;

	}; // Node

} // ari
