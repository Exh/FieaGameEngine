#pragma once

#include "SList.h"
#include <chrono>

namespace FieaGameEngine
{
	class EventQueue
	{
	public:

		EventQueue() = default;

		/** Enqueues a given event into the event queue.
		@param publisher Event to add to queue.
		@param gameTime the current game time.
		@param delay Time in milliseconds to delay sending the event. */
		void Enqueue(class EventPublisher& publisher,
					 class GameTime& gameTime,
					 std::chrono::milliseconds delay = std::chrono::milliseconds(0));

		/** Immediately sends an event.
		@param publisher The event to send. */
		void Send(class EventPublisher& publisher);

		/** Sends all events that have expired in the queue.
		@param gameTime Reference to the current game time object. */
		void Update(class GameTime& gameTime);

		/** Clears all events in the queue. Does not deliver these events.
		If an event is marked to be deleted after it is processed, then this 
		method will delete it too. */
		void Clear();

		/** Returns bool indicating whether the queue has any events waiting
		to be delivered.
		@return True if queue is empty.*/
		bool IsEmpty() const;

		/** Gets the size of the event queue. (The number of events waiting
		to be delivered).
		@return Size of queue. */
		std::uint32_t Size() const;

	private:

		SList<EventPublisher*> mEvents;

	};
}