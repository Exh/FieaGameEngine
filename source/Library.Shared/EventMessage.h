#pragma once

#include "Scope.h"

namespace FieaGameEngine
{
	class EventMessage : public Scope
	{
		RTTI_DECLARATIONS(EventMessage, Scope)

	public:

		EventMessage();
		virtual ~EventMessage() = default;

		const std::string& GetSubtype() const;

		class WorldState* GetWorldState();

		const class WorldState* GetWorldState() const;

		void SetSubtype(const std::string& subtype);

		void SetWorldState(class WorldState* worldState);

	private:

		std::string mSubtype;

		class WorldState* mWorldState;
	};
}

