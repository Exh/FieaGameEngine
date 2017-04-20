#pragma once

#include "EventSubscriber.h"

namespace FieaGameEngine
{
	class SubscriberAdder : public EventSubscriber
	{
	public:

		SubscriberAdder();

		virtual void Notify(const EventPublisher& publisher) override;

	public:

		EventSubscriber* mSpawnedSubscriber;
	};
}