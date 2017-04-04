#include "pch.h"

namespace FieaGameEngine
{

	RTTI_DEFINITIONS(ActionCreateAction)

	const std::string KEY_PROTOTYPE_CLASS = "prototypeClass";
	const std::string KEY_INSTANCE_NAME = "instanceName";
	const std::string KEY_ACTIONS = "actions";

	const std::string DEFAULT_PROTOTYPE_CLASS = "Action";
	const std::string DEFAULT_INSTANCE_NAME = "Action";

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
			Adopt(*newAction, KEY_ACTIONS);
		}
	}

	void ActionCreateAction::Populate()
	{
		Action::Populate();

		AddInternalAttribute(KEY_PROTOTYPE_CLASS, DEFAULT_PROTOTYPE_CLASS);
		AddInternalAttribute(KEY_INSTANCE_NAME, DEFAULT_INSTANCE_NAME);
	}
}