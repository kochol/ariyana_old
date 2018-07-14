#include "..\..\..\include\ari\Node.hpp"
#include "..\..\..\include\ari\World.hpp"
#include "..\..\..\include\ari\Component.hpp"
#include "..\..\..\include\ari\Entity.hpp"
#include <cassert>

namespace ari
{
	Node::Node() : m_pParent(nullptr), m_eNodeType(Type::Unknown), m_pWorld(nullptr)
	{
	}

	Node::~Node()
	{
		m_pParent = nullptr;
		RemoveChildren();
	}

	template <class T>
	void Node::AddChild(T* child)
	{
		m_vChilds.push_back(child);
		child->SetParent(this);

		if (m_eNodeType == Type::Component)
		{
			assert(m_pWorld);
			m_pWorld->emit<events::OnComponentAssigned<T>>({ GetParentEntity(), static_cast<T*>(this) });
		}

	} // AddChild

	template <class T>
	void Node::RemoveChild(T* child)
	{
		for (tinystl::vector<Node*>::iterator it = m_vChilds.begin();
			 it != m_vChilds.end(); ++it)
		{
			if ((*it) == child)
			{
				child->m_pParent = nullptr;
				m_vChilds.erase(it);
				if (m_eNodeType == Type::Component)
				{
					assert(m_pWorld);
					m_pWorld->emit<events::OnComponentRemoved<T>>({ GetParentEntity(), static_cast<T*>(this) });
				}
				return;
			}
		}

	} // RemoveChild

	void Node::RemoveChildren()
	{
		//for (auto & node : m_vChilds)
		//{
		//	node->m_pParent = nullptr;
		//}

		m_vChilds.clear();

	} // RemoveChildren

	void Node::SetParent(Node* parent)
	{
		if (m_pParent)
		{
			m_pParent->RemoveChild(this);
		}
		m_pParent = parent;

	} // SetParent

	Entity* Node::GetParentEntity() const
	{
		if (m_pParent)
		{
			if (m_pParent->m_eNodeType == Type::Entity)
			{
				return static_cast<Entity*>(m_pParent);
			}
			return m_pParent->GetParentEntity();
		}
		return nullptr;
	}

} // ari
