#pragma once

#include "Action.h"

namespace FieaGameEngine
{
	class ActionCreateAction final : public Action
	{
		RTTI_DECLARATIONS(ActionCreateAction, Action)

	public:

		static const std::string KEY_PROTOTYPE_CLASS;
		static const std::string KEY_INSTANCE_NAME;
		static const std::string KEY_ACTIONS;

		static const std::string DEFAULT_PROTOTYPE_CLASS;
		static const std::string DEFAULT_INSTANCE_NAME;

		ActionCreateAction();

		virtual void Update(class WorldState& state) override;

	private:

		void Populate();

	};

	DeclareActionFactory(ActionCreateAction)
}
