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

		ReactionAttributed();
		virtual ~ReactionAttributed() = default;

		virtual void Notify(const class EventPublisher& publisher) override;

		void SetSubtype(const std::string& subtype);

	protected:

		void Populate();

	protected:

		std::string mSubtype;
	};

	DeclareActionFactory(ReactionAttributed)
}

