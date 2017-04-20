#include "pch.h"

namespace FieaGameEngine
{
	void QueueClearer::Notify(const class EventPublisher& publisher)
	{
		Event<MessageClearQueue>* clearEvent = publisher.As<Event<MessageClearQueue>>();

		if (clearEvent != nullptr)
		{
			const MessageClearQueue& message = clearEvent->Message();

			if (message.mWorld != nullptr)
			{
				message.mWorld->GetEventQueue().Clear();
			}
		}
	}
}