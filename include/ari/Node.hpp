#pragma once

#include "aridef.hpp"
#include "tinystl/vector.h"
#include <memory>

namespace ari
{
	class World;
	class Entity;

	class ARI_API Node
	{
		friend class World;

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
		template <class T>
		void AddChild(T* child);

		/*! Removes a child from this node.
		\param child The pointer to the child.
		*/
		template <class T>
		void RemoveChild(T* child);

		//! Removes all children of this node.
		void RemoveChildren();

		//! Returns the node parent.
		virtual Node* GetParent() { return m_pParent; }

		//! Sets the node parent.
		virtual void SetParent(Node* parent);

		//! Returns the node type.
		Node::Type GetType() const { return m_eNodeType; }

		//! Returns the parent Entity in the tree
		Entity* GetParentEntity() const;


	protected:

		Node* m_pParent;
		tinystl::vector<Node*> m_vChilds;
		Node::Type m_eNodeType;
		World* m_pWorld;

	}; // Node

} // ari
