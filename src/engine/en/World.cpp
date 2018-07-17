#include "../../../include/ari/en/World.hpp"
#include "../../../include/ari/en/System.hpp"

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

	void World::Update(float tick)
	{
		for (auto s: systems)
		{
			s->Update(this, tick);
		}
	}

} // ari
