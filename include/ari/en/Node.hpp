#pragma once

#include "../aridef.hpp"
#include "tinystl/vector.h"
#include <memory>
#include <cassert>

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
		void AddChild(T* child)
		{
			m_vChilds.push_back(child);
			child->SetParent(this);

			if (child->m_eNodeType == Type::Component)
			{
				assert(m_pWorld);
				m_pWorld->emit<events::OnComponentAssigned<T>>({ GetParentEntity(), static_cast<T*>(this) });
			}

		} // AddChild

		/*! Removes a child from this node.
		\param child The pointer to the child.
		*/
		template <class T>
		void RemoveChild(T* child)
		{
			for (tinystl::vector<Node*>::iterator it = m_vChilds.begin();
				it != m_vChilds.end(); ++it)
			{
				if ((*it) == child)
				{
					child->m_pParent = nullptr;
					m_vChilds.erase(it);
					if (child->m_eNodeType == Type::Component)
					{
						assert(m_pWorld);
						m_pWorld->emit<events::OnComponentRemoved<T>>({ GetParentEntity(), static_cast<T*>(this) });
					}
					return;
				}
			}

		} // RemoveChild

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
