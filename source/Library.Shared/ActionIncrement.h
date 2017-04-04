#pragma once

#include "Action.h"

namespace FieaGameEngine
{
	class ActionIncrement final : public Action
	{
		RTTI_DECLARATIONS(ActionIncrement, Action)

	public:

		static const std::string KEY_TARGET;

		ActionIncrement();
		~ActionIncrement() = default;

		ActionIncrement(const ActionIncrement& rhs) = delete;
		ActionIncrement& operator=(const ActionIncrement& rhs) = delete;

		virtual void Update(class WorldState& state) override;

	protected:

		void Populate();

	};
}