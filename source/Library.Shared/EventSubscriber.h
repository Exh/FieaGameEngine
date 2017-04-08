#pragma once

namespace FieaGameEngine
{
	class EventSubscriber
	{
		virtual void Notify(class EventPublisher& publisher) = 0;
	};
}