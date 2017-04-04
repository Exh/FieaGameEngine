#pragma once

#include "Action.h"

namespace FieaGameEngine
{
	class ActionIf final : public Action
	{
		RTTI_DECLARATIONS(ActionIf, Action)

	public:

		static const std::string KEY_CONDITION;
		static const std::string KEY_THEN;
		static const std::string KEY_ELSE;

		static const std::int32_t DEFAULT_CONDITION = 0;

		ActionIf();
		~ActionIf() = default;

		ActionIf(const ActionIf& rhs) = delete;
		ActionIf& operator=(const ActionIf& rhs) = delete;

		virtual void Update(class WorldState& state) override;

	private:

		void Populate();

		std::int32_t mCondition;
	};

	DeclareActionFactory(ActionIf)
}