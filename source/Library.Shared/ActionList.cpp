#include "pch.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionList)

	const std::string ActionList::KEY_ACTIONS = "actions";

	ActionList::ActionList()
	{
		Populate();
	}

	void ActionList::Populate()
	{
		Action::Populate();

		AddEmptyNestedScopeAttribute(KEY_ACTIONS);
	}

	void ActionList::Update(WorldState& state)
	{
		Action::Update(state);

		Datum* actionDatum = Find(KEY_ACTIONS);
		assert(actionDatum != nullptr);

		Scope** actions = &(actionDatum->GetScope(0));

		for (std::uint32_t i = 0; i < actionDatum->Size(); i++)
		{
			assert(actions[i] != nullptr);
			assert(actions[i]->Is(Action::TypeIdClass()));
			static_cast<Action*>(actions[i])->Update(state);
		}
	}

	Action* ActionList::CreateAction(const std::string& className, const std::string& instanceName)
	{
		Action* newAction = Factory<Action>::Create(className);
		newAction->SetName(instanceName);
		Adopt(*newAction, KEY_ACTIONS);

		return newAction;
	}
}