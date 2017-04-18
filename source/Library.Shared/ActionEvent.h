#pragma once

#include "Action.h"
#include "RTTI.h"

namespace FieaGameEngine
{
	class ActionEvent : public Action
	{
		RTTI_DECLARATIONS(ActionEvent, Action)

	public:

		static const std::string KEY_DELAY;
		static const std::string KEY_SUBTYPE;

		static const std::int32_t DEFAULT_DELAY;
		static const std::string DEFAULT_SUBTYPE;

	public:

		/** Parameterless Constructor. Defaults prescribed attributes.*/
		ActionEvent();

		virtual ~ActionEvent() = default;

		/** Override of Action's Update. This will create an event of type 
		EventMessage and enqueue it to be delivered with the set "delay" attribute. */
		virtual void Update(class WorldState& state) override;

	protected:

		void Populate();

	protected:

		std::string mSubtype;

		std::int32_t mDelay;

	};

	DeclareActionFactory(ActionEvent)
}
