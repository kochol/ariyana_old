#include "../../../include/ari/en/Component.hpp"

namespace ari
{
	Component::Component(): _isFromNode3D(false), _isFromGui(false)
	{
		m_eNodeType = Type::Component;
	}

} // ari
