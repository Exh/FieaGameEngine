#include "pch.h"

using namespace std::chrono;
using namespace std;

namespace FieaGameEngine
{

	RTTI_DEFINITIONS(EventPublisher)

	EventPublisher::EventPublisher(Vector<EventSubscriber*>& subscribers, std::recursive_mutex& classMutex, bool destroyEvent) :
		mSubscribers(&subscribers),
		mMutex(&classMutex),
		mDestroyEvent(destroyEvent),
		mTimeEnqueued(),
		mDelay(0)
	{
	
	}

	EventPublisher::~EventPublisher()
	{
	
	}

	void EventPublisher::SetTime(std::chrono::high_resolution_clock::time_point currentTime,
								 std::chrono::milliseconds delay)
	{
		mTimeEnqueued = currentTime;
		mDelay = delay;
	}

	high_resolution_clock::time_point EventPublisher::TimeEnqueued() const
	{
		return mTimeEnqueued;
	}

	std::chrono::milliseconds EventPublisher::Delay() const
	{
		return mDelay;
	}

	bool EventPublisher::IsExpired(high_resolution_clock::time_point currentTime) const
	{
		return (mTimeEnqueued + mDelay) <= (currentTime);
	}

	void EventPublisher::Deliver()
	{
		vector<future<void>> futures;

		{
			lock_guard<recursive_mutex> lock(*mMutex);

			if (mSubscribers != nullptr)
			{
				return;
			}

			for (EventSubscriber* subscriber : *mSubscribers)
			{
				assert(subscriber != nullptr);
				const EventPublisher& pub = *this;
				//subscriber->Notify(const_cast<const EventPublisher&>(pub));
				futures.emplace_back(async(launch::async, [subscriber, &pub] {subscriber->Notify(const_cast<const EventPublisher&>(pub)); }));
			}
		}

		for (future<void>& future : futures)
		{
			future.get();
		}
	}

	bool EventPublisher::DeleteAfterPublishing() const
	{
		return mDestroyEvent;
	}

	EventPublisher::EventPublisher(EventPublisher&& rhs) :
		mSubscribers(rhs.mSubscribers),
		mMutex(rhs.mMutex),
		mDestroyEvent(rhs.mDestroyEvent),
		mTimeEnqueued(rhs.mTimeEnqueued),
		mDelay(rhs.mDelay)
	{
		rhs.mSubscribers = nullptr;
		rhs.mMutex = nullptr;
		rhs.mDestroyEvent = false;
	}

	EventPublisher& EventPublisher::operator=(EventPublisher&& rhs)
	{
		if (this != &rhs)
		{
			mSubscribers = rhs.mSubscribers;
			mDestroyEvent = rhs.mDestroyEvent;
			mTimeEnqueued = rhs.mTimeEnqueued;
			mDelay = rhs.mDelay;

			rhs.mSubscribers = nullptr;
			rhs.mMutex = nullptr;
			rhs.mDestroyEvent = false;
		}

		return *this;
	}
}