#pragma once

namespace FieaGameEngine
{
	class EventSubscriber
	{
	public:

		virtual void Notify(const class EventPublisher& publisher) = 0;

	};
}