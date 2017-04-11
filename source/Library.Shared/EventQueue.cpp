#include "pch.h"

using namespace std::chrono;

namespace FieaGameEngine
{
	void EventQueue::Enqueue(EventPublisher& publisher,
							 GameTime& gameTime,
							 milliseconds delay)
	{
		if (mEvents.Find(&publisher) == mEvents.end())
		{
			publisher.SetTime(gameTime.CurrentTime(), delay);
			mEvents.PushBack(&publisher);
		}
	}

	void EventQueue::Send(EventPublisher& publisher)
	{
		publisher.Deliver();

		// Assume in this case the caller is responsible for deleting the data?
	}

	void EventQueue::Update(GameTime& gameTime)
	{
		for (SList<EventPublisher*>::Iterator it = mEvents.begin(); it != mEvents.end();)
		{
			EventPublisher* publisher = (*it);
			assert(publisher != nullptr);
			++it;

			if (publisher->IsExpired(gameTime.CurrentTime()))
			{
				publisher->Deliver();

				mEvents.Remove(publisher);

				// Only delete heap memory if flagged.
				if (publisher->DeleteAfterPublishing())
				{
					delete publisher;
					publisher = nullptr;
				}
			}
		}
	}

	void EventQueue::Clear()
	{
		for (SList<EventPublisher*>::Iterator it = mEvents.begin(); it != mEvents.end();)
		{
			EventPublisher* subscriber = *it;
			mEvents.PopFront();
			it = mEvents.begin();

			assert(subscriber != nullptr);

			if (subscriber->DeleteAfterPublishing())
			{
				delete subscriber;
			}

			subscriber = nullptr;
		}
	}

	bool EventQueue::IsEmpty() const
	{
		return mEvents.IsEmpty();
	}

	std::uint32_t EventQueue::Size() const
	{
		return mEvents.Size();
	}
}