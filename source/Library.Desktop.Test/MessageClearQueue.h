#pragma once

namespace FieaGameEngine
{
	struct MessageClearQueue
	{
		class EventQueue* mEventQueue;

		MessageClearQueue() :
			mEventQueue(nullptr)
		{

		}
	};
}