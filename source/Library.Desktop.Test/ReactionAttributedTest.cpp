#pragma once

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace std::chrono;

namespace LibraryDesktopTest
{
	TEST_CLASS(ReactionAttributedTest)
	{
	public:

		TEST_METHOD_INITIALIZE(Initialize)
		{
#if !defined(NDEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
#if !defined(NDEBUG)

			Event<EventMessage>::UnsubscribeAll();
			Attributed::ClearPrescribedAttributeCache();

			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif
		}

		TEST_METHOD(Constructor)
		{
			ReactionAttributed reaction;
			Assert::IsTrue(reaction[ReactionAttributed::KEY_SUBTYPE] == ReactionAttributed::DEFAULT_SUBTYPE);
			Assert::IsTrue(reaction.IsPrescribedAttribute(ReactionAttributed::KEY_SUBTYPE));
		}

		TEST_METHOD(SetSubtype)
		{
			ReactionAttributed reaction;
			reaction.SetSubtype("Beep");

			Assert::IsTrue(reaction[ReactionAttributed::KEY_SUBTYPE] == "Beep");
		}

		TEST_METHOD(NotifyTest)
		{
			XmlParseMaster parseMaster;
			ScopeSharedData scopeData;
			XmlParseHelperWorld parseHelperWorld;
			XmlParseHelperScope parseHelperScope;
			EntityFactory entityFactory;
			ReactionAttributedFactory reactionAttributedFactory;
			ActionIncrementFactory actionIncrementFactory;

			parseMaster.SetSharedData(&scopeData);
			parseMaster.AddHelper(parseHelperWorld);
			parseMaster.AddHelper(parseHelperScope);

			parseMaster.ParseFromFile("../../../files/ReactionTest.xml");

			World* world = static_cast<World*>(scopeData.mScope);
			WorldState state;
			GameTime gameTime;
			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(0)));
			state.mWorld = world;
			state.SetGameTime(gameTime);

			// Ensure that whenever an ActionEvent of type "type1" is raised,
			// the player's health increases by 1.
			Sector& sector0 = static_cast<Sector&>(world->Sectors()[0]);
			Entity& player = static_cast<Entity&>(sector0.Entities()[0]);

			Assert::IsTrue(player["Health"] == 100);
			Assert::IsTrue(player["Speed"] == 3.0f);

			ActionEvent healthTick;
			healthTick[ActionEvent::KEY_SUBTYPE] = "type1";
			healthTick["Extra"] = 10;
			healthTick.Update(state);

			world->GetEventQueue().Update(gameTime);
			Assert::IsTrue(player["Health"] == 101);
			Assert::IsTrue(player["Speed"] == 3.0f);

			healthTick[ActionEvent::KEY_SUBTYPE] = "something";
			healthTick.Update(state);
			world->GetEventQueue().Update(gameTime);
			Assert::IsTrue(player["Health"] == 101);
			Assert::IsTrue(player["Speed"] == 3.0f);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState ReactionAttributedTest::sStartMemState;
}
