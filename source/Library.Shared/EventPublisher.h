#pragma once

#include "RTTI.h"
#include "EventSubscriber.h"
#include "Vector.h"
#include <chrono>

namespace FieaGameEngine
{
	class EventPublisher : public RTTI
	{
		EventPublisher(Vector<EventSubscriber>& subscribers, bool destroyEvent);

		~EventPublisher() = default;

		void SetTime(std::chrono::high_resolution_clock::time_point currentTime,
					 std::chrono::milliseconds delay);

		std::chrono::high_resolution_clock::time_point TimeEnqueued() const;

		std::chrono::milliseconds Delay() const;
	
		bool IsExpired(std::chrono::high_resolution_clock::time_point currentTime) const;

		void Deliver();

		bool DeleteAfterPublishing() const;

		EventPublisher(const EventPublisher& rhs) = default;
		EventPublisher& operator=(const EventPublisher& rhs) = default;

		EventPublisher(EventPublisher&& rhs);
		EventPublisher& operator=(EventPublisher&& rhs);

	protected:

		Vector<EventSubscriber>* mSubscribers;

		bool mDestroyEvent;

		std::chrono::high_resolution_clock::time_point mTimeEnqueued;

		std::chrono::milliseconds mDelay;
	};
}
