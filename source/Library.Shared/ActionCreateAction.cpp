#include "pch.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionCreateAction)

	const std::string ActionCreateAction::KEY_PROTOTYPE_CLASS = "prototypeClass";
	const std::string ActionCreateAction::KEY_INSTANCE_NAME = "instanceName";
	const std::string ActionCreateAction::KEY_ACTIONS = "actions";

	const std::string ActionCreateAction::DEFAULT_PROTOTYPE_CLASS = "";
	const std::string ActionCreateAction::DEFAULT_INSTANCE_NAME = "Action";

	ActionCreateAction::ActionCreateAction()
	{
		Populate();
	}

	void ActionCreateAction::Update(class WorldState& state)
	{
		Action::Update(state);

		std::string& prototypeClass = (*this)[KEY_PROTOTYPE_CLASS].GetString();
		std::string& instanceName = (*this)[KEY_INSTANCE_NAME].GetString();

		Scope* parent = GetParent();

		if (parent != nullptr)
		{
			Action* newAction = Factory<Action>::Create(prototypeClass);
			newAction->SetName(instanceName);
			parent->Adopt(*newAction, KEY_ACTIONS);
		}
	}

	void ActionCreateAction::Populate()
	{
		Action::Populate();

		AddInternalAttribute(KEY_PROTOTYPE_CLASS, DEFAULT_PROTOTYPE_CLASS);
		AddInternalAttribute(KEY_INSTANCE_NAME, DEFAULT_INSTANCE_NAME);
	}
}