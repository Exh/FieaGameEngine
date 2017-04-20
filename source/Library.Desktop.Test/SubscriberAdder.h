#pragma once

#include "EventSubscriber.h"

namespace FieaGameEngine
{
	class SubscriberAdder : public EventSubscriber
	{
	public:

		SubscriberAdder();

		~SubscriberAdder();

		virtual void Notify(const EventPublisher& publisher) override;

		int TotalSubscribers() const;

	public:

		SubscriberAdder* mSpawnedSubscriber;
	};
}