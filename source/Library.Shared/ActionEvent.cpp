#include "pch.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionEvent)

	const std::string ActionEvent::KEY_DELAY = "delay";
	const std::string ActionEvent::KEY_SUBTYPE = "subtype";

	const std::int32_t ActionEvent::DEFAULT_DELAY = 0;
	const std::string ActionEvent::DEFAULT_SUBTYPE = "null";

	ActionEvent::ActionEvent() :
		mSubtype(ActionEvent::DEFAULT_SUBTYPE),
		mDelay(ActionEvent::DEFAULT_DELAY)
	{
		Populate();
	}

	void ActionEvent::Update(WorldState& state)
	{
		Action::Update(state);

		EventMessage eventMessage;

		// Copy all auxiliary attributes to the event message
		for (auto& entry : mVector)
		{
			if (IsAuxiliaryAttribute(entry->first))
			{
				eventMessage.Append(entry->first) = entry->second;
			}
		}

		eventMessage.SetSubtype(mSubtype);
		eventMessage.SetWorldState(&state);

		Event<EventMessage>* message = new Event<EventMessage>(eventMessage, true);

		assert(state.mWorld != nullptr);
		state.mWorld->RaiseEvent(*message, state.GetGameTime(), std::chrono::milliseconds(mDelay));
	}

	void ActionEvent::Populate()
	{
		Action::Populate();

		AddExternalAttribute(KEY_DELAY, &mDelay, 1);
		AddExternalAttribute(KEY_SUBTYPE, &mSubtype, 1);
	}
}
