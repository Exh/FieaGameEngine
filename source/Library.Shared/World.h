#pragma once

#include "Attributed.h"
#include "Vector.h"
#include "EventQueue.h"

namespace FieaGameEngine
{
	class World final : public Attributed
	{

		RTTI_DECLARATIONS(World, Attributed)

	public:

		static const std::string KEY_NAME;
		static const std::string KEY_SECTORS;

		static const std::string DEFAULT_NAME;

	public:

		/** Default constructor. Sets up initial attributes. */
		World();

		~World() = default;

		World(const World& rhs) = delete;
		World& operator=(const World& rhs) = delete;

		/** Returns the name attribute of this World.
		@return Name */
		const std::string& Name() const;

		/** Given a new string, sets this World's name.
		@param name New name.*/
		void SetName(const std::string& name);

		/** Returns the datum that holds child sectors.
		@return Datum containing all sectores owned by this Sector. */
		Datum& Sectors();

		/** Returns the datum that holds child sectors.
		@return Datum containing all sectores owned by this Sector. */
		const Datum& Sectors() const;

		/** Creates a sector, and then adopts it into this World.
		@return The new sector that was created. */
		class Sector* CreateSector();

		/** Updates all sectors contained by this world.
		@param state World state for world to use in update. */
		void Update(class WorldState& state);

		void DestroyAction(class Action& action);

		void RaiseEvent(EventPublisher& publisher,
						GameTime& gameTime,
						std::chrono::milliseconds delay);

	private:

		void Populate();

	private:

		void DestroyQueuedActions();

		std::string mName;

		Vector<class Action*> mActionDestroyQueue;

		Datum* mSectors;

		EventQueue	mEventQueue;
	};
}
