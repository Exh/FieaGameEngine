#pragma once

#include "Factory.h"

namespace FieaGameEngine
{
	class Action : public Attributed
	{
		RTTI_DECLARATIONS(Action, Attributed)

	public:

		static const std::string KEY_NAME;

		static const std::string DEFAULT_NAME;

		Action();

		virtual ~Action() = default;

		Action(const Action& rhs) = delete;
		Action& operator=(const Action& rhs) = delete;

		virtual void Update(class WorldState& state) = 0;

		const std::string& Name() const;

		void SetName(const std::string& name);

	protected:

		void Populate();

		std::string mName;

	};

	#define DeclareActionFactory(ConcreteAction) ConcreteFactory(Action, ConcreteAction)
}