#include "pch.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(World)

	const std::string World::KEY_NAME = "name";
	const std::string World::KEY_SECTORS = "sectors";

	const std::string World::DEFAULT_NAME = "World";

	World::World() :
		mName(DEFAULT_NAME),
		mSectors(nullptr)
	{
		Populate();

		mSectors = Find(KEY_SECTORS);
		assert(mSectors != nullptr);
	}

	void World::Populate()
	{
		Attributed::Populate();

		AddExternalAttribute(KEY_NAME, &mName, 1);
		AddEmptyNestedScopeAttribute(KEY_SECTORS);
	}

	const std::string& World::Name() const
	{
		return mName;
	}

	void World::SetName(const std::string& name)
	{
		mName = name;
	}

	Datum& World::Sectors()
	{
		// Sectors should never be null. Assigned on construction.
		assert(mSectors != nullptr);

		return *mSectors;
	}

	const Datum& World::Sectors() const
	{
		// Sectors should never be null. Assigned on construction.
		assert(mSectors != nullptr);

		return *mSectors;
	}

	Sector* World::CreateSector()
	{
		Sector* sector = new Sector();

		Adopt(*sector, World::KEY_SECTORS);

		return sector;
	}

	void World::Update(class WorldState& state)
	{
		assert(mSectors != nullptr);

		if (mSectors->Size() > 0)
		{
			Scope** sectors = &(mSectors->GetScope(0));

			for (std::uint32_t i = 0; i < mSectors->Size(); i++)
			{
				assert(sectors[i] != nullptr);
				assert(sectors[i]->Is(Sector::TypeIdClass()));
				state.mSector = static_cast<Sector*>(sectors[i]);
				static_cast<Sector*>(sectors[i])->Update(state);
			}

			state.mSector = nullptr;
		}

		DestroyQueuedActions();
	}

	void World::DestroyQueuedActions()
	{
		for (Action*& action : mActionDestroyQueue)
		{
			delete action;
			action = nullptr;
		}

		mActionDestroyQueue.Clear();
	}

	void World::DestroyAction(class Action& action)
	{
		mActionDestroyQueue.PushBack(&action);
	}

	void World::RaiseEvent(EventPublisher& publisher,
						   GameTime& gameTime,
						   std::chrono::milliseconds delay)
	{
		mEventQueue.Enqueue(publisher, gameTime, delay);
	}

	EventQueue& World::GetEventQueue()
	{
		return mEventQueue;
	}

	const EventQueue& World::GetEventQueue() const
	{
		return mEventQueue;
	}
}
