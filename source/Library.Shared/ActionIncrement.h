#pragma once

#include "Action.h"

namespace FieaGameEngine
{
	class ActionIncrement final : public Action
	{
		RTTI_DECLARATIONS(ActionIncrement, Action)

	public:

		static const std::string KEY_TARGET;

		/** Parameterless constructor that initializes this Action's attributes.*/
		ActionIncrement();
		~ActionIncrement() = default;

		ActionIncrement(const ActionIncrement& rhs) = delete;
		ActionIncrement& operator=(const ActionIncrement& rhs) = delete;

		/** Updates the action, essentially executing any of its behavior.
		@param state The current world state.*/
		virtual void Update(class WorldState& state) override;

	protected:

		void Populate();

	};

	DeclareActionFactory(ActionIncrement)
}