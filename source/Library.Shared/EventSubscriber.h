#pragma once

namespace FieaGameEngine
{
	class EventSubscriber
	{
	public:

		virtual void Notify(class EventPublisher& publisher) = 0;

	};
}