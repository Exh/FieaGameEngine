#pragma once

namespace FieaGameEngine
{
	class WorldState
	{

	public:

		/** Default constructor that nulls out pointers.*/
		WorldState();
		~WorldState() = default;

		// Shallow copying allowed.
		WorldState(const WorldState& rhs) = default;
		WorldState& operator=(const WorldState& rhs) = default;

		/** Returns the currently assigned gametime object.
		@return GameTime object. */
		class GameTime& GetGameTime();

		/** Returns the currently assigned gametime object.
		@return GameTime object. */
		const class GameTime& GetGameTime() const;

		
		/** Given a GameTime reference. Set this GameTime object.
		@param gameTime The new GameTime object. */
		void SetGameTime(class GameTime& gameTime);

		/** Returns whether a GameTime object has been assigned to 
		this WorldState instance yet.
		@return true if one has been set. false otherwise.*/
		bool IsGameTimeSet() const;

		/** Returns the time in seconds since last frame.
		@return Time in seconds since last frame. */
		float DeltaTime() const;

	public:

		class World* mWorld;

		class Sector* mSector;

		class Entity* mEntity;

		class Action* mAction;

		// TODO: class Action* mAction;

	private:

		class GameTime* mGameTime;

	};
}
