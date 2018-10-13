#include "../../../include/ari/en/World.hpp"
#include "../../../include/ari/en/System.hpp"
#include "../../../include/ari/en/Entity.hpp"
#include <ftl/task_scheduler.h>
#include <ftl/atomic_counter.h>

namespace ari
{
	//---------------------------------------------------------
	//   T A S K   F U N C T I O N S

	struct SystemUpdateTaskData
	{
		World* world;
		System* system;
		System::UpdateState state;
	};

	void SystemUpdateTask(ftl::TaskScheduler *taskScheduler, void *arg)
	{
		auto data = reinterpret_cast<SystemUpdateTaskData*>(arg);
		data->system->Update(data->world, data->state);
		delete data;
	}

	struct MainTaskArg
	{
		World* world;
		tinystl::vector<System*> systems;
	};

	void MainTask(ftl::TaskScheduler *taskScheduler, void *arg)
	{
		MainTaskArg* task_arg =
			reinterpret_cast<MainTaskArg*>(arg);

		// Start the Gameplay state tasks
		ftl::AtomicCounter gameplayCounter(taskScheduler),
			inCounter(taskScheduler),
			sceneCounter(taskScheduler);
		tinystl::vector<ftl::Task> gameplay_tasks,
			independent_tasks,
			scene_tasks;
		for (auto s: task_arg->systems)
		{
			if (s->NeedUpdateOnState(System::UpdateState::GameplayState))
			{
				auto update_arg = new SystemUpdateTaskData;
				update_arg->system = s;
				update_arg->state = System::UpdateState::GameplayState;
				update_arg->world = task_arg->world;
				if (s->GetSystemType() == System::Type::GameplaySystem)
				{
					gameplay_tasks.push_back({ SystemUpdateTask, update_arg });
				}
				else
				{
					independent_tasks.push_back({ SystemUpdateTask , update_arg });
				}
			}
			if (s->NeedUpdateOnState(System::UpdateState::SceneManagerState))
			{
				auto update_arg = new SystemUpdateTaskData;
				update_arg->system = s;
				update_arg->state = System::UpdateState::SceneManagerState;
				update_arg->world = task_arg->world;
				scene_tasks.push_back({ SystemUpdateTask, update_arg });
			}
		}

		// Add gameplay tasks to the taskScheduler
		if (!gameplay_tasks.empty())
			taskScheduler->AddTasks(gameplay_tasks.size(), &gameplay_tasks[0], &gameplayCounter);
		if (!independent_tasks.empty())
			taskScheduler->AddTasks(independent_tasks.size(), &independent_tasks[0], &inCounter);

		// Wait for gameplay tasks to start scene manager tasks
		taskScheduler->WaitForCounter(&gameplayCounter, 0);
		if (!scene_tasks.empty())
			taskScheduler->AddTasks(scene_tasks.size(), &scene_tasks[0], &sceneCounter);

		taskScheduler->WaitForCounter(&sceneCounter, 0);
		taskScheduler->WaitForCounter(&inCounter, 0);

	}

	//   T A S K   F U N C T I O N S
	//---------------------------------------------------------

	World::World()
	{
		m_pTaskScheduler = new ftl::TaskScheduler();

	} // Constructor

	World::~World()
	{
		delete m_pTaskScheduler;

	} // Destructor

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
		MainTaskArg arg = { this, systems };
		m_pTaskScheduler->Run(25, MainTask, &arg);
	}

} // ari
