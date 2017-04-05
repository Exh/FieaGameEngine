#pragma once

#include "Attributed.h"
#include "Factory.h"

namespace FieaGameEngine
{
	class Entity : public Attributed
	{

		RTTI_DECLARATIONS(Entity, Attributed)

	public:

		static const std::string KEY_NAME;
		static const std::string KEY_ACTIONS;

		static const std::string DEFAULT_NAME;

	public:

		/** Default constructor. Sets up initial attributes. */
		Entity();

		/** Default constructor. Sets up initial attributes. */
		virtual ~Entity() = default;

		Entity(const Entity& rhs) = default;
		Entity& operator=(const Entity& rhs) = default;

		/** Returns the name attribute of this Entity.
		@return Name */
		const std::string& Name() const;

		/** Given a new string, sets this Entity's name.
		@param name New name.*/
		void SetName(const std::string& name);

		/** Returns parent sector that owns this Entity.
		@throw exception If the entity has no sector parent.
		@return Pointer to parent sector. */
		class Sector* GetSector();
		
		/** Returns parent sector that owns this Entity.
		@throw exception If the entity has no sector parent.
		@return Pointer to parent sector. */
		const class Sector* GetSector() const;

		/** Returns parent sector that owns this Entity.
		@param World state reference to be used by entity. */
		virtual void Update(class WorldState& state);

		/** Returns datum containing all actions contained by this entity.
		@return Datum containing array of Action pointers. */
		Datum& Actions();

		/** Returns datum containing all actions contained by this entity.
		@return Datum containing array of Action pointers. */
		const Datum& Actions() const;

		/** Creates an entity from a class name string using Factory<Action>.
		@param className The name of the class to instantiate. 
		@param instanceName The name of the action.
		@return Pointer to the newly allocated action. Caller is responsible
			for deleting the data.*/
		Action* CreateAction(const std::string& className, const std::string& instanceName);

	protected:

		std::string mName;

		Datum* mActions;

	private:

		void Populate();

	};

	ConcreteFactory(Entity, Entity)

#define DeclareEntityFactory(ConcreteEntity) ConcreteFactory(Entity, ConcreteEntity)
}

