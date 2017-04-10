#pragma once

#include "EventPublisher.h"

namespace FieaGameEngine
{
	template<typename T>
	class Event : public EventPublisher
	{
		RTTI_DECLARATIONS(Event, EventPublisher)

	public:

		Event(const T&, bool destroy);

		static void Subscribe(const class EventSubscriber& subscriber);

		static void Unsubscribe(const class EventSubscriber& subscriber);

		static void UnsubscribeAll();

		T& Message();

		Event(const Event& rhs);
		Event& operator=(const Event& rhs);

		Event(const Event&& rhs);
		Event& operator=(const Event&& rhs);

	private:

		T mMessage;
	};
}

#include "Event.inl"
