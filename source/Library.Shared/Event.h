#pragma once

#include "EventPublisher.h"

namespace FieaGameEngine
{
	template<typename T>
	class Event : public EventPublisher
	{
		RTTI_DECLARATIONS(Event, EventPublisher)

	public:

		Event(const T&, bool destroy = true);

		static void Subscribe(const class EventSubscriber& subscriber);

		static void Unsubscribe(const class EventSubscriber& subscriber);

		static void UnsubscribeAll();

		const T& Message() const;

		Event(const Event& rhs) = default;
		Event& operator=(const Event& rhs) = default;

		Event(Event&& rhs);
		Event& operator=(Event&& rhs);

	private:

		static Vector<EventSubscriber*> sSubscribers;

		T mMessage;
	};
}

#include "Event.inl"
