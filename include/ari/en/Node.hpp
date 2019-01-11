#pragma once

#include "../aridef.hpp"
#include "tinystl/vector.h"
#include <memory>
#include <cassert>
#include <unordered_map>

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
		T* AddChild(T* child)
		{
			m_vChilds.push_back(child);
			child->m_pWorld = m_pWorld;
			child->SetParent(this);

			if (child->m_eNodeType == Type::Component)
			{
				// Add the child to map
				auto index = getTypeIndex<T>();
				auto found = childs.find(index);
				if (found == childs.end())
				{
					tinystl::vector<Node*> subList;
					subList.push_back(child);

					childs.insert({ index, subList });
				}
				else
				{
					found->second.push_back(child);
				}

				assert(m_pWorld);
				m_pWorld->emit<events::OnComponentAssigned<T>>({ child->GetParentEntity(), child });
			}

			return child;

		} // AddChild

		// Returns the first attached component.
		template <class T>
		T* GetChild()
		{
			auto found = childs.find(getTypeIndex<T>());
			if (found != childs.end())
			{
				return found->second[0];
			}
			return nullptr;
		}

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
						// Remove it from map
						auto index = getTypeIndex<T>();
						auto found = childs.find(index);
						if (found != childs.end())
						{
							found->second.erase(std::remove(found->second.begin(), found->second.end(), child), found->second.end());
							if (found->second.size() == 0)
							{
								childs.erase(found);
							}
						}

						assert(m_pWorld);
						m_pWorld->emit<events::OnComponentRemoved<T>>({ child->GetParentEntity(), child });
					}
					return;
				}
			}

		} // RemoveChild

		//! Removes all children of this node.
		void RemoveChildren(bool _delete = false);

		//! Returns the node parent.
		virtual Node* GetParent() { return m_pParent; }

		//! Sets the node parent.
		virtual void SetParent(Node* parent);

		//! Returns the node type.
		Node::Type GetType() const { return m_eNodeType; }

		//! Returns the parent Entity in the tree
		Entity* GetParentEntity() const;

		const tinystl::vector<Node*>& GetChildren() const { return m_vChilds; }

		World* GetWorld() const { return m_pWorld; }

		/**
		 * Send the node to the destroy queue.
		 * It will be deleted in next two frame;
		 */
		void Destroy(bool addToDestroyQueue = true);

		uint32_t IsInDestroyQueue() const { return m_iIsInDestroyQueue; }

	protected:

		Node* m_pParent;
		tinystl::vector<Node*> m_vChilds;
		Node::Type m_eNodeType;
		World* m_pWorld;
		uint32_t m_iIsInDestroyQueue = 0;
		std::unordered_map<TypeIndex,
			tinystl::vector<Node*>> childs;

	}; // Node

} // ari
