#pragma once

#include "EventPublisher.h"

namespace FieaGameEngine
{
	template<typename T>
	class Event final : public EventPublisher
	{
		RTTI_DECLARATIONS(Event, EventPublisher)

	public:

		/** Constructor that takes a reference to the message it will copy,
		and a boolean flag to identify that this event should be deleted by
		the event queue that is processing it.
		@param message Reference to message to copy.
		@param destroy Flag letting queue know it should delete this message.*/
		Event(const T& message, bool destroy = true);

		/** Default destructor */
		~Event() = default;

		/** Given a reference to a subscriber, add it to this Event class' 
		subscriber list. Whenever an event is sent with Deliver(), all
		subscribers will be notified.
		@param subscriber Reference to the subscriber to add.*/
		static void Subscribe(class EventSubscriber& subscriber);

		/** Given a reference to a subscriber, remove it from this Event class' 
		subscriber list. It will no longer be notified when an event of this 
		class is processed and Deliver()'d.
		@param subscriber Reference to the subscriber to remove.*/
		static void Unsubscribe(class EventSubscriber& subscriber);

		/** Removes any subscribers that this event class might have.*/
		static void UnsubscribeAll();

		/** Returns a reference to the message that this event instance contains.
		@return Message reference. */
		const T& Message() const;

		Event(const Event& rhs) = default;
		Event& operator=(const Event& rhs) = default;

		/** Move constructor.
		@param rhs Event to move from.*/
		Event(Event&& rhs);

		
		/** Move constructor.
		@param rhs Event to move from.
		@return Reference to this event. */
		Event& operator=(Event&& rhs);

	private:

		static Vector<EventSubscriber*> sSubscribers;

		T mMessage;
	};
}

#include "Event.inl"
