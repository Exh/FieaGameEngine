#pragma once

#include "Attributed.h"

namespace FieaGameEngine
{

	class Sector final : public Attributed
	{

		RTTI_DECLARATIONS(Sector, Attributed)

	public:

		static const std::string KEY_NAME;
		static const std::string KEY_ENTITIES;

		static const std::string DEFAULT_NAME;

	public:

		/** Default constructor. Sets up initial attributes. */
		Sector();
		
		/** Default constructor. Sets up initial attributes. */
		~Sector() = default;

		Sector(const Sector& rhs) = delete;
		Sector& operator=(const Sector& rhs) = delete;

		/** Returns the name attribute of this Sector.
		@return Name */
		const std::string& Name() const;

		/** Given a new string, sets this Sector's name.
		@param name New name.*/
		void SetName(const std::string& name);

		/** Returns the datum that holds child entities.
		@return Datum containing all entities owned by this Sector. */
		Datum& Entities();

		/** Returns the datum that holds child entities.
		@return Datum containing all entities owned by this Sector. */
		const Datum& Entities() const;

		/** Creates an entity based on a class string, and then adopts
		it into this Sector.
		@throw exception If an unknown className is received.
		@param className The name of the class to create.
		@return The new entity that was created. */
		class Entity* CreateEntity(const std::string& className);

		/** Returns parent world that owns this sector.
		@throw exception If the sector has no world parent.
		@return Pointer to parent world. */
		class World* GetWorld();
		
		/** Returns parent world that owns this sector.
		@throw exception If the sector has no world parent.
		@return Pointer to parent world. */
		const class World* GetWorld() const;

		
		/** Updates all entities contained by this sector.
		@param state World state for sector to use in update. */
		void Update(class WorldState& state);

	private:

		void Populate();

	private:

		std::string mName;

		Datum* mEntities;

	};
}
