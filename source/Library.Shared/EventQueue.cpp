#include "pch.h"

namespace FieaGameEngine
{
	bool EventQueue::IsEmpty() const
	{
		return mEvents.IsEmpty();
	}
}