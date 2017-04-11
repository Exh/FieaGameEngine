#pragma once

namespace FieaGameEngine
{
	class EventSubscriber
	{
	public:

		/** Notifies this subscriber of an event that has occurred.
		To get the contents of the message, caller should use RTTI's
		interface for determining the type of message and handle it accordingly.
		An EventSubscriber will only be notified of an event if it has subscribed
		to that Event class with Event<T>::Subscribe().
		@param publisher The event that was raised. */
		virtual void Notify(const class EventPublisher& publisher) = 0;

	};
}