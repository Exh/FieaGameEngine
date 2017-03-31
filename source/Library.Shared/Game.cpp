#include "pch.h"

namespace FieaGameEngine
{
	Game::Game() :
		mWorld(nullptr)
	{

	}

	Game::~Game()
	{
		delete mWorld;
		mWorld = nullptr;
	}

	void Game::Initialize()
	{
		mGameClock.Reset();
		mWorldState.SetGameTime(mGameTime);
	}

	void Game::LoadWorld(const char* filename)
	{
		// This method can be used for loading different worlds at runtime.
		// There might already be a world loaded, so delete it first.
		delete mWorld;
		mWorld = nullptr;

		XmlParseMaster worldParser;
		XmlParseHelperWorld worldParseHelper;
		XmlParseHelperScope scopeParseHelper;
		ScopeSharedData scopeSharedData;

		worldParser.SetSharedData(&scopeSharedData);
		worldParser.AddHelper(worldParseHelper);
		worldParser.AddHelper(scopeParseHelper);

		worldParser.ParseFromFile(filename);

		mWorld = static_cast<World*>(scopeSharedData.SnatchScope());

		if (mWorld == nullptr)
		{
			throw std::exception("Failed to find World. Is the root element a World?");
		}
	}

	void Game::Update()
	{
		mGameClock.UpdateGameTime(mGameTime);

		if (mWorld != nullptr)
		{
			mWorld->Update(mWorldState);
		}
	}

	void Game::Render()
	{
	
	}

	void Game::Shutdown()
	{
		// TODO: Shutdown renderer
	}
}