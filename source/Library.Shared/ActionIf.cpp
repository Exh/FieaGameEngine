#include "pch.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionIf)

	const std::string ActionIf::KEY_CONDITION = "condition";
	const std::string ActionIf::KEY_THEN = "then";
	const std::string ActionIf::KEY_ELSE = "else";

	const std::int32_t DEFAULT_CONDITION = 0;

	ActionIf::ActionIf()
	{
		Populate();
	}

	void ActionIf::Update(WorldState& state)
	{
		Action::Update(state);

		Datum* thenAction = Find(KEY_THEN);
		Datum* elseAction = Find(KEY_ELSE);
		std::int32_t condition = (*this)[KEY_CONDITION].GetInteger();

		if (condition != 0 &&
			thenAction != 0)
		{
			Scope* then = thenAction->GetScope();
			assert(then->Is(Action::TypeIdClass()));
			static_cast<Action*>(then)->Update(state);
			
		}
		else if (elseAction != 0)
		{
			Scope* els = elseAction->GetScope();
			assert(els->Is(Action::TypeIdClass()));
			static_cast<Action*>(els)->Update(state);
		}
	}

	void ActionIf::Populate()
	{
		Action::Populate();
	}
}
