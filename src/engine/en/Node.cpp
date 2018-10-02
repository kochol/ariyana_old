#include "../../../include/ari/en/Node.hpp"
#include "../../../include/ari/en/World.hpp"
#include "../../../include/ari/en/Component.hpp"
#include "../../../include/ari/en/Entity.hpp"
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
