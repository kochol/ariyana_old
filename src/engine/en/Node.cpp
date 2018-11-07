#include "../../../include/ari/en/Node.hpp"
#include "../../../include/ari/en/World.hpp"
#include "../../../include/ari/en/Component.hpp"
#include "../../../include/ari/en/Entity.hpp"
#include <cassert>
#include "../../../include/ari/Engine.hpp"

namespace ari
{
	Node::Node() : m_pParent(nullptr), m_eNodeType(Type::Unknown), m_pWorld(nullptr)
	{
	}

	Node::~Node()
	{
		RemoveChildren(true);
	}

	void Node::RemoveChildren(bool _delete)
	{
		if (_delete)
			for (auto & node : m_vChilds)
			{
				delete node;
			}
		else
		{
			for (auto & node : m_vChilds)
			{
				node->m_pParent = nullptr;
			}

			m_vChilds.clear();
		}

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

	void Node::Destroy(bool addToDestroyQueue)
	{
		assert(m_pWorld);
		m_iIsInDestroyQueue = g_pEngine->GetCurrentFrameNumber() + 2;
		for (auto child : m_vChilds)
		{
			child->Destroy(false);
		}
		if (addToDestroyQueue)
			m_pWorld->_AddToDestroyQueue(this);
	}

} // ari
