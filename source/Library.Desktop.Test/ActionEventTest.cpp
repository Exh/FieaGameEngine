#pragma once

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace std::chrono;

namespace LibraryDesktopTest
{
	TEST_CLASS(ActionEventTest)
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
			ActionEvent actionEvent;
			Assert::IsTrue(actionEvent.IsPrescribedAttribute("this"));
			Assert::IsTrue(actionEvent.IsPrescribedAttribute(ActionEvent::KEY_SUBTYPE));
			Assert::IsTrue(actionEvent.IsPrescribedAttribute(ActionEvent::KEY_DELAY));
			Assert::IsTrue(actionEvent[ActionEvent::KEY_SUBTYPE] == ActionEvent::DEFAULT_SUBTYPE);
			Assert::IsTrue(actionEvent[ActionEvent::KEY_DELAY] == ActionEvent::DEFAULT_DELAY);
		}

		TEST_METHOD(Update)
		{
			World world;
			WorldState worldState;
			GameTime gameTime;

			worldState.mWorld = &world;
			worldState.SetGameTime(gameTime);

			ActionEvent actionEvent;

			actionEvent[ActionEvent::KEY_SUBTYPE] = "Beep";
			actionEvent[ActionEvent::KEY_DELAY] = 300;

			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(0)));

			Assert::IsTrue(world.GetEventQueue().IsEmpty() == true);
			Assert::IsTrue(world.GetEventQueue().Size() == 0U);

			actionEvent.Update(worldState);
			Assert::IsTrue(world.GetEventQueue().IsEmpty() == false);
			Assert::IsTrue(world.GetEventQueue().Size() == 1U);

			world.GetEventQueue().Update(gameTime);
			Assert::IsTrue(world.GetEventQueue().IsEmpty() == false);
			Assert::IsTrue(world.GetEventQueue().Size() == 1U);

			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(500)));
			world.GetEventQueue().Update(gameTime);
			Assert::IsTrue(world.GetEventQueue().IsEmpty() == true);
			Assert::IsTrue(world.GetEventQueue().Size() == 0U);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState ActionEventTest::sStartMemState;
}
