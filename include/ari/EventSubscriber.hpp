#pragma once
#include "aridef.hpp"
#include <memory>

namespace ari
{
	class World;
	class Entity;
	class Component;

	/**
	* Subclass this as EventSubscriber<EventType> and then call World::subscribe() in order to subscribe to events. Make sure
	* to call World::unsubscribe() or World::unsubscribeAll() when your subscriber is deleted!
	*/
	template<typename T>
	class ARI_API EventSubscriber
	{
	public:

		virtual ~EventSubscriber() = default;

		/**
		* Called when an event is emitted by the world.
		*/
		virtual void receive(World* world, const T& event) = 0;

	}; // EventSubscriber


	namespace events
	{
		// Called when a new entity is created.
		struct OnEntityCreated
		{
			ARI_DECLARE_TYPE;

			Entity* entity;
		};

		// Called when an entity is about to be destroyed.
		struct OnEntityDestroyed
		{
			ARI_DECLARE_TYPE;

			Entity* entity;
		};

		// Called when a component is assigned (not necessarily created).
		struct OnComponentAssigned
		{
			ARI_DECLARE_TYPE;

			Entity* entity;
			std::weak_ptr<Component> component;
		};

		// Called when a component is removed
		struct OnComponentRemoved
		{
			ARI_DECLARE_TYPE;

			Entity* entity;
			std::weak_ptr<Component> component;
		};
	} // events

} // ari
