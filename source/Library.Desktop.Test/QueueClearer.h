#pragma once

#include "EventSubscriber.h"
#include "MessageClearQueue.h"
#include "Event.h"
#include "EventPublisher.h"

namespace FieaGameEngine
{
	class QueueClearer : public EventSubscriber
	{
	public:

		virtual void Notify(const class EventPublisher& publisher);

	};
}