#pragma once

#include "Action.h"

namespace FieaGameEngine
{
	class ActionDestroyAction final : public Action
	{
		RTTI_DECLARATIONS(ActionDestroyAction, Action)

	public:

		static const std::string KEY_TARGET;
		static const std::string KEY_ACTIONS;

		ActionDestroyAction();

		virtual void Update(class WorldState& state) override;

	private:

		void Populate();

	};

	DeclareActionFactory(ActionDestroyAction)
}
