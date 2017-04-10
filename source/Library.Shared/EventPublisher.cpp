#include "pch.h"

using namespace std::chrono;

namespace FieaGameEngine
{
	EventPublisher::EventPublisher(Vector<EventSubscriber>& subscribers, bool destroyEvent) :
		mSubscribers(&subscribers),
		mDestroyEvent(destroyEvent),
		mTimeEnqueued(),
		mDelay()
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
		//return duration_cast<milliseconds>(mTimeEnqueued) > milliseconds(0);
		return (mTimeEnqueued + mDelay) > (currentTime);
	}

	void EventPublisher::Deliver()
	{
		if (mSubscribers != nullptr)
		{
			for (EventSubscriber& subscriber : *mSubscribers)
			{
				subscriber.Notify(*this);
			}
		}
	}

	bool EventPublisher::DeleteAfterPublishing() const
	{
		return mDestroyEvent;
	}

	EventPublisher::EventPublisher(EventPublisher&& rhs) :
		mSubscribers(rhs.mSubscribers),
		mDestroyEvent(rhs.mDestroyEvent),
		mTimeEnqueued(rhs.mTimeEnqueued),
		mDelay(rhs.mDelay)
	{
		rhs.mSubscribers = nullptr;
		mDestroyEvent = false;
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
			rhs.mDestroyEvent = false;
		}

		return *this;
	}
}