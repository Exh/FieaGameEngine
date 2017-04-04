#include "pch.h"

namespace FieaGameEngine
{

	RTTI_DEFINITIONS(ActionDestroyAction)

	const std::string ActionDestroyAction::KEY_TARGET = "target";
	const std::string ActionDestroyAction::KEY_ACTIONS = "actions";

	ActionDestroyAction::ActionDestroyAction()
	{
		Populate();
	}

	void ActionDestroyAction::Update(class WorldState& state)
	{
		Action::Update(state);

		Datum* targetDatum = Find(KEY_TARGET);

		if (targetDatum == nullptr)
		{
			// TODO: LOG WARNING target could not be found.
			return;
		}

		if (targetDatum->Type() != DatumType::String ||
			targetDatum->Size() == 0)
		{
			// TODO: LOG WARNING target not set.
			return;
		}

		const std::string& targetName = targetDatum->GetString();

		Scope* parent = GetParent();

		while (parent != nullptr)
		{
			Datum* actionsDatum = parent->Find(KEY_ACTIONS);

			if (actionsDatum != nullptr)
			{
				for (std::uint32_t i = 0; i < actionsDatum->Size(); i++)
				{
					Scope& scope = (*actionsDatum)[i];
					assert(scope.Is(Action::TypeIdClass()));
					
					if (scope[Action::KEY_NAME] == targetName)
					{
						state.mWorld->DestroyAction(static_cast<Action&>(scope));
						return;
					}
				}
			}

			parent = parent->GetParent();
		}

		// TODO: LOG WARNING Target action not found.
	}

	void ActionDestroyAction::Populate()
	{
		Action::Populate();
	}
}