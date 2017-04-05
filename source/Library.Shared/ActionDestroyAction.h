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

		/** Parameterless constructor that initializes this Action's attributes.*/
		ActionDestroyAction();

		/** Updates the action, essentially executing any of its behavior.
		@param state The current world state.*/
		virtual void Update(class WorldState& state) override;

	private:

		void Populate();

	};

	DeclareActionFactory(ActionDestroyAction)
}
