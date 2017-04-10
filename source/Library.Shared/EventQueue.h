#pragma once

#include "SList.h"

namespace FieaGameEngine
{
	class EventQueue
	{
	public:

		EventQueue() = default;

		void Enqueue(class EventPublisher& publisher,
					 class GameTime& gameTime,
					 float delay = 0.0f);

		void Send(class EventPublisher& publisher);

		void Update(class GameTime& gameTime);

		void Clear();

		bool IsEmpty() const;

		std::uint32_t Size() const;

	private:

		SList<EventPublisher*> mEvents;

	};
}