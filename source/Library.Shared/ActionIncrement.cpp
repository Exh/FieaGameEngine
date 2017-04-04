#include "pch.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionIncrement)

	const std::string ActionIncrement::KEY_TARGET = "target";

	ActionIncrement::ActionIncrement()
	{
		Populate();
	}

	void ActionIncrement::Update(WorldState& state)
	{
		Action::Update(state);

		Datum* datum = Search(KEY_TARGET);

		if (datum != nullptr)
		{
			Datum* target = Search(datum->GetString());

			if (target != nullptr &&
				target->Type() == DatumType::Integer)
			{
				(target->GetInteger())++;
			}
		}
	}
	
	void ActionIncrement::Populate()
	{
		Action::Populate();
	}

}
