#pragma once

namespace FieaGameEngine
{
	struct MessageClearQueue
	{
		class World* mWorld;

		MessageClearQueue() :
			mWorld(nullptr)
		{

		}
	};
}