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

		void SetTime(std::chrono::high_resolution_clock::time_point currentTime,
					 std::chrono::milliseconds delay);

		std::chrono::high_resolution_clock::time_point TimeEnqueued() const;

		std::chrono::milliseconds Delay() const;
	
		bool IsExpired() const;

		void Deliver();

		bool DeleteAfterPublishing() const;

		EventPublisher(const EventPublisher& rhs);
		EventPublisher& operator=(const EventPublisher& rhs);

		EventPublisher(const EventPublisher&& rhs);
		EventPublisher& operator=(const EventPublisher&& rhs);
	};
}
