#include "pch.h"


namespace FieaGameEngine
{
	RTTI_DEFINITIONS(EventMessage)

	EventMessage::EventMessage() :
		mWorldState(nullptr)
	{
	
	}

	const std::string& EventMessage::GetSubtype() const
	{
		return mSubtype;
	}

	WorldState* EventMessage::GetWorldState()
	{
		return mWorldState;
	}

	const WorldState* EventMessage::GetWorldState() const
	{
		return mWorldState;
	}

	void EventMessage::SetSubtype(const std::string& subtype)
	{
		mSubtype = subtype;
	}

	void EventMessage::SetWorldState(class WorldState* worldState)
	{
		mWorldState = worldState;
	}
}