#pragma once

#include "Reaction.h"
#include "Factory.h"
#include "World.h"
#include "Action.h"

namespace FieaGameEngine
{
	class ReactionAttributed : public Reaction
	{
		RTTI_DECLARATIONS(ReactionAttributed, Reaction)

	public:

		static const std::string KEY_SUBTYPE;

		static const std::string DEFAULT_SUBTYPE;

		/** Parameterless constructor. Establishes default attributes. */
		ReactionAttributed();

		virtual ~ReactionAttributed() = default;

		/** Notify interface implementation to handle EventMessage events.
		@param publisher The event being delivered. */
		virtual void Notify(const class EventPublisher& publisher) override;

		/** Sets this ReactionAttributed's subtype so that it only handles
		events of that subtype.
		@param subtype Name of subtype to handle */
		void SetSubtype(const std::string& subtype);

	protected:

		void Populate();

	protected:

		std::string mSubtype;
	};

	DeclareActionFactory(ReactionAttributed)
}

