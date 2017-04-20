#include "pch.h"

namespace FieaGameEngine
{
	SubscriberAdder::SubscriberAdder() :
		mSpawnedSubscriber(nullptr)
	{
		Event<MessageAddSubscriber>::Subscribe(*this);
	}

	void SubscriberAdder::Notify(const EventPublisher& publisher)
	{
		Event<MessageAddSubscriber>* addEvent = publisher.As<Event<MessageAddSubscriber>>();

		if (addEvent != nullptr &&
			mSpawnedSubscriber == nullptr)
		{
			mSpawnedSubscriber = new SubscriberAdder();
		}
	}
}