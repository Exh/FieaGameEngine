#pragma once

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{
	TEST_CLASS(ActionDestroyActionTest)
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

		TEST_METHOD(ConstructorTest)
		{
			ActionDestroyAction action;
			Assert::IsTrue(action.IsPrescribedAttribute(Action::KEY_NAME));
		}

		TEST_METHOD(UpdateTest)
		{
			EntityFactory entityFactory;
			ActionIncrementFactory incrementActionFactory;
			ActionDestroyActionFactory destroyActionFactory;
			World world;
			WorldState state;

			state.mWorld = &world;
			Sector* sector = world.CreateSector();
			Entity* entity = sector->CreateEntity("Entity");

			entity->SetName("Chips");
			entity->CreateAction("ActionIncrement", "Incy");

			Action* destroyer = entity->CreateAction("ActionDestroyAction", "Destroyer");
			(*destroyer)["target"] = "Incy";

			Assert::IsTrue(entity->Actions().Size() == 2);
			world.Update(state);
			Assert::IsTrue(entity->Actions().Size() == 1);
			Assert::IsTrue(entity->Actions()[0][Action::KEY_NAME] == "Destroyer");
			Assert::IsTrue(entity->Actions()[0].Is(ActionDestroyAction::TypeIdClass()));

			// Update again to ensure that destroyer does nothing if it can't find its target
			world.Update(state);
			Assert::IsTrue(entity->Actions().Size() == 1);
			Assert::IsTrue(entity->Actions()[0][Action::KEY_NAME] == "Destroyer");
			Assert::IsTrue(entity->Actions()[0].Is(ActionDestroyAction::TypeIdClass()));

			// Add another ActionDestroyAction but do not set it's target. 
			// Ensure that it's Update() will do nothing.
			entity->CreateAction("ActionDestroyAction", "Destroyer2");
			Assert::IsTrue(entity->Actions().Size() == 2);
			world.Update(state);
			Assert::IsTrue(entity->Actions().Size() == 2);
			Assert::IsTrue(entity->Actions()[0][Action::KEY_NAME] == "Destroyer");
			Assert::IsTrue(entity->Actions()[0].Is(ActionDestroyAction::TypeIdClass()));
			Assert::IsTrue(entity->Actions()[1][Action::KEY_NAME] == "Destroyer2");
			Assert::IsTrue(entity->Actions()[1].Is(ActionDestroyAction::TypeIdClass()));

		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState ActionDestroyActionTest::sStartMemState;
}
