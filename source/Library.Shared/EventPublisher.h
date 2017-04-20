#pragma once

#include "RTTI.h"
#include "EventSubscriber.h"
#include "Vector.h"
#include <chrono>
#include <mutex>

namespace FieaGameEngine
{
	class EventPublisher : public RTTI
	{
		RTTI_DECLARATIONS(EventPublisher, RTTI)

	public:

		
		/** Default constructor that takes a list of subscribers and a 
		bool that lets the event queue know whether or not to delete it after processing.
		@param subscribers Reference to a vector of subscribers from the derived class.
		@param destroyElement Flag to let EventQueue know whether to delete it or not. */
		EventPublisher(Vector<EventSubscriber*>& subscribers, std::recursive_mutex& classMutex, bool destroyEvent);

		virtual ~EventPublisher() = 0;

		
		/** Set this event's enqueue time and delay.
		@param currentTime time that this event was enqueued.
		@param delay Number of milliseconds to delay from enqueue time. */
		void SetTime(std::chrono::high_resolution_clock::time_point currentTime,
					 std::chrono::milliseconds delay);

		/** Get time enqueued. Time enqueued modified from SetTime().
		@return Time enqueued.*/
		std::chrono::high_resolution_clock::time_point TimeEnqueued() const;

		/** Get the delay in milliseconds that this event has been issued.
		@return Number of seconds that this event will delay it's processing from 
			it's time enqueued.*/
		std::chrono::milliseconds Delay() const;
	
		/** Given a current time as a GameTime object, returns a bool letting the
		caller know if this event should be processed. Primarily used by the EventQueue class. 
		@param currentTime Current time as a chrono time_point.
		@return bool True if the event should be processed. */
		bool IsExpired(std::chrono::high_resolution_clock::time_point currentTime) const;

		/** Delivers this message to all subscribers. */
		void Deliver();

		/** Returns a bool letting the caller know if this event should be deleted after
		it has been processed. Primarily used by EventQueue. 
		@return bool True if this event should be deleted after processing. */
		bool DeleteAfterPublishing() const;

		EventPublisher(const EventPublisher& rhs) = default;
		EventPublisher& operator=(const EventPublisher& rhs) = default;

		/** Move constructor.
		@param rhs Event to move from.*/
		EventPublisher(EventPublisher&& rhs);

		/** Move constructor.
		@param rhs Event to move from.
		@return Reference to this event. */
		EventPublisher& operator=(EventPublisher&& rhs);

	protected:

		Vector<EventSubscriber*>* mSubscribers;

		mutable std::recursive_mutex* mMutex;

		bool mDestroyEvent;

		std::chrono::high_resolution_clock::time_point mTimeEnqueued;

		std::chrono::milliseconds mDelay;
	};
}
