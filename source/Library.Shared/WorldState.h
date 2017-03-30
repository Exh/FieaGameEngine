#pragma once

namespace FieaGameEngine
{
	class WorldState
	{

	public:

		class GameTime& GetGameTime();
		
		const class GameTime& GetGameTime() const;

		void SetGameTime(class GameTime& gameTime);

		float DeltaTime() const;

	public:

		class World* mWorld;

		class Sector* mSector;

		class Entity* mEntity;

		// TODO: class Action* mAction;

	private:

		class GameTime* mGameTime;

	};
}
