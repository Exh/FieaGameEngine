#pragma once

#include "ActionList.h"
#include "EventSubscriber.h"
#include "RTTI.h"

namespace FieaGameEngine
{
	class Reaction : public ActionList, public EventSubscriber
	{
		RTTI_DECLARATIONS(Reaction, ActionList)

	public:

		virtual ~Reaction() = default;
	};
}
