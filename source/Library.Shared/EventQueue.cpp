#include "pch.h"

using namespace std;
using namespace std::chrono;

namespace FieaGameEngine
{
	void EventQueue::Enqueue(EventPublisher& publisher,
							 GameTime& gameTime,
							 milliseconds delay)
	{
		lock_guard<recursive_mutex> lock(mMutex);

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
		// Remove all expired events into a separate list for delivery.
		// The remaining events in mEvents will be unexpired.
		SList<EventPublisher*> expiredEvents;

		{
			lock_guard<recursive_mutex> lock(mMutex);

			for (SList<EventPublisher*>::Iterator it = mEvents.begin(); it != mEvents.end(); ++it)
			{
				SList<EventPublisher*>::Iterator currentIt = it++;

				// it is pointer to next item
				if (it != mEvents.begin())
				{
					if ((*it)->IsExpired(gameTime.CurrentTime()))
					{
						EventPublisher* publisher = (*it);
						mEvents.Remove(publisher);

						expiredEvents.PushBack(publisher);
					}
				}

				it = currentIt;
			}
		}

		vector<future<void>> futures;

		for (SList<EventPublisher*>::Iterator it = expiredEvents.begin(); it != mEvents.end();)
		{
			EventPublisher* publisher = (*it);
			assert(publisher != nullptr);
			++it;

			if (publisher->IsExpired(gameTime.CurrentTime()))
			{
				futures.emplace_back(async(launch::async, [&publisher]{publisher->Deliver();}));
				
				//publisher->Deliver();

				//mEvents.Remove(publisher);

				// Only delete heap memory if flagged.
				//if (publisher->DeleteAfterPublishing())
				//{
				//	delete publisher;
				//	publisher = nullptr;
				//}
			}
		}

		// Join with delivery threads
		for (future<void>& future : futures)
		{
			future.get();
		}

		// Delete publishers after delivering
		for (SList<EventPublisher*>::Iterator it = expiredEvents.begin(); it != expiredEvents.end(); ++it)
		{
			EventPublisher* publisher (*it);
			
			if (publisher->DeleteAfterPublishing())
			{
				delete publisher;
				publisher = nullptr;
			}
		}
	}

	void EventQueue::Clear()
	{
		lock_guard<recursive_mutex> lock(mMutex);

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
		lock_guard<recursive_mutex> lock(mMutex);

		return mEvents.IsEmpty();
	}

	std::uint32_t EventQueue::Size() const
	{
		lock_guard<recursive_mutex> lock(mMutex);

		return mEvents.Size();
	}
}