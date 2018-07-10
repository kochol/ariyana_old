#include "..\..\..\include\ari\Node.hpp"

namespace ari
{
	Node::Node() : m_pParent(nullptr), m_eNodeType(Type::Unknown)
	{
	}

	Node::~Node()
	{
		m_pParent = nullptr;
		RemoveChildren();
	}

	void Node::AddChild(std::shared_ptr<Node> child)
	{
		m_vChilds.push_back(child);
		child->SetParent(shared_from_this());

	} // AddChild

	void Node::RemoveChild(std::shared_ptr<Node> child)
	{
		for (tinystl::vector<std::shared_ptr<Node>>::iterator it = m_vChilds.begin();
			 it != m_vChilds.end(); ++it)
		{
			if ((*it) == child)
			{
				child->m_pParent = nullptr;
				m_vChilds.erase(it);
				return;
			}
		}

	} // RemoveChild

	void Node::RemoveChildren()
	{
		for (auto & node : m_vChilds)
		{
			node->m_pParent = nullptr;
		}

		m_vChilds.clear();

	} // RemoveChildren

	void Node::SetParent(std::shared_ptr<Node> parent)
	{
		if (m_pParent)
		{
			m_pParent->RemoveChild(shared_from_this());
		}
		m_pParent = parent;

	} // SetParent

} // ari
