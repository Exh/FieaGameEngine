#pragma once

#include "GameTime.h"
#include "GameClock.h"
#include "World.h"
#include "WorldState.h"

namespace FieaGameEngine
{
	class Game
	{

	public:

		Game();
		~Game();

		void Initialize();

		void LoadWorld(const char* filename);

		void Update();

		void Render();

		void Shutdown();

	private:

		GameTime mGameTime;
		GameClock mGameClock;
		WorldState mWorldState;
		World* mWorld;
	};
}