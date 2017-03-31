#include "pch.h"

namespace FieaGameEngine
{

	WorldState::WorldState() :
		mWorld(nullptr),
		mSector(nullptr),
		mEntity(nullptr),
		mGameTime(nullptr)
	{
	
	}

	GameTime& WorldState::GetGameTime()
	{
		if (mGameTime == nullptr)
		{
			throw std::exception("WorldState has no assigned GameTime. Call SetGameTime() first.");
		}

		return *mGameTime;
	}

	const GameTime& WorldState::GetGameTime() const
	{
		if (mGameTime == nullptr)
		{
			throw std::exception("WorldState has no assigned GameTime. Call SetGameTime() first.");
		}

		return *mGameTime;
	}

	void WorldState::SetGameTime(GameTime& gameTime)
	{
		mGameTime = &gameTime;
	}

	bool WorldState::IsGameTimeSet() const
	{
		return (mGameTime != nullptr);
	}

	float WorldState::DeltaTime() const
	{
		return mGameTime->ElapsedGameTime().count()/1000.0f;
	}
}