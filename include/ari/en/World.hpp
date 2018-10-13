#pragma once
#include "../aridef.hpp"
#include "tinystl/vector.h"
#include "EventSubscriber.hpp"
#include <algorithm>
#include <unordered_map>

namespace ftl
{
	class TaskScheduler;
}

namespace ari
{
	class System;
	class Entity;

	class ARI_API World
	{
	public:

		enum class UpdateType
		{
			Sync,
			Async
		};

		//! Constructor
		World();

		//! Destructor
		~World();

		void SetUpdateType(UpdateType type) { m_UpdateType = type; }

		UpdateType GetUpdateType() const { return m_UpdateType; }

		/**
		 * Add a new system to the world
		 */
		void AddSystem(System* p_system);

		/**
		 * Removes a system from world
		 */
		void RemoveSystem(System* p_system);

		/**
		 * Adds a new entity to the world
		 */
		void AddEntity(Entity* p_entity);

		/**
		 * Removes an entity from world
		 */
		void RemoveEntity(Entity* p_entity);

		/** 
		 * Updates the world
		 */
		void Update(float tick);

		/**
		* Subscribe to an event.
		*/
		template<typename T>
		void subscribe(EventSubscriber<T>* subscriber)
		{
			auto index = getTypeIndex<T>();
			auto found = subscribers.find(index);
			if (found == subscribers.end())
			{
				tinystl::vector<Internal::BaseEventSubscriber*> subList;
				subList.push_back(subscriber);

				subscribers.insert({ index, subList });
			}
			else
			{
				found->second.push_back(subscriber);
			}
		}

		/**
		* Unsubscribe from an event.
		*/
		template<typename T>
		void unsubscribe(EventSubscriber<T>* subscriber)
		{
			auto index = getTypeIndex<T>();
			auto found = subscribers.find(index);
			if (found != subscribers.end())
			{
				found->second.erase(std::remove(found->second.begin(), found->second.end(), subscriber), found->second.end());
				if (found->second.size() == 0)
				{
					subscribers.erase(found);
				}
			}
		}

		/**
		* Unsubscribe from all events. Don't be afraid of the void pointer, just pass in your subscriber as normal.
		*/
		void unsubscribeAll(void* subscriber)
		{
			for (auto kv : subscribers)
			{
				kv.second.erase(std::remove(kv.second.begin(), kv.second.end(), subscriber), kv.second.end());
				if (kv.second.empty())
				{
					subscribers.erase(subscribers.find(kv.first));
				}
			}
		}


		/**
		* Emit an event. This will do nothing if there are no subscribers for the event type.
		*/
		template<typename T>
		void emit(const T& event)
		{
			auto found = subscribers.find(getTypeIndex<T>());
			if (found != subscribers.end())
			{
				for (auto* base : found->second)
				{
					auto* sub = reinterpret_cast<EventSubscriber<T>*>(base);
					sub->Receive(this, event);
				}
			}
		}

		const tinystl::vector<Entity*>& GetAllEntities() const { return Entities; }

	protected:

		std::unordered_map<TypeIndex,
			tinystl::vector<Internal::BaseEventSubscriber*>> subscribers;
		tinystl::vector<System*> systems;
		tinystl::vector<Entity*> Entities;
		ftl::TaskScheduler	*	m_pTaskScheduler;
		UpdateType				m_UpdateType;

	}; // World

} // ari
