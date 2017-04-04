#include "pch.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Action)

	const std::string Action::KEY_NAME = "name";

	const std::string Action::DEFAULT_NAME = "Action";

	Action::Action() :
		mName(DEFAULT_NAME)
	{
		Populate();
	}
	void Action::Update(class WorldState& state)
	{
		state.mAction = this;
	}

	const std::string& Action::Name() const
	{
		return mName;
	}

	void Action::SetName(const std::string& name)
	{
		mName = name;
	}

	void Action::Populate()
	{
		Attributed::Populate();

		AddExternalAttribute(KEY_NAME, &mName, 1);
	}
}
