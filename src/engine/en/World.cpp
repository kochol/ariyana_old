#include "../../../include/ari/en/World.hpp"
#include "../../../include/ari/en/System.hpp"
#include "../../../include/ari/en/Entity.hpp"

namespace ari
{
	void World::AddSystem(System * p_system)
	{
		systems.push_back(p_system);
		p_system->Configure(this);
	}

	void World::RemoveSystem(System * p_system)
	{
		int c = 0;
		for (auto s: systems)
		{
			if (s == p_system)
			{
				p_system->Unconfigure(this);
				systems.erase(systems.begin() + c);
				return;
			}
			c++;
		}
	}

	void World::AddEntity(Entity * p_entity)
	{
		assert(p_entity->GetType() == Node::Type::Entity);
		Entities.push_back(p_entity);
		p_entity->m_pWorld = this;
		emit<events::OnEntityCreated>({ p_entity });
	}

	void World::RemoveEntity(Entity* p_entity)
	{
		assert(p_entity->GetType() == Node::Type::Entity);
		int c = 0;
		for (auto e: Entities)
		{
			if (e == p_entity)
			{
				emit<events::OnEntityDestroyed>({ p_entity });
				e->m_pWorld = nullptr;
				Entities.erase(Entities.begin() + c);
				return;
			}
			c++;
		}
	}

	void World::Update(float tick)
	{
		for (auto s: systems)
		{
			s->Update(this, tick);
		}
	}

} // ari
