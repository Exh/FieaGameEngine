#include "pch.h"

namespace FieaGameEngine
{
	SubscriberAdder::SubscriberAdder() :
		mSpawnedSubscriber(nullptr)
	{
		Event<MessageAddSubscriber>::Subscribe(*this);
	}

	SubscriberAdder::~SubscriberAdder()
	{
		if (mSpawnedSubscriber != nullptr)
		{
			delete mSpawnedSubscriber;
			mSpawnedSubscriber = nullptr;
		}
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

	int  SubscriberAdder::TotalSubscribers() const
	{
		if (mSpawnedSubscriber != nullptr)
		{
			return 1 + mSpawnedSubscriber->TotalSubscribers();
		}

		return 1;
	}
}