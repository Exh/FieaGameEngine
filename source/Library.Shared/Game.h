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

		/** Parameterless constructor that initializes data members.*/
		Game();

		/** Destructor. Destroys the current world if one exists. */
		~Game();

		/** Initializes the game clock and assigns the GameTime object to
		the WorldState member object. */
		void Initialize();

		/** Loads a world from XML.
		@throw exception If the file could not be read
		@throw exception If the file contains no world.
		the WorldState member object. */
		void LoadWorld(const char* filename);

		/** Updates the world, thus updating all entities.*/
		void Update();

		/** Renders all components that can be. */
		void Render();

		/** Shutdowns helpers such as renderer.*/
		void Shutdown();

	private:

		GameTime mGameTime;
		GameClock mGameClock;
		WorldState mWorldState;
		World* mWorld;
	};
}