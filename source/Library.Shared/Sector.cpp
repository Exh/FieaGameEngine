#include "Sector.h"
#include "Entity.h"
#include "World.h"
#include "WorldState.h"
#include "Factory.h"

namespace FieaGameEngine
{
	
	RTTI_DEFINITIONS(Sector)

	const std::string Sector::KEY_NAME = "Name";
	const std::string Sector::KEY_ENTITIES = "Entities";

	const std::string Sector::DEFAULT_NAME = "Sector";

	Sector::Sector() :
		mName(NAME_DEFAULT),
		mEntities(nullptr)
	{
		Populate();

		mEntities = Find(KEY_ENTITIES);
		assert(mEntities != nullptr);
	}

	void Sector::Populate()
	{
		Attributed::Populate();

		AddExternalAttribute(KEY_NAME, &mName, 1);
		AddEmptyNestedScopeAttribute(KEY_ENTITIES);
	}

	const std::string& Sector::Name() const
	{
		return mName;
	}

	void Sector::SetName(const std::string& name)
	{
		mName = name;
	}

	Datum& Sector::Entities()
	{
		// Entities datum should always be set on Populate().
		assert(mEntities != nullptr);

		return *mEntities;
	}

	const Datum& Sector::Entities() const
	{
		// Entities datum should always be set on Populate().
		assert(mEntities != nullptr);

		return *mEntities;
	}

	Entity* Sector::CreateEntity(const std::string& className)
	{
		Entity* entity = Factory<Entity>::Create(className);

		if (entity)
		{
			throw std::exception("Unknown Entity Class Name received.");
		}

		assert(mEntities != nullptr);
		mEntities->PushBack(entity);

		return entity;
	}

	World* Sector::GetWorld()
	{
		assert(mParent != nullptr);
		assert(mParent->Is(World::TypeIdClass()));

		return static_cast<World*>(mParent);
	}

	const World* Sector::GetWorld() const
	{
		assert(mParent != nullptr);
		assert(mParent->Is(World::TypeIdClass()));

		return static_cast<World*>(mParent);
	}

	void Sector::Update(WorldState& state)
	{
		assert(mEntities != nullptr);

		if (mEntities->Size() > 0)
		{
			Scope** entities = &(mEntities->GetScope(0));

			for (std::uint32_t i = 0; i < mEntities->Size(); i++)
			{
				assert(entities[i] != nullptr);
				assert(entities[i]->Is(Entity::TypeIdClass()));
				static_cast<Entity*>(entities[i])->Update(state);
			}
		}
	}
}
