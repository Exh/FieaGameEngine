#pragma once

#include "Scope.h"

namespace FieaGameEngine
{
	class EventMessage : public Scope
	{
		RTTI_DECLARATIONS(EventMessage, Scope)

	public:

		/** Parameterless Constructor. Defaults members. */
		EventMessage();

		virtual ~EventMessage() = default;

		/** Gets the subtype of interest.
		@return Subtype as a string. */
		const std::string& GetSubtype() const;

		/** Gets the registered WorldState that this event was delivered with.
		@return WorldState instance.*/
		class WorldState* GetWorldState();

		/** Gets the registered WorldState that this event was delivered with.
		@return WorldState instance.*/
		const class WorldState* GetWorldState() const;

		/** Sets the Subtype of this event message.
		@param subtype String for reactions to match. */
		void SetSubtype(const std::string& subtype);

		/** Sets the WorldState of this message.
		@param worldState Sets the currently processed world state instance. */
		void SetWorldState(class WorldState* worldState);

	private:

		std::string mSubtype;

		class WorldState* mWorldState;
	};
}

