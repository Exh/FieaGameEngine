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

		/** Default constructor which populates this class's attributes. */
		Action();

		virtual ~Action() = default;

		Action(const Action& rhs) = delete;
		Action& operator=(const Action& rhs) = delete;

		/** Updates the action, essentially executing any of its behavior.
		@param state The current world state.*/
		virtual void Update(class WorldState& state) = 0;

		/** Gets this action's name.
		@return Name of the action.*/
		const std::string& Name() const;

		/** Sets this action's name attribute.
		@param name New name of the action.*/
		void SetName(const std::string& name);

	protected:

		void Populate();

		std::string mName;

	};

	#define DeclareActionFactory(ConcreteAction) ConcreteFactory(Action, ConcreteAction)
}