#pragma once
#include "../aridef.hpp"
#include <memory>

namespace ari
{
	class World;
	class Entity;
	class Component;
	class FrameData;

	namespace Internal
	{
		class ARI_API BaseEventSubscriber
		{
		public:

			virtual ~BaseEventSubscriber() = default;
		};
		
	} // Internal

	/**
	* Subclass this as EventSubscriber<EventType> and then call World::subscribe() in order to subscribe to events. Make sure
	* to call World::unsubscribe() or World::unsubscribeAll() when your subscriber is deleted!
	*/
	template<typename T>
	class ARI_API EventSubscriber: public Internal::BaseEventSubscriber
	{
	public:

		virtual ~EventSubscriber() = default;

		/**
		* Called when an event is emitted by the world.
		*/
		virtual void Receive(World* world, const T& event) = 0;

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
		template <class T>
		struct OnComponentAssigned
		{
			ARI_DECLARE_TYPE;

			Entity* entity;
			T* component;
		};

		// Called when a component is removed
		template <class T>
		struct OnComponentRemoved
		{
			ARI_DECLARE_TYPE;

			Entity* entity;
			T* component;
		};

		struct OnFrameData
		{
			ARI_DECLARE_TYPE;

			FrameData* frame_data;

		};

	} // events

} // ari
