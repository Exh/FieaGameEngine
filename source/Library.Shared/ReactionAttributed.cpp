#include "pch.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ReactionAttributed)

	const std::string ReactionAttributed::KEY_SUBTYPE = "subtype";

	const std::string ReactionAttributed::DEFAULT_SUBTYPE = "null";

	ReactionAttributed::ReactionAttributed()
	{
		Populate();

		Event<EventMessage>::Subscribe(*this);
	}

	void ReactionAttributed::Notify(const EventPublisher& publisher)
	{
		Event<EventMessage>* genericMessage = publisher.As<Event<EventMessage>>();

		if (genericMessage != nullptr)
		{
			const EventMessage& message = genericMessage->Message();

			if (message.GetSubtype() == mSubtype)
			{
				CopyScopeData(message);

				if (message.GetWorldState() != nullptr)
				{
					WorldState worldState = *message.GetWorldState();
					Update(worldState);
				}
			}
		}
	}

	void ReactionAttributed::SetSubtype(const std::string& subtype)
	{
		mSubtype = subtype;
	}

	void ReactionAttributed::Populate()
	{
		ActionList::Populate();

		AddExternalAttribute(KEY_SUBTYPE, &mSubtype, 1);
	}
}